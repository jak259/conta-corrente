#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct CONTA_CORRENTE{
    char nome[30];
    int numAgencia;
    int numConta;
    float saldo;
};

struct CONTA_CORRENTE *c;
int acao, i = 0, j, agencia, con;
float valor;
char nome[30];

void abrirConta(){          //OK
    agencia = 0;
    con = 0;
    if(i == 0){
        c = (struct CONTA_CORRENTE*)malloc(1*sizeof(struct CONTA_CORRENTE));    //cria um espaço na memória
    }else{
        c = (struct CONTA_CORRENTE*)realloc(c, (i+1)*sizeof(struct CONTA_CORRENTE));  //aloca mais um espaço na memória
    }

    if(i == 0){                                 //como é a primeira conta não há casos de contas com dados iguais
        printf("\nAbrir conta");
        printf("\nDigite seu nome: ");
        fflush(stdin);                                            //dados inseridos pelo usuário
        fgets(c[i].nome, 30, stdin);
        printf("Numero da agencia: ");
        scanf("%d", &c[i].numAgencia);
        fflush(stdin);
        printf("Numero da conta: ");
        scanf("%d", &c[i].numConta);
        fflush(stdin);
        c[i].saldo = 0;
        printf("Ordem realizada com sucesso!!\n\n");
        i++;
    }else{                                          //verifica se os dados digitados ja existem
        for(j = 0; j <= i; j++){
            printf("\nDigite seu nome: ");
            fflush(stdin);
            fgets(nome, 30, stdin);
            printf("Numero da agencia: ");          //criação de segunda conta em diante
            scanf("%d", &agencia);
            fflush(stdin);
            printf("Numero da conta: ");
            scanf("%d", &con);
            fflush(stdin);
            if(((strcmp(nome, c[j].nome)) == 0) || (con == c[j].numConta)){
                printf("\nAlguns dos dados digitados ja existem!\n");           //se houver algum dado igual de outra conta o programa pede
                j--;                                                            //pra digitá-los novamente
            }else{                                                              //senão ele armazena normalmente
                strcpy(c[i].nome, nome);
                c[i].numAgencia = agencia;
                c[i].numConta = con;
                c[i].saldo = 0;
                printf("Ordem realizada com sucesso!\n\n");
                i++;
                break;
            }
        }
    }
    //Sleep(1500);
    //system("cls");
}

void depositar(){           //OK
    agencia = 0;
    con = 0;
    j = 0;
    printf("\nDepositar dinheiro\n");
    if(i == 0){                                                     //caso não haja contas criadas não será possível realizar a opreração
        printf("Nao ha contas para se depositar dinheiro!\n\n");
    }else{                                            //pede os dados da conta
        printf("Digite sua agencia: ");
        scanf("%d", &agencia);
        fflush(stdin);
        printf("Digite o numero da conta: ");
        scanf("%d", &con);
        fflush(stdin);

        do{
            if((agencia == c[j].numAgencia) && (con == c[j].numConta)){     //verifica a existencia da conta
                printf("\nUsuario: %s\n", c[j].nome);
                printf("Ha %.2f R$ na sua conta\n", c[j].saldo);
                printf("Digite a quantia a ser depositada: ");
                scanf("%f", &valor);                                        //verifica se o valor é menor do que zero
                if(valor < 0){
                    printf("A quantia e menor do que zero!!\n");
                    j--;
                }else{
                    c[j].saldo += valor;                                    //soma o valor ao saldo do usuario
                    valor = 0;
                    printf("Ordem realizada com sucesso!\n\n");
                    break;
                }
            }else if(j == i){                                      //se os dados não forem encontrados é porque ela não existe
                printf("\nEssa conta nao existe!\n\n");
                break;
            }else{
                j++;
            }
        }while(j != i);
    }
    //Sleep(1500);
    //system("cls");
}

void sacar(){               //OK
    agencia = con = j = 0;
    printf("\nSacar dinheiro\n");
    if(i == 0){                                             //caso não haja contas criadas não será possível realizar a opreração
        printf("Nao ha contas para haver saque!\n\n");
    }else{
        printf("Digite sua agencia: ");
        scanf("%d", &agencia);
        printf("Digite o numero da conta: ");
        scanf("%d", &con);

        do{
            if(agencia == c[j].numAgencia && con == c[j].numConta){             //verifica existencia de conta
                printf("Digite a quantia a ser sacada: ");
                scanf("%f", &valor);
                if(valor > c[j].saldo){                                         //verifica se o valor é maior do que ele possui
                    printf("\nA quantia e maior do que voce possui ou menor do que zero\n");
                    j--;
                }else if(valor <= 0){
                    printf("O valor sacado nao pode ser menor ou igual a zero\n");
                    j--;
                }else{
                    c[j].saldo -= valor;
                    valor = 0;
                    printf("Ordem realizada com sucesso!\n\n");
                    break;
                }
            }if(j > i){
                printf("\nEssa conta nao existe!");
            }
            j++;
        }while(j != i);
    }
    //Sleep(1500);
    //system("cls");
}

