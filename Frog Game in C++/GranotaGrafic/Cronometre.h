#include "Area.h"
#include "lib\Grafic.h"


const int TOTAL_DIGITOS = 10;

class Cronometre
{
public:
	Cronometre();
	Cronometre(Grafic numeros[], int posX, int posY);
	~Cronometre();
	void dibuixa(int& t_dif);

private:
	void mostrarCifra(int numero, int pos_x, int pos_y);

	Grafic m_numero[TOTAL_DIGITOS];
	int m_pos_U_X;
	int m_pos_U_Y;
	int m_pos_D_X;
	int m_pos_D_Y;
	int m_pos_C_X;
	int m_pos_C_Y;
};