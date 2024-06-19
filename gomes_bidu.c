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

    printf("Digite o codigo do cliente: ");
    scanf("%d", &cliente.codigo);
    printf("Digite o nome do cliente: ");
    scanf("%s", cliente.nome);
    printf("Digite o endereco do cliente: ");
    scanf("%s", cliente.endereco);
    printf("Digite o telefone do cliente: ");
    scanf("%s", cliente.telefone);
    cliente.totalEstadias = 0;

    fseek(file, 0, SEEK_END);
    fwrite(&cliente, sizeof(Cliente), 1, file);
}
// fim funcionalidade 3

// inicio funcionalidade 4
 void buscarClientePorCodigo(FILE *file, int codigo)
{
    Cliente cliente;

    rewind(file);
    while (fread(&cliente, sizeof(Cliente), 1, file) == 1)
    {
        if (cliente.codigo == codigo)
        {
            printf("Codigo: %d\n", cliente.codigo);
            printf("Nome: %s\n", cliente.nome);
            printf("Endereco: %s\n", cliente.endereco);
            printf("Telefone: %s\n", cliente.telefone);
            printf("Total de estadias: %d\n", cliente.totalEstadias);
            break;
        }
    }
}

void buscarClientePorNome(FILE *file, char *nome)
{
    Cliente cliente;
    int found = 0;

    rewind(file);
    while (fread(&cliente, sizeof(Cliente), 1, file) == 1)
    {
        if (strstr(cliente.nome, nome) != NULL)
        {
            printf("Codigo: %d\n", cliente.codigo);
            printf("Nome: %s\n", cliente.nome);
            printf("Endereco: %s\n", cliente.endereco);
            printf("Telefone: %s\n", cliente.telefone);
            printf("Total de estadias: %d\n", cliente.totalEstadias);
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

void cadastrarQuarto(FILE *file)
{
    Quarto quarto;

    printf("Digite o número do quarto: ");
    scanf("%d", &quarto.numero);
    printf("Digite a quantidade de hóspedes: ");
    scanf("%d", &quarto.quantidadeHospedes);
    printf("Digite o valor da diária: ");
    scanf("%f", &quarto.valorDiaria);
    printf("Digite a disponibilidade do quarto (1 para ocupado, 0 para desocupado): ");
    scanf("%d", &quarto.disponibilidade);
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

int converterDataParaDias(char *data)
{
    struct tm estruturaTempo = {0};
    if (sscanf(data, "%d/%d/%d", &estruturaTempo.tm_mday, &estruturaTempo.tm_mon, &estruturaTempo.tm_year) != 3)
    {
        printf("Erro ao ler a data. Certifique-se de que ela está no formato dd/mm/aaaa.\n");
        return -1;
    }
    estruturaTempo.tm_mon--;
    estruturaTempo.tm_year -= 1900;
    time_t tempo = mktime(&estruturaTempo);
    if (tempo == (time_t)-1)
    {
        printf("Erro ao converter a data para dias.\n");
        return -1;
    }
    return tempo / (60 * 60 * 24);
}

#include <time.h>
#include <stdio.h>

int calcularDiferencaDias(char *dataInicio, char *dataFim) {
    struct tm inicio = {0}, fim = {0};
    double diferenca;

    sscanf(dataInicio, "%d-%d-%d", &inicio.tm_mday, &inicio.tm_mon, &inicio.tm_year);
    inicio.tm_mon -= 1;  
    inicio.tm_year -= 1900; 

    sscanf(dataFim, "%d-%d-%d", &fim.tm_mday, &fim.tm_mon, &fim.tm_year);
    fim.tm_mon -= 1; 
    fim.tm_year -= 1900;

    diferenca = difftime(mktime(&fim), mktime(&inicio)) / (60 * 60 * 24);

    return (int)diferenca;
}

void cadastrarEstadia(FILE *file)
{
    Estadia estadia;

    printf("Digite o código da estadia: ");
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
            printf("Código da estadia: %d\n", estadia.codigoEstadia);
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
    FILE *fileQuartos = fopen("quartos.dat", "wb");
    FILE *fileEstadias = fopen("estadias.dat", "wb");
    FILE *fileClientes = fopen("clientes.dat", "wb");

    if (fileQuartos == NULL || fileEstadias == NULL || fileClientes == NULL)
    {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    do
    {
        printf("\nMenu:\n");
        printf("3. Cadastrar cliente\n");
        printf("4. Buscar cliente por codigo\n");
        printf("5. Buscar cliente por nome\n");
        printf("6. Cadastrar quarto\n");
        printf("7. Buscar quarto\n");
        printf("8. Cadastrar estadia\n");
        printf("9. Buscar estadia por cliente\n");
        printf("12. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 3:
            cadastrarCliente(fileClientes);
            break;
        case 4:
            printf("Digite o código do cliente que deseja buscar: ");
            scanf("%d", &codigoClienteBuscar);
            buscarClientePorCodigo(fileClientes, codigoClienteBuscar);
            break;
        case 5:
            printf("Digite o nome do cliente que deseja buscar: ");
            scanf("%s", nomeCliente);
            buscarClientePorNome(fileClientes, nomeCliente);
            break;
        case 6:
            cadastrarQuarto(fileQuartos);
            break;
        case 7:
            printf("Digite o número do quarto que deseja buscar: ");
            scanf("%d", &numeroQuarto);
            buscarQuarto(fileQuartos, numeroQuarto);
            break;
        case 8:
            cadastrarEstadia(fileEstadias);
            break;
        case 9:
            printf("Digite o código do cliente que deseja buscar estadias: ");
            scanf("%d", &codigoCliente);
            mostrarEstadiaPorCliente(fileEstadias, codigoCliente);
            break;
        case 12:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida.\n");
        }
    } while (opcao != 12);

    fclose(fileQuartos);
    fclose(fileEstadias);
    fclose(fileClientes);

    return 0;
}
// fim main