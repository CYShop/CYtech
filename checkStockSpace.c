typedef struct {
    char name[50];
    int refNum;
    int quantity;
    int price;
    int size;
} Product;

void checkStockSpace(Product *products, int numProducts, int maxSpace) {
    int totalSpace = 0;
    for (int i = 0; i < numProducts; i++) {
        totalSpace += products[i].size * products[i].quantity;
    }

    if (totalSpace > maxSpace) {
        printf("Attention: la capacité de stockage du magasin est dépassée.\n");
    } else {
        printf("Espace de stockage restant: %d\n", maxSpace - totalSpace);
    }
}
