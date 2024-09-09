/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef GRIDMATERIAL_H
#define GRIDMATERIAL_H


//#include "glm/glm.hpp"
#include "Material.h"
#include "glTexture.h"

#include <QColor>


/// ==============================================================
///    GridMaterial
/// -------------------
///
/// Classe représentant un matériel qui dessinera une grille sur les faces.
/// hérite de Matérial
///
/// Les paramètres sont :
///   - nbDivision : nombre de divisions dessinés
///   - color      : couleur des traits dessinés
///   - widthLine  : largeur des lignes
///

class DLL_SPEC GridMaterial : public Material
{
public:
    GridMaterial(int nbDivision = 10, const QColor &color = Qt::white, float widthLine = 0.05f );
    ~GridMaterial()  override;

    void   bindSpecific(const QGLCamera *c) override;

    QColor getColorLine () const;
    void   setColorLine (const QColor &colorLine);

    int    getNbDivision() const;
    void   setNbDivision(int nbDivision);

    float  getWidthLine () const;
    void   setWidthLine (float widthLine);

private:
    glTexture            * m_texture = nullptr;
    bool                   m_externTexture = false;

    QColor                 m_colorLine;
    int                    m_nbDivision;
    float                  m_widthLine;

};

#endif // GRIDMATERIAL_H
