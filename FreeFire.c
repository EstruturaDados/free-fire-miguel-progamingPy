#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes para definicao de limites
#define MAX_ITENS_VETOR 100 // Tamanho maximo da mochila baseada em vetor
#define TAM_NOME 30
#define TAM_TIPO 20

// Variaveis globais para contagem de comparacoes (requisito 6)
long long comparacoes_sequencial = 0;
long long comparacoes_binaria = 0;

// ===============================================
// 1. ESTRUTURAS DE DADOS BASE
// ===============================================

// Struct para representar um item generico
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Struct para os nos da Lista Encadeada
typedef struct No {
    Item dados;           // Os dados do Item armazenado no no
    struct No* proximo; // Ponteiro para o proximo no da lista
} No;

// ===============================================
// 2. IMPLEMENTACAO PARA O VETOR (LISTA SEQUENCIAL)
// ===============================================

// Variavel global que armazena os itens do vetor
Item mochilaVetor[MAX_ITENS_VETOR];
// Variavel global que rastreia o numero atual de itens no vetor
int totalItensVetor = 0;

// Prototipos das funcoes do Vetor
void listarVetor();
void inserirItemVetor(const char* nome, const char* tipo, int qtd);
void removerItemVetor(const char* nome);
void ordenarVetor();
int buscarSequencialVetor(const char* nome);
int buscarBinariaVetor(const char* nome);


// ===============================================
// 3. IMPLEMENTACAO PARA A LISTA ENCADEADA
// ===============================================

// Ponteiro que aponta para o inicio da lista encadeada (cabeca)
No* mochilaLista = NULL;

// Prototipos das funcoes da Lista Encadeada
void listarLista();
void inserirItemLista(const char* nome, const char* tipo, int qtd);
void removerItemLista(const char* nome);
No* buscarSequencialLista(const char* nome);


// ===============================================
// FUNCAO PRINCIPAL E MENUS
// ===============================================

// Funcao para exibir o menu e gerenciar as opcoes do Vetor
void menuVetor();
// Funcao para exibir o menu e gerenciar as opcoes da Lista Encadeada
void menuLista();

