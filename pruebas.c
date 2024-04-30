#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 20
#define MAX_USUARIS 10

struct Usuari{
    int id;
    char nom[MAX_STR];
    char poblacio[MAX_STR];
    char sexe;
    
    char data_naixement[MAX_STR];
};

struct Usuari llista_usuaris[MAX_USUARIS];

void nou_perfil() {
    static int id = 0;


    struct Usuari *usuari = &llista_usuaris[id];
    usuari->id = id;


    printf("Indica el teu nom: ");
    fgets(usuari->nom, MAX_STR, stdin);
    usuari->nom[strcspn(usuari->nom, "\n")] = 0;

    printf("Indica la teva poblacio: ");
    fgets(usuari->poblacio, MAX_STR, stdin);
    usuari->poblacio[strcspn(usuari->poblacio, "\n")] = 0;

    printf("Indica el teu sexe (H/D): ");
    scanf(" %c", &usuari->sexe);
    getchar(); 

    printf("Indica la teva data de naixement (DD/MM/AAAA): ");
    fgets(usuari->data_naixement, MAX_STR, stdin);
    usuari->data_naixement[strcspn(usuari->data_naixement, "\n")] = 0;

    id++;
}



void mostra_perfil(int id) {
    if (id < 0 || id >= MAX_USUARIS || llista_usuaris[id].id == -1) {
        printf("Error: ID del usuari no vàlid.\n");
        return;
    }

    struct Usuari *usuari = &llista_usuaris[id];

    printf("Perfil de l'usuari amb ID %d:\n", usuari->id);
    printf("Nom: %s\n", usuari->nom);
    printf("Poblacio: %s\n", usuari->poblacio);
    printf("Sexe: %c\n", usuari->sexe);
    printf("Data de naixement: %s\n", usuari->data_naixement);
}


// MAIN DE PRUEBA 
int main(){
    nou_perfil();
    mostra_perfil(0);
    return 0;
}
