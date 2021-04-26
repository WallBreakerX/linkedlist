CC:=gcc

LDFLAGS += -lpthread

CFLAGS:= -g

OBJS:=example.o linkedlist.o

all:app

app:$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)
	rm -rf *.o

clean:
	rm -rf *.o


