#include <stdio.h>
#include <stdlib.h>
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
    printf("ERRO! Lista nao foi alocada");
    printf("programa sera encerrado... \n\n\n");
    system("pause");
    exit(1);
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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
    if (no == *li){
        *li = no -> prox;
    } else {
        ant -> prox = no -> prox;
    }
    codigo = no -> dados.codigo;
    free(no);
    return codigo;
}

int consultaPosicao(Lista *li, CLIENTE *cli) {
    if (li == NULL){
        abortaPrograma();
    }

    ELEM *no = *li;
    int i = 1;
    while (no != NULL) {
        no = no -> prox;
        *cli = no -> dados;
        i++;
    }
    return 1;
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


