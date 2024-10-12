
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_NOTAS 4  // Limite de 4 notas por aluno

typedef struct nota {
    float nota;
    struct nota *prev;
    struct nota *next;
} Nota;

typedef struct aluno {
    int id;
    char nome[500];
    Nota *notas;
    struct aluno *prev; //ponteiro para o nó anterior
    struct aluno *next; //ponteiro para o nó posterior
} Aluno;

typedef struct {
    Aluno* head; // Ponteiro para o primeiro nó, para o head(cabeça) da lista
    Aluno* tail; // Ponteiro para o último nó da lista, para o tail(cauda) da lista
} DoublyLinkedList;

// Prototipação das funções
DoublyLinkedList* inicializar_lista();
void imprimir_lista(DoublyLinkedList *list);
void liberar_lista(DoublyLinkedList *lista);
int verificar_id(DoublyLinkedList *list, int id);
void inserir_aluno_no_final(DoublyLinkedList *list, int id, const char *nome);
void excluir_aluno(DoublyLinkedList *list, int id);
void inserir_nota(Aluno *aluno, float valor);
void imprimir_notas(Aluno *aluno);
void buscar_aluno_nota(DoublyLinkedList *list, int id);
void excluir_nota(Aluno *aluno, int posicao);
void alterar_nota(Aluno *aluno, int posicao, float valor);
void liberar_notas(Nota *nota);
void limpar_terminal();
void pausar_para_mensagem(const char* mensagem);
void exibir_menu_nota(Aluno *aluno);
int exibir_menu();

// Funções implementadas
DoublyLinkedList* inicializar_lista(){
DoublyLinkedList *lista = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
if(!lista){
    perror("Erro ao alocar memória.");
}

lista->head = NULL;
lista->tail = NULL;
return lista;

}

