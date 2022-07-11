#include "obtervalores.h"

void valoresMeio(unsigned char *v, unsigned char *numeros, int c){
    numeros[0] = *(v - c - 1);
    numeros[1] = *(v - c);
    numeros[2] = *(v - c + 1);
    numeros[3] = *(v + 1);
    numeros[4] = *(v + c + 1);
    numeros[5] = *(v + c);
    numeros[6] = *(v + c - 1);
    numeros[7] = *(v - 1);
}

void valoresBeirada(unsigned char *v, unsigned char *numeros, int c, int caso){
    switch(caso){
        case 0: // Beirada de cima
        numeros[0] = *(v + 1);
        numeros[1] = *(v + c + 1);
        numeros[2] = *(v + c);
        numeros[3] = *(v + c - 1);
        numeros[4] = *(v - 1);
        break;
        
        case 1: // Beirada de baixo
        numeros[0] = *(v - c - 1);
        numeros[1] = *(v - c);
        numeros[2] = *(v - c + 1);
        numeros[3] = *(v + 1);
        numeros[4] = *(v - 1);
        break;
        
        case 2: // Beirada da esquerda
        numeros[0] = *(v - c);
        numeros[1] = *(v - c + 1);
        numeros[2] = *(v + 1);
        numeros[3] = *(v + c + 1);
        numeros[4] = *(v + c);
        break;
        
        case 3: // Beirada da direita
        numeros[0] = *(v - c - 1);
        numeros[1] = *(v - c);
        numeros[2] = *(v + c);
        numeros[3] = *(v + c - 1);
        numeros[4] = *(v - 1);
        break;
        
        default:
        puts("\nOcorreu um erro durante a obtenção dos valores\n\n");
        exit(1);
    }
}

void valoresPonta(unsigned char *v, unsigned char *numeros, int c, int caso){
    switch (caso){
        case 0: // Ponta superior esquerda
        numeros[0] = *(v + 1);
        numeros[1] = *(v + c + 1);
        numeros[2] = *(v + c);
        break;
        
        case 1: // Ponta superior direita
        numeros[0] = *(v + c);
        numeros[1] = *(v + c - 1);
        numeros[2] = *(v - 1);
        break;
        
        case 2: // Ponta inferior esquerda
        numeros[0] = *(v - c);
        numeros[1] = *(v + c + 1);
        numeros[2] = *(v + 1);
        break;
        
        case 3: // Ponta inferior direita
        numeros[0] = *(v - c - 1);
        numeros[1] = *(v - c);
        numeros[2] = *(v - 1);
        break;
        
        default:
        puts("\nOcorreu um erro durante a obtenção de valores.\n\n");
        exit(1);
    }
}

      unsigned char tahNoMeio(unsigned char *pixel, unsigned char *v){
    int decimal = 0;
    
    for(int i = 0; *(v + i) != '\0'; i++)
        if(*(v + i) >= *pixel)
            decimal += pow(2, i);
    
    return (unsigned char) decimal;
}

unsigned char tahNaBeirada(unsigned char *pixel, int caso, unsigned char *v){
    int decimal = 0;
    int base[] = {0, 0, 0, 0, 0};

    switch(caso){
        case 0: // Beirada da parte de cima da matriz
        base[0] = 3;
        base[1] = 4;
        base[2] = 5;
        base[3] = 6;
        base[4] = 7;
        for(int i = 0; i < 5; i++)
            if(*(v + i) >= *pixel) 
                decimal += pow(2, base[i]);
        break;
    
        case 1: // Beirada da parte de baixo da matriz
        base[0] = 0;
        base[1] = 1;
        base[2] = 2;
        base[3] = 3;
        base[4] = 7;
        
        for(int i = 0; i < 5; i++)
            if(*(v + i) >= *pixel)
                decimal += pow(2, base[i]);
        break;
                    
        case 2: // Beirada do lado esquerdo da matriz
        base[0] = 1;
        base[1] = 2;
        base[2] = 3;
        base[3] = 4;
        base[4] = 5;
        
        for(int i = 0; i < 5; i++)
            if(*(v + i) >= *pixel)
                decimal += pow(2, base[i]);
        break;
            
        case 3: // Beirada do lado direito da matriz
        base[0] = 0;
        base[1] = 1;
        base[2] = 5;
        base[3] = 6;
        base[4] = 7;
        
        for(int i = 0; i < 5; i++)
            if(*(v + i) >= *pixel)
                decimal += pow(2, base[i]);
        break;
            
        default:
        puts("\nErro no cálculo do LPB.\n\n");
        exit(1);
    }
    
    return (unsigned char) decimal;
}
    
unsigned char tahNaPonta(unsigned char *pixel, int caso, unsigned char *v){
    int decimal = 0;
    int base[] = {0, 0, 0, 0, 0};
    
    switch(caso){
        case 0: // A ponta superior esquerda da matriz
        base[0] = 3;
        base[1] = 4;
        base[2] = 5;
        
        for(int i = 0; i < 3; i++)
            if(*(v + i) >= *pixel)
                decimal += pow(2, base[i]);
        break;
        
        case 1: // A ponta superior direita da matriz
        base[0] = 5;
        base[1] = 6;
        base[2] = 7;

        for(int i = 0; i < 3; i++)
            if(*(v + i) >= *pixel)
                decimal += pow(2, base[i]);
        break;
        
        case 2: // A ponta inferior esquerda da matriz
        base[0] = 1;
        base[1] = 2;
        base[2] = 3;

        for(int i = 0; i < 3; i++)
            if(*(v + i) >= *pixel)
                decimal += pow(2, base[i]);
        break;
        
        case 3: // A ponta inferior direita da matriz
        base[0] = 0;
        base[1] = 1;
        base[2] = 7;

        for(int i = 0; i < 3; i++)
            if(*(v + i) >= *pixel)
                decimal += pow(2, base[i]);
        break;
        
        default:
        puts("\n Erro no cálculo do LPB\n\n");
        exit(1);
    }
    
    return (unsigned char) decimal;
}