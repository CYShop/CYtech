typedef struct {
    char name[50];
    int refNum;
    int quantity;
    int price;
    int size;
} Product;

void manageMode(Product *products, int numProducts, int maxSpace) {
    int choice;
    do {
        printf("\n----- MODE GESTION -----\n");
        printf("1. Consulter le stock d'un produit\n");
        printf("2. Ajouter du stock à un produit\n");
        printf("3. Vérifier l'espace de stockage\n");
        printf("0. Quitter le mode gestion\n");
        printf("Choisissez une option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char productName[50];
                printf("Entrez le nom du produit: ");
                scanf("%s", productName);

                for (int i = 0; i < numProducts; i++) {
                    if (strcmp(products[i].name, productName) == 0) {
                        printf("Stock pour %s: %d\n", productName, products[i].quantity);
                        return;
                    }
                }

                printf("Produit non trouvé.\n");
                break;
            }
            case 2: {
                char productName[50];
                int increase;
                printf("Entrez le nom du produit: ");
                scanf("%s", productName);
                printf("Entrez la quantité à ajouter: ");
                scanf("%d", &increase);

                for (int i = 0; i < numProducts; i++) {
                    if (strcmp(products[i].name, productName) == 0) {
                        if (products[i].quantity + increase > maxSpace) {
                            printf("Espace de stock insuffisant.\n");
                        } else {
                            products[i].quantity += increase;
                            printf("Le stock de %s a été augmenté de %d.\n", productName, increase);
                        }
                        return;
                    }
                }

                printf("Produit non trouvé.\n");
                break;
            }
            case 3: {
                int totalSpace = 0;
                for (int i = 0; i < numProducts; i++) {
                    totalSpace += products[i].quantity;
                }
                printf("Espace de stock restant: %d\n", maxSpace - totalSpace);
                break;
            }
            case 0:
                printf("Sortie du mode gestion.\n");
                break;
            default:
                printf("Option invalide.\n");
                break;
        }
    } while (choice != 0);
}
