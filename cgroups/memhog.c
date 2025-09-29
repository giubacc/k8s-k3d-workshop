#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
  size_t size = 100 * 1024 * 1024; // 100 MB
  char *a = malloc(size);

  if (!a)
  {
    perror("malloc");
    return 1;
  }

  // Touch each page to force real allocation (page size = 4096)
  for (size_t i = 0; i < size; i += 4096)
  {
    a[i] = 1;
  }

  printf("Allocated and touched %zu MB, sleeping...\n", size / 1024 / 1024);
  fflush(stdout);

  sleep(300); // keep process alive for 5 minutes
  free(a);
  return 0;
}
