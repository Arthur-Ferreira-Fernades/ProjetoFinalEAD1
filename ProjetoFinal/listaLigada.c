#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "listaLigada.h"

struct elemento {
    CLIENTE dados;
    struct elemento *prox;
};
typedef struct elemento ELEM;

Lista *criaLista(){
    Lista *li;
    li = (Lista*) malloc (sizeof(Lista));
    if (li != NULL) {
        *li = NULL;
    }
    return li;
}

void abortaPrograma() {
    printf("ERRO! Lista nao foi alocada\n");
    printf("programa sera encerrado... \n\n\n");
    system("pause");
    exit(1);
}

void paraMinuscula(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void salvarClientesNoArquivo(Lista *li) {
    FILE *fp = fopen("clientes.dat", "wb");
    if (!fp) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return;
    }

    ELEM *no = *li;
    while (no != NULL) {
        fwrite(&no->dados, sizeof(CLIENTE), 1, fp);
        no = no->prox;
    }
    fclose(fp);
}

void carregarClientesDoArquivo(Lista *li) {
    FILE *fp = fopen("clientes.dat", "rb");
    if (!fp) return;

    CLIENTE cliente;
    while (fread(&cliente, sizeof(CLIENTE), 1, fp)) {
        insereOrdenado(li, cliente);
    }

    fclose(fp);

    int x = tamanhoLista(li);

    if (x > 0) {
        printf("%i cliente(s) encontado(s)\n\n", x);
    } else {
        printf("Nenhum Cliente encontrado\n\n");
    }
}


int tamanhoLista(Lista *li) {
    if(li == NULL) {
        abortaPrograma();
    }
    int acum = 0;
    ELEM *no = *li;
    while (no != NULL) {
        acum++;
        no = no -> prox;
    }
    return acum;
}

int listaCheia(Lista *li){
    if (li == NULL) {
        abortaPrograma();
    }
    return 0;
}

int listaVazia(Lista *li) {
    if (li == NULL) {
        abortaPrograma();
    }
    if (*li == NULL) {
        return 1;
    }
    return 0;
}

int insereOrdenado(Lista *li, CLIENTE cli) {
    if (li == NULL) {
        abortaPrograma();
    }

    ELEM *temp = *li;
    while(temp != NULL) {
        if(temp->dados.codigo == cli.codigo) {
            return -1;
        }
        temp = temp->prox;
    }

    
    ELEM *no = (ELEM*) malloc(sizeof(ELEM));
    if (no == NULL) {
        return 0;
    }
    no -> dados = cli;
    if(listaVazia(li)) {
        no -> prox = (*li);
        *li = no;
        return cli.codigo;
    } else {
        ELEM *ant, *atual = *li;
        while (atual != NULL && atual -> dados.codigo < cli.codigo) {
            ant = atual;
            atual = atual -> prox;
        }
        if (atual == *li) {
            no -> prox = (*li);
            *li = no;
        } else {
            no -> prox = ant -> prox;
            ant -> prox = no;
        }
        return cli.codigo;
    }
}

int removeOrdenado(Lista *li, int cod) {
    int codigo;
    if (li == NULL){
        abortaPrograma();
    }
    ELEM *ant, *no = *li;
    while (no != NULL && no -> dados.codigo != cod) {
        ant = no;
        no = no -> prox;
    }
    if (no == NULL) {
        return 0;
    }

    printf("\nCliente encontrado:\n");
    printf("Código:       %d\n", no->dados.codigo);
    printf("Nome:         %s\n", no->dados.Nome);
    printf("Empresa:      %s\n", no->dados.Empresa);
    printf("Departamento: %s\n", no->dados.Departamento);
    printf("Celular:      %s\n", no->dados.Celular);
    printf("Telefone:     %s\n", no->dados.Telefone);
    printf("Email:        %s\n", no->dados.Email);

    char confirmacao;
    printf("\nDeseja realmente remover este cliente? (s/n): ");
    limpar_buffer();
    scanf("%c", &confirmacao);
    if (confirmacao != 's' && confirmacao != 'S') {
        printf("\nRemoção cancelada.\n");
        return -1;
    }
    
    if (no == *li){
        *li = no -> prox;
    } else {
        ant -> prox = no -> prox;
    }
    codigo = no -> dados.codigo;
    free(no);
    return codigo;
}

void mostraTodosClientes(Lista *li) {
    if (li == NULL || *li == NULL) {
        printf("\nLista vazia ou não inicializada.\n");
        return;
    }

    ELEM *no = *li;
    int i = 1;

    while (no != NULL) {
        printf("\nCliente %d", i);
        printf("\nCódigo:       %d", no->dados.codigo);
        printf("\nNome:         %s", no->dados.Nome);
        printf("\nEmpresa:      %s", no->dados.Empresa);
        printf("\nDepartamento: %s", no->dados.Departamento);
        printf("\nCelular:      %s", no->dados.Celular);
        printf("\nTelefone:     %s", no->dados.Telefone);
        printf("\nEmail:        %s\n", no->dados.Email);
        printf("----------------------------------------\n");
        no = no->prox;
        i++;
    }

    printf("\nTotal de clientes cadastrados: %d\n", i - 1);
}

int consultaCodigo(Lista *li, int cod, CLIENTE *cli) {
    if (li == NULL){
        abortaPrograma();
    }
    ELEM *no = *li;
    while (no != NULL && no -> dados.codigo != cod){
        no = no -> prox;
    }
    if (no == NULL) {
        return 0;
    } else {
        *cli = no -> dados;
        return 1;
    }
}

