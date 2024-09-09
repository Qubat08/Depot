#ifndef TRACKER_H
#define TRACKER_H

#include <QObject>

#include <QVector3D>
#include <QQuaternion>
#include <QTimer>

#include "define.h"

/// ==============================================================
///    InteractionMode
/// ------------------
/// Liste des interactions qui pourront être prises en compte
/// La méthode   strInteractionMode  permet de connaitre la version textuelle de l'interaction
///

typedef enum { GRAB, SHOT, PUSH, LASER } InteractionMode;
const QStringList strInteractionMode = (QStringList() << "GRAB" << "SHOT" << "PUSH" << "LASER");





/// ==============================================================
///    HAND
/// ------------------
///   Classe représentant la description (non géométrique) d'une main
///
///   Les attributs sont publiques, donc le dévelopeur devra faire attention lors de leur utlisation.
///   L'enum  Pose  représente l'état reconnu de la pose de la main, par défaut l'état est mis à OPEN
///   Le tableau  strPose  permet d'obtenir facilement la traduction en chaine de caractère de la pose.
///

class DLL_SPEC Hand
{
public :
    typedef enum  { UNKNOW =0, OPEN, CLOSE } Pose;
    const QStringList strPose = (QStringList() << "UNKNOW" << "OPEN" << "CLOSE");

    QVector3D    position;          // Position 3D de la main
    QQuaternion  orientation;       // Orientation de la main
    Pose         pose;              // Pose de la main

    Hand () : pose(Hand::OPEN) {}
    Hand ( const QVector3D & pos, const QQuaternion & orient ) : position(pos), orientation(orient), pose(UNKNOW) {}
    ~Hand(){}

    Hand & operator = ( const Hand & h )
    {
        this->position = h.position;
        this->orientation = h.orientation;
        this->pose = h.pose;
        return * this;
    }

    // Retourne la pose en texte
    QString getStringPose() const   { return strPose[pose]; }
};




/// ==============================================================
///    HEAD
/// ------------------
///   Classe représentant la description (non géométrique) d'une tête
///
///   Les attributs sont publiques, donc le dévelopeur devra faire attention lors de leur utlisation.
///

class DLL_SPEC Head
{
public :
    QVector3D    position;          // Position 3D
    QQuaternion  orientation;       // Orientation

    Head () {}
    Head ( const QVector3D & pos, const QQuaternion & orient ) : position(pos), orientation(orient) {}
    ~Head(){}

};



/// ==============================================================
///    TRACKER
/// ------------------
///   Classe générique représentant un tracker/detecteur d'élément et encapsulant les différents éléments communs
///
///   Elle mémorise les données communes aux différents tracker qui pourront être implémentés.
///   et elle gère le timer, dont le déclenchement appele la lecture des données sur le flux entrant.
///   Ce flux varie suivant les trackers.
///   Elle possède les méthodes pour rendre standard les messages qui seront envoyés sur le log de l'application.
///

class DLL_SPEC Tracker : public QObject
{
    Q_OBJECT
protected :
    Head      m_head;               // Head détectée
    Hand      m_primaryHand;        // Main principale
    QString   m_log;                // Log = etat du processus
    QTimer    m_timer;              // timer pour lancer la recherche

public:
    Tracker(QObject * parent );
    virtual ~Tracker();

 /// Action sur le tracker
    virtual void start();
    virtual void stop ();
    virtual void pause(bool val);

    virtual bool isStarted() const;

    void    setReadFrequency(int val );

 /// Accesseurs
    const Head    & getHead       () const;
    const Hand    & getPrimaryHand() const;
    const QString & getLog        () const;

 /// Constructeurs des messages à émettre sur le log
    QString msgCamPosition           () const;
    QString msgHandPosition          () const;
    QString msgHandPose              () const;
    QString msgChangeInteractionMode ( InteractionMode m) const;

signals:
    void changeInteractionMode( InteractionMode   );
    void doTraveling          ( const QVector3D & );


public slots:
      virtual  void  readData () =0;
};

#endif // TRACKER_H
