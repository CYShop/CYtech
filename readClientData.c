#include <stdio.h>

typedef struct {
    char firstName[50];
    char lastName[50];
    int purchaseHistory[3];  
} Client;

void readClientData(Client *clients, int *numClients) {
    FILE *file = fopen("clients.txt", "r");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier clients.\n");
        return;
    }

    while (fscanf(file, "%s %s %d %d %d", clients[*numClients].firstName, clients[*numClients].lastName, &clients[*numClients].purchaseHistory[0], &clients[*numClients].purchaseHistory[1], &clients[*numClients].purchaseHistory[2]) != EOF) {
        (*numClients)++;
    }

    fclose(file);
}
