# cdir <  listaIps.txt  > ipsCdirOtimizados.txt

## 📜 Descrição
`cdir` é um programa desenvolvido em C++ que processa uma lista de endereços IP, mescla intervalos de IPs e gera uma lista otimizada de CIDRs. Foi criado para melhorar a eficiência do processamento de listas de IPs e é especialmente útil para administradores de rede e profissionais de TI, ou pessoas como eu.

## 💻 Requisitos
- GCC (G++) 7.4 ou superior
- Make

## 🛠 Instruções de Build

1. Clone o repositório:
    ```sh
    git clone https://github.com/adalbertobrant/cdir.git
    cd cdir
    ```

2. Compile o programa usando o make:
    ```sh
    make
    ```

## 🚀 Uso

Após a compilação, você pode executar o programa passando uma lista de IPs  através de um arquivo de entrada e redirecionando a saída para um arquivo de saída.

### Exemplo de Uso

1. Crie um arquivo `listaIps.txt` com a lista de IPs em formato CIDR, um por linha:
    ```
    192.168.0.1
    192.168.1.4
    ```

2. Execute o programa:
    ```sh
    ./cdir < listaIps.txt > output.txt
    ```

3. O arquivo `output.txt` conterá a lista otimizada de CIDRs.

### 📝 Dica de Performance
Para melhorar a performance do programa, é recomendável garantir que a lista de IPs seja única, evitando entradas duplicadas. Isso ajudará a reduzir o tempo de processamento e melhorar a eficiência geral.

## 🧹 Limpeza

Para limpar os arquivos compilados, execute:
```sh
make clean
```
🤔 Motivação
O cdir foi desenvolvido em C++ devido ao meu PC ser mais antigo e ter limitações de hardware. A escolha do C++ permitiu um controle mais detalhado sobre o desempenho e a eficiência do programa.

A inspiração para este projeto veio do projeto do Programador Kris Feldmann que você pode visitar (aqui)(https://github.com/kfeldmann/cidrmerge)

🤝 Contribuições
Contribuições são muito bem-vindas! Se você tiver sugestões, correções ou melhorias, por favor, abra um issue ou envie um pull request. Sua ajuda é muito bem vinda!

Obrigado por usar o cdir! 🚀

📜 Licença 

Para utilização favor ler o arquivo license.txt e concordar com os termos de utilização.
Programa orginalmente desenvolvido por Kris Feldmann [cdirmerge](https://github.com/kfeldmann/cidrmerge)

Portabilidade para C++ 17 realizada por mim e por várias IAs.
