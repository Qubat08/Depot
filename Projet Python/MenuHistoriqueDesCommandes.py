# -*- coding: utf-8 -*-
"""
Created on Sun May 10 13:40:05 2020

@author: quent
"""
import MenuPrincipal as Menu0
import json

#def InitialisationMenu4():
#    commande = ChargementCommande()
#
#    return commande
    
    
#def ChargementCommande():
#    commande = dict()
#    with open ("test.json") as c:
#        commande = json.load(c)
#    c.close()
#    return commande       

def AffichageMenu4(nbtot):
#    x = len(commande['Nom'])
#    print(x)
    print(80*'-')
    print(20*'-' + "{:^40s}".format("RESTAURANT LIPSUM") + 20*'-')
    print(20*'-' + "{:^40s}".format("HISTORIQUE DES COMMANDES")+20*'-')
    print(80*'-'+ "\n")
    print("NOMBRE TOTAL DE COMMANDES PASSES :",nbtot)
    print("MONTANT TOTAL DES COMMANDES",)