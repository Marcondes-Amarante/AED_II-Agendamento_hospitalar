# Introdução

Os algoritmos contidos no presente repositório referem-se a um projeto prático de fixação proposto pelo professor Carlos vinícius como componente avaliativo da disciplina de algoritmos e estruturas de dados II ministrada na turma 2024.1 do curso de ciência da computação da UFCA. 

O mesmo consiste em um sistema de geração de atendimentos hospitalares agrupados por dias e horários comerciais (das 8h as 11h, e das 13h as 16h) gerados mediante o tratamento e processamento de entradas previamente especificadas por um arquivo txt, contendo especificações gerais do hospital de referência, como quantidade de pacientes, salas, especialidades e médicos, e as informações gerais dos pacientes como id, idade, informações de contato (telefone) e de diagnóstico (altura, pesoa, sintomas e medicações atuais).

# Formato padrão do arquivo de entrada
O formato padrão para distribuição dos dados de especificação geral do hospital e seus pacientes foi definido da seguinte forma:

<ul>
    <li> 1° linha: informações gerais do hospital e suas respectivas especialidades:</li>
    <ul>
        <li>quantidade de pacientes,quantidade de salas,quantidde de médicos,quantidade de especialidades;nome da especialidade-quantidade de médicos desta especialidade:listegem de médicos da especialidade separada por vígula,</li>
    </ul>
    <li>2° linha em diante: dados dos pacientes e seus respectivos diagnósticos preliminares</li>
    <ul>
        <li>id,idade,peso,altura;especialidade;sintomas separados por vírgula;medicamentos usados separados por vírgula;</li>
    </ul>
</ul>

### Exemplo válido de entrada:

![exemplo_de_entrada](image.png)

# Esturutura e composição do projeto

- `FilaCircular.h:` biblioteca contendo struct e funções para gerenciamento de operações básicas de um fila circular tais como enfileiramento e desenfileiramento de elementos, e liberação de memória
- `HeapMinima.h:` biblioteca contendo struct's de definição para os tipos de elementos a serem armazenados na estrutura (pacientes, médicos, hospital...),  e funções para gerenciamento de operações básicas de um heap de prioridade mínima tais como inicialização, inserção e remoção de elementos
- `Main.c:` componente principal do código que contém instruções de obtenção dos dados extraídos do arquivo de entrada, tratamento e manipulação em memória das informações obtidas, e toda a lógica de geração do agendamentos e impressão dos dados em um arquivo txt

# Estruturas de dados e funções nativas utilizadas
- função fgets de <stdio.h>: para obteção individual das linhas do arquivo de entrada
- função strtok de <string.h>: para tokenização e obtenção das cadeias de string almejadas através da procura por delimitadores
- função strcpy de <string.h>: para cópia de strings obtidas pelo strtok para campos das struct's pré definidas
- função strcmp de <string.h>: para comparação de string's armazenadas em campos de struct's distintas
- funções de manipulação de memória como malloc e realloc de <stdlib.h>: para alocação e aumento de memória reservada as instâncias de struct's e vetores *char reservado ao armazenamento das linhas
- função fprintf de <stdio.h>: para impressão dos dados gerados no arquivo de saída txt
- função rand de <stdlib.h>: para geração de valores aleatórios para o campo prioridade das instâncias de pacientes
- heap de prioridade mínima: para armazenamento das instâncias de pacientes conforme seus valores de prioridade
- fila circular: para guardar os pacientes não atendidos em decorrência da indisponibilidade de médicos relativos a sua especialidade especificada


# Instruções de execução

### Instruções para Executar o Arquivo `main.c`

1. **Baixar o Repositório**  
   - Clique no botão verde **"Code"** na página principal do repositório.  
   - Selecione a opção **"Download ZIP"** e salve o arquivo em seu computador.  

2. **Extrair os Arquivos**  
   - Localize o arquivo ZIP baixado e extraia seu conteúdo para uma pasta de sua preferência.  

3. **Abrir o Arquivo `main.c`**  
   - Abra sua IDE de preferência (ex.: Dev-C++, Code::Blocks, ou outra compatível com C).  
   - Na IDE, navegue até a pasta onde você extraiu os arquivos e abra o arquivo `main.c`.  

4. **Compilar e Executar o Programa**  
   - Certifique-se de que o compilador C está configurado corretamente na sua IDE.  
   - Clique no botão **"Compile and Run"** (ou equivalente na sua IDE).  
   - Aguarde a compilação. Após sua conclusão um arquivo nomeado "saida_de_agendamentos.txt" será gerado contendo todas a listagem de agendamentos esperada.


# Saída esperada
Arquivo "saida_de_agendamentos.txt" contendo a relação de agendamentos gerados dispostos por dia e horários, onde cada linha abaixo do respectivo horário, contém sequencialmente o id da sala, id do paciente, sua respectiva prioridade, o médico disponível correspondente a especialidade requisitada pelo paciente e a respectiva especialidade do paciente. Além é claro da quantidade de dias necessários para atender todos os pacientes e a quantidade de horas trabalhadas por todos os médicos, ao final do arquivo.


