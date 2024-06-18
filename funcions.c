#include "FUNCIONS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Usuari *usuaris = NULL;
int *distancies = NULL;

/**
 * @brief Llegeix els usuaris des d'un fitxer
 * @param usuaris Punter a un array d'usuaris
 * @param num_usuaris Punter al nombre d'usuaris
 * @return 0 si llegeix correctament, 1 en cas d'error
 */
int llegir_usuaris(Usuari **usuaris, int *num_usuaris) {
    int r;
    FILE *fitxer = fopen("usuaris.txt", "r");
    if (fitxer == NULL) {
        return 1;
    }

    fscanf(fitxer, "%d", num_usuaris);
    *usuaris = malloc((*num_usuaris) * sizeof(Usuari));
    if (*usuaris == NULL) {
        fclose(fitxer);
        return 1;
    }

    for (int i = 0; i < *num_usuaris; i++) {
        fscanf(fitxer, "%d %s %s %s %s", &(*usuaris)[i].id, (*usuaris)[i].nom, (*usuaris)[i].sexe, (*usuaris)[i].poblacio, (*usuaris)[i].data_naixement);
    }

    fclose(fitxer);
    return 0;
}

/**
 * @brief Llegeix les distàncies des d'un fitxer
 * @param distancies Matriu de distàncies entre usuaris
 * @param num_usuaris Nombre d'usuaris
 * @return 0 si llegeix correctament, 1 en cas d'error
 */
int llegir_distancies(int **distancies, int num_usuaris) {
    int r; 
    FILE *fitxer = fopen("propers.txt", "r");
    if (fitxer == NULL) {
        r = 1;
    }

    *distancies = malloc(num_usuaris * num_usuaris * sizeof(int));
    if (*distancies == NULL) {
        fclose(fitxer);
        r = 1;
    }

    // Leemos la primera línea y no hacemos nada con ella
    fscanf(fitxer, "%d", &(*distancies)[0]);
    for (int i = 0; i < num_usuaris; i++) {
        for (int j = 0; j < num_usuaris; j++) {
            fscanf(fitxer, "%d", &(*distancies)[i * num_usuaris + j]);
        }
    }
    r = 0;
    fclose(fitxer);
    return r;
}

/**
 * @brief Inicialitza les dades d'usuaris i distancies.
 * @param usuaris Punter doble a un de estructuras Usuari, que será llenado con los datos leídos.
 * @param distancies Puntero doble a un arreglo de enteros, que será llenado con las distancias leídas.
 * @param num_usuaris Puntero a un entero que contendrá el número de usuarios leídos.
 * @return Un entero que indica el estado de la inicialización: 0 si es exitoso, 1 si hubo un error.
 */
int inicialitzar_dades(Usuari** usuaris, int** distancies, int* num_usuaris) {
    int r = 0;
    if (llegir_usuaris(usuaris, num_usuaris)) {
        printf("No s'ha pogut llegir el fitxer d'usuaris.\n");
        r = 1;
    }

    if (llegir_distancies(distancies, *num_usuaris)) {
        printf("No s'ha pogut llegir el fitxer de distàncies.\n");
        free(*usuaris);
        r = 1;
    }

    return r;
}

/**
 * @brief Mostra el perfil d'un usuari
 * @param id ID de l'usuari
 */
void mostra_perfil(int id, Usuari *usuaris) {
    if (id < 0 || usuaris[id].id == -1) {
        printf("Error: ID de l'usuari no valid.\n");
    } else {
        printf("\n********************************\n");
        printf("Perfil de l'usuari amb ID %d:\n", usuaris[id].id);
        printf("Nom: %s\n", usuaris[id].nom);
        printf("Poblacio: %s\n", usuaris[id].poblacio);
        printf("Sexe: %s\n", usuaris[id].sexe);
        printf("Data de naixement: %s\n", usuaris[id].data_naixement);
        printf("\n********************************\n");
    }
}

/**
 * @brief Mostra el menú d'opcions
 */
void mostra_menu() {
    printf("\nMenu:\n");
    printf("________________________________\n\n");
    printf("1. El meu perfil\n");
    printf("2. Les meves amistats\n");
    printf("3. Afegir amistats\n");
    printf("4. Eliminar amistats\n");
    printf("5. Editar Perfil\n");
    printf("6. Sortir\n");
    printf("________________________________\n\n");
    printf("Selecciona una opcio: ");
}

/**
 * @brief Mostra les amistats d'un usuari
 * @param id ID de l'usuari
 * @param distancies Matriu de distancies entre usuaris
 * @param num_usuaris Nombre d'usuaris
 */
