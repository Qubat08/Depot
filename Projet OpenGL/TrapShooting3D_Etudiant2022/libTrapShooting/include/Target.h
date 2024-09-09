/* Copyright (C) 2019 Stéphanie Prévost - All Rights Reserved
 * This file is part of libQGLShaderViewer
 *
 *   You are not allowed to post, publish or disseminate this file
 *   or any other part of the code provided for this course
 */


#ifndef TARGET_H
#define TARGET_H


#include <QVector3D>
#include <QColor>

#include "Mesh.h"
#include "PhongMaterial.h"
#include "define.h"

/// ==============================================================
///    TARGET
/// -------------
/// Classe générique représentant une cible 3D positionnée avec
///   une forme géométrique et un matérial contenu dans un mesh
///

class DLL_SPEC Target
{
public :
    /// Interaction
    typedef enum { FREE = 0, TOUCHED, GRABBED } TypeContact;


protected:
    unsigned int    m_id;                   // Identifiant de la cible
    Mesh          * m_shape    = nullptr;   // forme de la cible
    PhongMaterial * m_material = nullptr;   // rendu de la cible

    QVector3D       m_position;             // Position de la cible
    QColor          m_color;                // Couleur de la cible
    float           m_size;                 // Taille de la cible
    TypeContact     m_contactState;         // Etat de la cible pour le type de contact


    /// TODO - Interaction
    /// ...
#ifdef with_TODO
    long long    m_countDown;
#endif


public:
        /// TODO - Interaction
        /// ...
#ifdef with_TODO
    static long long explosionDuration;
#endif

    Target( Mesh * shape, unsigned int id, const QVector3D & pt, float size );

    virtual ~Target();

/// --- S E T T E R S
    void         setShape      ( Mesh * shape );
    void         setPosition   ( const QVector3D & p );
    void         setColor      ( const QColor & c );
    void         setSize       ( float s );

/// --- G E T T E R S
    QVector3D    getPosition   () const;
    float        getSize       () const;
    QColor       getColor      () const;


/// --- Interactions
    void                 setContactState ( TypeContact tpC );
    Target::TypeContact  getStateContact() const;

    virtual void  render   (QGLCamera * cam , const QList<PointLight> &lights);
    virtual bool  intersect( const QVector3D & pt) const = 0;

    /// TODO - Interaction
    /// ...
    virtual void      setCountDown   ( float tic ) ;
    virtual float     getAge         ( long long currentTime ) const;
    virtual bool      isDead         ( long long currentTime ) const;

/// Non
    static QColor getRandColor();
};






#endif // TARGET_H
