#ifndef BigInteger_h
#define BigInteger_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
};
struct BigInteger
{
    int length;
    struct node *L;
    char sign;
};

struct BigInteger initialize(char*);
struct BigInteger add(struct BigInteger , struct BigInteger );
struct BigInteger sub(struct BigInteger , struct BigInteger );
struct BigInteger mul(struct BigInteger , struct BigInteger );
struct BigInteger div1(struct BigInteger , struct BigInteger );
void display(struct BigInteger);
#endif