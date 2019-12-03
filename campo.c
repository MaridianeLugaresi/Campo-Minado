#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Inicializa_matriz(int m[][10]){
	int i,j;

	for(i=1;i<9;i++){
		m[i][0] = 1;
		m[i][9] = 1;
		for(j=1;j<9;j++){
			m[i][j] = 0;
			m[0][j] = 1;
			m[9][j] = 1;
		}
	}
	m[0][0] = 1;
	m[9][9] = 1;
	m[9][0] = 1;
	m[0][9] = 1;
}

void Mostra_matriz(int m[][10]){
	int i,j;
	printf("  ");
	for(j=0;j<8;j++){
		printf(" %d", j+1);
	}
	printf("\n");

	for(i=1;i<9;i++){
		printf("%d |", i);
		for(j=1;j<9;j++){
			if(m[i][j] >= 10){	//são posições já abertas
				printf("%d ", (m[i][j] - 10));	//na saída vai o número correto
			}else{
				printf("? ");
			}
		}
		printf("|\n");
	}
	printf("\n\n");
}

void Escolhe_bombas_randomica(int m[][10]){
	int i, j, facilidade, k;
	srand(time(NULL));

	printf("Informe o nível de facilidade do jogo:\n");
	scanf("%d", &facilidade);
	for(k=0;k<60;k++){
		if((rand() % facilidade) == 0){	//quanto menor a facilidade mais facil o resultado ser igual a zero e entrar no laço
			i = 1 + (rand() % 8);
			j = 1 + (rand() % 8);
			m[i][j] = 9;
		}
	}
}

void Marca_bombas_adjacentes(int m[][10]){
	int cont,i,j;

	for(i=1;i<9;i++){
		for(j=1;j<9;j++){
			cont = 0;
			if(m[i][j] == 0){
				if(m[i][j-1] == 9){
					cont ++;
				}
				if(m[i-1][j-1] == 9){
					cont ++;
				}
				if(m[i-1][j] == 9){
					cont ++;
				}
				if(m[i+1][j-1] == 9){
					cont ++;
				}
				if(m[i+1][j] == 9){
					cont ++;
				}
				if(m[i+1][j+1] == 9){
					cont ++;
				}
				if(m[i][j+1] == 9){
					cont ++;
				}
				if(m[i-1][j+1] == 9){
					cont ++;
				}
			m[i][j] = cont;
			}
		}
	}

}

int Joga(int m[][10], int i, int j){

	if(m[i][j] == 9){
		m[i][j] += 10;
		Mostra_matriz(m);
		return 0;
	}else{
		m[i][j] += 10; //estrá marcando como abertas
		Mostra_matriz(m);
		return 1;
	}
}

int Valida_Posicao(int m[][10], int i, int j){
	if(i > 8 || j > 8){
		printf("\nInforme posições válidas!\n");
		return 0;
	}else if(m[i][j] >=10){
		printf("\nPosição já esta aberta!\n");
		return 0;
	}
	return 1;
}

int main(void) {
	setbuf(stdout,NULL);
	int m[10][10],i,j,retorno;

	Inicializa_matriz(m);

	Mostra_matriz(m);

	Escolhe_bombas_randomica(m);

	Marca_bombas_adjacentes(m);

	do{
		do{
			printf("Informe as coordenadas que deseja abrir:\n");
			scanf("%d""%d", &i, &j);
			retorno = Valida_Posicao(m,i,j);
		}while(retorno == 0);

		if (i == 0 && j == 0){
			break;
		}
		retorno = Joga(m,i,j);

	}while(retorno == 1);

	if(retorno == 0){
        printf("\n\n   Fim de Jogo\n\n");
        printf("   Você abriu uma bomba!\n\n");
	} else{
		printf("\n\n   Fim de Jogo\n\n");

	}

}


