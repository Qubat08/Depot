/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef MATERIAL_H
#define MATERIAL_H


#include "QGLCamera.h"
#include "define.h"
#include "PointLight.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>
#include <QString>
#include <QList>


class Mesh;

/// ==============================================================
///    Material
/// -------------
///
/// Classe générique et virtuelle représentant un matériel,
/// qui charge des shaders.
///
///


/// Classe Générique qui charge des shaders
class DLL_SPEC Material
{
public:
    Material();
    virtual ~Material();


    virtual void render(const Mesh *m, const QGLCamera *c, const QList<PointLight> & lights = QList<PointLight>() );

    void initShader( const QString & pathname );
    void initShader( const QString & vertexName,  const QString & geometryName, const QString & fragmentName );

    void bindMatrix( const QGLCamera *c, const QMatrix4x4 & model );
    void bindMatrix( const QMatrix4x4 & model, const QMatrix4x4 & view, const QMatrix4x4 & proj );
    virtual void bindSpecific(const QGLCamera *c)  = 0;

protected :
    QString                m_name;
    QOpenGLShaderProgram * m_program = nullptr;
    QOpenGLFunctions      *gl = nullptr;
    GLuint                 attribPos, attribNorm, attribUvs, attribTangents, attribColor;

};

#endif // MATERIAL_H