int main() {
    int escolha;
    
    do {
        printf("\n=========================================\n");
        printf("       SELECAO DE ESTRUTURA (MOCHILA)\n");
        printf("=========================================\n");
        printf("1. Gerenciar Mochila com VETOR (Sequencial)\n");
        printf("2. Gerenciar Mochila com LISTA ENCADEADA\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        // Limpa o buffer de entrada apos scanf
        while(getchar() != '\n'); 

        switch (escolha) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
            case 0:
                printf("\nSaindo do sistema. Ate mais!\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}// Funcao que insere um item no final do vetor (O(1))
void inserirItemVetor(const char* nome, const char* tipo, int qtd) {
    if (totalItensVetor >= MAX_ITENS_VETOR) {
        printf("ERRO: Mochila do Vetor Cheia!\n");
        return;
    }

    // Copia os dados para a proxima posicao livre
    strcpy(mochilaVetor[totalItensVetor].nome, nome);
    strcpy(mochilaVetor[totalItensVetor].tipo, tipo);
    mochilaVetor[totalItensVetor].quantidade = qtd;
    totalItensVetor++;
    
    printf("\nSUCESSO: Item '%s' inserido na Mochila Vetor.\n", nome);
}

// Funcao que lista todos os itens do vetor
void listarVetor() {
    if (totalItensVetor == 0) {
        printf("\nINFO: A Mochila Vetor esta vazia.\n");
        return;
    }
    printf("\n--- MOCHILA VETOR (%d ITENS) ---\n", totalItensVetor);
    for (int i = 0; i < totalItensVetor; i++) {
        printf("[%d] Nome: %s, Tipo: %s, Qtd: %d\n", 
               i, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

// Funcao que remove um item buscando pelo nome (O(n))
void removerItemVetor(const char* nome) {
    // 1. Busca Sequencial para encontrar a posicao
    int i;
    for (i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            break; // Item encontrado na posicao 'i'
        }
    }

    if (i == totalItensVetor) {
        printf("\nERRO: Item '%s' nao encontrado para remocao.\n", nome);
        return;
    }

    // 2. Remocao: Move os elementos seguintes uma posicao para tras
    // Sobrescreve o item removido
    for (int j = i; j < totalItensVetor - 1; j++) {
        mochilaVetor[j] = mochilaVetor[j + 1];
    }
    totalItensVetor--;
    printf("\nSUCESSO: Item '%s' removido da Mochila Vetor.\n", nome);
}

// Funcao que ordena o vetor pelo nome usando Bubble Sort (O(n^2))
void ordenarVetor() {
    Item temp;
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - 1 - i; j++) {
            // Comparacao de nomes
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                // Troca (swap)
                temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("\nSUCESSO: Mochila Vetor ordenada por nome (Bubble Sort).\n");
}

// Funcao de Busca Sequencial (O(n))
// Retorna o indice do item no vetor ou -1 se nao for encontrado.
int buscarSequencialVetor(const char* nome) {
    comparacoes_sequencial = 0; // Reseta o contador
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoes_sequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            return i; // Item encontrado
        }
    }
    return -1; // Nao encontrado
}

// Funcao de Busca Binaria (Requer Ordenacao) (O(log n))
// Retorna o indice do item no vetor ou -1 se nao for encontrado.
int buscarBinariaVetor(const char* nome) {
    comparacoes_binaria = 0; // Reseta o contador
    int inicio = 0;
    int fim = totalItensVetor - 1;
    int meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        int cmp = strcmp(mochilaVetor[meio].nome, nome);
        comparacoes_binaria++; // Conta a comparacao

        if (cmp == 0) {
            return meio; // Item encontrado
        } else if (cmp < 0) {
            inicio = meio + 1; // Busca na metade direita
        } else {
            fim = meio - 1; // Busca na metade esquerda
        }
    }
    return -1; // Nao encontrado
}// Funcao que insere um novo item no inicio da lista (O(1))
void inserirItemLista(const char* nome, const char* tipo, int qtd) {
    // 1. Aloca memoria para o novo no
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("ERRO: Falha na alocacao de memoria para o novo item.\n");
        return;
    }

    // 2. Preenche os dados do item
    strcpy(novoNo->dados.nome, nome);
    strcpy(novoNo->dados.tipo, tipo);
    novoNo->dados.quantidade = qtd;

    // 3. O novo no aponta para onde a 'cabeca' da lista apontava (o antigo primeiro)
    novoNo->proximo = mochilaLista; 
    
    // 4. A 'cabeca' (mochilaLista) agora aponta para o novo no
    mochilaLista = novoNo; 
    
    printf("\nSUCESSO: Item '%s' inserido na Mochila Lista Encadeada.\n", nome);
}

// Funcao que lista todos os itens da lista encadeada (O(n))
void listarLista() {
    if (mochilaLista == NULL) {
        printf("\nINFO: A Mochila Lista Encadeada esta vazia.\n");
        return;
    }
    printf("\n--- MOCHILA LISTA ENCADEADA ---\n");
    No* atual = mochilaLista; // Ponteiro auxiliar para percorrer a lista
    int count = 0;
    while (atual != NULL) {
        printf("[%d] Nome: %s, Tipo: %s, Qtd: %d\n", 
               count++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo; // Avanca para o proximo no
    }
}

// Funcao que remove um item buscando pelo nome (O(n))
void removerItemLista(const char* nome) {
    No* atual = mochilaLista;
    No* anterior = NULL;

    // 1. Busca Sequencial pelo item
    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\nERRO: Item '%s' nao encontrado para remocao.\n", nome);
        return;
    }

    // 2. Remocao:
    if (anterior == NULL) {
        // Caso 1: Item na cabeca da lista
        mochilaLista = atual->proximo;
    } else {
        // Caso 2: Item no meio ou fim da lista
        anterior->proximo = atual->proximo;
    }

    // 3. Libera a memoria do no removido
    free(atual);
    printf("\nSUCESSO: Item '%s' removido da Mochila Lista Encadeada.\n", nome);
}

// Funcao de Busca Sequencial na Lista (O(n))
// Retorna o ponteiro para o no (ou NULL se nao encontrado)
No* buscarSequencialLista(const char* nome) {
    comparacoes_sequencial = 0; // Reseta o contador
    No* atual = mochilaLista;

    while (atual != NULL) {
        comparacoes_sequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            return atual; // Item encontrado
        }
        atual = atual->proximo;
    }
    return NULL; // Nao encontrado
}// Funcao para ler a string com espacos (Usada nos menus)
void lerString(char *destino, int tamanho) {
    if (fgets(destino, tamanho, stdin) != NULL) {
        // Remove o '\n' (Enter) que o fgets adiciona
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        }
    }
}

