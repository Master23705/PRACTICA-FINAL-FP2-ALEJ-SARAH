#include "FUNCIONS.h"

int main() {
    int opcion, id_usuari; 
    int num_usuaris;
    int distancies[MAX_USERS][MAX_USERS];

    
    printf("Benvingut a FPBook!\n");
    printf("Introdueix el teu ID: \n");
    scanf("%d", &id_usuari);
   

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
                mostra_perfil(id_usuari);
                break;
            case 2:
                mostrar_amistats(id_usuari, distancies, num_usuaris);
                break;
            case 3:
                usuaris_propers(id_usuari, distancies);
                afegir_amistat(id_usuari, distancies);
                break;
            case 4:
                mostrar_amistats(id_usuari, distancies, num_usuaris);
                eliminar_amistats(id_usuari,distancies);
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