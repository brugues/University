
#include "Cronometre.h"

Cronometre::Cronometre()
{

}

Cronometre::Cronometre(Grafic numeros[], int posX, int posY)
{
	for (int i = 0; i < TOTAL_DIGITOS; i++)
		m_numero[i] = numeros[i];

	m_pos_U_X = posX;
	m_pos_U_Y = posY;
	m_pos_D_X = m_pos_U_X - 25;
	m_pos_D_Y = m_pos_U_Y;
	m_pos_C_X = m_pos_D_X - 25;
	m_pos_C_Y = m_pos_D_Y;
}

Cronometre::~Cronometre()
{
}


/**
* Funcio per dibuixar els numeros del rellotge
@param numero es vol escriure en la pantalla
@param pos_X posicio en el eix X on es vol pintar el grafic
@param pos_Y posicion en el eix Y on es vol pintar el grafic
*/
void Cronometre::mostrarCifra(int numero,int pos_X,int pos_Y)
{

	switch (numero)
	{
	case 0:
		m_numero[0].dibuixa(pos_X, pos_Y);
		break;
	case 1:
		m_numero[1].dibuixa(pos_X, pos_Y);
		break;
	case 2:
		m_numero[2].dibuixa(pos_X, pos_Y);
		break;
	case 3:
		m_numero[3].dibuixa(pos_X, pos_Y);
		break;
	case 4:
		m_numero[4].dibuixa(pos_X, pos_Y);
		break;
	case 5:
		m_numero[5].dibuixa(pos_X, pos_Y);
		break;
	case 6:
		m_numero[6].dibuixa(pos_X, pos_Y);
		break;
	case 7:
		m_numero[7].dibuixa(pos_X, pos_Y);
		break;
	case 8:
		m_numero[8].dibuixa(pos_X, pos_Y);
		break;
	case 9:
		m_numero[9].dibuixa(pos_X, pos_Y);
		break;
	}
}

/**
* Funció per dibuixar el cronòmetre del temps que es porta jugant
* @param t aporta el temps de quan s'ha iniciat el joc
* @param t_it temps actual del joc
* @param t_dif diferència entre els dos temps
*/
void Cronometre::dibuixa(int& t_dif)
{
	//Inicialització de les variables necessàries
	int u; //Variable per emmagatzemar el nombre de les unidades
	int d; //Variable per emmagatzemar el nombre de les desenes
	int c;//Variable per emmagatzemar el nombre de les centenes
	if (t_dif < 10)
	{
		u = t_dif;
		mostrarCifra(u, m_pos_U_X,m_pos_U_Y );
	}
	else
	{
		if (t_dif < 100)
		{
			d = int(t_dif / 10);
			u = t_dif - d * 10;
			mostrarCifra(u, m_pos_U_X, m_pos_U_Y);
			mostrarCifra(d, m_pos_D_X, m_pos_D_Y);
		}
		else
		{
			if (t_dif < 1000)
			{
				c = int(t_dif / 100);
				d = int((t_dif - c * 100) / 10);
				u = t_dif - c * 100 - d * 10;
				mostrarCifra(u, m_pos_U_X, m_pos_U_Y);
				mostrarCifra(d, m_pos_D_X, m_pos_D_Y);
				mostrarCifra(c, m_pos_C_X, m_pos_C_Y);
			}
		}
	}
}
