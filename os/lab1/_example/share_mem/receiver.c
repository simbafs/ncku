#include "message.h"
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
  printf("open file\n");
  int fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);

  if (fd == -1)
    error("shm_open");

  printf("ftruncate\n");
  if (ftruncate(fd, sizeof(struct shmbuf)) == -1)
    error("ftruncate");

  printf("mmap\n");
  struct shmbuf *shmp =
      mmap(NULL, sizeof(*shmp), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  if (shmp == MAP_FAILED)
    error("mmap");

  // init lock
  printf("sem init\n");
  if (sem_init(&shmp->lock, 1, 0) == -1)
    error("sem_init-lock");

  // wail message from sender

  printf("waiting message\n");
  while (1) {
    if (sem_wait(&shmp->lock) == -1)
      error("sem_wait");

    if (strcmp(shmp->buf, EXIT_CMD) == 0) {
      printf("Received exit command\n");
      break;
    }

    printf("Received: %s\n", shmp->buf);
  }

  shm_unlink(SHM_NAME);

  return 0;
}