void imprimir_lista(DoublyLinkedList *list){
    Aluno *atual = list->head;
    if (atual == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    while (atual != NULL) {
        printf("%d  %s\n", atual->id, atual->nome);
        atual = atual->next;
    }
}

void liberar_lista(DoublyLinkedList *lista){
      Aluno* atual = lista->head;
    while (atual != NULL) {
        Aluno* proximo = atual->next;
        liberar_notas(atual->notas);  // Libera notas do aluno
        free(atual);
        atual = proximo;
    }
    free(lista);
}

int verificar_id(DoublyLinkedList *list, int id) {
    Aluno *aluno = list->head;
    while (aluno != NULL) {
        if (aluno->id == id) {
            return 1;
        }
        aluno = aluno->next; 
    }
    return 0; 
}

void inserir_aluno_no_final(DoublyLinkedList *list, int id, const char *nome) {
    if (verificar_id(list, id)) {
        fprintf(stderr, "⚠ Erro: ID já cadastrado");
        return;
    }

    Aluno *novo_aluno = (Aluno*)malloc(sizeof(Aluno));
    if (!novo_aluno) {
        perror("Erro ao alocar memória para o aluno");
        exit(1);
    }
    

    strcpy(novo_aluno->nome, nome);
    novo_aluno->id = id;
    novo_aluno->next = NULL;
    novo_aluno->notas = NULL;
    novo_aluno->prev = list->tail;

    if (list->tail != NULL) {
        list->tail->next = novo_aluno;
    } else {
        list->head = novo_aluno;
    }

    list->tail = novo_aluno;
    printf("Aluno cadastrado com sucesso!\n");
    return;
}


void excluir_aluno(DoublyLinkedList *list, int id) {
    Aluno *temp = list->head;
    while (temp != NULL) {
        if (temp->id == id) {
            liberar_notas(temp->notas);  // Libera as notas
            if (temp == list->head) {
                list->head = temp->next;
                if (list->head != NULL) {
                    list->head->prev = NULL;
                } else {
                    list->tail = NULL;
                }
            } else if (temp == list->tail) {
                list->tail = temp->prev;
                list->tail->next = NULL;
            } else {
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;
            }
            free(temp);
            printf("Aluno excluído com sucesso!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Aluno não encontrado. Verifique se o ID está correto.\n");
}

void liberar_notas(Nota *nota) {
    while (nota != NULL) {
        Nota *prox = nota->next;
        free(nota);
        nota = prox;
    }
}

int contar_notas(Aluno *aluno) {
    int count = 0;
    Nota *nota_atual = aluno->notas;
    while (nota_atual != NULL) {
        count++;
        nota_atual = nota_atual->next;
    }
    return count;
}

void inserir_nota(Aluno *aluno, float valor) {
    if (contar_notas(aluno) >= MAX_NOTAS) {
        printf("Erro: O aluno já possui o número máximo de %d notas.\n", MAX_NOTAS);
        return;
    }
    
     if (valor < 0 || valor > 10) {
        printf("Erro: A nota deve estar entre 0 e 10.\n");
        return;
    }

    Nota *nota = (Nota*)malloc(sizeof(Nota));
    if(!nota){
        perror("Erro ao alocar memória para o aluno");
        exit(1);
    }
    nota->nota = valor;
    nota->next = NULL;

    if (aluno->notas == NULL) {
        nota->prev = NULL;
        aluno->notas = nota;
    } else {
        Nota *ultima_nota = aluno->notas;
        while (ultima_nota->next != NULL) {
            ultima_nota = ultima_nota->next;
        }
        ultima_nota->next = nota;
        nota->prev = ultima_nota;
    }

    printf("Nota %.2f inserida com sucesso!\n", valor);
}

void imprimir_notas(Aluno *aluno) {
    float soma = 0.0;
    int count = 0;

    Nota *nota_atual = aluno->notas;
    if (nota_atual == NULL) {
        printf("Sem notas publicadas.\n");
        return;
    }

    while (nota_atual != NULL) {
        printf("%.2f ", nota_atual->nota);
        soma += nota_atual->nota;
        count++;
        nota_atual = nota_atual->next;
    }

    if (count > 0) {
        printf("\nMédia: %.2f\n", soma / count);
    }
}

void alterar_nota(Aluno *aluno, int posicao, float valor) {
    int count = 0;
    Nota *nota_atual = aluno->notas;
    while (nota_atual != NULL) {
        count++;
        if (count == posicao) {
            nota_atual->nota = valor;
            printf("Nota alterada\n");
            return;
        }
        nota_atual = nota_atual->next;
    }
    printf("A nota que deseja alterar não existe.\n");
}

void excluir_nota(Aluno *aluno, int posicao) {
    if (aluno->notas == NULL) {
        printf("Não há notas para excluir.\n");
        return;
    }

    Nota *nota_atual = aluno->notas;
    int count = 1;

    while (nota_atual != NULL) {
        if (count == posicao) {
            if (nota_atual == aluno->notas) {
                aluno->notas = nota_atual->next;
                if (aluno->notas != NULL) {
                    aluno->notas->prev = NULL;
                }
            } else if (nota_atual->next == NULL) {
                nota_atual->prev->next = NULL;
            } else {
                nota_atual->prev->next = nota_atual->next;
                nota_atual->next->prev = nota_atual->prev;
            }

            free(nota_atual);
            printf("Nota na posição %d excluída com sucesso!\n", posicao);
            return;
        }

        nota_atual = nota_atual->next;
        count++;
    }

    printf("Posição %d inválida. Não há notas nessa posição.\n", posicao);
}

void buscar_aluno_nota(DoublyLinkedList *list, int id) {
    Aluno *aluno = list->head;
    int opcao;
    float valor;

    while (aluno != NULL) {
        if (aluno->id == id) {
            do {
                printf("Aluno: %s\n", aluno->nome);
                printf("1. Inserir nota\n");
                printf("2. Visualizar notas\n");
                printf("3. Voltar ao menu\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        limpar_terminal();
                        printf("Insira a nota: ");
                        scanf("%f", &valor);
                        inserir_nota(aluno, valor);
                        break;

                    case 2:
                        exibir_menu_nota(aluno);
                        break;

                    case 3:
                        printf("Voltando ao menu inicial...\n");
                        break;

                    default:
                        printf("Opção inválida\n");
                        break;
                }
            } while (opcao != 3);
            return;
        }
        aluno = aluno->next;
    }

    printf("Aluno não encontrado.\n");
}

void exibir_menu_nota(Aluno *aluno) {
    int sub_opcao;
    int posicao_nota;
    float valor;

    limpar_terminal();
    imprimir_notas(aluno);
    printf("\n1. Alterar nota\n");
    printf("2. Excluir nota\n");
    printf("3. Voltar ao menu\n");
    printf("Escolha uma opção: ");
    scanf("%d", &sub_opcao);

    switch (sub_opcao) {
        case 1:
            printf("Qual nota deseja alterar?(digite a posição): ");
            scanf("%d", &posicao_nota);
            printf("Informe o novo valor da nota: ");
            scanf("%f", &valor);
            alterar_nota(aluno, posicao_nota, valor);
            pausar_para_mensagem("Nota alterada.");
            break;

        case 2:
            printf("Qual nota deseja excluir?(digite a posição): ");
            scanf("%d", &posicao_nota);
            excluir_nota(aluno, posicao_nota);
            pausar_para_mensagem("Nota excluída.");
            break;

        case 3:
            limpar_terminal();
            return;

        default:
            printf("Opção inválida\n");
            break;
    }
}

void limpar_terminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar_para_mensagem(const char* mensagem) {
    printf("%s\nPressione Enter para continuar...", mensagem);
    getchar(); // Lê o "Enter"
}

int exibir_menu() {
    int opcao;
    printf("SISTEMA DE NOTAS DE ALUNOS\n");
    printf("1. Cadastrar aluno\n");
    printf("2. Listar alunos\n");
    printf("3. Excluir aluno\n");
    printf("4. nota\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar(); 
    return opcao;
}

int main() {
    DoublyLinkedList *lista = inicializar_lista();
    int opcao;
    int aid;
    char name[500];

    do {
        limpar_terminal();
        opcao = exibir_menu();

        switch (opcao) {
            case 1:
                limpar_terminal();
                printf("CADASTRO DE ALUNOS\nID: ");
                scanf("%d", &aid);
                while(getchar() != '\n');
                printf("Nome do aluno: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; 
                inserir_aluno_no_final(lista, aid, name);
                pausar_para_mensagem("");
                break;

            case 2:
                limpar_terminal();
                imprimir_lista(lista);
                pausar_para_mensagem("");
                break;

            case 3:
                printf("Insira o ID do aluno que quer excluir: ");
                scanf("%d", &aid);
                excluir_aluno(lista, aid);
                pausar_para_mensagem("");
                break;

            case 4:
                limpar_terminal();
                printf("Insira o id do aluno: ");
                scanf("%d", &aid);
                buscar_aluno_nota(lista, aid);
                limpar_terminal();
                break;

            case 0:
                printf("O programa está sendo encerrado...\n");
                break;

            default:
                printf("Opção inválida\n");
                pausar_para_mensagem("");
                break;
        }
    } while (opcao != 0);

    liberar_lista(lista);
    return 0;
}


