#include "FUNCIONS.h"

int main() {

    int num_usuaris;
    int distancies[MAX_USERS][MAX_USERS];
    
    nou_perfil();

    if (llegir_usuaris(usuaris, &num_usuaris) != 0) {
        printf("Error al llegir l'arxiu de usuaris. Terminant el programa.\n");
        return 1;
    }
    
    if (llegir_distancies(distancies, num_usuaris) != 0) {
        printf("Error al llegir l'arxiu de distancies. Terminant el programa.\n");
        return 1; 
    }

              
    for (int i = 0; i < num_usuaris; i++) {
        mostra_perfil(i);
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
