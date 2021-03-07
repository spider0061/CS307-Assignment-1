// Importint Libraries
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

// File pointer to store in log files
FILE *fptr;

// Number of students
#define no_of_students 5

// Array of students
int a[5];

// Mutex locks for spoons and read write lock for writing in file
pthread_mutex_t spoons[no_of_students];
pthread_t students[no_of_students];
pthread_attr_t features[no_of_students];
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

// Status of each student
int stat[5]; 

// Function to print status and write in log file
void print_status() {
    pthread_rwlock_wrlock(&rwlock);
    fptr = fopen("file_name", "a");
    for (int i = 0; i < no_of_students; ++i) {
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

//Function when a student thinks
void think(int studentNumber) {
	int sleepTime = 2;
	if(stat[studentNumber]!=4) {
		stat[studentNumber]=4;
		print_status();
	}
	sleep(sleepTime);
	if(stat[studentNumber]!=1) {
		stat[studentNumber]=1;
		print_status();
	}
}

// Function to pick up a spoon
void pickUp(int studentNumber) {
	int right = (studentNumber + 1) % no_of_students;
	int left = (studentNumber + no_of_students) % no_of_students;
	if (studentNumber & 1) {
		pthread_mutex_lock(&spoons[right]);
		stat[studentNumber]=2;
		print_status();
		pthread_mutex_lock(&spoons[left]);
	}
	else {
		pthread_mutex_lock(&spoons[left]);
		stat[studentNumber]=2;
		print_status();
		pthread_mutex_lock(&spoons[right]);
	}
}

// Function to start eating
void eat(int studentNumber) {
	int eatTime = 20;
	stat[studentNumber]=3;
	print_status();
	sleep(eatTime);
}

// Function to put down spoons after eating
void putDown(int studentNumber) {
	pthread_mutex_unlock(&spoons[(studentNumber + 1) % no_of_students]);
	pthread_mutex_unlock(&spoons[(studentNumber + no_of_students) % no_of_students]);
}

// Initial function for each student
void *student(void *studentNumber) {
	int *ptr = (int *) studentNumber;
	while (1) {
		pickUp(*ptr);
		eat(*ptr);
		putDown(*ptr);
		think(*ptr);
	}
}

// Main function
int main() {
	for(int i=0;i< no_of_students;i++) {
		a[i]=i;
		stat[i]=1;
	}
	print_status();
	int i;
	srand(time(NULL));
	for (i = 0; i < no_of_students; ++i) {
		pthread_mutex_init(&spoons[i], NULL);
	}

	for (i = 0; i < no_of_students; ++i) {
		pthread_attr_init(&features[i]);
	}
	
	// Creating threads
	pthread_create(&students[0], &features[0], student, (void *)(&a[0]));
	pthread_create(&students[1], &features[1], student, (void *)(&a[1]));
	pthread_create(&students[2], &features[2], student, (void *)(&a[2]));
	pthread_create(&students[3], &features[3], student, (void *)(&a[3]));
	pthread_create(&students[4], &features[4], student, (void *)(&a[4]));
	
	// Waiting for all threads to complete execution
	pthread_join(students[0], NULL);
	pthread_join(students[1], NULL);
	pthread_join(students[2], NULL);
	pthread_join(students[3], NULL);
	pthread_join(students[4], NULL);
	
	// Return 0 after successful execution
	return 0;
}
