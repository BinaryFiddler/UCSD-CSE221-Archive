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


int main(int argc, char* argv[]) {
    unsigned long start, end, total_time;
    for(int k=2048; k<=32768*4; k+=k){
        //select file to read
        string temp = to_string(k);
        char filename[(int)temp.size()];
        strcpy(filename, temp.c_str());
        int number_of_blocks;
        size_t file_size;
        blksize_t block_size;
        total_time = 0;
    for (int i = 0;i < TIMES; i++) {
            //open file, and disable file cache
            int fd = open(filename, O_RDONLY);
            fcntl(fd, F_NOCACHE, 1);

            //GET file size and block size
            struct stat buffer;
            fstat(fd, &buffer);
            
            file_size = buffer.st_size;
            block_size = buffer.st_blksize;
            number_of_blocks = file_size/block_size;
            
            //read file sequentially
            char* buf = (char*)malloc(file_size);
            for(int j = 0;j < number_of_blocks;j++) {
                start = RDTSC();
                read(fd, buf, block_size);
                end = RDTSC_STOP();
                total_time += end - start;
            }
            
            close(fd);
            free(buf);
        }
        //write data back to disk
        ofstream output;
        output.open("seq.txt", std::ios_base::app);
        output << file_size / 1024 / 1024<< " " << total_time/(TIMES*number_of_blocks) << "\n";;
        output.close();
        cout << file_size << " " << total_time/(TIMES*number_of_blocks) << endl;
    }
}
