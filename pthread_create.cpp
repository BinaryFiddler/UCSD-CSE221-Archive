#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sched.h>
#include <iostream>

using namespace std;

#define TIMES 1000

static volatile uint32_t _lo, _hi;

static inline uint64_t RDTSC()
{
  unsigned int hi, lo;
  __asm__ volatile( "xor %%eax, %%eax;"
                    "cpuid;"
                    "rdtsc;"
                    : "=a" (lo), "=d" (hi)
                    :: "%rax", "%rbx", "%rcx", "%rdx");
  return ((uint64_t)hi << 32) | lo;
}

static inline uint64_t RDTSC_STOP()
{
    unsigned int hi, lo;
    __asm__ volatile("rdtscp;"
                     "mov %%eax, %0;"
                     "mov %%edx, %1;"
                     "xor %%eax, %%eax;"
                     "cpuid;"
                     : "=r" (lo), "=r" (hi)
                     ::"%rax", "%rbx", "%rcx", "%rdx");
    return ((uint64_t)hi << 32) | lo;
}



void *run(void* ptr) {
	pthread_exit(0);
}

int main() {

    uint64_t start, end, sum=0;
    int i = 0;
    
    //create a new kernal thread
    int pid = getpid();
    pthread_t thread;
   

    for(i = 0; i < TIMES; i++){
        //terminates old thread, or wait for that thread to terminate
        //make sure only one target thread from the calling thread
        start = RDTSC();
        pthread_create(&thread, NULL, run, NULL);
        pthread_join(thread, NULL); 
        end = RDTSC_STOP();
		sum += (end - start);
    }

    cout << "pthread_create() costs: " << 1.0*(sum)/(TIMES) << endl;
    

    //create a new process
    uint64_t total_time = 0;
    pid_t new_pid;

    for(i = 0; i < TIMES; i++){
        start = RDTSC();
        new_pid = fork();

        if (new_pid == -1) {
            //fork failed
            exit(-1);
        }
        if (new_pid == 0) {
            //exit child process
            exit(-1);
        } else {
            //wait child process to terminate
            wait(NULL);
            end = RDTSC_STOP();
            total_time += (end - start);
        }
    }

    cout << "fork() costs: " << 1.0*(total_time)/(TIMES) << endl;

   
    exit(0);


}
