#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

// Integer Stack
typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} IntStack;

void init(IntStack *s) {
    s->top = -1;
}

int isempty(IntStack *s) {
    return s->top == -1;
}

int isfull(IntStack *s) {
    return s->top == MAX_STACK_SIZE - 1;
}

void push(IntStack *s, int value) {
    if (isfull(s)) {
        printf("Error: Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    s->data[++s->top] = value;
}

int pop(IntStack *s) {
    if (isempty(s)) {
        printf("Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top--];
}

int peek(IntStack *s) {
    if (isempty(s)) {
        printf("Error: Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top];
}

// Character Stack
typedef struct {
    char data[MAX_STACK_SIZE];
    int top;
} CharStack;

void init_char(CharStack *s) {
    s->top = -1;
}

int isempty_char(CharStack *s) {
    return s->top == -1;
}

int isfull_char(CharStack *s) {
    return s->top == MAX_STACK_SIZE - 1;
}

void push_char(CharStack *s, char value) {
    if (isfull_char(s)) {
        printf("Error: Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    s->data[++s->top] = value;
}

char pop_char(CharStack *s) {
    if (isempty_char(s)) {
        printf("Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top--];
}

char peek_char(CharStack *s) {
    if (isempty_char(s)) {
        printf("Error: Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top];
}

#endif // STACK_H
