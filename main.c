#include "FUNCIONS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int id_usuari, opcio, count, r;
    int num_usuaris;
    int *ids_propers = NULL;

    r = inicializar_datos(&usuaris, &distancies, &num_usuaris);

    printf("Introdueix el teu ID d'usuari: ");
    scanf("%d", &id_usuari);

    while (r == 0) {
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
                break;
            default:
                printf("Opcio no valida.\n");
        }
    }

    return 0;
}
