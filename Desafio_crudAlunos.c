#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct aluno { //struct global
        int matricula;
        float nota1;
        float nota2;
        int qnt_faltas; 
};

void imprime(char *opcao) {

    if(opcao == "menu") {
        printf("----------------------\n");
        printf("|        MENU        |\n");
        printf("----------------------\n");
        printf("|1 - Cadastrar Aluno |\n");
        printf("|2 - Apagar Aluno    |\n");
        printf("|3 - Listar Alunos   |\n");
        printf("|4 - Sair            |\n");
        printf("----------------------\n");
    }
    if(opcao == "cadastro") {
        printf("-------------------------------------------------\n");
        printf("                CADASTRO DE ALUNO\n");
        printf("-------------------------------------------------\n");
    }
    
}

int checa_matricula(char *titulo_operacao, char *mensagem) {
    char matricula[7];
    bool erro = false;
    while(true) {
        system("@cls||clear");\
        
        if(erro) {
            printf("-------------------------------------------------\n");
            printf(titulo_operacao);
            printf("\n-------------------------------------------------\n");
            printf("     >>>> Numero de matricula invalido <<<<\n");
            printf("-------------------------------------------------\n");
        }
        else{
            printf("-------------------------------------------------\n");
            printf(titulo_operacao);
            printf("\n-------------------------------------------------\n");
        }
        printf("OBS.: O numero de matricula deve conter 6 digitos\n");
        printf("-------------------------------------------------\n");
        printf(mensagem);
        scanf("%s", matricula);

        erro = false;
        if(matricula[6] == '\0') {
            for(int i = 0; i < 6; i++) {
                if( (matricula[i] - '0') > 9) {
                    erro = true;
                    break;
                }
            }
        }
        else {
            erro = true;
        }
        if(!erro) {
            break;
        }
    }
    return atoi(matricula);
}

float valida_nota(char *nota) {
    bool e_valido = true;
    bool ponto_flutuante = false;
    for(int i = 0; i < strlen(nota); i++) {

        if(nota[i] == '\0') {
            break;
        }

        if(nota[i] == ',' && !ponto_flutuante) {
            nota[i] = '.';
        }
        
        if( (nota[i] - '0') < 0 || (nota[i] - '0') > 9) {
            if(nota[i] == '.') {
                if(!ponto_flutuante) {
                    ponto_flutuante = true;
                }
                else {
                    e_valido = false;
                    break;
                }
            }
            else {
                e_valido = false;
                break;
            }
        }
        
    }

    if(e_valido && atof(nota) && atof(nota) <= 10) {
        e_valido = true;
    }
    else {
        e_valido = false;
    }

    return e_valido;
}

struct aluno cadastro_aluno() {
    struct aluno dados_aluno;

    dados_aluno.matricula = checa_matricula("                CADASTRO DE ALUNO", "Insira a matricula: ");

    bool e_valido = true;
    char palavra[3][21] = {"primeira nota", "segunda nota", "quantidade de faltas"};
    int ordem = 0;
    while(true) {
        system("@cls||clear");

        imprime("cadastro");
        if(!e_valido) {
            printf("%s invalida\n", palavra[ordem]);
        }
        e_valido = true;
        
        
        printf("Insira a %s do aluno: ", palavra[ordem]);

        if(ordem == 0 || ordem == 1) {
            char nota[6];
            scanf("%s", nota);

            e_valido = valida_nota(nota);

            if(e_valido) {
                if(ordem == 0) {
                    dados_aluno.nota1 = atof(nota);
                    ordem++;
                }
                else {
                    dados_aluno.nota2 = atof(nota);
                    ordem++;
                }
            }
        }
        else {
            char qnt_faltas[3];
            scanf("%s", qnt_faltas);
            
            for(int i = 0; i < strlen(qnt_faltas); i++) {
                if(qnt_faltas[i] == '\0') {
                    break;
                }
                if( (qnt_faltas[i] - '0') < 0 || (qnt_faltas[i] - '0') > 9) {
                    e_valido = false;
                }
            }

            if(e_valido) {
                dados_aluno.qnt_faltas = atoi(qnt_faltas);
                break;
            }
        }

    }
    
    return dados_aluno;
}

