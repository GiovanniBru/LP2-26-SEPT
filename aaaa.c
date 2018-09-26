#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_THREADS 10

int x;
int prox; 
int num;
int turno[MAX_THREADS] = {0,0,0,0,0,0,0,0,0,0};

void* manipulaVariavel(void* y){
	int indice = (int)y;
	int exec = 0;
	printf("THREAD %d - Executando Funcao", indice);
	
	while(exec < 10){
		exec++;
		turno[indice] = __sync_fetch_and_add(&num,1); //protocolo de entrada
		while(turno[indice] !=prox); //protocolo de entrada
		if(indice % 2){
			x+= indice;
		}else{
			x+= (2*indice);
		}
		//secao critica
		printf("THREAD %d - alterei o valor da variavel para %d\n", indice, x);
		prox++;
	}
	return 0;
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
		result_create_thread = pthread_create(&threads[i], NULL, manipulaVariavel, (void*)i);
		if(result_create_thread){
			printf("ERRO");
			exit(-1);
		}
	}	
	
	for(i = 0; i < MAX_THREADS; i++){
		pthread_join(threads[i],NULL);
	}
	
	printf("O resultado final para X: %d\n", x);
}
