#include <mysemaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void AdultEat(int adult_sem, int k){
	sem_down(adult_sem);
	printf("======Adult %d is eating\n",k);
	sleep(15);
	sem_up(adult_sem);
	printf("=====Adult %d is done", k); 
}

void Adult(int cake, int adult_sem){
	int i = 0;
	while(i < 1) {
		sem_down(cake);
		int k;
		printf("====Only adults can eat\n");
		for(k = 1; k < 3; k++){
			if(fork() == 0){
				AdultEat(adult_sem, k);
			}
		}
		sem_up(cake);
		printf("===Adults are done eating\n");
		i++;
	}
}


void ChildEat(int child_sem, int k){
	sem_down(child_sem);
	printf("====Child %d is eating...\n", k);
	sleep(15);
	sem_up(child_sem);
	printf("====Child %d is done...\n", k);
}

void Child(int cake, int child_sem){
	int i = 0, k;	
	while( i < 1) {
		sem_down(cake);
		printf("==== Only Childs can eat \n");
		for(k = 1; k <= 2; k++){
			if(fork() == 0){
				ChildEat(child_sem, k);
			}
		}
		sem_up(cake);
		printf("---Childs done eating\n");
		i++;
	}
}
int main(){
	int i;
	
	int cake = 0; 
	sem_create(cake);
	int adult_sem = 1;
	sem_create(adult_sem);
	int child_sem = 2;
	sem_create(child_sem);

	if(fork()==0){
	  Adult(cake,adult_sem);
	  Child(cake,child_sem);
	}
		
	sem_terminate(adult_sem);
        sem_terminate(child_sem);	
	sem_terminate(cake);
	return 0;	
}


