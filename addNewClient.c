typedef struct {
    char firstName[50];
    char lastName[50];
    int purchaseHistory[3];  
} Client;

void addNewClient(Client *clients, int *numClients) {
    printf("Entrez le prénom du client: ");
    scanf("%s", clients[*numClients].firstName);
    printf("Entrez le nom de famille du client: ");
    scanf("%s", clients[*numClients].lastName);
    for (int i = 0; i < 3; i++) {
        clients[*numClients].purchaseHistory[i] = 0;
    }
    (*numClients)++;
    printf("Nouveau client ajouté avec succès.\n");
}
