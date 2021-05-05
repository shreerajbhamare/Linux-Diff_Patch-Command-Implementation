all: mydiff mypatch
#diff
mydiff: diff.o stack.o queue.o
	gcc -o ./diff diff.o stack.o queue.o 
diff3.o: diff.c stack1.o queue1.o
	gcc -c diff.c
stack.o: stack.h stack.c
	gcc -c stack.c
queue.o: queue.h queue.c
	gcc -c queue.c
	
#patch
mypatch: patch.o
	gcc -o ./patch patch.o
patch.o: patch.c
	gcc -c patch.c
				
