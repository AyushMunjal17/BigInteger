#include "BigInteger.h"

struct node *makenode(int n)
{
    struct node *t = (struct node *)malloc(sizeof(struct node));
    t->data = n;
    t->next = NULL;
    return t;
}

struct node *createList(char *s)
{
    struct node *ptr = NULL;
    struct node *curr;
    int i = 0;
    while (*(s + i) != '\0')
    {
        curr = makenode((*(s + i) - '0'));
        curr->next = ptr;
        ptr = curr;
        i++;
    }
    return ptr;
}

struct BigInteger createBig()
{
    struct BigInteger t;
    t.L = NULL;
    t.length = 0;
    t.sign = '+';
    return t;
}

struct BigInteger initialize(char *s)
{
    struct BigInteger t;
    t.L = createList(s);
    t.length = strlen(s);
    t.sign = '+';
    return t;
}

struct node *reverse(struct node *head)
{
    struct node *prev = NULL;
    struct node *next = NULL;
    struct node *curr = head;
    while (curr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

int length(struct node *ptr)
{
    int len = 0;
    while (ptr)
    {
        ptr = ptr->next;
        len++;
    }
    return len;
}

struct BigInteger add(struct BigInteger a, struct BigInteger b)
{
    struct node *num1 = a.L;
    struct node *num2 = b.L;
    struct node *prev = NULL;
    int len = 0, a1, b2;
    int carry = 0;
    while (num1 != NULL || num2 != NULL || carry != 0)
    {
        if (num1)
        {
            a1 = num1->data;
        }
        else
        {
            a1 = 0;
        }

        if (num2)
        {
            b2 = num2->data;
        }
        else
        {
            b2 = 0;
        }
        int sum = a1 + b2 + carry;
        carry = sum / 10;
        sum = sum % 10;

        struct node *res = makenode(sum);
        res->next = prev;
        prev = res;

        if (num1)
            num1 = num1->next;
        if (num2)
            num2 = num2->next;
        len++;
    }
    struct BigInteger result = createBig();
    result.L = prev;
    result.length = len;
    return result;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b)
{
    struct node *num1 = a.L;
    struct node *num2 = b.L;
    struct node *prev = NULL;
    int borrow = 0, x, y;
    int l = 0;

    struct BigInteger result = createBig();

    if (a.length < b.length)
    {
        struct node *temp = num2;
        num2 = num1;
        num1 = temp;
        result.sign = '-';
    }
    else if (a.length == b.length && num1->data < num2->data)
    {
        struct node *temp = num2;
        num2 = num1;
        num1 = temp;
        result.sign = '-';
    }

    while (num1 != NULL || num2 != NULL)
    {
        if (num1 != NULL)
        {
            x = num1->data;
        }
        else
        {
            x = 0;
        }

        if (num2 != NULL)
        {
            y = num2->data;
        }
        else
        {
            y = 0;
        }
        int diff = x - y - borrow;

        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        struct node *res = makenode(diff);
        res->next = prev;
        prev = res;

        if (num1 != NULL)
            num1 = num1->next;
        if (num2 != NULL)
            num2 = num2->next;
    }

    while (prev->next != NULL && prev->data == 0)
    {
        struct node *temp = prev;
        prev = prev->next;
        free(temp);
    }
    if (result.sign == '-')
    {
        prev->data = -prev->data;
    }
    result.L = prev;
    result.length = length(prev);
    return result;
}

struct BigInteger mul(struct BigInteger a, struct BigInteger b)
{
    struct node *num1 = a.L;
    struct node *num2 = b.L;
    struct BigInteger result = createBig();
    struct BigInteger lis = createBig();
    struct node *tempPrev = NULL;
    int i = 0;

    while (num2)
    {
        int carry = 0;
        struct node *prev = NULL;
        while (num1)
        {
            int val = num1->data * num2->data + carry;
            carry = val / 10;
            val = val % 10;

            struct node *res = makenode(val);
            res->next = prev;
            prev = res;
            num1 = num1->next;
        }
        while (carry)
        {
            int val = carry % 10;
            carry = carry / 10;

            struct node *res = makenode(val);
            res->next = prev;
            prev = res;
        }

        prev = reverse(prev);
        for (int j = 0; j < i; ++j)
        {
            struct node *temp = makenode(0);
            temp->next = prev;
            prev = temp;
        }

        num2 = num2->next;
        num1 = a.L;
        lis.L = prev;
        result = add(result, lis);
        result.L = reverse(result.L);
        i++;
    }
    result.L = reverse(result.L);
    result.length = length(result.L);
    return result;
}

int compare(struct BigInteger a, struct BigInteger b)
{
    if (a.sign == '-' && b.sign == '+')
    {
        return -1;
    }
    else if (a.sign == '+' && b.sign == '-')
    {
        return 1;
    }
    if (a.length < b.length)
    {
        return -1;
    }
    else if (a.length > b.length)
    {
        return 1;
    }
    struct node *ptrA = a.L;
    struct node *ptrB = b.L;
    while (ptrA != NULL && ptrB != NULL)
    {
        if (ptrA->data < ptrB->data)
        {
            return -1;
        }
        else if (ptrA->data > ptrB->data)
        {
            return 1;
        }
        ptrA = ptrA->next;
        ptrB = ptrB->next;
    }

    return 0;
}

struct BigInteger div1(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger res;
    struct node *dividend = a.L;
    struct node* divisor = b.L;
    struct node* quotient = NULL;
    struct node* currentQuotientNode = NULL;
    struct node* remainder = NULL;
    struct node* currentRemainderNode = NULL;

    if (divisor->data == 0) {
        exit(1);
    }

    while (dividend != NULL) {
        int currentDividend = dividend->data;
        if (remainder != NULL) {
            struct node* temp = makenode(currentDividend);
            temp->next = remainder;
            remainder = temp;
        } else {
            remainder = makenode(currentDividend);
        }

        int currentQuotient = 0;

        while (currentDividend >= divisor->data) {
            currentDividend -= divisor->data;
            currentQuotient++;
        }

        if (currentQuotient > 0) {
            if (quotient == NULL) {
                quotient = makenode(currentQuotient);
                currentQuotientNode = quotient;
            } else {
                currentQuotientNode->next = makenode(currentQuotient);
                currentQuotientNode = currentQuotientNode->next;
            }
        }

        dividend = dividend->next;
    }
    res.L = quotient;
    return res;
}

void display(struct BigInteger a)
{
    struct node *tmp = a.L;
    if (tmp==NULL)
    {
        printf("List is empty\n");
        return;
    }
    printf("\n");
    while (tmp != NULL)
    {
        printf("%d", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

