#include "FUNCIONS.h"

int main() {
    int opcion, id_usuari; 
    int num_usuaris;
    int distancies[MAX_USERS][MAX_USERS];
    
    printf("escogeix un ID de usuari\n");
    scanf("%d", &id_usuari);
    getchar();

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
        getchar(); // Netejar buffer de entrada

        switch (opcion) {
            case 1:
                mostra_perfil(id_usuari);
                break;
            case 2:
                mostrar_amistats(id_usuari, distancies, num_usuaris);
                break;
            case 3:
            
                break;
            case 4:
                printf("Adeu!\n");
                return 0; //Sortir del programa
            default:
                printf("Opcio no valida, tria una valida");
                break;
        }
    } while (1); //Bucle infint amb el cual es pot surtir amb el return(0) de el case 4
    
    return 0;
}