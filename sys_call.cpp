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


int main()
{
        printf("System call overhead\n");
        //cache for pid
        //warmup -> steady
        //sched_yield depends on explicit scheduler
        int i;
		volatile uint64_t start, end;

        start = RDTSC();
        getpid();
        end = RDTSC_STOP();
        cout << "single getpid(): " <<  end - start << endl;
		
        start = RDTSC();
        for(i = 0; i < TIMES; i++){
            getpid();//idempotent system call
        }
        end = RDTSC_STOP();
		cout << "getpid(): " << 1.0*(end - start)/TIMES << endl;
		
        time_t  timev;
		start = RDTSC();
        for(i = 0; i < TIMES; i++){
            time(&timev);//non-idempotent system call
        }
        end = RDTSC_STOP();
        cout << "time(): " << 1.0*(end - start)/TIMES << endl;

		start = RDTSC();
        for(i = 0; i < TIMES; i++){
            getuid();
        }
        end = RDTSC_STOP();
        cout << "getuid(): " << 1.0*(end - start)/TIMES << endl;
		
		int pid = getpid();
		start = RDTSC();
        for(i = 0; i < TIMES; i++){
			sched_yield();
        }
        end = RDTSC_STOP();
        cout << "sched_yield(): " << 1.0*(end - start)/TIMES << endl;

		return 0;
}
