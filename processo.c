#include "processo.h"

void LBP(struct pgm *pio, struct pgm *lbp, unsigned char *hist){
    
    lbp->tipo = pio->tipo;
    lbp->r = pio->r;
    lbp->c = pio->c;
    lbp->mv = pio->mv;
    lbp->pData = (unsigned char*) malloc(lbp->r * lbp->c * sizeof(unsigned char));
    
    int caso;
    unsigned char numeros[TAM];
    
    for(int i = 0; i < (pio->r * pio->c); i++){
        // Caso o pixel selecionado esteja numa das pontas da matriz
        if( (i == 0) || (i + 1 == (pio->r * pio->c)) || (i + 1) / pio->c == 1 || (i + 1) == ((pio->r * pio->c) - pio->c)){
            
            if(i == 0) { // Canto superior esquerdo
                caso = 0;
                valoresPonta(pio->pData+i, numeros, pio->c, caso);
                lbp->pData[i] = calculoLBP(pio->pData+i, numeros);
            } else if ((i + 1) / pio->c == 1) {  // Canto superior direito
                caso = 1;
                valoresPonta(pio->pData+i, numeros, pio->c, caso);
                lbp->pData[i] = calculoLBP(pio->pData+i, numeros);
            } else if(i + 1 == (pio->r * pio->c) - pio->c) { // Canto inferior esquerdo
                caso = 2;
                valoresPonta(pio->pData+i, numeros, pio->c, caso);
                lbp->pData[i] = calculoLBP(pio->pData+i, numeros);
            } else if(i + 1 == (pio->r * pio->c)) { // Canto inferior direito
                caso = 3;
                valoresPonta(pio->pData+i, numeros, pio->c, caso);
                lbp->pData[i] = calculoLBP(pio->pData+i, numeros);
            }
            
        // Caso o pixel selecionado esteja na beirada da matriz    
        } else if ((i % pio->c == 0)  || ((i + 1) % pio->c == 0) || (i - pio->c < 0) || (i + pio->c > (pio->r * pio->c))){
            
            if(i - pio->c < 0) { // Parte de cima
                caso = 0;
                valoresBeirada(pio->pData+i, numeros, pio->c, caso);
                lbp->pData[i] = calculoLBP(pio->pData+i, numeros);
            } else if(i + pio->c > (pio->r * pio->c)) { // Parte de baixo
                caso = 1;
                valoresBeirada(pio->pData+i, numeros, pio->c, caso);
                lbp->pData[i] = calculoLBP(pio->pData+i, numeros);
            } else if(i % pio->c == 0) { // Lado esquerdo
                caso = 2;
                valoresBeirada(pio->pData+i, numeros, pio->c, caso);
                lbp->pData[i] = calculoLBP(pio->pData+i, numeros);
            } else if((i + 1) % pio->c == 0) { // Lado direito
                caso = 3;
                valoresBeirada(pio->pData+i, numeros, pio->c, caso);
                lbp->pData[i] = calculoLBP(pio->pData+i, numeros);
            }
            
        } else{
            valoresMeio(pio->pData, numeros, pio->c);
            lbp->pData[i] = calculoLBP(pio->pData+i, numeros);
        }
        
    }

      for(int i = 0; i < pio->r * pio->c; i++){
        *(hist  + lbp->pData[i]) += 1;
      }
    
}

void CSV(unsigned char *hist, char rotulo){
    FILE *csv;
    
    if(!(csv = fopen("histograma.csv", "a+"))){
        puts("\nErro na criação ou na leitura do arquivo!\n\n");
        exit(2);
    }
    
    for(int i = 0; i < 256; i++)
        fprintf(csv, "%d, ", *(hist + i));
    
    fprintf(csv, "%d\n", rotulo - 48);
    
    fclose(csv);
}
