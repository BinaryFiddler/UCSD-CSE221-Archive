#include <iostream>
#include <stdint.h> /* for uint64_t */
#include <mach/mach_time.h>

#define TIMES 100000

using namespace std;

void test0(){};
void test1(int a){};
void test2(int a, int b){};
void test3(int a, int b, int c){};
void test4(int a, int b, int c, int d){};
void test5(int a, int b, int c, int d, int e){};
void test6(int a, int b, int c, int d, int e, int f){};
void test7(int a, int b, int c, int d, int e, int f, int g){};

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

void readOverhead(){
    uint64_t start, end, total_time, now, then;
    total_time = 0;
    start = RDTSC();
    for(int i = 0; i < TIMES; i++){
        now = RDTSC();
        then = RDTSC_STOP();
    }
    end = RDTSC_STOP();
    total_time = end - start;
    cout << "Read Overhead:" << (double)total_time/(double)TIMES << endl;
}

void loopOverhead(){
    uint64_t now = mach_absolute_time();
    uint64_t begin = RDTSC();
    for(int i = 0; i<TIMES; i++);
    uint64_t end = RDTSC_STOP();
    uint64_t then = mach_absolute_time();
    cout << "Loop Overhead:" << (double)(end - begin)/(double)TIMES << endl;
    cout << "Measured CPU CLK:" << (double)(end - begin)/(double)(then - now) << "Hz" << endl;
}

void measureProcedureOverhead(){
    uint64_t start, end, total_time;
    start = RDTSC();
    for(int i = 0; i < TIMES; i++){
        test0();
    }
    end = RDTSC_STOP();
    total_time = end - start;
    cout << "[test0] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;

    start = RDTSC();
    for(int i = 0; i < TIMES; i++){
        test1(1);
    }
    end = RDTSC_STOP();
    total_time = end - start;
    cout << "[test1] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;

    start = RDTSC();
    for(int i = 0; i < TIMES; i++){
        test2(1,2);
    }
    end = RDTSC_STOP();
    total_time = end - start;
    cout << "[test2] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;

    start = RDTSC();
    for(int i = 0; i < TIMES; i++){
        test3(1,2,3);
    }
    end = RDTSC_STOP();
    total_time = end - start;
    cout << "[test3] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;

    start = RDTSC();
    for(int i = 0; i < TIMES; i++){
        test4(1,2,3,4);
    }
    end = RDTSC_STOP();
    total_time = end - start;
    cout << "[test4] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;

    start = RDTSC();
    for(int i = 0; i < TIMES; i++){
        test5(1,2,3,4,5);
    }
    end = RDTSC_STOP();
    total_time = end - start;
    cout << "[test5] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;

    start = RDTSC();
    for(int i = 0; i < TIMES; i++){
        test6(1,2,3,4,5,6);
    }
    end = RDTSC_STOP();
    total_time = end - start;
    cout << "[test6] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;

    start = RDTSC();
    for(int i = 0; i < TIMES; i++){
        test7(1,2,3,4,5,6,7);
    }
    end = RDTSC_STOP();
    total_time = end - start;
    cout << "[test7] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;
}

void measureProcedureOverheadOneTimer(){
    uint64_t start, end, total_time;

    total_time = 0;
    for(int i = 0; i < TIMES; i++){
        start = RDTSC();
        end = RDTSC_STOP();
        total_time += end - start;
    }
    cout << "[NULL!] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;

    total_time = 0;
    for(int i = 0; i < TIMES; i++){
        start = RDTSC();
        test0();
        end = RDTSC_STOP();
        total_time += end - start;
    }
    cout << "[test0] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;

    total_time = 0;
    for(int i = 0; i < TIMES; i++){
        start = RDTSC();
        test1(1);
        end = RDTSC_STOP();
        total_time += end - start;
    }
    cout << "[test1] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;

    total_time = 0;
    for(int i = 0; i < TIMES; i++){
        start = RDTSC();
        test2(1,2);
        end = RDTSC_STOP();
        total_time += end - start;
    }
    cout << "[test2] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;

    total_time = 0;
    for(int i = 0; i < TIMES; i++){
        start = RDTSC();
        test3(1,2,3);
        end = RDTSC_STOP();
        total_time += end - start;
    }
    cout << "[test3] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;

    total_time = 0;
    for(int i = 0; i < TIMES; i++){
        start = RDTSC();
        test4(1,2,3,4);
        end = RDTSC_STOP();
        total_time += end - start;
    }
    cout << "[test4] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;

    total_time = 0;
    for(int i = 0; i < TIMES; i++){
        start = RDTSC();
        test5(1,2,3,4,5);
        end = RDTSC_STOP();
        total_time += end - start;
    }
    cout << "[test5] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;

    total_time = 0;
    for(int i = 0; i < TIMES; i++){
        start = RDTSC();
        test6(1,2,3,4,5,6);
        end = RDTSC_STOP();
        total_time += end - start;
    }
    cout << "[test6] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;

    total_time = 0;
    for(int i = 0; i < TIMES; i++){
        start = RDTSC();
        test7(1,2,3,4,5,6,7);
        end = RDTSC_STOP();
        total_time += end - start;
    }
    cout << "[test7] CPU CLK Cycle:" << (double)total_time/(double)TIMES << endl;
}

void warmup(){
    //Warmup
    for(int i = 0; i<TIMES; i++) RDTSC();
}
int main(){
    warmup();
    cout << "-----------------------" << endl;
    readOverhead();
    loopOverhead();
    cout << "-----------------------" << endl;
    measureProcedureOverhead();
    cout << "-----------------------" << endl;
    measureProcedureOverheadOneTimer();
    return 0;
}
