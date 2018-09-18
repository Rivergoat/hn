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
    decimal_c -> next -> carry = 0;
    return 0;
}

int append(Decimal* decimal, int indigit, int carry)
    //thsi here is a simple test to determine the average outcome of this shit
    //
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
    decimal_c -> next -> carry = carry;
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
    Decimal* linkedlist = malloc(sizeof(Decimal));  //check whehter this is really necaasary
    init(linkedlist);
    int i = 0;
    while(string[i] != 0)
    {
        adddigit(linkedlist, string[i++] - 48);
    }
    return linkedlist;
}

Decimal* ndadd(Decimal* sum_one, Decimal* sum_two)
{
    //this segfaults even though it shouldnt, please debug
    Decimal* result = malloc(sizeof(Decimal));
    init(result);
    int i = 0;
    while(sum_one -> next != NULL && sum_two -> next != NULL)
    {
        int digitsum = sum_one -> next -> digit + sum_two -> next -> digit + result -> carry;
        if(digitsum < 10)
        {
            appenddigit(result, digitsum);
        }else{
            appenddigit(result, digitsum - 10);
            result -> next -> carry = 1;
        }
        result = result -> next;
        sum_one = sum_one -> next;
        sum_two = sum_two -> next;
       i++;

    }
    //TODO(Hnel): add carry add even after the loop broke. This implies checking the current place we are at, aswell as n - 1 correting.
}

int main()
{
    Decimal* a = parsestring("1488");
    Decimal* b = parsestring("1488");
    Decimal* c = ndadd(a,b);
    traverse(c);
    return 0;
}
