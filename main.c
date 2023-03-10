#include <stdio.h>
#include <stdlib.h>

#define NMAX 100

int D;
int bispo, rei, cavalo;
int frequencia;
int valores;
int nsolucoes = 0;

int tabtest1[NMAX][NMAX];
int tabtest2[NMAX][NMAX];
int tabtest3[NMAX][NMAX];
int tabtest_rainha[NMAX][NMAX];

int posicao_valida(int linha, int coluna);

int ocorrencias[NMAX][NMAX];
int solucao[NMAX];
int solucao_valida(int solucao[NMAX]);
int tab_solucao[NMAX][NMAX];

void zera_tabuleiro(int tabuleiro [NMAX][NMAX]);
void compara_tabuleiro (int tabuleiro1 [NMAX][NMAX], int tabuleiro2 [NMAX][NMAX]);
void ataca_se_puder(int tabuleiro[NMAX][NMAX], int i,int j);
void imprime_tabuleiro(int tabuleiro [NMAX][NMAX]);

void ataca_cavalo(int tabuleiro[NMAX][NMAX], int i_cavalo,int j_cavalo);
void ataca_rei(int tabuleiro[NMAX][NMAX], int i_rei,int j_rei);
void ataca_bispo(int tabuleiro [NMAX][NMAX], int i_bispo, int j_bispo);
void ataca_torre(int tabuleiro [NMAX][NMAX], int i_torre, int j_torre);
void ataca_rainha(int tabuleiro [NMAX][NMAX], int i, int j);

void generate (int N, int b, int c, int r, int f, int v);
void acumula_tabuleiro(int tab1[NMAX][NMAX], int tab2[NMAX][NMAX]);
void imprime_solucao(int solucao[NMAX], int n);
void todas_solucoes(int n);
void imprime_frequencias(void);


int main(int argc, char *argv[]) {


int N = atoi(argv[1]);
int b = atoi(argv[2]);
int c = atoi(argv[3]);
int r = atoi(argv[4]);
int f = atoi(argv[5]);
int v = atoi(argv[6]);

/*
int N, b, c, r, f, v;

N = 6;
b = 1;
c = 0;
r = 0;
f = 1;
v = 1;*/

D = N;

generate(N, b, c, r, f, v);

return 0;
}



int ultima_solucao(int solucao [NMAX], int n){
    int i;

    for (i = 0; i < n; i++) {

        if (solucao[i] < n - 1) {
            return 0;
        }
}
    return 1;
}

void imprime_solucao(int solucao [NMAX], int n) {

    int i;
    if (solucao_valida(solucao) == 0) {

        return;
    }

    nsolucoes++;

    zera_tabuleiro(tab_solucao);

    for (i = 0; i <= n - 1; i++) {
            tab_solucao[i][solucao[i]] = 1;
    }
        imprime_tabuleiro(tab_solucao);
        acumula_tabuleiro(ocorrencias, tab_solucao);
}

void imprime_frequencias(void) {
int i, j;

    if (frequencia == 0) {
    return;
    }

    printf("\n");

        for (i=0; i <= D - 1; i++){

            printf("\n");

                for (j = 0; j <= D - 1; j++) {
          printf("%.4f ", (float)ocorrencias[i][j] / (float) nsolucoes);

        }
    }
}


void todas_solucoes(int n){

int i;

    for (i = 0; i < n; i++){
        solucao[1] = 0;
    }

        do {
        i = 0;
        solucao[i]++;
        while (solucao[i] == n) {
            solucao[i] = 0;
            i++;
            solucao[i]++;
        }

        imprime_solucao(solucao, n);
    }

            while(!ultima_solucao(solucao, n));

}


void zera_tabuleiro(int tabuleiro [NMAX][NMAX]){
    int i, j;
    for (i=0; i <= D - 1; i++){
        for (j = 0; j <= D - 1; j++) {
         tabuleiro [i][j] = 0;
        }
    }
}

int solucao_valida(int solucao[NMAX]){

    int i;

int tab_ataque[NMAX][NMAX];

    zera_tabuleiro(tab_ataque);

    for (i = 0; i <= D - 1; i++) {
        ataca_rainha(tab_ataque, i, solucao[i]);

    }

    for (i = 0; i <= D - 1; i++) {
        if (tab_ataque[i][solucao[i]] == 1) {
                return 0;
        }
    }

    return 1;

}

void compara_tabuleiro (int tabuleiro1 [NMAX][NMAX], int tabuleiro2 [NMAX][NMAX]){
    int i, j;
    for (i = 0; i <= D - 1; i++) {
       for (j = 0; j <= D - 1; j++){
            if (tabuleiro1 [i][j] != tabuleiro2 [i][j]){
                printf("falha!\n");
                return;
                }
       }
    }

        printf("sucesso!");
}


