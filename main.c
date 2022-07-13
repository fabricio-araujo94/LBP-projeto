#include "caio.h"
#include "lerimagem.h"
#include "processo.h"

#define MXCHAR 265
#define QTDIMG 656

int main(void){
	struct pgm img;
	struct pgm lbp;
  	char nome[TAM_N];
  	unsigned char *hist;

  	int k;
  	clock_t begin, end;
  	double time_per_img, time_total=0;
  	long long int a = 999999999;
	
	DIR *dir;
	
	if(!(dir = opendir("./datasets/oncotex_pgm"))){
	    puts("\nNão foi possível acessar o diretório!\n\n");
	    exit(1);
	}
	
	struct dirent *dent;
	
  	int i = 0;

  	// A função readdir irá ler todos os arquivos do diretório
  	while((dent = readdir(dir)) != NULL){
    		// É necessário uma string para armazenar o endereço das imagens
    		strcpy(nome,"./datasets/oncotex_pgm/");
		strcat(nome, dent->d_name);

    		hist = calloc(MXCHAR, sizeof(unsigned char));

    		if(i >= 2){ // Os primeiros dois nomes são apenas pontos
      			readPGMImage(&img, nome);

      			begin = clock();
      
      			LBP(&img, &lbp, hist);

      			end = clock();
		
			CSV(hist, dent->d_name[0]);

			time_per_img = (double)(end - begin) / CLOCKS_PER_SEC;

			time_total += time_per_img;

      			memset(nome, 0, TAM_N); // Apaga a string nome
    		}
		
	i++;
  }
	printf("\nTempo médio: %lf\n",time_total/QTDIMG);
	printf("Tempo Total: %lf\n",time_total);
	
	free(hist);

	closedir(dir);

	return 0;
}
