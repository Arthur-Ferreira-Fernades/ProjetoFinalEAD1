#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaLigada.h"

int main()
{
    int x, opcao = 1;
    int codigo;
    CLIENTE cliente_consulta;

    Lista *li = criaLista();

    if ((li = criaLista()) == NULL) {
        abortaPrograma();
    }

    carregarClientesDoArquivo(li); 

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
            if (x > 0) {
                printf("\nCliente cadastrado com sucesso!");
                printf("\nPressione ENTER para voltar ao menu...");
                limpar_buffer();
                getchar();
                system("clear");
            }
            else if(x == -1){
                printf("Código duplicado. Insira outro código.\n");
            }else {
                system("clear");
                printf("Erro ao inserir cliente (lista pode estar cheia).\n");
                printf("\nPressione ENTER para voltar ao menu...");
                limpar_buffer();
                getchar();
                system("clear");
            }
            break;
        case 2:
                printf("\tGerar lista geral de clientes:\n");
                mostraTodosClientes(li);
                printf("\nPressione ENTER para voltar ao menu...");
                limpar_buffer();
                getchar();
                system("clear");
            break;
       case 3:
            printf("\tBuscar cliente por codigo:\n");
            printf("Digite o codigo do cliente:\n");
            scanf("%i", &codigo);
            x = consultaCodigo(li, codigo, &cliente_consulta);
            printf("%i", x);
            if (x) {
                printf("\nCliente %d", codigo);
                printf("\nCódigo:       %d", cliente_consulta.codigo);
                printf("\nNome:         %s", cliente_consulta.Nome);
                printf("\nEmpresa:      %s", cliente_consulta.Empresa);
                printf("\nDepartamento: %s", cliente_consulta.Departamento);
                printf("\nCelular:      %s", cliente_consulta.Celular);
                printf("\nTelefone:     %s", cliente_consulta.Telefone);
                printf("\nEmail:        %s\n", cliente_consulta.Email);
                printf("\nPressione ENTER para voltar ao menu...");
                limpar_buffer();
                getchar();
                system("clear");
            } else {
                printf("\nCodigo Invalido");
                printf("\nPressione ENTER para voltar ao menu...");
                limpar_buffer();
                getchar();
                system("clear");
            }
            break;
            case 4: {
                char nomeBusca[100];
                printf("Digite o nome ou parte do nome do cliente: ");
                limpar_buffer();
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                buscaClientePorNome(li, nomeBusca);
                printf("\nPressione ENTER para voltar ao menu...");
                getchar();
                system("clear");
                break;
            }            
        case 5:
            printf("\tEditar dados cliente por codigo:\n");
            printf("Digite o código do cliente: ");
            scanf("%d", &codigo);
            x = editarClientePorCodigo(li, codigo);
            if (x) {
                printf("\nCliente editado com sucesso!");
            } else {
                printf("\nCliente não encontrado ou edição cancelada.");
            }
            printf("\nPressione ENTER para voltar ao menu...");
            limpar_buffer();
            getchar();
            system("clear");
            break;
        case 6:
            printf("\tRemover cliente por codigo:\n");
            printf("Digite o código do cliente: ");
            scanf("%d", &codigo);
            x = removeOrdenado(li, codigo);
            if (x >= 0) {
                printf("\nCliente removido com sucesso!");
            } else if (x == -1) {
                printf("\nRemoção cancelada pelo usuário.");
            } else {
                printf("\nCliente não encontrado.");
            }
            printf("\nPressione ENTER para voltar ao menu...");
            limpar_buffer();
            getchar();
            system("clear");
            break;
        case 0:
            printf("\nSalvando dados...");
            salvarClientesNoArquivo(li); 
            printf("Dados salvos com sucesso. Encerrando.\n");
            apagaLista(li); 
            break;
        default:
            printf("opcao invalida, digite novamente:\n");
            break;
        }

    }

}
