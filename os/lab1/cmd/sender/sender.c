#include "sender.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int send(Message msg, Mailbox *mbox, Timer *timer) {
  int err;
  switch (mbox->flag) {
  case MECH_MESSAGE_QUEUE:
    Timer_Start(timer);
    err = mq_send(mbox->storage.mq, msg.buf, msg.len, 0);
    Timer_End(timer);

    if (err == -1) {
      perror("mq_send() failed");
      Timer_End(timer);
      return 1;
    }

    break;
  case MECH_SHARED_MEMORY:
    if (sem_wait(&mbox->storage.shm->write) == -1) {
      perror("sem_wait() failed");
      return 1;
    }

    /* printf("writing message\n"); */
    Timer_Start(timer);
    Message_Copy(&mbox->storage.shm->msg, &msg);
    Timer_End(timer);

    /* printf("posting read semaphore\n"); */
    if (sem_post(&mbox->storage.shm->read) == -1) {
      perror("sem_post() failed");
      return 1;
    }

    break;
  default:
    fprintf(stderr, "Invalid flag\n");
    return 1;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <1|2> <input file>\n", argv[0]);
    return 1;
  }

  int flag = atoi(argv[1]);

  Mailbox mbox;
  if (Mailbox_Init(&mbox, MAILBOX_NAME, flag, MODE_WRITE) != 0) {
    return 1;
  }
  Mailbox_Info(&mbox);

  FILE *file = fopen(argv[2], "r");
  if (file == NULL) {
    perror("fopen() failed");
    return 1;
  };

  char buf[BUF_SIZE];
  Message msg;

  Timer timer;
  Timer_Init(&timer);

  while (fgets(buf, BUF_SIZE, file) != NULL) {
    buf[strcspn(buf, "\n")] = 0; // remove newline character

    printf("\033[96mSending message:\033[39m %s\n", buf);
    Message_SetMsg(&msg, buf);
    if (send(msg, &mbox, &timer) != 0) {
      printf("\033[93mFailed to send message\033[39m\n");
      break;
    }
  }

  if (feof(file)) {
    Message_SetMsg(&msg, CMD_EXIT);
    send(msg, &mbox, &timer);
    printf("\033[93mEnd of file, exit!\033[39m\n");
  }

  // TODO: sometimes, this will be -nan
  // I have no idea how to reproduc this issue
  printf("total time: %f µs\n", timer.Total);

  fclose(file);
  Mailbox_Close(&mbox);

  return 0;
}
