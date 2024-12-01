#include <stdio.h>
#include <stdlib.h>



typedef struct{
	int *idPaciente; //ponteiro para array de tamanho a ser alocado dinamicamente
	int frente; //indice para posi��o de �nicio da fila
	int traseira; //indice para posi��o referente ao fim da fila
	int capacidade; //quantidade m�xima de elementos suportados pela fila
	int tamanho; //atual quantidade de elementos contidos na fila
}FilaCircular;


void inicializarFila(FilaCircular **fila, int capacidade) {
    *fila = (FilaCircular *)malloc(sizeof(FilaCircular));
    (*fila)->frente = 0;
    (*fila)->traseira = -1;
    (*fila)->capacidade = capacidade;
    (*fila)->tamanho = 0;
    
    //alocando dinamicamente espa�o para armazenar id's dos pacientes
    (*fila)->idPaciente = (int *)malloc(capacidade * sizeof(int));
}

void enfilerarPaciente(FilaCircular **fila, int idPaciente){
	
	//verificando se a fila atingiu sua capacidade
	if((*fila)->tamanho == (*fila)->capacidade){
		printf("fila cheia, n�o � mais poss�vel adicionar novos elementos");
		return;
	}else{
		
		//incrementado valor do campo traseira da fila
		//se o novo �ndice do elemento a ser enfileirado for diferente da capacidade, o resto da divis�o (%) ser� o valor de traseira. ex: 3 % 5 = 0 e resto 3
		//caso contr�rio traseira retornar� a primeira posi��o. ex 5 % 5=0 e resto 0
		(*fila)->traseira = ((*fila)->traseira + 1) % (*fila)->capacidade;
	
		//adicionando valor no array da fila na posi��o indicada por traseira
		(*fila)->idPaciente[(*fila)->traseira] = idPaciente;
	
		//incrementando seu tamanho
		(*fila)->tamanho++;	
	}
}


void desfileirarPaciente(FilaCircular **fila){
	
	//verificando se fila est� vazia
	if((*fila)->tamanho==0){
		printf("fila vazia, n�o � poss�vel remover mais elementos");
		return;
	}else{
		//desfileirando elemento da frente de fila
		
		//incrementado valor do campo frente da fila
		//frente receber� �ndice incrementado ou 0 caso atinja a capacidade
		(*fila)->frente = ((*fila)->frente+1) % (*fila)->capacidade;
		
		//decrementado tamanho da fila
		(*fila)->tamanho--;
	}
}


void exibirFila(FilaCircular **fila) {
    if ((*fila)->tamanho == 0) {
        printf("A fila est� vazia.\n");
        return;
    }

    printf("Fila (tamanho: %d): ", (*fila)->tamanho);

    int index = (*fila)->frente; // Come�a no �ndice da frente
    for (int i = 0; i < (*fila)->tamanho; i++) {
        printf("%d ", (*fila)->idPaciente[index]); // Exibe id armazenado do paciente
        index = (index + 1) % (*fila)->capacidade; // atualiza valor do �ndice ou retorna ao 1� posi��o caso alcance a capacidade
    }

    printf("\n");
}

void liberarFila(FilaCircular **fila) {
    if (*fila) {
        free((*fila)->idPaciente);
        free(*fila);
    }
}
