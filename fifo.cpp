#include "fifo.h"

Fifo::Fifo(int size)
{
	qsize = size;
	buf = new int[qsize];
	Reset();
}

Fifo::~Fifo()
{
	delete buf;
}

void Fifo::Push(int value)
{
	buf[bi++] = value;
	if (bi >= qsize)
		bi = 0;
}

int Fifo::Pop()
{
	int value = buf[fi++];
	if (fi >= qsize)
		fi = 0;

	return value;
}

void Fifo::Reset()
{
	fi = bi = 0;
}

bool Fifo::Empty()
{
	return fi == bi;
}

int Fifo::Count()
{
	if (fi < bi)
		return bi - fi;
	else
		return (qsize + bi) - fi;
}

