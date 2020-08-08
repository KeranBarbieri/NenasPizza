#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define SIZE 100

//VARIÁVEIS PARA O CADASTRO DE CLIENTES
typedef struct{
    char nomeCliente[200];
    char cpfCliente[200];
    char dataNasc[15];
    char telefoneCliente[10];
}Cliente;

//VARIÁVEIS PARA CADASTRO DE RECLAMAÇÕES
typedef struct{
    char nomeCliente[200];
    char Observacao[1000];
}Reclamacao;

//VARIÁVEIS PARA CADASTRO DE ELOGIOS
typedef struct{
    char nomeCliente[200];
    char Observacao[1000];
}Elogio;

//VARIÁVEIS PARA O CADASTRO DE FUNCIONARIOS
typedef struct{
    char nomeFuncionario[200];
    char cargoFuncionario[200];
    char dataNasc[15];
    char salarioFuncionario[50];
    char cpfFuncionario[200];
    char telefoneFuncionario[200];
    char rgFuncionario[200];
}Funcionario;

//VARIÁVEIS PARA PRODUTOS
typedef struct{
    char nome[100];
    char fornecedor[100];
    char categoria[100];
    int qtde;
    float valorUnitario;
}Produto;

//VARIÁVEIS PARA FAZER PEDIDO DE PIZZA OU PARA CADASTRAR +PIZZAS
typedef struct{
    int id;
    char sabor[80];
    float preco;
}Pizza;

//VARIÁVEIS PARA FAZER PEDIDO DE BEBIDAS OU PARA CADASTRAR +BEBIDAS
typedef struct{
    int id;
    char bebida[60];
    char marca[50];
    float preco;
}Bebida;

//OPERADOR GLOBAL USO GERAL
char dataDiario[8];
int op;
int comandasCanceladas;
int comandasFinalizadas;
float valorTotal;

//PARAMETRO SEM RETORNO - PEDE PARA USUÁRIO INSERIR DADOS
void menu(); //MENU
void cardapio(); //CARDAPIO DA PIZZARIA
void fazerPedido(); //FUNÇÃO PARA FAZER OS PEDIDIOS
void cadastroCliente(); //CADASTRO DE CLIENTE
void cadastroFuncionario(); //CADASTRO DE FUNCIONARIOS
void fazerElogios(); //CADASTRAR ELOGIOS OU LER
void listaCadastros(); //CADASTRO DE CLIENTES E FUNCIONARIOS
void fazerReclamacoes(); //CADASTRAR ELOGIOS OU LER
void Estoques(); //GERENCIADOR DE ESTOQUE
void cadastrarProduto(); //CADASTRA OS PRODUTOS DENTRO DE ESTOQUE
void listarProdutos(); //MOSTRA TUDO O QUE TEM DENTRO DE ESTOQUE

//COMEÇO DO PROGRAMA
void main(){
    setlocale(LC_ALL, "Portuguese");
    Cliente clientes[SIZE];
    Funcionario funcionarios[SIZE];
    Elogio elogios[SIZE];
    Reclamacao reclamacoes[SIZE];
    Produto produtos[SIZE];
    Pizza pizzas[SIZE];

    printf("Data (ex. 01/01/01): "); //SOLICITA QUE O USUÁRIO INSIRA A DATA
    gets(dataDiario);
    fflush(stdin);

    menu(clientes, funcionarios, elogios, reclamacoes, produtos, pizzas); //APRESENTA O MENU INICIAL
}

//CARPÁPIO DE BEBIDAS
void bebida_cardapio(Bebida bebidas[SIZE]){
    FILE *bebidas_cardapio;
    int i = 0;
    bebidas_cardapio = fopen("Estoque//CardapioBebida.txt", "rt");

    if(!bebidas_cardapio){
        printf("ERRO");
        getch();
        exit(1);
    }

        printf("\t\t _______________________________________________________________________\n");
        printf("\t\t|                        CARDÁPIO DE BEBIDAS                               |\n");
        printf("\t\t|-----------------------------------------------------------------------|\n");
        while(!feof(bebidas_cardapio)){
            fscanf(bebidas_cardapio, "%d", &bebidas[i].id);
            printf("\t\t| Código: %d\n", bebidas[i].id);

            fscanf(bebidas_cardapio, "%s", &bebidas[i].marca);
            printf("\t\t| Marca: %s\n", bebidas[i].marca);

            fscanf(bebidas_cardapio, "%s", &bebidas[i].bebida);
            printf("\t\t| Bebida: %s\n", bebidas[i].bebida);

            fscanf(bebidas_cardapio, "%f", &bebidas[i].preco);
            printf("\t\t| Preço: %.2f\n", bebidas[i].preco);
            printf("\t\t|=======================================================================|\n");
            i++;
        }
        fclose(bebidas_cardapio);
}

