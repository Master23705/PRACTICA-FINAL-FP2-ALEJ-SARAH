#include "FUNCIONS.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Usuari usuaris[MAX_USERS];

int llegir_usuaris(Usuari usuaris[], int *num_usuaris) {
    FILE *fitxer = fopen("usuaris.txt", "r");
    if (fitxer == NULL) {
        return 1;
    }
    
    fscanf(fitxer, "%d", num_usuaris);
    
    fgetc(fitxer);

    for (int i = 0; i < *num_usuaris; i++) {
        fscanf(fitxer, " %d", &usuaris[i].id);    //se puede hacer una función que sea (llegir usuario)
        fscanf(fitxer, " %s", usuaris[i].nom);
        fscanf(fitxer, " %s", usuaris[i].sexe);
        fscanf(fitxer, " %s", usuaris[i].poblacio);
        fscanf(fitxer, " %s", usuaris[i].data_naixement);
    }
    
    fclose(fitxer);
    return 0; 
}

int llegir_distancies(int distancies[][MAX_USERS], int num_usuaris) {
    FILE *fitxer = fopen("propers.txt", "r");
    if (fitxer == NULL) {
        return 1;
    }
    
    for (int i = 0; i < num_usuaris; i++) {
        for (int j = 0; j < num_usuaris; j++) {
            fscanf(fitxer, "%d", &distancies[i][j]);
        }
    }
    
    fclose(fitxer);
    return 0; 
}

void nou_perfil() {
    static int id = 0;

    usuaris[id].id = id;


    printf("Indica el teu nom: ");
    fgets(usuaris[id].nom, MAX_STR, stdin);
    usuaris[id].nom[strcspn(usuaris[id].nom, "\n")] = 0;

    printf("Indica la teva poblacio: ");
    fgets(usuaris[id].poblacio, MAX_STR, stdin);
    usuaris[id].poblacio[strcspn(usuaris[id].poblacio, "\n")] = 0;

    printf("Indica el teu sexe (H/D): ");
    scanf(" %c", &usuaris[id].sexe);
    getchar(); 

    printf("Indica la teva data de naixement (DD/MM/AAAA): ");
    fgets(usuaris[id].data_naixement, MAX_STR, stdin);
    usuaris[id].data_naixement[strcspn(usuaris[id].data_naixement, "\n")] = 0;

    id++;
}
void mostra_perfil(int id) {
    if (id < 0 || id >= MAX_USERS || usuaris[id].id == -1) {
        printf("Error: ID del usuari no valid.\n");
        return;
    }


    printf("Perfil de l'usuari amb ID %d:\n", usuaris[id].id);
    printf("Nom: %s\n", usuaris[id].nom);
    printf("Poblacio: %s\n", usuaris[id].poblacio);
    printf("Sexe: %s\n", usuaris[id].sexe);
    printf("Data de naixement: %s\n", usuaris[id].data_naixement);
}
