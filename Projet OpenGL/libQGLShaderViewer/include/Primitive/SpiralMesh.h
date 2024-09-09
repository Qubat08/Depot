/* Copyright (C) 2019 Stéphanie Prévost
 * All Rights Reserved
 * This file is part of libQGLShaderViewer
 */



#ifndef SPIRALMESH_H
#define SPIRALMESH_H

#include "Mesh.h"
#include "ColorMaterial.h"
#include "define.h"

class Material;
class Geometry;

/// ==============================================================
///    SpiralGeometry
/// -------------------
///
/// Classe représentant la description geométrique d'une spirale par
/// un maillage triangulaire (pas de texture).
///
///

class DLL_SPEC  SpiralGeometry : public Geometry
{
public :
    SpiralGeometry();

private :
    void create();
};





/// ==============================================================
///    SpiralMesh
/// ---------------
///
/// Classe représentant une spirale de type maillage associé à un matériel (rendu) et à une géométrie.
/// WARNING     En cours de réalisation ne pas utiliser.
///
///

class SpiralMesh : public Mesh
{
public:
    SpiralMesh();

private :
    SpiralGeometry * m_geom;
    ColorMaterial    m_colormaterial;

    void createGeometry();
};

#endif // SPIRALMESH_H
