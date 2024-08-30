#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

// Função para gerar um número inteiro aleatório entre min e max
int random_int(int min, int max)
{
    return min + rand() % (max - min + 1);
}

// Função para ajustar o Heap com raiz em índice i
void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;

    // Verifica se o filho da esquerda existe e é maior que o pai
    if (left_child < n && arr[left_child] > arr[largest])
        largest = left_child;

    // Verifica se o filho da direita existe e é maior que o pai
    if (right_child < n && arr[right_child] > arr[largest])
        largest = right_child;

    // Se o maior elemento não for o pai, faz a troca e chama Heapify recursivamente
    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

// Função para construir o Heap
void make_heap(int arr[], int n)
{
    // Começa a partir do último nó não-folha e vai até o primeiro
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

// Função para remover o maior elemento do Heap e retorná-lo
int remove_heap(int arr[], int *n)
{
    int root = arr[0];
    arr[0] = arr[(*n) - 1];
    (*n)--;
    heapify(arr, *n, 0);
    return root;
}

// Função para ordenar o array usando heapsort
void heap_sort(int arr[], int n)
{
    make_heap(arr, n);
    for (int i = n - 1; i >= 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// Função para ordenar o array usando o algoritmo "ordenação de raiz quadrada"
void sqrt_sort(int arr[], int n)
{
    int chunk_size = (int)sqrt(n);
    int num_chunks = (n + chunk_size - 1) / chunk_size;

    int *result = malloc(n * sizeof(int));
    int result_index = 0;

    for (int i = 0; i < num_chunks; i++)
    {
        int start = i * chunk_size;
        int end = start + chunk_size;
        if (end > n)
            end = n;
        
        heap_sort(arr + start, end - start);
        for (int j = start; j < end; j++)
        {
            result[result_index++] = arr[j];
        }
    }

    memcpy(arr, result, n * sizeof(int));
    free(result);
}

int main()
{
    srand(time(NULL));

    int sizes[] = {10000, 100000, 1000000, 10000000, 100000000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++)
    {
        int *array = malloc(sizes[i] * sizeof(int));

        for (int j = 0; j < sizes[i]; j++)
        {
            array[j] = random_int(1, sizes[i]);
        }

        double total_time = 0;
        for (int j = 0; j < 5; j++)
        {
            clock_t start_time = clock();
            sqrt_sort(array, sizes[i]);
            clock_t end_time = clock();
            total_time += ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000;
        }
        double avg_time = total_time / 5;

        printf("Tamanho da entrada: %d, Tempo médio: %.6fms\n", sizes[i], avg_time);

        free(array);
    }

    return 0;
}

