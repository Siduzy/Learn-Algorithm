#include "HashMap.h"
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

using namespace std;

int main()
{
    int fd = open("inputfile.txt",O_RDONLY);
	if (fd != -1)
	{
		cout << "Loading..." <<endl;
	}
    int len = lseek(fd,0,SEEK_END);
    char *mbuf = (char *) mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);    
	if (mbuf == MAP_FAILED)
	{
		throw ("mmap failed\n");
	}

	clock_t timeBegin = clock();
	HashMap hash(1024);
	char *pLine = NULL;
	char *pEndLine = NULL;
	int i = 0;
	while (i < len)
	{
		pLine = mbuf + i;
	 	pEndLine = pLine + 3;
		*pEndLine = 0;
		hash.Insert(pLine, 1);
		i += 4;
	}
	
	int cnt = hash.Print();
	cout << "HashMap count: " << cnt <<endl;
	clock_t timeEnd = clock();

	cout << "Time cost: " << (timeEnd-timeBegin)/CLOCKS_PER_SEC <<endl;

	munmap(mbuf, len);
}
