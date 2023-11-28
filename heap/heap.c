#include <stdio.h>
void printArray(int arr[], int n);
// Função para fazer o heapify de uma subárvore enraizada no índice i
void heapify(int arr[], int n, int i) {
    int maior = i; // Inicializa o maior como raiz
    int esq = 2 * i + 1; // Índice do filho esquerdo
    int dir = 2 * i + 2; // Índice do filho direito

    // Se o filho esquerdo é maior que a raiz
    if (esq < n && arr[esq] > arr[maior])
        maior = esq;

    // Se o filho direito é maior que a raiz
    if (dir < n && arr[dir] > arr[maior])
        maior = dir;

    // Se o maior não é a raiz
    if (maior != i) {
        // Troca o maior com a raiz
        int temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;

        // Chama recursivamente a função heapify na subárvore afetada
        heapify(arr, n, maior);
    }
}

// Função para realizar o Heap-Sort
void heapSort(int arr[], int n) {
    // Constrói o heap (reorganiza o array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    printArray(arr, n);
    // Extrai elementos um por um do heap
    for (int i = n - 1; i > 0; i--) {
        // Move a raiz (o maior elemento) para o final do array ordenado
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Chama heapify na subárvore reduzida
        heapify(arr, i, 0);
    }
}

// Função para imprimir um array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7, 10, 15, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original:\n");
    printArray(arr, n);

    heapSort(arr, n);

    printf("\nArray ordenado usando Heap-Sort:\n");
    printArray(arr, n);
    return 0;
}
