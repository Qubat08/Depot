/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef EFFECT_H
#define EFFECT_H

#include "ShaderTools.h"
#include "Geometry.h"
#include "FBO.h"
#include "glTexture.h"



/// ==============================================================
///    Effect
/// -------------
///
/// Classe générique représentant un effet, basé sur un shader.
///
/// Les shaders doivent être nommés de manière standard, à savoir vertex.txt, geometry.txt et fragment.txt. Leur nom correspond à la catégorie du shader.
/// Le chemin où sont situés les shaders doit être donné au constructeur.
/// Exploite le maillage :/3d/quad.obj
///
/// Cette classe possède les méthodes facilitant
///   - la communication avec les shader chargés sur le GPU et leur exploitation.
///   - l'attachement des textures (cf. attachTexture)
///
/// L'application de l'effet est réalisée via l'appel de la méthode apply.
///

class DLL_SPEC Effect
{
public:
    Effect( const QString &shaderPath = ":/glsl/quad/" );
    virtual ~Effect();

    virtual void apply();

    void attachTexture( int num, const char * name, glTexture * tex );
    void attachTexture( int num, const char * name, FBO * fbo );
    void attachTexture( int num, int location,      FBO * fbo );

protected :
    Geometry             * m_geometry = nullptr;

    QOpenGLShaderProgram * m_program;
    QOpenGLFunctions     * gl;
    GLuint                 attribPos;

};

#endif // EFFECT_H
