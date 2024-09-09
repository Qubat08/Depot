/* Copyright (C) 2019 Stéphanie Prévost - All Rights Reserved
 * This file is part of libQGLShaderViewer v2
 */

#ifndef QGLSHADERVIEWER_QGLCAMERA_H
#define QGLSHADERVIEWER_QGLCAMERA_H

#include "define.h"

#include "Entity.h"

#include <QVector3D>
#include <QVector2D>
#include <QMatrix4x4>
#include <QString>


/// ==============================================================
///    QGLCamera
/// -------------
///
/// Classe représentant une caméra.
/// Sa matrice de projection est défini avec les paramètres d'une matrice de perspective, à savoir afov, ratio, near, far.
///
/// Ses paramètres sont :
///  - w, h : Taille de la fenetre OpenGL (en pixel)
///
///  En cours de construction

/*
/// Initialisation par defaut des parametres stereo
///  - taille de l'écran :
///  - DIO : 0.062 m
///  - largeur de l'écran : 0.5 m
///  - focusDistance = Fov
*/

class DLL_SPEC QGLCamera : public Entity
{
public:    

    /// Déclaration des différents types de rendu
    typedef enum { MONO=0, STEREO_QUAD=1, ANAGLYPH_RC=2, SIDE_BY_SIDE_H=3, SIDE_BY_SIDE_V=4, SIDE_BY_SIDE_X=5, MULTIVIEW=6} RenderingMode;
    QString               getStrRenderingMode() const;

    /// Déclaration des différentes configurations possibles de disposition des capteurs d'acquisition de la camera
    typedef enum { PARALLEL=0, OFFAXIS=1, TOEIN=2, OFFAXISGV }     SensorDispositionMode;
    QString               getStrSensorDispositionMode() const;
    SensorDispositionMode getSensorDispositionMode   () const;
    void                  setSensorDispositionMode   (const QGLCamera::SensorDispositionMode &configMode);



    static const double deg2rad;        // Constante pour passer des angles exprimés en dégré en radian
    static const double rad2deg;        // Constante pour passer des angles exprimés en radian en degré


	QGLCamera();
    QGLCamera( int widthScreenInPixel, int heightScreenInPixel );
    virtual ~QGLCamera() override;
	
	
    /// --- FOV (vertical or horizontal) setting ---
    ///   Modifie la valeur de l'attribut	m_afov_v
    ///   Entraine la mise à jour de la distance de focalisation et de la matrice de projection
    void setFieldOfViewVerticalDeg  ( qreal fov );          // Setting du FOV
    void setFieldOfViewVerticalRad  ( qreal fov );
    void setFieldOfViewHorizontalRad( qreal hfov );

    // init the radius of the scene and implicitly the focus distance, flySpeed and projection matrix
    virtual void setSceneRadius         ( qreal radius       );
	void setSceneCenter         ( const QVector3D & center );
    void setNearAndFar          ( qreal znear, qreal zfar );
	void setScreenWidthAndHeight(int width, int height);
	
    void setIODistance         ( qreal distanceInMeter ) ;
	void setFocusDistance      ( qreal fd              );
	void setPhysicalScreenWidth( qreal widthInMeter    );
    void setIView( int i );
    void setLeftHanded(bool val);
    bool isLeftHanded() const;
 
	void setView( const QVector3D & pos, const QVector3D & up, const QVector3D & center );		// Use only in init function, modify scene and camera
    void setRenderingMode( RenderingMode mode );
    QGLCamera::RenderingMode getRenderingMode() const;

