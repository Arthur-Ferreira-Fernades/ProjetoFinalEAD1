#include <stdio.h>
#include <stdlib.h>
#include "listaLigada.h"

int main()
{
    int x, opcao = 1;
    int codigo, posicao = 2;
    CLIENTE cliente_consulta;

    Lista *li = NULL;

    if ((li = criaLista()) == NULL) {
        abortaPrograma();
    }

    while(opcao != 0) {
        printf("\n\tDigite a Opcao desejada:\n");
        printf("1 - Inserir novo cliente:\n");
        printf("2 - Gerar lista geral de cliente:\n");
        printf("3 - Buscar cliente por codigo:\n");
        printf("4 - Buscar cliente por nome:\n");
        printf("5 - Editar dados cliente por codigo:\n");
        printf("6 - Remover cliente por codigo:\n");
        printf("0 - Encerrar programa:\n");
        scanf("%i", &opcao);
        switch (opcao)
        {
        case 1:
        printf("\tInserir cliente:\n");
            struct cliente novo = coleta_dados_cliente();
            x = insereOrdenado(li, novo);
            if (x) {
                printf("Cliente inserido com sucesso!\nPrecione qualquer tecla para continuar");
                system("pause");
                system("cls");
            }
            else{
            system("cls");
            printf("Erro ao inserir cliente (lista pode estar cheia).\n");
            }
            break;
        case 2:
            printf("\tGerar lista geral de cliente:\n");
            x = tamanhoLista(li);
            int i = 0;
            while (i < x) {
                x = consultaPosicao(li, &cliente_consulta);
                if (x) {
                    printf("\nCliente %i", &i);
                    printf("\nCodigo:    %d", cliente_consulta.codigo);
                    printf("\n\nCliente: %c", cliente_consulta.Nome);
                    printf("\nEmpresa:   %.2f", cliente_consulta.Empresa);
                    printf("\nDepartamento:   %.2f", cliente_consulta.Departamento);
                    printf("\nCelular:   %.2f\n", cliente_consulta.Celular);
                    printf("\nTelefone:   %.2f\n", cliente_consulta.Telefone);
                    printf("\nEmail:   %.2f\n", cliente_consulta.Email);
                } else {
                    printf("\nNão foi possivel gerar lista geral");
                }
                i++;
            }
            system("cls");
            break;
   /*     case 3:
            printf("\tBuscar cliente por codigo:\n");
            printf("Digite a matricula do aluno:\n");
            scanf("%i", &matricula);
            x = removeOrdenado(li, matricula);
            if (x) {
                printf("\nAluno %d removido ordenadamente com sucesso!", x);
            } else {
                printf("\nNao foi possivel remover o aluno");
            }
        case 4:
            printf("\tBuscar cliente por nome:\n");
            printf("Digite a matricula do aluno:\n");
            scanf("%i", &matricula);
            x = removeOrdenado(li, matricula);
            if (x) {
                printf("\nAluno %d removido ordenadamente com sucesso!", x);
            } else {
                printf("\nNao foi possivel remover o aluno");
            }
        case 5:
            printf("\tEditar dados cliente por codigo:\n");
            printf("Digite a matricula do aluno:\n");
            scanf("%i", &matricula);
            x = removeOrdenado(li, matricula);
            if (x) {
                printf("\nAluno %d removido ordenadamente com sucesso!", x);
            } else {
                printf("\nNao foi possivel remover o aluno");
            }
        case 6:
            printf("\tRemover cliente por codigo:\n");
            printf("Digite a matricula do aluno:\n");
            scanf("%i", &matricula);
            x = removeOrdenado(li, matricula);
            if (x) {
                printf("\nAluno %d removido ordenadamente com sucesso!", x);
            } else {
                printf("\nNao foi possivel remover o aluno");
            }*/
        case 0:
            break;
        default:
            printf("opcao invalida, digite novamente:\n");
            break;
        }

    }

}
