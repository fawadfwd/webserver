HEADERS = headers/

lh: accept.o server.o process.o file.o listhell.o
	cc -g -pthread -o lh accept.o server.o process.o file.o listhell.o
	
listhell.o: $(HEADERS)accept.h listhell.c
	cc -g -c -pthread listhell.c
	
process.o : $(HEADERS)accept.h process.c
	cc -g -c -pthread process.c

file.o : $(HEADERS)accept.h file.c
	cc -g -c -pthread file.c

server.o : $(HEADERS)accept.h server.c
	cc -g -c -pthread server.c

accept.o : $(HEADERS)accept.h accept.c
	cc -g -c -pthread accept.c


clean :
	rm lh accept.o server.o process.o file.o listhell.o
