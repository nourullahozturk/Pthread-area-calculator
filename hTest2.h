
void* fArea2(void* pArg) {
	int myId = *((int*)pArg);
	double step = 1.0 / N;
	double x;
	struct timeval tStrt, tStop;
	gettimeofday(&tStrt, nullptr);

	// lPi dizisi globaldir. local sonuclari tutmak uzere hDef.h'da tanimlanmistir.
	// Threadlerin gPi degiskenini ortak kullanmamasi icin gereklidir.
	lPi[myId] = 0.0;

	for (int i = myId; i < N; i += NTHREADS) {
		x = (i + 0.5f) * step;
		// Her thread kendi local pi degiskenini setliyor.
		lPi[myId] += step * 4.0 / (1.0 + x * x);
	}

	gettimeofday(&tStop, nullptr);
	printf("Id: %5d,     %12.1f ms\n", myId, fSure(&tStop, &tStrt));
	
	return 0;
}

void fTest2() {

	gettimeofday(&tStrt, nullptr);
	printf("\n\nTest-2 basladi...\n");
	
	gPi = 0.0;
	for (i = 0; i < NTHREADS; ++i) {
		tNum[i] = i;
		pthread_create(&tHandles[i], NULL, fArea2, (void*)(&tNum[i]));
	}

	for (i = 0; i < NTHREADS; ++i) {
		pthread_join(tHandles[i], NULL);
	}
	// butun threadler bittiginde local pi'ler toplaniyor.
	for (i = 0; i < NTHREADS; ++i) {
		gPi += lPi[i];
	}

	gettimeofday(&tStop, nullptr);
	printf("Test-2: Toplam Sure:  %12.1f ms\n", fSure(&tStop, &tStrt));
	printf("Pi Degeri:  %12.9f \n", gPi);
}

