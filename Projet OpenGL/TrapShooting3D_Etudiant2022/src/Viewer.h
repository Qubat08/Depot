#ifndef VIEWER_H
#define VIEWER_H

#include "TrackingViewer.h"

#include <QTimer>


#include "BallTarget.h"




class Viewer : public TrackingViewer
{
    Q_OBJECT

public:
    Viewer(char choice,
           const QMap<QString, QString> & params );
    virtual ~Viewer() override;

    virtual void  animate        () override;
    virtual void  drawInformation() override;
    virtual void  drawScene()       override;
    virtual void  keyPressEvent  (QKeyEvent * event)   override;

    virtual void  createSceneEntities() override;



public slots:
    // Lien avec TrackingInterface
        virtual void doTraveling( const QVector3D & t ) override;
        virtual void pause(bool)                        override;
        virtual void setTimerInterval(int)              override;
        virtual void changePort( int p )                override;
        virtual void changeInteractionMode( InteractionMode m) override;

protected:
    // Gestion des modes de rendu
        virtual void drawMono  () override;
        virtual void drawStereo() override;
        virtual void drawIemeViewInFBo( int iView, FBO * fbo ) override;
    virtual void drawTargets() override;
    virtual void drawHands();

    // TODO TP 2
        virtual void createSpiralScene( Mesh * shape ) override;
        virtual void spiralAnim       ( float elapsed ) override;

    // Gestion des animations
        virtual void moveCamera( const QVector3D &m_ratioTA2GL, const QVector3D & m_decalOrigin ) override;
        virtual void moveHand  ( const QVector3D & m_ratioTA2GL, const QVector3D & m_decalOrigin ) override;
        virtual void cleanDeadTarget( long long currentTime ) override;
        virtual void manageInteraction(long long currentTime) override;


        virtual void ballAnim(float elapsed);
    /// ========== Attributs ==========
    /// -------------------------------
    /// tracking
         Tracker *       m_tracker = nullptr;


    /// --- TODO : Ajouter des attributs
    /// ...
    ///


    QList<BallTarget*> conteneurTarget;
    Mesh* m_targetAvatar;
    BallTarget* m_ball;
    float m_coefAngleSpirale;
    bool m_animeBool =false;
    int m_animeNumber = 1;
};

#endif // VIEWER_H
