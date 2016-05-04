#include "Grafic.h"

#include "libreria.h"


Grafic::Grafic(void)
{
}


Grafic::~Grafic(void)
{
}

bool Grafic::crea(char* nom)
{
	sprite = Sprite_Create (nom);
	if (sprite->frame_actual->pixels != NULL)
		return true;
	else 
		return false;
}

int Grafic::getScaleX()
{
	return sprite->frame_actual->tamx;
}

int Grafic::getScaleY()
{
	return sprite->frame_actual->tamy;
}
	

void Grafic::setScale(float scale)
{
	Sprite_SetScale(sprite, scale);
}

void Grafic::destrueix()
{
	Sprite_Delete(sprite);
}

void Grafic::dibuixa(int x, int y)
{
	Sprite_Draw(sprite, x, y);
}