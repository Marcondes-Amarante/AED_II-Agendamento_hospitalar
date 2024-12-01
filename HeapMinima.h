#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[15];
    char especialidade[15];
    int atendimentoAgendado;
    int qtdHorasTrabalhadas;
}Medico;

typedef struct{
	float peso;
	float altura;
	char sintomas[60];
	char medicacoes[60];
}Diagnostico;

typedef struct{
	int id;
    int idade;
    char telefone[14];
    Diagnostico diagnostico_preliminar;
    int prioridade;
    char especialidade[15];
     
    int qtdVezesAtendido;
    Medico *medicoPrimeiroAtendimento;
}Paciente;

typedef struct{
	char nome[15];
	int qtdMedicos;
	Medico *medicos;
}Especialidade;

typedef struct {
    int hora;                     
    Especialidade especialidade;  
    Paciente paciente;           
    Medico medico;
	int agendado;                
} Atendimento;

typedef struct {
    Atendimento atendimentos[8];  
} Sala;

typedef struct{
    Sala salas[100];
    Medico *medicos;
    Especialidade *especialidades;
    int qtdPacientes;
    int qtdSalas;
    int qtdEspec;
    int qtdMedicos;
}Hospital;

typedef struct{
	Paciente *dados; //ponteiro para array de tamanho din�mico que ir� armazenar dados da heap
	int capacidade; //n�mero m�ximo de elem que a heap pode armazenar
	int tam; //n�mero de elementos atualmente presente na heap
}HeapMin;


void inicializarHeap(HeapMin *heap, int capacidade){
	heap->tam=0;
	heap->capacidade = capacidade;
	
	//alocando espa�o de mem�ria do array que ir� armazenar os elem da heap
	heap->dados = (Paciente *)malloc(heap->capacidade * sizeof(Paciente));
	
	//verificando se aloca��o foi bem sucedida
	if(heap->dados==NULL){
		printf("erro ao alocar heap na mem�ria");
		exit(1);
	}
}


void inserirElemHeap(HeapMin *heap, Paciente *paciente){
	
	//verificando se a heap se encontra cheia
	if(heap->tam == heap->capacidade){
		printf("Heap cheia, n�o � mais poss�vel armazenar elementos");
		return;
	}
	
	//adicionando inst�ncia de paciente ao final da heap
	int indice = heap->tam;
	heap->dados[indice] = *paciente;
	heap->tam++;
	
	//movendo elemento para posi��o correta conforme a sua prioridade
	while(indice>0 && heap->dados[indice].prioridade < heap->dados[(indice-1)/2].prioridade){
		Paciente pacienteTemporario = heap->dados[indice];
		
		//n� atual recebe paciente pai
		heap->dados[indice] = heap->dados[(indice-1)/2];
		
		//n� pai recebe paciente atual
		heap->dados[(indice-1)/2] = pacienteTemporario;
		
		//atualiza indice
		indice = (indice-1)/2;
	}
}


int removerElemHeap(HeapMin *heap) {
	
    // Tratando caso em que a heap est� vazia
    if (heap->tam <= 0) {
        printf("Heap underflow, n�o � poss�vel mais remover elementos da heap\n");
    }

    // Tratando caso em que a heap possui apenas 1 elemento
    if (heap->tam == 1) {
        heap->tam--;  // A heap fica vazia ap�s a remo��o
        return 1;
    }

    // Removendo n� raiz (elemento com menor prioridade)
    // Guardando paciente do n� raiz
    Paciente pacienteRaiz = heap->dados[0];

    // Atribuindo paciente do �ltimo n� para a posi��o referente ao n� raiz
    heap->dados[0] = heap->dados[heap->tam - 1];

    // Decrementando campo de tamanho da heap (atual quantidade de elementos)
    heap->tam--;

    // Reorganizando heap para manter prioridade m�nima
    int i = 0;
    while (i < heap->tam) { 
        int indiceNoEsquerdo = 2 * i + 1;
        int indiceNoDireito = 2 * i + 2;

        // Assumindo que o n� de menor prioridade � o referente � posi��o atual
        int menor = i;

        // Verificando se o n� filho referente � sub�rvore esquerda est� dentro da capacidade de elementos da heap
        if (indiceNoEsquerdo < heap->tam) {
            // Verificando se a prioridade do n� filho esquerdo � menor que a prioridade do n� pai assumido como menor
            if (heap->dados[indiceNoEsquerdo].prioridade < heap->dados[menor].prioridade) {
                menor = indiceNoEsquerdo;
            }
        }

        // Verificando se o n� filho referente � sub�rvore direita est� dentro da capacidade de elementos da heap
        if (indiceNoDireito < heap->tam) {
            // Verificando se a prioridade do n� filho direito � menor que a prioridade do n� pai assumido como menor
            if (heap->dados[indiceNoDireito].prioridade < heap->dados[menor].prioridade) {
                menor = indiceNoDireito;
            }
        }

        // Verificando se a prioridade do n� da posi��o atual "i" ainda continua como a "menor"
        // Caso sim, encerramos o la�o, pois n�o � necess�rio mais verifica��es
        if (menor == i) {
            break;
        }

        // Troca os elementos de posi��o (mover o n� de menor prioridade para cima)
        Paciente pacienteTemporario = heap->dados[i];
        heap->dados[i] = heap->dados[menor];
        heap->dados[menor] = pacienteTemporario;

        // Atualizando o �ndice atual "i" para o valor de �ndice de "menor"
        i = menor;
    }
    
    return 1;
}


void exibirHeap(HeapMin *heap, FILE *arquivo){
	for(int i=0; i<heap->tam; i++){
		fprintf(arquivo, "prioridade: %d, idPaciente: %d\n", heap->dados[i].prioridade, heap->dados[i].id);
	}
}
