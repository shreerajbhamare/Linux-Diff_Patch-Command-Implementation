typedef struct stack{
    char *a;
    int size;
    int i;
}stack;

void init(stack *s, int len);
void push(stack *s, char d);
int isfull(stack *s) ;
int isempty(stack *s);
int pop(stack *s);
int peek(stack s);
