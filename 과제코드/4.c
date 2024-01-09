#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
int MAX = 30;
int A[30];	
int B[30];
int *m;									
int Min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;
}
int airtelDong(int n, int s, int d) {
	int total = 0;
	m = (int*)malloc(sizeof(int) * n);
	m[s] = 0;
	for (int i = s + 1; i <= d; i++) {
		m[i] = 999999;
		for (int j = s; j < i; j++) {
			if (j == s)
				total = m[j] + A[i - j];
			else
				total = m[j] + B[j] + A[i - j];
			m[i] = Min(m[i], total);
		}
	}
	return m[d];
}	
int rAirtelBun(int s, int d) {
	int minimum = 999999;
	int total = 0;
	if (s == d)					
		return 0;
	for (int i = 0; i < d; i++) {
		if (i == s)		
			total = rAirtelBun(s, i) + A[d - i];
		else
			total = rAirtelBun(s, i) + B[i] + A[d - i];
		minimum = Min(minimum, total);
	}
	return minimum;
}
int airtelBun(int n, int s, int d) {
	return rAirtelBun(s, d);
}
int main() {
	int n, s, d, mincost;
	int sd[3][2] = { {0,4},{2,5},{2,4} };
    clock_t S, E;
    srand(time(NULL));
	A[0] = 0;									
	A[1] = 1;
	for (int i = 2; i < MAX; i++)
		A[i] = A[i - 1] + A[i - 1] % 5 + 3;

	B[0] = 0;
	B[1] = 5;
	for (int i = 2; i < MAX; i++)
		B[i] = (B[i - 1] + i) % 9 + 1;
	printf("  n  s  d   mincost  version   cputime\n");
	n = 6;

	for (int i = 0; i < 3; i++) {
		s = sd[i][0];
		d = sd[i][1];

		S = clock();
		mincost = airtelBun(n, s, d);
		E = clock();
		double cpu_time_used = ((double)(E - S)) / CLOCKS_PER_SEC * 1000;
		printf("%3d%3d%3d  %8d    %s    %.8f\n", n, s, d, mincost, "DC", cpu_time_used);

		S = clock();
		mincost = airtelDong(n, s, d);
		E = clock();
		cpu_time_used = ((double)(E - S)) / CLOCKS_PER_SEC * 1000;
		printf("%3d%3d%3d  %8d    %s    %.8f\n", n, s, d, mincost, "DP", cpu_time_used);

		free(m);	
	}
    d = MAX - 2;
	s = 1;
	n = MAX;

	S = clock();
	mincost = airtelBun(n, s, d);
	E = clock();
	double cpu_time_used = ((double)(E - S)) / CLOCKS_PER_SEC * 1000;
    printf("%3d%3d%3d  %8d    %s    %.8f\n", n, s, d, mincost, "DC", cpu_time_used);

	S = clock();
	mincost = airtelDong(n, s, d);
	E = clock();
	cpu_time_used = ((double)(E - S)) / CLOCKS_PER_SEC * 1000;
    printf("%3d%3d%3d  %8d    %s    %.8f\n", n, s, d, mincost, "DP", cpu_time_used);
	free(m);	

	return 0;
}