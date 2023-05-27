#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Définir les structures pour le produit et le client

typedef struct {
    char name[50];
    int refNum;
    int quantity;
    int price;
    int size;
} Product;

typedef struct {
    int id;
    char name[50];
    char firstName[50];
    int balance;
    int numPurchases;
    int purchaseHistory[3];
    int cart[3]; // Panier de consommation
    int cartQuantities[3]; // Quantité des produits dans le panier
    int numItemsInCart; // Nombre d'articles dans le panier
} Client;


// juste le titre
void printTitle(const char* title) {
    int length = strlen(title);
    int i;

    printf("+");
    for (i = 0; i < length + 4; i++) {
        printf("-");
    }
    printf("+\n");

    printf("|  ");
    printf("%s", title);
    printf("  |\n");

    printf("+");
    for (i = 0; i < length + 4; i++) {
        printf("-");
    }
    printf("+\n");
}
// Stocker les numéros de référence des produits pour l'historique des achats
// Fonctions pour gérer les produits

void readProductData(Product *products, int *numProducts) {
    FILE *file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("\n===========================================\n");
        printf("\033[31mErreur d'ouverture du fichier des produits.\033[0m\n");
        printf("\n===========================================\n");
        return;
    }

    while (fscanf(file, "%s %d %d %d %d", products[*numProducts].name, &products[*numProducts].refNum, &products[*numProducts].quantity, &products[*numProducts].price, &products[*numProducts].size) != EOF) {
        (*numProducts)++;
    }

    fclose(file);
}

void writeProductData(Product *products, int numProducts) {
    FILE *file = fopen("products.txt", "w");
    if (file == NULL) {
        printf("\n===========================================\n");
        printf("\033[31mErreur d'ouverture du fichier des produits.\033[0m\n");
        printf("\n===========================================\n");
        return;
    }

    for (int i = 0; i < numProducts; i++) {
        fprintf(file, "%s %d %d %d %d\n", products[i].name, products[i].refNum, products[i].quantity, products[i].price, products[i].size);
    }

    fclose(file);
}

void displayStock(Product *products, int numProducts) {
    printf("\n===========================================\n");
    printf("Stock de produits:\n\n");
    printf("------------------------------------------------------------------\n");
    printf("|   Nom         |   Référence   |  Quantité  |   Prix    |  Taille |\n");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < numProducts; i++) {
        printf("|%-15s|%-14d|%-12d|%-11d|%-10d|\n", products[i].name, products[i].refNum, products[i].quantity, products[i].price, products[i].size);
    }
    printf("------------------------------------------------------------------\n");
    printf("\n===========================================\n");
}

void updateStock(Product *products, int *numProducts) {
    int refNum, quantity;
    //Référence en tant que chaine de caractère
    printf("Entrez le numéro de référence du produit stocké : \n");
    char refNumstr[50];
    saisiref:
    scanf("%s", refNumstr);
    refNum=atoi(refNumstr);
    if (refNum<=0) {
        printf("Entrez un numéro de numéro de référence correcte : \n");
        goto saisiref;
    }
   
    int productIndex = -1;
    for (int i = 0; i < *numProducts; i++) {
        if (products[i].refNum == refNum) {
            productIndex = i;
            break;
        }
    }

    if (productIndex == -1) {
        printf("\033[31mProduit non trouvé.\033[0m\n");
        printf("\n===========================================\n");
        return;
    }

    printf("Entrez la quantité à ajouter : ");
    char quantitystr[50];
    SaisiRef:
    scanf("%s", quantitystr);
    quantity = atoi(quantitystr);
    if (quantity <= 0) {
        printf("\033[31mQuantité invalide. Veuillez entrer une quantité positive :\033[0m\n");
        goto SaisiRef;
    }
    
    int totalSpace = 100;
    int maxSpace=0;
    for (int i = 0; i < *numProducts; i++) {
        maxSpace += products[i].size * products[i].quantity;
    }
    int productSpace = products[productIndex].size * (products[productIndex].quantity + quantity);
    if (maxSpace + quantity > totalSpace) {
        printf("\033[31mCapacité de stockage maximale atteinte. Impossible d'ajouter plus de produits.\033[0m\n");
        printf("\n===========================================\n");
        return;
    }
    
    products[productIndex].quantity += quantity;
    printf("\033[32mLe stock du produit a été mis à jour.\033[0m\n");
    printf("\n===========================================\n");
    writeProductData(products, *numProducts); // sauvegarder les modifications dans le fichier
}