//CARDÁPIO DE PIZZAS
void pizza_cardapio(Pizza pizzas[SIZE]){
    FILE *pizzas_cardapio;
    int i = 0;
    pizzas_cardapio = fopen("Estoque//CardapioPizza.txt", "rt");

    if(!pizzas_cardapio){
        printf("ERRO");
        getch();
        exit(1);
    }

        printf("\t\t _______________________________________________________________________\n");
        printf("\t\t|                         CARDÁPIO DE PIZZAS                               |\n");
        printf("\t\t|-----------------------------------------------------------------------|\n");
        while(!feof(pizzas_cardapio)){
            fscanf(pizzas_cardapio, "%d", &pizzas[i].id);
            printf("\t\t| Código: %d\n", pizzas[i].id);

            fscanf(pizzas_cardapio, "%s", &pizzas[i].sabor);
            printf("\t\t| Sabor: %s\n", pizzas[i].sabor);

            fscanf(pizzas_cardapio, "%f", &pizzas[i].preco);
            printf("\t\t| Preço: %.2f\n", pizzas[i].preco);
            printf("\t\t|=======================================================================|\n");
            i++;
        }
    fclose(pizzas_cardapio);
}


//SUB-MENU CARDÁPIOS
void cardapio(Pizza pizzas[SIZE], Bebida bebidas[SIZE]){
    FILE *pizzas_cardapio, *bebidas_cardapio;
    int i = 0;

    pizzas_cardapio = fopen("Estoque//CardapioPizza.txt", "rt");
    bebidas_cardapio = fopen("Estoque//CardapioBebida.txt", "rt");

    if(!pizzas_cardapio){
        printf("ERRO");
        getch();
        exit(1);
    }

    if(!bebidas_cardapio){
        printf("ERRO");
        getch();
        exit(1);
    }

    printf("\t\t __________________________________\n");
    printf("\t\t|             CARDÁPIOS            |\n");
    printf("\t\t|----------------------------------|\n");
    printf("\t\t| 1 - Cardápio de Pizzas.          |\n");
    printf("\t\t| 2 - Cardápio de Bebidas.         |\n");
    printf("\t\t|__________________________________|\n");
    scanf("%d", &op);


    switch(op){
    case 1:
        i = 0;
        printf("\t\t _______________________________________________________________________\n");
        printf("\t\t|                         CARDÁPIO DE PIZZAS                            |\n");
        printf("\t\t|-----------------------------------------------------------------------|\n");
        while(!feof(pizzas_cardapio)){
            fscanf(pizzas_cardapio, "%d", &pizzas[i].id);
            printf("\t\t| Código: %d\n", pizzas[i].id);

            fscanf(pizzas_cardapio, "%s", &pizzas[i].sabor);
            printf("\t\t| Sabor: %s\n", pizzas[i].sabor);

            fscanf(pizzas_cardapio, "%f", &pizzas[i].preco);
            printf("\t\t| Preço: %.2f\n", pizzas[i].preco);
            printf("\t\t|=======================================================================|\n");
            i++;
        }
        printf("\t\t|_______________________________________________________________________|\n");
        fclose(pizzas_cardapio);
        fclose(bebidas_cardapio);
        break;
    case 2:
        i = 0;
        printf("\t\t _______________________________________________________________________\n");
        printf("\t\t|                       CARDÁPIO DE BEBIDAS                               |\n");
        printf("\t\t|-----------------------------------------------------------------------|\n");
        while(!feof(bebidas_cardapio)){
            fscanf(bebidas_cardapio, "%d", &bebidas[i].id);
            printf("\t\t| Código: %d\n", bebidas[i].id);

            fscanf(bebidas_cardapio, "%s", &bebidas[i].marca);
            printf("\t\t| Marca: %s\n", bebidas[i].marca);

            fscanf(bebidas_cardapio, "%s", &bebidas[i].bebida);
            printf("\t\t| Bebida: %s\n", bebidas[i].bebida);

            fscanf(bebidas_cardapio, "%f", &bebidas[i].preco);
            printf("\t\t| Preço: %.2f\n", bebidas[i].preco);
            printf("\t\t|=======================================================================|\n");
            i++;
        }

        printf("\t\t|_______________________________________________________________________|\n");
        fclose(pizzas_cardapio);
        fclose(bebidas_cardapio);
        break;
    default:
        printf("Opção Inválida\nEscolha 1 Para visualizar Cardápio de Pizzas\nEscolha 2 para visualizar o Cardapio de Bebidas\n");
        system("pause");
        system("cls");
        return cardapio(pizzas, bebidas);
        break;
    }
}