int main()
{
    char opcao[2] = {'f', '\0'};
    
    int quant_registros = 1;
    struct aluno *dados_aluno = malloc(sizeof(struct aluno) * quant_registros);
    //struct aluno dados_aluno[quant_registros];
    for(int i = 0; i < quant_registros; i++) {
        dados_aluno[i].matricula = -1;
        dados_aluno[i].nota1 = -1;
        dados_aluno[i].nota2 = -1;
        dados_aluno[i].qnt_faltas = -1;
    }

    while(true) {
        //getchar();
        system("@cls||clear");

        imprime("menu");
        if(opcao[0] == '0') {
            printf("|   Opcao Invalida   |\n");
            printf("----------------------\n");
        }

        printf("Digite sua opcao: ");
        scanf("%s", opcao);

        if (((opcao[0] - '0') < 1 || (opcao[0] - '0') > 4) || opcao[1] != '\0') {
            opcao[0] = '0';
        }

        // EXECUCAO DAS OPERACOES

        if(opcao[0] == '1') { // REGISTRO DE ALUNO 
            int posicao = -1;
            for(int i = 0; i < quant_registros; i++) { 
                if(dados_aluno[i].matricula == -1) {
                    posicao = i;
                    break;
                }
                if(i == (quant_registros - 1) && dados_aluno[i].matricula != -1) { // CASO EXCEDA O TAMANHO INICIAL DO VETOR, ALOCA MAIS 1 POSICAO
                    quant_registros += 1;
                    dados_aluno = realloc(dados_aluno, (sizeof(struct aluno) * quant_registros));
                    dados_aluno[i + 1].matricula = -1;
                    dados_aluno[i + 1].nota1 = -1;
                    dados_aluno[i + 1].nota2 = -1;
                    dados_aluno[i + 1].qnt_faltas = -1;
                }
            }

            dados_aluno[posicao] = cadastro_aluno();

            system("@cls||clear");

            imprime("cadastro");
            printf("     >>> Dados registrados com sucesso! <<<\n");
            printf("-------------------------------------------------\n");


            printf("|    Resumo do aluno:    |\n--------------------------\n");
            printf("| Matricula: %d\n| Nota 1: %.1f\n| Nota 2: %.1f\n| Quantidade de faltas: %d\n", dados_aluno[posicao].matricula, dados_aluno[posicao].nota1, dados_aluno[posicao].nota2, dados_aluno[posicao].qnt_faltas);
            printf("--------------------------\n");

            printf("\nPressione Enter Para Continuar . . . ");
            getchar();
            getchar();
    
        }
        else if(opcao[0] == '2') { // DELETA ALUNO (INCOMPLETO)
            int matricula_deletar = checa_matricula("                  APAGAR ALUNO", "Insira a matricula que deseja deletar: ");
            for(int i = 0; i < quant_registros; i++) {
                if(dados_aluno[i].matricula == matricula_deletar) {
                    dados_aluno[i].matricula = -1;
                    dados_aluno[i].nota1 = -1;
                    dados_aluno[i].nota2 = -1;
                    dados_aluno[i].qnt_faltas = -1;
                }
            }
        }
        else if(opcao[0] == '3') { // LISTA ALUNOS (INCOMPLETO)
            system("@cls||clear");

            for(int i = 0; i < quant_registros; i++) {
                if(dados_aluno[i].matricula != -1) {
                    printf("Matricula: %d\n", dados_aluno[i].matricula);
                    printf("Nota 1: %.1f\n", dados_aluno[i].nota1);
                    printf("Nota 2: %.1f\n", dados_aluno[i].nota2);
                    printf("Faltas: %d\n", dados_aluno[i].qnt_faltas);
                }
                if(i == (quant_registros - 1) && dados_aluno[i].matricula == -1) {
                    printf("Nenhum aluno registrado!\n");
                    printf("  \n");

                    printf("Pressione Enter Para Continuar. . . ");
                    getchar();
                    getchar();

                }
            }
        }
        else if(opcao[0] == '4') { // ENCERRA O PROGRAMA
            system("@cls||clear");

            printf("------------------------------------------------\n");
            printf("Obrigado por utilizar o programa. Ate a proxima!\n");
            printf("------------------------------------------------\n");
            printf("  \n");

            printf("Pressione Enter Para Finalizar o Programa. . . ");
            getchar();
            getchar();
            /* Escolhi essa solucao para pausar o programa por ser versatil entre windows e linux  
            (sao executados dois getchar(); nesse caso, porque o primeiro consome o '\n'
            pendente no buffer devido a leituras anteriores) */

            system("@cls||clear");
            break;
        }
        else {
            opcao[0] = '0';
        }

    }

    free(dados_aluno);
    return 0;
}
