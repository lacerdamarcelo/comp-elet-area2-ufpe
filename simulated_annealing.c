//Este código implementa o algoritmo Simulated Annealing.
#include <stdio.h>
//A biblioteca math.h possui a funcao "pow", que calcula potências.
#include <math.h>
//Estes includes sao necessários para gerar números aleatórios.
#include <time.h>
#include <stdlib.h>

void copiar_vetor(float origem[], float destino[], int num_dimensoes){
    int i;
	for(i = 0; i < num_dimensoes; i++){
		destino[i] = origem[i];
	}
}

/*Essa funcao cacula a qualidade da solucao, utilizando como funcao objetivo
a funcao esfera.*/
float funcao_esfera(float solucao[], int num_dimensoes){
	float resultado = 0;
	int i;
	for(i = 0; i < num_dimensoes; i++){
		resultado += pow(solucao[i], 2);
	}
	return resultado;
}

/*Essa funcao possuia funcionalidade de gerar uma solucao nova a partir da
anterior (recebida como entrada) e, se for o caso, substituir o vetor da
solucao corrente com a nova.*/
void gerar_e_analisar_vizinho(float solucao[], float temperatura, int num_dimensoes){
	float nova_solucao[num_dimensoes];
	int i, r;
	for(i = 0; i < num_dimensoes; i++){
        r = rand();
        nova_solucao[i] = solucao[i] + (((float)(r % 10000) / 10000) * temperatura) - (temperatura / 2);
	}
	float qualidade_solucao_corrente = funcao_esfera(solucao, num_dimensoes);
	float qualidade_solucao_nova = funcao_esfera(nova_solucao, num_dimensoes);
	if(qualidade_solucao_nova < qualidade_solucao_corrente){
        copiar_vetor(nova_solucao, solucao, num_dimensoes);
	}else{
        float delta_qualidade = qualidade_solucao_nova - qualidade_solucao_corrente;
        float probabilidade_escolha = exp(-delta_qualidade / temperatura);
        float sorteio = rand() / 10000;
        if(sorteio < probabilidade_escolha){
            copiar_vetor(nova_solucao, solucao, num_dimensoes);
        }
	}
}

void inicializar_solucao(float solucao[], float temperatura, int num_dimensoes){
    int i, r;
	for(i = 0; i < num_dimensoes; i++){
        r = rand();
        solucao[i] = ((float)(r % 10000) / 10000) * temperatura - (temperatura / 2);
	}
}

/*Executando o procedimento de busca durante um numero maximo de iteracoes para um dada temperatura fixa.*/
void executar_temperatura_fixa(float solucao[], int num_dimensoes, int temperatura, int maximo_iteracoes){
    int i;
    for(i = 0; i < maximo_iteracoes; i++){
        gerar_e_analisar_vizinho(solucao, temperatura, num_dimensoes);
    }
}

//Atualizando melhor solucao
float atualizar_melhor_solucao(float solucao[], float melhor_solucao[], int num_dimensoes){
    float qualidade_solucao_corrente = funcao_esfera(solucao, num_dimensoes);
	float qualidade_melhor_solucao = funcao_esfera(melhor_solucao, num_dimensoes);
    if(qualidade_solucao_corrente < qualidade_melhor_solucao){
        copiar_vetor(solucao, melhor_solucao, num_dimensoes);
        return qualidade_solucao_corrente;
    }
    return qualidade_melhor_solucao;
}

//Atualizando temperatura
float calcular_nova_temperatura(float temperatura, float alfa){
    return temperatura * alfa;
}

int main(){
	srand(time(NULL));
    int num_dimensoes = 10;

    //Parâmetros
    float temperatura = 100;
    int maximo_iteracoes = 10;
    float alfa = 0.8;

    float solucao[num_dimensoes];
    float melhor_solucao[num_dimensoes];

    inicializar_solucao(solucao, temperatura, num_dimensoes);
    copiar_vetor(solucao, melhor_solucao, num_dimensoes);
    printf("Solucao inicial:\n");
    int i;
    for(i = 0; i < num_dimensoes; i++){
        printf("%f ", melhor_solucao[i]);
    }
    printf("\n");
    printf("Evolucao da qualidade da solucao:\n");
    float qualidade_melhor_solucao = atualizar_melhor_solucao(solucao, melhor_solucao, num_dimensoes);
    printf("%f\n", qualidade_melhor_solucao);
    while(temperatura > 0.0001){
        executar_temperatura_fixa(solucao, num_dimensoes, temperatura, maximo_iteracoes);
        temperatura = calcular_nova_temperatura(temperatura, alfa);
        qualidade_melhor_solucao = atualizar_melhor_solucao(solucao, melhor_solucao, num_dimensoes);
        printf("%f\n", qualidade_melhor_solucao);
    }
    printf("Solucao final:\n");
    for(i = 0; i < num_dimensoes; i++){
        printf("%f ", melhor_solucao[i]);
    }
    printf("\n");
	return 0;
}