void checkStockSpace(Product *products, int numProducts, int maxSpace) {
    int totalSpace = 100;
    maxSpace=0;
    for (int i = 0; i < numProducts; i++) {
        maxSpace += products[i].size * products[i].quantity;
    }
    if (maxSpace > totalSpace) {
        printf("\n===========================================\n");
        printf("\033[31mAttention: la capacité de stockage du magasin est dépassée de:\033[0m %d\n", abs(totalSpace - maxSpace));
        printf("\n===========================================\n");
    } else {
        printf("\n===========================================\n");
        printf("\033[32mEspace de stockage restant:\033[0m %d\n", totalSpace - maxSpace);
        printf("\n===========================================\n");
    }
}

// Fonctions pour gérer les clients

void readClientData(Client *clients, int *numClients) {
    FILE *file = fopen("clients.txt", "r");
    if (file == NULL) {
        printf("\n===========================================\n");
        printf("\033[31mErreur d'ouverture du fichier clients.\033[0m\n");
        printf("\n===========================================\n");
        return;
    }

    while (fscanf(file, "%s %s %d %d %d %d %d", clients[*numClients].firstName, clients[*numClients].name, &clients[*numClients].id, &clients[*numClients].purchaseHistory[0], &clients[*numClients].purchaseHistory[1], &clients[*numClients].purchaseHistory[2], &clients[*numClients].balance) != EOF) {
        (*numClients)++;
    }

    fclose(file);
}

void writeClientData(Client *clients, int numClients) {
    FILE *file = fopen("clients.txt", "w");
    if (file == NULL) {
        printf("\n===========================================\n");
        printf("\033[31mImpossible d'ouvrir le fichier clients.txt\033[0m\n");
        printf("\n===========================================\n");
        return;
    }

    for (int i = 0; i < numClients; i++) {
        fprintf(file, "%s %s %d %d %d %d %d\n", clients[i].firstName, clients[i].name, clients[i].id, clients[i].purchaseHistory[0], clients[i].purchaseHistory[1], clients[i].purchaseHistory[2], clients[i].balance);
    }

    fclose(file);
}

int checkClientID(Client *clients, int numClients, int id) {
    for (int i = 0; i < numClients; i++) {
        if (clients[i].id == id) {
            return 1;
        }
    }
    return 0;
}

void addNewClient(Client *clients, int *numClients) {
    printf("\n===========================================\n");
    printf("Entrez le nom du client:\n ");
    NAME:
    scanf("%s", clients[*numClients].name);
    if (atoi(clients[*numClients].name)>0 || atoi(clients[*numClients].name)<0){
        printf ("Entrez un nom existant :\n");
        goto NAME;
    }


    printf("Entrez le prénom du client: \n");
    FIRSTNAME:
    scanf("%s", clients[*numClients].firstName);
    if (atoi(clients[*numClients].firstName)>0 || atoi(clients[*numClients].firstName)<0){
        printf ("Entrez un prénom existant :\n");
        goto FIRSTNAME;
    }


    printf("Combien d'argent voulez-vous déposer sur le compte ? \n");
    char soldestr[50];
    Solderef:
    scanf("%s", soldestr);
    int solde;
    solde = atoi(soldestr);
    clients[*numClients].balance = solde;
    if (solde <= 0) {
        printf("Veuillez rentrer un prix réel :\n");
        goto Solderef;
    }




    clients[*numClients].id = *numClients;
    clients[*numClients].numPurchases = 0;
    clients[*numClients].numItemsInCart = 0;
    (*numClients)++;
    printf("\n===========================================\n");
}

int findClientByID(Client *clients, int numClients, int id) {
    for (int i = 0; i < numClients; i++) {
        if (clients[i].id == id) {
            return i;
        }
    }
    return -1;
}

void removeClient(Client *clients, int *numClients, int clientID) {
    if (clientID < 0 || clientID >= *numClients) {
        printf("\n===========================================\n");
        printf("\033[31mID de client invalide.\033[0m\n");
        printf("\n===========================================\n");
        return;
    }

    for (int i = clientID; i < *numClients - 1; i++) {
        clients[i] = clients[i + 1];
    }

    (*numClients)--;
    printf("\n===========================================\n");
    printf("\033[32mClient supprimé avec succès.\033[0m\n");
    printf("\n===========================================\n");
}

