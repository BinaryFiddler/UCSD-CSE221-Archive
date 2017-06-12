#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <fstream>


#define TIMES 10
using namespace std;
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


int main(int argc, char const *argv[]){
    int number_of_blocks_to_read = 20;
    srand(time(NULL));
    unsigned long start, end, total;
    
    for(int k=2048; k<=32768*4; k+=k){
        string temp = to_string(k);
        char filename[(int)temp.size()];
        strcpy(filename, temp.c_str());
        size_t file_size;
        blksize_t block_size;
        total = 0;

        for (int i=0;i < TIMES; i++) {
            
            int fd = open(filename, O_RDONLY);
            fcntl(fd, F_NOCACHE, 1);
            
            struct stat buf;
            fstat(fd, &buf);
            file_size = buf.st_size;
            block_size = buf.st_blksize;
            
            char* buffer = (char*)malloc(file_size);
            int j = 0;
            for(;j < number_of_blocks_to_read;j++) {
                int block_position = rand() % number_of_blocks_to_read;
                int read_offset = block_position * block_size;
                start = RDTSC();
                pread(fd, buffer, block_size, read_offset);
                end = RDTSC_STOP();
                total += (end - start);
            }
            close(fd);
            free(buffer);
        }
        //write data back to disk
        ofstream output;
        output.open("ran.txt", std::ios_base::app);
        output << file_size / 1024 << " " << total/(TIMES*number_of_blocks_to_read) << "\n";;
        output.close();
        cout << file_size << " " << total/(TIMES*number_of_blocks_to_read) << endl;
    }
}

