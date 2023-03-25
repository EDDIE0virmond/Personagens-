#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Categoria {
    char nome[20];
    int forca;
    int defesa;
    struct Categoria* proxima;
    struct Categoria* anterior;
};

void adicionar_categoria(struct Categoria** cabeca, char nome[20], int forca, int defesa) {
    struct Categoria* nova_categoria = (struct Categoria*)malloc(sizeof(struct Categoria));
    strcpy(nova_categoria->nome, nome);
    nova_categoria->forca = forca;
    nova_categoria->defesa = defesa;

    if (*cabeca == NULL) {
        nova_categoria->anterior = NULL;
        nova_categoria->proxima = NULL;
        *cabeca = nova_categoria;
    } else {
        struct Categoria* atual = *cabeca;
        while (atual->proxima != NULL) {
            atual = atual->proxima;
        }
        atual->proxima = nova_categoria;
        nova_categoria->anterior = atual;
        nova_categoria->proxima = NULL;
    }
}

void imprimir_categorias(struct Categoria* cabeca) {
    struct Categoria* atual = cabeca;
    while (atual != NULL) {
        printf("Categoria: %s\n", atual->nome);
        printf("Força: %d\n", atual->forca);
        printf("Defesa: %d\n", atual->defesa);
        atual = atual->proxima;
    }
}

void remover_categoria(struct Categoria** cabeca, char nome[20]) {
    struct Categoria* atual = *cabeca;
    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        atual = atual->proxima;
    }
    if (atual != NULL) {
        if (atual->anterior != NULL) {
            atual->anterior->proxima = atual->proxima;
        } else {
            *cabeca = atual->proxima;
        }
        if (atual->proxima != NULL) {
            atual->proxima->anterior = atual->anterior;
        }
        free(atual);
    }
}

void liberar_categorias(struct Categoria** cabeca) {
    struct Categoria* atual = *cabeca;
    while (atual != NULL) {
        struct Categoria* proxima = atual->proxima;
        free(atual);
        atual = proxima;
    }
    *cabeca = NULL;
}


struct Personagem {
    char nome[20];
    int idade;
    float altura;
    struct Categoria categoria;
    struct Personagem* esquerda;
    struct Personagem* direita;
};

// Função para criar um novo nó na árvore
struct Personagem* criar_personagem(char nome[], int idade, float altura, struct Categoria categoria) {
    struct Personagem* novo_personagem = (struct Personagem*) malloc(sizeof(struct Personagem));
    strcpy(novo_personagem->nome, nome);
    novo_personagem->idade = idade;
    novo_personagem->altura = altura;
    novo_personagem->categoria = categoria;
    novo_personagem->esquerda = NULL;
    novo_personagem->direita = NULL;
    return novo_personagem;
}

// Função para inserir um novo nó na árvore
struct Personagem* inserir_personagem(struct Personagem* raiz, char nome[], int idade, float altura, struct Categoria categoria) {
    if (raiz == NULL) {
        return criar_personagem(nome, idade, altura, categoria);
    }
    if (strcmp(nome, raiz->nome) < 0) {
        raiz->esquerda = inserir_personagem(raiz->esquerda, nome, idade, altura, categoria);
    } else if (strcmp(nome, raiz->nome) > 0) {
        raiz->direita = inserir_personagem(raiz->direita, nome, idade, altura, categoria);
    }
    return raiz;
}

// Função para buscar um nó na árvore
struct Personagem* buscar_personagem(struct Personagem* raiz, char nome[]) {
    if (raiz == NULL || strcmp(nome, raiz->nome) == 0) {
        return raiz;
    }
    if (strcmp(nome, raiz->nome) < 0) {
        return buscar_personagem(raiz->esquerda, nome);
    }
    return buscar_personagem(raiz->direita, nome);
}

// Função para deletar um nó da árvore
struct Personagem* deletar_personagem(struct Personagem* raiz, char nome[]) {
    if (raiz == NULL) {
        return raiz;
    }
    if (strcmp(nome, raiz->nome) < 0) {
        raiz->esquerda = deletar_personagem(raiz->esquerda, nome);
    } else if (strcmp(nome, raiz->nome) > 0) {
        raiz->direita = deletar_personagem(raiz->direita, nome);
    } else {
        if (raiz->esquerda == NULL) {
            struct Personagem* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            struct Personagem* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        struct Personagem* temp = raiz->direita;
        while (temp && temp->esquerda != NULL) {
            temp = temp->esquerda;
        }
        strcpy(raiz->nome, temp->nome);
        raiz->idade = temp->idade;
    }
}
void imprimir_personagem(struct Personagem* personagem) {
    printf("Nome: %s\nIdade: %d\n", personagem->nome, personagem->idade);
printf("Altura: %.2f\n", personagem->altura);
printf("Categoria:\n");
printf("- Nome: %s\n", personagem->categoria.nome);
printf("- Força: %d\n", personagem->categoria.forca);
printf("- Defesa: %d\n", personagem->categoria.defesa);
}

void imprimir_arvore(struct Personagem* raiz) {
if (raiz != NULL) {
imprimir_arvore(raiz->esquerda);
imprimir_personagem(raiz);
imprimir_arvore(raiz->direita);
}
}

void alterar_categoria(struct Personagem* personagem, struct Categoria nova_categoria) {
personagem->categoria = nova_categoria;
}

int main() {
struct Personagem* raiz = NULL;

// Criação das categorias
struct Categoria categoria1 = {"Guerreiro", 10, 8};
struct Categoria categoria2 = {"Mago", 6, 4};

// Criação dos personagens
struct Personagem* personagem1 = criar_personagem("João", 25, 1.80, categoria1);
struct Personagem* personagem2 = criar_personagem("Maria", 30, 1.70, categoria2);
struct Personagem* personagem3 = criar_personagem("Pedro", 20, 1.75, categoria1);

// Inserção dos personagens na árvore
raiz = inserir_personagem(raiz, personagem1->nome, personagem1->idade, personagem1->altura, personagem1->categoria);
raiz = inserir_personagem(raiz, personagem2->nome, personagem2->idade, personagem2->altura, personagem2->categoria);
raiz = inserir_personagem(raiz, personagem3->nome, personagem3->idade, personagem3->altura, personagem3->categoria);

// Impressão da árvore
printf("Árvore antes da alteração de categoria:\n");
imprimir_arvore(raiz);

// Alteração de categoria do personagem 1
struct Categoria nova_categoria = {"Arqueiro", 7, 5};
struct Personagem* personagem1_atualizado = buscar_personagem(raiz, "João");
alterar_categoria(personagem1_atualizado, nova_categoria);

// Impressão da árvore após a alteração
printf("\nÁrvore após a alteração de categoria:\n");
imprimir_arvore(raiz);

// Deleção do personagem 2
raiz = deletar_personagem(raiz, "Maria");

// Impressão da árvore após a deleção
printf("\nÁrvore após a deleção do personagem 2:\n");
imprimir_arvore(raiz);

return 0;
}

