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

// Redimensiona o vetor se o vetor ficar cheio
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

// Leitura do arquivo e armazenamento dos números no vetor
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

    fclose(file); // Fecha o arquivo
}

// Função para exibir os dados
void exibirDados(int *dados, int tamanho) {
    printf("Lista de Dados: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", dados[i]);
    }
    printf("\n");
}

// Função Insertion Sort
void InsertionSort(int* v, int tam) {
    int i, j, chave;
    int trocas = 0;
    for (j = 1; j < tam; j++) {
        chave = v[j];
        i = j - 1;
        while ((i >= 0) && (v[i] > chave)) {
            v[i + 1] = v[i];
            i--;
            trocas++;
        }
        v[i + 1] = chave;
    }
    printf("Quantidade de trocas no InsertionSort: %d\n", trocas);
}

// Função QuickSort corrigida
void QuickSort(int* v, int tam, int* trocas) {
    int j = tam, k;
    if (tam <= 1)
        return;

    int x = v[0];  // pivô
    int a = 1;
    int b = tam - 1;

    do {
        while ((a < tam) && (v[a] <= x))
            a++;
        while (v[b] > x)
            b--;

        if (a < b) {  // faz a troca
            int temp = v[a];
            v[a] = v[b];
            v[b] = temp;
            a++;
            b--;
            (*trocas)++;
        }
        
    } while (a <= b);

    // Troca o pivô para a posição correta
    v[0] = v[b];
    v[b] = x;
    (*trocas)++;

    // Ordena sub-vetores restantes
    QuickSort(v, b, trocas);
    QuickSort(&v[a], tam - a, trocas);
}

// Função BubbleSort corrigida
void BubbleSort(int* v, int tam, int* trocas) {
    int i;
    int trocou;
    *trocas = 0; // Inicializa o contador de trocas
    do {
        tam--;
        trocou = 0;
        for (i = 0; i < tam; i++) {
            if (v[i] > v[i + 1]) {
                int aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
                trocou = 1;
                (*trocas)++;
            }
        }
    } while (trocou);
    printf("Quantidade de trocas no BubbleSort: %d\n", *trocas);
}

// Função principal
int main() {
    LeitorArquivo leitor;
    inicializarLeitor(&leitor);

    // Ler o arquivo e popular a lista de números
    lerArquivo(&leitor, "DadosAPS/500/Com Duplicidade/Aleatorio/dtaleat500dup0.txt");

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

        // Cria uma cópia dos dados originais para cada método de ordenação
        int* copiaDados = (int*)malloc(leitor.tamanho * sizeof(int));
        memcpy(copiaDados, leitor.numeros, leitor.tamanho * sizeof(int));

        switch (escolha) {
            case 1:
                InsertionSort(copiaDados, leitor.tamanho);
                printf("Dados ordenados com Insertion Sort:\n");
                break;
            case 2: {
                int trocas = 0;
                QuickSort(copiaDados, leitor.tamanho, &trocas);
                printf("Quantidade de trocas no QuickSort: %d\n", trocas);
                printf("Dados ordenados com QuickSort:\n");
                break;
            }
            case 3: {
                int trocas = 0;
                BubbleSort(copiaDados, leitor.tamanho, &trocas);
                printf("Dados ordenados com Bubble Sort:\n");
                break;
            }
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Escolha inválida.\n");
        }

        if (escolha != 0) {
            exibirDados(copiaDados, leitor.tamanho);
        }

        // Libera a cópia dos dados
        free(copiaDados);
        
    } while (escolha != 0);

    // Libera a memória alocada
    free(leitor.numeros);

    return 0;
}
