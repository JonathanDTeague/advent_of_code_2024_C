#include <stdio.h>
#include <stdlib.h>

void sort(int a[], int length);
void sort_rec(int a[], int l, int r);
void sorted_array(int a[], int l, int m, int r);

int main(void)
{
    FILE *fptr = fopen("values.txt", "r");
    int first_list[1000];
    int second_list[1000];
    int count = 0;
    int total = 0;

    if (fptr == NULL)
    {
        printf("Not able to open the file.\n");
        return 1;
    }

    while (fscanf(fptr, "%d %d", &first_list[count], &second_list[count]) == 2)
    {
        count++;
        if (count >= 1000) break; // Prevent buffer overflow
    }

    fclose(fptr);

    sort(first_list, count);
    sort(second_list, count);
    
    for (int i = 0; i < count; i++)
    {
        if (first_list[i] > second_list[i])
        {
            total += (first_list[i] - second_list[i]);
        }
        else
        {
            total += (second_list[i] - first_list[i]);
        }
        
    }
    
    printf("%d\n", total);

    return 0;
}

void sort(int a[], int length)
{
    if (length > 1)
        sort_rec(a, 0, length - 1);
}

void sort_rec(int a[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        sort_rec(a, l, m);
        sort_rec(a, m + 1, r);

        sorted_array(a, l, m, r);
    }
}

void sorted_array(int a[], int l, int m, int r)
{
    int left_length = m - l + 1;
    int right_length = r - m;

    int *tmp_left = malloc(left_length * sizeof(int));
    int *tmp_right = malloc(right_length * sizeof(int));

    if (!tmp_left || !tmp_right)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < left_length; i++)
        tmp_left[i] = a[l + i];

    for (int i = 0; i < right_length; i++)
        tmp_right[i] = a[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < left_length && j < right_length)
    {
        if (tmp_left[i] <= tmp_right[j])
            a[k++] = tmp_left[i++];
        else
            a[k++] = tmp_right[j++];
    }

    while (i < left_length)
        a[k++] = tmp_left[i++];

    while (j < right_length)
        a[k++] = tmp_right[j++];

    free(tmp_left);
    free(tmp_right);
}
