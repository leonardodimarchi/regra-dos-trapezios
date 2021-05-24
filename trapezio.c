#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int grau;
    float intervaloInicial;
    float intervaloFinal;
} polinomial;

void main () {
    polinomial *polinomio = NULL;
    float *coeficientes = NULL;

    alocaPolinomial(&polinomio,1);

    recebeGrauPolinomio(polinomio);

    mostrarFormatoPolinomio(polinomio);

    alocaFloat(&coeficientes, polinomio->grau + 1);

    recebeCoeficientes(coeficientes, polinomio);
}

void recebeCoeficientes(float *coeficientes, polinomial *polinomio){
	int contador;
    char coeficienteLetra = 'a';

	printf("\n--- Digite os valores dos coeficientes ---\n");

	for(contador=0; contador < polinomio->grau + 1; contador++, coeficienteLetra++){
		printf("Valor de %c = ",coeficienteLetra);
        fflush(stdin);
		scanf("%f",coeficientes+contador);
	}
}

void recebeGrauPolinomio(polinomial *polinomio){
	printf("\nGrau do polinomio: ");
    fflush(stdin);
	scanf("%d",&polinomio->grau);
}

void mostrarFormatoPolinomio(polinomial *polinomio) {
    int contador, expoente;
    char coeficienteLetra = 'a';

    printf("\n");
    printf("%cx^%i ", coeficienteLetra++, polinomio->grau);
    for(contador=0, expoente = polinomio->grau -1; contador < polinomio->grau - 1; contador++, expoente--, coeficienteLetra++) {
        printf("+ %cx^%i ",coeficienteLetra,expoente);
    }
    printf("+ %c = 0\n", coeficienteLetra);
}

void alocaPolinomial(polinomial **p, int tam) {
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