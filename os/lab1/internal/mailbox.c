#include "mailbox.h"
#include <fcntl.h>
#include <mqueue.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int Message_Init(Message *msg) {
  msg = (Message *)malloc(sizeof(Message));
  if (msg == NULL) {
    perror("malloc() failed");
    return 1;
  }

  msg->type = TYPE_MSG;
  msg->len = 0;
  msg->buf[0] = '\0';

  return 0;
}

void Message_Copy(Message *dst, Message *src) {
  dst->type = src->type;
  dst->len = src->len;
  strncpy(dst->buf, src->buf, BUF_SIZE);
}

void Message_SetMsg(Message *msg, const char *str) {
  if (strcmp(str, CMD_EXIT) == 0) {
    msg->type = TYPE_EXIT;
  } else {
    msg->type = TYPE_MSG;
  }
  msg->len = strlen(str);
  strncpy(msg->buf, str, BUF_SIZE - 1);
  msg->buf[msg->len] = '\0';
}

// firsst run receiver, the run sender

int Mailbox_Init(Mailbox *mbox, char *name, int flag, int mode) {
  switch (flag) {
  case MECH_MESSAGE_QUEUE:
    mbox->flag = MECH_MESSAGE_QUEUE;

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = QUEUE_SIZE;
    attr.mq_msgsize = BUF_SIZE;
    attr.mq_curmsgs = 0;

    switch (mode) {
    case MODE_READ:
      mbox->mode = MODE_READ;
      mbox->storage.mq = mq_open(name, O_CREAT | O_RDONLY, 0666, &attr);
      if (mbox->storage.mq == (mqd_t)-1) {
        perror("mq_open() failed");
        return 1;
      }

      break;
    case MODE_WRITE:
      mbox->mode = MODE_WRITE;
      mbox->storage.mq = mq_open(name, O_CREAT | O_WRONLY, 0666, &attr);
      if (mbox->storage.mq == (mqd_t)-1) {
        perror("mq_open() failed");
        return 1;
      }

      break;
    default:
      fprintf(stderr, "Invalid mode\n");
      return 1;
    }
    break;

  case MECH_SHARED_MEMORY:
    mbox->flag = MECH_SHARED_MEMORY;
    int shm_fd;

    switch (mode) {
    case MODE_READ:
      mbox->mode = MODE_READ;
      shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

      if (shm_fd == -1) {
        perror("shm_open");
        return 1;
      }

      if (ftruncate(shm_fd, sizeof(Shm)) == -1) {
        perror("ftruncate");
        return 1;
      }

      mbox->storage.shm = mmap(NULL, sizeof(Shm), PROT_READ | PROT_WRITE,
                               MAP_SHARED, shm_fd, 0);
      if (mbox->storage.shm == MAP_FAILED) {
        perror("mmap");
        return 1;
      }

      if (sem_init(&mbox->storage.shm->read, 1, 0) == -1) {
        perror("init read sem failed");
        return 1;
      }

      if (sem_init(&mbox->storage.shm->write, 1, 1) == -1) {
        perror("init write sem failed");
        return 1;
      }

      Message_Init(&mbox->storage.shm->msg);

      break;

    case MODE_WRITE:
      mbox->mode = MODE_WRITE;
      shm_fd = shm_open(name, O_RDWR, 0666);
      if (shm_fd == -1) {
        perror("shm_open");
        return 1;
      }

      mbox->storage.shm = mmap(NULL, sizeof(Shm), PROT_READ | PROT_WRITE,
                               MAP_SHARED, shm_fd, 0);
      if (mbox->storage.shm == MAP_FAILED) {
        perror("mmap");
        return 1;
      }

      break;

    default:
      fprintf(stderr, "Invalid mode\n");
      return 1;
    }

    break;

  default:
    fprintf(stderr, "Invalid flag\n");
    return 1;
  }

  return 0;
}

int Mailbox_Close(Mailbox *mbox) {
  switch (mbox->flag) {
  case MECH_MESSAGE_QUEUE:

    break;
  case MECH_SHARED_MEMORY:
    if (munmap(mbox->storage.shm, sizeof(Shm)) == -1) {
      perror("munmap");
      return 1;
    }

    break;
  default:
    fprintf(stderr, "Invalid flag\n");
    return 1;
  }

  return 0;
}

int Mailbox_Destroy(Mailbox *mbox) {
  switch (mbox->flag) {
  case MECH_MESSAGE_QUEUE:
    if (mq_close(mbox->storage.mq) == -1) {
      perror("mq_close() failed");
      return 1;
    }

    break;
  case MECH_SHARED_MEMORY:
    if (munmap(mbox->storage.shm, sizeof(Shm)) == -1) {
      perror("munmap");
      return 1;
    }

    if (shm_unlink("mailbox") == -1) {
      perror("shm_unlink() failed");
      return 1;
    }

    if (sem_destroy(&mbox->storage.shm->read) == -1) {
      perror("destroy read sem failed");
      return 1;
    }

    if (sem_destroy(&mbox->storage.shm->write) == -1) {
      perror("destroy write sem failed");
      return 1;
    }

    break;
  default:
    fprintf(stderr, "Invalid flag\n");
    return 1;
  }

  return 0;
}

void Mailbox_Info(Mailbox *mbox) {
  printf("\033[94m");

  switch (mbox->flag) {
  case MECH_MESSAGE_QUEUE:
    switch (mbox->mode) {
    case MODE_READ:
      printf("Message queue in read mode");
      break;
    case MODE_WRITE:
      printf("Message queue in write mode");
      break;
    default:
      printf("Invalid mode");
      break;
    }
    break;
  case MECH_SHARED_MEMORY:
    switch (mbox->mode) {
    case MODE_READ:
      printf("Shared memory in read mode");
      break;
    case MODE_WRITE:
      printf("Shared memory in write mode");
      break;
    default:
      printf("Invalid mode");
      break;
    }
    break;
  default:
    printf("Invalid flag");
    break;
  }

  printf("\033[39m\n");
}
