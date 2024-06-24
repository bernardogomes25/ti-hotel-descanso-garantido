#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>

// inicio funcionalidade 1
typedef struct
{
    int codigo;
    char nome[100];
    char telefone[15];
    char cargo[50];
    float salario;
} Funcionario;

void cadastrarFuncionario(FILE *file)
{
    Funcionario funcionario;
    Funcionario funcionarioExistente;

    printf("\nDigite o codigo do funcionario: ");
    scanf("%d", &funcionario.codigo);
    getchar();
    rewind(file);
    while (fread(&funcionarioExistente, sizeof(Funcionario), 1, file) == 1)
    {
        if (funcionarioExistente.codigo == funcionario.codigo)
        {
            printf("Erro: Já existe um funcionario com o código %d.\n", funcionario.codigo);
            return;
        }
    }
    printf("Digite o nome do funcionario: ");
    fgets(funcionario.nome, sizeof(funcionario.nome), stdin);
    funcionario.nome[strcspn(funcionario.nome, "\n")] = 0;
    printf("Digite o telefone do funcionario: ");
    scanf("%s", funcionario.telefone);
    getchar();
    printf("Digite o cargo do funcionario: ");
    fgets(funcionario.cargo, sizeof(funcionario.cargo), stdin);
    funcionario.cargo[strcspn(funcionario.cargo, "\n")] = 0;
    printf("Digite o salario do funcionario: ");
    scanf("%f", &funcionario.salario);
    getchar();

    fseek(file, 0, SEEK_END);
    fwrite(&funcionario, sizeof(Funcionario), 1, file);
}
// fim funcionalidade 1

