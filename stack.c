#include "stack.h"
#include<limits.h>
#include<stdlib.h>

void init(stack *s, int len){
    s->a = (char*)malloc(sizeof(char)*len);
    s->size = len;
    s->i = 0;
}
int isfull(stack *s) {
    return (s->i == s->size-1);
}

int isempty(stack *s) {
    return (s->i == 0);
}
void push(stack *s, char d){
    if(isfull(s))
        return ;
    else {
        s->i++;
        s->a[s->i] = d;
        return;
    }
}

int pop(stack *s){
    char e ;
    e = s->a[s->i];
    s->i--;
    return e;

}

int peek(stack s){
        return s.a[s.i];
}
