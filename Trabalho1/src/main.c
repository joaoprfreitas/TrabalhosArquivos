/*
 * SSC0215 - 2022 - Organização de arquivos
 * Trabalho 1
 * Nome: João Pedro Rodrigues Freitas, N USP: 11316552
 * Nome: Guilherme Pacheco de Oliveira Souza, N USP: 11797091
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <funcionalidades.h>
#include <funcoesFornecidas.h>

typedef struct cab {
    char status; // '0' para inconsistente, '1' para consistente
    long long int topo; // armazena o byte offset do registro que está no topo da pilha
    char descricao[40 + 1];
    char desC1[22 + 1];
    char desC2[19 + 1];
    char desC3[24 + 1];
    char desC4[8 + 1];
    char codC5;
    char desC5[16 + 1]; 
    char codC6;
    char desC6[18 + 1];
    char codC7;
    char desC7[19 + 1]; 
    long long int proxByteOffset;
    int nroRegRem;
} cabecalho;

typedef struct reg {
    char removido;
    int tamanhoRegistro;
    long long int prox;
    int id;
    int ano;
    int qtt;
    char sigla[TAM_SIGLA + 1];
    int tamCidade;
    char codC5;
    char *cidade;
    int tamMarca;
    char codC6;
    char *marca;
    int tamModelo;
    char codC7;
    char *modelo;
} regvar;

regvar printRegistro(FILE *f) {
    regvar r;
    fread(&r.removido, sizeof(char), 1, f);
    fread(&r.tamanhoRegistro, sizeof(int), 1, f);
    fread(&r.prox, sizeof(long long int), 1, f);
    fread(&r.id, sizeof(int), 1, f);
    fread(&r.ano, sizeof(int), 1, f);
    fread(&r.qtt, sizeof(int), 1, f);
    fread(&r.sigla, sizeof(char), TAM_SIGLA, f);
    int tamAtual = 22;

    r.tamCidade = -1;
    r.tamMarca = -1;
    r.tamModelo = -1;

    int auxtam;
    char auxCod;
    while (r.tamanhoRegistro > tamAtual) {
        fread(&auxtam, sizeof(int), 1, f);
        fread(&auxCod, sizeof(char), 1, f);

        tamAtual += 1 + 4 + auxtam;

        if (auxCod == '0') {
            r.tamCidade = auxtam;
            r.codC5 = auxCod;
            r.cidade = (char *) malloc(sizeof(char) * (r.tamCidade + 1));
            fread(r.cidade, sizeof(char), r.tamCidade, f);
            r.cidade[r.tamCidade] = '\0';

        } else if (auxCod == '1') {
            r.tamMarca = auxtam;
            r.codC6 = auxCod;
            r.marca = (char *) malloc(sizeof(char) * (r.tamMarca + 1));
            fread(r.marca, sizeof(char), r.tamMarca, f);
            r.marca[r.tamMarca] = '\0';
        } else if (auxCod == '2') {
            r.tamModelo = auxtam;
            r.codC7 = auxCod;
            r.modelo = (char *) malloc(sizeof(char) * (r.tamModelo + 1));
            fread(r.modelo, sizeof(char), r.tamModelo, f);
            r.modelo[r.tamModelo] = '\0';
        }
    }

    printf("%c\n", r.removido);
    printf("%d\n", r.tamanhoRegistro);
    printf("%lld\n", r.prox);
    printf("%d\n", r.id);
    printf("%d\n", r.ano);
    printf("%d\n", r.qtt);
    printf("%s\n", r.sigla);
    if (r.tamCidade != -1) {
        printf("%d\n", r.tamCidade);
        printf("%c\n", r.codC5);
        printf("%s\n", r.cidade);
    }
    if (r.tamMarca != -1) {
        printf("%d\n", r.tamMarca);
        printf("%c\n", r.codC6);
        printf("%s\n", r.marca);
    }
    if (r.tamModelo != -1) {
        printf("%d\n", r.tamModelo);
        printf("%c\n", r.codC7);
        printf("%s\n", r.modelo);
    }

}

void teste() {
    FILE *f = fopen("binario2.bin", "rb");
    fseek(f, 190, SEEK_SET);

    // cabecalho cab;
    // fread(&cab.status, sizeof(char), 1, f);
    // fread(&cab.topo, sizeof(long long int), 1, f);
    // fread(&cab.descricao, sizeof(char), 40, f);
    // cab.descricao[40] = '\0';
    // fread(&cab.desC1, sizeof(char), 22, f);
    // cab.desC1[22] = '\0';
    // fread(&cab.desC2, sizeof(char), 19, f);
    // cab.desC2[19] = '\0';
    // fread(&cab.desC3, sizeof(char), 24, f);
    // cab.desC3[24] = '\0';
    // fread(&cab.desC4, sizeof(char), 8, f);
    // cab.desC4[8] = '\0';
    // fread(&cab.codC5, sizeof(char), 1, f);
    // fread(&cab.desC5, sizeof(char), 16, f);
    // cab.desC5[16] = '\0';
    // fread(&cab.codC6, sizeof(char), 1, f);
    // fread(&cab.desC6, sizeof(char), 18, f);
    // cab.desC6[18] = '\0';
    // fread(&cab.codC7, sizeof(char), 1, f);
    // fread(&cab.desC7, sizeof(char), 19, f);
    // cab.desC7[19] = '\0';
    // fread(&cab.proxByteOffset, sizeof(long long int), 1, f);
    // fread(&cab.nroRegRem, sizeof(int), 1, f);

    // printf("%c\n", cab.status);
    // printf("%lld\n", cab.topo);
    // printf("%s\n", cab.descricao);
    // printf("%s\n", cab.desC1);
    // printf("%s\n", cab.desC2);
    // printf("%s\n", cab.desC3);
    // printf("%s\n", cab.desC4);
    // printf("%c\n", cab.codC5);
    // printf("%s\n", cab.desC5);
    // printf("%c\n", cab.codC6);
    // printf("%s\n", cab.desC6);
    // printf("%c\n", cab.codC7);
    // printf("%s\n", cab.desC7);
    // printf("%lld\n", cab.proxByteOffset);
    // printf("%d\n", cab.nroRegRem);

    printRegistro(f);
    printf("-------------\n");
    printRegistro(f);


    fclose(f);
}

int main() {
    int funcionalidade;
    char tipoArquivo[20];
    char nomeCSV[100];
    char nomeBin[100];

    scanf("%d ", &funcionalidade);
    scanf("%s ", tipoArquivo);

    switch (funcionalidade) {
        case 1:
            scanf("%s ", nomeCSV);
            scanf("%s\r\n", nomeBin);

            createTable(nomeBin, tipoArquivo, nomeCSV);

            binarioNaTela(nomeBin);
            break;
        case 2:
            scanf("%s\r\n", nomeBin);

            listarTodosRegistros(nomeBin, tipoArquivo);
            
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;
    
        default:
            break;
    }

    

    return EXIT_SUCCESS;
}