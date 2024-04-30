#define FUNCIONS_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_USERS 10
#define MAX_STR 20

typedef struct {
    int id;
    char nom[MAX_STR];
    char poblacio[MAX_STR];
    char sexe[MAX_STR];
    char sexe1;
    char data_naixement[MAX_STR];
} Usuari;

Usuari usuaris[MAX_USERS];

struct Usuari * usuari =&usuaris[id];

int llegir_usuaris(Usuari usuaris[], int *num_usuaris);
int llegir_distancies(int distancies[][MAX_USERS], int num_usuaris);