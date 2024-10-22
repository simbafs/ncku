#ifndef RECEIVER_H
#define RECEIVER_H

#include "../../internal/mailbox.h"
#include "../../internal/timer.h"

int receive(Message *msg, Mailbox *mbox, Timer *timer);

#endif
