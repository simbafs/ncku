#include "receiver.h"
#include <bits/time.h>
#include <mqueue.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int receive(Message *msg, Mailbox *mbox, Timer *timer) {
  char buf[BUF_SIZE];
  int len;

  switch (mbox->flag) {
  case MECH_MESSAGE_QUEUE:
    Timer_Start(timer);
    // TODO: subtract the blocking time
    len = mq_receive(mbox->storage.mq, buf, BUF_SIZE, NULL);
    Timer_End(timer);

    if (len >= 0) {
      buf[len] = '\0';

      Message_SetMsg(msg, buf);
    } else {
      perror("mq_receive() failed");
      return 1;
    }

    break;
  case MECH_SHARED_MEMORY:
    if (sem_wait(&mbox->storage.shm->read) == -1) {
      perror("sem_wait() failed");
      return 1;
    }

    Timer_Start(timer);
    Message_Copy(msg, &mbox->storage.shm->msg);
    Timer_End(timer);

    if (sem_post(&mbox->storage.shm->write) == -1) {
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
  if (argc != 2) {
    printf("Usage: %s <1|2>\n", argv[0]);
    return 1;
  }

  int flag = atoi(argv[1]);

  Mailbox mbox;
  if (Mailbox_Init(&mbox, MAILBOX_NAME, flag, MODE_READ) != 0) {
    return 1;
  }
  Mailbox_Info(&mbox);

  Message msg;

  Timer timer;
  Timer_Init(&timer);

  while (1) {
    if (receive(&msg, &mbox, &timer) != 0) {
      printf("\033[93mFailed to receive message\033[39m\n");
      break;
    }
    if (msg.type == TYPE_EXIT) {
      break;
    }

    printf("\033[96mReceiving message:\033[39m %s\n", msg.buf);
  }

  printf("\033[93mSender exit!\033[39m\n");

  printf("total time: %f\n", timer.Total);

  Mailbox_Close(&mbox);
  Mailbox_Destroy(&mbox);

  return 0;
}
