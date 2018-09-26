#include<stdio.h>
#include<stdlib.h>
#define bool int
#define true 1
#define false 0

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
    printf("[HEAD,");
    while(decimal -> next != NULL)
    {
        decimal = decimal -> next;
        printf("%d, ",decimal -> digit);
        printf("SPONGE!\n");
    }
    printf("TAIL]");
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
    decimal_c -> next -> next = NULL;
    return 0;
}

int append(Decimal* decimal, int indigit, int carry)
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
    printf("SPONGE!\n");
    int i = 0;
    while(string[i] != 0)
    {
        adddigit(linkedlist, string[i++] - 48);
    }
    printf("SPONGE\n");
    return linkedlist;
}

void pparsestring(Decimal** decimal, char* string)
{
    init(*decimal);
    printf("SPONGE!\n");
    int i = 0;
    while(string[i] != 0)
    {
        adddigit(*(decimal), string[i++] - 48);
    }
    printf("SPONGE\n");
}
void gotoindex(Decimal** decimal)
{
    Decimal *decimal_c = *decimal;
    while(decimal_c -> next != NULL)
    {
        decimal_c = decimal_c -> next;
    }
    *decimal = decimal_c;
}

Decimal* ndadd(Decimal* sum_one, Decimal* sum_two)  //TODO(Hnel): Add
{
    Decimal* result = malloc(sizeof(Decimal));
    Decimal* result_c = result;
    init(result);
    int i = 0,r = 0;
    while(sum_one -> next != NULL && sum_two -> next != NULL)
    {
        int carry = 0;
        if(result_c -> next != NULL)
        {
            carry = result_c -> next -> carry;
        }
        int digitsum = sum_one -> next -> digit + sum_two -> next -> digit + carry;
        if(digitsum < 10)
        {
            appenddigit(result, digitsum);
        }
        else
        {
            appenddigit(result, digitsum - 10);
            result -> next -> carry = 1;
        }
        //traverse(result_c);
        result = result -> next;
        sum_one = sum_one -> next;
        sum_two = sum_two -> next;
        ++i;
        if(sum_one -> next == NULL){r = 1;}
        else if(sum_two -> next == NULL){r = 2;}
    }
    
    traverse(result_c);
    //TODO(Hnel): add carry add even after the loop broke. This implies checking the current place we are at, aswell as n - 1 correcting.
    return result;
}
void nl(){printf("\n");}
void freell(Decimal* decimal)   //interesting behaviour. It appears memory is not instantly purged but rather freed as the name suggests
{
    while(decimal -> next != NULL)
    {
        Decimal* old = decimal;
        decimal  = decimal -> next;
        free(old);
    }
    free(decimal -> next);
}

int main()
{
    Decimal* decimal = malloc(sizeof(Decimal));
    init(decimal);
    decimal -> next = malloc(sizeof(Decimal));
    decimal -> next -> digit = 1;
    decimal -> next -> next = malloc(sizeof(Decimal));
    decimal -> next -> next -> digit = 4;
    decimal -> next -> next -> next  = malloc(sizeof(Decimal));
    decimal -> next -> next -> next -> digit = 8;
    decimal -> next -> next -> next -> next  = malloc(sizeof(Decimal));
    decimal -> next -> next -> next -> next -> digit = 8;
    decimal -> next -> next -> next -> next -> next = NULL;
    adddigit(decimal, 9);
    Decimal* b = parsestring("1235813");

    traverse(b);
    





}
