#include <stdio.h>

char flag[6][12] = {
    {'#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'},
    {'#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'},
    {'#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'}
};

int main(void) {

    int row = 0;
loop0:
    if (row >= 6) goto end0;

    int col = 0;
loop1:
    if (col >= 12) goto end1;

    printf ("%c", flag[row][col]);
    col++;
    goto loop1;

end1:
    printf("\n");
    row++;
    goto loop0;

end0:
    return 0;
}
