#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void initq(queue *q, int length) {
	q->size = length;
	q->arr = (char*) malloc(length * sizeof(int));
	if (q->arr == NULL)
		return ;
	q->front = -1;
	q->rear = -1;
	q->c=0;
}

void deletequeue(queue *q) {
	q->front = -1;
	q->rear = -1;
	q->size = 0;
	q->c=0;
	free(q->arr);
	return;
}

void enqueue(queue *q, char element) {
	if (isfullq(q))
		return ;
	if (q->front == -1)
		q->front = 0;

	q->rear = (q->rear + 1) % q->size;
	q->arr[q->rear] = element;
	q->c++;
	return ;
}

char dequeue(queue *q) {
	char d;
	d = q->arr[q->front];
	if (q->front == q->rear) {
		q->front = -1;
		q->rear = -1;
		return d;
	}
	q->front = (q->front + 1) % q->size;
	q->c--;

	return d;
}

int isfullq(queue *q) {
	return (q->c==q->size);
}

int isemptyq(queue *q) {
	return (q->c==0);
}

