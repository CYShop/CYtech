# CYtechPrincipe de notre projet : CY Shop 

Notre projet est un programme C qui permet la gestion de stocks et de clients d’un concessionnaire Porsche.  

Vous avez accès a deux modes, un mode gestion et un mode achat. 

Le mode gestion, est le mode qui est plus destinée au “concessionnaire”. 

Le mode gestion contient plusieurs fonctionnalités :  

1. Afficher le stock, permet d’afficher le stock actuel du concessionnaire. 

2. Mettre à jour le stock, permet d’ajouter la quantité d’un produit du stock. 

3. Vérifier l'espace de stockage, vérifie si le l’espace de stockage du stock n’est pas ou pour voir combien de place il reste dans le garage. 

4. Ajouter un nouveau produit, permet d’ajouter un modèle de voiture avec 

5. Vider le stock, permet d’enlever une certaine quantité (choisi par l’utilisateur) du produit au stock ou de supprimer le produit du stock. 

6. Quitter le mode de gestion, permet de revenir en arrière, pour choisir le mode gestion ou mode d’achat. 

Le mode d’achat est destiné aux clients. 

Le mode d’achat contient également plusieurs fonctionnalités : 

1. Afficher l'historique des achats, voir les trois derniers produits achetés 

2. Ajouter un produit au panier, permet au client d’ajouter le produit de son choix dans son panier s’il a le solde nécessaire. 

3. Supprimer un produit du panier, supprime la quantité du produit décidée par le client de son panier. 

4. Acheter les produits du panier, permet d’acheter le panier dans son intégralité si son solde le lui permet.  

5. Voir le solde, permet de voir l’argent du client. 

6. Ajouter au solde, rajoute de l’argent dans le solde du client. 

7. Afficher le panier, permet de voir ce que le client dans son panier. 

8. Supprimer le compte, supprime définitivement le compte du client. 

9. Quitter le mode d'achat, permet de revenir en arrière, pour choisir le mode gestion ou mode d’achat. 

Bug connu :  

L'historique d’achat affiche uniquement “0” quand il écrit la référence.  

Lors du choix du mode gestion puis création d’une erreur avec des caractère dans le mode puis quitter le mode cela affiche ceci : *** stack smashing detected ***: terminated. Et quitte le programme 

 
