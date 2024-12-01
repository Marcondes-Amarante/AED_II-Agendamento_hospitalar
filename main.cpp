#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

#include "HeapMinima.h"
#include "FilaCircular.h"

char* obterLinhaDinamicamente(FILE *arquivo){
    
	if(arquivo == NULL){
    	printf("Arquivo inexistente ou caminho incorreto\n");
        exit(0);
    }
    
     // Inicializando variável para armazenamento das linhas do arquivo
    int tam = 50;
    char *linha = (char *)malloc(tam * sizeof(char));

    if(linha == NULL){
        printf("Memória indisponível para alocação de linha\n");
		exit(0);
    }

    //variável de controle para a posição lida referente a linha
    int posLinha = 0;
    
    while(fgets(linha + posLinha, tam - posLinha, arquivo)){
        
        // Verificando se o final da linha foi alcançado
        if(strchr(linha, '\n') != NULL) {
            break;
        }

        // Verificando se o espaço foi esgotado e realocando memória
        if(tam - posLinha == 1){
            tam *= 2;
            //verificar se posição de memória retornada por realloc é igual a posição de memória apontada anteriormente por linha
            linha = (char *)realloc(linha, tam * sizeof(char));

            if(linha == NULL){
                printf("Erro ao realocar memória\n");
                exit(0);
            }
        }

        // Atualizando posição da linha lida
        posLinha = strlen(linha);
    }

    //retornando conteudo da linha lida
    return linha;
}


void reinserirPacientesNaoAtendidos(FilaCircular **fila, HeapMin *heap, Paciente *pacientes) {
    
    //guarda atual tamanho da fila
	int tamanhoAtual = (*fila)->tamanho;

    for (int i = 0; i < tamanhoAtual; i++) {
        int idPaciente = (*fila)->idPaciente[(*fila)->frente]; // Acessa o paciente no início da fila
        inserirElemHeap(heap, &pacientes[idPaciente - 1]); // Reinsere o paciente na heap
        desfileirarPaciente(fila); // Remove o paciente processado da fila
        printf("Reinserindo paciente com ID: %d na heap\n", idPaciente);
    }
}


