#include <stdio.h>
#include <stdlib.h>
#include "arvAVL.h"

struct REGISTRO {
    int identificador,
        localizacao,
        capacidade,
        trafego;
};

struct NO {
    Reg info;
    int altura;
    struct no *sae,
              *sad;
};

int altura_no (struct NO* no) {
    if (no == NULL)
        return -1;
    else
        return no->altura;
}

int fator_balanceamento (struct NO* no) {
    return labs(altura_no(no->sae) - altura_no(no->sad));
}

int maior (int x, int y) {
    if (x > y)
        return x;
    else
        return y;
}

void RotacaoLL(AAVL *raiz) {
    struct NO* no;
    no = (*raiz)->sae;
    no->sad = *raiz;
    (*raiz)->altura = maior(altura_no((*raiz)->sae),
                            altura_no((*raiz)->sae)) + 1;
    no->altura = maior(altura_no(no->sae),
                       ((*raiz)->altura + 1));
    *raiz = no;
}

void RotacaoRR(AAVL *raiz) {
    struct NO* no;
    no = (*raiz)->sad;
    (*raiz)->sad = no->sae;
    no->sae = (*raiz);
    (*raiz)->altura = maior(altura_no((*raiz)->sae),
                            altura_no((*raiz)->sad)) +1;
    no->altura = maior(altura_no(no->sad),
                       ((*raiz)->altura) + 1);
    (*raiz) = no;
}

void RotacaoLR (AAVL *raiz) {
    RotacaoRR(&(*raiz)->sae);
    RotacaoLL(raiz);
}

void RotacaoRL (AAVL *raiz) {
    RotacaoLL(&(*raiz)->sad);
    RotacaoRR(raiz);
}

int insere_AVL (AAVL *raiz, Reg elem) {
    int res;
    if(*raiz == NULL) {
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if (novo == NULL)
            return 0;
        novo->info = elem;
        novo->altura = 0;
        novo->sae = NULL;
        novo->sad = NULL;
        *raiz = novo;

        return 1;
    }
    struct NO *atual = *raiz;
    if (elem.identificador < atual->info.identificador) {
        if ((res = insere_AVL(&(atual->sae), elem)) == 1) {
            if(fator_balanceamento(atual) >= 2) {
                if(elem.identificador < (*raiz)->sae->info.identificador) {
                    RotacaoLL(raiz);
                } else {
                    RotacaoLR(raiz);
                }
            }    
        }
    } else {
        if (elem.identificador > atual->info.identificador) {
            if ((res = insere_AVL(&(atual->sad), elem)) == 1) {
                if (fator_balanceamento(atual) >= 2) {
                    if ((*raiz)->sad->info.identificador < elem.identificador) {
                        RotacaoRR(raiz);
                    } else {
                        RotacaoRL(raiz);
                    }
                }
            }
        } else {
            printf("Valor duplicado!\n");
            return 0;
        }
    }
    atual->altura = maior(altura_no(atual->sae),
                          (altura_no(atual->sad)) + 1);
    return res;
}

int remove_AVL(AAVL *raiz, Reg elem) {
    if (*raiz == NULL) {
        printf("O Valor não existe\n");
        return 0;
    }
    int res;
    if (elem.identificador < (*raiz)->info.identificador) {
        if ((res = remove_AVL(&(*raiz)->sae, elem)) == 1) {
            if (fator_balanceamento(*raiz) >= 2) {
                if (altura_no((*raiz)->sad->sae) <= altura_no((*raiz)->sad->sad))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
        }
    }
    if ((*raiz)->info.identificador < elem.identificador) {
        if ((res = remove_AVL(&(*raiz)->sad, elem)) == 1) {
            if (fator_balanceamento(*raiz) >= 2) {
                if (altura_no((*raiz)->sae->sad) <= altura_no((*raiz)->sae->sae))
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
    }
    if ((*raiz)->info.identificador == elem.identificador) {
        if (((*raiz)->sae == NULL || (*raiz)->sad == NULL)) {
            struct NO *velho = (*raiz);
            if((*raiz)->sae != NULL)
                *raiz = (*raiz)->sae;
            else 
                *raiz = (*raiz)->sad;
            free(velho);
        } else {
            struct NO *temp = procuraMenor((*raiz)->sad);
            (*raiz)->info = temp->info;
            remove_AVL(&(*raiz)->sad, (*raiz)->info);
            if (fator_balanceamento(*raiz) >= 2) {
                if (altura_no((*raiz)->sae->sad) <= altura_no((*raiz)->sae->sae))
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
        return 1;
    }
    return res;
}

struct NO *procuraMenor(struct NO *atual) {
    struct NO *no1 = atual;
    struct NO *no2 = atual->sae;
    while (no2 != NULL) {
        no1 = no2;
        no2 = no2->sae;
    }
    return no1;
}