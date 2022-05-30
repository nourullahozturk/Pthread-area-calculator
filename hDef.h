#include <pthread.h>

#define N 200000000
#define NTHREADS 8

double gPi = 0.0;

double lPi[NTHREADS] = { 0.0 };
pthread_t tHandles[NTHREADS];
int tNum[NTHREADS], i;
struct timeval tStrt, tStop;

int step_t = N / NTHREADS; //25.000.000

/* 
	myId	baþlangýç			son
	0		0					25.000.000
	1		25.000.000			50.000.000
	2		50.000.000			75.000.000
	3		75.000.000			100.000.000
	4		100.000.000			125.000.000
	5		125.000.000			150.000.000
	6		150.000.000			175.000.000
	7		175.000.000			200.000.000

	myId	myId*25.000.000		myId*25.000.000 + 25.000.000
*/