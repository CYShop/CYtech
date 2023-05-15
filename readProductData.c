#include <stdio.h>

typedef struct {
    char name[50];
    int refNum;
    int quantity;
    int price;
    int size;
} Product;

void readProductData(Product *products, int *numProducts) {
    FILE *file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier des produits.\n");
        return;
    }

    while (fscanf(file, "%s %d %d %d %d", products[*numProducts].name, &products[*numProducts].refNum, &products[*numProducts].quantity, &products[*numProducts].price, &products[*numProducts].size) != EOF) {
        (*numProducts)++;
    }

    fclose(file);
}