// inicio funcionalidade 2
void buscarFuncionarioPorCodigo(FILE *file, int codigo)
{
    Funcionario funcionario;
    int found = 0;

    if (file == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }

    rewind(file);
    while (fread(&funcionario, sizeof(Funcionario), 1, file) == 1)
    {
        if (funcionario.codigo == codigo)
        {
            printf("\nCodigo: %d\n", funcionario.codigo);
            printf("Nome: %s\n", funcionario.nome);
            printf("Telefone: %s\n", funcionario.telefone);
            printf("Cargo: %s\n", funcionario.cargo);
            printf("Salario: %.2f\n", funcionario.salario);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nFuncionario com o codigo %d nao foi encontrado.\n", codigo);
    }
}

void buscarFuncionarioPorNome(FILE *file, char *nome)
{
    Funcionario funcionario;
    int found = 0;

    if (file == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }

    rewind(file);
    while (fread(&funcionario, sizeof(Funcionario), 1, file) == 1)
    {
        if (strstr(funcionario.nome, nome) != NULL)
        {
            printf("\nCodigo: %d\n", funcionario.codigo);
            printf("Nome: %s\n", funcionario.nome);
            printf("Telefone: %s\n", funcionario.telefone);
            printf("Cargo: %s\n", funcionario.cargo);
            printf("Salario: %.2f\n", funcionario.salario);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\nFuncionario com o nome %s nao foi encontrado.\n", nome);
    }
}
// fim funcionalidade 2

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

    quarto.disponibilidade = 0;
    quarto.clienteId = -1;

    fseek(file, 0, SEEK_END);
    fwrite(&quarto, sizeof(Quarto), 1, file);
    printf("Quarto cadastrado com sucesso.\n");
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
            printf("Disponibilidade: %s\n", quarto.disponibilidade == 1 ? "Ocupado" : "Desocupado");
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

#define bool _Bool

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

bool clienteExiste(FILE *fileClientes, int codigoCliente)
{
    Cliente cliente;

    rewind(fileClientes);
    while (fread(&cliente, sizeof(Cliente), 1, fileClientes) == 1)
    {
        if (cliente.codigo == codigoCliente)
        {
            return true;
        }
    }

    return false;
}

bool quartoExiste(FILE *fileQuartos, int numeroQuarto)
{
    Quarto quarto;

    rewind(fileQuartos);
    while (fread(&quarto, sizeof(Quarto), 1, fileQuartos) == 1)
    {
        if (quarto.numero == numeroQuarto)
        {
            return true;
        }
    }

    return false;
}

void cadastrarEstadia(FILE *fileClientes, FILE *fileQuartos, FILE *fileEstadias)
{
    Estadia estadia;
    Quarto quarto;

    printf("\nDigite o código da estadia: ");
    scanf("%d", &estadia.codigoEstadia);
    printf("Digite a data de entrada (dd/mm/aaaa): ");
    scanf("%s", estadia.dataEntrada);
    printf("Digite a data de saída (dd/mm/aaaa): ");
    scanf("%s", estadia.dataSaida);
    estadia.quantidadeDiarias = calcularDiferencaDias(estadia.dataEntrada, estadia.dataSaida);
    printf("Digite o código do cliente: ");
    scanf("%d", &estadia.codigoCliente);

    if (!clienteExiste(fileClientes, estadia.codigoCliente))
    {
        printf("Erro: Cliente com o código %d não existe.\n", estadia.codigoCliente);
        return;
    }

    printf("Digite o número do quarto: ");
    scanf("%d", &estadia.numeroQuarto);

    if (!quartoExiste(fileQuartos, estadia.numeroQuarto))
    {
        printf("Erro: Quarto número %d não existe.\n", estadia.numeroQuarto);
        return;
    }

    if (quarto.disponibilidade == 1)
    {
        printf("Erro: Quarto número %d está ocupado.\n", estadia.numeroQuarto);
        return;
    }

    quarto.disponibilidade = 1;

    fseek(fileEstadias, 0, SEEK_END);
    fwrite(&estadia, sizeof(Estadia), 1, fileEstadias);
    printf("Estadia cadastrada com sucesso.\n");
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

// inicio funcionalidade 9
void darBaixaEstadia(FILE *fileEstadias, FILE *fileQuartos, int codigoEstadia)
{
    Estadia estadia;
    Quarto quarto;
    int foundEstadia = 0;
    int foundQuarto = 0;
    FILE *tempFileEstadias;

    if ((tempFileEstadias = fopen("tempEstadias.dat", "w+b")) == NULL)
    {
        printf("\nErro ao criar arquivo temporário.\n");
        return;
    }

    rewind(fileEstadias);
    while (fread(&estadia, sizeof(Estadia), 1, fileEstadias) == 1)
    {
        if (estadia.codigoEstadia == codigoEstadia)
        {
            foundEstadia = 1;
            rewind(fileQuartos);
            while (fread(&quarto, sizeof(Quarto), 1, fileQuartos) == 1)
            {
                if (quarto.numero == estadia.numeroQuarto)
                {
                    foundQuarto = 1;
                    float total = quarto.valorDiaria * estadia.quantidadeDiarias;
                    printf("\nDetalhes da Estadia:\n");
                    printf("Código da estadia: %d\n", estadia.codigoEstadia);
                    printf("Data de entrada: %s\n", estadia.dataEntrada);
                    printf("Data de saída: %s\n", estadia.dataSaida);
                    printf("Quantidade de diárias: %d\n", estadia.quantidadeDiarias);
                    printf("Número do quarto: %d\n", estadia.numeroQuarto);
                    printf("Valor total: %.2f\n", total);
                    printf("Confirmar pagamento? (1 para sim, 0 para não): ");
                    int confirmacao;
                    scanf("%d", &confirmacao);

                    if (confirmacao == 1)
                    {
                        printf("\nPagamento confirmado. Estadia finalizada.\n");
                        quarto.disponibilidade = 0;
                        fseek(fileQuartos, -sizeof(Quarto), SEEK_CUR);
                        fwrite(&quarto, sizeof(Quarto), 1, fileQuartos);
                    }
                    else
                    {
                        printf("\nPagamento não confirmado. Estadia não finalizada.\n");
                        fwrite(&estadia, sizeof(Estadia), 1, tempFileEstadias);
                    }
                    break;
                }
            }
        }
        else
        {
            fwrite(&estadia, sizeof(Estadia), 1, tempFileEstadias);
        }
    }

    if (!foundEstadia)
    {
        printf("\nEstadia com o código %d não foi encontrada.\n", codigoEstadia);
    }
    else if (!foundQuarto)
    {
        printf("\nQuarto associado à estadia não foi encontrado.\n");
    }

    fclose(fileEstadias);
    fclose(tempFileEstadias);
    remove("estadias.dat");
    rename("tempEstadias.dat", "estadias.dat");
    fileEstadias = fopen("estadias.dat", "r+b");
}
// fim funcionalidade 9

// inicio main
int main()
{
    int opcao;
    int numeroQuarto;
    int codigoCliente;
    int codigoClienteBuscar;
    char nomeCliente[50];
    int codigoFuncionarioBuscar;
    char nomeFuncionario[50];
    FILE *fileQuartos;
    FILE *fileEstadias;
    FILE *fileClientes;
    FILE *fileFuncionarios;

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

    if ((fileFuncionarios = fopen("funcionarios.dat", "r+b")) == NULL)
    {
        printf("\nArquivo funcionarios.dat não existia ... criando arquivo!\n");
        if ((fileFuncionarios = fopen("funcionarios.dat", "w+b")) == NULL)
        {
            printf("\nErro na criação do arquivo funcionarios.dat!!\n");
            exit(1);
        }
    }

    do
    {
        system("cls");
        printf("\nMenu:\n");
        printf("0. Limpar todos os dados salvos\n");
        printf("1. Cadastrar funcionario\n");
        printf("2. Buscar funcionario por codigo\n");
        printf("3. Buscar funcionario por nome\n");
        printf("4. Cadastrar cliente\n");
        printf("5. Buscar cliente por codigo\n");
        printf("6. Buscar cliente por nome\n");
        printf("7. Cadastrar quarto\n");
        printf("8. Buscar quarto\n");
        printf("9. Cadastrar estadia\n");
        printf("10. Buscar estadia por cliente\n");
        printf("11. Dar baixa em uma estadia\n");
        printf("13. Sair\n");
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
            if ((fileFuncionarios = fopen("funcionarios.dat", "w+b")) == NULL)
            {
                printf("Erro ao apagar os dados dos funcionarios.\n");
            }

            printf("Todos os dados foram apagados.\n");
            break;
        case 1:
            cadastrarFuncionario(fileFuncionarios);
            break;
        case 2:
            printf("\nDigite o código do Funcionario que deseja buscar: ");
            scanf("%d", &codigoFuncionarioBuscar);
            buscarFuncionarioPorCodigo(fileFuncionarios, codigoFuncionarioBuscar);
            break;
        case 3:
            printf("\nDigite o nome do Funcionario que deseja buscar: ");
            scanf("%s", nomeFuncionario);
            buscarFuncionarioPorNome(fileFuncionarios, nomeFuncionario);
            break;
        case 4:
            cadastrarCliente(fileClientes);
            break;
        case 5:
            printf("\nDigite o código do cliente que deseja buscar: ");
            scanf("%d", &codigoClienteBuscar);
            buscarClientePorCodigo(fileClientes, codigoClienteBuscar);
            break;
        case 6:
            printf("\nDigite o nome do cliente que deseja buscar: ");
            scanf("%s", nomeCliente);
            buscarClientePorNome(fileClientes, nomeCliente);
            break;
        case 7:
            cadastrarQuarto(fileQuartos);
            break;
        case 8:
            printf("\nDigite o número do quarto que deseja buscar: ");
            scanf("%d", &numeroQuarto);
            buscarQuarto(fileQuartos, numeroQuarto);
            break;
        case 9:
            cadastrarEstadia(fileClientes, fileQuartos, fileEstadias);
            break;
        case 10:
            printf("\nDigite o código do cliente que deseja buscar estadias: ");
            scanf("%d", &codigoCliente);
            mostrarEstadiaPorCliente(fileEstadias, codigoCliente);
            break;
        case 11:
            printf("\nDigite o codigo da estadia que deseja dar baixa: ");
            int codigoEstadia;
            scanf("%d", &codigoEstadia);
            darBaixaEstadia(fileEstadias, fileQuartos, codigoEstadia);
            break;
        case 13:
            printf("\nSaindo...\n");
            break;
        default:
            printf("\nOpção inválida.\n");
        }
        printf("\nPressione qualquer tecla para prosseguir...\n");
        getch();
    } while (opcao != 13);

    fclose(fileQuartos);
    fclose(fileEstadias);
    fclose(fileClientes);

    return 0;
}
// fim main
