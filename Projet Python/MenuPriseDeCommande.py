# -*- coding: utf-8 -*-
"""
Created on Mon May  4 17:54:54 2020

@author: quent
"""
import MenuPrincipal as Menu0
import json # sauvegarde commande
import datetime # heure


def InitialisationMenu4(plat): # initialisation du menu prise de commande
    liste_menu = [""] * len(plat)
    prixtot =0
    p = [0]*len(plat)
    commande = {'Nom':[],'Heure':[], 'plat':[], 'quantite' : [], 'prix':[]}
    prixtot = 0
    return commande,liste_menu,prixtot,p,prixtot
    
def AffichageMenu4(name,quantite,produit,N,plat,categorie,prix,commande,liste_menu,p,prixtot,nbtot): # affichage du menu prise de commande

    print(80*'-')
    print(20*'-' + "{:^40s}".format("RESTAURANT LIPSUM") + 20*'-')
    print(20*'-' + "{:^40s}".format("PRISE DE COMMANDE")+20*'-')
    print(80*'-'+ "\n")
    print("NOM DU CLIENT : ",name,"\n")
    print("\nENTREES DISPONIBLES :")
    v = 0
    for i in range(len(plat)):  # recherche toutes les entrées 
        if categorie[i]== "ENTREE" and plat[i]!= "" and prix [i]!= 0:
            v = v+1
            liste_menu[v-1]= plat[i]
            p[v-1] = prix[i]
            print(v,".",plat[i])
    i = 0
    print("\nPLATS DISPONIBLES : ")
    for i in range(len(plat)): # recherche de tous les plats
        if categorie[i] == "PLAT PRINCIPAL" and plat[i]!="":
            v = v+1
            liste_menu[v-1]= plat[i]
            p[v-1] = prix[i]
            print(v,".", plat[i])
    print("\nDESSERTS DISPONIBLES :")
    i = 0
    for i in range(len(plat)):
        if categorie[i] == "DESSERT" and plat[i]!="": # recherche de tous les desserts
            v = v+1
            liste_menu[v-1]= plat[i]
            p[v-1] = prix[i]
            print(v,".", plat[i])
    print("\nBOISSON DISPONIBLE :")
    i = 0
    for i in range(len(plat)):
        if categorie[i] == "BOISSON" and plat[i]!="": # recherche de toutes les boissons
            v = v+1
            liste_menu[v-1]= plat[i]
            p[v-1] = prix[i]
            print(v, ".", plat[i])      # permet d'avoir liste_menu trié avec entré, plat, dessert et boisson (dans cet ordre)
    print("\n 1. SELECTIONNER UN PRODUIT")
    print(" 2. RESUME DE LA COMMANDE")
    print(" 3. ENVOI DE LA COMMANDE EN CUISINE")
    print(" 4. RETOUR AU MENU PRINCIPAL")
    Menu4(commande,p,liste_menu,name,quantite,produit,N,plat,categorie,prix,prixtot,nbtot) # partie code menu prise de commande
    
    
def Menu4(commande,p,liste_menu,name,quantite,produit,N,plat,categorie,prix,prixtot,nbtot):
    b,c,hc = "","",dict()
    r = int (input("Que voulez vous faire? \n")) # demande utilisateur sur ce qu'il veut faire
    if r == 1: # sélectionner un produit dans la commande du client
        if name not in commande["Nom"]:    
            commande["Nom"].append(name)
            b = int(input("Saisir le numéro du produit :\n ")) # le numéro
            c = int(input("Saisir la quantité de ce produit :\n" )) # la quantite
            # dictionnaire ou est stocké le nom, le(s) plat(s), leur quantite, l'heure et le prix total
            commande["plat"].append(liste_menu[b-1])
            commande["quantite"].append(c)
            prixtot += c*(p[b-1])
            commande["prix"]=prixtot
            h = str(datetime.datetime.now())
            commande["Heure"] = h
            
            AffichageMenu4(name,quantite,produit,N,plat,categorie,prix,commande,liste_menu,p,prixtot,nbtot) # retour à l'affichage
        else:
            b = int(input("Saisir le numéro du produit :\n ")) # le numéro
            c = int(input("Saisir la quantité de ce produit :\n" )) # la quantite
            # dictionnaire ou est stocké le nom, le(s) plat(s), leur quantite, l'heure et le prix total
            commande["plat"].append(liste_menu[b-1])
            commande["quantite"].append(c)
            prixtot += c*(p[b-1])
            commande["prix"] = prixtot
            h = str(datetime.datetime.now())
            commande["Heure"] = h
            AffichageMenu4(name,quantite,produit,N,plat,categorie,prix,commande,liste_menu,p,prixtot,nbtot) # retour à l'affichage



    if r == 2: # Affiche le resumé de la commande
        print(80*'-')
        print(20*'-' + "{:^40s}".format("RESTAURANT LIPSUM") + 20*'-')
        print(20*'-' + "{:^40s}".format("RESUME COMMANDE") + 20*'-')
        print(80*'-')
        for key,values in commande.items(): # affiche les clés et les valeurs du dictionnaire
            print("\n",key,":",values)
        
        print(" \n1. ENVOI EN CUISINE")
        print("2. RETOUR MENU PRISE DE COMMANDE")
        print("3. RETOUR MENU PRINCIPAL")
        g = int(input("Que voulez vous faire ? : "))
 
        
        if g == 1:
            nbtot = Nbcommande(nbtot)
            hc['Commande n°' + str(nbtot)] = commande
            SauvegardeCommande(hc,nbtot) # envoi en cuisine depuis l'affichage du resumé de la commande
            print("La commande a bien été envoyé. ")
            AffichageMenu4(name,quantite,produit,N,plat,categorie,prix,commande,liste_menu,p,prixtot,nbtot)
        if g == 2:
            AffichageMenu4(name,quantite,produit,N,plat,categorie,prix,commande,liste_menu,p,prixtot,nbtot) # retour au menu prise de commande
        if g == 3:
            Menu0.MenuPrincipal(quantite,produit,N,plat,categorie,prix,nbtot) # menu principal
        
    if r == 3: # Envoie en cuisine
        nbtot = Nbcommande(nbtot)
        hc['Commande n°' + str(nbtot)] = commande
        SauvegardeCommande(hc,nbtot)
        
        AffichageMenu4(name,quantite,produit,N,plat,categorie,prix,commande,liste_menu,p,prixtot,nbtot) # retour prise de commande
    if r == 4:
        Menu0.MenuPrincipal(quantite,produit,N,plat,categorie,prix,nbtot)  # menu principal
   
def SauvegardeCommande(hc,nbtot): # sauvegarde dans un json sans supprimer les anciennes commandes (a, le + sert si le fichier n'est pas crée)
    print(hc)
    fp = open ("Commande.json", "w+", encoding ="utf8")
    json.dump(hc['Commande n°' + str(nbtot)], fp, sort_keys = False, indent = 4)   
    fp.close()   
    

    
def Nbcommande(nbtot): # Compteur de commande
    nbtot += 1
    e = open("nbtot.txt", "w+", encoding = "utf8")
    e.write(str(nbtot))     
    e.close()
    return nbtot