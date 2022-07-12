#include "processo.h"

void LBP(struct pgm *pio, struct pgm *lbp){
    
    lbp->tipo = pio->tipo;
    lbp->r = pio->r;
    lbp->c = pio->c;
    lbp->mv = pio->mv;
    lbp->pData = (unsigned char*) malloc(lbp->r * lbp->c * sizeof(unsigned char));
    
    // É necessário encontrar os valores para cada
    // caso. Sim, isso vai demorar.
    
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
        
        //lbp->pData++;
    }
    
}

void histograma(struct pgm *lbp, unsigned char *hist){
    unsigned char numeros[TAM_N] = {'0'};
    
    unsigned char aux;

    puts("1");
    
    // Ordenação do vetor
    for(int i = 0; i < (lbp->c * lbp->r); i++) {
        for(int j = i + 1; j < (lbp->c * lbp->r) - i - 1; j++) { 
            if (lbp->pData[i] > lbp->pData[j]) {
                aux = lbp->pData[i];
                lbp->pData[i] = lbp->pData[j];
                lbp->pData[j] = aux;
            }
        }
    } 

    puts("2");

    //viewPGMImage(lbp);
    
    int k = 0;
    
    for(int i = 0; i < (lbp->c * lbp->r); i++){
        if(i == 0){
            numeros[k] = lbp->pData[i];
            k++;
          } else{
      
        for(int j = 0; numeros[j] != '\0'; j++){
            printf("%huu", numeros[j]);
            if (*(numeros + j) != lbp->pData[i]){
                numeros[k] = lbp->pData[i];
                k++;
                break;
            }
        }
          }
    }

    puts("3");
    
    int count;
    k = 0;
    for(int i = 0; *(numeros + i) != '\0'; i++){
        count = 0;
        
        for(int j = 0; j < (lbp->c * lbp->r); j++){
            if(*(numeros + i) == lbp->pData[j])
                count++;
        }
        
        hist[k++] = (unsigned char) count;
    }

    puts("4");
    
    puts("Histograma:");
    for(int i = 0; i < k; i++)
        printf("%d ", *(hist + i));
    
}


void CSV(unsigned char *hist, unsigned char rotulo){
    FILE *csv;
    
    if(!(csv = fopen("histograma.csv", "a+"))){
        puts("\nErro na criação ou na leitura do arquivo!\n\n");
        exit(2);
    }
    
    for(int i = 0; i < 256; i++)
        fprintf(csv, "%d, ", *(hist + i));
    
    fprintf(csv, "%huu", rotulo);
    
    fclose(csv);
}
