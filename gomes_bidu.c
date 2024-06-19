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

void cadastrarCliente(FILE *file)
{
    Cliente cliente;
    Cliente clienteExistente;

    printf("\nDigite o codigo do cliente: ");
    scanf("%d", &cliente.codigo);
    getchar();
    rewind(file);
    while (fread(&clienteExistente, sizeof(Cliente), 1, file) == 1)
    {
        if (clienteExistente.codigo == cliente.codigo)
        {
            printf("Erro: Já existe um cliente com o código %d.\n", cliente.codigo);
            return;
        }
    }
    printf("Digite o nome do cliente: ");
    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = 0;
    printf("Digite o endereco do cliente: ");
    fgets(cliente.endereco, sizeof(cliente.endereco), stdin);
    cliente.endereco[strcspn(cliente.endereco, "\n")] = 0;
    printf("Digite o telefone do cliente: ");
    scanf("%s", cliente.telefone);
    getchar();
    cliente.totalEstadias = 0;

    fseek(file, 0, SEEK_END);
    fwrite(&cliente, sizeof(Cliente), 1, file);
}
// fim funcionalidade 3

// inicio funcionalidade 4
void buscarClientePorCodigo(FILE *file, int codigo)
{
    Cliente cliente;
    int found = 0;

    if (file == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }

    rewind(file);
    while (fread(&cliente, sizeof(Cliente), 1, file) == 1)
    {
        if (cliente.codigo == codigo)
        {
            printf("\nCodigo: %d\n", cliente.codigo);
            printf("Nome: %s\n", cliente.nome);
            printf("Endereco: %s\n", cliente.endereco);
            printf("Telefone: %s\n", cliente.telefone);
            printf("Total de estadias: %d\n", cliente.totalEstadias);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nCliente com o codigo %d nao foi encontrado.\n", codigo);
    }
}

void buscarClientePorNome(FILE *file, char *nome)
{
    Cliente cliente;
    int found = 0;

    if (file == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }

    rewind(file);
    while (fread(&cliente, sizeof(Cliente), 1, file) == 1)
    {
        if (strstr(cliente.nome, nome) != NULL)
        {
            printf("\nCodigo: %d\n", cliente.codigo);
            printf("Nome: %s\n", cliente.nome);
            printf("Endereco: %s\n", cliente.endereco);
            printf("Telefone: %s\n", cliente.telefone);
            printf("Total de estadias: %d\n", cliente.totalEstadias);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\nCliente com o nome %s nao foi encontrado.\n", nome);
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

void cadastrarQuarto(FILE *file)
{
    Quarto quarto;

    printf("\nDigite o número do quarto: ");
    scanf("%d", &quarto.numero);
    getchar();
    printf("Digite a quantidade de hóspedes: ");
    scanf("%d", &quarto.quantidadeHospedes);
    getchar();
    printf("Digite o valor da diária: ");
    scanf("%f", &quarto.valorDiaria);
    getchar();
    do
    {
        printf("Digite a disponibilidade do quarto (1 para ocupado, 0 para desocupado): ");
        scanf("%d", &quarto.disponibilidade);
        getchar();
    } while (quarto.disponibilidade != 0 && quarto.disponibilidade != 1);
    quarto.clienteId = -1;

    fseek(file, 0, SEEK_END);
    fwrite(&quarto, sizeof(Quarto), 1, file);
}
// fim funcionalidade 5

// inicio funcionalidade 6
void buscarQuarto(FILE *file, int numeroQuarto)
{
    Quarto quarto;

    rewind(file);
    while (fread(&quarto, sizeof(Quarto), 1, file) == 1)
    {
        if (quarto.numero == numeroQuarto)
        {
            printf("\nNúmero do quarto: %d\n", quarto.numero);
            printf("Quantidade de hóspedes: %d\n", quarto.quantidadeHospedes);
            printf("Valor da diária: %.2f\n", quarto.valorDiaria);
            printf("Disponibilidade: %s\n", quarto.disponibilidade ? "Ocupado" : "Desocupado");
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

#include <time.h>

int calcularDiferencaDias(char *dataEntrada, char *dataSaida)
{
    struct tm tmEntrada, tmSaida;
    time_t tEntrada, tSaida;

    sscanf(dataEntrada, "%d/%d/%d", &tmEntrada.tm_mday, &tmEntrada.tm_mon, &tmEntrada.tm_year);
    sscanf(dataSaida, "%d/%d/%d", &tmSaida.tm_mday, &tmSaida.tm_mon, &tmSaida.tm_year);

    tmEntrada.tm_mon -= 1;
    tmEntrada.tm_year -= 1900;
    tmEntrada.tm_hour = 0;
    tmEntrada.tm_min = 0;
    tmEntrada.tm_sec = 0;
    tmEntrada.tm_isdst = -1;

    tmSaida.tm_mon -= 1;
    tmSaida.tm_year -= 1900;
    tmSaida.tm_hour = 0;
    tmSaida.tm_min = 0;
    tmSaida.tm_sec = 0;
    tmSaida.tm_isdst = -1;

    tEntrada = mktime(&tmEntrada);
    tSaida = mktime(&tmSaida);

    int diferencaDias = (tSaida - tEntrada) / (60 * 60 * 24);

    return diferencaDias;
}

void cadastrarEstadia(FILE *file)
{
    Estadia estadia;

    printf("\nDigite o código da estadia: ");
    scanf("%d", &estadia.codigoEstadia);
    printf("Digite a data de entrada (dd/mm/aaaa): ");
    scanf("%s", estadia.dataEntrada);
    printf("Digite a data de saída (dd/mm/aaaa): ");
    scanf("%s", estadia.dataSaida);
    estadia.quantidadeDiarias = calcularDiferencaDias(estadia.dataEntrada, estadia.dataSaida);
    printf("Digite o código do cliente: ");
    scanf("%d", &estadia.codigoCliente);
    printf("Digite o número do quarto: ");
    scanf("%d", &estadia.numeroQuarto);

    fseek(file, 0, SEEK_END);
    fwrite(&estadia, sizeof(Estadia), 1, file);
}
// fim funcionalidade 7

// inicio funcionalidade 8
void mostrarEstadiaPorCliente(FILE *file, int codigoCliente)
{
    Estadia estadia;
    int encontrou = 0;

    rewind(file);
    while (fread(&estadia, sizeof(Estadia), 1, file) == 1)
    {
        if (estadia.codigoCliente == codigoCliente)
        {
            printf("\nCódigo da estadia: %d\n", estadia.codigoEstadia);
            printf("Data de entrada: %s\n", estadia.dataEntrada);
            printf("Data de saída: %s\n", estadia.dataSaida);
            printf("Quantidade de diárias: %d\n", estadia.quantidadeDiarias);
            printf("Número do quarto: %d\n", estadia.numeroQuarto);
            encontrou = 1;
            break;
        }
    }
    if (!encontrou)
    {
        printf("\nNenhuma estadia encontrada para o cliente com código %d\n", codigoCliente);
    }
}
// fim funcionalidade 8

// inicio main
int main()
{
    int opcao;
    int numeroQuarto;
    int codigoCliente;
    int codigoClienteBuscar;
    char nomeCliente[50];
    FILE *fileQuartos;
    FILE *fileEstadias;
    FILE *fileClientes;

    if ((fileQuartos = fopen("quartos.dat", "r+b")) == NULL)
    {
        printf("\nArquivo quartos.dat não existia ... criando arquivo!\n");
        if ((fileQuartos = fopen("quartos.dat", "w+b")) == NULL)
        {
            printf("\nErro na criação do arquivo quartos.dat!!\n");
            exit(1);
        }
    }

    if ((fileEstadias = fopen("estadias.dat", "r+b")) == NULL)
    {
        printf("\nArquivo estadias.dat não existia ... criando arquivo!\n");
        if ((fileEstadias = fopen("estadias.dat", "w+b")) == NULL)
        {
            printf("\nErro na criação do arquivo estadias.dat!!\n");
            exit(1);
        }
    }

    if ((fileClientes = fopen("clientes.dat", "r+b")) == NULL)
    {
        printf("\nArquivo clientes.dat não existia ... criando arquivo!\n");
        if ((fileClientes = fopen("clientes.dat", "w+b")) == NULL)
        {
            printf("\nErro na criação do arquivo clientes.dat!!\n");
            exit(1);
        }
    }

    do
    {
        system("cls");
        printf("\nMenu:\n");
        printf("0. Limpar todos os dados salvos\n");
        printf("3. Cadastrar cliente\n");
        printf("4. Buscar cliente por codigo\n");
        printf("5. Buscar cliente por nome\n");
        printf("6. Cadastrar quarto\n");
        printf("7. Buscar quarto\n");
        printf("8. Cadastrar estadia\n");
        printf("9. Buscar estadia por cliente\n");
        printf("12. Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 0:
            printf("\nApagando todos os dados...\n");

            if ((fileQuartos = fopen("quartos.dat", "w+b")) == NULL)
            {
                printf("Erro ao apagar os dados dos quartos.\n");
            }

            if ((fileEstadias = fopen("estadias.dat", "w+b")) == NULL)
            {
                printf("Erro ao apagar os dados das estadias.\n");
            }

            if ((fileClientes = fopen("clientes.dat", "w+b")) == NULL)
            {
                printf("Erro ao apagar os dados dos clientes.\n");
            }

            printf("Todos os dados foram apagados.\n");
            break;
        case 3:
            cadastrarCliente(fileClientes);
            break;
        case 4:
            printf("\nDigite o código do cliente que deseja buscar: ");
            scanf("%d", &codigoClienteBuscar);
            buscarClientePorCodigo(fileClientes, codigoClienteBuscar);
            break;
        case 5:
            printf("\nDigite o nome do cliente que deseja buscar: ");
            scanf("%s", nomeCliente);
            buscarClientePorNome(fileClientes, nomeCliente);
            break;
        case 6:
            cadastrarQuarto(fileQuartos);
            break;
        case 7:
            printf("\nDigite o número do quarto que deseja buscar: ");
            scanf("%d", &numeroQuarto);
            buscarQuarto(fileQuartos, numeroQuarto);
            break;
        case 8:
            cadastrarEstadia(fileEstadias);
            break;
        case 9:
            printf("\nDigite o código do cliente que deseja buscar estadias: ");
            scanf("%d", &codigoCliente);
            mostrarEstadiaPorCliente(fileEstadias, codigoCliente);
            break;
        case 12:
            printf("\nSaindo...\n");
            break;
        default:
            printf("\nOpção inválida.\n");
        }
        printf("\nPressione qualquer tecla para prosseguir...\n");
        getch();
    } while (opcao != 12);

    fclose(fileQuartos);
    fclose(fileEstadias);
    fclose(fileClientes);

    return 0;
}
// fim main
