typedef struct {
    char name[50];
    int refNum;
    int quantity;
    int price;
    int size;
} Product;

void displayStock(Product *products, int numProducts) {
    printf("Stock de produits:\n");
    for (int i = 0; i < numProducts; i++) {
        printf("Nom: %s, Référence: %d, Quantité: %d, Prix: %d, Taille: %d\n", products[i].name, products[i].refNum, products[i].quantity, products[i].price, products[i].size);
    }
}