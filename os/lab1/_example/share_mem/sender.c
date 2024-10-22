#include "message.h"
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <message>\n", argv[0]);
    return 1;
  }

  char *msg = argv[1];
  size_t len = strlen(msg);

  if (len >= BUF_SIZE) {
    // cut the message if it is too long
    msg[BUF_SIZE - 1] = '\0';
  }

  // open shared memory

  int fd = shm_open(SHM_NAME, O_RDWR, 0);
  if (fd == -1)
    error("shm_open");

  struct shmbuf *shmp =
      mmap(NULL, sizeof(*shmp), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (shmp == MAP_FAILED)
    error("mmap");

  // init lock
  /* printf("sem init\n"); */
  /* if (sem_init(&shmp->lock, 1, 0) == -1) */
  /*   error("sem_init-lock"); */

  // write message to shared memory
  shmp->cnt = len;
  memcpy(shmp->buf, msg, len);

  // send signal to receiver
  if (sem_post(&shmp->lock) == -1)
    error("sem_post");

  return 0;
}