void displayPurchaseHistory(Client *clients, int numClients, int clientID) {
    if (clientID >= 0 && clientID < numClients) {
        printf("\n===========================================\n");
        printf("Historique d'achat du client :\n");
        printf("Prénom : %s, Nom : %s\n", clients[clientID].firstName, clients[clientID].name);
        int numPurchases = clients[clientID].numPurchases;
        if (numPurchases > 0) {
            printf("Achats :\n");
            for (int i = 0; i < numPurchases; i++) {
                printf("Réference de l'achat %d : %d\n", i + 1, clients[clientID].purchaseHistory[i]);
            }
        } else {
            printf("\033[31mAucun achat enregistré.\033[0m\n");
            printf("\n===========================================\n");

        }
    } else {
        printf("\033[31mID client invalide.\033[0m\n");
        printf("\n===========================================\n");

    }
}

// Fonction pour acheter un produit

void buyProduct(Product *products, int numProducts, Client *clients, int clientID) {
    int refNum, quantity, size;
    char refNumstr[50];
   
    printf("\n===========================================\n");
    printf("Voici les produits disponibles :\n\n");
    displayStock(products, numProducts);
    printf("\nEntrez le numéro de référence du produit que vous souhaitez acheter : ");
    SAISiref:
    scanf("%s", refNumstr);
    refNum=atoi(refNumstr);
    if (refNum<=0) {
        printf("Entrez un numéro de numéro de référence correcte : \n");
        goto SAISiref;
    }

    for (int i = 0; i < numProducts; i++) {
        if (products[i].refNum == refNum) {
            if (products[i].quantity > 0) {
                printf("Entrez la quantité du produit à acheter  : ");
                char quantitystr[50];
                SaisiRef:
                scanf("%s", quantitystr);
                quantity = atoi(quantitystr);
                if (quantity <= 0) {
                printf("\033[31mQuantité invalide. Veuillez entrer une quantité valide :\033[0m\n");
                goto SaisiRef;
                }

                if (quantity > products[i].quantity) {
                    printf("\033[31mQuantité insuffisante en stock.\033[0m\n");
                    printf("\n===========================================\n");
                    return;
                }

                char sizestr[50];
                int size;
                printf("Entrez la taille du produit que vous souhaitez acheter :\n");
                SaisiReF:
                scanf("%s", sizestr);
                size = atoi(sizestr);
                if (size <= 0) {
                printf("\033[31mTaille invalide. Veuillez entrer une taille réelle :\033[0m\n");
                goto SaisiReF;
                }
               
                if (size != products[i].size) {
                    printf("\033[31mLa taille spécifiée n'est pas disponible pour ce produit.\033[0m\n");
                    printf("\n===========================================\n");
                    return;
                }

                int totalPrice = products[i].price * quantity; // Calculer le prix total en fonction de la quantité choisie

                if (clients[clientID].balance >= totalPrice) {
                    products[i].quantity -= quantity;
                    printf("Vous avez ajouté %d unité(s) du produit %s (taille %d) au panier.\n", quantity, products[i].name, size);
                    printf("\n===========================================\n");
                    // Ajouter le produit au panier du client
                    if (clients[clientID].numItemsInCart < 3) {
                        clients[clientID].cart[clients[clientID].numItemsInCart] = refNum;
                        clients[clientID].cartQuantities[clients[clientID].numItemsInCart] = quantity;
                        clients[clientID].numItemsInCart++;
                        return;
                    } else {
                        printf("\033[31mVotre panier est plein. Veuillez effectuer l'achat ou supprimer des articles du panier.\033[0m\n");
                        printf("\n===========================================\n");
                        return;
                    }
                } else {
                    printf("\033[31mSolde insuffisant pour cet achat.\033[0m\n");
                    printf("\n===========================================\n");
                    return;
                }
            } else {
                printf("\033[31mDésolé, ce produit est en rupture de stock.\033[0m\n");
                printf("\n===========================================\n");
                return;
            }
        }
    }

    printf("\033[31mProduit non trouvé.\033[0m\n");
    printf("\n===========================================\n");
}


// Supprimer un produit du panier

