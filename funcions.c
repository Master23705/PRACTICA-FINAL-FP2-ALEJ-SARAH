#ifndef FUNCIONS_H
#define FUNCIONS_H

#define MAX_USERS 100
#define MAX_STRING 50

typedef struct {
    int id;
    char nom[MAX_STRING];
    char sexe[MAX_STRING];
    char poblacio[MAX_STRING];
    char data_naixement[MAX_STRING];
} Usuari;

typedef struct {
    int id;
    int distancia;
} Proper;

extern Usuari *usuaris;
extern int *distancies;

int editar_perfil(int id, Usuari * usuaris, int num_usuaris);
int inicialitzar_dades(Usuari** usuaris, int** distancies, int* num_usuaris);
int llegir_usuaris(Usuari **usuaris, int *num_usuaris);
int llegir_distancies(int **distancies, int num_usuaris);
void mostra_perfil(int id, Usuari *usuaris);
void mostra_menu();
void mostrar_amistats(int id, int *distancies, int num_usuaris, Usuari *usuaris);
void mergeSort(Proper arr[], int l, int r);
int* usuaris_propers(int id, int *distancies, int num_usuaris, int *count);
int escriure_en_fitxer_distancies(int *distancies, int num_usuaris);
void afegir_amistat(int id, int *distancies, int *ids_propers, int count, int num_usuaris);
void eliminar_amistat(int id, int *distancies, int num_usuaris);
int escriure_en_fitxer_usuaris();

#endif
