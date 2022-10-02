CC := gcc
CFLAGS := -Wall -pedantic -std=c17

OBJS := main.o \
vector\vector.o

all: $(OBJS) build

build:
	$(CC) $(CFLAGS) -o main $(OBJS)


$(OBJS): clean
$(OBJS): %.o : %.c

clean:
	del $(OBJS)
