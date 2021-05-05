#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct queue {
    	char *arr;
	int size;
	int front;
	int rear;
	int c;
}queue;

void initq(queue*, int length);
void deletequeue(queue*);
void enqueue(queue*, char element);
char dequeue(queue*);
int isfullq(queue*);
int isemptyq(queue*);


#endif
