all: sender receiver

sender: sender.c message.h
	gcc -Wall -o sender -lrt sender.c

receiver: receiver.c message.h
	gcc -Wall -o receiver -lrt receiver.c

run_sender: sender
	./sender

run_receiver: receiver
	./receiver

clean:
	rm -f sender receiver

.PHONY: all