    void showEntireScene();
    void fitSphere      (const QVector3D & center, qreal radius);
    void fitBoundingBox (const QVector3D & min, const QVector3D & max);


/// getters of directions
    QVector3D  getUpDir()    const;
    QVector3D  getLeftDir      ()  const;                // Direction from the camera : left
    QVector3D  getRightDir     ()  const;                // Direction from the camera : right
    QVector3D  getFrontDir     ()  const;                // Direction from the camera : front
    QVector3D  getViewDirection()  const               { return getFrontDir(); }

/// Getters of matrix
    virtual QVector2D  getViewportRatio   () const;
	virtual QMatrix4x4 getViewMatrix      () const;
    virtual QMatrix4x4 getProjectionMatrix() const;
    virtual QMatrix4x4 getViewMatrix      ( int iView ) const;
    virtual QMatrix4x4 getProjectionMatrix( int iView ) const;
            QMatrix4x4 getSceneModelMatrix() const;

 
/// Getters of parameters
    virtual QVector3D  getPosition        () const;      // Position de la camera centrale
    qreal     getZNear      () const;
	qreal     getZFar       () const;
	qreal     getAspectRatio() const;
	qreal     getSceneRadius() const;
    QVector3D getSceneCenter() const;
    QVector3D getCenter     () const        {return getSceneCenter(); }
    qreal     getAVFovRad   () const;
	qreal     getAHFovRad   () const;  
	qreal     getFlySpeed   () const;
    QSize     getScreenSize () const;
	
    qreal     getIODistance             () const;
	qreal     getFocusDistance          () const;
    qreal     getPhysicalScreenWidth    () const;
    qreal     getPhysicalDistanceToScreen() const;
    int       getIView                  () const;
    int       getNbView() const;
    void      setNbView( int n );

    qreal     getZNearCoef      () const;
    qreal     getZFarCoef       () const;

/// ------ Others
/// Matrix
    void  setPerspectiveProjection(qreal fovInDeg, qreal ratio, qreal znear, qreal zfar);


    void  setZNear               ( qreal coef );
    void  setZClippingCoefficient( qreal coef );
    void  setViewMatrix           ( const QVector3D & pos,  const QVector3D & center,  const QVector3D & up);
    void  setSceneModelMatrix     (const QMatrix4x4 &sceneModelMatrix);
    void       setUpDirAndCenter       ( const QVector3D & up, const QVector3D & center  )
    { setView( Entity::getPosition(), up, center ); }
    // A zigouiller
    void       setRatio        (float widthInPixel, float heightInPixel );

    /// Méthodes de Manipulation
        virtual void setPosition      ( const QVector3D & pos )             override;
        virtual void translate        ( const QVector3D & trans )           override;
        virtual void rotateOnSelf     ( float angle, const QVector3D &rot ) override;
        virtual void rotateOnSelf     ( const QQuaternion & q  ) override;

        virtual void rotate           ( const QPoint & ref, const QPoint & p );
        virtual void travelling       (float speed );
        virtual void move             (float speed );



        virtual void print( bool withMatrix = false) const;



protected:
    /// --- C a m e r a   p a r a m e t e r s
    RenderingMode m_renderingMode = RenderingMode::MONO;
    SensorDispositionMode    m_sensorDispositionMode = OFFAXIS;

    QSize     m_screenSize;         // Taille de l'écran en pixel
    qreal     m_afov_v;             // angle du field of view vertical en degré
    QVector3D m_sceneCenter;        // Scene center (lookAt)
    qreal     m_sceneRadius;        // OpenGL units
	
private:	
    qreal     m_zNearCoef;          // indicator to znear coeff
    qreal     m_zClippingCoef;      // indicator to zfar coeff
    bool      m_constructorStep = true;

    void      computeFrustumParam( int iView, qreal & left,  qreal & right,  qreal & bottom,  qreal & top ) const;

protected:
    QMatrix4x4 m_proj;              // Matrice de projection
    QMatrix4x4 m_view;              // Matrice view
    QMatrix4x4 m_sceneModelMatrix;  // Matrice modele de la scene globale

	/// --- S t e r e o   p a r a m e t e r s
    qreal m_IOD;		     		// inter-ocular distance, in meters
    qreal m_focusDistance;	     	// in scene units
    qreal m_physicalScreenWidth;	// in meters
    bool  m_leftHanded = false;
    int   m_iView      = -1;        // index of rendering view
    int   m_nbView     = 1;         // nbre de vues

	/// Animation
    qreal m_flySpeed;               // Speed for camera's movement
	
	
	virtual void  updateViewMatrix();
    virtual void  updateProjectionMatrix();


    qreal     distanceToSceneCenter() const;

};

#endif
