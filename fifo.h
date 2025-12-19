#ifndef __FIFO_DEFINED__
#define __FIFO_DEFINED__

class Fifo
{
public:
	Fifo(int size);
	~Fifo();
	void Push(int value);
	int Pop();
	void Reset();
	bool Empty();
	int Count();

private:
	int* buf;
	int qsize;
	int fi, bi;
};

#endif // __FIFO_DEFINED__
