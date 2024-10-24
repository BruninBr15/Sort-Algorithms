import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class LeitorArquivo {
    private List<Integer> numeros = new ArrayList<>(); // Lista para armazenar os números

    // Método para ler o arquivo e preencher a lista de números
    public void lerArquivo(String caminhoDoArquivo) {
        try (BufferedReader br = new BufferedReader(new FileReader(caminhoDoArquivo))) {
            String linha;
            while ((linha = br.readLine()) != null) {
                try {
                    // Converte a linha em um número inteiro e adiciona na lista
                    int numero = Integer.parseInt(linha.trim());
                    numeros.add(numero);
                } catch (NumberFormatException e) {
                    System.out.println("Valor inválido encontrado e ignorado: " + linha);
                }
            }
        } catch (IOException e) {
            System.out.println("Ocorreu um erro ao tentar ler o arquivo.");
            e.printStackTrace();
        }
    }

    // Método getter para retornar a lista de números
    public List<Integer> getLista() {
        return numeros;
    }
}
