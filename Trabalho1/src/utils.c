/*
 * SSC0215 - 2022 - Organização de arquivos
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#include <utils.h>

#define CSV_DELIMITER ","
#define CSV_COLS 7
#define BUFFER_SIZE 32

/* Faz a leitura de uma sequência de caracteres até achar o caracter de parada ou '\n' ou EOF.
 * Durante a leitura, suprime o '\r' caso houver.
 * Aloca em blocos de tamanho BUFFER_SIZE.
 * Caso encontre o EOF, altera 'fimArquivo' para true
 * Adiciona o '\0' no final da string criada.
 * Retorna a string.
 */
char *lerString(FILE *f, char parada, bool *fimArquivo) {
    char *linha = NULL, tmp;
    int cont = 0;

    do {
        tmp = getc(f);
        if (tmp == '\r') tmp = getc(f);

        if (cont % BUFFER_SIZE == 0) // Aloca em blocos de tamanho BUFFER_SIZE
            linha = realloc(linha, sizeof(char) * (cont + BUFFER_SIZE));

        if (tmp == parada) break;
        
        if (tmp == EOF) *fimArquivo = true;

        if ((tmp != '\n') && (tmp != EOF))
            linha[cont++] = tmp;

    } while ((tmp != '\n') && (tmp != EOF));

    linha[cont] = '\0';

    return linha;
}

/*
 * Faz a leitura de uma linha do arquivo CSV.
 * A partir da linha do CSV, realiza um split utilizando o delimitador CSV_DELIMITER.
 * Transforma os campos id, ano, qtt em inteiros.
 * Altera o parametro 'data' com os dados lidos, fazendo as seguintes verificações:
 *  - Para os campos ano e qtt, verifica se o valor existe, setando como -1 caso não exista.
 *  - Para o campo sigla, seta como lixo ('$$') caso esteja vazio.
 *  - Para os demais campos, faz um cópia dinâmica (strdup)
 * 
 * Retorna true se a leitura foi bem sucedida ou false caso tenha chegado ao fim do arquivo.
 */
bool readLineCSV(FILE *csv, data_t *data) {
    bool fimArquivo = false;
    char *token, *buffer;

    char *linha = lerString(csv, CSV_ENDLINE, &fimArquivo);
    buffer = linha; // Faz uma cópia para não perder a referência durante o strsep

    if (fimArquivo) {
        free(linha);
        return false;
    }

    int i = 0;

    /* strsep é para extrair os tokens de uma string separada por delimitadores
     * mesmo que algum field esteja vazio, o delimitador será considerado
     */
    while ((token = strsep(&buffer, CSV_DELIMITER)) != NULL) { // Enquanto houver tokens
        switch (i) {
            case 0:
                data->id = atoi(token);
                break;

            case 1:
                if (!(strcmp(token, "")))
                    data->ano = -1;
                else
                    data->ano = atoi(token);

                break;

            case 2:
                data->cidade = strdup(token); // Cria dinamicamente uma cópia da string
                break;

            case 3:
                if (!(strcmp(token, "")))
                    data->qtt = -1;
                else
                    data->qtt = atoi(token);

                break;

            case 4:
                if (!(strcmp(token, ""))) { // Altera para lixo caso esteja vazio
                    data->sigla[0] = '$';
                    data->sigla[1] = '$';
                } else    
                    strcpy(data->sigla, token);
                    
                break;

            case 5:
                data->marca = strdup(token);
                break;

            case 6:
                data->modelo = strdup(token);
                break;
        }
        i++;
    }

    free(linha);

    return true;
}

/*
 *  Faz a leitura dos campos a serem pesquisados.
 *  Retorna o vetor de campos a serem pesquisados. 
*/
campos* capturaCampos(int n){
    campos* n_campos = malloc(n * sizeof(campos));
    
    // Faz a leitura dos n campos
    for (int i = 0; i < n; i++) {
        scanf("%s ", n_campos[i].str1);
        scan_quote_string(n_campos[i].str2);
    }    

    return n_campos;
}

/*
 * Realiza uma busca binária na lista de indices
 * em busca da posição de um determinado id.
 */
int buscaBinariaIndex(int id, index_t *index) {
    int inicio = 0, meio;
    int fim = index->tamanho;
    
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (id == index->lista[meio].id)
            return meio;
        else if (id < index->lista[meio].id)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    
    return -1;
}

/*
 * Insertion sort decrescente
 * Melhor caso: ordenado em ordem decrescente O(n)
 */