void ataca_cavalo(int tabuleiro[NMAX][NMAX], int i_cavalo,int j_cavalo){

/*1,3 - 3,4 = -2, -1
1,5 - 3,4 = -2, 1
2,2 - 3,4 = -1, -2
2,6 - 3,4 = -1, 2
4,2 - 3,4 = 1, -2
4,6 - 3,4 = 1, 2
5,3 - 3,4 = 2, -1
5,5 - 3,4 = 2, 1*/

/*tabuleiro[i_cavalo - 2][j_cavalo - 1] = 1;
tabuleiro[i_cavalo - 2][j_cavalo + 1] = 1;
tabuleiro[i_cavalo - 1][j_cavalo - 2] = 1;
tabuleiro[i_cavalo - 1][j_cavalo + 2] = 1;
tabuleiro[i_cavalo + 1][j_cavalo - 2] = 1;
tabuleiro[i_cavalo + 1][j_cavalo - 2] = 1;
tabuleiro[i_cavalo + 2][j_cavalo - 1] = 1;
tabuleiro[i_cavalo + 2][j_cavalo + 1] = 1;*/

ataca_se_puder(tabuleiro, i_cavalo - 2, j_cavalo - 1);
ataca_se_puder(tabuleiro, i_cavalo - 2, j_cavalo + 1);
ataca_se_puder(tabuleiro, i_cavalo - 1, j_cavalo - 2);
ataca_se_puder(tabuleiro, i_cavalo - 1, j_cavalo + 2);
ataca_se_puder(tabuleiro, i_cavalo + 1, j_cavalo - 2);
ataca_se_puder(tabuleiro, i_cavalo + 1,j_cavalo + 2);
ataca_se_puder(tabuleiro, i_cavalo + 2, j_cavalo - 1);
ataca_se_puder(tabuleiro, i_cavalo + 2, j_cavalo + 1);

}

int tab_ataque_cavalo[NMAX][NMAX] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}

};



void ataca_rei(int tabuleiro[NMAX][NMAX], int i_rei,int j_rei) {


/*4,1 - 4,2 = 0, -1
4,3 - 4,2 = 0, 1
3,1 - 4,2 = -1, -1
3,2 - 4,2 = -1, 0
3,3 - 4,2 = -1, 1
5,1 - 4,2 = 1, -1
5,2 - 4,2 = 1, 0
5,3 - 4,2 = 1, 1

tabuleiro[i_rei][j_rei - 1] = 1;
tabuleiro[i_rei][j_rei + 1] = 1;
tabuleiro[i_rei - 1][j_rei - 1] = 1;
tabuleiro[i_rei - 1][j_rei] = 1;
tabuleiro[i_rei -1][j_rei + 1] = 1;
tabuleiro[i_rei + 1][j_rei - 1] = 1;
tabuleiro[i_rei + 1][j_rei] = 1;
tabuleiro[i_rei + 1][j_rei + 1] = 1;*/

ataca_se_puder(tabuleiro, i_rei, j_rei - 1);
ataca_se_puder(tabuleiro, i_rei, j_rei + 1);
ataca_se_puder(tabuleiro, i_rei - 1, j_rei - 1);
ataca_se_puder(tabuleiro, i_rei - 1, j_rei);
ataca_se_puder(tabuleiro, i_rei - 1, j_rei + 1);
ataca_se_puder(tabuleiro, i_rei + 1,j_rei - 1);
ataca_se_puder(tabuleiro, i_rei + 1, j_rei);
ataca_se_puder(tabuleiro, i_rei + 1, j_rei + 1);


}


int tab_ataque_rei[NMAX][NMAX] = {

    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1},
    {0, 0, 0, 0, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}

};

int posicao_valida(int linha, int coluna) {

    if (linha < 0 || linha >= D || coluna >= D || coluna < 0) {
        return 0;
    }
        else {
            return 1;
        }
}

void ataca_se_puder(int tabuleiro[NMAX][NMAX], int i,int j) {
    if(posicao_valida(i,j) == 1) {
        tabuleiro[i][j] = 1;
    }
}

int tab_ataque_bispo[NMAX][NMAX] = {

    {1, 0, 0, 0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 1}


};