void removeProductFromCart(Client *client) {
    int refNum, quantity;
    printf("\n===========================================\n");
    printf("Entrez le numéro de référence du produit à supprimer du panier : \n");
    char refNumstr[50];
    saisiref:
    scanf("%s", refNumstr);
    refNum = atoi(refNumstr);
    if (refNum <= 0) {
        printf("Entrez un numéro de référence correct : \n");
        goto saisiref;
    }

    for (int i = 0; i < client->numItemsInCart; i++) {
        if (client->cart[i] == refNum) {
            printf("Entrez la quantité du produit à supprimer du panier : ");
            char quantitystr[50];
            SaisiRef:
            scanf("%s", quantitystr);
            quantity = atoi(quantitystr);
            if (quantity <= 0) {
                printf("\033[31mQuantité invalide. Veuillez entrer une quantité valide :\033[0m\n");
                goto SaisiRef;
            }

            // Vérifier si la quantité spécifiée est supérieure ou égale à la quantité présente dans le panier
            if (quantity >= client->cartQuantities[i]) {
                // Supprimer complètement le produit du panier
                for (int j = i; j < client->numItemsInCart - 1; j++) {
                    client->cart[j] = client->cart[j + 1];
                    client->cartQuantities[j] = client->cartQuantities[j + 1];
                }
                client->numItemsInCart--;
            } else {
                // Réduire la quantité du produit dans le panier
                client->cartQuantities[i] -= quantity;
            }

            printf("\033[31mQuantité spécifiée du produit supprimée du panier avec succès.\033[0m\n");
            printf("\n===========================================\n");
            return;
        }
    }

    printf("\033[31mProduit non trouvé dans le panier.\033[0m\n");
    printf("\n===========================================\n");
}



// Acheter les produits du panier

void checkout(Client *client, Product *products, int numProducts) {
    int totalCost = 0;
    printf("\n===========================================\n");
    printf("Produits achetés:\n");
    for (int i = 0; i < client->numItemsInCart; i++) {
        for (int j = 0; j < numProducts; j++) {
            if (products[j].refNum == client->cart[i]) {
                printf("%s - Prix unitaire: %d - Quantité: %d\n", products[j].name, products[j].price, client->cartQuantities[i]);
                totalCost += products[j].price * client->cartQuantities[i]; // Calculer le prix total en multipliant le prix unitaire par la quantité
                break;
            }
        }
    }

    if (totalCost > 0) {
        if (client->balance >= totalCost) {
            client->balance -= totalCost; // Déduire le prix total de l'achat du solde du client
            printf("\033[32mAchat réussi ! Votre nouveau solde est de :\033[0m %d\n", client->balance);
            client->numPurchases++;
            client->numItemsInCart = 0; // Vider le panier après l'achat
            printf("\n===========================================\n");
        } else {
            printf("\033[31mSolde insuffisant pour cet achat.\033[0m\n");
            printf("\n===========================================\n");
        }
    } else {
        printf("\033[31mVotre panier est vide. Impossible de procéder au paiement.\033[0m\n");
        printf("\n===========================================\n");
    }
}

//ajout d'un produit

