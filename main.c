#include "FUNCIONS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int id_usuari, opcio, count;
    int num_usuaris;
    int *ids_propers = NULL;

    if (llegir_usuaris(&usuaris, &num_usuaris)) {
        printf("No s'ha pogut llegir el fitxer d'usuaris.\n");
        return 1;
    }

    if (llegir_distancies(&distancies, num_usuaris)) {
        printf("No s'ha pogut llegir el fitxer de distàncies.\n");
        free(usuaris);
        return 1;
    }

    printf("Introdueix el teu ID d'usuari: ");
    scanf("%d", &id_usuari);

    while (1) {
        mostra_menu();
        scanf("%d", &opcio);

        switch (opcio) {
            case 1:
                mostra_perfil(id_usuari, usuaris);
                break;
            case 2:
                mostrar_amistats(id_usuari, distancies, num_usuaris, usuaris);
                break;
            case 3:
                ids_propers = usuaris_propers(id_usuari, distancies, num_usuaris, &count);
                afegir_amistat(id_usuari, distancies, ids_propers, count, num_usuaris);
                free(ids_propers);  // Alliberem la memòria de ids_propers
                break;
            case 4:
                eliminar_amistat(id_usuari, distancies, num_usuaris);
                break;
            case 5:
                printf("Sortint...\n");
                free(usuaris);
                free(distancies);
                return 0;
            default:
                printf("Opcio no valida.\n");
        }
    }

    return 0;
}
