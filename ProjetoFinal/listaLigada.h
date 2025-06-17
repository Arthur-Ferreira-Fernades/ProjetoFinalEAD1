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

void limpar_buffer();

int tamanhoLista(Lista *li);

int listaCheia(Lista *li);

int listaVazia(Lista *li);

int insereOrdenado (Lista *li, CLIENTE cli);

int removeOrdenado(Lista *li, int cod);

void mostraTodosClientes(Lista *li);

int consultaCodigo(Lista *li, int cod, CLIENTE *cli);

void buscaClientePorNome(Lista *li, const char *nomeBusca);

int editarClientePorCodigo(Lista *li, int codigo);

struct cliente coleta_dados_cliente();

void apagaLista (Lista *li);

void carregarClientesDoArquivo(Lista *li);

void salvarClientesNoArquivo(Lista *li);