void addNewProduct(Product *products, int *numProducts) {
    printf("\n===========================================\n");
    printf("Entrez le nom du produit :\n ");
    scanf("%s", products[*numProducts].name);

    int refNum;
    displayStock(products, *numProducts);
    printf("\nEntrez le numéro de référence du produit :\n ");
    char refNumstr[50];
    SAISIRef:
    scanf("%s", refNumstr);
    refNum=atoi(refNumstr);
    if (refNum<=0) {
        printf("Entrez un numéro de numéro de référence correcte : \n");
        goto SAISIRef;
    }

    // Vérifier si la référence du produit existe déjà
    for (int i = 0; i < *numProducts; i++) {
        if (products[i].refNum == refNum) {
            printf("\033[31mUn produit avec la même référence existe déjà. Veuillez entrer une référence différente.\033[0m\n");
            goto SAISIRef;
            return;
        }
    }

    products[*numProducts].refNum = refNum;
    char quantitystr[50];
    printf("Entrez la quantité du produit :\n");
    Saisiref:
    scanf("%s", quantitystr);
    int quantity;
    quantity = atoi(quantitystr);
    products[*numProducts].quantity = quantity;
    if (quantity <= 0) {
        printf("\033[31mQuantité invalide. Veuillez entrer une quantité positive :\033[0m\n");
        goto Saisiref;
    }

    char sizestr[50];
    int size;
    printf("Entrez la taille du produit :\n");
    SaisiRef:
    scanf("%s", sizestr);
    size = atoi(sizestr);
    products[*numProducts].size = size;
    if (size <= 0) {
        printf("\033[31mTaille invalide. Veuillez entrer une taille réelle :\033[0m\n");
        goto SaisiRef;
    }

    int totalSpace = 100;
    int maxSpace=0;
    int productSpace = products[*numProducts].size * quantity;
    for (int i = 0; i < *numProducts; i++) {
        maxSpace += products[i].size * products[i].quantity;
    }
    maxSpace+=productSpace;
   
    if (totalSpace < maxSpace) {
        printf("\033[31mCapacité de stockage dépassée de : %d unité(s).\033[0m", abs(maxSpace - totalSpace)); printf (" Impossible d'ajouter plus de produits.\n");
        printf("\n===========================================\n");
        return;
    }

    printf("Entrez le prix du produit :\n ");
    int price;
    char pricestr[50];
    Priceref:
    scanf("%s", pricestr);
    price = atoi(pricestr);
    products[*numProducts].price = price;
    if (price <= 0) {
        printf("Veuillez rentrer un prix réel :\n");
        goto Priceref;
    }

    (*numProducts)++;
    printf("\033[32mNouveau produit ajouté avec succès.\033[0m\n");
    checkStockSpace(products, *numProducts, 100);
}


//Afficher le panier
void displayCart(Product *products, int numProducts, Client *client) {
    printf("\n===========================================\n");
    printf("Panier de %s %s:\n", client->firstName, client->name);

    if (client->numItemsInCart == 0) {
        printf("\033[31mVotre panier est vide.\033[0m\n");

        printf("Souhaitez-vous consulter le stock ? (1: Oui, 2: Non)\n");
        int choice;
        char choicestr[50];
        Choiceref:
        scanf("%s", choicestr);
        choice = atoi(choicestr);
        if (choice != 1 && choice != 2 ) {
        printf("Veuillez rentrer l'un des deux choix possible (1: Oui, 2: Non) pour consulter le stock :\n");
        goto Choiceref;
        }

        if (choice == 1) {
            displayStock(products, numProducts);
        }
       
        return;
    }

    printf("---------------------------------------------------------------------\n");
    printf("|    Nom    |   Référence  |   Quantité   |     Prix    |    Taille   |\n");
    printf("---------------------------------------------------------------------\n");

    for (int i = 0; i < client->numItemsInCart; i++) {
        int refNum = client->cart[i];
        int quantity = client->cartQuantities[i];

        for (int j = 0; j < numProducts; j++) {
            if (products[j].refNum == refNum) {
                printf("| %-10s| %12d | %12d | %12d | %12d |\n", products[j].name, products[j].refNum, quantity, products[j].price, products[j].size);
                break;
            }
        }
    }

    printf("---------------------------------------------------------------------\n");
    printf("\n===========================================\n");
}



//supprimer un compte

void removeAccount(Client *clients, int *numClients, int clientID) {
    if (clientID < 0 || clientID >= *numClients) {
        printf("\n===========================================\n");
        printf("\033[31mID de client invalide.\033[0m\n");
        return;
    }

    for (int i = clientID; i < *numClients - 1; i++) {
        clients[i] = clients[i + 1];
    }

    (*numClients)--;
    printf("\n===========================================\n");
    printf("\033[32mCompte supprimé avec succès.\033[0m\n");
}

//supprimer produit

