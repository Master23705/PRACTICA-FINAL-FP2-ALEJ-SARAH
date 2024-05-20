#include "FUNCIONS.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Usuari usuaris[MAX_USERS];

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

int llegir_distancies(int distancies[][MAX_USERS], int num_usuaris) {
    FILE *fitxer = fopen("propers.txt", "r");
    if (fitxer == NULL) {
        return 1;
    }

    for (int i = 0; i < num_usuaris; i++) {
        for (int j = 0; j < num_usuaris; j++) {
            fscanf(fitxer, "%d", &distancies[i][j]);
        }
    }

    fclose(fitxer);
    return 0;
}

void mostra_perfil(int id) {
    if (id < 0 || id >= MAX_USERS || usuaris[id].id == -1) {
        printf("Error: ID de l'usuari no valid.\n");
        return;
    }

    printf("\nPerfil de l'usuari amb ID %d:\n", usuaris[id].id);
    printf("Nom: %s\n", usuaris[id].nom);
    printf("Poblacio: %s\n", usuaris[id].poblacio);
    printf("Sexe: %s\n", usuaris[id].sexe);
    printf("Data de naixement: %s\n", usuaris[id].data_naixement);
}

void mostra_menu() {
    printf("\nMenu:\n");
    printf("1. El meu perfil\n");
    printf("2. Les meves amistats\n");
    printf("3. Afegir amistats\n");
    printf("4. Sortir\n");
    printf("Selecciona una opcio: ");
}

void mostrar_amistats(int id, int distancies[][MAX_USERS], int num_usuaris) {
    
    if (id < 0 || id >= MAX_USERS || usuaris[id].id == -1) {
        printf("Error: ID de l'usuari no valid.\n");
        return;
    }

    printf("\nAmistats de l'usuari amb ID %d:\n", usuaris[id].id);
    for (int i = 0; i < num_usuaris; i++) {
        if (distancies[id][i] == -1) {  
            mostra_perfil(i - 1);
        }
    }
}

typedef struct {
    int id;
    int distancia;
} Proper;

int comparar(const void *a, const void *b) {
    Proper *usuariA = (Proper *)a;
    Proper *usuariB = (Proper *)b;
    return usuariA->distancia - usuariB->distancia;
}

int* usuaris_propers(int id, int distancies[][MAX_USERS]) {
    Proper propers[MAX_USERS];
    int count = 0;

    for (int i = 0; i < MAX_USERS; i++) {
        if (i != id && distancies[id][i] != -1 && distancies[id][i] != 0) {
            propers[count].id = i;
            propers[count].distancia = distancies[id][i];
            count++;
        }
    }

    qsort(propers, count, sizeof(Proper), comparar);

    // Crear una lista para guardar los IDs de los usuarios cercanos
    int* ids_propers = malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) {
        ids_propers[i] = propers[i].id - 1;
        mostra_perfil(ids_propers[i]);
    }

    return ids_propers;
}

void afegir_amistat(int id_usuari, int distancies[][MAX_USERS], int id_nova_amistat) {
    id_nova_amistat++;
    
    distancies[id_usuari][id_nova_amistat] = -1;
    distancies[id_nova_amistat][id_usuari] = -1;
}