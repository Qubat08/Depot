CREATE TABLE OGM(
   idOGM INT NOT NULL,
   NomOGM VARCHAR(10),
   PRIMARY KEY(idOGM)
);

CREATE TABLE Colorants(
   idColorants INT NOT NULL,
   NomColorant VARCHAR(20),
   PRIMARY KEY(idColorants)
);

CREATE TABLE MarqueProduit(
   idMarque INT NOT NULL,
   NomMarque VARCHAR(10),
   PRIMARY KEY(idMarque)
);

CREATE TABLE FicheDescriptive(
   idFicheDescriptive INT NOT NULL,
   PoidsProduit DECIMAL(15,2),
   VolumeProduit DECIMAL(15,2),
   DescriptionProduit VARCHAR(100),
   PRIMARY KEY(idFicheDescriptive)
);

CREATE TABLE Categorie(
   idCategorie INT NOT NULL,
   NomCategorie VARCHAR(20),
   PRIMARY KEY(idCategorie)
);

CREATE TABLE Lots(
   idLots INT NOT NULL,
   QuantiteLots DECIMAL(15,2),
   DateEntrée DATE,
   DateSortie DATE,
   DateConsommation DATE,
   Origine VARCHAR(50),
   idEmballages INT,
   idComposition INT,
   idFicheDescriptive INT,
   idCadresAdministratifs INT,

   PRIMARY KEY(idLots)
);

CREATE TABLE Emballages(
   idEmballages INT NOT NULL,
   NomEmballages VARCHAR(50),
   PRIMARY KEY(idEmballages)
);

CREATE TABLE Composition(
   idComposition INT NOT NULL,
   DescriptionComposition VARCHAR(100),
   PRIMARY KEY(idComposition)
);

CREATE TABLE CadresAdministratifs(
   idCadresAdministratifs INT NOT NULL,
   dureeMax INT,
   TempératureMin DECIMAL(15,2),
   TempératureMax DECIMAL(15,2),
   PRIMARY KEY(idCadresAdministratifs)
);

CREATE TABLE Controles(
   idContoles INT,
   TauxMatièreGrasse DECIMAL(15,2),
   ValeurNutritionnelle DECIMAL(15,2),
   QuantiteCalcium DECIMAL(15,2),
   idOGM INT,
   idColorants INT,
   idCadresAdministratifs INT,
   PRIMARY KEY(idContoles)
);

CREATE TABLE Technicien(
   idTechnicien INT NOT NULL,
   Nom VARCHAR(50),
   Prenom VARCHAR(50),
   PRIMARY KEY(idTechnicien)
);

CREATE TABLE FicheInventaire(
   idInventaire INT NOT NULL,
   NumeroAn INT ,
   NumeroSemaine INT ,
   Commentaire VARCHAR(100),
   Statuts VARCHAR(10),
   idLots INT,
   idCadresAdministratifs INT,
   idTechnicien INT,
   PRIMARY KEY(idInventaire)
);



CREATE TABLE Produit(
   idProduit INT NOT NULL,
   NomProduit VARCHAR(50),
   PrixProduit DECIMAL(15,2),
   idTechnicien INT,
   idCategorie INT,
   idMarque INT,
   idColorants INT,
   idOGM INT,
   idLots INT,

   PRIMARY KEY(idProduit)
);




ALTER TABLE Produit ADD
    CONSTRAINT Produitfk1
        FOREIGN KEY (idTechnicien) REFERENCES
            Technicien(idTechnicien);
            
ALTER TABLE Produit ADD
    CONSTRAINT Produitfk2
        FOREIGN KEY (idCategorie) REFERENCES
            Categorie(idCategorie);

ALTER TABLE Produit ADD
    CONSTRAINT Produitfk3
        FOREIGN KEY (idMarque) REFERENCES
            MarqueProduit(idMarque);
        
ALTER TABLE Produit ADD
    CONSTRAINT Produitfk4
        FOREIGN KEY (idColorants) REFERENCES
            Colorants(idColorants);
        
ALTER TABLE Produit ADD
    CONSTRAINT Produitfk5
        FOREIGN KEY (idOGM) REFERENCES
            OGM(idOGM);

ALTER TABLE Produit ADD
    CONSTRAINT Produitfk6
        FOREIGN KEY (idLots) REFERENCES
            Lots(idLots);
 

ALTER TABLE Lots ADD
    CONSTRAINT Lotsfk1
        FOREIGN KEY (idEmballages) REFERENCES
        Emballages(idEmballages);

ALTER TABLE Lots ADD
    CONSTRAINT Lotsfk2
        FOREIGN KEY (idComposition) REFERENCES
        Composition(idComposition);

ALTER TABLE Lots ADD
    CONSTRAINT Lotsfk3
        FOREIGN KEY (idFicheDescriptive) REFERENCES
            FicheDescriptive(idFicheDescriptive);

ALTER TABLE Lots ADD 
    CONSTRAINT Lotsfk4
        FOREIGN KEY (idCadresAdministratifs) REFERENCES
            CadresAdministratifs(idCadresAdministratifs);