void buscaClientePorNome(Lista *li, const char *nomeBusca) {
    if (li == NULL) {
        abortaPrograma();
    }

    char nomeBuscaMinuscula[100];
    strncpy(nomeBuscaMinuscula, nomeBusca, sizeof(nomeBuscaMinuscula));
    nomeBuscaMinuscula[sizeof(nomeBuscaMinuscula) - 1] = '\0';
    paraMinuscula(nomeBuscaMinuscula);

    ELEM *no = *li;
    int achou = 0;

    while (no != NULL) {
        char nomeClienteMinusculo[100];
        strncpy(nomeClienteMinusculo, no->dados.Nome, sizeof(nomeClienteMinusculo));
        nomeClienteMinusculo[sizeof(nomeClienteMinusculo) - 1] = '\0';
        paraMinuscula(nomeClienteMinusculo);

        if (strstr(nomeClienteMinusculo, nomeBuscaMinuscula) != NULL) {
            printf("\nCodigo: %d\n", no->dados.codigo);
            printf("Nome: %s\n", no->dados.Nome);
            printf("Empresa: %s\n", no->dados.Empresa);
            printf("Departamento: %s\n", no->dados.Departamento);
            printf("Telefone: %s\n", no->dados.Telefone);
            printf("Celular: %s\n", no->dados.Celular);
            printf("Email: %s\n\n", no->dados.Email);
            achou = 1;
        }
        no = no->prox;
    }

    if (!achou) {
        printf("Nenhum cliente encontrado com o nome contendo \"%s\".\n", nomeBusca);
    }
}


struct cliente coleta_dados_cliente() {
    struct cliente c;

    printf("\nDigite o codigo do cliente: ");
    scanf("%d", &c.codigo);
    limpar_buffer();

    printf("Digite o nome do cliente: ");
    fgets(c.Nome, sizeof(c.Nome), stdin);
    c.Nome[strcspn(c.Nome, "\n")] = '\0';

    printf("Digite a empresa do cliente: ");
    fgets(c.Empresa, sizeof(c.Empresa), stdin);
    c.Empresa[strcspn(c.Empresa, "\n")] = '\0';

    printf("Digite o departamento do cliente: ");
    fgets(c.Departamento, sizeof(c.Departamento), stdin);
    c.Departamento[strcspn(c.Departamento, "\n")] = '\0';

    printf("Digite o email do cliente: ");
    fgets(c.Email, sizeof(c.Email), stdin);
    c.Email[strcspn(c.Email, "\n")] = '\0';

    printf("Digite o celular do cliente: ");
    fgets(c.Celular, sizeof(c.Celular), stdin);
    c.Celular[strcspn(c.Celular, "\n")] = '\0';

    printf("Digite o telefone do cliente: ");
    fgets(c.Telefone, sizeof(c.Telefone), stdin);
    c.Telefone[strcspn(c.Telefone, "\n")] = '\0';

    return c;
}

int editarClientePorCodigo(Lista *li, int codigo) {
    if (li == NULL || *li == NULL)
        return 0;

    ELEM *no = *li;
    while (no != NULL) {
        if (no->dados.codigo == codigo) {
            printf("\nCliente encontrado:\n");
            printf("Código:       %d\n", no->dados.codigo);
            printf("Nome:         %s\n", no->dados.Nome);
            printf("Empresa:      %s\n", no->dados.Empresa);
            printf("Departamento: %s\n", no->dados.Departamento);
            printf("Celular:      %s\n", no->dados.Celular);
            printf("Telefone:     %s\n", no->dados.Telefone);
            printf("Email:        %s\n", no->dados.Email);

            char confirmacao;
            printf("\nDeseja editar os dados deste cliente? (s/n): ");
            limpar_buffer();
            scanf("%c", &confirmacao);
            if (confirmacao != 's' && confirmacao != 'S') {
                printf("\nEdição cancelada. Retornando ao menu...");
                return 0;
            }

            printf("\n--- Editando cliente (deixe em branco para manter) ---\n");
            CLIENTE novo = no->dados;

            limpar_buffer();
            printf("Novo nome (%s): ", novo.Nome);
            fgets(novo.Nome, sizeof(novo.Nome), stdin);
            if (novo.Nome[0] != '\n') novo.Nome[strcspn(novo.Nome, "\n")] = '\0';

            printf("Nova empresa (%s): ", novo.Empresa);
            fgets(novo.Empresa, sizeof(novo.Empresa), stdin);
            if (novo.Empresa[0] != '\n') novo.Empresa[strcspn(novo.Empresa, "\n")] = '\0';

            printf("Novo departamento (%s): ", novo.Departamento);
            fgets(novo.Departamento, sizeof(novo.Departamento), stdin);
            if (novo.Departamento[0] != '\n') novo.Departamento[strcspn(novo.Departamento, "\n")] = '\0';

            printf("Novo telefone (%s): ", novo.Telefone);
            fgets(novo.Telefone, sizeof(novo.Telefone), stdin);
            if (novo.Telefone[0] != '\n') novo.Telefone[strcspn(novo.Telefone, "\n")] = '\0';

            printf("Novo celular (%s): ", novo.Celular);
            fgets(novo.Celular, sizeof(novo.Celular), stdin);
            if (novo.Celular[0] != '\n') novo.Celular[strcspn(novo.Celular, "\n")] = '\0';

            printf("Novo email (%s): ", novo.Email);
            fgets(novo.Email, sizeof(novo.Email), stdin);
            if (novo.Email[0] != '\n') novo.Email[strcspn(novo.Email, "\n")] = '\0';

            no->dados = novo;
            return 1;
        }
        no = no->prox;
    }
    return 0;
}

void apagaLista(Lista *li) {
    if (li != NULL) {
        ELEM *no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li) -> prox;
            free(no);
        }
        free(li);
    }
}


