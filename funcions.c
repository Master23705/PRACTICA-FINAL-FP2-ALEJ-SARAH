#include "FUNCIONS.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Usuari usuaris[MAX_USERS];

/**
 * @brief Llegeix els ususaris des d'un fitxer
 * @param usuaris Array d'usuaris
 * @param num_usuaris Punter al nombre d'usuaris
 * @return 0 si llegeix correctament, 1 en cas d'error
 */

int llegir_usuaris(Usuari usuaris[], int *num_usuaris) {
    FILE *fitxer = fopen("usuaris.txt", "r");
    if (fitxer == NULL) {
        return 1;
    }

    fscanf(fitxer, "%d", num_usuaris);

    for (int i = 0; i < *num_usuaris; i++) {
        fscanf(fitxer, "%d %s %s %s %s", &usuaris[i].id, usuaris[i].nom, usuaris[i].sexe, usuaris[i].poblacio, usuaris[i].data_naixement);
    }

    fclose(fitxer);
    return 0;
}

/**
 * @brief Llegeix les ditàncies des d'un fitxer
 * @param distancies Matriu de distànceis entre usuaris
 * @param num_usuaris Nombre d'usuaris
 * @return 0 si llegeix correctament, 1 en cas d'error
 */

int llegir_distancies(int distancies[][MAX_USERS], int num_usuaris) {
    FILE *fitxer = fopen("propers.txt", "r");
    if (fitxer == NULL) {
        return 1;
    }
    // Leemos la primera línea y no hacemos nada con ella
    fscanf(fitxer, "%d", &distancies[0][0]);
    for (int i = 0; i < num_usuaris; i++) {
        for (int j = 0; j < num_usuaris; j++) {
            fscanf(fitxer, "%d", &distancies[i][j]);
        }
    }
    
    fclose(fitxer);
    return 0;
}

 /**
 * @brief Mostra el perfil d'un usuari
 * @param id ID de l'usuari
 */

void mostra_perfil(int id) {
    if (id < 0 || id >= MAX_USERS || usuaris[id].id == -1) {
        printf("Error: ID de l'usuari no valid.\n");
        return;
    }

    printf("Perfil de l'usuari amb ID %d:\n", usuaris[id].id);
    printf("Nom: %s\n", usuaris[id].nom);
    printf("Poblacio: %s\n", usuaris[id].poblacio);
    printf("Sexe: %s\n", usuaris[id].sexe);
    printf("Data de naixement: %s\n", usuaris[id].data_naixement);
    printf("\n********************************\n");
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
    printf("5. Sortir\n");
    printf("________________________________\n\n");
    printf("Selecciona una opcio: ");
}

/**
 * @brief Mostra les amistats d'un usuari
 * @param id ID de l'usuari
 * @param distancies Matriu de distancies entre usuaris
 * @param num_usuaris Nombre d'usuaris
 */

int* mostrar_amistats(int id, int distancies[][MAX_USERS], int num_usuaris) {
    
    if (id < 0 || id >= MAX_USERS || usuaris[id].id == -1) {
        printf("Error: ID de l'usuari no valid.\n");
        return NULL;
    }

    // Crear un array para almacenar los IDs de los amigos
    int* amistats = malloc(num_usuaris * sizeof(int));
    int count = 0;

    printf("\nAmistats de l'usuari amb ID %d:\n", usuaris[id].id);
    printf("\n********************************\n");
    for (int i = 0; i < num_usuaris; i++) {
        if (distancies[id][i] == -1) {  
            mostra_perfil(i);
            amistats[count] = i;
            count++;
        }
    }

    // Redimensionar el array para que tenga el tamaño exacto
    amistats = realloc(amistats, count * sizeof(int));

    // Devolver el array de IDs de amigos
    return amistats;

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
 * @return Punter a un array d'enters amb els IDs dels usuaris més propers.
 */
int* usuaris_propers(int id, int distancies[][MAX_USERS], int* count) {
    Proper propers[MAX_USERS];
    *count = 0;
    printf("\nUsuaris propers a tu:\n");
    printf("\n********************************\n");
    
    for (int i = 0; i < MAX_USERS; i++) {
        if (i != id && distancies[id][i] != -1) {
            propers[*count].id = i;
            propers[*count].distancia = distancies[id][i];
            (*count)++;
        }
    }

    mergeSort(propers, 0, *count - 1);
    
    // Crear una llista para guardar els IDs de los usuaris propers
    int* ids_propers = malloc(*count * sizeof(int));
    for (int i = 0; i < *count; i++) {
        ids_propers[i] = propers[i].id;
        mostra_perfil(ids_propers[i]);
    }

    return ids_propers;
}

/**
 * Afegeix una amistat entre usuaris.
 * 
 * @param id Identificador de l'usuari principal.
 * @param distancies Matriu de distàncies entre usuaris.
 */
void afegir_amistat(int id_usuari, int distancies[][MAX_USERS],int* ids_propers, int count) {
    int id_nova_amistat;
    printf("Vols afegir amistat amb algun d'aquests usuaris? (si/no) ");
    char resposta[2];
    scanf("%s", resposta);
    int es_si = ((resposta[0] == 's' || resposta[0] == 'S') &&
             (resposta[1] == 'i' || resposta[1] == 'I'));

    if (es_si) {
        printf("Introdueix l'ID de l'usuari amb el que vols afegir amistat: ");
        scanf("%d", &id_nova_amistat);

        // Comprobar si el ID está en la lista ids_propers
        int id_valid = 0;
        for (int i = 0; i < count; i++) {
            if (ids_propers[i] == id_nova_amistat) {
                id_valid = 1;
                break;
            }
        }
        if (!id_valid) {
            printf("Has introduit un ID no valid. L'usuari amb ID %d no es troba en la llista de noves amistats.\n", id_nova_amistat);
        } else {
            distancies[id_usuari][id_nova_amistat] = -1;
            distancies[id_nova_amistat][id_usuari] = -1;
            printf("S'ha introduit l'usuari amb ID %d com a amistat.\n", id_nova_amistat);
        }
    }
}

/**
 * Elimina una amistat entre usuaris.
 * 
 * @param id_usuari Identificador de l'usuari principal.
 * @param distancies Matriu de distàncies entre usuaris.
 * @param id_amistat_a_eliminar Identificador de l'amistat a eliminar.
 */
void eliminar_amistats(int id_usuari, int distancies[][MAX_USERS], int* amistats, int count) {
    int id_elim_amis;
    printf("Vols eliminar algun usuari de les teves amistats? (si/no) ");
    char resposta[2];
    scanf("%s", resposta);
    int es_si = ((resposta[0] == 's' || resposta[0] == 'S') &&
             (resposta[1] == 'i' || resposta[1] == 'I'));

    if (es_si) {
        printf("Introdueix l'ID de l'usuari del qual vols eliminar l'amistat:");
        scanf("%d", &id_elim_amis);

        int id_valid = 0;
        for (int i = 0; i < count; i++) {
            if (amistats[i] == id_elim_amis) {
                id_valid = 1;
                break;
            }
        }
        if (!id_valid) {
            printf("Has introduit un ID no valid. L'usuari amb ID %d no es troba en la llista d'amistats.\n", id_elim_amis);
        } else {
            // Decisió de disseny: enlloc de posar la distància a 0, posem la distància a 5 per si després es volen tornar a afegir com a amistats
            distancies[id_usuari][id_elim_amis] = 5;
            distancies[id_elim_amis][id_usuari] = 5;
            printf("S'ha eliminat l'usuari amb ID %d com a amistat.\n", id_elim_amis);
        }

    }
   
}