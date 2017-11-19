#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct banda{
    int id;
    char nome[100];
    char pais[50];
    int ano_criacao;
};

struct resultado{
    char nome_membro[200];
    char nome_banda[100];
};

int main(){
    FILE* arquivo_bandas = fopen("bandas.txt", "r");
    FILE* arquivo_membros = fopen("membros.txt", "r");
    FILE* arquivo_destino = fopen("resultado.dat", "wb");
    if(arquivo_bandas != NULL && arquivo_membros != NULL && arquivo_destino != NULL){
        int num_bandas;
        fscanf(arquivo_bandas, "%d", &num_bandas);
        struct banda bandas[num_bandas];
        int i, j;
        for(i = 0; i < num_bandas;i++){
            fscanf(arquivo_bandas, "%d", &(bandas[i].id));
            fscanf(arquivo_bandas, "%s", bandas[i].nome);
            fscanf(arquivo_bandas, "%s", bandas[i].pais);
            fscanf(arquivo_bandas, "%d", &(bandas[i].ano_criacao));
            printf("%s\n", bandas[i].nome);
        }
        int num_membros;
        fscanf(arquivo_membros, "%d", &num_membros);
        struct resultado resultados_relatorio[num_membros];
        int id_banda, id_banda_procura;
        for(i = 0; i < num_membros;i++){
            fscanf(arquivo_membros, "%s", resultados_relatorio[i].nome_membro);
            fscanf(arquivo_membros, "%d", &id_banda);
            j = 0;
            do{
                id_banda_procura = bandas[j].id;
                if(id_banda_procura == id_banda){
                    strcpy(resultados_relatorio[i].nome_banda, bandas[j].nome);
                    printf("%s - %s\n", resultados_relatorio[i].nome_membro, resultados_relatorio[i].nome_banda);
                }
                j++;
            }while(id_banda_procura != id_banda);
        }
        fwrite(resultados_relatorio, sizeof(struct resultado), num_membros, arquivo_destino);
        fclose(arquivo_bandas);
        fclose(arquivo_membros);
        fclose(arquivo_destino);
    }else{
        printf("Erro ao abrir um dos arquivos.");
    }
}
