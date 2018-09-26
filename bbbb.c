#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_THREADS 10

int x;
int prox; 
int num;
int turno[MAX_THREADS] = {0,0,0,0,0,0,0,0,0,0};

void* tabuada(void* param){
	int indice = (int)param;
}

int main(){
	pthread_t threads[MAX_THREADS];
	int result_create_thread;
	x = 0;
	num = 0;
	prox = 0;
	long i;
	
	for(i = 0; i < MAX_THREADS; i++){
		printf("Main: Criando Thread %ld\n", i);
		result_create_thread = pthread_create(&threads[i], NULL, tabuada, (void*)i);
		if(result_create_thread){
			printf("ERRO");
			exit(-1);
		}
	}	
	
	char line[20];
	int a = 2;
	int b = 3;
	FILE *file_descriptor;
	
	file_descriptor = fopen("arq.txt", "a");
	fprintf(file_descriptor, "%d x %d = %d\n", a ,b, (a*b));
	fclose(file_descriptor);
	
	file_descriptor = fopen("arq.txt", "r");
	fgets(line, sizeof(line), file_descriptor);
	printf("%s\n", line);
	
	return 0;
}
