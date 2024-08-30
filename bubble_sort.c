#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

// Função para gerar um número inteiro aleatório entre min e max
int random_int(int min, int max)
{
    return min + rand() % (max - min + 1);
}

// Implementação do algoritmo Bubble sort
void bubble_sort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Função para ordenar o array usando o algoritmo "ordenação de raiz quadrada"
void sqrt_sort(int arr[], int n)
{
    // Determinando o tamanho de cada "pedaço" do array
    int chunk_size = (int)sqrt(n);
    // Calculando o número total de "pedaços"
    int num_chunks = (n + chunk_size - 1) / chunk_size;

    // Alocando espaço para o array de resultados
    int *result = malloc(n * sizeof(int));
    // Índice para acompanhar a posição atual no array de resultados
    int result_index = 0;

    // Iterando sobre cada "pedaço" do array
    for (int i = 0; i < num_chunks; i++)
    {
        // Determinando o início e o final do "pedaço" atual
        int start = i * chunk_size;
        int end = start + chunk_size;
        if (end > n)
            end = n;
        
        // Ordenando o "pedaço" usando Bubble Sort
        bubble_sort(arr + start, end - start);

        // Armazenando os elementos do "pedaço" ordenado no array de resultados
        for (int j = start; j < end; j++)
        {
            result[result_index++] = arr[j];
        }
    }

    // Copiando os resultados ordenados de volta para o array original
    memcpy(arr, result, n * sizeof(int));
    // Liberando a memória alocada para o array de resultados
    free(result);
}

int main()
{
    // Inicializando a semente para gerar números aleatórios
    srand(time(NULL));

    // Tamanhos das entradas para testes
    int sizes[] = {10000, 100000, 1000000, 10000000, 100000000};
    // Número total de tamanhos de entrada
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    // Loop através de cada tamanho de entrada
    for (int i = 0; i < num_sizes; i++)
    {
        // Alocando memória para o array com o tamanho da entrada atual
        int *array = malloc(sizes[i] * sizeof(int));

        // Preenchendo o array com números aleatórios
        for (int j = 0; j < sizes[i]; j++)
        {
            array[j] = random_int(1, sizes[i]);
        }

        // Medindo o tempo de execução médio
        double total_time = 0;
        for (int j = 0; j < 5; j++)
        {
            clock_t start_time = clock();
            sqrt_sort(array, sizes[i]);
            clock_t end_time = clock();
            total_time += ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000;
        }
        double avg_time = total_time / 5;

        // Imprimindo o tamanho da entrada e o tempo médio de execução
        printf("Tamanho da entrada: %d, Tempo médio: %.6fms\n", sizes[i], avg_time);

        // Liberando a memória alocada para o array
        free(array);
    }

    return 0;
}

