#include<stdio.h>
#include<stdlib.h>

typedef struct decimal
{
    int digit;
    int place;
    int carry;
    struct decimal* next;
}Decimal;

void init(Decimal* decimal)
{
    decimal -> next = NULL;
    decimal -> digit = 5;
    decimal -> place = 0;
}

void traverse(Decimal* decimal)
{
    Decimal *decimal_c = decimal;
    while(decimal_c -> next != NULL)
    {
        decimal_c = decimal_c -> next;
        printf("%d\n",decimal_c -> digit);
    }
}

int getlastdigit(Decimal* decimal)
{
    Decimal *decimal_c = decimal;
    while(decimal_c -> next != NULL)
    {
        decimal_c = decimal_c -> next;
    }
    return decimal_c -> digit;
}

int appenddigit(Decimal* decimal, int indigit)
{
    if(indigit > 9)
    {
        return -1;
    }
    Decimal *decimal_c = decimal;
    while(decimal_c -> next != NULL)
    {
        decimal_c = decimal_c -> next;
    }
    decimal_c -> next = malloc(sizeof(Decimal));
    decimal_c -> next -> digit = indigit;
    return 0;
}

void adddigit(Decimal* decimal, int indigit)
{
    Decimal* swap = decimal -> next;
    decimal -> next = malloc(sizeof(Decimal));
    decimal -> next -> next = swap;
    decimal -> next -> digit = indigit;
}

void makelentable(Decimal* decimal)
{
    int i = 0;
    Decimal* decimal_c = decimal;
    while(decimal_c -> next != NULL)
    {
        decimal_c = decimal_c -> next;
        decimal_c -> place = i++;
    }
}

void traversedebug(Decimal* decimal)
{
    Decimal *decimal_c = decimal;
    while(decimal_c -> next != NULL)
    {
        decimal_c = decimal_c -> next;
        printf("[Dec: %d, Place: %d]\n",decimal_c -> digit,decimal_c -> place);
    }
}

Decimal* parsestring(char* string)
{
    Decimal* linkedlist;
    int i = 0;
    while(string[i] != 0)
    {

    }
}

int main(int argc, char *argv[])
{
    Decimal k;
    init(&k);
    appenddigit(&k, 1);
    appenddigit(&k, 2);
    appenddigit(&k, 3);
    appenddigit(&k, 4);
    appenddigit(&k, 5);
    printf("Last digit is %d\n",getlastdigit(&k));
    traverse(&k);
    makelentable(&k);
    traversedebug(&k);


    return 0;
}
