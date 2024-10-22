#include <semaphore.h>

#define SHM_NAME "/test_shm"
#define EXIT_CMD "exit"

#define BUF_SIZE 1024

struct shmbuf {
  sem_t lock;
  size_t cnt;
  char buf[BUF_SIZE];
};

#define error(msg)                                                             \
  {                                                                            \
    perror(msg);                                                               \
    return 1;                                                                  \
  }