void consultarSaldo(){      //OK
    agencia = con = j = 0;
    printf("\nConsultar saldo\n");
    if(i == 0){                                                     //caso não haja contas criadas não será possível realizar a opreração
        printf("Nao ha contas para consultar\n\n");
    }else{
        printf("Digite sua agencia: ");
        scanf("%d", &agencia);
        printf("Digite o numero da conta: ");
        scanf("%d", &con);

        do{
            if(agencia == c[j].numAgencia && con == c[j].numConta){
                printf("\nUsuario atual: %s\n", c[j].nome);
                printf("Seu saldo atual eh: %.2f\n", c[j].saldo);
                printf("Ordem realizada com sucesso!\n\n");
                break;
            }else if(j > i){
                printf("\nEssa conta nao existe!");
                j--;
            }
            j++;
        }while(j != i);
    }
}

void transferirDinheiro(){
    int agOrigem, agDestino, conOrigem, conDestino, k = 0;
    float transf;
    agOrigem = agDestino = conOrigem = conDestino = 0;
    printf("\nTransferir dinheiro\n\n");

    if(i == 0 || i == 1){                           //caso não haja contas suficientes para se fazer uma transferencia
        printf("\nPara haver transferencia deve-se ter pelo menos duas contas validas\n");
    }else{

        printf("Digite sua agencia: ");                                 //pede o numero da agencia e conta de origem e destino da transferencia
        scanf("%d", &agOrigem);
        printf("Digite sua conta: ");
        scanf("%d", &conOrigem);
        printf("Digite a agencia a quem quer trasferir: ");
        scanf("%d", &agDestino);
        printf("Digite a conta a quem quer trasferir: ");
        scanf("%d", &conDestino);
        j=0;

        do{
            if((agOrigem == c[j].numAgencia) && (conOrigem == c[j].numConta)){      //verifica se os dados do que está transferindo são validos
                printf("\nSeu saldo atual eh: %.2f\n", c[j].saldo);
                printf("Digite a quantia a ser transferida: ");
                scanf("%f", &transf);
                if(transf > c[j].saldo){                                            //verifica se o valor transferido e maior do que o saldo
                    printf("\nTransferencia de valor superior ao armazenado ou menor do que zero");
                    j--;
                }else if(transf <= 0){
                    printf("O valor transferido nao pode ser menor ou igual a zero\n");
                    j--;
                }else{
                    do{
                        if((agDestino == c[k].numAgencia) && (conDestino == c[k].numConta)){        //verifica a validação do destinatário da transferencia
                            c[j].saldo -= transf;
                            c[k].saldo += transf;
                            printf("Ordem realizada com sucesso!\n\n");
                            break;
                        }else if(k > i){
                            printf("Conta de destino nao encontrada\n\n");
                            break;
                        }
                        k++;
                    }while(k != i);
                }
            }else if(j > i){
                printf("\nEssa conta nao existe!\n\n");
                break;
            }
            j++;
        }while(j != i);
    }
    //Sleep(1500);
    //system("cls");
}

void listagemDeContas(){                                    //lista todas as contas abertas
    int lin;
    j=0;
    printf("\nListar contas abertas\n\n");

    if(i == 0){
        printf("\nNao ha contas abertas\n");
    }else{
        do{
            for(lin=0;lin<=20;lin++){
                printf("-");
            }
            printf("\nUser: %s", c[j].nome);
            printf("\nAgencia: %d", c[j].numAgencia);
            printf("\nNumero da Conta: %d", c[j].numConta);
            printf("\nSaldo disponivel: %.2f\n", c[j].saldo);
            j++;
        }while(j != i);
    }
}

int main(){

    do{
    printf("\nBoas Vindas, o que deseja fazer?\n\t1-Abrir Conta Corrente\n\t2-Depositar");
    printf("\n\t3-Sacar\n\t4-Consultar Saldo\n\t5-Tranferencia\n\t6-Listar contas abertas\n\t7-Sair\n--");
    scanf("%d", &acao);

    switch(acao){
        case 1:
            abrirConta();
            break;
        case 2:
            depositar();
            break;
        case 3:
            sacar();
            break;
        case 4:
            consultarSaldo();
            break;
        case 5:
            transferirDinheiro();
            break;
        case 6:
            listagemDeContas();
            break;
        case 7:
            printf("\nOrdem finalizada com sucesso\n\n");
            break;
        default:
            printf("\nOpcao Invalida! Tente novamente\n\n");
            //Sleep(1500);
            //system("cls");
            break;
        }
    }while(acao != 7);
}
