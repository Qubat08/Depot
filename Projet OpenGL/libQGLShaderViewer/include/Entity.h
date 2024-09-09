/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef ENTITY_H
#define ENTITY_H


#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>

#include "define.h"



/// ==============================================================
///    ENTITY
/// -------------
///
/// Classe générique représentant une entité.
/// Une entité a une position, une taille et peut être orienté suivant son centre.
/// Par défaut, sa position est (0,0,0), sa taille 1 et il n'y a pas de rotation.
///

class DLL_SPEC Entity
{

public:
    Entity();
    virtual ~Entity() {}

/// Setters/Getters
    QVector3D    getPosition   () const;
    virtual void setPosition   ( const QVector3D & pos );

    void         setScale      ( const QVector3D & sc );
    void         setScale      ( float sc );

    void         setRotation   (float angle, const QVector3D &rot );
    void         setRotation   ( const QQuaternion & q );

    QMatrix4x4   getTrans      () const;
    QMatrix4x4   getScale      () const;
    QMatrix4x4   getRot        () const;

    QMatrix4x4   getModelMatrix() const;
    void         setModelMatrix( const QMatrix4x4 & m );



/// Méthodes de Manipulation
    virtual void translate   ( const QVector3D & trans );
    virtual void scale       ( const QVector3D & sc );
    virtual void scale       (float sc );
    virtual void rotateOnSelf( float angle, const QVector3D &rot );
    virtual void rotateOnSelf( const QQuaternion & q );

    virtual void print       () const;


    bool getFrozen() const;
    void setFrozen(bool frozen);

protected :
    /// Matrices de Transformation
    QMatrix4x4   m_trans;   // Matrice de translation
    QMatrix4x4   m_scale;   // Matrice de mise à l'échelle
    QMatrix4x4   m_rot;     // Matrice de rotation

    bool         m_frozen;  // permet de figer l'objet
};

#endif // ENTITY_H
