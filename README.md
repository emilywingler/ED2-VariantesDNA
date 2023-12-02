# ED2- Trabalho - Encontrar Variantes de DNA
## Objetivo do trabalho
Escreva um programa que recebe dois arquivos:

(1) BaseDadosDNA.txt: contém as sequências de DNA coletadas dos animais,

(2) PadroesVirus.txt: contém as sequências de DNA dos variantes do vírus.

Para cada padrão de DNA do vírus, o programa deve imprimir o número de ocorrências
do mesmo na sequência do DNA do animal seguido de uma lista com as posições onde o
primeiro caractere do padrão (do vírus) ocorre na sequência de DNA do animal.

## Algoritmo Usado
Correspondência de Strings - Algoritmo KMP

## Padrão de saída
Para cada padrão contido no arquivo PadroesVirus.txt, imprima (no terminal) uma linha
com a descrição do padrão e, nas linhas seguintes, imprima a descrição da sequência de
DNA (do arquivo BaseDadosDNA.txt) entre colchetes seguido do número de ocorrências e
das posições onde o padrão ocorre na sequência de DNA (uma linha para cada sequência de
DNA). Veja o exemplo a seguir.

    variante B12.1
    [L034233.4 lobo guara] no. de ocorrencias: 2 posicoes: 47 128

    variante C4.3
    [O989487.1 onca pintada] no. de ocorrencias: 3 posicoes: 47 113 215
    [L034233.4 lobo guara] no. de ocorrencias: 1 posicoes: 44

### Formato de Entrega
    ED2_Grupo <4>_[Emily][Gabrielly][Guilherme][Samuel].zip