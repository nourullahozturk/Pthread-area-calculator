//#include <pthread.h>
//#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <chrono>
#include <iostream>
#include "myTime.h"

#include "hDef.h"

#include "hTest1.h"
#include "hTest2.h"
#include "hTest3.h"
// #include "hTest4.h"
#include "hQuiz.h"

using namespace std;
using namespace std::chrono;

void fAreaSeri()
{
	double x;
	struct timeval tStrt, tStop;

	printf("Seri fonksiyon basladi...\n");

	auto BslTimer = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	gettimeofday(&tStrt, nullptr);

	gPi = 0.0;
	double step = 1.0 / N;

	for (int i = 0; i < N; i++) {
		x = (i + 0.5f) * step;
		gPi += step * 4.0 / (1.0 + x * x); // sqrt(1.0 - x^2) * h
	}

	auto BtsTimer = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	gettimeofday(&tStop, nullptr);

	auto tm = BtsTimer - BslTimer;
	printf("System time: %d ms\n", tm);
	printf("Sure: %.1f ms\nPi: %12.9f\n", fSure(&tStop, &tStrt), gPi);
}

void *fMerhaba(void* pArg) {
	int myId = *((int*)pArg);
	printf("Merhaba ben: %5d,\n", myId);
	return 0;
}

void fMesaj() {
	for (i = 0; i < NTHREADS; ++i) {
		tNum[i] = i;
		pthread_create(&tHandles[i], NULL, fMerhaba, (void*)&tNum[i]);
	}

	for (i = 0; i < NTHREADS; ++i) {
		pthread_join(tHandles[i], NULL);
	}
}

int main(int argc, char **argv) {
	//fMesaj();
	fAreaSeri();
	fTest1();
	fTest2();
	fTest3();
	fQuiz();
	getchar();
	return 0;
}