void mostrar_amistats(int id, int *distancies, int num_usuaris, Usuari *usuaris) {
    printf("\nAmistats de l'usuari amb ID %d:\n", usuaris[id].id);
    printf("\n********************************\n");
    for (int i = 0; i < num_usuaris; i++) {
        if (distancies[id * num_usuaris + i] == -1) {  
            mostra_perfil(i, usuaris);
        }
    }
}

void mostrar_menu_edit_perfil()
{
    printf("________________________________\n\n");
    printf("1. Editar Nom\n");
    printf("2. Editar Sexe\n");
    printf("3. Editar Poblacio\n");
    printf("*****\n");
    printf("4. Guardar i sortir\n");
    printf("________________________________\n\n");
    printf("Selecciona una opcio: ");
}
/**
 * Funció auxiliar per a l'ordenació per barreja.
 * 
 * @param arr Array d'usuaris propers a ordenar.
 * @param l Índex esquerre del subarray a ordenar.
 * @param m Índex mitjà del subarray a ordenar.
 * @param r Índex dret del subarray a ordenar.
 */
void merge(Proper arr[], int p_i, int m, int p_f) {
    int esq = p_i, drt = m + 1, k;
    Proper temp[MAX_USERS];

    k = p_i;
    while ((esq <= m) && (drt <= p_f)) {
        if (arr[esq].distancia < arr[drt].distancia) {
            temp[k] = arr[esq];
            esq++;
        } else {
            temp[k] = arr[drt];
            drt++;
        }
        k++;
    }

    while (esq <= m) {
        temp[k] = arr[esq];
        esq++;
        k++;
    }

    while (drt <= p_f) {
        temp[k] = arr[drt];
        drt++;
        k++;
    }

    for (k = p_i; k <= p_f; k++) {
        arr[k] = temp[k];
    }
}

/**
 * Ordena un array d'usuaris propers utilitzant l'algorisme d'ordenació per barreja (merge sort).
 * 
 * @param arr Array d'usuaris propers a ordenar.
 * @param l Índex esquerre del subarray a ordenar.
 * @param r Índex dret del subarray a ordenar.
 */
