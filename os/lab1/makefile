CC := gcc
override CFLAGS += -O3 -Wall -lrt -pthread

# Source files and binaries
SOURCE1 := cmd/sender/sender.c internal/mailbox.c internal/timer.c
BINARY1 := sender

SOURCE2 := cmd/receiver/receiver.c internal/mailbox.c internal/timer.c
BINARY2 := receiver

# Build both sender and receiver
all: $(BINARY1) $(BINARY2)

# Rule to build sender
$(BINARY1): $(SOURCE1) cmd/sender/sender.h internal/mailbox.h internal/timer.h
	$(CC) $(CFLAGS) $(SOURCE1) -o $@

# Rule to build receiver
$(BINARY2): $(SOURCE2) cmd/receiver/receiver.h internal/mailbox.h internal/timer.h
	$(CC) $(CFLAGS) $(SOURCE2) -o $@

# Run sender
run_$(BINARY1): $(BINARY1)
	./$(BINARY1)

# Run receiver
run_$(BINARY2): $(BINARY2)
	./$(BINARY2)

test_timer: test/timer.c internal/timer.c internal/timer.h
	$(CC) $(CFLAGS) test/timer.c internal/timer.c -o test_timer
	./test_timer

# Clean up compiled binaries
.PHONY: clean
clean:
	rm -f $(BINARY1) $(BINARY2) test_timer