// SUB-MENU FAZER PEDIDOS
void fazerPedido(Pizza pizzas[SIZE], Bebida bebidas[SIZE]){
    FILE *pedido_comanda;
    char nomeComanda[50];
    int id;

    do{
        printf("\t\t _______________________________________________________________________\n");
        printf("\t\t|                         MENU DE PEDIDOS                               |\n");
        printf("\t\t|-----------------------------------------------------------------------|\n");
        printf("\t\t| 1 - Pedido de Pizzas.     \t\t\t\t\t\t|\n");
        printf("\t\t| 2 - Pedido de Bebidas.    \t\t\t\t\t\t|\n");
        printf("\t\t| 0 - Sair.                 \t\t\t\t\t\t|\n");
        printf("\t\t|_______________________________________________________________________|\n");
        scanf("%d", &op);

        switch(op){
        case 1: //FAZER PEDIDO DE PIZZAS
            printf("\t\t > Digite o nome da comanda: ");
            fflush(stdin);
            gets(nomeComanda);
            pedido_comanda = fopen(nomeComanda, "a+");

            if(!pedido_comanda){
                printf("ERRO");
                getch();
                exit(1);
            }
            pizza_cardapio(pizzas); //INFORMA AO USUÁRIO O CARDÁPIO SOMENTE DAS PIZZAS E FAZ COM QUE AS VARIÁVEIS ENTREM NA STRUCT

            printf("\t\t > Digite o cÓdigo da pizza: ");
            scanf("%d", &id);

            for(int i = 0; i < id; i++){
                if(id == pizzas[i].id){
                    printf("\t\t _______________________________________________________________________\n");
                    printf("\t\t|                        PEDIDOS DE PIZZAS                              |\n");
                    printf("\t\t|-----------------------------------------------------------------------|\n");
                    printf("\t\t| Comanda: %s.\n", nomeComanda);
                    printf("\t\t| Pizza: %s.\n", pizzas[i].sabor);
                    printf("\t\t| Preço: %.2f\n", pizzas[i].preco);
                    printf("\t\t|                                                                       |\n");
                    printf("\t\t| Confirmar Pedido ?                                                     |\n");
                    printf("\t\t| Digite 1 para SIM.                                                    |\n");
                    printf("\t\t| Digite 2 para NÃO.                                                    |\n");
                    printf("\t\t|_______________________________________________________________________|\n");
                    scanf("%d", &op);
                    if(op == 1){
                        fprintf(pedido_comanda, "%s\n%.2f\n", pizzas[i].sabor, pizzas[i].preco);

                        valorTotal = valorTotal + pizzas[i].preco; //CÁLCULO TOTAL DAS PIZZAS
                        comandasFinalizadas++;; //SOMANDO TOTAL DE COMANDAS FEITAS
                    }
                }
            }
            fclose(pedido_comanda);
            break;
        case 2: //FAZER PEDIDO DE BEBIDAS
            printf("\t\t > Digite o nome da comanda: ");
            fflush(stdin);
            gets(nomeComanda);
            pedido_comanda = fopen(nomeComanda, "a+");

            if(!pedido_comanda){
                printf("ERRO");
                getch();
                exit(1);
            }
            bebida_cardapio(bebidas); //INFORMA AO USUÁRIO O CARDÁPIO SOMENTE DAS BEBIDAS E FAZ COM QUE AS VARIÁVEIS ENTREM NA STRUCT

            printf("\t\t > Digite o código da bebida: ");
            scanf("%d", &id);

            for(int i = 0; i < id; i++){
                if(id == bebidas[i].id){
                    printf("\t\t _______________________________________________________________________\n");
                    printf("\t\t|                       PEDIDOS DE BEBIDAS                              |\n");
                    printf("\t\t|-----------------------------------------------------------------------|\n");
                    printf("\t\t| Comanda: %s.\n", nomeComanda);
                    printf("\t\t| Bebida: %s.\n", bebidas[i].bebida);
                    printf("\t\t| Marca: %s.\n", bebidas[i].marca);
                    printf("\t\t| Preço: %.2f\n", bebidas[i].preco);
                    printf("\t\t|                                                                       |\n");
                    printf("\t\t| Confirmar Pedido ?                                                     |\n");
                    printf("\t\t| Digite 1 para SIM.                                                    |\n");
                    printf("\t\t| Digite 2 para NÃO.                                                    |\n");
                    printf("\t\t|_______________________________________________________________________|\n");
                    scanf("%d", &op);
                    if(op == 1){
                        fprintf(pedido_comanda, "%s\n%s\n%.2f", bebidas[i].bebida, bebidas[i].marca, bebidas[i].preco);

                        valorTotal = valorTotal + bebidas[i].preco; //CALCULO TOTAL DAS BEBIDAS
                        comandasFinalizadas++; //SOMANDO TOTAL DE COMANDAS FEITAS
                    }

                }
            }
            fclose(pedido_comanda);
            break;
        }
    }while(op != 0);
}


//CADASTRO DE CLIENTES
void cadastroCliente(Cliente clientes[SIZE]){
    static int linha;
    FILE *p2;

    p2 = fopen("Cadastros//ClientesLista.txt", "a+");
    if(!p2){
        printf("ERRO, POSSIVELMENTE MEMÓRIA CHEIA!");
        getch();
        exit(1);
    }

    do{
        fflush(stdin);
        printf("\t\t _______________________________________________________________________\n");
        printf("\t\t|                            CADASTRO DE CLIENTE                        |\n");
        printf("\t\t|-----------------------------------------------------------------------|\n");
        printf("\t\t|\tNome...................: ");
        gets(clientes[linha].nomeCliente);
        fprintf(p2, "| Nome...................: %s\n", clientes[linha].nomeCliente);

        printf("\t\t|\tCPF....................: ");
        scanf("%s", clientes[linha].cpfCliente);
        fprintf(p2, "| CPF....................: %s\n", clientes[linha].cpfCliente);

        printf("\t\t|\tData de Nascimento.....: ");
        scanf("%s", clientes[linha].dataNasc);
        fprintf(p2, "| Data Nascimento........: %s\n", clientes[linha].dataNasc);

        fflush(stdin);
        printf("\t\t|\tTelefone...............: ");
        scanf("%s", clientes[linha].telefoneCliente);
        fprintf(p2, "| Telefone...............: %s\n", clientes[linha].telefoneCliente);
        fprintf(p2, "|=======================================================================\n");
        fflush(stdin);
        printf("\t\t|\tDigite 1 para +CADASTRO.                                        |\n");
        printf("\t\t|\tDigite outro valor para SAIR.                                   |\n");
        printf("\t\t|_______________________________________________________________________|\n");
        scanf("%d", &op);
        linha++;
    }while(op == 1);

    fclose(p2);
    printf("\t\t\t    ______________________________________________\n");
    printf("\t\t\t   |\t    CADASTRO SALVO COM SUCESSO. . .\t  |\n ");
    printf("\t\t\t   |______________________________________________|\n");
}


