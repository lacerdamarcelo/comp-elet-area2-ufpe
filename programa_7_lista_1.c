#include <stdio.h>
#include <stdlib.h>
/*
AQUI TEMOS UM COMENTARIO NA LINGUAGEM C!
Exercitando lacos, condicionais e leitura do input do usuario.
*/

int main(){
    int n;
    do{
        printf("Defina o valor de N como dimensao do cenario quadrado N x N (maior do que 1): ");
        scanf("%d", &n);
    }while(n <= 1);
    int x, y;
    do{
        printf("Defina a posicao x inicial do robo (%d < x < %d): ", 1, n - 1);
        scanf("%d", &x);
    }while(x <= 1 || x >= n - 1);
    do{
        printf("Defina a posicao y inicial do robo (%d < y < %d): ", 1, n - 1);
        scanf("%d", &y);
    }while(y <= 1 || y >= n - 1);

    char comando;
    int contador_passos = 0;
    do{
        /*
        Aqui estou checando se o sistema operacional que estou usando e windows ou linux,
        pois os comandos "cls" e "clear" sao proprios do windows e do linux, respectivamente.
        Nao se preocupem com isso, e apenas um detalhe e uma forma de deixar o programa mais
        bonito, pois com ele eu posso apagar a tela e comecar a preencher a mesma novamente. =D
        */
        #ifdef _WIN32
        system("cls");
        #endif
        #ifdef linux
        system("clear");
        #endif
        int i, j;
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                if(i == 0 || i == n-1){
                    printf("#");
                }else{
                    if(j == 0 || j == n-1){
                        printf("#");
                    }else{
                        if(i == y && j == x){
                            printf("O");
                        }else{
                            printf(" ");
                        }
                    }
                }
            }
            printf("\n");
        }
        printf("Numero de passos dados: %d\n", contador_passos);
        printf("Escolha o comando a ser enviado para o robo e pressione ENTER:\n");
        printf("w - Anda para frente\ns - Anda para tras\nd - Anda para a direita\ne - Anda para a esquerda\nq - Desliga o robo\n");
        scanf("%c", &comando);
        switch(comando){
        case 'w':
            if(y > 1){
                y--;
                contador_passos++;
            }
            break;
        case 's':
            if(y < n - 2){
                y++;
                contador_passos++;
            }
            break;
        case 'a':
            if(x > 1){
                x--;
                contador_passos++;
            }
            break;
        case 'd':
            if(x < n - 2){
                x++;
                contador_passos++;
            }
            break;
        case 'q':
            continue;
        }
    }while(comando != 'q');

    #ifdef _WIN32
    system("cls");
    #endif
    #ifdef linux
    system("clear");
    #endif
    printf("Obrigado por usar meu simulador =D");
    return 0;
}
