#include <lib.h>
#include <unistd.h>
#include <stdio.h>

void sig(int singo)
{
	return;
}

int semaphore(int id, int choice){
	message m;
	m.m1_i1 = id;
	m.m1_i2 = getpid();
	return (_syscall(PM_PROC_NR, choice, &m)); 
}

int sem_create(int id)
{
	int j = semaphore(id, PM_SEM_CREATE);
	if(j == 0){
		return 0;
	}
	else
		return -1;
}

int sem_terminate(int id)
{
	int j = semaphore(id, PM_SEM_TERMINATE);
	if(j == 0)
		return 0;
	else
		return -1;
}

int sem_down(int id)
{
//	if(signal(SIGSTOP, sig));
	int lock = 1;
	while(lock == 1){
		pause();
		lock = semaphore(id, PM_SEM_DOWN);
	}
	return lock;
	
	
}

int sem_up(int id)
{
//	if(signal(SIGCONT, sig));
	int j = semaphore(id, PM_SEM_UP);
	if(j == 0)
		return 0;
	else
		return -1;
}
