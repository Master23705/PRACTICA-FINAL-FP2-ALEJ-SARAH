#define FUNCIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_STR 20

typedef struct {
    int id;
    char nom[MAX_STR];
    char poblacio[MAX_STR];
    char sexe[MAX_STR];
    char data_naixement[MAX_STR];
} Usuari;

typedef struct {
    int id;
    int distancia;
} Proper;

extern Usuari usuaris[MAX_USERS];
extern Proper propers[MAX_USERS];

int llegir_usuaris(Usuari usuaris[], int *num_usuaris);
int llegir_distancies(int distancies[][MAX_USERS], int num_usuaris);
void mostra_perfil(int id);
void mostra_menu();
void mostrar_amistats(int id, int distancies[][MAX_USERS], int num_usuaris);
int* usuaris_propers(int id, int distancies[][MAX_USERS]);
void afegir_amistat(int id, int distancies[][MAX_USERS]);
void eliminar_amistats(int id_usuari, int distancies[][MAX_USERS], int id_amistat_a_eliminar);
void merge(Proper arr[], int l, int m, int r);
void mergeSort(Proper arr[], int l, int r);