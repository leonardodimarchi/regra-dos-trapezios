#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int grau;
    float *coeficientes;
    float intervaloInicial;
    float intervaloFinal;
} polinomial;

void main () {
    polinomial *polinomio = NULL;

    alocaPolinomio(&polinomio,1);

    recebeGrauPolinomio(polinomio);

    alocaFloat(&polinomio->coeficientes, polinomio->grau); // Arrumar

    recebeCoeficientes(polinomio);
}

void recebeCoeficientes(polinomial *polinomio){
	int contador;

	printf("\n--- Digite os valores dos coeficientes ---\n");

	for(contador=0; contador < polinomio->grau; contador++){
		printf("x[%d] = ",contador);
		scanf("%f",&(polinomio->coeficientes)+contador); //Arrumar
	}

    	for(contador=0; contador < polinomio->grau; contador++){
		printf("x[%d] = ",(polinomio->coeficientes)+contador);
	}
}

void recebeGrauPolinomio(polinomial *polinomio){
	printf("\nGrau do polinomio: ");
	scanf("%d",&polinomio->grau);
}

void alocaPolinomio(polinomial **p, int tam) {
    if((*p=(polinomial*)realloc(*p,tam*sizeof(polinomial)))==NULL){
        printf("\nFalha na alocacao dinamica !(polinomio)\n");
        exit(1);
    }
}

void alocaFloat(float **p, int tam){
    if((*p=(float*)realloc(*p,tam*sizeof(float)))==NULL){
        printf("\nFalha na alocacao dinamica !(float)\n");
        exit(1);
    }
}

void alocaInt(int **p, int tam){
    if((*p=(int*)realloc(*p,tam*sizeof(int)))==NULL){
        printf("\nFalha na alocacao dinamica ! (int)\n");
        exit(1);
    }
}