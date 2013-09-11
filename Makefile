all: clean chooseln

chooseln:
	gcc -O2 chooseln.c -o chooseln

install: chooseln
	cp chooseln /usr/sbin/chooseln

clean:
	rm -rf *o chooseln


