#include <stdio.h>

int main(void) {
    int i;
    int numbers[10] = {0};

    i = 0;

loop0:
loop0_condition:
    if (i >= 10) goto end0;
loop0_body:
    scanf("%d", &numbers[i]);
loop0_increment:
    i++;
loop0_repeat:
    goto loop0;

end0:
    i = 9;

loop1:
    if (i < 0) goto end1;
    printf("%d\n", numbers[i]);
    i--;
    goto loop1;

end1:
    return 0;
}
