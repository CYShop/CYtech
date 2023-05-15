#include <stdio.h>
#include "readProductData.h"
#include "writeProductData.h"
#include "displayStock.h"
#include "updateStock.h"
#include "checkStockSpace.h"
#include "readClientData.h"
#include "writeClientData.h"
#include "addNewClient.h"
#include "removeClient.h"
#include "displayPurchaseHistory.h"
#include "manageMode.h"
#include "purchaseMode.h"

// Définir les structures pour le produit et le client

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

// Stocker les numéros de référence des produits pour l'historique des achats
// Fonctions pour gérer les produits

void readProductData(Product *products, int *numProducts);
void writeProductData(Product *products, int numProducts);
void displayStock(Product *products, int numProducts);
void updateStock(Product *products, int numProducts);
void checkStockSpace(Product *products, int numProducts, int maxSpace);

// Fonctions pour gérer les clients

void readClientData(Client *clients, int *numClients);
void writeClientData(Client *clients, int numClients);
void addNewClient(Client *clients, int *numClients);
void removeClient(Client *clients, int *numClients, int clientID);
void displayPurchaseHistory(Client *clients, int numClients, int clientID);

// Fonctions pour gérer les modes

void managementMode(Product *products, int numProducts, Client *clients, int numClients);
void purchaseMode(Client *clients, int numClients, Product *products, int numProducts);

int main() {
    // Initialiser les tableaux de produits et de clients
    Product products[100];
    int numProducts = 0;

    Client clients[100];
    int numClients = 0;

    // Lire les données du produit et du client à partir des fichiers
    readProductData(products, &numProducts);
    readClientData(clients, &numClients);

    // Boucle principale du programme
    while (1) {
        printf("Choisissez un mode : \n1. Mode gestion \n2. Mode achat \n3. Quitter\n");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                managementMode(products, numProducts, clients, numClients);
                break;
            case 2:
                purchaseMode(products, numProducts, clients, numClients);
                break;
            case 3:
                return 0;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
    }
}
