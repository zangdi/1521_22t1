#include <stdio.h>

int main(void) {
    int x, y;
    printf("Enter a number: ");
    scanf("%d", &x);

    if (x > 46340) goto square_too_big;
    y = x * x;
    printf("%d\n", y);
    goto end;

square_too_big:
    printf("square too big for 32 bits\n");

end:
    return 0;
}
