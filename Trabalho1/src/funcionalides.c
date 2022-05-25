/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#include <funcionalidades.h>
#include <funcoesFornecidas.h>

/*
 * Funcionalidade 1 do trabalho.
 *
 * Cria o arquivo de dados armazenando o cabeçalho e todos os
 * os registros (de acordo com o tipo) do arquivo CSV.
 */
void createTable(char *nomeArquivo, char *tipoArquivo, char *nomeCSV) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *file = criarArquivoBinario(nomeArquivo);

    if (file == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    setRegistroCabecalho(file, tipoArquivo);

    preencherArquivoDados(file, tipoArquivo, nomeCSV);

    setStatusSeguro(file);

    fclose(file);
}

/*
 * Funcionalidade 2 do trabalho.
 *
 * Realiza a impressão de todos os registro os registros
 * armazenados em um determinado arquivo.
 */
void listarTodosRegistros(char *nomeArquivo, char *tipoArquivo) {
    if (strcmp(tipoArquivo, "tipo1") && strcmp(tipoArquivo, "tipo2")) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *f = abrirArquivoDados(nomeArquivo);
    
    if (f == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    int codigo = lerTodosRegistros(f, tipoArquivo);

    if (codigo == -1)
        printf("Registro inexistente.\n");
    else if (codigo == -2)
        printf("Falha no processamento do arquivo.\n");

    fclose(f);
}

/*
 * Funcionalidade 4 do trabalho.
 *
 * Realiza a impressão de um determinado registro fixo do arquivo
 * a partir de um dado RRN
 */
void getRegistroFixo(char *nomeArquivo, char *tipoArquivo, int RRN) {
    if (strcmp(tipoArquivo, "tipo1")) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    FILE *f = abrirArquivoDados(nomeArquivo);

    if (f == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    if (getStatus(f) == '0' || RRN < 0) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    
    if (RRN > getNumeroRegistros(f)) {
        printf("Registro inexistente.\n");
        return;
    }

    regFixo *r = lerRegistroFixo(f, RRN);

    if (r->removido == '0')
        imprimirRegistroFixo(r);
    else
        printf("Registro inexistente.\n");
        
    freeRegistroFixo(r);

    fclose(f);
}

/*
    Função captura os campos a serem pesquisados e os 
    retorna em um vetor de n structs to tipo campo. 

    Retorno:
        - ponteiro para o os campos

*/

campos* capturaCampos(int n){
    campos* n_campos = (campos*)malloc((n) * sizeof(campos));
    
   
    //capturando os n campos necessários 
    for(int i = 0; i < n; i++){
        n_campos[i].str1 = malloc(6 * sizeof(char));
        n_campos[i].str2 = malloc(6 * sizeof(char));
        scanf("%s", n_campos[i].str1);
        scan_quote_string(n_campos[i].str2);
    }    

    return n_campos;
}

void liberaCampos(campos* n_campos, int n){
    for(int i = 0; i < n; i++){
        free(n_campos[i].str1);
        free(n_campos[i].str2);
    }    
    free(n_campos);    
    return;
}



/*
  Retorno:
    -2: Falha ao ler arquivo
    -1: Arquivo vazio  
     0: Sucesso
*/
int listarCamposPesquisados(char* nomeArquivo, campos* n_campos, int numCampos, char* tipoArquivo){
    FILE *f = abrirArquivoDados(nomeArquivo);

    if (f == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return -2;
    }

    int retorno = 0;

    //Registros de tamanho fixo
    if(!strcmp("tipo1", tipoArquivo)){
        int total_rrn = getNumeroRegistros(f);
        if(total_rrn == 0)
            //printf("Registro inexistente\n");
            return -1;
            //printf("Vazio");
        for(int j = 0; j < total_rrn; j++){
            regFixo* r = lerRegistroFixo(f, j);
            if(verificaCamposFixos(r, n_campos, numCampos) == 0){
                imprimirRegistroFixo(r);
                retorno = 0;
            }else
                retorno = -1;
            
        }
    }
    else if(!(strcmp("tipo2", tipoArquivo))){
        int proxByteOffSet = getProxByteOffset(f);
        if(proxByteOffSet == 0) return -1;
       
        regVariavel* r = NULL;

        //Voltando para o início do arquivo
        fseek(f, 190, SEEK_SET);
        do{
            r = lerRegistroVariavel(f);
            if(verificaCamposVariaveis(r, n_campos, numCampos) == 0){
                imprimirRegistroVariavel(r); 
                retorno = 0;
            }else
                retorno = -1;
        }while(proxByteOffSet != ftell(f)); 
        freeRegistroVariavel(r);
                 
    }
    /* 
    if(retorno != 0) 
        printf("Registro inexistente\n");
    */
    return retorno;
}

