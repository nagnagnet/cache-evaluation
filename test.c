#include <stdio.h>
#include <stdlib.h>
#define N 1024*16*5 
#define RDTSC(X) asm volatile("rdtsc; shlq $32, %%rdx; orq %%rdx, %%rax":"=r"(X) :: "%rdx")

void timer(int *num);
void shuffle(int *array, int set);

struct st{
	int num;
	char name[60];
};

int main(){
	int i, j, tmp, *array;
	char *c;
	struct st *buf;
	buf = (struct st*)malloc(sizeof(struct st)*N);
	array = (int*)malloc(sizeof(int)*N);
	
	for(i = 0; i < N; i++) {
		buf[i].num = i;
		array[i] = i;
	}

	for(i = 0; i < N; i++){
		//timer(&buf[i].num);
		c = (char*)&buf[i];
		asm __volatile__(
				"clflush 0(%0)\n"
				:
				:"c"(c)
				:
				);
		//timer(&buf[i].num);
		//printf("\n");
	}
	shuffle(array, i);
	for(i = 0; i < 10000; i++){
		for(j = 0; j < N; j++){
			tmp = buf[array[j]].num;
		}
	}
	return 0;
}

void timer(int *num){
	int tmp;
	unsigned long long t1, t2, time;
	asm("lfence");
	RDTSC(t1);
	tmp = *num;
	asm("lfence");
	RDTSC(t2);
	time = t2 - t1;
	printf("%llu\n", time);
}

void shuffle(int *array, int set){
	int i, j, tmp;
	srand(set);
	for(i = 0; i < N; i++){
		j = rand() % N;
		tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
	}
}
