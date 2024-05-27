#include "FUNCIONS.h"

int main() {
    int opcion, id_usuari; 
    int num_usuaris;
    int count;
    int distancies[MAX_USERS][MAX_USERS];
    int* id_propers; 
    int* amistats; 

    
    printf("Benvingut a FPBook!\n");
    printf("Introdueix el teu ID: \n");
        if (scanf("%d", &id_usuari) < 0 || id_usuari > MAX_USERS - 1) {
            printf("ID no valid. Si us plau, introdueix un ID entre 0 y %d.\n", MAX_USERS-1);
        }


   

    if (llegir_usuaris(usuaris, &num_usuaris) != 0) {
        printf("Error al llegir l'arxiu de usuaris. Terminant el programa.\n");
        return 1;
    }
    
    if (llegir_distancies(distancies, num_usuaris) != 0) {
        printf("Error al llegir l'arxiu de distancies. Terminant el programa.\n");
        return 1; 
    }

    do {
        mostra_menu();
        scanf("%d", &opcion);
        

        switch (opcion) {
            case 1:
                printf("\n********************************\n");
                mostra_perfil(id_usuari);
                break;
            case 2:
                mostrar_amistats(id_usuari, distancies, num_usuaris);
                break;
            case 3:
                id_propers = usuaris_propers(id_usuari, distancies, &count);
                afegir_amistat(id_usuari, distancies, id_propers, count);
                break;
            case 4:
                amistats = mostrar_amistats(id_usuari, distancies, num_usuaris);
                eliminar_amistats(id_usuari,distancies, count);
                break;
            case 5:
                printf("Adeu!\n");
                return 0; //Sortir del programa
            default:
                printf("\nOpcio no valida, tria una opcio valida siusplau\n");
                break;
        }
    } while (1); //Bucle infint amb el cual es pot surtir amb el return(0) de el case 4
    
    return 0;
}