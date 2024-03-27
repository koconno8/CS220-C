#include <stdio.h>

#define SUM(a, b) ((a) + (b))
#define BIT(n) (1 << (n))
#define IS_SET(v, n) (((v) & BIT(n)) != 0)
#define BIT_SET(v, n) (v |= BIT(n))
#define BIT_CLEAR(v, n) (v &= ~(BIT(n)))
#define BIT_FLIP(v, n) (IS_SET(v, n))?BIT_CLEAR(v,n):BIT_SET(v,n)

struct bad_struct{
    short s1;
    long l1;
    short s2;
};

struct good_struct{
    short s1;
    short s2;
    long l1;
};

union unit{
    char c;
    int i;
    long l;
};

enum Grade {F = 0, E, D, C, B, A};

void print_in_binary(unsigned int x) {
    for (int i = 31; i >= 0; i--) 
    {
        if (IS_SET(x, i))
        {
            printf("1");
        } 
        else
        {
            printf("0");
        }
    }
    printf("\n");

    for (int k = 31; k >= 0; k--)
    {
        BIT_FLIP(x, k);
    }


    for (int j = 31; j >= 0; j--) 
    {
        if (IS_SET(x, j))
        {
            printf("1");
        } 
        else
        {
            printf("0");
        }
    }
    printf("\n");

}



int main()
{
    struct good_struct gs;
    struct bad_struct bs;
    
    union unit u;

    enum Grade g = A;

    printf("Size of gs: %d\n", sizeof(gs));
    printf("Size of bs: %d\n", sizeof(bs));

    printf("Address of gs.s1: %p\n", &gs.s1);
    printf("Address of gs.s2: %p\n", &gs.s2);
    printf("Address of gs.l1: %p\n", &gs.l1);

    printf("Address of bs.s1: %p\n", &bs.s1);
    printf("Address of bs.l1: %p\n", &bs.l1);
    printf("Address of bs.s2: %p\n", &bs.s2);

    printf("Size of u: %d\n", sizeof(u));
    
    printf("Address of u.c: %p\n", &u.c);
    printf("Address of u.i: %p\n", &u.i);
    printf("Address of u.l: %p\n", &u.l);

    printf("Enter a long value: ");
    scanf("%lu", &u.l);

    printf("%c, %lu, %d, %s\n", u.c, u.l, u.i, &u.l);

    printf("Grade g = %d\n", g);

    const char enum2str[] = {'F', 'E', 'D', 'C', 'B', 'A'};
    printf("Grade g = %c\n", enum2str[g]);

    unsigned int x = 21;
    print_in_binary(x);
}

