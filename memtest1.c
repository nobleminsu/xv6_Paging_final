#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

char buf[8192];
char name[3];
char *echoargv[] = { "echo", "ALL", "TESTS", "PASSED", 0 };
int stdout = 1;
#define TOTAL_MEMORY ((1 << 20) + (1 << 19) + (1 << 17))
#define MIN_MEMORY ((1 << 20) + (1 << 18) )

void
mem(void)
{
	void *m1 = 0, *m2, *start, *to_free;
	uint cur = 0;
	uint on_mem = 0;
	uint count = 0;
	// uint total_count;
	// int i;

	printf(1, "mem test\n");

	m1 = malloc(4096);
	if (m1 == 0)
		goto failed;
	start = m1;

	to_free = start;

	while (cur < TOTAL_MEMORY) {
		m2 = malloc(4096);
		if (m2 == 0)
			goto failed;
		*(char**)m1 = m2;
		((int*)m1)[2] = count++;
		// if(count > 596){
			printf(1, "value stored = %d, total=%d \n", count, TOTAL_MEMORY/4096);
		// }
		
		m1 = m2;

		cur += 4096;	
		on_mem += 4096;

		if (on_mem >= MIN_MEMORY) {
			printf(1, "freeing %p \n", to_free);
			void* next = *(char**)to_free;
			free(to_free);
			to_free = next;
			on_mem -= 4096;
		}	
	}
	((int*)m1)[2] = count;
	// total_count = count;

	// count = 0;
	// m1 = start;

	// while (count != total_count) {
	// 	if (count % 4 == 0 || count % 4 == 2) count++;
	// 	if (((int*)m1)[2] != count)
	// 		goto failed;
	// 	m1 = *(char**)m1;
	// 	count++;
	// }

	printf(1, "mem ok %d\n", bstat());
	exit();
failed:
	printf(1, "test failed!\n");
	exit();
}

int
main(int argc, char *argv[])
{

	printf(1, "MEMTEST1 IS COMMENCING mem-limit: %d\n");
	mem();
	return 0;
}