void insertionSort(topo_t *listaTopo) {
    for (int j = 1; j < listaTopo->tamanhoLista; j++) {
        campoTopo_t chave = listaTopo->lista[j];
        int i = j - 1;
        while (chave.tamanho > listaTopo->lista[i].tamanho && i >= 0) {
            listaTopo->lista[i + 1] = listaTopo->lista[i];
            i--;
        }
        listaTopo->lista[i + 1] = chave;
    }
}

/*
 * 
 */
int getPosListaTopo(topo_t lista, int tamanhoRegistro) {
    for (int i = 0; i < lista.tamanhoLista; i++) {
        if (lista.lista[i].tamanho <= tamanhoRegistro) {
            return i; // insere na posição i
        }
    }
    return -1; // insere no final
}

/*
 * Realiza a inserção de um novo elemento na lista de topo.
 * Após a inserção, realiza uma ordenação decrescente da lista
 * por meio de um insertionSort (neste caso, O(n))
 */
void inserirListaTopo(topo_t *lista, int pos, int tamanhoRegistro) {
    lista->lista = realloc(lista->lista, (lista->tamanhoLista + 1) * sizeof(campoTopo_t));

    lista->lista[lista->tamanhoLista].topo = pos;
    lista->lista[lista->tamanhoLista].tamanho = tamanhoRegistro;
    lista->tamanhoLista++;

    insertionSort(lista);
}

/*
 * Faz a leitura de uma linha de dados da entrada padrão.
 * Com as informações lidas, preenche a estrutura data_t.
 * Retorna essa estrutura.
 */
data_t lerLinhaDadosInserir() {
    char campo[100];
    data_t data;

    for (int i = 0; i < 7; i++) {
        scan_quote_string(campo);

        switch (i) {
        case 0:
            if (strcmp(campo, "")) { // Se não for nulo
                data.id = atoi(campo);
            } else {
                data.id = -1;
            }
            break;

        case 1:
            if (strcmp(campo, "")) { // Se não for nulo
                data.ano = atoi(campo);
            } else {
                data.ano = -1;
            }
            break;
        
        case 2:
            if (strcmp(campo, "")) { // Se não for nulo
                data.qtt = atoi(campo);
            } else {
                data.qtt = -1;
            }
            break;
        
        case 3:
            if (strcmp(campo, "")) { // Se não for nulo
                data.sigla[0] = campo[0];
                data.sigla[1] = campo[1];
            } else {
                data.sigla[0] = '$';
                data.sigla[1] = '$';
            }
            break;

        case 4:
            data.cidade = strdup(campo); // Faz uma cópia dinâmica da string
            break;

        case 5:
            data.marca = strdup(campo); // Faz uma cópia dinâmica da string
            break;

        case 6:
            data.modelo = strdup(campo); // Faz uma cópia dinâmica da string
            break;
        
        default:
            break;
        }
    }

    return data;
}

/*
 * Realiza uma ordenação decrescente na lista de indices
 * por meio de um quickSort
 */
void quickSortIndex(index_t *index, int ini, int fim) {
    // Caso base: vetor de tamanho 0 ou 1
    if (ini >= fim) return;

    // Partição ao redor do pivo
        // Seleciona o pivo [... l1 ...] <= p < [... l2 ...]
        // percorre o inicio do vetor para garantivo <= pivo
        // percorre o fim do vetor para garantir > pivo
    int p = ini;

    // troca pivo com a 1.a pos
    campoIndex_t tmp = index->lista[p];
    index->lista[p] = index->lista[ini];
    index->lista[ini] = tmp;

    p = ini;
    int i = ini + 1; // percorre l1 <= p ++
    int j = fim; // percorre l2 > p --

    while (i <= j) {
        while (i <= fim && index->lista[i].id <= index->lista[p].id) i++;
        while (index->lista[j].id > index->lista[p].id) j--;
        // i e j são candidatos a troca
        if (j > i) {
            tmp = index->lista[i];
            index->lista[i] = index->lista[j];
            index->lista[j] = tmp;
        }
    }
    // posicionar o pivo na sua posição ja ordenada
    // a posição do pivo será a j
    tmp = index->lista[p];
    index->lista[p] = index->lista[j];
    index->lista[j] = tmp;
    p = j;

    // Chamadas recursivas
    quickSortIndex(index, ini, p - 1);
    quickSortIndex(index, p + 1, fim);
}