
void* fArea3(void* pArg) {
	int myId = *((int*)pArg);
	double step = 1.0 / N;
	double x;
	struct timeval tStrt, tStop;
	gettimeofday(&tStrt, nullptr);

	double pPi = 0.0;

	// dongu icerisinde surekli global lPi dizine ulasmak yerine her
	// thread kendi local pPi degiskenini setliyor.
	for (int i = myId; i < N; i += NTHREADS) {
		x = (i + 0.5f) * step;
		pPi += step * 4.0 / (1.0 + x * x);
	}
	
	// Dongu disinda global diziye ataniyor.
	lPi[myId] = pPi;
	gettimeofday(&tStop, nullptr);
	printf("Id: %5d,     %12.1f ms\n", myId, fSure(&tStop, &tStrt));

	return 0;
}

void fTest3() {

	gettimeofday(&tStrt, nullptr);
	printf("\n\nTest-3 basladi...\n");

	gPi = 0.0;
	for (i = 0; i < NTHREADS; ++i) {
		tNum[i] = i;
		pthread_create(&tHandles[i], NULL, fArea3, (void*)(&tNum[i]));
	}

	for (i = 0; i < NTHREADS; ++i) {
		pthread_join(tHandles[i], NULL);
	}

	for (i = 0; i < NTHREADS; ++i) {
		gPi += lPi[i];
	}

	gettimeofday(&tStop, nullptr);
	printf("Test-3: Toplam Sure:  %12.1f ms\n", fSure(&tStop, &tStrt));
	printf("Pi Degeri:  %12.9f \n", gPi);
}

