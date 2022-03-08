int max(int a[], int length) {
    int first_element = a[0];

    if (length != 1) goto length_greater;
    return first_element;

length_greater:
    int max_so_far = max(&a[1], length - 1);
    if (first_element <= max_so_far) goto max_end;
    max_so_far = first_element;

max_end:
    return max_so_far;
}
