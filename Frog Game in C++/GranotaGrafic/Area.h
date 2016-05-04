#pragma once

class Area
{
public:
	Area();
	Area(int minX, int maxX, int minY, int maxY);
	~Area();
	int getMinX();
	int getMaxX();
	int getMinY();
	int getMaxY();
	bool pertany(int x, int y);
	bool inclou(Area area);
	bool solapa(Area area);

private:
	int m_minX;
	int m_maxX;
	int m_minY;
	int m_maxY;
};

