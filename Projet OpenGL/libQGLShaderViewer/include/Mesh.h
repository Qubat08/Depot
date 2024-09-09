/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef MESH_H
#define MESH_H

#include "Entity.h"
#include "Geometry.h"
#include "Material.h"
#include "QGLCamera.h"


/// ==============================================================
///    Mesh
/// -------------
///
/// Classe représentant une entité de type maillage associé à un matériel (rendu) et à une géométrie.
///
/// Hérite de Entity
/// Un mesh a donc une position, une taille et peut être orienté suivant son centre.
///
/// Ses paramètres sont :
///  - g :  le pointeur d'une instance de Geometry
///  - m :  le pointeur d'une instance de Matéria
///  - visibility : indicateur pour la visibilité de l'objet
///
/// Attention -  il s'agit uniquement d'emprunt de ces instances, cette classe n'a pas la responsabilité de les détruire.
///

class DLL_SPEC  Mesh : public Entity
{
public:
  // Attention -  uniquement emprunt des objets, pas de responsabilité de destructions
    Mesh(Geometry *g, Material *m,  bool visibility = true);
    virtual ~Mesh() {}

    virtual void render(const QGLCamera *c, const QList<PointLight> & lights = QList<PointLight>(), Material *m = nullptr );

    void toggleVisibility();


    void       setGeometry( Geometry * g );
    Geometry * getGeometry() const;


    void       setMaterial(Material *material);
    Material * getMaterial() const;


/// ATTRIBUTS
protected:
    Geometry    * m_geometry;
    Material    * m_material;

public :
    bool         m_visibility = true;

};

#endif // MESH_H
