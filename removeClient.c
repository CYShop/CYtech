typedef struct {
    char firstName[50];
    char lastName[50];
    int purchaseHistory[3];  
} Client;

void removeClient(Client *clients, int *numClients, int clientID) {
    if (clientID < 0 || clientID >= *numClients) {
        printf("ID de client invalide.\n");
        return;
    }

    for (int i = clientID; i < *numClients - 1; i++) {
        clients[i] = clients[i + 1];
    }

    (*numClients)--;
    printf("Client supprimé avec succès.\n");
}
