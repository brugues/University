#include <pthread.h>
#include <stdio.h> /* printf, scanf, NULL */
#include <string.h> // string
#include <stdlib.h>	/* malloc, free, rand */
#include <unistd.h>	// Funciones del sistema: exit, fork, read, write
#include <time.h> /* time*/

//syscall(). How to obtain gettid in c with syscall

#define NUM_CONSUMER 1
#define NUM_PETICIONES 100
#define TAM_BUFFER 5

FILE *compras;

typedef struct
{
	int id_cliente;
	int id_compra;

}peticion_t;

typedef struct
{
	int pos_lectura; // Siguiente posicion a leer
	int pos_escritura; // Siguiente posicion a escribir
	int num_peticiones; // Numero de peticiones en el buffer
	peticion_t peticiones[TAM_BUFFER]; // Buffer de peticiones (circular)

}buffer_peticiones_t;


buffer_peticiones_t bufferPeticiones; //Declaracion del buffer de peticiones
buffer_peticiones_t bufferPrioridad;
pthread_mutex_t mutex; //Declaracion del semaforo para controlar el acceso al buffer de peticiones
pthread_mutex_t mutexPrioridad;

pthread_cond_t normales;
pthread_cond_t prioritarios;

/**
* Inicializa la estructura del buffer y sus centinelas @pos_lectura y @pos_escritura
*/
void buffer_inicializar(buffer_peticiones_t* buffer_peticiones)
{
	buffer_peticiones->pos_lectura = 0;
	buffer_peticiones->pos_escritura = 0;
	buffer_peticiones->num_peticiones = 0;
}

/**
* Devuelve 1 si el buffer esta completamente lleno, 0 en caso contrario
*/
int buffer_lleno(buffer_peticiones_t* buffer_peticiones)
{
	if (buffer_peticiones->num_peticiones == TAM_BUFFER)
		return 1;
	else
		return 0;
}

/**
* Devuelve 1 si el buffer esta completamente vacio, 0 en caso contrario
*/
int buffer_vacio(buffer_peticiones_t* buffer_peticiones)
{
	if (buffer_peticiones->num_peticiones == 0)
		return 1;
	else;
		return 0;
}

/**
* Encola @peticion en el buffer
*/
void buffer_encolar(buffer_peticiones_t* buffer,pthread_mutex_t* mutex, pthread_cond_t* cond, peticion_t* peticion)
{
	pthread_mutex_lock(mutex);
	while (buffer_lleno(buffer) == 1)
		pthread_cond_wait(cond, mutex);

	buffer->peticiones[buffer->pos_escritura] = *peticion;
	buffer->pos_escritura = ((buffer->pos_escritura + 1) % TAM_BUFFER);
	buffer->num_peticiones++;
	pthread_mutex_unlock(mutex);
}

/**
* Retira del buffer la peticion mas antigua (FIFO)S la copia en @peticion
*/
void buffer_peticiones_atender(buffer_peticiones_t* buffer_peticiones, buffer_peticiones_t* buffer_prioridad, peticion_t* peticion)
{
	pthread_mutex_lock(&mutexPrioridad);

	if (buffer_vacio(buffer_prioridad) == 0)
	{
		*peticion = buffer_prioridad->peticiones[buffer_prioridad->pos_lectura];
		buffer_prioridad->pos_lectura = ((buffer_prioridad->pos_lectura + 1) % TAM_BUFFER);
		buffer_prioridad->num_peticiones = buffer_prioridad->num_peticiones - 1;
		pthread_cond_signal(&prioritarios);
		fprintf(compras, "Id compra: %d; Id comprador: %d \n", peticion->id_compra, peticion->id_cliente);
	}

	pthread_mutex_unlock(&mutexPrioridad);
	pthread_mutex_lock(&mutex);

	if ((buffer_vacio(buffer_prioridad) == 1)&&(buffer_vacio(buffer_peticiones) == 0))
	{
		*peticion = buffer_peticiones->peticiones[buffer_peticiones->pos_lectura];
		buffer_peticiones->pos_lectura = ((buffer_peticiones->pos_lectura + 1) % TAM_BUFFER);
		buffer_peticiones->num_peticiones = buffer_peticiones->num_peticiones - 1;
		pthread_cond_signal(&normales);
		fprintf(compras, "Id compra: %d; Id comprador: %d \n", peticion->id_compra, peticion->id_cliente);
	}

	pthread_mutex_unlock(&mutex);
}

/**
 * Función consumidor que de servidor recibiendo las peticiones del buffer y guardandolas en fichero
 * @param int thread_id: id del trhead
 */
//(RAW) void* ptrhead_funcion (void* thread_number)
void* consumer_function(int thread_id)
{
	peticion_t peticion_recibida;

	while (1)
	{
		buffer_peticiones_atender(&bufferPeticiones, &bufferPrioridad, &peticion_recibida);
		if((peticion_recibida.id_cliente == 0) && (peticion_recibida.id_compra == 0))
			break;
	}

	fclose(compras);
	pthread_exit(NULL);
}

/**
 * Función productor que hace de cliente creando las peticiones y enviandolas por el buffer
 * @param int thread_id: id del trhead
 */
void* producer_function(int thread_id)
{
	int pid = (int)getpid();
	int i, aleatorio;
	peticion_t peticion;
	srand(time(NULL) + getpid());

	for (i = 1; i <= NUM_PETICIONES; i++)
	{
		aleatorio = rand() % 3;
		peticion.id_compra =  i;
		peticion.id_cliente = thread_id;

		if (aleatorio == 0)
			buffer_encolar(&bufferPrioridad,&mutexPrioridad,&prioritarios, &peticion);
		else
			buffer_encolar(&bufferPeticiones,&mutex,&normales, &peticion);
	}

	pthread_exit(NULL);
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("%s Numero de clients erroni\n", argv[0]);
		return 1;
	}

	//Create threads
	long int i;
	int numero_clientes = atoi(argv[1]);
	pthread_t consumer[NUM_CONSUMER];
	pthread_t *producer;
	producer = (pthread_t*) malloc (numero_clientes*sizeof(pthread_t));

	//Inicialización del buffer peticiones
	buffer_inicializar(&bufferPeticiones);
	buffer_inicializar(&bufferPrioridad);

	//Inicialización del mutex
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&mutexPrioridad, NULL);

	//Inicializacion de las condiciones
	pthread_cond_init(&normales, NULL);
	pthread_cond_init(&prioritarios, NULL);


	for (i = 0; i < numero_clientes; i++)
		pthread_create(producer+i, NULL, (void* (*)(void*))producer_function,(void*)(i));

	compras = fopen("compras.txt", "w");
	if (compras == NULL)
		perror("Error al abrir el fichero");

	for (i = 0; i < NUM_CONSUMER; i++)
		pthread_create(consumer+i, NULL, (void* (*)(void*))consumer_function,(void*)(i));

	//Wait for threads
	for(i = 0; i < numero_clientes; i++)
		pthread_join(producer[i], NULL);

	//Peticion final
	peticion_t final;
	final.id_cliente = 0;
	final.id_compra = 0;

	buffer_encolar(&bufferPeticiones,&mutex,&normales, &final);

	for(i = 0; i < NUM_CONSUMER; i++)
		pthread_join(consumer[i], NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&normales);
	pthread_mutex_destroy(&mutexPrioridad);
	pthread_cond_destroy(&prioritarios);

	free(producer);

	return 0;
}