//CADASTRO DE FUNCIONÁRIOS
void cadastroFuncionario(Funcionario funcionarios[SIZE]){
    FILE *p;
    static int linha;

    p = fopen("Cadastros//FuncionáriosLista.txt", "a+");

    if(!p){
        printf("ERRO AO ABRIR ARQUIVO. FIM DO PROGRAMA!");
        getch();
        exit(1);
    }

    do{
        fflush(stdin);
        printf("\t\t _______________________________________________________________________\n");
        printf("\t\t|                       CADASTRO DE FUNCIONÁRIOS                        |\n");
        printf("\t\t|-----------------------------------------------------------------------|\n");
        printf("\t\t|\tNome...................: ");
        gets(funcionarios[linha].nomeFuncionario);
        fprintf(p, "| Nome....................: %s\n", funcionarios[linha].nomeFuncionario);


        printf("\t\t|\tData de Nascimento.....: ");
        scanf("%s", funcionarios[linha].dataNasc);
        fprintf(p, "| Data Nascimento.........: %s\n", funcionarios[linha].dataNasc);

        printf("\t\t|\tCPF....................: ");
        scanf("%s", &funcionarios[linha].cpfFuncionario);
        fflush(stdin);
        fprintf(p, "| CPF.....................: %s\n", funcionarios[linha].cpfFuncionario);

        printf("\t\t|\tRG.....................: ");
        scanf("%s", &funcionarios[linha].rgFuncionario);
        fflush(stdin);
        fprintf(p, "| RG......................: %s\n", funcionarios[linha].rgFuncionario);

        printf("\t\t|\tTelefone...............: ");
        scanf("%s", &funcionarios[linha].telefoneFuncionario);
        fflush(stdin);
        fprintf(p, "| Telefone................: %s\n", funcionarios[linha].telefoneFuncionario);

        printf("\t\t|\tCargo..................: ");
        gets(funcionarios[linha].cargoFuncionario);
        fflush(stdin);
        fprintf(p, "| Cargo...................: %s\n", funcionarios[linha].cargoFuncionario);

        printf("\t\t|\tSalário................: ");
        scanf("%s", &funcionarios[linha].salarioFuncionario);
        fflush(stdin);
        fprintf(p, "| Salário.................: %s\n", funcionarios[linha].salarioFuncionario);
        fprintf(p, "|=======================================================================\n");
        fflush(stdin);
        printf("\t\t|\tDigite 1 para +CADASTRO.                                        |\n");
        printf("\t\t|\tDigite outro valor para SAIR.                                   |\n");
        printf("\t\t|_______________________________________________________________________|\n");
        scanf("%d", &op);
        linha++;
    }while(op == 1);

    printf("\t\t\t    ______________________________________________\n");
    printf("\t\t\t   |\t   CADASTRO SALVO COM SUCESSO. . .\t  |\n ");
    printf("\t\t\t   |______________________________________________|\n");
    fclose(p);
}


//LISTA DE CADASTROS
void listaCadastros(Cliente clientes[SIZE], Funcionario funcionarios[SIZE]){
    int i;
    FILE *p1, *p2;

    p1 = fopen("Cadastros//ClientesLista.txt", "rt");
    p2 = fopen("Cadastros//FuncionáriosLista.txt", "rt");

    if(!p1){
        printf("ERRO AO ABRIR ARQUIVO. FIM DO PROGRAMA!");
        getch();
        exit(1);
    }

    if(!p2){
        printf("ERRO AO ABRIR ARQUIVO. FIM DO PROGRAMA!");
        getch();
        exit(1);
    }

    printf("\t\t __________________________________\n");
    printf("\t\t|             CADASTROS            |\n");
    printf("\t\t|----------------------------------|\n");
    printf("\t\t| 1 - Lista de Funcionários.       |\n");
    printf("\t\t| 2 - Lista de Clientes.           |\n");
    printf("\t\t|__________________________________|\n");
    scanf("%d", &op);

    if(op == 1){
        char FileFuncionario[200];
            printf("\t\t  _______________________________________________________________________\n");
            printf("\t\t |                        FUNCIONÁRIOS ENCONTRADOS                        |\n");
            printf("\t\t |-----------------------------------------------------------------------|\n");
        while(fgets(FileFuncionario, 200, p2)){
            printf("\t\t %s", FileFuncionario);
        }
    }
    if(op == 2){
        char FileCliente[200];
            printf("\t\t  _______________________________________________________________________\n");
            printf("\t\t |                            CLIENTES ENCONTRADOS                        |\n");
            printf("\t\t |-----------------------------------------------------------------------|\n");
        while(fgets(FileCliente, 200, p1)){
            printf("\t\t %s", FileCliente);
        }
    }
    fclose(p1);
    fclose(p2);
}


