#include <mysemaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	int i, write = 10;
	sem_create(write);
	FILE *text;
	char str[] = "hello my name is jesus pereyra";
	text = fopen("/home/text.txt", "w");
	for(i = 0; i < 5; i++){	
		fseek(text, SEEK_SET, 0);
		sem_down(write);
		printf("Proceso %i empieza a escribir", i);
 		fwrite(str, 1, sizeof(str), text);
		sem_up(write);
		printf("Proceso termino de escribir \n\n");
	}
	fclose(text);
	sem_terminate(write);
	return 0;
		
}


