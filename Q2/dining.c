#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

// Codes for processes
// 1. Waiting for Spoons
// 2. One spoon acquired.
// 3. Both spoons acquired and eating
// 4. Thinking (< 2 seconds)

FILE *fptr;

#define NUMBER_OF_PHILOSOPHERS 5
int a[5];

pthread_mutex_t chopsticks[NUMBER_OF_PHILOSOPHERS];
pthread_t philosophers[NUMBER_OF_PHILOSOPHERS];
pthread_attr_t attributes[NUMBER_OF_PHILOSOPHERS];
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

int stat[5]; 

void print_status() {
    pthread_rwlock_wrlock(&rwlock);
    fptr = fopen("file_name", "a");
    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i) {
		if(stat[i]==1) {
			fprintf(fptr,"S%d: Waiting for spoons.\n", i);
			printf("S%d: Waiting for spoons.\n", i);
		}
		if(stat[i]==2) {
			fprintf(fptr,"S%d: One spoon acquired.\n", i);
			printf("S%d: One spoon acquired.\n", i);
		}
		if(stat[i]==3) {
			fprintf(fptr,"S%d: Both spoons acquired and eating.\n", i);	
			printf("S%d: Both spoons acquired and eating.\n", i);
		}
		if(stat[i]==4) {
			fprintf(fptr,"S%d: Thinking.\n", i);	
			printf("S%d: Thinking.\n", i);
		}
	}
	fprintf(fptr,"---------------------------------------------\n");	
	printf("---------------------------------------------\n");
	fclose(fptr);
	pthread_rwlock_unlock(&rwlock);
}

void think(int philosopherNumber) {
	int sleepTime = 2;
	if(stat[philosopherNumber]!=4) {
		stat[philosopherNumber]=4;
		print_status();
	}
	sleep(sleepTime);
	if(stat[philosopherNumber]!=1) {
		stat[philosopherNumber]=1;
		print_status();
	}
}

void pickUp(int philosopherNumber) {
	int right = (philosopherNumber + 1) % NUMBER_OF_PHILOSOPHERS;
	int left = (philosopherNumber + NUMBER_OF_PHILOSOPHERS) % NUMBER_OF_PHILOSOPHERS;
	if (philosopherNumber & 1) {
		pthread_mutex_lock(&chopsticks[right]);
		stat[philosopherNumber]=2;
		print_status();
		pthread_mutex_lock(&chopsticks[left]);
	}
	else {
		pthread_mutex_lock(&chopsticks[left]);
		stat[philosopherNumber]=2;
		print_status();
		pthread_mutex_lock(&chopsticks[right]);
	}
}

void eat(int philosopherNumber) {
	int eatTime = 20;
	stat[philosopherNumber]=3;
	print_status();
	sleep(eatTime);
}

void putDown(int philosopherNumber) {
	pthread_mutex_unlock(&chopsticks[(philosopherNumber + 1) % NUMBER_OF_PHILOSOPHERS]);
	pthread_mutex_unlock(&chopsticks[(philosopherNumber + NUMBER_OF_PHILOSOPHERS) % NUMBER_OF_PHILOSOPHERS]);
}


void *philosopher(void *philosopherNumber) {
	int *ptr = (int *) philosopherNumber;
	while (1) {
		pickUp(*ptr);
		eat(*ptr);
		putDown(*ptr);
		think(*ptr);
	}
}

int main() {
	for(int i=0;i< NUMBER_OF_PHILOSOPHERS;i++) {
		a[i]=i;
		stat[i]=1;
	}
	print_status();
	int i;
	srand(time(NULL));
	for (i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i) {
		pthread_mutex_init(&chopsticks[i], NULL);
	}

	for (i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i) {
		pthread_attr_init(&attributes[i]);
	}
	
	pthread_create(&philosophers[0], &attributes[0], philosopher, (void *)(&a[0]));
	pthread_create(&philosophers[1], &attributes[1], philosopher, (void *)(&a[1]));
	pthread_create(&philosophers[2], &attributes[2], philosopher, (void *)(&a[2]));
	pthread_create(&philosophers[3], &attributes[3], philosopher, (void *)(&a[3]));
	pthread_create(&philosophers[4], &attributes[4], philosopher, (void *)(&a[4]));
	

	for (i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i) {
		pthread_join(philosophers[i], NULL);
	}
	return 0;
}
