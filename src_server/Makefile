CC=gcc
INCLUDE=../include
CFLAGS=-c -I$(INCLUDE) -g -Wall
LDFLAGS=-lpthread
TARGET=app

RM=sudo rm -rf

SRCFILE=$(wildcard *.c)
DESFILE=$(patsubst %.c,%.o,$(SRCFILE))
$(TARGET): $(DESFILE)
	$(CC) $(DESFILE) -o $(TARGET) $(LDFLAGS)

%.o:%.c
		$(CC) $(CFLAGS) $<
.PHONY:clean
clean:
	$(RM) $(DESFILE) $(TARGET)
	
