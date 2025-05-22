#include <stdio.h>
#include "extern1.h"
// extern int shared_var;
// extern void display(void);

int main()
{
    display();
    shared_var += 50;
    display();
    return 0;
}
