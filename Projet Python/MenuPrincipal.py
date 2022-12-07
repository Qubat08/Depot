# -*- coding: utf-8 -*-
"""
Created on Tue Apr 28 20:05:00 2020

@author: quent
"""
import MenuGestionDesStocks as Menu2
import MenuGestionDesPlats as Menu3
import MenuPriseDeCommande as Menu1
import MenuHistoriqueDesCommandes as Menu4
def InitialisationMenu(): # Fonction initialisation (appel chargement fichier)
#    N=100
#    quantite = [0]*100
#    quantite[0]=50
#    quantite[1]=10
#    quantite[2]= 30
#    quantite[3]=70
#    produit = [""]*100   
#    produit[0]= "PAIN A HAMBURGER"
#    produit[1]="ONGLET DE BOEUF"
#    produit[2]= "TOMATES"
#    produit[3]= "POMMES DE TERRE"
#    plat=[""]*100
#    plat[0]="SAUTE DE BOEUF"
#    plat[1]="TERRINE DE CAMPAGNE"
#    plat[2]="QUICHE LORRAINE"
#    plat[3]="TARTE AUX POMMES"
#    plat[4]="VIN BLANC ARJOLLES"
#    categorie=[""]*100
#    categorie[0]="PLAT PRINCIPAL"
#    categorie[1]="ENTREE"
#    categorie[2]="PLAT PRINCIPAL"
#    categorie[3]="DESSERT"
#    categorie[4]="BOISSON"
#    prix = [0]*100
#    prix[0]=12
#    prix[1]=5
#    prix[2]=10
#    prix[3]=5
#    prix[4]=3
    quantite,produit,N = ListeProduitsChargement()
    prix,categorie,plat = ListePlatsChargement()
    nbtot = nbtotchargement()
#    nbtot = 0
    return quantite,produit,N,plat,categorie,prix,nbtot #retourne les valeurs



def nbtotchargement():
    nbtot = 0
    f = open("nbtot.txt","r",encoding = "utf8")
    nbtot = int(f.readline())
    f.close()
    return nbtot   
    
    
def ListeProduitsChargement(): # lit le fichier produit.txt
    quantite=[0]*100
    produit = [""]*100

    f = open("./Produits.txt","r",encoding = "utf8") # ouverture

    N = int(f.readline()) # taille du doc
    
    for i in range(N):
        split= f.readline().replace("\n","").split(" ",1) # permet de séparer en 2 groupes (premier groupe avant l'espace et 2e tout le reste)
        quantite[i]= int(split[0]) # affectation dans une liste quantite
        produit[i] = split[1] # affectation dans une liste produit
        
    f.close()
    return quantite,produit,N # retourne valeurs

def ListePlatsChargement(): # lit le fichier plat.txt et categorie.txt
    prix=[0]*100
    categorie = [""]*100
    plat = [""]*100
    
    f = open("Plat.txt","r", encoding= "utf8")  # meme principe qu'a dessus
    Z = int(f.readline())
    for h in range(Z):
        split = f.readline().replace("\n","").split(" ",1)
        prix[h]= int(split[0])
        plat[h]= split[1]
        
    f.close()
    
    z = open("Categorie.txt","r", encoding = "utf8")
    X = int(z.readline())
    
    for g in range(X):
        split = z.readline().replace("\n","") # lit une ligne entière
        categorie[g] = split
        
    z.close()
    
    return prix,categorie,plat # retourne les valeurs

def MenuPrincipal(quantite,produit,N,plat,categorie,prix,nbtot): # début menu principal
    
    print(80*'-')
    print(20*'-' + "{:^40s}".format("RESTAURANT LIPSUM") + 20*'-')  # Affichage MenuPrincipal
    print(20*'-' + "{:^40s}".format("15 rue des Ecoles") + 20*'-')
    print(20*'-' + "{:^40s}".format("08360 GIVET") + 20*'-')
    print(80*'-' +"\n")
    print("MENU PRINCIPAL : \n")
    print("   1. PRISE DE COMMANDE")
    print("   2. GESTION DES STOCKS")
    print("   3. GESTION DU MENU")
    print("   4. HISTORIQUE DES COMMANDES")
    print("   5. QUITTER")
    
    reponse =int(input("\n QUE VOULEZ VOUS FAIRE ? (1-5):\n"))  # demande utilisateur
    if reponse == 1 : # ouverture prise de commande
        name= input("LE NOM DU CLIENT?\n")
        commande,liste_menu,prix_tot,p,prixtot = Menu1.InitialisationMenu4(plat)
        Menu1.AffichageMenu4(name,quantite,produit,N,plat,categorie,prix,commande,liste_menu,p,prixtot,nbtot)
    if reponse == 2: # ouverture gestion des stocks
        print ("\nGESTION DES STOCKS OUVERTURE .... ")
        Menu2.AffichageMenu2(quantite,produit,N,plat,categorie,prix,nbtot)
    if reponse == 3: # ouverture gestion du menu
        print ("\nGESTION DU MENU OUVERTURE ...." )
        Menu3.AffichageMenu3(quantite,produit,N,plat,categorie,prix,nbtot)
    if reponse == 4: # ouverture historique des commandes
        print ("\nHISTORIQUE DES COMMANDES .... ")
#        commande = Menu4.InitialisationMenu4()
        Menu4.AffichageMenu4(nbtot)
        
    if reponse == 5: # quitter
        print ("\nA bientôt")
#    if reponse != 1 or reponse!= 2 or reponse!=3 or reponse!= 4 or reponse!= 5:
#        print("MERCI DE SAISIR UNE VALEUR COMPRISE ENTRE 1 ET 5") 
#        MenuPrincipal(quantite,produit,N,plat,categorie,prix)