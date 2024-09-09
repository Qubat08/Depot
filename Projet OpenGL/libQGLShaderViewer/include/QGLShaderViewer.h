/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QList>
#include <QMap>
#include <QString>
#include <QFont>
#include <QColor>
#include <QElapsedTimer>
#include <QOpenGLFramebufferObject>
#include <QOpenGLExtraFunctions>
#include <QWidget>

#include "define.h"



#include "QGLCamera.h"

#include "Mesh.h"

#include "TextureMaterial.h"
#include "GridMaterial.h"
#include "FBO.h"
//#include "MouseManager.h"

class MouseManager;



/// ==============================================================
///    QGLShaderViewer
/// ---------------------
///
/// Classe représentant une fenêtre OpenGL,
/// Classe centrale du projet libQGLShaderViewer.
///
/// Hérite de QOpenGLWindow
/// Elle facilite le développement d'application de visu 3D, exploitant les shaders, les FBO de OpenGL 3.
/// L'activation d'une vision en relief quadBuffer est possible.
///

class DLL_SPEC QGLShaderViewer : public QOpenGLWindow, protected QOpenGLFunctions
{
   Q_OBJECT

public:
    QGLShaderViewer(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    virtual ~QGLShaderViewer() override;



// ----- P O O L S   A C T I O N S   ---
    void addEntityInScene     ( const QString & name, Mesh * entity );      // Add a entity in the scene
    void removeEntityFromScene( const QString & name );                     // Remove and delete the entity named "name"
    void addGeometry          ( const QString & name, Geometry * entity );  // Add a geometry in the pool
    void removeGeometry       ( const QString & name );                     // Remove and delete the geometry named "name" of the pool
    void addMaterial          (const QString & name, Material * material ); // Add a material in the pool
    void removeMaterial       ( const QString & name );                     // Remove and delete the material named "name" of the pool
    Mesh     *    getEntityInScene    (const QString & name ) const;
    QList<Mesh *> getListEntityInScene();
    Geometry *    getGeometry         (const QString & name ) const;
    Material *    getMaterial         (const QString & name ) const;


// ----- A N I M A T I O N  ---
    bool   isAnimated          () const;           // return true if the animation is started
    void   setAnimationPeriod  (int period);       // set the period of the animation loop
    void   startAnimation      ();                 // Enable  the animation loop
    void   stopAnimation       ();                 // Disable the animation loop
    qint64 getLastTimeAnimation    () const;
    qint64 getCurrentTimeAnimation () const;
    qint64 getEllapsedTimeAnimation() const;


protected:
// ----- W i d g e t   C o n t a i n e r
    QWidget * getThisWidget() const;
    bool      event(QEvent *event) override;

// ----- E v e n t  m a n a g e r
    virtual void mousePressEvent  (QMouseEvent * event)   override;
    virtual void mouseMoveEvent   (QMouseEvent * event)   override;
    virtual void mouseReleaseEvent(QMouseEvent * event)   override;
    virtual void mouseDoubleClickEvent (QMouseEvent * ev ) override;
    virtual void wheelEvent       (QWheelEvent * event)   override;
    virtual void keyPressEvent    (QKeyEvent   * event)   override;

// ----- A n i m a t i o n    and   d r a w i n g     L O O P
    virtual void  init           ();
    virtual void  resizeGL(int width, int height) override;
    virtual void  animate        ();
    virtual void  drawInformation();
    virtual void  drawScene();
            void  moveCamera( const QVector3D & dir, float speed );
            double getCameraSpeed() const;

    virtual void  createSceneEntities();

// ----- C a m e r a
    void        setCamera( QGLCamera * cam );       // Takes ownership of the cam instance to use as a camera
    QGLCamera * getCamera() const;                  // Return the camera of renderer
    void        setCameraRatio();                   // Set the ratio of the camera with the value in m of the display

// ----- G r i d   -   A x i s
    void setCoordinateSystemSize( float val );
    void drawAxis();
    void drawGrid();
    void drawFPS();

// ----- D r a w    t e x t
    void drawText(int x, int y, const QString& text, const QColor &color, const QFont& fnt=QFont());


// Gestion des evenements souris
    float m_precisionStep = 1;

// A virer et à integrer dans le resize de la camera
    float m_ratioStereo = 1.0;

protected slots:
    void setKeyBoardGrabbingEvent(int val);

private slots:
    void _animate();
    void release ();


private :
    //   W i d g e t   C o n t a i n e r
    QWidget * m_thisWidget;
    bool      m_withKeyboardGrabEnabled = false;
    void defaultConstructor(QWidget *parent, Qt::WindowFlags flags);

    QGLCamera     *  m_camera;
    MouseManager  *  m_mouseManager;
    double           m_moveCamera = 0;

// gestion fps
    QElapsedTimer    m_fpsTimer;
    uint             m_frameCount;
    qreal            m_fps;
    QString          m_fpsString;

    QTimer           m_animationTimer;
    QElapsedTimer    m_appliTimer;
    qint64           m_lastAnimTime = 0;
    qint64           m_currentTime  = 0;

// Gestion des dessins des axes et grille
    bool             m_drawingAxis  = true;
    bool             m_drawingGrid  = true;
    bool             m_drawingFps   = true;
    Mesh          *  m_axis         = nullptr;
    Mesh          *  m_grid         = nullptr;


// Gestion des pools d'éléments
    QMap < QString, Geometry * >       m_geometries;
    QMap < QString, Material * >       m_materials;
    QMap < QString, Mesh     * >       m_sceneEntities;


// méthodes privées pour aider à l'encapsulation de savoir faire
    void initializeGL()                  override;
    void paintGL()                       override;

    void _drawInformation();
    void fpsCompute();

    friend MouseManager;

};

extern long long      DLL_SPEC  getCurrentTimeMillis(); // retourne en ms le temps écoulé depuis le démarrage du système


#endif //WINDOW_H
