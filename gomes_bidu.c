#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <time.h>

// inicio funcionalidade 3
#define MAX_CLIENTES 100
typedef struct
{
    int codigo;
    char nome[100];
    char endereco[200];
    char telefone[15];
    int totalEstadias;
} Cliente;

void cadastrarCliente(Cliente clientes[], int *numClientes)
{
    if (*numClientes >= MAX_CLIENTES)
    {
        printf("Número máximo de clientes atingido.\n");
        return;
    }

    Cliente *cliente = &clientes[*numClientes];

    printf("Digite o codigo do cliente: ");
    scanf("%d", &cliente->codigo);
    getchar();

    printf("Digite o nome do cliente: ");
    fgets(cliente->nome, sizeof(cliente->nome), stdin);
    cliente->nome[strcspn(cliente->nome, "\n")] = '\0';

    printf("Digite o endereco do cliente: ");
    fgets(cliente->endereco, sizeof(cliente->endereco), stdin);
    cliente->endereco[strcspn(cliente->endereco, "\n")] = '\0'; // Remover o newline do final

    printf("Digite o telefone do cliente: ");
    fgets(cliente->telefone, sizeof(cliente->telefone), stdin);
    cliente->telefone[strcspn(cliente->telefone, "\n")] = '\0'; // Remover o newline do final

    (*numClientes)++;
}
// fim funcionalidade 3

// inicio funcionalidade 4
void exibirCliente(Cliente cliente)
{
    printf("\nDados do Cliente:\n");
    printf("Codigo: %d\n", cliente.codigo);
    printf("Nome: %s\n", cliente.nome);
    printf("Endereco: %s\n", cliente.endereco);
    printf("Telefone: %s\n", cliente.telefone);
}

void buscarClientePorCodigo(Cliente clientes[], int numClientes, int codigo)
{
    for (int i = 0; i < numClientes; i++)
    {
        if (clientes[i].codigo == codigo)
        {
            exibirCliente(clientes[i]);
            return;
        }
    }
    printf("Cliente com código %d não encontrado.\n", codigo);
}

void buscarClientePorNome(Cliente clientes[], int numClientes, char *nome)
{
    int found = 0;
    for (int i = 0; i < numClientes; i++)
    {
        if (strstr(clientes[i].nome, nome) != NULL)
        {
            exibirCliente(clientes[i]);
            found = 1;
        }
    }
    if (!found)
    {
        printf("Nenhum cliente com o nome %s encontrado.\n", nome);
    }
}
// fim funcionalidade 4

// inicio funcionalidade 5
typedef struct
{
    int numero;
    int quantidadeHospedes;
    float valorDiaria;
    int disponibilidade;
    int clienteId;
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

int converterDataParaDias(char *data)
{
    struct tm estruturaTempo = {0};
    sscanf(data, "%d/%d/%d", &estruturaTempo.tm_mday, &estruturaTempo.tm_mon, &estruturaTempo.tm_year);
    estruturaTempo.tm_mon--;
    estruturaTempo.tm_year -= 1900;
    return mktime(&estruturaTempo) / (60 * 60 * 24);
}

void cadastrarEstadia(Estadia **estadias, int *totalEstadias)
{
#define MAX_ESTADIAS 10

    *estadias = (Estadia *)realloc(*estadias, (*totalEstadias + 1) * sizeof(Estadia));
    printf("Digite o código da estadia: ");
    scanf("%d", &(*estadias)[*totalEstadias].codigoEstadia);
    printf("Digite a data de entrada (dd/mm/aaaa): ");
    scanf("%s", (*estadias)[*totalEstadias].dataEntrada);
    printf("Digite a data de saída (dd/mm/aaaa): ");
    scanf("%s", (*estadias)[*totalEstadias].dataSaida);

    int entrada = converterDataParaDias((*estadias)[*totalEstadias].dataEntrada);
    int saida = converterDataParaDias((*estadias)[*totalEstadias].dataSaida);
    (*estadias)[*totalEstadias].quantidadeDiarias = saida - entrada;

    printf("Digite o número do quarto: ");
    scanf("%d", &(*estadias)[*totalEstadias].numeroQuarto);

    printf("Digite o código do cliente: ");
    scanf("%d", &(*estadias)[*totalEstadias].codigoCliente);

    (*totalEstadias)++;
}
// fim funcionalidade 7

// inicio funcionalidade 8
void mostrarEstadiaPorCliente(Estadia *estadias, int totalEstadias, int codigoCliente)
{
    int encontrou = 0;
    for (int i = 0; i < totalEstadias; i++)
    {
        if (estadias[i].codigoCliente == codigoCliente)
        {
            printf("Código da estadia: %d\n", estadias[i].codigoEstadia);
            printf("Data de entrada: %s\n", estadias[i].dataEntrada);
            printf("Data de saída: %s\n", estadias[i].dataSaida);
            printf("Quantidade de diárias: %d\n", estadias[i].quantidadeDiarias);
            printf("Número do quarto: %d\n", estadias[i].numeroQuarto);
            encontrou = 1;
            break;
        }
    }
    if (!encontrou)
    {
        printf("Nenhuma estadia encontrada para o cliente com código %d\n", codigoCliente);
    }
}
// fim funcionalidade 8

// inicio main
int main()
{
    setlocale(LC_ALL, "Portuguese");

    Cliente clientes[MAX_CLIENTES];
    int numClientes = 0;
    int codigo;

    Quarto *listaQuartos = NULL;
    int totalQuartos = 0;
    Estadia *listaEstadias = NULL;
    Estadia estadias[5];
    int totalEstadias = 0;
    int opcao;

    do
    {
        system("cls");
        printf("\nMenu:\n");
        printf("1 - Cadastrar quarto\n");
        printf("2 - Buscar quarto\n");
        printf("3 - Cadastrar estadia\n");
        printf("4 - Cadastrar cliente\n");
        printf("5 - Buscar cliente por código\n");
        printf("6 - Buscar cliente por nome\n");
        printf("7 - Buscar estadia por cliente\n");
        printf("11 - Sair\n");
        printf("\nDigite a opção desejada: ");
        scanf("%d", &opcao);
        getchar();

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
        case 4:
            cadastrarCliente(clientes, &numClientes);
            break;
        case 5:
            printf("Digite o código do cliente: ");
            scanf("%d", &codigo);
            getchar();
            buscarClientePorCodigo(clientes, numClientes, codigo);
            break;
        case 6:
            printf("Digite o nome do cliente: ");
            char nome[50];
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;
            buscarClientePorNome(clientes, numClientes, nome);
            break;
        case 7:
            printf("Digite o código do cliente: ");
            int codigoCliente;
            scanf("%d", &codigoCliente);
            getchar();
            mostrarEstadiaPorCliente(estadias, totalEstadias, codigoCliente);
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