typedef struct {
    char name[50];
    int refNum;
    int quantity;
    int price;
    int size;
} Product;

typedef struct {
    char firstName[50];
    char lastName[50];
    int purchaseHistory[3];  
} Client;

void purchaseMode(Client *clients, int numClients, Product *products, int numProducts) {
    int choice;
    do {
        printf("\n----- MODE ACHAT -----\n");
        printf("1. Rechercher un produit\n");
        printf("2. Acheter un produit\n");
        printf("3. Afficher l'historique des achats\n");
        printf("0. Quitter le mode achat\n");
        printf("Choisissez une option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char productName[50];
                printf("Entrez le nom du produit: ");
                scanf("%s", productName);

                for (int i = 0; i < numProducts; i++) {
                    if (strcmp(products[i].name, productName) == 0) {
                        printf("Produit trouvé: %s, référence: %d, quantité en stock: %d, prix: %.2f\n", products[i].name, products[i].refNum, products[i].quantity, products[i].price);
                        return;
                    }
                }

                printf("Produit non trouvé.\n");
                break;
            }
            case 2: {
                int clientID;
                int productRef;
                printf("Entrez votre ID client: ");
                scanf("%d", &clientID);
                printf("Entrez la référence du produit: ");
                scanf("%d", &productRef);

                if (clientID < 0 || clientID >= numClients) {
                    printf("ID de client invalide.\n");
                    return;
                }

                for (int i = 0; i < numProducts; i++) {
                    if (products[i].refNum == productRef) {
                        if (products[i].quantity > 0) {
                            products[i].quantity--;
                            for (int j = 2; j > 0; j--) {
                                clients[clientID].purchaseHistory[j] = clients[clientID].purchaseHistory[j - 1];
                            }
                            clients[clientID].purchaseHistory[0] = productRef;
                            printf("Vous avez acheté %s.\n", products[i].name);
                        } else {
                            printf("Désolé, ce produit est en rupture de stock.\n");
                        }
                        return;
                    }
                }

                printf("Produit non trouvé.\n");
                break;
            }
            case 3: {
                int clientID;
                printf("Entrez votre ID client: ");
                scanf("%d", &clientID);

                if (clientID < 0 || clientID >= numClients) {
                    printf("ID de client invalide.\n");
                    return;
                }

                printf("Historique des achats:\n");
                for (int i = 0; i < 3; i++) {
                    if (clients[clientID].purchaseHistory[i] != 0) {
                        printf("%d ", clients[clientID].purchaseHistory[i]);
                    }
                }
                printf("\n");
                break;
            }
            case 0:
                printf("Sortie du mode achat.\n");
                break;
            default:
                printf("Option invalide.\n");
                break;
        }
    } while (choice != 0);
}
