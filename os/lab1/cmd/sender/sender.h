#ifndef SENDER_H
#define SENDER_H

#include "../../internal/mailbox.h"
#include "../../internal/timer.h"

int send(Message msg, Mailbox *mbox, Timer *timer);

#endif
