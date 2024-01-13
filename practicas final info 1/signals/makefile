SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJS= $(patsubst %.c, %.o, $(SOURCES))
EJEC = main

CC			= gcc
CFLAGS		= -c -Wall
LDFLAGS		= -Wall -lm
EXTRA_CFLAGS= -lm



# <Contiene la dependencia del target
# @Contiene el target

ejec: $(EJEC) 

$(EJEC): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

%.o:%.c Makefile
	$(CC) $(CFLAGS) (EXTRA_CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(EJEC)

new:clean ejec		