// Funcao para ler dados do Item
void lerDadosItem(char *nome, char *tipo, int *qtd) {
    printf("Nome do Item: ");
    lerString(nome, TAM_NOME);
    
    printf("Tipo do Item (Ex: Pocao, Arma): ");
    lerString(tipo, TAM_TIPO);
    
    printf("Quantidade: ");
    scanf("%d", qtd);
    while(getchar() != '\n'); // Limpa o buffer
}

// Menu principal para a Estrutura Vetor
void menuVetor() {
    int escolha, qtd, indice;
    char nome[TAM_NOME], tipo[TAM_TIPO];

    do {
        printf("\n--- MOCHILA VETOR ---\n");
        printf("1. Inserir Item\n");
        printf("2. Listar Itens\n");
        printf("3. Remover Item por Nome\n");
        printf("4. Buscar Sequencial por Nome\n");
        printf("5. Ordenar por Nome (Bubble Sort)\n");
        printf("6. Buscar BINARIA por Nome (REQUER ORDENACAO!)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        while(getchar() != '\n');

        switch (escolha) {
            case 1:
                lerDadosItem(nome, tipo, &qtd);
                inserirItemVetor(nome, tipo, qtd);
                break;
            case 2:
                listarVetor();
                break;
            case 3:
                printf("Nome do Item a remover: ");
                lerString(nome, TAM_NOME);
                removerItemVetor(nome);
                break;
            case 4:
                printf("Nome do Item para Busca Sequencial: ");
                lerString(nome, TAM_NOME);
                indice = buscarSequencialVetor(nome);
                if (indice != -1) {
                    printf("\nSUCESSO: Item '%s' encontrado no indice %d.\n", nome, indice);
                } else {
                    printf("\nINFO: Item '%s' nao encontrado.\n", nome);
                }
                printf(">> Comparações realizadas: %lld\n", comparacoes_sequencial);
                break;
            case 5:
                ordenarVetor();
                break;
            case 6:
                printf("Nome do Item para Busca Binaria: ");
                lerString(nome, TAM_NOME);
                indice = buscarBinariaVetor(nome);
                if (indice != -1) {
                    printf("\nSUCESSO: Item '%s' encontrado no indice %d.\n", nome, indice);
                } else {
                    printf("\nINFO: Item '%s' nao encontrado.\n", nome);
                }
                printf(">> Comparações realizadas: %lld\n", comparacoes_binaria);
                break;
            case 0:
                break;
            default:
                printf("\nOpcao invalida.\n");
        }
    } while (escolha != 0);
}

// Menu principal para a Estrutura Lista Encadeada
void menuLista() {
    int escolha, qtd;
    char nome[TAM_NOME], tipo[TAM_TIPO];
    No* noEncontrado;

    do {
        printf("\n--- MOCHILA LISTA ENCADEADA ---\n");
        printf("1. Inserir Item\n");
        printf("2. Listar Itens\n");
        printf("3. Remover Item por Nome\n");
        printf("4. Buscar Sequencial por Nome\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        while(getchar() != '\n');

        switch (escolha) {
            case 1:
                lerDadosItem(nome, tipo, &qtd);
                inserirItemLista(nome, tipo, qtd);
                break;
            case 2:
                listarLista();
                break;
            case 3:
                printf("Nome do Item a remover: ");
                lerString(nome, TAM_NOME);
                removerItemLista(nome);
                break;
            case 4:
                printf("Nome do Item para Busca Sequencial: ");
                lerString(nome, TAM_NOME);
                noEncontrado = buscarSequencialLista(nome);
                if (noEncontrado != NULL) {
                    printf("\nSUCESSO: Item '%s' encontrado (Qtd: %d).\n", 
                           nome, noEncontrado->dados.quantidade);
                } else {
                    printf("\nINFO: Item '%s' nao encontrado.\n", nome);
                }
                printf(">> Comparações realizadas: %lld\n", comparacoes_sequencial);
                break;
            case 0:
                break;
            default:
                printf("\nOpcao invalida.\n");
        }
    } while (escolha != 0);
}