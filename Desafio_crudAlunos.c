#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct aluno { 
    int matricula;
    float nota1;
    float nota2;
    int qnt_faltas; 
};

void pausa_programa();
void imprime(char *opcao);
bool valida_matricula(char *matricula, char *operacao, struct aluno *vetor_alunos, int quant_registros);
bool valida_nota(char *nota);

int main() {
    char opcao[2] = {'f', '\0'};
    
    int quant_registros = 1;

    struct aluno *dados_aluno = malloc(sizeof(struct aluno));
    for(int i = 0; i < quant_registros; i++) {
        dados_aluno[i].matricula = -1;
        dados_aluno[i].nota1 = -1;
        dados_aluno[i].nota2 = -1;
        dados_aluno[i].qnt_faltas = -1;
    }

    while(true) {
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

            char matricula_prov[7];
            bool e_valido = true;
            while(true) {
                system("@cls||clear");

                imprime("cadastro");
                if(!e_valido) {
                    printf("     >>>> Numero de matricula invalido <<<<\n");
                    printf("-------------------------------------------------\n");
                }
                e_valido = true;
                printf("Insira a matricula: ");
                scanf("%s", matricula_prov);

                e_valido = valida_matricula(matricula_prov, "cadastro", dados_aluno, quant_registros);

                if(e_valido) {
                    dados_aluno[posicao].matricula = atoi(matricula_prov);
                    break;                 
                }
            }

            e_valido = true;
            char palavra[3][21] = {"primeira nota", "segunda nota", "quantidade de faltas"};
            int ordem = 0;
            while(true) {
                system("@cls||clear");

                imprime("cadastro");
                if(!e_valido) {
                    printf("          >>> %s invalida <<<\n", palavra[ordem]);
                    printf("-------------------------------------------------\n");
                }
                e_valido = true;
                
                printf("Insira a %s do aluno: ", palavra[ordem]);

                if(ordem == 0 || ordem == 1) {
                    char nota[6];
                    scanf("%s", nota);

                    e_valido = valida_nota(nota);

                    if(e_valido) {
                        if(ordem == 0) {
                            dados_aluno[posicao].nota1 = atof(nota);
                            ordem++;
                        }
                        else {
                            dados_aluno[posicao].nota2 = atof(nota);
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
                        dados_aluno[posicao].qnt_faltas = atoi(qnt_faltas);
                        break;
                    }
                }

            }

            system("@cls||clear");

            imprime("cadastro");
            printf("     >>> Dados registrados com sucesso! <<<\n");
            printf("-------------------------------------------------\n");
            printf("|    Resumo do aluno:    |\n");
            printf("--------------------------\n");
            printf("| Matricula: %d\n", dados_aluno[posicao].matricula);
            printf("| Nota 1: %.1f\n", dados_aluno[posicao].nota1);
            printf("| Nota 2: %.1f\n", dados_aluno[posicao].nota2);
            printf("| Quantidade de Faltas: %d\n", dados_aluno[posicao].qnt_faltas);
            printf("--------------------------\n");

            pausa_programa();
    
        }
        else if(opcao[0] == '2') { // DELETA ALUNO
            int matricula = -1;
            bool tem_registro = false;
            for(int i = 0; i < quant_registros; i++) {
                if(dados_aluno[i].matricula != -1) {
                    tem_registro = true;
                }
            }

            if(tem_registro) {
                char matricula_prov[7];
                bool e_valido = true;
                while(true) {
                    system("@cls||clear");

                    imprime("apagar");
                    if(!e_valido) {
                        printf("     >>>> Numero de matricula invalido <<<<\n");
                        printf("-------------------------------------------------\n");
                    }
                    e_valido = true;

                    printf("Insira a matricula: ");
                    scanf("%s", matricula_prov);

                    e_valido = valida_matricula(matricula_prov, "apagar", dados_aluno, quant_registros);

                    if(e_valido) {
                        for(int i = 0; i < quant_registros; i++) {
                            if(dados_aluno[i].matricula == atoi(matricula_prov)) {
                                dados_aluno[i].matricula = -1;
                                dados_aluno[i].nota1 = -1;
                                dados_aluno[i].nota2 = -1;
                                dados_aluno[i].qnt_faltas = -1;
                                break;
                            }
                        }
                        system("@cls||clear");

                        imprime("apagar");
                        printf("     >>>> Aluno Apagado com Sucesso <<<<\n");
                        printf("-------------------------------------------------\n");

                        pausa_programa();
                        break;
                    }
                    
                }
            }
            else {
                system("@cls||clear");

                imprime("apagar");
                printf("         >>> Nenhum aluno registrado! <<<\n");
                printf("-------------------------------------------------\n");
                
                pausa_programa();
            }
        }
        else if(opcao[0] == '3') { // LISTA ALUNOS
            system("@cls||clear");

            imprime("listar");

            bool imprimiu = false; 
            for(int i = 0; i < quant_registros; i++) {
                if(dados_aluno[i].matricula != -1) {
                    if(!imprimiu) {
                        printf("|   Resumo dos alunos:   |\n");
                        printf("--------------------------\n");
                        imprimiu = true;
                    }
                    printf("| Matricula: %d\n", dados_aluno[i].matricula);
                    printf("| Nota 1: %.1f\n", dados_aluno[i].nota1);
                    printf("| Nota 2: %.1f\n", dados_aluno[i].nota2);
                    printf("| Quantidade de Faltas: %d\n", dados_aluno[i].qnt_faltas);
                    printf("--------------------------\n");

                }
                if(i == (quant_registros - 1) && dados_aluno[i].matricula == -1 && !imprimiu) {
                    printf("        >>> Nenhum aluno registrado! <<<\n");
                    printf("------------------------------------------------\n");
                }
            }
            pausa_programa();
        }
        else if(opcao[0] == '4') { // ENCERRA O PROGRAMA
            system("@cls||clear");

            printf("------------------------------------------------\n");
            printf("Obrigado por utilizar o programa. Ate a proxima!\n");
            printf("------------------------------------------------\n");

            pausa_programa();

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
    if(opcao == "apagar") {
        printf("-------------------------------------------------\n");
        printf("                  APAGAR ALUNO\n");
        printf("-------------------------------------------------\n");
    }   
    if(opcao == "listar") {
        printf("-------------------------------------------------\n");
        printf("                LISTA DE ALUNOS\n");
        printf("-------------------------------------------------\n");
    }
}

void pausa_programa() {
    printf("\nPressione Enter Para Continuar. . . ");
    getchar();
    getchar();
}

bool valida_matricula(char *matricula, char *operacao, struct aluno *vetor_alunos, int quant_registros) {
    bool e_valido = true;
    for(int i = 0; i < strlen(matricula); i++) {
        if(matricula[i] == '\0') {
            break;
        }
        if( (matricula[i] - '0') < 0 || (matricula[i] - '0') > 9) {
            e_valido = false;
        }
    }
    
    if(quant_registros != 0) {
        for(int i = 0; i < quant_registros; i++) {
            if(vetor_alunos[i].matricula == atoi(matricula)) {
                if(operacao == "cadastro") {
                    e_valido = false;
                    break;
                }
                else if(operacao == "apagar") {
                    e_valido = true;
                    break;
                }
            }
            else {
                if(i == (quant_registros - 1) && operacao == "apagar") {
                    e_valido = false;
                    break;
                }
            }
        }
    }

    return e_valido;
}

bool valida_nota(char *nota) {
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