//FAZER E LISTAR  ELOGIOS
void fazerElogios(Elogio elogios[SIZE]){
    FILE *p, *p1;
    int i = 0;

    p = fopen("Criticas//ElogiosLista.txt", "at");
    p1 = fopen("Criticas//ElogiosLista.txt", "rt");

    if(!p){
        printf("ERRO AO ABRIR ARQUIVO. FIM DO PROGRAMA!");
        getch();
        exit(1);
    }
    if(!p1){
        printf("ERRO AO ABRIR ARQUIVO. FIM DO PROGRAMA!");
        getch();
        exit(1);
    }

    printf("\t\t __________________________________\n");
    printf("\t\t|              ELOGIOS             |\n");
    printf("\t\t|----------------------------------|\n");
    printf("\t\t| 1 - Cadastrar Elogios.           |\n");
    printf("\t\t| 2 - Visualizar Elogios.          |\n");
    printf("\t\t|__________________________________|\n");
    scanf("%d", &op);

    if(op == 1){
        do{
            fflush(stdin);
            printf("\t\t  _______________________________________________________________________\n");
            printf("\t\t |                            CADASTRAR ELOGIOS                          |\n");
            printf("\t\t |-----------------------------------------------------------------------|\n");
            printf("\t\t |\tNome do Cliente: ");
            gets(elogios[i].nomeCliente);
            fprintf(p, "| Nome..: %s\n", elogios[i].nomeCliente);
            fflush(stdin);
            printf("\t\t |\tElogio.........: ");
            gets(elogios[i].Observacao);
            fprintf(p, "| Elogio: %s\n", elogios[i].Observacao);
            fprintf(p, "|========================================================================|\n");
            fflush(stdin);
            printf("\t\t |                                                                       |\n");
            printf("\t\t |\tDigite 1 para +ELOGIOS.                                          |\n");
            printf("\t\t |\tDigite outro valor para SAIR.                                    |\n");
            printf("\t\t |_______________________________________________________________________|\n");
            scanf("%d", &op);
            i++;
        }while(op == 1);
    }
    if(op == 2){
        char FileElogios[200];
            printf("\t\t  ________________________________________________________________________\n");
            printf("\t\t |                            LISTA DE ELOGIOS                            |\n");
            printf("\t\t |------------------------------------------------------------------------|\n");
        while(fgets(FileElogios, 200, p1)){
            printf("\t\t %s", FileElogios);
        }
    }
    fclose(p1);
    fclose(p);
}


//FAZER E LISTAR RECLAMAÇÕES
void fazerReclamacoes(Reclamacao reclamacoes[SIZE]){
    FILE *p, *p1;
    int i = 0;

    p = fopen("Criticas//ReclamaçõesLista.txt", "at");
    p1 = fopen("Criticas//ReclamaçõesLista.txt", "rt");

    if(!p){
        printf("ERRO AO ABRIR ARQUIVO. FIM DO PROGRAMA!");
        getch();
        exit(1);
    }
    if(!p1){
        printf("ERRO AO ABRIR ARQUIVO. FIM DO PROGRAMA!");
        getch();
        exit(1);
    }

    printf("\t\t __________________________________\n");
    printf("\t\t|           RECLAMAÇÕES            |\n");
    printf("\t\t|----------------------------------|\n");
    printf("\t\t| 1 - Cadastrar Reclamações.       |\n");
    printf("\t\t| 2 - Visualizar Reclamações.      |\n");
    printf("\t\t|__________________________________|\n");
    scanf("%d", &op);

    if(op == 1){
        do{
            fflush(stdin);
            printf("\t\t  _______________________________________________________________________\n");
            printf("\t\t |                        CADASTRAR RECLAMAÇÕES                          |\n");
            printf("\t\t |-----------------------------------------------------------------------|\n");
            printf("\t\t |\tNome do Cliente...: ");
            gets(reclamacoes[i].nomeCliente);
            fprintf(p, "| Nome......: %s\n", reclamacoes[i].nomeCliente);
            fflush(stdin);
            printf("\t\t |\tReclamação.........: ");
            gets(reclamacoes[i].Observacao);
            fprintf(p, "| Reclamação: %s\n", reclamacoes[i].Observacao);
            fprintf(p, "|========================================================================|\n");
            fflush(stdin);
            printf("\t\t |                                                                       |\n");
            printf("\t\t |\tDigite 1 para +RECLAMAÇÕES.                                      |\n");
            printf("\t\t |\tDigite outro valor para SAIR.                                    |\n");
            printf("\t\t |_______________________________________________________________________|\n");
            scanf("%d", &op);
            i++;
        }while(op == 1);
    }
    if(op == 2){
        char FileReclamacoes[200];
            printf("\t\t  ________________________________________________________________________\n");
            printf("\t\t |                        LISTA DE RECLAMAÇÕES                            |\n");
            printf("\t\t |------------------------------------------------------------------------|\n");
        while(fgets(FileReclamacoes, 200, p1)){
            printf("\t\t %s", FileReclamacoes);
        }
    }
    fclose(p1);
    fclose(p);
}


