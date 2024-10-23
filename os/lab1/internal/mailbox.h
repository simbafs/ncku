#ifndef MAILBOX_H
#define MAILBOX_H

#include <mqueue.h>
#include <semaphore.h>

#define MAILBOX_NAME "/mailbox"

#define MECH_MESSAGE_QUEUE 1
#define MECH_SHARED_MEMORY 2

#define MODE_READ 0
#define MODE_WRITE 1

#define BUF_SIZE 1024
#define QUEUE_SIZE 10

// message

#define TYPE_MSG 0
#define TYPE_EXIT 1
#define CMD_EXIT "exit"

typedef struct {
  char buf[BUF_SIZE];
  int len;
  int type;
} Message;

int Message_Init(Message *msg);
void Message_Copy(Message *dst, Message *src);
void Message_SetMsg(Message *msg, const char *str);

// shared memory

typedef struct {
  Message msg;

  sem_t read;
  sem_t write;
} Shm;

// mailbox

typedef struct {
  int flag; // 1 for message queue, 2 for shared memory
  int mode; // 0 for read, 1 for write
  union {
    // message queue
    mqd_t mq;

    // shared memory
    Shm *shm;

  } storage;
} Mailbox;

// Mailbox_Init initializes a mailbox.
int Mailbox_Init(Mailbox *mbox, char *name, int flag, int mode);

// Mailbox_Close closes a mailbox, but does not destroy it.
int Mailbox_Close(Mailbox *mbox);

// Mailbox_Destroy destroys a mailbox.
int Mailbox_Destroy(Mailbox *mbox);

// Mailbox_InFo prints the information of a mailbox.
void Mailbox_Info(Mailbox *mbox);

#endif
