#include <stdio.h>

int main(void) {
    int x;
    printf("Enter a number: ");
    scanf("%d", &x);

    char *message = "small/big\n";
    if (x <= 100) goto end;
    if (x >= 1000) goto end;
    message = "medium";


end:
    printf("%s", message);
}
