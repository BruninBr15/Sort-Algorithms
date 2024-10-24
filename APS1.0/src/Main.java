public class Main {
    public static void main(String[] args) {
        // Cria uma instância de LeitorArquivo
        LeitorArquivo leitor = new LeitorArquivo();

        // Chama o método lerArquivo para ler o arquivo e popular a lista de números
        leitor.lerArquivo("DadosAPS/1k/Com Duplicidade/Aleatorio/dtaleat1kdup0.txt");

        AreaDesmatada areaDesmatada = new AreaDesmatada(leitor);

        // Exibir os dados antes da ordenação
        System.out.println("Dados antes da ordenação:");
        areaDesmatada.exibirDados();

        // Ordenar os dados usando o InsertionSort
        InsertionSort.insertionSort(areaDesmatada.dados);

        // Exibir os dados após a ordenação
        System.out.println("Dados após a ordenação:");
        areaDesmatada.exibirDados();
    }
}
