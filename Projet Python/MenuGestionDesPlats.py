# -*- coding: utf-8 -*-
"""
Created on Mon May  4 08:49:36 2020

@author: quent
"""
import MenuPrincipal as Menu0


def AffichageMenu3(quantite,produit,N,plat,categorie,prix,nbtot): # Fonction affichage gestion du menu
    print(80*'-')
    print(20*'-' + "{:^40s}".format("RESTAURANT LIPSUM") + 20*'-')
    print(20*'-' + "{:^40s}".format("GESTION DU MENU")+20*'-')
    print(80*'-'+ "\n\n")
    print(80*'-')
    print("|" + 4*' ' + 4*' ' + "PLAT"+ 18*' ' + "|" + 5*' ' + "CATEGORIE" + 18*' '+ "|"+5*' '+"PRIX" )
    print(80*'-')
    for i in range(len(plat)):
        if plat[i]!="":
            mot = str(categorie[i])
            carac = 25 - len(plat[i]) # variable pour avoir le même espacement lors du print quelques soit la longueur de plat ou de la categorie
            carac2 = 31 - len(categorie[i])
            print( "|", i+1,"."+  plat[i], carac*' '+"|"+ mot, carac2*' '+"|" ,prix[i])      
    print(80*'-')
    print("\nMENU GESTION DU MENU :")
    print("\n   1. MODIFIER UN PLAT")
    print("   2. AJOUTER UN PLAT")
    print("   3. SUPPRIMER UN PRODUIT")
    print("   4. RETOUR AU MENU PRINCIPAL")
    Menu3(quantite,produit,N,plat,categorie,prix,nbtot)  # appel aux codes du menu
    
def Menu3(quantite,produit,N,plat,categorie,prix,nbtot):
    b = int(input("\n QUE VOULEZ VOUS FAIRE ? (1-4):\n")) # demande utilisateur sur ce qu'il veut faire
    
    if b == 1: # Modifier Produit
        print(" 1. Le nom d'un plat")
        print(" 2. La catégorie d'un plat")
        print(" 3. Le prix d'un plat")
        print(" 4. Retour")
        rep = int(input("Que voulez-vous modifier ? \n")) # demande de ce qu'il veut modifier
        if rep == 1:# modification du nom d'un plat
            nb = int(input("Quel est le numéro du plat à modifier?\n"))-1 # demande du numéro du plat à modifier (-1 car l'affichage commence à 1)
            newname = (input("Saisir le nouveau nom\n")) # le nouveau nom 
            plat[nb]= newname
            print("Le nom a bien été modifié.\n")
            AffichageMenu3(quantite,produit,N,plat,categorie,prix,nbtot) # retourne l'affichage pour voir les modifications
        if rep == 2: # modifier la categorie d'un plat
            nb = int(input("Quel est le numéro du plat à modifier?\n"))-1 # demande le numéro
            print(" 1. PLAT PRINCIPAL")
            print(" 2. ENTREE")
            print(" 3. DESSERT")
            print(" 4. BOISSON")
            print(" 5. RETOUR")
            newcat = int(input("Saisir la nouvelle catégorie (1-5).\n")) # demande la nouvelle categorie
            if newcat == 1:
                categorie[nb]= "PLAT PRINCIPAL"
                print("La catégorie du plat a bien été modifié\n") # changement de categorie
                AffichageMenu3(quantite,produit,N,plat,categorie,prix,nbtot)
            if newcat == 2:
                categorie[nb]= "ENTREE"
                print("La catégorie du plat a bien été modifié\n")
                AffichageMenu3(quantite,produit,N,plat,categorie,prix,nbtot)
            if newcat == 3:
                categorie[nb]= "DESSERT"
                print("La catégorie du plat a bien été modifié\n")
                AffichageMenu3(quantite,produit,N,plat,categorie,prix,nbtot)
            if newcat== 4:
                categorie[nb]= "BOISSON"
                print("La catégorie du plat a bien été modifié\n")
                AffichageMenu3(quantite,produit,N,plat,categorie,prix,nbtot)
            if newcat == 5:
                AffichageMenu3(quantite,produit,N,plat,categorie,prix,nbtot)
        if rep == 3: # modification du prix d'un produit
            nb = int(input("Quel est le numéro du plat à modifier?\n"))-1
            newprix = (int(input("Saisir le nouveau prix\n")))
            prix[nb]=newprix
            print("Le prix du plat a bien été modifié .\n")
            AffichageMenu3(quantite,produit,N,plat,categorie,prix,nbtot) # retour à l'affichage pour voir les modifications
        if rep == 4: # retour
            AffichageMenu3(quantite,produit,N,plat,categorie,prix,nbtot)
            
    if b == 2: #Ajout plat
        for i in range(len(plat)):
            if plat[i]=="": # detection première case vide
                nb = i
                break
        newp = input("Saisir le nom du nouveau plat: \n") # nouveau nom
        plat[nb]=newp
        print(" 1. PLAT PRINCIPAL")
        print(" 2. ENTREE")
        print(" 3. DESSERT")
        print(" 4. BOISSON")
        print(" 5. RETOUR")
        newc = int(input("Saisir la nouvelle catégorie (1-5): \n")) # choix de la catégorie
        if newc == 1:
            categorie[nb]= "PLAT PRINCIPAL"
        if newc == 2:
            categorie[nb]= "ENTREE"
        if newc == 3:
            categorie[nb]= "DESSERT"
        if newc== 4:
            categorie[nb]= "BOISSON"
        if newc == 5:
            AffichageMenu3(quantite,produit,N,plat,categorie,prix,nbtot) #bouton retour
        newp = int(input("Saisir le nouveau prix : \n" )) # prix du nouveau plat
        prix[nb]=newp
        print("Le plat a été ajouté:")
        AffichageMenu3(quantite,produit,N,plat,categorie,prix,nbtot) # retour affichage pour avoir les modifications
        
    if b ==3: #Supression d'un plat
        nb = int(input("Saisir le numéro du produit à supprimer:\n"))
        print("1. Oui\n")
        print("2. Non\n") 
        conf = int(input("Etes-vous sûr ?")) # demande confirmation
        if conf == 1:
            plat[nb-1]= ""
            categorie[nb-1] = ""
            prix[nb-1]=0
            print("Le produit a bien été supprimé.")
            AffichageMenu3(quantite,produit,N,plat,categorie,prix,nbtot) # retour affichage pour avoir les modifications
        if conf == 2:
            AffichageMenu3(quantite,produit,N,plat,categorie,prix,nbtot) # annule la suppression
    if b == 4: # retour au menu principal avec sauvegarde automatique
        SauvegardePlat(plat,categorie,prix) 
        Menu0.MenuPrincipal(quantite,produit,N,plat,categorie,prix,nbtot)

def SauvegardePlat(plat,categorie,prix): # sauvegarde (2 fichiers, l'un avec les prix et le nom et l'autre avec les categories)
    f = open("Plat.txt", "w+", encoding = "utf8")
    
    f.write(str(len(plat)))
    
    for i in range(len(plat)):
            f.write("\n{:d} {:s}".format(prix[i], plat[i]))
            
    f.close()
    
    z = open("Categorie.txt","w+", encoding = "utf8")
    
    z.write(str(len(categorie)))
    
    for i in range(len(categorie)):
           z.write("\n{:s}".format(categorie[i]))
            
    z.close()