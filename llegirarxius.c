#include "FUNCIONS.H"

int llegir_usuaris(Usuari usuaris[], int *num_usuaris) {
    FILE *fitxer = fopen("usuaris.txt", "r");
    if (fitxer == NULL) {
        return 1;
    }
    
    fscanf(fitxer, "%d", num_usuaris);
    
    fgetc(fitxer);

    for (int i = 0; i < *num_usuaris; i++) {
        fscanf(fitxer, " %d", &usuaris[i].id);    //se puede hacer una función que sea (llegir usuario)
        fscanf(fitxer, " %s", usuaris[i].nom);
        fscanf(fitxer, " %s", usuaris[i].sexe);
        fscanf(fitxer, " %s", usuaris[i].poblacio);
        fscanf(fitxer, " %s", usuaris[i].data_naixement);
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
