/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Entity.h"
#include <QColor>

/// ==============================================================
///   PointLight
/// -------------
///
/// Classe représentant une lumière ponctuelle
/// Hérite de Entity
///
/// Ses paramètres sont :
///   - pos   : position
///   - color : couleur de la lumière
///

class DLL_SPEC   PointLight : public Entity
{
public:
    PointLight();
    PointLight( const QVector3D & pos, const QColor    & color );
    PointLight( const QVector3D & pos, const QVector4D & color );
    PointLight( const QColor    & color );
    PointLight( const QVector4D & color );

    QVector4D getColor() const;
    void      setColor(const QVector4D & color);
    void      setColor(const QColor    & color);

protected :
    QVector4D  m_color;     // Couleur de la lumière
};

#endif // POINTLIGHT_H
