typedef struct {
    char name[50];
    int refNum;
    int quantity;
    int price;
    int size;
} Product;

void updateStock(Product *products, int numProducts) {
    int refNum, quantity;
    printf("Entrez le numéro de référence du produit: ");
    scanf("%d", &refNum);
    printf("Entrez la quantité à ajouter: ");
    scanf("%d", &quantity);

    for (int i = 0; i < numProducts; i++) {
        if (products[i].refNum == refNum) {
            products[i].quantity += quantity;
            printf("Le stock du produit a été mis à jour.\n");
            return;
        }
    }

    printf("Produit non trouvé.\n");
}