void removeProduct(Product *products, int *numProducts) {
    int refNum;
    printf("Entrez le numéro de référence du produit à supprimer :\n ");
    char refNumstr[50];
    SAISIRef:
    scanf("%s", refNumstr);
    refNum=atoi(refNumstr);
    if (refNum<=0) {
        printf("Entrez un numéro de numéro de référence correcte : \n");
        goto SAISIRef;
    }

    int productIndex = -1;
    for (int i = 0; i < *numProducts; i++) {
        if (products[i].refNum == refNum) {
            productIndex = i;
            break;
        }
    }

    if (productIndex == -1) {
        printf("\033[31mProduit non trouvé.\033[0m\n");
        printf("\n===========================================\n");
        return;
    }

    printf("Entrez la quantité du produit à supprimer :\n");
    char quantitystr[50];
    SAIsiref:
    scanf("%s", quantitystr);
    int quantity;
    quantity = atoi(quantitystr);

    if (quantity <= 0 || quantity > products[productIndex].quantity) {
        printf("\033[31mQuantité invalide. Veuillez entrer une quantité valide.\033[0m\n");
        goto SAIsiref;
        return;
    }

    if (quantity == products[productIndex].quantity) {
        // Supprimer complètement le produit
        for (int i = productIndex; i < *numProducts - 1; i++) {
            products[i] = products[i + 1];
        }
        (*numProducts)--;
        printf("\033[32mProduit supprimé avec succès.\033[0m\n");
        printf("\n===========================================\n");
    } else {
        // Réduire la quantité du produit
        products[productIndex].quantity -= quantity;
        printf("\033[32mQuantité du produit réduite avec succès.\033[0m\n");
        printf("\n===========================================\n");
    }

    // Vérifier si le stock est vide
    if (*numProducts == 0) {
        printf("\033[31mStock vide.\033[0m\n");
        printf("\n===========================================\n");
    }
}


void managementMode(Product *products, int *numProducts, Client *clients, int *numClients) {
    while (1) {
        printf("\nChoisissez une option:\n\n 1. Afficher le stock\n 2. Mettre à jour le stock\n 3. Vérifier l'espace de stockage\n 4. Ajouter un nouveau produit\n 5. Vider le stock\n 6. Quitter le mode de gestion\n");
       
        int choice;
        char choices[2];
        scanf("%s", choices);
        choice = atoi(choices);
        Menu:
       
        switch (choice) {
            case 1:
                displayStock(products, *numProducts);
                break;
            case 2:
                displayStock(products, *numProducts);
                updateStock(products, numProducts);
                writeProductData(products, *numProducts); // save changes to file
                break;
            case 3:
                checkStockSpace(products, *numProducts, 200); // assuming max space is 200
                break;
            case 4:
                addNewProduct(products, numProducts);
                writeProductData(products, *numProducts); // save changes to file
                break;
            case 5:
                displayStock(products, *numProducts);
                removeProduct(products, numProducts);
                writeProductData(products, *numProducts); // sauvegarder les modifications dans le fichier
                break;
            case 6:
                return;
            default:
                printf("\n===========================================\n");
                printf("\033[31mChoix invalide. Veuillez réessayer.\033[0m\n");
               
                printf("\nChoisissez une option:\n\n 1. Afficher le stock\n 2. Mettre à jour le stock\n 3. Vérifier l'espace de stockage\n 4. Ajouter un nouveau produit\n 5. Vider le stock\n 6. Quitter le mode de gestion\n");
       
                scanf("%s", choices);
                choice = atoi(choices);                
                goto Menu;
                printf("\n===========================================\n");
                break;
        }
    }
}

