#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
typedef struct 
{
    unsigned long long arr[35];
    int size;
} bigInt;

//here we could have used normal objects too since we are returning the object
bigInt *initialize(char *s)
{
    bigInt *newptr = (bigInt*)malloc(sizeof(bigInt));
    int k;
    int i = 0, num = 0;
    k = strlen(s) % 9;
    for (int j = 0; j < k; j++)
    {
        num = num * 10 + ((int)s[i] - 48);
        i++;
    }
    newptr->arr[0]= num;
    k = 1;
    while (s[i] != '\0')
    {
        num = 0;
        for (int j = 0; s[i] != '\0' && j < 9; j++)
        {
            num = num * 10 + ((int)s[i] - 48);
            i++;
        }
        newptr->arr[k] = num;
        k++;
    }
    newptr->size = k-1;
    return newptr;
}

int compare(char *s)
{
    bigInt *p = initialize(s);
    int ret_val = 1, i = 0;
    bigInt *largest = initialize("179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137216");
    if (p->size == largest->size)
    {
        while (i < p->size && largest->arr[i] == p->arr[i]) i++;
        if (i == p->size+1 || largest->arr[i] < p->arr[i]) ret_val = 0;
    }
    else if (p->size > largest->size)
    {
        ret_val = 0;
    }
    return ret_val;
}

