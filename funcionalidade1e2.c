#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <time.h>

typedef struct {
    int codigo;
    char nome[100];
    char telefone[15];
    char cargo[50];
    float salario;
} Funcionario;

void cadastrarFuncionario(FILE *file) {
    Funcionario funcionario;
    Funcionario funcionarioExistente;

    printf("\nDigite o codigo do funcionario: ");
    scanf("%d", &funcionario.codigo);
    getchar();
    rewind(file);
    while (fread(&funcionarioExistente, sizeof(Funcionario), 1, file) == 1) {
        if (funcionarioExistente.codigo == funcionario.codigo) {
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

void buscarFuncionarioPorCodigo(FILE *file, int codigo) {
    Funcionario funcionario;
    int found = 0;

    if (file == NULL) {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }

    rewind(file);
    while (fread(&funcionario, sizeof(Funcionario), 1, file) == 1) {
        if (funcionario.codigo == codigo) {
            printf("\nCodigo: %d\n", funcionario.codigo);
            printf("Nome: %s\n", funcionario.nome);
            printf("Telefone: %s\n", funcionario.telefone);
            printf("Cargo: %s\n", funcionario.cargo);
            printf("Salario: %.2f\n", funcionario.salario);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nFuncionario com o codigo %d nao foi encontrado.\n", codigo);
    }
}

void buscarFuncionarioPorNome(FILE *file, char *nome) {
    Funcionario funcionario;
    int found = 0;

    if (file == NULL) {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }

    rewind(file);
    while (fread(&funcionario, sizeof(Funcionario), 1, file) == 1) {
        if (strstr(funcionario.nome, nome) != NULL) {
            printf("\nCodigo: %d\n", funcionario.codigo);
            printf("Nome: %s\n", funcionario.nome);
            printf("Telefone: %s\n", funcionario.telefone);
            printf("Cargo: %s\n", funcionario.cargo);
            printf("Salario: %.2f\n", funcionario.salario);
            found = 1;
        }
    }

    if (!found) {
        printf("\nFuncionario com o nome %s nao foi encontrado.\n", nome);
    }
}