void ataca_bispo(int tabuleiro [NMAX][NMAX], int i_bispo, int j_bispo) {
    int i_ataque_bispo, j_ataque_bispo;


    i_ataque_bispo = i_bispo + 1;
    j_ataque_bispo =  j_bispo + 1;

    while (posicao_valida(i_ataque_bispo, j_ataque_bispo) == 1) {
        tabuleiro[i_ataque_bispo][j_ataque_bispo] = 1;
        i_ataque_bispo = i_ataque_bispo + 1;
        j_ataque_bispo = j_ataque_bispo + 1;
}

    i_ataque_bispo = i_bispo - 1;
    j_ataque_bispo = j_bispo - 1;

    while (posicao_valida (i_ataque_bispo, j_ataque_bispo) == 1) {
        tabuleiro[i_ataque_bispo][j_ataque_bispo] = 1;
        i_ataque_bispo = i_ataque_bispo - 1;
        j_ataque_bispo = j_ataque_bispo - 1;
    }

    i_ataque_bispo = i_bispo + 1;
    j_ataque_bispo = j_bispo - 1;

    while (posicao_valida (i_ataque_bispo, j_ataque_bispo) == 1) {
        tabuleiro[i_ataque_bispo][j_ataque_bispo] = 1;
        i_ataque_bispo = i_ataque_bispo + 1;
        j_ataque_bispo = j_ataque_bispo - 1;
}

    i_ataque_bispo = i_bispo - 1;
    j_ataque_bispo = j_bispo + 1;

    while (posicao_valida (i_ataque_bispo, j_ataque_bispo) == 1) {
        tabuleiro[i_ataque_bispo][j_ataque_bispo] = 1;
        i_ataque_bispo = i_ataque_bispo - 1;
        j_ataque_bispo = j_ataque_bispo + 1;
}

        }

int tab_ataque_torre[NMAX][NMAX] = {

    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {1, 1, 1, 0, 1, 1, 1, 1},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0}

};

void ataca_torre(int tabuleiro [NMAX][NMAX], int i_torre, int j_torre){
    int i_ataque_torre, j_ataque_torre;

    i_ataque_torre = i_torre + 1;
    j_ataque_torre = j_torre;

   while (posicao_valida(i_ataque_torre, j_torre) == 1) {
        tabuleiro[i_ataque_torre][j_ataque_torre] = 1;
        i_ataque_torre++;
    }

    i_ataque_torre = i_torre - 1;
    j_ataque_torre = j_torre;

   while (posicao_valida(i_ataque_torre, j_torre) == 1) {
        tabuleiro[i_ataque_torre][j_ataque_torre] = 1;
        i_ataque_torre--;
    }

    i_ataque_torre = i_torre;
    j_ataque_torre = j_torre - 1;

     while (posicao_valida(i_torre, j_ataque_torre) == 1) {
        tabuleiro[i_ataque_torre][j_ataque_torre] = 1;
        j_ataque_torre--;
    }

    i_ataque_torre = i_torre;
    j_ataque_torre = j_torre + 1;

   while (posicao_valida(i_torre, j_ataque_torre) == 1) {
        tabuleiro[i_ataque_torre][j_ataque_torre] = 1;
        j_ataque_torre++;
    }

}

void ataca_rainha(int tabuleiro [NMAX][NMAX], int i, int j){

ataca_torre(tabuleiro, i, j);

    if (bispo == 1) {
        ataca_bispo(tabuleiro, i, j);
    }

    if (cavalo == 1) {
        ataca_cavalo(tabuleiro, i, j);
    }

    if (rei == 1) {
        ataca_rei(tabuleiro, i, j);
    }
}


int tab_ataque_rainha[NMAX][NMAX] = {

    {1, 1, 1, 1, 1, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0},
    {1, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 0, 1}
};

void imprime_tabuleiro(int tabuleiro [NMAX][NMAX]){
int i, j;

printf("\n");

    for (i=0; i <= D - 1; i++){

            printf("\n");

        for (j = 0; j <= D - 1; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("- ");
            }

            else {
                printf("X ");
            }

        }

    }

}


void acumula_tabuleiro(int tab1[NMAX][NMAX], int tab2[NMAX][NMAX]) {

int i, j;

    for (i=0; i <= D - 1; i++){
        for (j = 0; j <= D - 1; j++) {
         tab1[i][j] = tab1[i][j] + tab2[i][j];
        }
    }

}


void generate (int N, int b, int c, int r, int f, int v) {

bispo = b;
cavalo = c;
rei = r;
frequencia = f;
valores = v;

zera_tabuleiro(ocorrencias);
todas_solucoes(N);
imprime_frequencias();


}



/*
zera_tabuleiro(tabtest1);
ataca_cavalo(tabtest1, 3, 4);
compara_tabuleiro(tabtest1, tab_ataque_cavalo);
compara_tabuleiro(tabtest2, ataque_rei);
tabtest1[3][3] = 6;
zera_tabuleiro (tabtest2);
ataca_rei(tabtest2, 4, 6);


zera_tabuleiro(tabtest3);
ataca_torre(tabtest3, 3,3);
compara_tabuleiro(tabtest3, tab_ataque_torre);
imprime_tabuleiro(tab_ataque_torre);
imprime_tabuleiro(tabtest3);

*/



/*b = 1;
c = 1;
r = 1;

zera_tabuleiro(tabtest_rainha);
ataca_rainha(tabtest_rainha, 2, 2, b, c, r);
compara_tabuleiro(tabtest_rainha, tab_ataque_rainha);
imprime_tabuleiro(tabtest_rainha);
imprime_tabuleiro(tab_ataque_rainha);


N = 8;

tabuleiro [2][3] = 1;
tabuleiro [7][7] = 0;

*/
