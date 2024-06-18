#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <time.h>

// inicio funcionalidade 5
typedef struct
{
    int numero;
    int quantidadeHospedes;
    float valorDiaria;
    int disponibilidade;
} Quarto;

void cadastrarQuarto(Quarto **quartos, int *totalQuartos)
{
    *quartos = (Quarto *)realloc(*quartos, (*totalQuartos + 1) * sizeof(Quarto));
    if (*quartos == NULL)
    {
        printf("Erro ao alocar memória.\n");
        return;
    }

    printf("Digite o número do quarto: ");
    scanf("%d", &(*quartos)[*totalQuartos].numero);
    printf("Digite a quantidade de hóspedes: ");
    scanf("%d", &(*quartos)[*totalQuartos].quantidadeHospedes);
    printf("Digite o valor da diária: ");
    scanf("%f", &(*quartos)[*totalQuartos].valorDiaria);
    printf("Digite a disponibilidade do quarto (1 para ocupado, 0 para desocupado): ");
    scanf("%d", &(*quartos)[*totalQuartos].disponibilidade);

    (*totalQuartos)++;
}
// fim funcionalidade 5

// inicio funcionalidade 6
void buscarQuarto(Quarto *quartos, int totalQuartos, int numeroQuarto)
{
    for (int i = 0; i < totalQuartos; i++)
    {
        if (quartos[i].numero == numeroQuarto)
        {
            printf("\nNúmero do quarto: %d\n", quartos[i].numero);
            printf("Quantidade de hóspedes: %d\n", quartos[i].quantidadeHospedes);
            printf("Valor da diária: %.2f\n", quartos[i].valorDiaria);
            printf("Disponibilidade: %s\n", quartos[i].disponibilidade ? "Ocupado" : "Desocupado");
            return;
        }
    }
    printf("\nQuarto não encontrado.\n");
}
// fim funcionalidade 6

// inicio funcionalidade 7
typedef struct
{
    int codigoEstadia;
    char dataEntrada[11];
    char dataSaida[11];
    int quantidadeDiarias;
    int codigoCliente;
    int numeroQuarto;
} Estadia;

int converterDataParaDias(char *data) {
    struct tm estruturaTempo = {0};
    sscanf(data, "%d/%d/%d", &estruturaTempo.tm_mday, &estruturaTempo.tm_mon, &estruturaTempo.tm_year);
    estruturaTempo.tm_mon--; // tm_mon é baseado em 0
    estruturaTempo.tm_year -= 1900; // tm_year é anos desde 1900
    return mktime(&estruturaTempo) / (60 * 60 * 24); // converter para dias
}

void cadastrarEstadia(Estadia **estadias, int *totalEstadias) {
    *estadias = (Estadia *) realloc(*estadias, (*totalEstadias + 1) * sizeof(Estadia));
    printf("Digite o código da estadia: ");
    scanf("%d", &(*estadias)[*totalEstadias].codigoEstadia);
    printf("Digite a data de entrada (dd/mm/aaaa): ");
    scanf("%s", (*estadias)[*totalEstadias].dataEntrada);
    printf("Digite a data de saída (dd/mm/aaaa): ");
    scanf("%s", (*estadias)[*totalEstadias].dataSaida);

    int entrada = converterDataParaDias((*estadias)[*totalEstadias].dataEntrada);
    int saida = converterDataParaDias((*estadias)[*totalEstadias].dataSaida);
    (*estadias)[*totalEstadias].quantidadeDiarias = saida - entrada;

    printf("Digite o código do cliente: ");
    scanf("%d", &(*estadias)[*totalEstadias].codigoCliente);
    printf("Digite o número do quarto: ");
    scanf("%d", &(*estadias)[*totalEstadias].numeroQuarto);
    (*totalEstadias)++;
}
//fim funcionalidade 7

//inicio funcionalidade 8

//fim funcionalidade 8

// inicio main
int main()
{
    setlocale(LC_ALL, "Portuguese");

    Quarto *listaQuartos = NULL;
    int totalQuartos = 0;
    Estadia *listaEstadias = NULL;
    int totalEstadias = 0;
    int opcao;

    do
    {
        printf("\nMenu:\n");
        printf("1 - Cadastrar quarto\n");
        printf("2 - Buscar quarto\n");
        printf("3 - Cadastrar estadia\n");
        printf("11 - Sair\n");
        printf("\nDigite a opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrarQuarto(&listaQuartos, &totalQuartos);
            break;
        case 2:
            printf("\nDigite o número do quarto que deseja buscar: ");
            int numeroQuarto;
            scanf("%d", &numeroQuarto);
            buscarQuarto(listaQuartos, totalQuartos, numeroQuarto);
            break;
        case 3:
            cadastrarEstadia(&listaEstadias, &totalEstadias);
            break;
        case 11:
            printf("\nSaindo...\n");
            break;
        default:
            printf("\nOpção inválida.\n");
        }
        if (opcao != 11)
        {
            printf("\nPressione qualquer tecla para prosseguir.\n");
            getch();
        }
    } while (opcao != 11);

    free(listaQuartos);
    free(listaEstadias);

    return 0;
}
// fim main