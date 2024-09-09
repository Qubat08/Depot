/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef TEXTUREMAT_H
#define TEXTUREMAT_H

#include "Material.h"
#include "glTexture.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>
#include <QString>

/// ==============================================================
///    TextureMaterial
/// -------------------
///
/// Classe représentant un matériel qui applique une texture sur l'objet.
/// hérite de Matérial
///
/// Le paramètre est :
///   - texturename : nom du fichier texture sur le disque.
/// soit
///   - texture : une instance de glTexture
///

class DLL_SPEC  TextureMaterial : public Material
{
public:
    TextureMaterial( const QString & texturename);
    TextureMaterial( glTexture * texture);

    ~TextureMaterial()  override;
   // void render(Mesh *mesh, QGLCamera *c, GLenum mode = GL_TRIANGLES) override;

    virtual void bindSpecific( const QGLCamera *c )  override;

private:
    glTexture            * m_texture;
    bool                   m_externTexture = false;
};

#endif
