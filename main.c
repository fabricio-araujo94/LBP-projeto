#include "caio.h"
#include "lerimagem.h"
#include "processo.h"

int main(void){
	struct pgm img;
	struct pgm lbp;
  char nome[TAM_N];
  //unsigned char *hist;

	/*if (argc!=2){
		printf("Formato: \n\t %s <endereço das imagens> \n",argv[0]);
		exit(1);
	} */
	
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

    if(i >= 2){ // Os primeiros dois nomes são apenas pontos
      readPGMImage(&img, nome);
      LBP(&img, &lbp);

      //hist = malloc(256 * sizeof(unsigned char));
      //histograma(&lbp, hist);

      memset(nome, 0, TAM_N); // Apaga a string nome
    }
    
    i++;
  }
    
  //writePGMImage(&lpb, argv[2]);
	//viewPGMImage(&lpb);

  closedir(dir);

	return 0;

}
