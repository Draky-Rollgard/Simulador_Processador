#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INSTRUCOES 31
#define TAMANHO_MEMORIA 31
#define REGISTRADORES 4

//////////////////////// Estrutura do processador/////////////////////////////////////
typedef struct 
{
    int PC;                     // Contador de Programa
    int IR;                     // Registrador de Instrução
    char memoria[TAMANHO_MEMORIA][100]; // Memória principal
    int registradores[REGISTRADORES]; // Registradores R0 a R3
} CPU;


///////////////////////////FUNÇÕES A USAR //////////////////////////////////////////////
void inicializarCPU(CPU *cpu);
int obterNumeroRegistrador(const char *reg);
int ehNumero(const char *str);
void executarInstrucao(CPU *cpu);
void salvarEstado(CPU *cpu);

///////////////////////////// Função para inicializar o processador////////////////////
void inicializarCPU(CPU *cpu) 
{
    cpu->PC = 0;
    cpu->IR = 0;
    memset(cpu->memoria, 0, sizeof(cpu->memoria));
    memset(cpu->registradores, 0, sizeof(cpu->registradores));
}
///////////////////// Função para obter o número do registrador/////////////////////////
int obterNumeroRegistrador(const char *reg) 
{
    if (strcmp(reg, "R0") == 0) return 0;
    if (strcmp(reg, "R1") == 0) return 1;
    if (strcmp(reg, "R2") == 0) return 2;
    if (strcmp(reg, "R3") == 0) return 3;
    return -1;
}
////////////////////Função para verificar se uma string é um número////////////////////
int ehNumero(const char *str) 
{
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}
///////////////////// Função para executar uma instrução/////////////////////////////
void executarInstrucao(CPU *cpu) 
{
    char instrucao[10];
    char reg1[3], reg2[3], reg3[3];
    int enderecoMemoria;

	for(cpu->PC = 0; cpu->PC < 32; cpu->PC++)
	{


        char *linha = cpu->memoria[cpu->PC];
        sscanf(linha, "%s", instrucao);
        
        if (strcmp(instrucao, "LOAD") == 0) 
        {
            sscanf(linha, "%*s %s %d", reg2, &enderecoMemoria);

            if (enderecoMemoria < 0 || enderecoMemoria >= TAMANHO_MEMORIA) 
            {
                printf("Endereço de memória inválido: %d\n", enderecoMemoria);
                return; 
            }

            int numReg = obterNumeroRegistrador(reg2);
            if (numReg != -1) 
            {
                cpu->registradores[numReg] = atoi(cpu->memoria[enderecoMemoria]);
            }
                    printf("%d\n", cpu->registradores[numReg]);
        } 
        
        else if (strcmp(instrucao, "STORE") == 0) 
        {
            sscanf(linha, "%*s %d %s", &enderecoMemoria, reg2);

            if (enderecoMemoria < 0 || enderecoMemoria >= TAMANHO_MEMORIA) 
            {
                printf("Endereço de memória inválido: %d\n", enderecoMemoria);
                return; 
            }

            int numReg = obterNumeroRegistrador(reg2);
            
            if (numReg != -1) 
            {
                sprintf(cpu->memoria[enderecoMemoria], "%d", cpu->registradores[numReg]);
            }
        } 
        
        else if (strcmp(instrucao, "MOVE") == 0) 
        {
            sscanf(linha, "%*s %s %s", reg2, reg3);
            int numReg2 = obterNumeroRegistrador(reg2);
            int numReg3 = obterNumeroRegistrador(reg3);
            
            if (numReg2 != -1 && numReg3 != -1) 
            {
                cpu->registradores[numReg2] = cpu->registradores[numReg3];
            }
        } 
        
        else if (strcmp(instrucao, "ADD") == 0) 
        {
            sscanf(linha, "%*s %s %s %s", reg1, reg2, reg3);
            int numReg1 = obterNumeroRegistrador(reg1);
            int numReg2 = obterNumeroRegistrador(reg2);
            int numReg3 = obterNumeroRegistrador(reg3);
            if (numReg1 != -1 && numReg2 != -1 && numReg3 != -1) 
            {
                cpu->registradores[numReg1] = cpu->registradores[numReg2] + cpu->registradores[numReg3];
            }
        }
        
        else if (strcmp(instrucao, "SUB") == 0) 
        {
            sscanf(linha, "%*s %s %s %s", reg1, reg2, reg3);
            int numReg1 = obterNumeroRegistrador(reg1);
            int numReg2 = obterNumeroRegistrador(reg2);
            int numReg3 = obterNumeroRegistrador(reg3);
            if (numReg1 != -1 && numReg2 != -1 && numReg3 != -1) 
            {
                cpu->registradores[numReg1] = cpu->registradores[numReg2] - cpu->registradores[numReg3];
            }
        }
        
        else if (strcmp(instrucao, "AND") == 0) 
        {
            sscanf(linha, "%*s %s %s %s", reg1, reg2, reg3);
            int numReg1 = obterNumeroRegistrador(reg1);
            int numReg2 = obterNumeroRegistrador(reg2);
            int numReg3 = obterNumeroRegistrador(reg3);
            if (numReg1 != -1 && numReg2 != -1 && numReg3 != -1) 
            {
                cpu->registradores[numReg1] = cpu->registradores[numReg2] & cpu->registradores[numReg3];
            }
        }
        
        else if (strcmp(instrucao, "OR") == 0) 
        {
            sscanf(linha, "%*s %s %s %s", reg1, reg2, reg3);
            int numReg1 = obterNumeroRegistrador(reg1);
            int numReg2 = obterNumeroRegistrador(reg2);
            int numReg3 = obterNumeroRegistrador(reg3);
            if (numReg1 != -1 && numReg2 != -1 && numReg3 != -1) 
            {
                cpu->registradores[numReg1] = cpu->registradores[numReg2] | cpu->registradores[numReg3];
            }
        }
        
        else if (strcmp(instrucao, "BRANCH") == 0) 
        {
            sscanf(linha, "%*s %d", &enderecoMemoria);

            if (enderecoMemoria < 0 || enderecoMemoria >= TAMANHO_MEMORIA) 
            {
                printf("Endereço de memória inválido: %d\n", enderecoMemoria);
                return; // Lida com erros
            }

            cpu->PC = enderecoMemoria - 1; // -1 para ajustar o incremento no final
        }
        
        else if (strcmp(instrucao, "BZERO") == 0) 
        {
            sscanf(linha, "%*s %d", &enderecoMemoria);

            if (enderecoMemoria < 0 || enderecoMemoria >= TAMANHO_MEMORIA) 
            {
                printf("Endereço de memória inválido: %d\n", enderecoMemoria);
                return; 
            }

            if (cpu->registradores[0] == 0) 
            { // Considerando R0 como o registrador de resultado
                cpu->PC = enderecoMemoria - 1; 
            }
        }
        
        else if (strcmp(instrucao, "BNEG") == 0) 
        {
            sscanf(linha, "%*s %d", &enderecoMemoria);
            
            if (enderecoMemoria < 0 || enderecoMemoria >= TAMANHO_MEMORIA) 
            {
                printf("Endereço de memória inválido: %d\n", enderecoMemoria);
                return; 
            }
        
            if (cpu->registradores[0] < 0) 
            { 
                cpu->PC = enderecoMemoria - 1; 
            }
        }
        
        else if (strcmp(instrucao, "NOP") == 0) {}//Não faz nada

        // tem um erro nessa parte do código. Ele não está criando arquivos quando coloco halt
        ///*
        else if (strcmp(instrucao, "HALT") == 0) 
        {
            salvarEstado(cpu); 
            break;
        }
        //*/
	}
}

