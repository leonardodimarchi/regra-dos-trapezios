//Bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Estruturas

//Armazena os valores relacionados a construcao da integral 
typedef struct {
    int grau;
    float intervaloInicial;
    float intervaloFinal;
} integral;

//Armazena variaveis importantes para a realizacao do metodo
typedef struct {
    int numeroDivisoes;
    int quantidadeLinhasTabela;
    float valorH;
    float resultadoIntegral;
} resultadoTrapezio; 

//Representa uma linha da tabela de valores, sendo utilizado em um "array" para compor a tabela completa
typedef struct {
    float x;
    float fX;
} linhaTabela; 

//Prototipo das funcoes gerais
void calculaMostraIntegralTrapezio(linhaTabela *linhasTabela, resultadoTrapezio *resultados);
void calculaValoresTabela(linhaTabela *linhasTabela, integral *polinomio, resultadoTrapezio *resultados, float *coeficientes);
void mostraTabela(linhaTabela *linhasTabela, resultadoTrapezio *resultados);
void calculaMostraValorH(integral *polinomio, resultadoTrapezio *resultados);
void recebeIntervalo(integral *polinomio);
void mostrarFormatoPolinomio(integral *polinomio);
float calcularFuncao(float *coeficientes, integral *polinomio, float x);

//Prototipo das funcoes de alocacao
void alocaIntegral(integral **p, int tam);
void alocaResultado(resultadoTrapezio **p, int tam);
void alocaLinhaTabela(linhaTabela **p, int tam);
void alocaFloat(float **p, int tam);
void alocaInt(int **p, int tam);

void main () {
    integral *polinomio = NULL; //Ponteiro que representa o polinomio a ser trabalhado
    resultadoTrapezio *resultados = NULL; //Ponteiro que possui os resultados/valores importantes para realizar o metodo
    linhaTabela *linhasTabela = NULL; //Ponteiro utilizado para armazenar as linhas da tabela de valores

    float *coeficientes = NULL;
    char perguntaRepeticaoMesmaIntegracao = 'n', perguntaRepeticaoOutraIntegracao = 'n';

    do {
        system("cls");

        printf("___ Metodos Numericos - Regra dos Trapezios ___\n");

        //Procedimentos iniciais para criacao do polinomio.
        alocaIntegral(&polinomio,1);
        recebeGrauPolinomio(polinomio);
        mostrarFormatoPolinomio(polinomio);

        //Aloca os coeficientes, com espaco para uma constante para entao recebe-los.
        alocaFloat(&coeficientes, polinomio->grau + 1);
        recebeCoeficientes(coeficientes, polinomio);

        //Aloca os resultados e recebe os valores de intervalo.
        alocaResultado(&resultados, 1);
        recebeIntervalo(polinomio);

        do {
            //Recebe a quantidade de trapezios / divisoes que serao feitas
            recebeNumeroDivisoes(polinomio, resultados);

            printf("\n\t___ Resultados ___\n");

            //Calcula o valor de h = (b-a)/n
            calculaMostraValorH(polinomio, resultados);

            //Calcula a quantidade de linhas necessarias para a tabela  ( (b-a)/h )
            resultados->quantidadeLinhasTabela = round(((polinomio->intervaloFinal - polinomio->intervaloInicial)/resultados->valorH)+1);

            //Aloca as linhas da tabela e calcula o f(x) para cada valor de intervalo, com base na quantidade de linhas necessarias.
            alocaLinhaTabela(&linhasTabela, resultados->quantidadeLinhasTabela);
            calculaValoresTabela(linhasTabela, polinomio, resultados, coeficientes);

            //Calcula a integral do trapezio ( (h/2) * ( f(x_0) + f(x_n) + 2*SOMA_INTERVALOS( f(x_k) ) ) )
            calculaMostraIntegralTrapezio(linhasTabela, resultados);

            printf("\n\t______________\n");

            //Pergunta se deseja clacular a partir de outro numero de trapezios
            printf("\n\nDeseja calcular com outro numero de divisao (trapezios) ? [s / n]: ");
            fflush(stdin);
            scanf("%c",&perguntaRepeticaoMesmaIntegracao);    
        
        }while(perguntaRepeticaoMesmaIntegracao != 'N' && perguntaRepeticaoMesmaIntegracao != 'n');

        //Pergunta se deseja clacular a partir de outra integracao
        printf("\nDeseja realizar os calculos a partir de outra integracao numerica ? [s / n]: ");
        fflush(stdin);
        scanf("%c",&perguntaRepeticaoOutraIntegracao);    

    }while(perguntaRepeticaoOutraIntegracao != 'N' && perguntaRepeticaoOutraIntegracao != 'n');

    printf("\n\n___ Obrigado por utilizar nosso programa ___");
    printf("\n\n\tPor: Leonardo e Luiz =)\n\n");
}

void calculaMostraIntegralTrapezio(linhaTabela *linhasTabela, resultadoTrapezio *resultados) {
    int contador;
    float somaIntervalos = 0;

    //Realiza a soma dos Intervalos, desconsiderando o intervalo inicial e o intervalo final, assim como descrito na "formula"
    for(contador=1; contador < resultados->quantidadeLinhasTabela-1; contador++) {
        somaIntervalos += (linhasTabela + contador)->fX;
    }

    resultados->resultadoIntegral = (resultados->valorH / 2) * (linhasTabela->fX + (linhasTabela + resultados->quantidadeLinhasTabela-1)->fX + 2*somaIntervalos);

    printf("\n\n\tITR = %.4f", resultados->resultadoIntegral);
}

