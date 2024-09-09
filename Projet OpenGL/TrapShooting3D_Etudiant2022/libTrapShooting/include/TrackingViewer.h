#ifndef TRACKINGVIEWER_H
#define TRACKINGVIEWER_H

#include "define.h"
#include "QGLShaderViewer.h"

#include <QTimer>

class StereoInterface;
class StereoComposer;
class TrackingInterface;


#include "Target.h"
#include "Tracking/Tracker.h"

#include "Primitive/AxisMesh.h"

/**
/** * @brief The TrackingViewer class
/** */
class DLL_SPEC TrackingViewer : public QGLShaderViewer
{
    Q_OBJECT

public:
    TrackingViewer(char choice,
           const QMap<QString, QString> & params );
    ~TrackingViewer() override;

    virtual void  resizeGL(int width, int height) override;
    virtual void  init           () override;
    virtual void  animate        () override;
    virtual void  drawInformation() override;
    virtual void  drawScene()       override;
    virtual void  keyPressEvent  (QKeyEvent * event)   override;

    virtual void  createSceneEntities() override;

    // TP 1
    QGLCamera * getStereoCamera() const;

public slots:
    // Lien interface  stereo
        void  setStereo ( int val );
        void  setSwap   ( int val );
        void  setIOD    ( double valInCm );
        void  setDistance2Screen( double valInM );
        void  setFocusDistance  ( double zw     );
        void  setNbView (int nbV );
        void  setZDistCoef      ( double val    );
        void  decalView( int d );


    // Lien avec TrackingInterface
        void changePort        ();
        void changeTrackCamera (bool b);
        void changeTrackingArea();

        virtual void pause           (bool);
        virtual void doTraveling     ( const QVector3D & t );
        virtual void setTimerInterval(int);
        virtual void changeInteractionMode( InteractionMode m);
        virtual void changePort      (int p);

signals:
    void  addMessage(const QString&);

protected :
// Declaration des modes de rendus
    typedef enum { MONO=0, STEREO_QUAD=1, ANAGLYPH_RC=2,
                   SIDE_BY_SIDE_H=3, SIDE_BY_SIDE_V=4} RenderingMode;
    RenderingMode    m_renderingMode = MONO;
    QString getStrConfigRenderingMode() const;


// Gestion des modes de rendu
        virtual void drawMono  ();
        virtual void drawStereo();
        virtual void drawIemeViewInFBo( int iView, FBO * fbo );
        virtual void drawTargets();
        virtual void drawHand();

// Gestion des animations
        virtual void moveCamera( const QVector3D &m_ratioTA2GL, const QVector3D & m_decalOrigin );
        virtual void moveHand  ( const QVector3D & m_ratioTA2GL, const QVector3D & m_decalOrigin );
        virtual void cleanDeadTarget( long long currentTime );
        virtual void manageInteraction(long long currentTime);




/// ========== Attributs ==========
/// -------------------------------
// ---  ART
     ushort         m_dataPort;
     ushort         m_serverPort;
     std::string    m_serverHost;


/// Stereo - Quad buffer - Anaglyph
     bool                 m_swapQuadBuffer   = false;
     QVector< FBO * >     m_fbos;                           // Liste des fbos
     StereoInterface    * m_stereoInterface   = nullptr;    // Lien vers l'interface stereo
     TrackingInterface  * m_trackingInterface = nullptr;    // Lien vers l'interface tracking
     StereoComposer     * m_stereoComposer    = nullptr;

     void setTrackingInterface( QGLCamera *cam, bool initWithCam);
     void setTrackingArea     ( const QVector3D & a, const QVector3D &up );

     void setStereoInterface  (  QGLCamera * cam, bool modeReadCam );

     void createFBO           ();

/// Scene 3D spirale
    QList<PointLight> m_lights;
    static float ballSize;


    virtual void createSpiralScene   ( Mesh * shape );
    virtual void spiralAnim          ( float elapsed );
    void createSpiralSceneNew( Mesh * shape );


/// tracking ART
     InteractionMode m_interactionMode;

     // attributs de gestion du tracking
     bool                  m_trackCamera;
     QVector3D             m_trackingArea;
     QVector3D             m_decalOrigin;


     // attributs relatifs au dessin
     Hand                  m_primaryHand;         // Position du crayon
     InteractionMode       m_mode;

     long long             m_startTimeSystem;          // temps système du début du programme
     long long             m_lastAnimTimeSystem;


     /// --- TODO : Ajouter des attributs
     /// ...

};

#endif // VIEWER_H
