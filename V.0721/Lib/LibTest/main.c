#include <stdio.h>
#include "add.h"
#include "sub.h"

int main() {
    int add;
    int subt;
    
    sum(1, 5, &add);
    sub(5, 1, &subt);
    
    printf("%d\n", add);
    printf("%d", subt);
}