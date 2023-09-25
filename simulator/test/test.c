
int bubble_sort(int *array, int size)
{
    int i, j, temp;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size - 1 - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
            }
        }
    }
    return 0;
}
int main()
{
    int array[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
    bubble_sort(array, 10);
 
    return 0;
}