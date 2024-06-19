#include "FUNCIONS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,  char const *argv[]) 
{   
    int opcio, count, r;
    int num_usuaris;
    int *ids_propers = NULL;

    if (argc != 2)
    {
        printf("\nCal que introdueixis el teu Usuari (0 a 9)\n");
    }
    else if (atoi(argv[1]) < 0 || atoi(argv[1]) > 9)
    {
        printf("\nL'usuari introduit no es valid, torna a obrir el programa amb un usuari entre 0 i 9\n");
    }
    else
    {
        r = inicialitzar_dades(&usuaris, &distancies, &num_usuaris);

        while (r == 0) {
            mostra_menu();
            scanf("%d", &opcio);
            {
            switch (opcio) {
                case 1:
                    mostra_perfil(atoi(argv[1]), usuaris);
                    break;
                case 2:
                    mostrar_amistats(atoi(argv[1]), distancies, num_usuaris, usuaris);
                    break;
                case 3:
                    ids_propers = usuaris_propers(atoi(argv[1]), distancies, num_usuaris, &count);
                    afegir_amistat(atoi(argv[1]), distancies, ids_propers, count, num_usuaris);
                    free(ids_propers);  // Alliberem la memòria de ids_propers
                    break;
                case 4:
                    mostrar_amistats(atoi(argv[1]), distancies, num_usuaris, usuaris);
                    eliminar_amistat(atoi(argv[1]), distancies, num_usuaris);
                    break;
                case 5:
                    editar_perfil(atoi(argv[1]), usuaris, num_usuaris);
                    break;
                case 6:
                    r = 1;
                    printf("Sortint...\n");
                    free(usuaris);
                    free(distancies);
                    break;
                default:
                printf("Opcio no valida.\n");
                }
            }
        }
    }
    return 0;
}
