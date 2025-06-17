typedef struct cliente {
    int codigo;
    char Nome[100];
    char Empresa[100];
    char Departamento[100];
    char Telefone[20];
    char Celular[20];
    char Email[100];
} CLIENTE;

typedef struct elemento* Lista;

Lista *criaLista();

void abortaPrograma();

int tamanhoLista(Lista *li);

int listaCheia(Lista *li);

int listaVazia(Lista *li);

int insereOrdenado (Lista *li, CLIENTE cli);

int removeOrdenado(Lista *li, int cod);

int consultaPosicao(Lista *li, CLIENTE *cli);

int consultaCodigo(Lista *li, int cod, CLIENTE *cli);

struct cliente coleta_dados_cliente();

void apagaLista (Lista *li);
