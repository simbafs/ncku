#include "message.h"
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  mqd_t mq;
  char buffer[MAX_SIZE];
  ssize_t bytes_read;
  struct mq_attr attr;

  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = MAX_SIZE;
  attr.mq_curmsgs = 0;

  mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0666, &attr);
  if (mq == (mqd_t)-1) {
    perror("mq_open() failed");
    return 1;
  }

  printf("Receiving Data...\n");

  while (1) {
    bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
    if (bytes_read >= 0) {
      buffer[bytes_read] = '\0';
      printf("Received: %s\n", buffer);

      if (strcmp(buffer, CLOSE_CMD) == 0) {
        break;
      }
    } else {
      perror("mq_receive() failed");
      return 1;
    }
  }

  mq_close(mq);
  mq_unlink(QUEUE_NAME);

  return 0;
}
