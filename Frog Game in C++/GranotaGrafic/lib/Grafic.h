#pragma once
#include "libreria.h"

class Grafic
{
public:
	Grafic(void);
	~Grafic(void);

	bool crea(char* nom);
	int getScaleX();
	int getScaleY();
	void setScale(float scale);
	void destrueix();
	void dibuixa(int x, int y);
private:
	struct T_SPRITE *sprite;
};
