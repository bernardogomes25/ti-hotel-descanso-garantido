#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int codigo;
    char nome[100];
    char endereco[200];
    char telefone[15];
    int totalEstadias;
} Cliente;


int calcularPontosFidelidade(int diarias) {
    return diarias * 10;
}

int main() {
    int numDiarias;
    printf("Digite o número de diárias do cliente: ");
    scanf("%d", &numDiarias);

    int pontos = calcularPontosFidelidade(numDiarias);
    printf("Pontos de fidelidade: %d\n", pontos);

    return 0;
}
