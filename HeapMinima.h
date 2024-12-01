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
	Paciente *dados; //ponteiro para array de tamanho dinâmico que irá armazenar dados da heap
	int capacidade; //número máximo de elem que a heap pode armazenar
	int tam; //número de elementos atualmente presente na heap
}HeapMin;


void inicializarHeap(HeapMin *heap, int capacidade){
	heap->tam=0;
	heap->capacidade = capacidade;
	
	//alocando espaço de memória do array que irá armazenar os elem da heap
	heap->dados = (Paciente *)malloc(heap->capacidade * sizeof(Paciente));
	
	//verificando se alocação foi bem sucedida
	if(heap->dados==NULL){
		printf("erro ao alocar heap na memória");
		exit(1);
	}
}


void inserirElemHeap(HeapMin *heap, Paciente *paciente){
	
	//verificando se a heap se encontra cheia
	if(heap->tam == heap->capacidade){
		printf("Heap cheia, não é mais possível armazenar elementos");
		return;
	}
	
	//adicionando instância de paciente ao final da heap
	int indice = heap->tam;
	heap->dados[indice] = *paciente;
	heap->tam++;
	
	//movendo elemento para posição correta conforme a sua prioridade
	while(indice>0 && heap->dados[indice].prioridade < heap->dados[(indice-1)/2].prioridade){
		Paciente pacienteTemporario = heap->dados[indice];
		
		//nó atual recebe paciente pai
		heap->dados[indice] = heap->dados[(indice-1)/2];
		
		//nó pai recebe paciente atual
		heap->dados[(indice-1)/2] = pacienteTemporario;
		
		//atualiza indice
		indice = (indice-1)/2;
	}
}


int removerElemHeap(HeapMin *heap) {
	
    // Tratando caso em que a heap está vazia
    if (heap->tam <= 0) {
        printf("Heap underflow, não é possível mais remover elementos da heap\n");
    }

    // Tratando caso em que a heap possui apenas 1 elemento
    if (heap->tam == 1) {
        heap->tam--;  // A heap fica vazia após a remoção
        return 1;
    }

    // Removendo nó raiz (elemento com menor prioridade)
    // Guardando paciente do nó raiz
    Paciente pacienteRaiz = heap->dados[0];

    // Atribuindo paciente do último nó para a posição referente ao nó raiz
    heap->dados[0] = heap->dados[heap->tam - 1];

    // Decrementando campo de tamanho da heap (atual quantidade de elementos)
    heap->tam--;

    // Reorganizando heap para manter prioridade mínima
    int i = 0;
    while (i < heap->tam) { 
        int indiceNoEsquerdo = 2 * i + 1;
        int indiceNoDireito = 2 * i + 2;

        // Assumindo que o nó de menor prioridade é o referente à posição atual
        int menor = i;

        // Verificando se o nó filho referente à subárvore esquerda está dentro da capacidade de elementos da heap
        if (indiceNoEsquerdo < heap->tam) {
            // Verificando se a prioridade do nó filho esquerdo é menor que a prioridade do nó pai assumido como menor
            if (heap->dados[indiceNoEsquerdo].prioridade < heap->dados[menor].prioridade) {
                menor = indiceNoEsquerdo;
            }
        }

        // Verificando se o nó filho referente à subárvore direita está dentro da capacidade de elementos da heap
        if (indiceNoDireito < heap->tam) {
            // Verificando se a prioridade do nó filho direito é menor que a prioridade do nó pai assumido como menor
            if (heap->dados[indiceNoDireito].prioridade < heap->dados[menor].prioridade) {
                menor = indiceNoDireito;
            }
        }

        // Verificando se a prioridade do nó da posição atual "i" ainda continua como a "menor"
        // Caso sim, encerramos o laço, pois não é necessário mais verificações
        if (menor == i) {
            break;
        }

        // Troca os elementos de posição (mover o nó de menor prioridade para cima)
        Paciente pacienteTemporario = heap->dados[i];
        heap->dados[i] = heap->dados[menor];
        heap->dados[menor] = pacienteTemporario;

        // Atualizando o índice atual "i" para o valor de índice de "menor"
        i = menor;
    }
    
    return 1;
}


void exibirHeap(HeapMin *heap, FILE *arquivo){
	for(int i=0; i<heap->tam; i++){
		fprintf(arquivo, "prioridade: %d, idPaciente: %d\n", heap->dados[i].prioridade, heap->dados[i].id);
	}
}
