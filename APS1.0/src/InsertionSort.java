// Classe para armazenar dados de uma área desmatada

import java.util.List;

class AreaDesmatada {
    List<Integer> dados;

    // Construtor
    public AreaDesmatada(LeitorArquivo arquivo) {
        this.dados = arquivo.getLista();
        ;
    }

    // Método para exibir as informações de uma área desmatada
    public void exibirDados() {
        System.out.println("Lista de Dados: " + dados);
    }
}

public class InsertionSort {

    // Método para ordenar os dados dentro de cada AreaDesmatada usando insertion
    // sort
    public static void insertionSort(List<Integer> dados) {
        int n = dados.size();

        // Loop pelo conjunto de dados começando do segundo item
        for (int i = 1; i < n; ++i) {
            int chave = dados.get(i);
            int j = i - 1;

            // Mover elementos que são maiores que a chave para uma posição à frente
            while (j >= 0 && dados.get(j) > chave) {
                dados.set(j + 1, dados.get(j)); // Desloca o elemento para frente
                j = j - 1;
            }
            dados.set(j + 1, chave); // Insere a chave na posição correta
        }
    }
}