//GERENCIARDOR DE ESTOQUE
void Estoques(Produto produtos[SIZE]){
    int i = 1;
    do{
        fflush(stdin);
        printf("\t\t _______________________________________________________________________\n");
        printf("\t\t|                         GERENCIADOR DE ESTOQUE                        |\n");
        printf("\t\t|-----------------------------------------------------------------------|\n");
        printf("\t\t| 1 - Cadastrar um produto.          \t\t\t\t\t|\n");
        printf("\t\t| 2 - Listar todos os produtos.      \t\t\t\t\t|\n");
        printf("\t\t| 3 - Cadastrar +PIZZAS.             \t\t\t\t\t|\n");
        printf("\t\t| 4 - Cadastrar +BEBIDAS.            \t\t\t\t\t|\n");
        printf("\t\t| 0 - Sair.                          \t\t\t\t\t|\n");
        printf("\t\t|_______________________________________________________________________|\n");
        scanf("%d", &op);

        switch(op){
        case 1:
                cadastrarProduto(produtos);
            break;
        case 2:
                listarProdutos(produtos);
            break;
        case 3:
                cadastrarPizza();
            break;
        case 4:
                cadastrarBebida();
            break;
        case 0:
                printf("\t\t\t\t _____________________________________\n");
                printf("\t\t\t\t|\t  VOLTANDO PARA O MENU\t      |\n ");
                printf("\t\t\t\t|_____________________________________|\n");
            break;
        }
        system("pause");
    }while(op != 0);

}


//CADASTRO DE PRODUTOS
void cadastrarProduto(){
    FILE *p;
    Produto produtos[SIZE];
    int i = 0;

    p = fopen("Estoque//EstoqueProdutos.txt", "a+");

    if(!p){
        printf("ERRO");
        getch();
        exit(1);
    }

    do{
        fflush(stdin);
        printf("\t\t _______________________________________________________________________\n");
        printf("\t\t|                           CADASTRO DE PRODUTOS                        |\n");
        printf("\t\t|-----------------------------------------------------------------------|\n");
        printf("\t\t|\tProduto..............: ");
        gets(produtos[i].nome);
        fprintf(p, "| Produto...............: %s\n", produtos[i].nome);
        fflush(stdin);

        printf("\n\t\t|\tFornecedor...........: ");
        gets(produtos[i].fornecedor);
        fprintf(p, "| Fornecedor............: %s\n", produtos[i].fornecedor);
        fflush(stdin);

        printf("\n\t\t|\tCategoria............: ");
        gets(produtos[i].categoria);
        fprintf(p, "| Categoria.............: %s\n", produtos[i].categoria);
        fflush(stdin);

        printf("\n\t\t|\tQuantidade em estoque: ");
        scanf("%d", &produtos[i].qtde);
        fprintf(p, "| Quantidade em Estoque.: %d\n", produtos[i].qtde);
        fflush(stdin);

        printf("\n\t\t|\tValor Unitario.......: ");
        scanf("%f", &produtos[i].valorUnitario);
        fprintf(p, "| Valor Unitario........: %f\n", produtos[i].valorUnitario);
        fprintf(p, "|=======================================================================|\n");
        fflush(stdin);
        printf("\t\t|\tDigite 1 para +PRODUTOS.                                        |\n");
        printf("\t\t|\tDigite outro valor para SAIR.                                   |\n");
        printf("\t\t|_______________________________________________________________________|\n");
        scanf("%d", &op);
        i++;
    }while(op == 1);

    printf("\t\t\t    ______________________________________________\n");
    printf("\t\t\t   |\t    PRODUTOS SALVOS COM SUCESSO. . .\t  |\n ");
    printf("\t\t\t   |______________________________________________|\n");
    fclose(p);
    system("pause");
    system("cls");
}


//LISTAR PRODUTOS EM ESTOQUE
void listarProdutos(Produto produtos[SIZE]){
    FILE *p;

    p = fopen("Estoque//EstoqueProdutos.txt", "rt");

    if(!p){
        printf("ERRO");
        getch();
        exit(1);
    }

    char FileProduto[200];
        printf("\t\t _______________________________________________________________________\n");
        printf("\t\t|                        PRODUTOS EM ESTOQUE                            |\n");
        printf("\t\t|-----------------------------------------------------------------------|\n");
    while(fgets(FileProduto, 200, p)){
        printf("\t\t%s", FileProduto);
    }
    fclose(p);
    system("pause");
    system("cls");
}


//CADASTRAR + PIZZAS
void cadastrarPizza(){
    FILE *p;
    Pizza pizzas[SIZE];
    int i = 0;

    p = fopen("Estoque//CardapioPizza.txt", "a+");

    if(!p){
        printf("ERRO");
        getch();
        exit(1);
    }

    do{
        fflush(stdin);
        printf("\t\t _______________________________________________________________________\n");
        printf("\t\t|                            CADASTRO DE PIZZAS                        |\n");
        printf("\t\t|-----------------------------------------------------------------------|\n");
        printf("\t\t|\tCadigo: ");
        scanf("%d", &pizzas[i].id);
        fprintf(p, "\n%d\t", pizzas[i].id);
        fflush(stdin);

        printf("\t\t|\tSabor: ");
        scanf("%s", &pizzas[i].sabor);
        fprintf(p, "%s\t", pizzas[i].sabor);
        fflush(stdin);

        printf("\t\t|\tPreço......................: ");
        scanf("%f", &pizzas[i].preco);
        fprintf(p, "\t%f", pizzas[i].preco);
        fflush(stdin);

        printf("\t\t|\tDigite 1 para +PIZZAS.                                          |\n");
        printf("\t\t|\tDigite outro valor para SAIR.                                   |\n");
        printf("\t\t|_______________________________________________________________________|\n");
        scanf("%d", &op);
        i++;
    }while(op == 1);
    printf("\t\t\t    ______________________________________________\n");
    printf("\t\t\t   |\t      PIZZAS SALVAS COM SUCESSO. . .\t  |\n ");
    printf("\t\t\t   |______________________________________________|\n");
    fclose(p);
    system("pause");
    system("cls");
}


