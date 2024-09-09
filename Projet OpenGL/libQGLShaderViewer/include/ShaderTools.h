/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef SHADERSET_H
#define SHADERSET_H


#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "define.h"


/// ==============================================================
///    ShaderTools
/// -------------------
///
/// Classe regroupant des méthodes utiles pour l'exploitation des shaders.
///

class DLL_SPEC ShaderTools
{
public:
    static void initShader(QOpenGLShaderProgram * program,
                            const QString & pathname );


    static void initShader( QOpenGLShaderProgram * program,
                            const QString & vertexName,  const QString & geometryName, const QString & fragmentName );
};

#endif // SHADERSET_H
