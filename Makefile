#
# Makefile
# wojtek, 2018-04-15 16:16
#

CC=gcc
RM=rm -rf
CFLAGS= -g -pedantic -Wall -Wextra -Werror -O2 -std=c11
LDFLAGS= -g
LIBS=
TARGET=simple_daemon

SRCS=main.c
OBJS=$(subst .c,.o,$(SRCS))

all: $(TARGET)
	@echo "Makefile needs your attention"

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

$(OBJS): $(SRCS)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJS) $(TARGET)

# vim:ft=make
#
