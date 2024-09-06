obj-m+=test1.o

all:
	make /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) test1char.c -o test

clean:
	make /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm test
