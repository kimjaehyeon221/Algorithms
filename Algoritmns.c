//Exchange sort, Mergesort, Quicksort, Heapsort, Radix sort �˰����� C���� ����
//100, 500, 1000, 5000, 10000���� random generated data�� ���� ���� �ð��� ��
//���� �ð��� �� test case�� ���� 5ȸ �ݺ� �����Ͽ� ��հ�


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//�������� ���� ����
#define SIZE 1000 //100, 500, 1000, 5000, 10000 ��ȯ�ذ��� �����ϱ� 

int array[SIZE];    //�� ���� �˰��򿡼� �ʿ��� �迭
int original[SIZE];    //���� �����͸� ������ ���� �迭
int sorted[SIZE]; //�պ����Ŀ��� �ʿ��� �߰����� �迭
 
int n; //�������� ������ �޴� �������� ����
clock_t start, finish, used_time = 0;    //���� �ð� ������ ���� ����


// ================ Exchange sort ===============
void exchange_sort (int array[], int n) {
    int* i, * j, temp;
    int* const end = array + n;

    for (i = array; i < end - 1; i++) {
        for (j = i + 1; j < end; j++) {
            if (*i > *j) {
                temp = *i;
                *i = *j;
                *j = temp;
            }
        }
    }
}

// ================ Merge sort ===============
void merge(int array[], int left, int mid, int right)
{
    int i, j, k, l;
    i = left, j = mid + 1; k = left;

    while (i <= mid && j <= right)
    {
        if (array[i] <= array[j])
            sorted[k++] = array[i++];
        else
            sorted[k++] = array[j++];
    }

    if (i > mid)
        for (l = j; l <= right; l++)
            sorted[k++] = array[l];
    else
        for (l = i; l <= right; l++)
            sorted[k++] = array[l];

    for (l = left; l <= right; l++)
        array[l] = sorted[l];
}
void merge_sort(int array[], int left, int right)
{
    int mid;
    if (left < right)
    {
        mid = (left + right) / 2;
        merge_sort(array, left, mid);
        merge_sort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

// ================ Quick sort ===============
// // �� ���� ����� ��ġ�� �ٲٱ� ���� �Լ� 
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// partition position�� ã�� ���� �Լ� 
int partition(int array[], int low, int high) {

    int pivot = array[high];

    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {

            i++;

            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[high]);

    return (i + 1);
}

void quick_sort(int array[], int left, int right)
{
    if (left < right)
    {
        int q = partition(array, left, right);
        quick_sort(array, left, q - 1);
        quick_sort(array, q + 1, right);
    }
}

//=================== Heap sort ====================
void heapify(int array[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && array[left] > array[largest])
        largest = left;

    if (right < n && array[right] > array[largest])
        largest = right;

    if (largest != i) {
        swap(&array[i], &array[largest]);
        heapify(array, n, largest);
    }
}

void heap_sort(int array[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(&array[0], &array[i]);

        heapify(array, i, 0);
    }
}

// ============= Radix Sort ============
int getMax(int a[], int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max)
            max = a[i];
    }
    return max;  
}

void countingSort(int a[], int n, int place) 
{
    int output[SIZE + 1];
    int count[10] = { 0 };

    for (int i = 0; i < n; i++)
        count[(a[i] / place) % 10]++;


    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(a[i] / place) % 10] - 1] = a[i];
        count[(a[i] / place) % 10]--;
    }

    for (int i = 0; i < n; i++)
        a[i] = output[i];
}

void radix_sort(int a[], int n) {

    int max = getMax(a, n);

    for (int place = 1; max / place > 0; place *= 10)
        countingSort(a, n, place);
}

//���� �迭�� �����ϴ� �Լ�
void CopyArr(void)
{
    int i;
    for (i = 0; i < n; i++)
        array[i] = original[i];
}

//���� �ð��� ���� �� ����ϴ� �Լ�
double CalcTime(void)
{
    used_time = finish - start;
    return (float)used_time / CLOCKS_PER_SEC;
}

void main()
{
    printf("Exchange sort, Mergesort, Quicksort, Heapsort, Radix sort �˰���\n");
    printf("100, 500, 1000, 5000, 10000���� random generated data�� ���� ���� �ð��� ��\n");

    n = SIZE;  // �̸� ���ؼ� ���� �ð��� �����Ѵ�. 
    double calcuate_exchange_sum = 0;
    double calcuate_heap_sum = 0;
    double calcuate_radix_sum = 0;
    double calcuate_merge_sum = 0;
    double calcuate_quick_sum = 0;

    for (int i = 0; i < n; i++)
        original[i] = rand();
    printf("[ �������� ���� : %d ]\n\n", n);

    printf("1. Exchange sort start\n");
    for (int j = 0; j < 5; j++) {
        CopyArr();
        start = clock();
        exchange_sort(array, n);
        finish = clock();
        calcuate_exchange_sum += CalcTime();
    }
    printf("1. Exchange sort complete\n");
    printf("1. Exchange sort average running time %f sec\n\n", calcuate_exchange_sum / 5);  //��սð��̱⿡ 5�� ��������. 


    printf("2. Heap sort start\n");
    for (int j = 0; j < 5; j++) {
        CopyArr();
        start = clock();
        heap_sort(array, n);
        finish = clock();
        calcuate_heap_sum += CalcTime();
    }
    printf("2. Heap sort complete\n");
    printf("2. Heap sort average running time %f sec\n\n", calcuate_heap_sum / 5);  //��սð��̱⿡ 5�� ��������.

   printf("3. Radix sort start\n");
    for (int j = 0; j < 5; j++) {
        CopyArr();
        start = clock();
        radix_sort(array, n);
        finish = clock();
        calcuate_radix_sum += CalcTime();
    }
    printf("3. Radix sort complete\n");
    printf("3. Radix sort average running time %f sec\n\n", calcuate_radix_sum / 5);  //��սð��̱⿡ 5�� ��������. */


    printf("4. Merge sort start\n");
    for (int j = 0; j < 5; j++) {
        CopyArr();
        start = clock();
        printf("[%d] Radix sort running ...", j);
        merge_sort(array, 0, n);
        finish = clock();
        calcuate_merge_sum += CalcTime();
    }
    printf("\n");
    printf("4. Merge sort complete \n");
    printf("4. Merge sort average running time %f sec\n\n", calcuate_merge_sum / 5);  //��սð��̱⿡ 5�� ��������. 

    printf("5. Quick sort start\n");
    for (int j = 0; j < 5; j++) {
        CopyArr();
        start = clock();
        printf("[%d] Quick sort running ... ", j);
        quick_sort(array, 0, n);
        finish = clock();
        calcuate_quick_sum += CalcTime();
    }
    printf("\n");
    printf("5. Quick sort complete\n");
    printf("5. Quick sort average running time %f sec\n\n", calcuate_quick_sum / 5);  //��սð��̱⿡ 5�� ��������. 
}