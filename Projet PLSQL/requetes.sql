/* PARTIE SQL */
/* 1)	Afficher le noms des marques des produits non conforme ou périmés :*/
Select nomMarque from MarqueProduit where idMarque IN (
    Select idMarque from Produit where idLots IN (
        Select idLots from FicheInventaire where Statuts Like 'C' OR Statuts Like 'E'
        )
    );


/* 2)	Le nom des produits plus cher que la moyenne :*/

Select NomProduit from Produit where idProduit IN (
    Select idProduit from Produit where PrixProduit > (
        Select AVG(PrixProduit) From Produit
    ));

/*3)	Les produits qui appartiennent à la catégorie « viande » et qui contiennent des colorants :*/


Select nomProduit from PRoduit where idProduit in (
Select idProduit FROM Produit where idCategorie in (
Select idCategorie from Categorie where NomCategorie LIKE 'viande')
INTERSECT
Select idProduit FROM Produit where idColorants in (
Select idColorants from Colorants where NomColorant NOT LIKE 'SansColorant')
);


/*4)	Les produits qui sortent le 15 décembre (périmé et / ou sortie) : */
Select nomProduit from Produit where idLots IN (
Select idLots from Lots where 
    DateSortie LIKE TO_DATE('2022-12-15','YYYY-MM-DD')
UNION 
Select idLots from Lots where 
    DateConsommation LIKE TO_DATE('2022-12-15','YYYY-MM-DD')
);

/* 5)	Les noms des produits qui ne viennent pas de France :*/
Select nomProduit from Produit where idLots IN (
Select idLots from Lots where Origine NOT LIKE 'France');

/* 6)	Les noms des produits qui ont une fiche inventaire conforme réalisée par le technicien Legault*/
Select nomProduit from Produit where idLots in (
Select idLots from FicheInventaire where statuts LIKE 'P'
INTERSECT 
Select idLots from FicheInventaire where idTechnicien in (
Select idTechnicien from Technicien where 
    nom LIKE 'Legault'
));


/* PLSQL */
/* 1)	Afficher le statut d’un lots passé en paramètre :*/

CREATE OR REPLACE PROCEDURE afficher_lots_tuple (l1 in Lots.idLots%TYPE) IS
Cursor c1 is 
Select * from Lots 
    where idLots = l1;
    
CURSOR c2 is 
SELECT * from FicheInventaire
where idLots = l1;

v1 Lots%ROWTYPE;
v2 FicheInventaire%ROWTYPE;

BEGIN
OPEN c1;
LOOP
   fetch c1 INTO v1;
   EXIT WHEN c1%NOTFOUND;
   DBMS_OUTPUT.PUT_line('id :' ||v1.idLots);
   OPEN c2;
    LOOP
        FETCH c2 INTO v2;
        EXIT WHEN c2%NOTFOUND;
        IF v2.Statuts = 'P' THEN 
         DBMS_OUTPUT.PUT_LINE('Statut : (' || v2.Statuts|| ') Présent en stock');
        ELSIF v2.Statuts = 'D' THEN 
        DBMS_OUTPUT.PUT_LINE('Statut : (' || v2.Statuts|| ') Distribué');
        ELSIF v2.Statuts = 'E' THEN 
        DBMS_OUTPUT.PUT_LINE('Statut : (' || v2.Statuts|| ') Périmé');
        ELSIF v2.Statuts = 'c' THEN 
        DBMS_OUTPUT.PUT_LINE('Statut : (' || v2.Statuts|| ') Non Conforme');
        END IF;
        END LOOP;
        ClOSE c2;
   END LOOP;
   CLOSE c1;
END;

CALL afficher_lots_tuple(1);



/*2 2)	Insertion d’une nom par défaut si le nom d’une marque n’est pas renseigné : */

CREATE OR REPLACE TRIGGER mon_trigger
BEFORE INSERT OR UPDATE ON MarqueProduit 
FOR EACH ROW
BEGIN 
IF :NEW.NomMarque is NULL THEN
    :NEW.NomMarque := 'Inconnue';
END IF ;
END;

INSERT INTO MarqueProduit(IdMarque, NomMarque) VALUES (6, NULL);

/*3)	Curseur paramétré qui fournit la quantité stockée d’un produit (en passant en paramètre l’id d’un produit)*/

CREATE OR REPLACE PROCEDURE getQuantite(P IN Produit.idProduit%TYPE) IS 
Cursor c1 is Select * from Produit where idProduit = P;
v1 Produit%ROWTYPE;
BEGIN
OPEN c1;
LOOP
FETCH c1 INTO v1;
EXIT WHEN c1%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('Quantite'|| getQuantite2(v1.idLots));
END LOOP;
Close c1;
END;

CREATE OR REPLACE FUNCTION getQuantite2(l IN Lots.idLots%TYPE) RETURN REAL IS 
CURSOR c2 is Select QuantiteLots from Lots where idLots = l;
v2 Lots.QuantiteLots%TYPE;
BEGIN
OPEN c2;
LOOP 
FETCH c2 INTO v2;
EXIT WHEN c2%NOTFOUND;
return v2;
END LOOP;
Close c2;
END;

CALL getQuantite(1);

/*4)	Affiche le contrôle d’un produit */

CREATE OR REPLACE PROCEDURE controle(l in Lots.idLots%Type) is  
CURSOR c1 is Select idCadresAdministratifs from Lots where idLots = l; 
v1 Lots.idCadresAdministratifs%TYPE; 
BEGIN 
OPEN c1; 
LOOP 
FETCH c1 INTO v1; 
 EXIT WHEN c1%NOTFOUND; 
    controleAffichage(v1); 
END LOOP; 
CLOSE c1; 
END;

CREATE OR REPLACE PROCEDURE controleAffichage(a1 in CadresAdministratifs.idCadresAdministratifs%TYPE) IS  
CURSOR c3 is SELECT * from Controles where idCadresAdministratifs = a1; 
v3 Controles%ROWTYPE; 
BEGIN 
OPEN c3; 
LOOP  
    FETCH c3 INTO v3; 
    EXIT WHEN c3%NOTFOUND; 
    DBMS_OUTPUT.PUT_LINE('Taux de Matière grasse : '||v3.TauxMatièreGrasse); 
    IF v3.TauxMatièreGrasse > 10 THEN  
     DBMS_OUTPUT.PUT_LINE('ATTENTION Taux de Matière grasse  non conforme'); 
    END IF; 
     DBMS_OUTPUT.PUT_LINE('Valeur Nutritionnelle'||v3.ValeurNutritionnelle); 
    IF v3.ValeurNutritionnelle <5 THEN  
     DBMS_OUTPUT.PUT_LINE('ATTENTION Valeur Nutritionnelle non conforme'); 
    END IF; 
 DBMS_OUTPUT.PUT_LINE('Quantite Calcium'||v3.QuantiteCalcium); 
    IF v3.QuantiteCalcium <5 THEN  
     DBMS_OUTPUT.PUT_LINE('ATTENTION QuantiteCalcium non conforme'); 
    END IF; 
END LOOP; 
END;

CALL controle(1);


/*5)	Afficher les informations d’un produit :*/
DECLARE
CURSOR c1 is SELECT * FROM Produit;

BEGIN 
FOR p in c1 LOOP
DBMS_OUTPUT.PUT_LINE('ID : '||p.idProduit);
DBMS_OUTPUT.PUT_LINE('Nom : '|| p.NomProduit);
DBMS_OUTPUT.PUT_LINE('Prix: '||p.PrixProduit);
END LOOP;
END;

