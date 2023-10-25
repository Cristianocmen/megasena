#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SORTEIOS 5000
#define NUM_NUMEROS 6
#define NUM_BOLAS 60

void gerarSorteio(int sorteios[NUM_SORTEIOS][NUM_NUMEROS]);

int main() {
    srand(time(NULL));
    int sorteios[NUM_SORTEIOS][NUM_NUMEROS];
    gerarSorteio(sorteios);

    int frequenciaNumeros[NUM_BOLAS] = {0};

    // Contagem da frequência dos números
    for (int i = 0; i < NUM_SORTEIOS; i++) {
        for (int j = 0; j < NUM_NUMEROS; j++) {
            frequenciaNumeros[sorteios[i][j] - 1]++;
        }
    }

    // Exibindo estatísticas dos números
    printf("Estatísticas:\n");
    for (int i = 0; i < NUM_BOLAS; i++) {
        printf("Número %02d = %d vezes.\n", i + 1, frequenciaNumeros[i]);
    }

    // Inicializando contadores para estatísticas das duplas e números únicos
    int duplas[NUM_BOLAS][NUM_BOLAS] = {0};
    int numerosUnicos[NUM_BOLAS] = {0};

    // Contagem das duplas e números únicos
    for (int i = 0; i < NUM_SORTEIOS; i++) {
        for (int j = 0; j < NUM_NUMEROS; j++) {
            numerosUnicos[sorteios[i][j] - 1]++;
            for (int k = j + 1; k < NUM_NUMEROS; k++) {
                duplas[sorteios[i][j] - 1][sorteios[i][k] - 1]++;
                duplas[sorteios[i][k] - 1][sorteios[i][j] - 1]++;
            }
        }
    }

    // Exibindo as 15 duplas mais sorteadas
    printf("\nAs 15 duplas mais sorteadas:\n");
    for (int i = 0; i < NUM_BOLAS; i++) {
        for (int j = i + 1; j < NUM_BOLAS; j++) {
            if (duplas[i][j] > 0) {
                printf("Números %02d e %02d = %d vezes.\n", i + 1, j + 1, duplas[i][j]);
            }
        }
    }

    // Exibindo os 15 números únicos mais sorteados
    printf("\nOs 15 números únicos mais sorteados:\n");
    for (int i = 0; i < NUM_BOLAS; i++) {
        printf("Número %02d = %d vezes.\n", i + 1, numerosUnicos[i]);
    }

    // Simulação de jogadas para 3 usuários
    for (int usuario = 0; usuario < 3; usuario++) {
        char nome[100];
        char cpf[12];
        int numerosApostados[NUM_NUMEROS];

        printf("\nUsuário %d, por favor, insira seu nome: ", usuario + 1);
        scanf("%s", nome);
        printf("Usuário %d, insira seu CPF: ", usuario + 1);
        scanf("%s", cpf);

        printf("Usuário %d, insira 6 números únicos (01 a 60): ", usuario + 1);
        for (int i = 0; i < NUM_NUMEROS; i++) {
            scanf("%d", &numerosApostados[i]);
        }

        int maxAcertos = 0;
        int sorteioComMaisAcertos = 0;
        for (int i = 0; i < NUM_SORTEIOS; i++) {
            int acertos = 0;
            for (int j = 0; j < NUM_NUMEROS; j++) {
                for (int k = 0; k < NUM_NUMEROS; k++) {
                    if (numerosApostados[j] == sorteios[i][k]) {
                        acertos++;
                        break;
                    }
                }
            }
            if (acertos > maxAcertos) {
                maxAcertos = acertos;
                sorteioComMaisAcertos = i + 1;
            }
        }

        printf("\nParabéns, %s! Você acertou %d números! No sorteio %d.\n", nome, maxAcertos, sorteioComMaisAcertos);
    }

    return 0;
}

void gerarSorteio(int sorteios[NUM_SORTEIOS][NUM_NUMEROS]) {
    for (int i = 0; i < NUM_SORTEIOS; i++) {
        int numerosSorteados[NUM_BOLAS];
        for (int j = 0; j < NUM_BOLAS; j++) {
            numerosSorteados[j] = j + 1;
        }

        for (int j = 0; j < NUM_NUMEROS; j++) {
            int indice = rand() % (NUM_BOLAS - j);
            sorteios[i][j] = numerosSorteados[indice];
            numerosSorteados[indice] = numerosSorteados[NUM_BOLAS - j - 1];
        }
    }
}