void purchaseMode(Client *clients, int *numClients, Product *products, int *numProducts) {
    menuID:
    int clientID;
    printf("Entrez votre ID de client (ou -1 si vous êtes un nouveau client) :\n");
    char clientIDstr[50];
    scanf("%s", clientIDstr);
    if (strlen(clientIDstr)>1 && atoi(clientIDstr) == 0){
        goto menuID;
    }
    clientID = atoi(clientIDstr);

    if (clientID == -1) {
    addNewClient(clients, numClients);
    clientID = clients[*numClients - 1].id;
    writeClientData(clients, *numClients+1); // save changes to file
    }
    else if (findClientByID(clients, *numClients, clientID) == -1) {
        printf("\033[31mID de client invalide.\033[0m\n");
        printf("\n===========================================\n");
        goto menuID;
        return;
    }

    printf("Bonjour %s %s:\n\n", clients[clientID].firstName, clients[clientID].name);
    printf("\033[32mVotre identifiant est:\033[0m %d \n\n", clientID);

    while (1) {
        printf("Choisissez une option:\n\n");
        printf("1. Afficher l'historique des achats\n");
        printf("2. Ajouter un produit au panier\n");
        printf("3. Supprimer un produit du panier\n");
        printf("4. Acheter les produits du panier\n");
        printf("5. Voir le solde\n");
        printf("6. Ajouter au solde\n");
        printf("7. Afficher le panier\n");
        printf("8. Supprimer le compte\n");
        printf("9. Quitter le mode d'achat\n");
       
        int choice;
        char choices[2];
        scanf("%s", choices);
        choice = atoi(choices);
        menus:
       
        switch (choice) {
            case 1:
                displayPurchaseHistory(clients, *numClients, clientID);
                break;
            case 2:
                buyProduct(products, *numProducts, clients, clientID);
                writeProductData(products, *numProducts); // save changes to file
                writeClientData(clients, *numClients); // save changes to file
                break;
            case 3:
                removeProductFromCart(&clients[clientID]);
                break;
            case 4:
                checkout(&clients[clientID], products, *numProducts);
                writeProductData(products, *numProducts); // save changes to file
                writeClientData(clients, *numClients); // save changes to file
                break;
            case 5:
                printf("\n===========================================\n");
                printf("Votre solde actuel est: %d\n", clients[clientID].balance);
                printf("\n===========================================\n");
                break;
            case 6:
            printf("\n===========================================\n");
                printf("Entrez le montant à ajouter à votre solde: ");
                char amountstr[50];
                amountref:
                scanf("%s", amountstr);
                int amount;
                amount = atoi(amountstr);
                if (amount <= 0) {
                printf("Veuillez rentrer un prix correcte :\n");
                goto amountref;
                }
                clients[clientID].balance += amount;
                printf("\033[32mVotre solde a été mis à jour. Nouveau solde:\033[0m %d\n", clients[clientID].balance);
                writeClientData(clients, *numClients); // save changes to file
                printf("\n===========================================\n");
                break;
            case 7:
                displayCart(products, *numProducts, &clients[clientID]);
                break;
            case 8:
                removeAccount(clients, numClients, clientID);
                writeClientData(clients, *numClients); // save changes to file
                return;
            case 9:
                return;
            default:
                printf("\n===========================================\n");
                printf("\033[31mChoix invalide. Veuillez réessayer.\033[0m\n\n");

                printf("Choisissez une option:\n\n");
                printf("1. Afficher l'historique des achats\n");
                printf("2. Ajouter un produit au panier\n");
                printf("3. Supprimer un produit du panier\n");
                printf("4. Acheter les produits du panier\n");
                printf("5. Voir le solde\n");
                printf("6. Ajouter au solde\n");
                printf("7. Afficher le panier\n");
                printf("8. Supprimer le compte\n");
                printf("9. Quitter le mode d'achat\n");
               
                scanf("%s", choices);
                choice = atoi(choices);                
                goto menus;              
                printf("\n===========================================\n");
                break;
        }
    }
}

//souligner
void underline(char *str) {
    printf("%s\n", str);
    for(int i = 0; i < strlen(str); i++) {
        printf("-");
    }
    printf("\n");
}

void mainLoop(Product *products, int *numProducts, Client *clients, int *numClients) {
    while (1) {
        char choiceStr[] = "\n\033[34mChoisissez un mode:\033[0m";
        underline(choiceStr);
        printf("\n1. Mode gestion \n2. Mode achat \n3. Quitter\n");

        int choice;
        char choices[2];
        scanf("%s", choices);
        choice = atoi(choices);
        menu:

        switch (choice) {
            case 1:
                printf("\n===========================================\n");
                managementMode(products, numProducts, clients, numClients);
                printf("\n===========================================\n");
                break;
            case 2:
                printf("\n===========================================\n");
                purchaseMode(clients, numClients, products, numProducts);
                printf("\n===========================================\n");
                break;
            case 3:
                return;
            default:
                printf("\n===========================================\n");
                printf("\033[31mChoix invalide. Veuillez réessayer.\033[0m\n");
                printf("\n1. Mode gestion \n2. Mode achat \n3. Quitter\n");
                scanf("%s", choices);
                choice = atoi(choices);
                goto menu;
                printf("\n===========================================\n");
                break;
        }
    }
}

int main() {
    const char* title = "Bienvenue chez Luxury Porsche";
    printTitle(title);

    // Initialiser les tableaux de produits et de clients
    Product products[100];
    int numProducts = 0;

    Client clients[100];
    int numClients = 0;

    // Lire les données du produit et du client à partir des fichiers
    readProductData(products, &numProducts);
    readClientData(clients, &numClients);

    // Boucle principale du programme
    mainLoop(products, &numProducts, clients, &numClients);

    return 0;
}