void mergeSort(Proper arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

/**
 * Troba els usuaris més propers a un usuari donat el seu ID.
 * 
 * @param id Identificador de l'usuari.
 * @param distancies Matriu de distàncies entre usuaris.
 * @param count Punter a una variable on es guardarà el nombre d'usuaris propers.
 * @return Punter a un array d'enters amb els IDs dels usuaris més propers.
 */
int* usuaris_propers(int id, int *distancies, int num_usuaris, int *count) {
    Proper propers[MAX_USERS];
    *count = 0;
    printf("\nUsuaris propers a tu:\n");
    printf("\n********************************\n");
    
    for (int i = 0; i < num_usuaris; i++) {
        if (i != id && distancies[id * num_usuaris + i] != -1) {
            propers[*count].id = i;
            propers[*count].distancia = distancies[id * num_usuaris + i];
            (*count)++;
        }
    }

    mergeSort(propers, 0, *count - 1);
    
    // Crear una llista per guardar els IDs dels usuaris propers
    int* ids_propers = malloc(*count * sizeof(int));
    for (int i = 0; i < *count; i++) {
        ids_propers[i] = propers[i].id;
        mostra_perfil(ids_propers[i], usuaris);
    }

    return ids_propers;
}

/**
 * @brief Escriu en la matriu de fitxers
 * @param distancies Matriu de distàncies entre usuaris.
 * @param num_usuaris Nombre total d'usuaris.
 * @return 0 si s'escriu correctament, 1 en cas d'error.
 */
int escriure_en_fitxer_distancies(int *distancies, int num_usuaris) {
    int r = 0;
    FILE *fitxer = fopen("propers.txt", "w");
    if (fitxer == NULL) {
        printf("Error: No s'ha pogut obrir el fitxer propers.txt.\n");
        r = 1;
    }

    fprintf(fitxer, "%d\n", num_usuaris);
    for (int i = 0; i < num_usuaris; i++) {
        for (int j = 0; j < num_usuaris; j++) {
            fprintf(fitxer, " %d", distancies[i * num_usuaris + j]);
        }
        fprintf(fitxer, "\n");
    }
    
    fclose(fitxer);
    return r;
}

/**
 * Afegeix una amistat entre usuaris i actualitza el fitxer de distàncies.
 * 
 * @param id_usuari Identificador de l'usuari principal.
 * @param distancies Matriu de distàncies entre usuaris.
 * @param ids_propers Array amb els IDs dels usuaris propers.
 * @param count Nombre d'usuaris propers.
 * @param num_usuaris Nombre total d'usuaris.
 */
void afegir_amistat(int id_usuari, int *distancies, int *ids_propers, int count, int num_usuaris) {
    int id_nova_amistat;
    printf("Vols afegir amistat amb algun d'aquests usuaris? (si/no) ");
    char resposta[3];
    scanf("%s", resposta);
    int es_si = ((resposta[0] == 's' || resposta[0] == 'S') &&
                 (resposta[1] == 'i' || resposta[1] == 'I'));

    if (es_si) {
        printf("Introdueix l'ID de l'usuari amb qui vols afegir amistat: ");
        scanf("%d", &id_nova_amistat);
        
        if (id_nova_amistat >= 0 && id_nova_amistat < num_usuaris && id_nova_amistat != id_usuari) {
            // Afegir amistat en ambdues direccions
            distancies[id_usuari * num_usuaris + id_nova_amistat] = -1;
            distancies[id_nova_amistat * num_usuaris + id_usuari] = -1;
            printf("Amistat afegida correctament amb l'usuari %d.\n", id_nova_amistat);

            // Actualitzar el fitxer de distàncies
            if (escriure_en_fitxer_distancies(distancies, num_usuaris)) {
                printf("Error: No s'ha pogut actualitzar el fitxer de distàncies.\n");
            }
        } else {
            printf("ID no valid.\n");
        }
    }
}

/**
 * Elimina una amistat entre usuaris i actualitza el fitxer de distàncies.
 * 
 * @param id Identificador de l'usuari principal.
 * @param distancies Matriu de distàncies entre usuaris.
 * @param num_usuaris Nombre total d'usuaris.
 */
void eliminar_amistat(int id, int *distancies, int num_usuaris) {
    int id_amistat_eliminar;
    printf("Introdueix l'ID de l'usuari amb qui vols eliminar amistat: ");
    scanf("%d", &id_amistat_eliminar);
    
    if (id_amistat_eliminar >= 0 && id_amistat_eliminar < num_usuaris && id_amistat_eliminar != id) {
        // Eliminar amistat en ambdues direccions
        distancies[id * num_usuaris + id_amistat_eliminar] = 5;
        distancies[id_amistat_eliminar * num_usuaris + id] = 5;
        printf("Amistat eliminada correctament amb l'usuari %d.\n", id_amistat_eliminar);

        // Actualitzar el fitxer de distàncies
        if (escriure_en_fitxer_distancies(distancies, num_usuaris)) {
            printf("Error: No s'ha pogut actualitzar el fitxer de distàncies.\n");
        }
    } else {
        printf("ID no valid.\n");
    }
}
/**
 * @brief Edita el perfil d'un usuari
 * @param id_usuari ID de l'usuario que vol editar el seu perfil
 * @param usuaris Array dels usuaris
 */
void editar_perfil(int id, Usuari *usuaris, int num_usuaris) {
    int opcion = 0;
    int ok;

    while (opcion != 4) {
        mostrar_menu_edit_perfil();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Introdueix el nou nom: ");
                scanf("%s", usuaris[id].nom);
                break;
            case 2:
                ok = 0;
                while (ok == 0) {
                    printf("Escogeix el nou sexe (Home/Dona): \n");
                    scanf("%s", usuaris[id].sexe);
                    // Comprovem que el sexe introduit sigui correcte
                    if (strcmp(usuaris[id].sexe, "Home") == 0 || strcmp(usuaris[id].sexe, "Dona") == 0 ||
                        strcmp(usuaris[id].sexe, "HOME") == 0 || strcmp(usuaris[id].sexe, "DONA") == 0 ||
                        strcmp(usuaris[id].sexe, "home") == 0 || strcmp(usuaris[id].sexe, "dona") == 0) {
                        ok = 1;
                    } else {
                        printf("Sexe introduit no valid, introdueix Home o Dona\n");
                    }
                }
                break;
            case 3:
                printf("Introdueix la nova poblacio: ");
                scanf("%s", usuaris[id].poblacio);
                break;
            case 4:
                desar_dades(id, usuaris, num_usuaris);
                printf("Perfil actualitzat correctament.\n");
                break;
            default:
                printf("Opció no vàlida. Intenta de nou.\n");
        }
    }
}

/**
 * @brief Desa les dades dels usuaris en un fitxer
 * @param usuaris Array dels usuaris
 * @param num_usuaris Nombre total d'usuaris
 */
void desar_dades(int id, Usuari *usuaris, int num_usuaris) {
    FILE *fitxer = fopen("usuaris.txt", "w");
    if (fitxer == NULL) {
        printf("Error: No s'ha pogut obrir el fitxer usuaris.txt.\n");
        return;
    }
    fprintf(fitxer, "%d %s %s %s %s\n", usuaris[id].id, usuaris[id].nom, usuaris[id].sexe, usuaris[id].poblacio, usuaris[id].data_naixement);
    fclose(fitxer);
}

