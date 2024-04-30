#include "funcions.h"

int main() {

    int num_usuaris;
    Usuari usuaris[MAX_USERS];
    int distancies[MAX_USERS][MAX_USERS];
    
    if (llegir_usuaris(usuaris, &num_usuaris) != 0) {
        printf("Error al llegir l'arxiu de usuaris. Terminant el programa.\n");
        return 1;
    }
    
    if (llegir_distancies(distancies, num_usuaris) != 0) {
        printf("Error al llegir l'arxiu de distancies. Terminant el programa.\n");
        return 1; 
    }

    printf("Usuaris llegits correctament:\n");               
    for (int i = 0; i < num_usuaris; i++) {
        printf("Usuari %d:\n", i+1); 
        printf("  Nom: %s\n", usuaris[i].nom);
        printf("  Sexe: %s\n", usuaris[i].sexe);
        printf("  Poblacio: %s\n", usuaris[i].poblacio);
        printf("  Data naixement: %s\n", usuaris[i].data_naixement);
    } 

    printf("\nDistancias llegides correctament:\n");
    for (int i = 0; i < num_usuaris; i++) {
        for (int j = 0; j < num_usuaris; j++) {
            printf("%d ", distancies[i][j]);
        }
        printf("\n");
    }
    
    return 0;
} 
