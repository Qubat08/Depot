# -*- coding: utf-8 -*-
"""
Created on Mon May  4 08:15:18 2020

@author: quent
"""
import MenuPrincipal as Menu0

def AffichageMenu2(quantite,produit,N,plat,categorie,prix,nbtot): # Affichage Menu2
    i=0
    cara = 0
    print(80*'-')
    print(20*'-' + "{:^40s}".format("RESTAURANT LIPSUM") + 20*'-')
    print(20*'-' + "{:^40s}".format("GESTION DES STOCKS")+20*'-')
    print(80*'-'+ "\n")
    print(80*'-'+ "\n")
    print("|" + 3*' ' + "|" + 4*' ' + "PRODUIT"+ 42*' ' + "|" + 5*' ' + "QUANTITE")
    print (80*'-')

    for i in range(N): 
        if produit[i]!="":
            cara = 50 - len(produit[i]) # permet d'avoir le même nombre d'espace quelques soit la longueur de produit[i]
            print( "|", i+1,"|", produit[i], cara*' ', "|", 5*' ', quantite[i])
    
            
    print(80*'-')
    print("\n MENU GESTION DES STOCKS :")
    print("\n   1.MISE A JOUR DU STOCK")
    print("   2.AJOUT DE PRODUITS")
    print("   3.EXPORTER LA LISTE DES PRODUITS")
    print("   4.SUPPRIMER UN PRODUIT")
    print("   5.RETOUR AU MENU PRINCIPAL")
    Menu2(quantite,produit,N,plat,categorie,prix,nbtot)
    
    
def Menu2(quantite,produit,N,plat,categorie,prix,nbtot): # Partie code menu2
   
    r = int(input("\n QUE VOULEZ VOUS FAIRE ? (1-5):\n")) # demande utilisateur
    
    
    if r == 1: # modifie un produit
        nbp = int(input("VEUILLEZ ENTRER LE NUMERO DU PRODUIT: \n")) # demande le numéro
        print (" \n 1. MODIFIER UN NOM")
        print(" 2. MODIFIDER UNE QUANTITE")
        b = int(input("Que voulez vous faire")) # choisir quoi modifier
        if b == 1: # modifier le nom
            newname = input("Saisir le nouveau nom")
            produit[nbp-1] = newname
            
        if b == 2: # modifier la quantite
            modif = int(input("COMBIEN RESTE T'IL DE PRODUIT:\n"))
            quantite[nbp-1]=modif
        print("LE PRODUIT", nbp, "A ETAIT MODIFIEE")
        AffichageMenu2(quantite,produit,N,plat,categorie,prix,nbtot) # retoune à l'affichage pour voir les modifications dans le menu
    
    
    if r == 2: # Ajout d'un produit
        newp=input("VEUILLEZ ENTRER LE NOM DU NOUVEAU PRODUIT:\n")
        for i in range(N):
            if produit[i]=="":  # cherche la première case vide
                produit[i]=newp
                break
        newq=int(input("VEUILLEZ ENTRER LA QUANTITE DE CE PRODUIT:\n")) # demande la quantite du nouveau produit
        quantite[i]=newq
        print("LE PRODUIT A BIEN ETE AJOUTE A LA LISTE.")
        AffichageMenu2(quantite,produit,N,plat,categorie,prix,nbtot) # retoune à l'affichage pour voir les modifications dans le menu
    if r == 3:# Sauvegarde
        Sauvegarde(quantite,produit) # appel fonction sauvegarde
        print("EXPORTATION TERMINEE\n")
        AffichageMenu2(quantite,produit,N,plat,categorie,prix,nbtot)
    if r == 4: # Supprimer un produit
        delp=int(input("Quel est le numéro du produit que vous voulez supprimer?\n"))
        produit[delp-1]= "" # remise à zeo des cases de la liste correspondante (i-1 car pour l'affichage je commence au produit numéro 1 et pas 0 comme dans la liste)
        quantite[delp-1]= 0 
        print("Le produit a bien été supprimé.\n")
        AffichageMenu2(quantite,produit,N,plat,categorie,prix,nbtot)
    if r == 5: # Retour au menu principal avec sauvegarde automatique
        Sauvegarde(quantite,produit)
        Menu0.MenuPrincipal(quantite,produit,N,plat,categorie,prix,nbtot) 

def Sauvegarde(quantite,produit): # fonction sauvegarde
    f = open("Produits.txt", "w+", encoding = "utf8")
    
    f.write(str(len(produit)))
    
    for i in range(len(produit)):
        f.write("\n{:d} {:s}".format(quantite[i], produit[i]))
    
    f.close()