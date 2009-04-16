ALL = main.o utils.o request.o response.o

httpd : $(ALL)
	cc -o httpd $(ALL)

CFLAGS=-Wall

main.o : main.c request.h response.h utils.h
	cc -c main.c

response.o : response.h response.c
	cc -c response.c

request.o : request.h request.c
	cc -c request.c

utils.o : utils.h utils.c
	cc -c utils.c

clean :
	rm httpd $(ALL)