int main(){
	
	setlocale(LC_ALL, "portuguese");
	setlocale(LC_NUMERIC, "C");
	
	//INICIO - instruções de leitura e obtenção de dados do arquivo de entrada
	//inicializando arquivo de leitura
	FILE *arquivo;
	arquivo = fopen("exemplo_de_entrada.txt", "r");
	
	//inicializando ponteiro para armazenamento da linha retornada
	char* linha;
	
	//incializando instâncias de hospital
	Hospital hospital;
	
	//inicializando vetor de instâncias de especialidade
	int qtdEspec=1;
	Especialidade *especialidades = (Especialidade *)malloc(qtdEspec * sizeof(Especialidade));
	
	//incializando vetor de instâncias de médicos
	int qtdMedicos=1;
	Medico *medicos = (Medico *)malloc(qtdMedicos * sizeof(Medico));
	
	//incializando vetor de instâncias de pacientes
	int qtdPacientes=1;
	Paciente *pacientes = (Paciente *)malloc(qtdPacientes * sizeof(Paciente));
	
	//inicializando 1° linha para garantir execução correta do fluxo while
	linha=obterLinhaDinamicamente(arquivo);
	
	//incializando ponteiro de string para armazenamento dos dados de hospital e pacientes
	char *infoGeral;
	char *infoPacientes;
	
	//variável de controle para as posições de linha do arquivo
	int indiceLinha=1;
	
	//variáveis de controle para controlar atribuição sequencial dos médicos e pacientes
	int posMedico=0;
	int posPaciente=0;
	
	//gerando seed para garantir aleatoriedade dos valores de prioridade posteriormente gerados para os pacientes
	srand(time(NULL));
	
	while(linha!=NULL){
   		
   		printf("%s \n", linha);
   		
		if(indiceLinha==1){
			//obtendo quantidade de pacientes
			infoGeral = strtok(linha, ",");
			hospital.qtdPacientes = atoi(infoGeral);
			
			//obtendo quantidade de salas
			infoGeral = strtok(NULL, ",");
			hospital.qtdSalas = atoi(infoGeral);
			
			//obtendo quantidade de médicos
			infoGeral = strtok(NULL, ",");
			hospital.qtdMedicos = atoi(infoGeral);
			
			if(hospital.qtdSalas>hospital.qtdMedicos){
				printf("quantidade de salas inferior a de médicos");
				exit(0);
			}
			
			//obtendo quantidade de especialidades
			infoGeral = strtok(NULL, ";");
			hospital.qtdEspec = atoi(infoGeral);
			
			//inicializando vetor de pacientes que irá armazenar instâncias de paciente com base em hospital.qtdPacientes
			pacientes = (Paciente *)realloc(pacientes, hospital.qtdPacientes * sizeof(Paciente));
			
			//alocando dinamicamente memória para o campo(ponteiro) medicos e especialidades da instância de hospital
			hospital.medicos = (Medico *)malloc(hospital.qtdMedicos * sizeof(Medico));
			hospital.especialidades = (Especialidade *)malloc(hospital.qtdEspec * sizeof(Medico));			
			
			//realocando memória do vetor de especialidades para se adequar a quantidade de especialidades especificada para hopsital
			qtdEspec = hospital.qtdEspec;
			especialidades = (Especialidade *)realloc(especialidades, qtdEspec * sizeof(Especialidade));
			
			//relocando memória do vetor de medicos para se adequar a quantidade de médicos especificada para o hospital
			qtdMedicos = hospital.qtdMedicos;
			medicos = (Medico *)realloc(medicos, qtdMedicos * sizeof(Medico));
			
			//variável de controle para o índice de médico para garantir a correta e sequencial atribuição no vetor
			int posMedico=0;
			
			//obtendo dados de especialidades
			infoGeral = strtok(NULL, "-");
			
			for(int i=0; i<hospital.qtdEspec; i++){
				
				//atribuindo nome da especialidade
				strcpy(especialidades[i].nome, infoGeral);
				
				//obtendo quantidade de médicos da especialidade
				infoGeral = strtok(NULL, ":");
				especialidades[i].qtdMedicos = atoi(infoGeral);
				
				//atribuindo especialidade gerada para a instância de hospital
				hospital.especialidades[i] = especialidades[i];
				
				//alocando dinamicamente memória para o campo(ponteiro) medicos de especialidade
				especialidades[i].medicos = (Medico *)malloc(especialidades[i].qtdMedicos * sizeof(Medico));
				
				
				//obtendo médicos
				for(int j=0; j<especialidades[i].qtdMedicos; j++){
					
					//obtendo nome do médico
					infoGeral = strtok(NULL, ",");
					strcpy(medicos[posMedico].nome, infoGeral);
					
					//atribuindo sua especialidade
					strcpy(medicos[posMedico].especialidade, especialidades[i].nome);
					
					//atribuindo booleano do campo atendimento agendado para falso
					medicos[posMedico].atendimentoAgendado = 0;
					
					//atribuindo como zero o campo de horas trabalhadas de médico
					medicos[posMedico].qtdHorasTrabalhadas = 0;
					
					//atribuindo médicos gerado para o respecitvo campo medico da especialidade em que está vinculado
					especialidades[i].medicos[j]= medicos[posMedico];
					
					//atribuindo médico gerado para a instância de hospital
					hospital.medicos[posMedico] = medicos[posMedico];
					
					posMedico++;
				}
				
				//obtendo nome da especialidade
				infoGeral = strtok(NULL, "-");
			}	
		}
		
		if(indiceLinha>1){
			
			//obtendo id
			infoPacientes = strtok(linha, ",");
			pacientes[indiceLinha-2].id = atoi(infoPacientes);
			
			//obtendo idade
			infoPacientes = strtok(NULL, ",");
			pacientes[indiceLinha-2].idade = atoi(infoPacientes);
			
			//obtendo telefone
			infoPacientes = strtok(NULL, ",");
			strcpy(pacientes[indiceLinha-2].telefone, infoPacientes);
			
			//obtendo peso
			infoPacientes = strtok(NULL, ",");
			pacientes[indiceLinha-2].diagnostico_preliminar.peso = atof(infoPacientes);
			
			//obtendo altura
			infoPacientes = strtok(NULL, ";");
			pacientes[indiceLinha-2].diagnostico_preliminar.altura = atof(infoPacientes);
			
			//obtendo especialidade indicada para o paciente
			infoPacientes = strtok(NULL, ";");
			strcpy(pacientes[indiceLinha-2].especialidade, infoPacientes);
			
			//obtendo sintomas
			infoPacientes = strtok(NULL, ";");
			strcpy(pacientes[indiceLinha-2].diagnostico_preliminar.sintomas, infoPacientes);
			
			//obtendo medicações
			infoPacientes = strtok(NULL, ";");
			strcpy(pacientes[indiceLinha-2].diagnostico_preliminar.medicacoes, infoPacientes);
			
			//gerando valor de prioridade
			pacientes[indiceLinha-2].prioridade = rand()% hospital.qtdPacientes;
			
			//definindo número de atendimento igual a zero
			pacientes[indiceLinha-2].qtdVezesAtendido = 0;
			
			//setando quantidade de vezes atendido para 0
			pacientes[indiceLinha-2].qtdVezesAtendido = 0;

		}
		
		//verificanco término do arquivo
   		if(feof(arquivo)){
   			fclose(arquivo);
   			break;	
		}
		
		free(linha);	
		
		linha=obterLinhaDinamicamente(arquivo);
		indiceLinha++;
	}
	//FIM - instruções de leitura e obtenção de dados do arquivo de entrada
	
	
	//INÍCIO - instruções de preparação e preenchimento da heap
	//criando vetor de instâncias de sala de acordo com a quantidade de salas especificadas no arquivo para o hospital
	Sala *salas = (Sala *)malloc(hospital.qtdSalas * sizeof(Sala));
	printf("vetor de salas criado com sucesso\n");
	
	//criando instância de estrutura heap
	HeapMin heapPacientes;
	
	//inicializando heap com alocação de memória equivalente a quantidade de pacientes especificada para o hospital
	inicializarHeap(&heapPacientes, hospital.qtdPacientes);
	printf("heap criada com sucesso!\n");
	
	//covertendo vetor de pacientes para heap
	for(int i=0; i<hospital.qtdPacientes; i++){
		inserirElemHeap(&heapPacientes, &pacientes[i]);
	}
	
	printf("vetor de pacientes convertido para heap com sucesso\n");
	
	//vetor de horários comerciais disponíveis
	int vetHorarios[8] = {8,9,10,11,13,14,15,16};
	
	//preenchendo os 8 horários de cada sala
	for(int i=0; i<8; i++){
		for(int j=0; j<hospital.qtdSalas; j++){
			salas[j].atendimentos[i].hora = vetHorarios[i];
		}
	}
	//FIM - instruções de preparação e preenchimento da heap
	
	
	//INÍCIO - instruções de geração do arquivo de saída
	//Inicializando arquivo de saída
    FILE *arquivoSaida = fopen("saida_de_agendamentos.txt", "w");
    if (arquivoSaida == NULL) {
        printf("Erro ao criar ou acessar arquivo\n");
    }
    
    //inicializando fila para armazenamento de pacientes não atendidos devido falta de médico
    FilaCircular *filaPacientesNaoAtendidos;
	inicializarFila(&filaPacientesNaoAtendidos, hospital.qtdPacientes);
	
	//variável de controle para os dias
	int qtdDias = 0;
	
	while(heapPacientes.tam>0){
		qtdDias++;
		
		fprintf(arquivoSaida, "dia %d\n\n", qtdDias);
		
		//iterando por todos os horários disponíveis
		for(int i=0; i<8; i++){
			
			exibirFila(&filaPacientesNaoAtendidos);
			fprintf(arquivoSaida, "%d horas\n", vetHorarios[i]);
			
			//resetando flag de sinalização de ocupação com atendimento de todos os médicos para o horário atual
			for(int a=0; a<hospital.qtdEspec; a++){
				for(int b=0; b<especialidades[a].qtdMedicos; b++){
					especialidades[a].medicos[b].atendimentoAgendado=0;
				}
			}
			
			//iterando por todas as instâncias das salas de hospital
			for(int j=0; j<hospital.qtdSalas; j++){
				
				Paciente pacienteAtual = heapPacientes.dados[0];
				
				//variável de controle para verificar se houve agendamento para a sala atual
				int agendado=0;
				
				//iterando por todas as especialidades em busca de uma correspondente a devida especialidade do paciente atual
				for(int k=0; k<hospital.qtdEspec; k++){
					if(strcmp(pacienteAtual.especialidade, especialidades[k].nome)==0){
						
						//iterando por todos os médicos da especialidade encontrada a fim de encontrar um disponível
						for(int l=0; l<especialidades[k].qtdMedicos; l++){
							Medico EspecMedico = especialidades[k].medicos[l];
							
							if(EspecMedico.atendimentoAgendado==0){
								fprintf(arquivoSaida, "sala %d - id do paciente: %d, prioridade: %d, medico: %s, especialidade: %s\n", j, pacienteAtual.id,
								pacienteAtual.prioridade, EspecMedico, especialidades[k].nome);
								
								//setando médico como ocupado
								EspecMedico.atendimentoAgendado=1;
								
								//atualizando quantidade de horas trabalhadas pelo médico
								EspecMedico.qtdHorasTrabalhadas++;
								
								especialidades[k].medicos[l]=EspecMedico;

								
								//atualizando qtd de vezes atendido de paciente
								pacienteAtual.qtdVezesAtendido = 1;
								heapPacientes.dados[0]=pacienteAtual;
								
								agendado=1;
									
								break;
							}
							
						}
						
					}
					
				}
				
				//verificando se não houve concretização do agendamento, para esse caso o paciente é inserido na fila de não atendidos
				//por indisponibilidade de médico correspondente a sua especialidade
				if(heapPacientes.dados[0].qtdVezesAtendido==0){
					enfilerarPaciente(&filaPacientesNaoAtendidos, pacienteAtual.id);
				}
				
				removerElemHeap(&heapPacientes);
				
				//verifcando se a heap se encontra vazia e interropendo laço caso afirmativo
				if(heapPacientes.tam == 0){
					break;
				}
				
				
			}
			
			
			//reinserindo pacientes não atendidos na heap para nova tentativa de agendamento relativa ao próximo horário
			reinserirPacientesNaoAtendidos(&filaPacientesNaoAtendidos, &heapPacientes, pacientes);
			fprintf(arquivoSaida, "\n");

		}
		
		if(heapPacientes.tam == 0){
			break;
		}
		
	}
	
	
	//imprimindo quantidade de dias necessários para atender todos os pacientes
	fprintf(arquivoSaida, "\nqtd dias necessários para atender todos os pacientes: %d\n", qtdDias);
	
	//imprimindo quantidade de horas trabalhadas por cada médico
	fprintf(arquivoSaida, "\nrelatório de horas trabalhadas:\n\n");
	for(int i=0; i<hospital.qtdEspec; i++){
		for(int j=0; j<especialidades[i].qtdMedicos; j++){
			fprintf(arquivoSaida, "%s: %d horas\n", especialidades[i].medicos[j].nome, especialidades[i].medicos[j].qtdHorasTrabalhadas);
		}
	}
	//FIM - instruções de geração do arquivo de saída
	
	liberarFila(&filaPacientesNaoAtendidos);
	fclose(arquivoSaida);
	
	return 0;
}