//CADASTRAR + BEBIDAS
void cadastrarBebida(){
    FILE *p;
    Bebida bebidas[SIZE];
    int i = 0;
    p = fopen("Estoque//CardapioBebida.txt", "a+");

    if(!p){
        printf("ERRO");
        getch();
        exit(1);
    }

    do{
        fflush(stdin);
        printf("\t\t _______________________________________________________________________\n");
        printf("\t\t|                           CADASTRO DE BEBIDAS                         |\n");
        printf("\t\t|-----------------------------------------------------------------------|\n");
        printf("\t\t|\tCodigo: ");
        scanf("%d", &bebidas[i].id);
        fprintf(p, "%d\t", bebidas[i].id);
        fflush(stdin);

        printf("\t\t|\tMarca: ");
        gets(bebidas[i].marca);
        fprintf(p, "%s\t", bebidas[i].marca);
        fflush(stdin);

        printf("\t\t|\tBebida: ");
        gets(bebidas[i].bebida);
        fprintf(p, "%s\t", bebidas[i].bebida);
        fflush(stdin);

        printf("\t\t|\tPreço: ");
        scanf("%f", &bebidas[i].preco);
        fprintf(p, "%f\n", bebidas[i].preco);
        fflush(stdin);
        printf("\t\t|\tDigite 1 para +BEBIDAS.                                         |\n");
        printf("\t\t|\tDigite outro valor para SAIR.                                   |\n");
        printf("\t\t|_______________________________________________________________________|\n");
        scanf("%d", &op);
        i++;
    }while(op == 1);
    printf("\t\t\t    ______________________________________________\n");
    printf("\t\t\t   |\t     BEBIDAS SALVAS COM SUCESSO. . .\t  |\n ");
    printf("\t\t\t   |______________________________________________|\n");
    fclose(p);
    system("pause");
    system("cls");
}