void add(char *s1, char *s2)
{
    bigInt *a = initialize(s1);
    bigInt *b = initialize(s2);
    bigInt *c = (bigInt*)malloc(sizeof(bigInt));
    int size = a->size , carry = 0, start= 1;
    if (size < b->size ) size = b->size;
    size++;
    c->size = size;
    while (a->size >= 0 || b->size >= 0)
    {
        if (a->size >= 0 && b->size >= 0)
        {
            c->arr[size] = a->arr[a->size] + b->arr[b->size] + carry;
            a->size--;
            b->size--;
        }
        else if (a->size < 0)
        {
            c->arr[size] = b->arr[b->size] + carry;
            b->size--;
        }
        else
        {
            c->arr[size] = a->arr[a->size] + carry;
            a->size--;
        }
        if (c->arr[size] > 999999999)//10^9-1
        {
            c->arr[size] = c->arr[size] - 1000000000;//10^9
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        size--;
    }
    if (carry == 1)
    {
        c->arr[0] = 1;
        start = 0;
    }
    int i = 0, overflow = 0;
    bigInt *largest = initialize("179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137216");
    if (c->size >= largest->size)
    {
        if (c->size == largest->size)
        {
            while (i < c->size && largest->arr[i] == c->arr[i]) i++;
            if (i == c->size+1 || largest->arr[i] < c->arr[i]) overflow = 1;
        }
        else
        {
            overflow = 1;
        }
    }
    if (overflow == 1)
    {
        printf ("\nOverflow");
    }
    else
    {
        int x, count;
        printf("\nSum is: ");
        for (int i = start; i <= c->size; i++)
        {
            if (i != start)
            {
                x = 1, count = 9;
                while (c->arr[i]/x != 0)
                {
                    x=x*10;
                    count--;
                }
                while (count != 0)
                {
                    printf ("0");
                    count--;
                }
            }
            printf("%" PRIu64, c->arr[i]);
        }  
    }
}

void subtract(char *s1, char *s2)
{
    bigInt *a = initialize(s1);
    bigInt *b = initialize(s2);
    bigInt *c = (bigInt*)malloc(sizeof(bigInt));
    int size = a->size , borrow = 0, compare = 1;
    size = a->size;
    c->size = size;
    int i = 0;
    if (a->size == b->size)
    {
        while (i <= a->size && a->arr[i] == b->arr[i]) i++;
        if (i <= a->size && a->arr[i] < b->arr[i]) compare = 0;
    }
    else if (b->size > a->size)
    {
        compare = 0;
    }
    if (compare == 0) printf ("\nDifference is: Negative");
    else
    {
        while (a->size >= 0)
        {
            if (b->size >= 0)
            {
                if (a->arr[a->size] >= b->arr[b->size] + borrow)
                {
                    c->arr[size] = a->arr[a->size] - b->arr[b->size] - borrow;
                    borrow = 0;
                }
                else
                {
                    c->arr[size] = a->arr[a->size] - b->arr[b->size] - borrow + 1000000000;//10^9
                    borrow = 1;
                }
                b->size--;
            }
            else
            {
                if (a->arr[a->size] >= (unsigned long long)borrow)
                {
                    c->arr[size] = a->arr[a->size] - borrow;
                    borrow = 0;
                }
                else
                {
                    c->arr[size] = a->arr[a->size] + 100000000 - borrow;
                    borrow = 1;
                }
            }
            size--;
            a->size--;
        }
        int x, count;
        printf("\nDifference is: ");
        for (int i = 0; i <= c->size; i++)
        {
            if (i != 0)
            {
                x = 1, count = 9;
                while (c->arr[i]/x != 0)
                {
                    x=x*10;
                    count--;
                }
                while (count != 0)
                {
                    printf ("0");
                    count--;
                }
            }
            printf("%" PRIu64, c->arr[i]);
        }
    }
}

void multiply(char *s1, char *s2)
{
    bigInt *a = initialize(s1);
    bigInt *b = initialize(s2);
    bigInt *c = (bigInt*)malloc(sizeof(bigInt));
    c->size = a->size + b->size + 1;

    for (int i = 0; i < c->size; i++)
    {
        c->arr[i] = 0;
    }

    if (a->size + b->size + 2 > 35)
    {
        printf ("\nToo large Numbers!");
    } 
    else
    {
        for (int i = 0; i <= a->size; i++)
        {
            for (int j = 0; j <= b->size; j++)
            {
                c->arr[i+j+1] = c->arr[i+j+1] + (a->arr[i] * b->arr[j]) % 1000000000;//10^9
                c->arr[i+j] = c->arr[i+j] + (a->arr[i] * b->arr[j]) / 1000000000;//10^9
            }
        }

        for (int i = c->size; i > 0; i--)
        {
            c->arr[i-1] = c->arr[i-1] + c->arr[i] / 1000000000;
            c->arr[i] = c->arr[i] % 1000000000;
        }

        int i = 0, overflow = 0;
        bigInt *largest = initialize("179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137216");
        if (c->size >= largest->size)
        {
            if (c->size == largest->size)
            {
                while (i < c->size && largest->arr[i] == c->arr[i]) i++;
                if (i == c->size+1 || largest->arr[i] < c->arr[i]) overflow = 1;
            }
            else
            {
                overflow = 1;
            }
        }
        if (overflow == 1)
        {
            printf ("\nOverflow");
        }
        else
        {
            printf("\nProduct is: ");
            int start = 0;
            while (start < c->size - 1 && c->arr[start] == 0)
            {
                start++;
            }
            int x = 1, count = 9;
            for (int i = start; i <= c->size; i++)
            {
                if (i != start)
                {
                    x = 1, count = 9;
                    while (c->arr[i]/x != 0)
                    {
                        x=x*10;
                        count--;
                    }
                    while (count != 0)
                    {
                        printf ("0");
                        count--;
                    }
                }
                printf("%" PRIu64, c->arr[i]);
            }
        }
    }
}

int main()
{
    printf ("Enter two numbers: \n");
    char s1[309], s2[309];
    scanf ("%s %s", s1, s2);
    if (compare(s1) && compare(s2))
    {
        add(s1, s2);
        subtract(s1, s2);
        multiply(s1, s2);
    }
    return 0;
}

// add("53425326432634256312", "867686765531"); 53425327300321021843
// subtract("53425326432634256312", "867686765531"); 53425325564947490781
// multiply("53425326432634256312", "867686765531"); 46356448689770256623268900781672