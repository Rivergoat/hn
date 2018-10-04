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

Decimal* new_decimal()
{
    Decimal* decimal = malloc(sizeof(Decimal));
    init(decimal);
    return decimal;
}

void traverse(Decimal* decimal)
{
    printf("[HEAD,");
    while(decimal -> next != NULL)
    {
        decimal = decimal -> next;
        printf("%d, ",decimal -> digit);
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

int append(Decimal* decimal, int indigit, int carry, int operator)
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

Decimal* ndadd(Decimal* sum_one, Decimal* sum_two)  //this is the nondestructive addition function
{
    int carry = 0, result_calc= 0;
    Decimal* result = new_decimal();
    while(sum_one -> next != NULL && sum_two -> next != NULL)
    {
        result_calc = sum_one -> next -> digit + sum_two -> next -> digit + carry;
        if(result_calc > 9)
        {
            result_calc -= 10;
            carry = 1;
        }
        else{carry = 0;}
        appenddigit(result, result_calc);
        //Now we need to move forward
        sum_one = sum_one -> next;
        sum_two = sum_two -> next;
    }
    if(sum_one -> next != NULL) //TODO(hnel): remove this if statement since it is unnecceassary
    {
        while(sum_one -> next != NULL)
        {
            result_calc = sum_one -> next -> digit + carry;
            if(result_calc > 9){result_calc -= 10; carry = 1;}   //result_calc could be set to zero directly since no greater carry is possible
            appenddigit(result, result_calc);
            sum_one = sum_one -> next;

        }
    }
    if(sum_two -> next != NULL) //TODO(hnel): remove this if statement since it is unnecceassary
    {
        while(sum_two -> next != NULL)
        {
            result_calc = sum_two -> next -> digit + carry;
            if(result_calc > 9){result_calc -= 10; carry = 1;}else{carry = 0;}   //result_calc could be set to zero directly since no greater carry is possible
            appenddigit(result, result_calc);
            sum_two = sum_two -> next;

        }
    }
    //if carry is still 1 (one), add a last element to the result,  containing a 1
    if(carry == 1){adddigit(result, 1);}
    return result;
}

//TODO(hnel): multiplication (multithreaded!)

int main()
{
    Decimal* b = parsestring("2");
    Decimal* a = parsestring("10");

    Decimal* c = ndadd(a,b);
    traverse(c);
}
//TODO(hne this shit doesn't work. carry goes lost? Numbers are not added correctly. This should be an easy fix
