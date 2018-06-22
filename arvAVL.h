#pragma once

typedef struct REGISTRO Reg;
typedef struct NO* AAVL;

// básico
AAVL *cria_AVL();
int AVL_vazia(AAVL A);
int insere_AVL(AAVL *A, Reg elem);
int remove_AVL(AAVL *A, Reg elem);
int busca_bin_AVL(AAVL A, int identificador);
void exibe_AVL(AAVL A);
void exibe_AVL_ord(AAVL A);
void libera_AVL(AAVL A);

//trabalho
Reg *menor_trafego(AAVL A);
int qtde_ocioso(AAVL A);
int nro_nosDerivacao(AAVL A);
int cheia(AAVL A);
int nivel_no(AAVL A, Reg elem);
int iguais(AAVL A, AAVL B);