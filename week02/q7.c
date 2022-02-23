#include <stdio.h>

int main(void) {
    int x = 24;

loop:
    if (x >= 42) goto end;
    printf ("%d\n", x);
    x += 3;
    goto loop;

end:
    return 0;
}
