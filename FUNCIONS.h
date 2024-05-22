#define FUNCIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10 //Màxim de usuaris que es poden llegir
#define MAX_STR 20   //Màxim de caràcters per string

//Estructura per guardar la informació dels usuaris
typedef struct {
    int id;                        //Identificador de l'usuari
    char nom[MAX_STR];             //Nom de l'usuari
    char poblacio[MAX_STR];        //Població de l'usuari
    char sexe[MAX_STR];            //Sexe de l'usuari
    char data_naixement[MAX_STR];  //Data de naixement de l'usuari
} Usuari;

//Estructura per guardar la informació dels usuaris propers
typedef struct {
    int id;          //Identificador de l'usuari
    int distancia;   //Distància de l'usuari a un altre usuari
} Proper;

//Declaració de variables globals
extern Usuari usuaris[MAX_USERS];  
extern Proper propers[MAX_USERS];  

//Declaració de funcions
int llegir_usuaris(Usuari usuaris[], int *num_usuaris);
int llegir_distancies(int distancies[][MAX_USERS], int num_usuaris);
void mostra_perfil(int id);
void mostra_menu();
void mostrar_amistats(int id, int distancies[][MAX_USERS], int num_usuaris);
void merge(Proper arr[], int l, int m, int r);
void mergeSort(Proper arr[], int l, int r);
int* usuaris_propers(int id, int distancies[][MAX_USERS]);
void afegir_amistat(int id, int distancies[][MAX_USERS]);
void eliminar_amistats(int id_usuari, int distancies[][MAX_USERS], int id_amistat_a_eliminar);

