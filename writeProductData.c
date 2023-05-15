#include <stdio.h>

typedef struct {
    char name[50];
    int refNum;
    int quantity;
    int price;
    int size;
} Product;

void writeProductData(Product *products, int numProducts) {
    FILE *file = fopen("products.txt", "w");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier des produits.\n");
        return;
    }

    for (int i = 0; i < numProducts; i++) {
        fprintf(file, "%s %d %d %d %d\n", products[i].name, products[i].refNum, products[i].quantity, products[i].price, products[i].size);
    }

    fclose(file);
}