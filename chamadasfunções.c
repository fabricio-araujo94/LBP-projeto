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
                lbp->pData[i] = tahNaPonta(pio->pData+i, caso, numeros);
            } else if ((i + 1) / pio->c == 1) {  // Canto superior direito
                caso = 1;
                valoresPonta(pio->pData+i, numeros, pio->c, caso);
                lbp->pData[i] = tahNaPonta(pio->pData+i, caso, numeros);;
            } else if(i + 1 == (pio->r * pio->c) - pio->c) { // Canto inferior esquerdo
                caso = 2;
                valoresPonta(pio->pData+i, numeros, pio->c, caso);
                lbp->pData[i] = tahNaPonta(pio->pData+i, caso, numeros);
            } else if(i + 1 == (pio->r * pio->c)) { // Canto inferior direito
                caso = 3;
                valoresPonta(pio->pData+i, numeros, pio->c, caso);
                lbp->pData[i] = tahNaPonta(pio->pData+i, caso, numeros);
            }
            
        // Caso o pixel selecionado esteja na beirada da matriz    
        } else if (i % pio->c == 0  || (i + 1) % pio->c == 0 || i - pio->c < 0 || i + pio->c > (pio->r * pio->c)){
            
            if(i - pio->c < 0) { // Parte de cima
                caso = 0;
                valoresBeirada(pio->pData+i, numeros, pio->c, caso);
                lbp->pData[i] = tahNaBeirada(pio->pData+i, caso, numeros);
            } else if(i + pio->c > (pio->r * pio->c)) { // Parte de baixo
                caso = 1;
                valoresBeirada(pio->pData+i, numeros, pio->c, caso);
                lbp->pData[i] = tahNaBeirada(pio->pData+i, caso, numeros);
            } else if((i + 1) % pio->c == 0) { // Lado esquerdo
                caso = 2;
                valoresBeirada(pio->pData+i, numeros, pio->c, caso);
                lbp->pData[i] = tahNaBeirada(pio->pData+i, caso, numeros);
            } else if(i % pio->c == 0) { // Lado direito
                caso = 3;
                valoresBeirada(pio->pData+i, numeros, pio->c, caso);
                lbp->pData[i] = tahNaBeirada(pio->pData+i, caso, numeros);
            }
            
        } else{
            valoresMeio(pio->pData, numeros, pio->c);
            lbp->pData[i] = tahNoMeio(pio->pData+i, numeros);
        }
        
        //lbp->pData++;
    }
    
}