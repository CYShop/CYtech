#include <stdio.h>

typedef struct {
    char firstName[50];
    char lastName[50];
    int purchaseHistory[3];  
} Client;

void writeClientData(Client *clients, int numClients) {
    FILE *file = fopen("clients.txt", "w");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier clients.\n");
        return;
    }

    for (int i = 0; i < numClients; i++) {
        fprintf(file, "%s %s %d %d %d\n", clients[i].firstName, clients[i].lastName, clients[i].purchaseHistory[0], clients[i].purchaseHistory[1], clients[i].purchaseHistory[2]);
    }

    fclose(file);
}