ALTER TABLE Controles ADD
    CONSTRAINT Controlesfk1
        FOREIGN KEY (idOGM) REFERENCES
        OGM(idOGM);

ALTER TABLE Controles ADD
    CONSTRAINT Controlesfk2
        FOREIGN KEY (idColorants) REFERENCES
        Colorants(idColorants);

ALTER TABLE Controles ADD
    CONSTRAINT Controlesfk3
        FOREIGN KEY (idCadresAdministratifs) REFERENCES
        CadresAdministratifs(idCadresAdministratifs);

ALTER TABLE FicheInventaire ADD
    CONSTRAINT FicheInventairefk1
        FOREIGN KEY (idLots) REFERENCES
        Lots(idLots);

ALTER TABLE FicheInventaire ADD
    CONSTRAINT FicheInventairefk2
        FOREIGN KEY (idCadresAdministratifs) REFERENCES
        CadresAdministratifs(idCadresAdministratifs);

ALTER TABLE FicheInventaire ADD 
    CONSTRAINT FicheDescriptivefk3
        FOREIGN KEY (idTechnicien) REFERENCES
        Technicien(idTechnicien);
        
INSERT INTO CadresAdministratifs VALUES (1, 15, -15, 0);
INSERT INTO CadresAdministratifs VALUES (2, 15, 0, 5);
INSERT INTO CadresAdministratifs VALUES (3, 15, 10, 20);

INSERT INTO Categorie VALUES (1,'Produitslaitiers');
INSERT INTO Categorie VALUES (2,'fruits');
INSERT INTO Categorie VALUES (3,'boissons');
INSERT INTO Categorie VALUES (4,'viande');
INSERT INTO Categorie VALUES (5,'surgelés');

INSERT INTO MarqueProduit VALUES (1,'Lactalos');
INSERT INTO MarqueProduit VALUES(2,'Charal');
INSERT INTO MarqueProduit VALUES(3,'Picard');
INSERT INTO MarqueProduit VALUES(4,'Coca');
INSERT INTO MarqueProduit VALUES(5,'BioFruits');

INSERT INTO OGM VALUES (1,'SansOGM');
INSERT INTO OGM VALUES (2,'OGM1');
INSERT INTO OGM VALUES(3,'OGM2');

INSERT INTO Colorants VALUES (1,'SansColorant');
INSERT INTO Colorants VALUES (2,'Colorant1');
INSERT INTO Colorants VALUES (3,'Colorant2');

INSERT INTO FicheDescriptive VALUES (1,9.5,3,'FicheDescriptive1');
INSERT INTO FicheDescriptive VALUES (2,20,5,'FicheDescriptive2');
INSERT INTO FicheDescriptive VALUES (3,5,1,'FicheDescriptive2');

INSERT INTO Emballages VALUES (1,'Aucun');
INSERT INTO Emballages VALUES (2,'Carton ');
INSERT INTO Emballages VALUES (3,'Plastique');
INSERT INTO Emballages VALUES (4,'Verre');

INSERT INTO Composition VALUES (1,'Composition1');
INSERT INTO Composition VALUES (2,'Composition2');
INSERT INTO Composition VALUES (3,'Composition1');


INSERT INTO Lots VALUES (1,2.6,TO_DATE('2022-12-3','YYYY-MM-DD'),TO_DATE('2022-12-15','YYYY-MM-DD'),TO_DATE('2022-12-25','YYYY-MM-DD'), 'France', '1','1','1','1');
INSERT INTO Lots VALUES (2,5.2,TO_DATE('2022-11-29','YYYY-MM-DD'),TO_DATE('2022-12-2','YYYY-MM-DD'),TO_DATE('2022-12-15','YYYY-MM-DD'), 'Belgique', '2','2','2','2');
INSERT INTO Lots VALUES (3,4,TO_DATE('2022-12-29','YYYY-MM-DD'),TO_DATE('2022-12-29','YYYY-MM-DD'),TO_DATE('2024-01-05','YYYY-MM-DD'), 'Italie', '3','3','3','3');

INSERT INTO Controles VALUES (1,23.5,15.2,1.0,1,1,1);
INSERT INTO Controles VALUES (2,4,5,6,2,2,2);
INSERT INTO Controles VALUES (3,6,7,8,3,3,3);

INSERT INTO Technicien VALUES (1,'Legault','Franck');
INSERT INTO Technicien VALUES (2,'Lapierre','Lyle');
INSERT INTO Technicien VALUES (3,'Marceau','Delphine');

INSERT INTO FicheInventaire VALUES (1,2022,46,'ok','P',1,1,1);
INSERT INTO FicheInventaire VALUES (2,2022,45,'non conforme','C',2,2,2);
INSERT INTO FicheInventaire VALUES (3,2022,45,'périmé','E',3,3,3);


INSERT INTO Produit VALUES (1,'Briquedelait', 2.6,1,1,1,1,2,3);
INSERT INTO Produit VALUES (2,'Steak', 7.80,3,4,2,2,1,2);
INSERT INTO Produit VALUES (3,'Pate',6.9,2,5,3,3,2,1);