//RELATÓRIOS
void relatorio(){
    FILE *mensal;
    FILE *diario;

    diario = fopen(dataDiario, "wt");
    mensal = fopen("Relatorio//Relatorio.txt", "at");

   if(!diario){
        printf("ERRO");
        getch();
        exit(1);
   }
   if(!mensal){
        printf("ERRO");
        getch();
        exit(1);
   }

    fprintf(diario, "%d\n%d\n%f", comandasCanceladas, comandasFinalizadas, valorTotal); //COLOCANDO OS VALORES NO RELATORIO DIARIO COM A DATA QUE O USUARIO DIGITAR NO MAIN
    fprintf(mensal, "%d\n%d\n%f\n", comandasCanceladas, comandasFinalizadas, valorTotal); //COLOCANDO OS VALORES NO RELATORIO MENSAL

    fclose(diario);
    fclose(mensal);

}
void menu(Bebida bebidas[SIZE], Pizza pizzas[SIZE], Cliente clientes[SIZE], Funcionario funcionarios[SIZE], Elogio elogios[SIZE], Reclamacao reclamacoes[SIZE], Produto produtos[SIZE]){

   do{
        fflush(stdin);
        system("cls");
        printf("\t\t_______________________________________________________________________________________\n");
        printf("\t\t|\t\t                                                             \t\t|\n");
        printf("\t\t|\t\t                                                             \t\t|\n");
        printf("\t\t|\t\t                                                             \t\t|\n");
        printf("\t\t|\t\t                                           d8b               \t\t|\n");
        printf("\t\t|\t\t  888b    88 88888888 888b    88 8888888888 Tb 8888888888    \t\t|\n");
        printf("\t\t|\t\t  888b    88 d8P      888b    88 88b    d88 Y  d888888888    \t\t|\n");
        printf("\t\t|\t\t  88 888  88 d8P      88 888  88 88b    d88     d8P          \t\t|\n");
        printf("\t\t|\t\t  88  8P  88 d8P8888  88  8P  88 88b    d88      d8P         \t\t|\n");
        printf("\t\t|\t\t  88   8P8 8 d8P8888  88   8P8 8 8888888888       d8P        \t\t|\n");
        printf("\t\t|\t\t  88    8P8  d8P      88    8P8  8888888888        d8P       \t\t|\n");
        printf("\t\t|\t\t  88     8P8 d8P      88     8P8 88      88   888888888      \t\t|\n");
        printf("\t\t|\t\t  88     888 88888888 88     888 88      88  888888888b      \t\t|\n");
        printf("\t\t|\t\t                                                             \t\t|\n");
        printf("\t\t|\t\t                                                             \t\t|\n");
        printf("\t\t|\t\t                                                             \t\t|\n");
        printf("\t\t|\t\t           d8b                                               \t\t|\n");
        printf("\t\t|\t\t           Y8P                                               \t\t|\n");
        printf("\t\t|\t\t                                                             \t\t|\n");
        printf("\t\t|\t\t  88888b.  888 888888888 888888888  88888b.    \t\t\t\t|\n");
        printf("\t\t|\t\t  888  88b 888     d88P      d88P       88b    \t\t\t\t|\n");
        printf("\t\t|\t\t  888  888 888    d88P      d88P   .d888888    \t\t\t\t|\n");
        printf("\t\t|\t\t  888 d8P  888   d88P      d88P    888  888    \t\t\t\t|\n");
        printf("\t\t|\t\t  88888P   888 888888888 888888888  Y888888    \t\t\t\t|\n");
        printf("\t\t|\t\t  888    \t\t\t\t\t\t\t\t|\n");
        printf("\t\t|\t\t  888    \t\t\t\t\t\t\t\t|\n");
        printf("\t\t|\t\t  888    \t\t\t\t\t\t\t\t|\n");
        printf("\t\t|\t\t                             ,(   `-.  \t\t\t\t\t|\n");
        printf("\t\t|\t\t                           ,': `.    `.\t\t\t\t\t|\n");
        printf("\t\t|\t\t                         ,`  *   `-.    ` .  \t\t\t\t|\n");
        printf("\t\t|\t\t                       ,`  ` :+  =  ` .    `\t\t\t\t|\n");
        printf("\t\t|\t\t                      ,~  (O):  .,     `.    .\t\t\t\t|\n");
        printf("\t\t|\t\t                    ,'  ; :   ,(__)   X;`.    )\t\t\t\t|\n");
        printf("\t\t|\t\t                   '  :'  itz  ;    ;  ;  _`,- \t\t\t\t|\n");
        printf("\t\t|\t\t                 .'O  ; = _' C ;   ;`_,_ ;\t\t\t\t|\n");
        printf("\t\t|\t\t               ,;  _;     ` : ;   _ -'   i'\t\t\t\t|\n");
        printf("\t\t|\t\t             ,`  `;(_)  0  ;   ','         \t\t\t\t|\n");
        printf("\t\t|\t\t           .' ;6      ; ' ,-'~         \t\t\t\t\t|\n");
        printf("\t\t|\t\t          '  Q  ,& ;' ,-.              \t\t\t\t\t|\n");
        printf("\t\t|\t\t       ,(  :` ; _,-'~  ;               \t\t\t\t\t|\n");
        printf("\t\t|\t\t      ,~. `C _','                      \t\t\t\t\t|\n");
        printf("\t\t|\t\t    .';^_,-'                           \t\t\t\t\t|\n");
        printf("\t\t|\t\t  ,'_;-''                             \t\t\t\t\t|\n");
        printf("\t\t|\t\t ,,~                                   \t\t\t\t\t|\n");
        printf("\t\t|\t\ti'                                   \t\t\t\t\t|\n");
        printf("\t\t|\t\t:                                     \t\t\t\t\t|\n");
        printf("\t\t|\t\t                                \t\t\t\t\t|\n");
        printf("\t\t|\t\t _______________________________________\t\t\t\t|\n");
        printf("\t\t|\t\t|             Central de Suporte        |\t\t\t\t|\n");
        printf("\t\t|\t\t|---------------------------------------|\t\t\t\t|\n");
        printf("\t\t|\t\t|  1 - Ver Cardápio.                    |\t\t\t\t|\n");
        printf("\t\t|\t\t|  2 - Fazer Pedidos.                   |\t\t\t\t|\n");
        printf("\t\t|\t\t|  3 - Cadastrar Cliente.               |\t\t\t\t|\n");
        printf("\t\t|\t\t|  4 - Cadastrar Funcionário.           |\t\t\t\t|\n");
        printf("\t\t|\t\t|  5 - Lista de Cadastro.               |\t\t\t\t|\n");
        printf("\t\t|\t\t|  6 - Reclamações.                     |\t\t\t\t|\n");
        printf("\t\t|\t\t|  7 - Elogios.                         |\t\t\t\t|\n");
        printf("\t\t|\t\t|  8 - Estoque.                         |\t\t\t\t|\n");
        printf("\t\t|\t\t|  9 - Fechar programa.                 |\t\t\t\t|\n");
        printf("\t\t|\t\t|_______________________________________|\t\t\t\t|\n");
        printf("\t\t|\t\t                                         \t\t\t\t|\n");
        printf("\t\t|\t\t                                         \t\t\t\t|\n");
        printf("\t\t|\t\t ESCOLHA UMA OPÇÃO!  ;)                \t\t\t\t\t|\n");
        printf("\t\t|\t\t                                       \t\t\t\t\t|\n");
        printf("\t\t|_______________________________________________________________________________________|\n");
        scanf("%d", &op);
        fflush(stdin);

        switch(op){
            //CARDAPIO
        case 1:
                cardapio(pizzas, bebidas);
            break;
            //PEDIDOS
        case 2:
                fazerPedido(pizzas, bebidas);
            break;
            //CADASTRO DE CLIENTE
        case 3:
                cadastroCliente(clientes);
            break;
            //PESQUISAR CLIENTE
        case 4:
                cadastroFuncionario(funcionarios);
            break;
            //CADASTRAR FUNCIONARIO
        case 5:
                listaCadastros(clientes, funcionarios);
            break;
            //RECLAMAÇÕES
        case 6:
                fazerReclamacoes(reclamacoes);
            break;
            //ELOGIOS
        case 7:
                fazerElogios(elogios);
            break;
            //ESTOQUE
        case 8:
                Estoques(produtos);
            break;
            //FECHA PROGRAMA
        case 9:
                fazer_relatorio();
                printf("\t\t\t\t ______________________________________________\n");
                printf("\t\t\t\t|\t    NENA AGRADECE SUA PREFERÊCIA. . .\t   |\n ");
                printf("\t\t\t\t|_____________________________________________|\n");
            break;
        default:
            printf("Opção inválida!");
            break;
        }

        system("pause");
   }while(op != 9);
}
