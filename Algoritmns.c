//Exchange sort, Mergesort, Quicksort, Heapsort, Radix sort 알고리즘을 C언어로 구현
//100, 500, 1000, 5000, 10000개의 random generated data에 대해 실행 시간을 비교
//실행 시간은 각 test case에 대해 5회 반복 실행하여 평균값


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//데이터의 개수 지정
#define SIZE 1000 //100, 500, 1000, 5000, 10000 변환해가며 실행하기 

int array[SIZE];    //각 정렬 알고리즘에서 필요한 배열
int original[SIZE];    //랜덤 데이터를 저장할 원본 배열
int sorted[SIZE]; //합병정렬에서 필요한 추가적인 배열
 
int n; //데이터의 개수를 받는 전역변수 설정
clock_t start, finish, used_time = 0;    //실행 시간 측정을 위한 변수


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
// // 두 개의 요소의 위치를 바꾸기 위한 함수 
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// partition position을 찾기 위한 함수 
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

//원본 배열을 복사하는 함수
void CopyArr(void)
{
    int i;
    for (i = 0; i < n; i++)
        array[i] = original[i];
}

//실행 시간을 측정 및 출력하는 함수
double CalcTime(void)
{
    used_time = finish - start;
    return (float)used_time / CLOCKS_PER_SEC;
}

void main()
{
    printf("Exchange sort, Mergesort, Quicksort, Heapsort, Radix sort 알고리즘\n");
    printf("100, 500, 1000, 5000, 10000개의 random generated data에 대해 실행 시간을 비교\n");

    n = SIZE;  // 이를 통해서 실행 시간을 조절한다. 
    double calcuate_exchange_sum = 0;
    double calcuate_heap_sum = 0;
    double calcuate_radix_sum = 0;
    double calcuate_merge_sum = 0;
    double calcuate_quick_sum = 0;

    for (int i = 0; i < n; i++)
        original[i] = rand();
    printf("[ 데이터의 개수 : %d ]\n\n", n);

    printf("1. Exchange sort start\n");
    for (int j = 0; j < 5; j++) {
        CopyArr();
        start = clock();
        exchange_sort(array, n);
        finish = clock();
        calcuate_exchange_sum += CalcTime();
    }
    printf("1. Exchange sort complete\n");
    printf("1. Exchange sort average running time %f sec\n\n", calcuate_exchange_sum / 5);  //평균시간이기에 5로 나누었다. 


    printf("2. Heap sort start\n");
    for (int j = 0; j < 5; j++) {
        CopyArr();
        start = clock();
        heap_sort(array, n);
        finish = clock();
        calcuate_heap_sum += CalcTime();
    }
    printf("2. Heap sort complete\n");
    printf("2. Heap sort average running time %f sec\n\n", calcuate_heap_sum / 5);  //평균시간이기에 5로 나누었다.

   printf("3. Radix sort start\n");
    for (int j = 0; j < 5; j++) {
        CopyArr();
        start = clock();
        radix_sort(array, n);
        finish = clock();
        calcuate_radix_sum += CalcTime();
    }
    printf("3. Radix sort complete\n");
    printf("3. Radix sort average running time %f sec\n\n", calcuate_radix_sum / 5);  //평균시간이기에 5로 나누었다. */


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
    printf("4. Merge sort average running time %f sec\n\n", calcuate_merge_sum / 5);  //평균시간이기에 5로 나누었다. 

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
    printf("5. Quick sort average running time %f sec\n\n", calcuate_quick_sum / 5);  //평균시간이기에 5로 나누었다. 
}