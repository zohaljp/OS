#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>


#define NTHREADS 12 // great number to run tests


typedef struct _rwlock_t {
	sem_t lock; // binary semaphore (basic lock)
	sem_t writelock; // allow ONE writer/MANY readers
	int readers; // #readers in critical section
	sem_t extracontrol;

} rwlock_t;

void rwlock_init(rwlock_t* rw) {
	rw->readers = 0;
	sem_init(&rw->lock, 0, 1);
	sem_init(&rw->writelock, 0, 1);
	sem_init(&rw->extracontrol, 0, 1);

}

void rwlock_acquire_readlock(rwlock_t* rw) {
	sem_wait(&rw->extracontrol);
	sem_wait(&rw->lock);
	rw->readers++;
	printf("Reader is reading, number of reader is %d \n", rw->readers);
	if (rw->readers == 1) // first reader gets writelock
		sem_wait(&rw->writelock);
	sem_post(&rw->lock);
	sem_post(&rw->extracontrol);

}

void rwlock_release_readlock(rwlock_t* rw) {
	sem_wait(&rw->lock);
	rw->readers--;
	if (rw->readers == 0) {// last reader lets it go
		sem_post(&rw->writelock);
		

	}
	sem_post(&rw->lock);

}

void rwlock_acquire_writelock(rwlock_t* rw) {
	sem_wait(&rw->extracontrol);
	sem_wait(&rw->writelock);
	printf("Writing in Data base \n");

}

void rwlock_release_writelock(rwlock_t* rw) {
	sem_post(&rw->writelock);
	sem_post(&rw->extracontrol);


}

void reading_writing() { // from slides-This function is only meant to waste time for a variable amount of time.
	int x = 0, T;
	T = rand() % 10000;
	for (int i = 0; i < T; i++)
		for (int j = 0; j < T; j++)
			x = i * j;
}

rwlock_t rw; // declare readwrite lock 

void* reader(void* args) { 
	rwlock_acquire_readlock(&rw);
	//critical section 
	reading_writing();
	// done with critical section
	rwlock_release_readlock(&rw);
	printf("Reader done reading, readers present in Data Base %d \n", rw.readers);
	return NULL;
}

void* writer(void* args) {

	rwlock_acquire_writelock(&rw);
	//critical section 
	reading_writing();
	// done with critical section 
	rwlock_release_writelock(&rw);
	printf("Done Writing \n ");
	return NULL;
}


int main() {


	rwlock_init(&rw);  //initialize readwrite lock 


	FILE* fp;
	fp = fopen("scenarios.txt", "r");

	if (fp == NULL) {
		printf("Error opening the file \n");
	}




	pthread_t threads[NTHREADS]; // max number of threads
	char rw_character[NTHREADS]; //  max character per line for simplicity let's keep it equal to max number of threads







	int idx = 0; // initialize- this will be set back to 0 whenever a new line is detected 
	char ch; // control variable for scaning read writes and end of file 
	int i;// loop controk variable for creating and jointing threads

	while (1) { //We need an "infinite loop" to run all of our cases


		ch = fgetc(fp);// condition to break the loop once we reach the end of the file 
		if (ch == EOF)
			break;


		if (ch == '\n') {  // new line detected, let's deal with this scnenario before scanning the next line -- This is the body of the simulation 
			idx = 0;


			printf("Scenario Begins: \n");
			for (i = 0; i < NTHREADS; i++) {

				if (rw_character[i] == 'r') { // inspired from main.c given from project 
					if (pthread_create(&threads[i], NULL, reader, NULL) != 0) {
						printf("Thread number %d cannot be created \n", i);
						break;
					}
				}
				else if (rw_character[i] == 'w') {
					if (pthread_create(&threads[i], NULL, writer, NULL) != 0) {
						printf("Thread number %d cannot be created \n", i);
						break;
					}
				}
				
			}

			//joining  threads 
			for (i = 0; i < NTHREADS; i++) {
				if (pthread_join(threads[i], NULL) != 0) {
					printf("Thread number %d cannot be joined \n", i);
				}
			}
			printf("Scenario Finished! \n");
			continue;// skip rest of while(1) loop to restart scanning next line 
		}


		else if (ch == 'w' || ch == 'r') {    // scan line and populate rw_character array so we can simulate later 

			rw_character[idx] = ch;
			printf("%c ", rw_character[idx]);
			idx++;
		}
		else { // Something went wrong- for testing file purposes
			printf("File Does not respect format \n");
		}
	}


	printf("Simulation file has reached its end and all the scanrios have been simulated \n");
	return 0;
}

















	 
	 
	 
	 
	 
	 



