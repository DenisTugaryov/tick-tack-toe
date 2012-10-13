#ifndef CELL_H
#define CELL_H


enum CCell_state
{
	EMPTY,
	X,
	O
};

struct CCell
{
	CCell_state state;
	double weight;
};

#endif //CELL_H