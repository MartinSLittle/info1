CC=gcc

all: clean app

app: app.c sock-lib.c
	$(CC) -Wall app.c sock-lib.c -o app

clean:
	rm -f app
	rm -f database.bin

test:
	@echo "25;2.2" | nc localhost 8000
	@echo "26;2.1" | nc localhost 8000
	@echo "a#;2,3xxxxxxxxxxxxxxxxxxxxxxxxxx" | nc localhost 8000
	@echo "27;2.3" | nc localhost 8000
	@pkill -15 -f app

