typedef struct {
    char firstName[50];
    char lastName[50];
    int purchaseHistory[3];  
} Client;

void displayPurchaseHistory(Client *clients, int numClients, int clientID) {
    if (clientID < 0 || clientID >= numClients) {
        printf("ID de client invalide.\n");
        return;
    }

    printf("Historique d'achats pour %s %s:\n", clients[clientID].firstName, clients[clientID].lastName);
    for (int i = 0; i < 3; i++) {
        if (clients[clientID].purchaseHistory[i] != 0) {
            printf("Produit %d: %d\n", i+1, clients[clientID].purchaseHistory[i]);
        }
    }
}
