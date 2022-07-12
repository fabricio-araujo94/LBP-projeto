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
        numeros[0] = 0; 
        numeros[1] = 0; 
        numeros[2] = 0; 
        numeros[3] = *(v + 1);
        numeros[4] = *(v + c + 1);
        numeros[5] = *(v + c);
        numeros[6] = *(v + c - 1);
        numeros[7] = *(v - 1);
        break;
        
        case 1: // Beirada de baixo
        numeros[0] = *(v - c - 1);
        numeros[1] = *(v - c);
        numeros[2] = *(v - c + 1);
        numeros[3] = *(v + 1);
        numeros[4] = 0;
        numeros[5] = 0;
        numeros[6] = 0;
        numeros[7] = *(v - 1);
        break;
        
        case 2: // Beirada da esquerda
        numeros[0] = 0; 
        numeros[1] = *(v - c);
        numeros[2] = *(v - c + 1);
        numeros[3] = *(v + 1);
        numeros[4] = *(v + c + 1);
        numeros[5] = *(v + c);
        numeros[6] = 0;
        numeros[7] = 0;
        break;
        
        case 3: // Beirada da direita
        numeros[0] = *(v - c - 1);
        numeros[1] = *(v - c);
        numeros[2] = 0;
        numeros[3] = 0;
        numeros[4] = 0;
        numeros[5] = *(v + c);
        numeros[6] = *(v + c - 1);
        numeros[7] = *(v - 1);
        break;
        
        default:
        puts("\nOcorreu um erro durante a obtenção dos valores\n\n");
        exit(1);
    }
}

void valoresPonta(unsigned char *v, unsigned char *numeros, int c, int caso){
    switch (caso){
        case 0: // Ponta superior esquerda
        numeros[0] = 0;
        numeros[1] = 0;
        numeros[2] = 0;
        numeros[3] = *(v + 1);
        numeros[4] = *(v + c + 1);
        numeros[5] = *(v + c);
        numeros[6] = 0;
        numeros[7] = 0;
        break;
        
        case 1: // Ponta superior direita
        numeros[0] = 0;
        numeros[1] = 0;
        numeros[2] = 0;
        numeros[3] = 0;
        numeros[4] = 0;
        numeros[5] = *(v + c);
        numeros[6] = *(v + c - 1);
        numeros[7] = *(v - 1);
        break;
        
        case 2: // Ponta inferior esquerda
        numeros[0] = 0;
        numeros[1] = *(v - c);
        numeros[2] = *(v + c + 1);
        numeros[3] = *(v + 1);
        numeros[4] = 0;
        numeros[5] = 0;
        numeros[6] = 0;
        numeros[7] = 0;
        break;
        
        case 3: // Ponta inferior direita
        numeros[0] = *(v - c - 1);
        numeros[1] = *(v - c);
        numeros[2] = 0;
        numeros[3] = 0;
        numeros[4] = 0;
        numeros[5] = 0;
        numeros[6] = 0;
        numeros[7] = *(v - 1);
        break;
        
        default:
        puts("\nOcorreu um erro durante a obtenção de valores.\n\n");
        exit(1);
    }
}

unsigned char calculoLBP(unsigned char *pixel, unsigned char *v){
    int decimal = 0;
    
    for(int i = 0; i < 8; i++)
        if(*(v + i) >= *pixel)
            decimal += pow(2, i);
    
    return (unsigned char) decimal;
}