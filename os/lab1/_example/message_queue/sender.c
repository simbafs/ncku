#include "message.h"
#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  mqd_t mq;
  char buffer[MAX_SIZE];

  struct mq_attr attr;
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = MAX_SIZE;
  attr.mq_curmsgs = 0;

  mq = mq_open(QUEUE_NAME, O_WRONLY | O_CREAT, 0666, &attr);
  if (mq == (mqd_t)-1) {
    perror("mq_open() failed");
    return 1;
  }

  printf("Sending Data...\n");

  for (int i = 0; i < 10; i++) {
    int n = sprintf(buffer, "ping: %d", i);

    if (mq_send(mq, buffer, n, 0) == -1) {
      perror("mq_send() failed");
      return 1;
    }
    printf("Send: %s\n", buffer);

    // sleep 1 second
    sleep(1);
  }

  mq_send(mq, CLOSE_CMD, 5, 0);

  mq_close(mq);

  return 0;
}
