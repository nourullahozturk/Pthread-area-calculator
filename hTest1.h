
void* fArea1(void* pArg) {
	int myId = *((int*)pArg);
	double step = 1.0 / N;
	double x;
	struct timeval tStrt, tStop;
	gettimeofday(&tStrt, nullptr);

	// Her thread kendi id'sinden baslayarak 8er 8er islem yapar. boylece hepsine esit is paylastirilmis olur.
	for (int i = myId; i < N; i += NTHREADS) {
		x = (i + 0.5f) * step;
		gPi += step * 4.0 / (1.0 + x * x);
	}

	gettimeofday(&tStop, nullptr);
	printf("Id: %5d,     %12.1f ms\n", myId, fSure(&tStop, &tStrt));
	return 0;
	
}

void fTest1() {

	gettimeofday(&tStrt, nullptr);
	printf("\n\nTest-1 basladi...\n");
	gPi = 0.0;

	for(i=0; i<NTHREADS; ++i){
		tNum[i] = i;
		//4.parametre fArea1 fonksiyonuna verilen argumani belirtir (myId).
		pthread_create(&tHandles[i], NULL, fArea1, (void*)(&tNum[i]));
	}

	for (i = 0; i < NTHREADS; ++i) {
		pthread_join(tHandles[i], NULL);
	}

	gettimeofday(&tStop, nullptr);
	printf("Test-1: Toplam Sure:  %12.1f ms\n", fSure(&tStop, &tStrt));
	printf("Pi Degeri:  %12.9f \n", gPi);
}

