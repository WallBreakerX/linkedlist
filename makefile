CC:=gcc

LDFLAGS += -lpthread

OBJS:=example.o linkedlist.o

all:app

app:$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
	rm -rf *.o

clean:
	rm -rf *.o


