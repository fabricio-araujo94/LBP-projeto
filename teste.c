#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAM 8

struct pgm{
	int tipo;
	int c;
	int r;
	int mv;
	unsigned char *pData;
};

void readPGMImage(struct pgm *, char *);
void viewPGMImage(struct pgm *);
void writePGMImage(struct pgm *, char *);

void LBP(struct pgm *, struct pgm *);

void valoresMeio(unsigned char *, unsigned char *, int);
void valoresBeirada(unsigned char *, unsigned char *, int, int);
void valoresPonta(unsigned char *, unsigned char *, int, int);

unsigned char tahNoMeio(unsigned char *, unsigned char *);
unsigned char tahNaBeirada(unsigned char *, int, unsigned char*);
unsigned char tahNaPonta(unsigned char *, int , unsigned char *);

int main(int argc, char *argv[]){

	struct pgm img;
	struct pgm lpb;

	if (argc!=3){
		printf("Formato: \n\t %s <imagemEntrada.pgm> <imagemSaida.pgm>\n",argv[0]);
		exit(1);
	}

	readPGMImage(&img,argv[1]);
	
	LBP(&img, &lpb);

	writePGMImage(&lpb, argv[2]);

	viewPGMImage(&lpb);

	return 0;

}

void readPGMImage(struct pgm *pio, char *filename){

	FILE *fp;
	char ch;

	if (!(fp = fopen(filename,"r"))){
		perror("Erro.");
		exit(1);
	}

	if ( (ch = getc(fp))!='P'){
		puts("A imagem fornecida não está no formato pgm");
		exit(2);
	}
	
	pio->tipo = getc(fp)-48;
	
	fseek(fp,1, SEEK_CUR);

	while((ch=getc(fp))=='#'){
		while( (ch=getc(fp))!='\n');
	}

	fseek(fp,-1, SEEK_CUR);

	fscanf(fp, "%d %d",&pio->c,&pio->r);
	if (ferror(fp)){ 
		perror(NULL);
		exit(3);
	}	
	fscanf(fp, "%d",&pio->mv);
	fseek(fp,1, SEEK_CUR);

	pio->pData = (unsigned char*) malloc(pio->r * pio->c * sizeof(unsigned char));

	switch(pio->tipo){
		case 2:
			puts("Lendo imagem PGM (dados em texto)");
			for (int k=0; k < (pio->r * pio->c); k++){
				fscanf(fp, "%hhu", pio->pData+k);
			}
		break;	
		case 5:
			puts("Lendo imagem PGM (dados em binário)");
			fread(pio->pData,sizeof(unsigned char),pio->r * pio->c, fp);
		break;
		default:
			puts("Não está implementado");
	}
	
	fclose(fp);

}

void writePGMImage(struct pgm *pio, char *filename){
	FILE *fp;
	char ch;

	if (!(fp = fopen(filename,"wb"))){
		perror("Erro.");
		exit(1);
	}

	fprintf(fp, "%s\n","P5");
	fprintf(fp, "%d %d\n",pio->c, pio->r);
	fprintf(fp, "%d\n", 255);

	fwrite(pio->pData, sizeof(unsigned char),pio->c * pio->r, fp);

	fclose(fp);

}


void viewPGMImage(struct pgm *pio){
	printf("Tipo: %d\n",pio->tipo);
	printf("Dimensões: [%d %d]\n",pio->c, pio->r);
	printf("Max: %d\n",pio->mv);

	for (int k=0; k < (pio->r * pio->c); k++){
		if (!( k % pio->c)) printf("\n");
		printf("%2hhu ",*(pio->pData+k));
	}	
	printf("\n");
}

void LBP(struct pgm *pio, struct pgm *lbp){
    unsigned char buffer[TAM];
    
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

/* Agora eu vou criar funções para encontrar os valores.
Se fosse alocação estática, era simples. Mas não é. */

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