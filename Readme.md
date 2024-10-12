# Sistema de Notas de Alunos 📚✏️

Este é um sistema simples para gerenciar informações de alunos e suas respectivas notas utilizando uma lista duplamente encadeada em C. O sistema permite cadastrar alunos, listar, excluir, inserir notas e visualizar as notas de cada aluno.

# Funcionalidades

   ## Cadastrar Aluno: 
      Adicione um novo aluno com um ID único e nome.

   ## Listar Alunos: 
      Veja todos os alunos cadastrados.

   ## Excluir Aluno: 
      Remova um aluno da lista.
   ## Gerenciar Notas:
        Inserir notas para cada aluno.
        Visualizar notas e calcular a média.
        Alterar notas existentes.
        Excluir notas específicas.

# Estruturas de Dados

Utiliza-se uma lista duplamente encadeada, onde cada aluno possui um ponteiro para o próximo e o anterior, além de um ponteiro para suas notas:

    Aluno: Contém o ID, nome e um ponteiro para a lista de notas.
    Nota: Contém o valor da nota e ponteiros para a próxima e anterior nota.

# Exemplo de Uso

Ao iniciar o programa, você verá um menu interativo. Basta escolher a opção desejada e seguir as instruções na tela.

```
SISTEMA DE NOTAS DE ALUNOS
1. Cadastrar aluno
2. Listar alunos
3. Excluir aluno
4. Gerenciar notas
0. Sair
Escolha uma opção:
``` 

# Tecnologias Utilizadas

    Linguagem de programação: C
    Estruturas de dados: Listas Duplamente Encadeadas

# Como Compilar e Executar

    Salve o código em um arquivo chamado sistema_notas.c.

    Compile o código usando o GCC:

```
gcc sistema_notas.c -o sistema_notas
```

# Execute o programa:

```
    ./sistema_notas
```

## Link para Vídeo Tutorial 🎥

Para um guia visual sobre como utilizar o sistema, confira este vídeo no YouTube: [Como usar o Sistema de Notas de Alunos](https://youtu.be/DaVJvFUxNQU?si=KKCmLuf8TgRMn6K8)

# Contribuições

Sinta-se à von-tade para contribuir com melhorias ou correções! 😊

# Licença

Este projeto está sob a licença MIT. Veja o arquivo LICENSE para mais informações.


