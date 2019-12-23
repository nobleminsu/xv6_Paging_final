// Test that fork fails gracefully.
// Tiny executable so that the limit can be filling the proc table.

#include "types.h"
#include "stat.h"
#include "user.h"

#define N 2

char *argv[] = { "memtest1", 0 };
char *argv2[] = { "memtest4", 0 };

// void
// printf(int fd, char *s, ...)
// {
//   write(fd, s, strlen(s));
// }

void
multiproctest(void)
{
  int n, pid;

  printf(1, "fork test\n");

  for(n=0; n<N; n++){
    pid = fork();
    if(pid < 0)
      break;
    if(pid == 0){
      if(n == 0 || n == 2) {
        if(exec("memtest1", argv) < 0){
          printf(1, "exec mem failed\n");
          exit();
        }
      } else 
      if(n == 1 || n == 3) {
          if(exec("memtest4", argv2) < 0){
          printf(1, "exec mem failed\n");
          exit();
        }
      }
      exit();
    }
  }

  if(n == N){
    printf(1, "fork claimed to work %d times!\n", N);
    exit();
  }

  for(; n > 0; n--){
    if(wait() < 0){
      printf(1, "wait stopped early\n");
      exit();
    }
  }

  if(wait() != -1){
    printf(1, "wait got too many\n");
    exit();
  }

  printf(1, "multiproctest OK in %d\n", uptime());
}

int
main(void)
{
  multiproctest();
  exit();
}
