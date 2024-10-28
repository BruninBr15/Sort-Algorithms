#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *numeros;
    int tamanho;
    int capacidade;
} LeitorArquivo;

// Função para inicializar a estrutura LeitorArquivo
void inicializarLeitor(LeitorArquivo *leitor) {
    leitor->capacidade = 10;
    leitor->tamanho = 0;
    leitor->numeros = (int *)malloc(leitor->capacidade * sizeof(int));
}

// Função para redimensionar o vetor se necessário
void redimensionar(LeitorArquivo *leitor) {
    leitor->capacidade *= 2;
    leitor->numeros = (int *)realloc(leitor->numeros, leitor->capacidade * sizeof(int));
}

// Função para ler o arquivo e preencher o vetor de números
void lerArquivo(LeitorArquivo *leitor, const char *caminhoDoArquivo) {
    FILE *file = fopen(caminhoDoArquivo, "r");
    if (!file) {
        printf("Ocorreu um erro ao tentar ler o arquivo.\n");
        return;
    }
    
    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        int numero;
        if (sscanf(linha, "%d", &numero) == 1) {
            if (leitor->tamanho >= leitor->capacidade) {
                redimensionar(leitor);
            }
            leitor->numeros[leitor->tamanho++] = numero;
        } else {
            printf("Valor inválido encontrado e ignorado: %s", linha);
        }
    }
    fclose(file);
}

// Função para exibir os dados
void exibirDados(int *dados, int tamanho) {
    printf("Lista de Dados: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", dados[i]);
    }
    printf("\n");
}

// Função para ordenar o vetor usando Insertion Sort
void insertionSort(int *dados, int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int chave = dados[i];
        int j = i - 1;
        while (j >= 0 && dados[j] > chave) {
            dados[j + 1] = dados[j];
            j = j - 1;
        }
        dados[j + 1] = chave;
    }
}

// Função para trocar dois elementos
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para fazer a partição do array (usada pelo QuickSort)
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Escolhendo o último elemento como pivot
    int i = (low - 1); // Índice do menor elemento

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) { // Se o elemento atual é menor que o pivot
            i++; // Incrementa o índice do menor elemento
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Função para implementar o algoritmo QuickSort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Função principal
int main() {
    LeitorArquivo leitor;
    inicializarLeitor(&leitor);

    // Ler o arquivo e popular a lista de números
    lerArquivo(&leitor, "DadosAPS/1k/Com Duplicidade/Aleatorio/dtaleat1kdup0.txt");

    // Exibir os dados antes da ordenação
    printf("Dados antes da ordenação:\n");
    exibirDados(leitor.numeros, leitor.tamanho);

    // Escolher o método de ordenação
    int escolha;
    printf("Escolha o método de ordenação:\n1 - Insertion Sort\n2 - QuickSort\n");
    scanf("%d", &escolha);

    // Ordenar os dados com base na escolha
    if (escolha == 1) {
        insertionSort(leitor.numeros, leitor.tamanho);
        printf("Dados após a ordenação (Insertion Sort):\n");
    } else if (escolha == 2) {
        quickSort(leitor.numeros, 0, leitor.tamanho - 1);
        printf("Dados após a ordenação (QuickSort):\n");
    } else {
        printf("Escolha inválida.\n");
        free(leitor.numeros);
        return 1;
    }

    // Exibir os dados após a ordenação
    exibirDados(leitor.numeros, leitor.tamanho);

    // Liberar a memória alocada
    free(leitor.numeros);

    return 0;
}
