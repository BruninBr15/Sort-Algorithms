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

// Redimensiona o vetor se o Vetor ficar cheio
void redimensionar(LeitorArquivo *leitor) {
    int novaCapacidade = leitor->capacidade * 2;
    int *novoVetor = (int *)realloc(leitor->numeros, novaCapacidade * sizeof(int));
    if (novoVetor == NULL) {
        printf("Erro ao realocar memória.\n");
        exit(1);
    }
    leitor->numeros = novoVetor;
    leitor->capacidade = novaCapacidade;
}

//Leitura do arquivo e armazenamento dos números no vetor
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

    fclose(file); // Fecha o arquivo dentro do bloco if
}

// Função para exibir os dados
void exibirDados(int *dados, int tamanho) {
    printf("Lista de Dados: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", dados[i]);
    }
    printf("\n");
}

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

// Troca de elementos para o QuickSort
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Divisão do vetor para o QuickSort
int partição(int arr[], int low, int high) {
    int pivot = arr[high]; // Escolhendo o último elemento como pivô
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

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partição(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void bubbleSort(int arr[], int n) {
    int i, j, swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
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

    do {
        printf("Escolha o método de ordenação:\n");
        printf("1 - Insertion Sort\n");
        printf("2 - QuickSort\n");
        printf("3 - BubbleSort\n");
        printf("0 - Sair\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                insertionSort(leitor.numeros, leitor.tamanho);
                printf("Dados ordenados com Insertion Sort:\n");
                break;
            case 2:
                quickSort(leitor.numeros, 0, leitor.tamanho - 1);
                printf("Dados ordenados com QuickSort:\n");
                break;
            case 3:
                bubbleSort(leitor.numeros, leitor.tamanho);
                printf("Dados ordenados com Bubble Sort:\n");
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Escolha inválida.\n");
        }

        if (escolha != 0) {
            exibirDados(leitor.numeros, leitor.tamanho);
        }
    } while (escolha != 0);
        printf("Escolha inválida.\n");
        free(leitor.numeros);

    return 0;
}