void calculaValoresTabela(linhaTabela *linhasTabela, integral *polinomio, resultadoTrapezio *resultados, float *coeficientes) {
    int contador;
    float valorDeX = 0;

    //Calcula e insere os valores na tabela, utilizando a estrutura de linhaTabela, representando cada linha da tabela.
    for(contador=0; contador < resultados->quantidadeLinhasTabela; contador++) {
        if (contador == 0) {
            valorDeX = polinomio->intervaloInicial;
        } else {
            valorDeX += resultados->valorH;
        }

        (linhasTabela+contador)->x = valorDeX;

        //Recebe o valor atraves da chamada da funcao de calculo
        (linhasTabela+contador)->fX = calcularFuncao(coeficientes, polinomio, (linhasTabela+contador)->x);
    }

    mostraTabela(linhasTabela, resultados);
}

float calcularFuncao(float *coeficientes, integral *polinomio, float x) {
    int contador, expoente;
    float resultado = 0;

    //Calcula o f(x) para o x enviado como parametro
    for(contador=0, expoente=polinomio->grau; contador <= polinomio->grau; contador++, expoente--) {
        resultado += *(coeficientes+contador) * pow(x, expoente);
    }

    return resultado;
}

void mostraTabela(linhaTabela *linhasTabela, resultadoTrapezio *resultados) {
    int f;

    printf("\n\n\t_Tabela de valores_");

    printf("\n\n\tx\tf(x)");

    for(f=0; f<resultados->quantidadeLinhasTabela; f++){
        printf("\n\t%.4f\t%.4f",(linhasTabela+f)->x,(linhasTabela+f)->fX);
    }
}

void calculaMostraValorH(integral *polinomio, resultadoTrapezio *resultados) {

    //Calcula o valor de H, conforme: h = (b-a)/n
    resultados->valorH = (polinomio->intervaloFinal - polinomio->intervaloInicial) / resultados->numeroDivisoes;

    printf("\n\th = (%.4f - %.4f) / %i",polinomio->intervaloFinal,polinomio->intervaloInicial, resultados->numeroDivisoes);
    printf("\n\th = %.4f",resultados->valorH);
}

void recebeNumeroDivisoes(integral *polinomio, resultadoTrapezio *resultado) {
    printf("\nDigite o numero de divisoes do intervalo [%.4f, %.4f]: ", polinomio->intervaloInicial, polinomio->intervaloFinal);
    scanf("%i",&resultado->numeroDivisoes);
}

void recebeIntervalo(integral *polinomio) {
    float aux;

    //Repeticao ate que os intervalos sejam diferentes
    do{
        printf("\nIntervalo inicial: ");
        scanf("%f", &polinomio->intervaloInicial);

        printf("Intervalo final: ");
        scanf("%f", &polinomio->intervaloFinal);

        if (polinomio->intervaloFinal == polinomio->intervaloInicial) {
            printf("\nIntervalo invalido, tente novamente.\n");
        }

    }while(polinomio->intervaloFinal == polinomio->intervaloInicial);

    //Caso o intervalo final seja menor que o inicial, ocorre a inversao
    if (polinomio->intervaloInicial > polinomio->intervaloFinal) {
        printf("\nOs valores de intervalo foram reajustados: ");
        printf("\n- Intervalo inicial: %.4f", polinomio->intervaloInicial);
        printf("\n- Intervalo final: %.4f", polinomio->intervaloFinal);

        aux = polinomio->intervaloFinal;

        polinomio->intervaloFinal = polinomio->intervaloInicial;
        polinomio->intervaloInicial = aux;
    }
}

void recebeCoeficientes(float *coeficientes, integral *polinomio) {
	int contador;
    char coeficienteLetra = 'a';

	printf("\n___ Digite os valores dos coeficientes ___\n\n");

    //Recebe os coeficientes, incluindo o que acompanha x^0
	for(contador=0; contador < polinomio->grau + 1; contador++, coeficienteLetra++){
		printf("Valor de %c = ",coeficienteLetra);
        fflush(stdin);
		scanf("%f",coeficientes+contador);
	}
}

void recebeGrauPolinomio(integral *polinomio){
    do {
        printf("\nGrau do polinomio (max: 10): ");
        fflush(stdin);
        scanf("%d",&polinomio->grau);

        if (polinomio->grau > 10){
            printf("\nPor favor, insira o grau respeitando o valor maximo (max: 10).\n");
        }
    }while(polinomio->grau > 10);
	
}

void mostrarFormatoPolinomio(integral *polinomio) {
    int contador, expoente;
    char coeficienteLetra = 'a';

    //Printa o polinomio gerado para o usuario, com as indicacoes dos coeficientes para insercao
    printf("\n");
    printf("%cx^%i ", coeficienteLetra++, polinomio->grau);
    for(contador=0, expoente = polinomio->grau -1; contador < polinomio->grau - 1; contador++, expoente--, coeficienteLetra++) {
        printf("+ %cx^%i ",coeficienteLetra,expoente);
    }
    printf("+ %c = 0\n", coeficienteLetra);
}

void alocaIntegral(integral **p, int tam) {
    if((*p=(integral*)realloc(*p,tam*sizeof(integral)))==NULL){
        printf("\nFalha na alocacao dinamica !(integral)\n");
        exit(1);
    }
}

void alocaResultado(resultadoTrapezio **p, int tam) {
    if((*p=(resultadoTrapezio*)realloc(*p,tam*sizeof(resultadoTrapezio)))==NULL){
        printf("\nFalha na alocacao dinamica !(resultadoTrapezio)\n");
        exit(1);
    }
}

void alocaLinhaTabela(linhaTabela **p, int tam){
    if((*p=(linhaTabela*)realloc(*p,tam*sizeof(linhaTabela)))==NULL){
        printf("\nFalha na alocacao dinamica !(linhaTabela)\n");
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