#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
  char data[100][100];
  int top;
} stack;

void
init_stack(stack *s)
{
  s->top = -1;
}

bool
is_stack_empty(stack *s)
{
  return s->top == -1;
}

void push(stack *s, char item[])
{
  if(s->top < 100 - 1) {
    s->top++;
    strcpy(s->data[s->top], item);
  }
}

void
pop(stack *s)
{
  if(!is_stack_empty(s)) s->top--;
}

void
print_stack(stack *s) {
    for (int i = s->top; i >= 0; i--) {
        printf("%s\n", s->data[i]);
    }
}

typedef struct {
    char data[100][100];
    int front;
    int rear;
} que;

void
init_que(que *q)
{
  q->front = 0;
  q->rear = -1;
}

bool
is_que_empty(que *q)
{
  return q->front > q->rear;
}

void
enqueue(que *q, char item[])
{
    if(q->rear < 100 - 1) {
    strcpy(q->data[++q->rear], item);
  }
}

void
dequeue(que *q)
{
  if(!is_que_empty(q)) q->front++;
}

void
print_que(que *q)
{
  for (int i = q->front; i <= q->rear; i++) {
        printf("%s\n", q->data[i]);
    }
}

int
main(void)
{
  // NOTE: If I did it like you via ```stack fruit = new stack()```
  // I have to do a heap allocation based one.
  // which is not what we have in C. since C does not have constructors.
  // Same thing for que
  stack fruit;

  init_stack(&fruit);
  push(&fruit, "Apple");
  push(&fruit, "Banana");
  print_stack(&fruit);

  printf("------------------------------------\n");
  pop(&fruit);
  push(&fruit, "Canned Yams");
  push(&fruit, "Durian");
  print_stack(&fruit);

  printf("------------------------------------\n");

  que q;
  init_que(&q);

  enqueue(&q, "Job 1");
  enqueue(&q, "Job 2");
  enqueue(&q, "Job 3");
  print_que(&q);
  printf("------------------------------------\n");


  dequeue(&q);
  dequeue(&q);
  print_que(&q);
  printf("------------------------------------\n");
  return 0;
}
