
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
    char id[15];
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
int verificar_id(DoublyLinkedList *list, char *id);
int verificar_quatidade_de_digitos(char *id);
void inserir_aluno_no_final(DoublyLinkedList *list, char *id, const char *nome);
void excluir_aluno(DoublyLinkedList *list, char *id);
void inserir_nota(Aluno *aluno, float valor);
void imprimir_notas(Aluno *aluno);
void buscar_aluno_nota(DoublyLinkedList *list, char *id);
void excluir_nota(Aluno *aluno, int posicao);
void alterar_nota(Aluno *aluno, int posicao, float valor);
void liberar_notas(Nota *nota);
void limpar_terminal();
void pausar_para_mensagem(const char* mensagem);
void exibir_menu_nota(Aluno *aluno);
void dividir_lista(Aluno* head, Aluno** front, Aluno** back);
Aluno* merge_listas(Aluno *front, Aluno *back);
Aluno *merge_sort(Aluno *head);
void ordenar_alunos(DoublyLinkedList *list);


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
    ordenar_alunos(list);
    Aluno *atual = list->head;
    if (atual == NULL) {
        printf("A lista está vazia.\n");
        return;
    }
    
    while (atual != NULL) {
        printf("%s  %s\n", atual->id, atual->nome);
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

int verificar_id(DoublyLinkedList *list, char *id) {
    Aluno *aluno = list->head;
    while (aluno != NULL) {
        if (strcmp(aluno->id, id) == 0) {
        return 1;
    }
        aluno = aluno->next; 
    }
    return 0; 
}

int verificar_quatidade_de_digitos(char *id){
int digitos = strlen(id);

if(digitos>14 || digitos<14){
printf("erro");
return 1;
}
return 0;
}


void inserir_aluno_no_final(DoublyLinkedList *list, char *id, const char *nome) {
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
    strcpy(novo_aluno->id, id);
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


void excluir_aluno(DoublyLinkedList *list, char *id) {
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
    

    printf("\n---NOTAS---\n");
    while (nota_atual != NULL) {
        count++;
        printf("Nota %d - %.2f\n", count, nota_atual->nota);
        soma += nota_atual->nota;
        nota_atual = nota_atual->next;
    }

    if (count==MAX_NOTAS) {
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

void buscar_aluno_nota(DoublyLinkedList *list, char *id) {
    Aluno *aluno = list->head;
    int opcao;
    float valor;

    while (aluno != NULL){
        if (strcmp(aluno->id, id) == 0) {
            do {
                printf("\nAluno: %s\n", aluno->nome);
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
    limpar_terminal();
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

// Função auxiliar para dividir a lista em duas sublistas
void dividir_lista(Aluno* head, Aluno** front, Aluno** back){
    Aluno* slow;
    Aluno* fast;
    slow = head;
    fast = head->next;

    // Avança o ponteiro fast 2 nós e o slow 1 nó
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // Dividindo a lista em duas partes
    *front = head;
    *back = slow->next;
    slow->next = NULL; // Finaliza a primeira metade
    if (*back != NULL) {
        (*back)->prev = NULL; // Previne referências circulares
    }
}




// Função auxiliar para unir duas listas ordenadas
Aluno* merge_listas(Aluno* front, Aluno* back) {
    // Caso base: Se uma das listas está vazia, retorna a outra
    if (front == NULL) {
        return back;
    } else if (back == NULL) {
        return front;
    }

    Aluno* resultado = NULL;

    // Comparando os nomes dos alunos para ordenar alfabeticamente
    if (strcmp(front->nome, back->nome) <= 0) {
        resultado = front;
        resultado->next = merge_listas(front->next, back);
        if (resultado->next != NULL) {
            resultado->next->prev = resultado;
        }
    } else {
        resultado = back;
        resultado->next = merge_listas(front, back->next);
        if (resultado->next != NULL) {
            resultado->next->prev = resultado;
        }
    }

    return resultado;
}

// Função principal do Merge Sort
Aluno* merge_sort(Aluno* head) {
    // Caso base: Se a lista está vazia ou contém apenas 1 elemento
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Aluno* front;
    Aluno* back;

    // Dividindo a lista em duas sublistas
    dividir_lista(head, &front, &back);

    // Chamando recursivamente o merge_sort nas duas metades
    front = merge_sort(front);
    back = merge_sort(back);

    // Unindo as duas metades ordenadas
    return merge_listas(front, back);
}

void ordenar_alunos(DoublyLinkedList *list) {
    if (list->head != NULL) {
        list->head = merge_sort(list->head);

        // Atualizando a referência da tail (cauda)
        Aluno *temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        list->tail = temp;
    }
}



int main() {
    DoublyLinkedList *lista = inicializar_lista();
    int opcao;
    char id[15];
    char name[500];

    do {
        limpar_terminal();
        opcao = exibir_menu();

        switch (opcao) {
            case 1:
                limpar_terminal();
                printf("CADASTRO DE ALUNOS\nID: ");
                scanf("%18s", id);
                while(getchar() != '\n');
                
                if(verificar_quatidade_de_digitos(id)){
                 fprintf(stderr, ": O id inserido possui mais ou menos de 14 dígitos.\n");
                 sleep(1.5);
                 printf("Retornando ao menu...");
                 sleep(3.5);
                 break;
                 }
 
                printf("Nome do aluno: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; 
                inserir_aluno_no_final(lista, id, name);
                pausar_para_mensagem("");
                break;

            case 2:
                limpar_terminal();
                imprimir_lista(lista);
                pausar_para_mensagem("");
                break;

            case 3:
                printf("Insira o ID do aluno que quer excluir: ");
                scanf("%s", id);
                excluir_aluno(lista, id);
                pausar_para_mensagem("");
                break;

            case 4:
                limpar_terminal();
                printf("Insira o id do aluno: ");
                scanf("%s", id);
                buscar_aluno_nota(lista, id);
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
