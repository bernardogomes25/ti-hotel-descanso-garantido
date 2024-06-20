#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_CLIENTES 100

typedef struct {
    int codigo;
    char nome[100];
    char endereco[200];
    char telefone[15];
} Cliente;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarCliente(FILE *file) {
    Cliente cliente;
    Cliente clienteExistente;

    printf("\nDigite o codigo do cliente: ");
    scanf("%d", &cliente.codigo);
    limparBuffer();

    rewind(file);
    while (fread(&clienteExistente, sizeof(Cliente), 1, file) == 1) {
        if (clienteExistente.codigo == cliente.codigo) {
            printf("Erro: Ja existe um cliente com o codigo %d.\n", cliente.codigo);
            return;
        }
    }

    printf("Digite o nome do cliente: ");
    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = '\0';

    printf("Digite o endereco do cliente: ");
    fgets(cliente.endereco, sizeof(cliente.endereco), stdin);
    cliente.endereco[strcspn(cliente.endereco, "\n")] = '\0';

    printf("Digite o telefone do cliente: ");
    fgets(cliente.telefone, sizeof(cliente.telefone), stdin);
    cliente.telefone[strcspn(cliente.telefone, "\n")] = '\0';

    fseek(file, 0, SEEK_END);
    fwrite(&cliente, sizeof(Cliente), 1, file);
}

void buscarClientePorCodigo(FILE *file, int codigo) {
    Cliente cliente;
    int found = 0;

    rewind(file);
    while (fread(&cliente, sizeof(Cliente), 1, file) == 1) {
        if (cliente.codigo == codigo) {
            printf("\nCodigo: %d\n", cliente.codigo);
            printf("Nome: %s\n", cliente.nome);
            printf("Endereco: %s\n", cliente.endereco);
            printf("Telefone: %s\n", cliente.telefone);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nCliente com o codigo %d nao foi encontrado.\n", codigo);
    }
}

void buscarClientePorNome(FILE *file, char *nome) {
    Cliente cliente;
    int found = 0;

    rewind(file);
    while (fread(&cliente, sizeof(Cliente), 1, file) == 1) {
        if (strstr(cliente.nome, nome) != NULL) {
            printf("\nCodigo: %d\n", cliente.codigo);
            printf("Nome: %s\n", cliente.nome);
            printf("Endereco: %s\n", cliente.endereco);
            printf("Telefone: %s\n", cliente.telefone);
            found = 1;
        }
    }

    if (!found) {
        printf("\nCliente com o nome %s nao foi encontrado.\n", nome);
    }
}

int main() {
    int opcao;
    int codigoClienteBuscar;
    char nomeCliente[100];
    FILE *fileClientes;

    if ((fileClientes = fopen("clientes.dat", "r+b")) == NULL) {
        printf("\nArquivo clientes.dat nao existia ... criando arquivo!\n");
        if ((fileClientes = fopen("clientes.dat", "w+b")) == NULL) {
            printf("\nErro na criacao do arquivo clientes.dat!!\n");
            exit(1);
        }
    }

    do {
        system("cls");
        printf("\nMenu:\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Buscar cliente por codigo\n");
        printf("3. Buscar cliente por nome\n");
        printf("4. Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarCliente(fileClientes);
                break;
            case 2:
                printf("\nDigite o codigo do cliente que deseja buscar: ");
                scanf("%d", &codigoClienteBuscar);
                limparBuffer();
                buscarClientePorCodigo(fileClientes, codigoClienteBuscar);
                break;
            case 3:
                printf("\nDigite o nome do cliente que deseja buscar: ");
                fgets(nomeCliente, sizeof(nomeCliente), stdin);
                nomeCliente[strcspn(nomeCliente, "\n")] = '\0';
                buscarClientePorNome(fileClientes, nomeCliente);
                break;
            case 4:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
        }
        printf("\nPressione qualquer tecla para prosseguir...\n");
        getch();
    } while (opcao != 4);

    fclose(fileClientes);

    return 0;
}