/////////////////////Programa principal////////////////////////////////////////////////////////
int main() 
{
    CPU cpu;
    inicializarCPU(&cpu);

    FILE *arquivoEntrada = fopen("entrada.txt", "rt");
    if (arquivoEntrada == NULL) 
    {
        printf("Erro ao abrir entrada.txt\n");
        return 1;
    }

    char linha[100];
    int contadorInstrucoes = 0;
    for (contadorInstrucoes = 0; contadorInstrucoes < MAX_INSTRUCOES; contadorInstrucoes++) 
    {
        fgets(linha, sizeof(linha), arquivoEntrada);
        linha[strcspn(linha, "\n")] = 0; 
				if (ehNumero(linha)) 
        {
            strcpy(cpu.memoria[contadorInstrucoes], linha);
        } 
        else
        {
            strcpy(cpu.memoria[contadorInstrucoes], linha);
        }
    }
    fclose(arquivoEntrada);

    executarInstrucao(&cpu);

    salvarEstado(&cpu);
    return 0;
}

/////////////////////// Função para salvar o estado final em arquivos////////////////////////
void salvarEstado(CPU *cpu) 
{
    FILE *arquivoUC = fopen("unidade_controle.txt", "wt");
    if (arquivoUC) {
        fprintf(arquivoUC, "%d %d\n", cpu->PC, cpu->IR);
        fclose(arquivoUC);
    }

    FILE *arquivoReg = fopen("banco_registradores.txt", "wt");
    if (arquivoReg) 
    {
        for (int i = 0; i < REGISTRADORES; i++) 
        {
            fprintf(arquivoReg, "%d\n", cpu->registradores[i]);
        }
        fclose(arquivoReg);
    }

    FILE *arquivoMem = fopen("memoria_ram.txt", "wt");
    if (arquivoMem) 
    {
        for (int i = 0; i < TAMANHO_MEMORIA; i++) 
        {
            fprintf(arquivoMem, "%s\n", cpu->memoria[i]);
        }
        fclose(arquivoMem);
    }
}

