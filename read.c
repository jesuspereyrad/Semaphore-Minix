#include <mysemaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	int read = 10;
	sem_create(read);
	FILE *text;
	char buffer[100];
	text = fopen("/home/text.txt", "r");
	fseek(text, SEEK_SET, 0);
	while(!feof(text)){
		sem_down(read);
		printf("Proceso esta leyendo del archivo");
 		fread(buffer, sizeof(buffer), 1, text);
		sem_up(read);
		printf("Proceso termino de leer del archivo\n\n");
	}
	fclose(text);
	sem_terminate(read);
	return 0;
		
}


