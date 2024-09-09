#include "Viewer.h"

#include "PhongMaterial.h"

#include <QInputDialog>


#include <QScreen>
#include <iostream>



#define DEFAULTREADINGDATAPORT    5000
#define DEFAULTREADINGSERVERPORT 50110


Viewer::Viewer(char choice, const QMap<QString, QString> &params)
    : TrackingViewer( choice, params)
{
    m_dataPort = DEFAULTREADINGDATAPORT;
    m_serverPort = DEFAULTREADINGSERVERPORT;
    m_serverHost = ("192.168.95.31");
    m_tracker = nullptr;
    m_coefAngleSpirale = 1;


    /// TODO - Instantiation du tracker répondant à la demande de l'utilisateur
    /// this->m_tracker = ???
    /// Si le tracker n'a pas pu est instantiée alors le message "m_tracker not allocated" est affiché et l'application est fermée
    ///




}


Viewer::~Viewer()
{
    /// --- TODO : Un peu de menage ....

}






void Viewer::doTraveling( const QVector3D & t )
{
    /// TODO - effectue le traveling demandé, de direction t.

    this->update();
}


void Viewer::pause(bool ok)
{
    /// TODO - Pause ou relance le tracking
    ///
    if ( m_tracker )
    {
        if (!ok)   this->m_tracker->stop();
        else       this->m_tracker->start();
    }

}

void Viewer::setTimerInterval(int i)
{
    if ( m_tracker )
    {
        this->m_tracker->stop();
        this->m_tracker->setReadFrequency(i);
        this->m_tracker->start();
    }
    Q_UNUSED( i );

}

// méthode spécifique à ArtDrawer, changement du port UDP pour la lecture des informations
void Viewer::changePort(int p)
{
    /// TODO - à compléter
    /// ...

}

void Viewer::createSceneEntities()
{
    qDebug() << " createSceneEntities .... ";
/// --- TODO : Ajout des géométries
/// ...
    //addGeometry(  "cube",    new Geometry(":/3d/cube.obj") );
    addGeometry("sphere", new Geometry(":/3d/sphere.obj"));

/// --- TODO : Ajout des Materials
/// ...

    addMaterial("phong", new PhongMaterial (QVector4D(.3,.3,.3,1.0), QVector4D(1, 1, 1, 1), 210000));

/// --- TODO : Création des mesh
/// ...

    Mesh* mesh = new Mesh(getGeometry("sphere"), getMaterial("phong"));
    m_targetAvatar = mesh;
    m_ball = new BallTarget(mesh, 1, QVector3D(200,0,0), Viewer::ballSize);
    m_targetAvatar->scale(Viewer::ballSize);
    m_targetAvatar->translate(QVector3D(200,0,0));

    createSpiralScene(mesh);

/// -------------- Ne pas modifier après ce code

// Ajout de la lumière de base
    m_lights.push_back( PointLight( getCamera()->getPosition() +
                                    getCamera()->getRightDir()*100.f  +
                                    getCamera()->getUpDir()*100.f, Qt::white ) );
    qDebug() << " fin createSceneEntities ";


}


// spirale d'archimède
// eq polaire : r = a. e^(b.teta)
// xM = r.cos θ et yM = r.sin θ.

void Viewer::createSpiralScene( Mesh * shape )
{
   /// TODO - Creation de la spirale de la scene via la lecture du fichier.
   ///        La spirale est constitué de cibles placées en spirale autour de l'axe Y.
   /// ...
    QFile file("./ballAnim.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){

        QTextStream in(&file);
        QString line = in.readLine();
        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList words = line.split(" ");

            m_targetAvatar = new Mesh(shape->getGeometry(), shape->getMaterial());
            m_targetAvatar->scale(words.at(4).toFloat());

            BallTarget *balle = new BallTarget(m_targetAvatar,
                                               words.at(0).toUInt(),
                                               words.at(1).toFloat(),
                                               words.at(2).toFloat(),
                                               words.at(3).toFloat(),
                                               words.at(4).toFloat()
                                               );


            balle->setColor(QColor(words.at(5).toInt(), words.at(6).toInt(), words.at(7).toInt()));
            conteneurTarget.push_back(balle);

        }
        file.close();
    }
}




void Viewer::spiralAnim( float elapsed )
{
    /// TODO - Animation de la spirale
    /// ...

    QMatrix4x4 posRot = QMatrix4x4();


    posRot.rotate(m_coefAngleSpirale, QVector3D(0.,1.,0.));
    if (elapsed > 150){
       foreach(BallTarget* ball, conteneurTarget){
            posRot.rotate(m_coefAngleSpirale, QVector3D((int)rand()%2,(int)rand()%2,(int)rand()%2));
            ball->setPosition(posRot * ball->getPosition());
        }
    }

}

void Viewer::moveCamera( const QVector3D & m_ratioTA2GL, const QVector3D & m_decalOrigin )
{
    /// TODO - Déplacement de la camera
    /// ...
}


void Viewer::moveHand( const QVector3D & m_ratioTA2GL, const QVector3D & m_decalOrigin )
{
    /// TODO - Déplacement de l'avatar de la main
    /// ...
}


void Viewer::cleanDeadTarget( long long currentTime )
{
    /// TODO - Elimination des cibles mortes
    /// ...

}


void Viewer::manageInteraction( long long currentTime )
{
/// TODO - Gestion des interactions
/// ...


}

void  Viewer::animate        ()
{
    QString msg;
	long long currentTime = getCurrentTimeMillis();


/// TODO - Animation de la spirale
/// ...

    //spiralAnim(getCurrentTimeAnimation());
    if (m_animeBool){
        ballAnim(getCurrentTimeAnimation());
    }
/// TODO - Interactions Tracker
/// ...


/// ------- Ne pas modifier
/// affichage du message dans l'interface
    if ( !msg.isEmpty() )       addMessage(msg);
	m_lastAnimTimeSystem = currentTime;
}

void Viewer::ballAnim(float elapsed)
{
    foreach (BallTarget* ball1, conteneurTarget) {
        QVector3D position1 = ball1->getPosition();

        // Vérifie si la nouvelle position après la translation reste à l'intérieur du cube
        if ((position1.x() + ball1->getSize() + ball1->direction.x() * ball1->vitesse < 1001 &&
             position1.x() - ball1->getSize() + ball1->direction.x() * ball1->vitesse > -1001) &&
            (position1.y() + ball1->getSize() + ball1->direction.y() * ball1->vitesse < 1001 &&
             position1.y() - ball1->getSize() + ball1->direction.y() * ball1->vitesse > -1001) &&
            (position1.z() + ball1->getSize() + ball1->direction.z() * ball1->vitesse < 1001 &&
             position1.z() - ball1->getSize() + ball1->direction.z() * ball1->vitesse > -1001)) {

            QMatrix4x4 posTrs; // Réinitialise la matrice à chaque itération

            posTrs.translate(ball1->direction.x() * ball1->vitesse,
                             ball1->direction.y() * ball1->vitesse,
                             ball1->direction.z() * ball1->vitesse);

            ball1->setPosition(posTrs * ball1->getPosition());

            foreach (BallTarget* ball2, conteneurTarget) {

                    if (ball1 != ball2) {
                        QVector3D position2 = ball2->getPosition();
                        float distance = position1.distanceToPoint(position2);
                        float combinedRadius = ball1->getSize() + ball2->getSize();

                        if (distance < combinedRadius) {
                            if (m_animeNumber == 1){
                                // Collision détectée
                                QVector3D normal = (position2 - position1).normalized();
                                ball1->direction -= 2 * QVector3D::dotProduct(ball1->direction, normal) * normal;
                                ball2->direction -= 2 * QVector3D::dotProduct(ball2->direction, normal) * normal;

                                float overlap = combinedRadius - distance + 5;
                                QVector3D correction = 0.5f * overlap * normal;
                                ball1->setPosition(ball1->getPosition() - correction);
                                ball2->setPosition(ball2->getPosition() + correction);

                                ball1->vitesse *= 0.9f;
                                ball2->vitesse *= 0.9f;
                        }
                            else if (m_animeNumber == 2){ // active l'echange de couleur
                                QVector3D normal = (position2 - position1).normalized();
                                ball1->direction -= 2 * QVector3D::dotProduct(ball1->direction, normal) * normal;
                                ball2->direction -= 2 * QVector3D::dotProduct(ball2->direction, normal) * normal;

                                float overlap = combinedRadius - distance + 5;
                                QVector3D correction = 0.5f * overlap * normal;
                                ball1->setPosition(ball1->getPosition() - correction);
                                ball2->setPosition(ball2->getPosition() + correction);

                               if (ball1->vitesse >= ball2->vitesse){
                                   ball2->setColor(ball1->getColor());
                               }
                               else {
                                   ball1->setColor(ball2->getColor());
                               }
                            }
                    }
                }
            }
        }

     else {
        if (position1.x() + ball1->getSize() + ball1->direction.x() * ball1->vitesse >= 1001 ||
            position1.x() - ball1->getSize() + ball1->direction.x() * ball1->vitesse <= -1001) {
            ball1->direction.setX(-ball1->direction.x());
    }

        if (position1.y() + ball1->getSize() + ball1->direction.y() * ball1->vitesse >= 1001 ||
            position1.y() - ball1->getSize() + ball1->direction.y() * ball1->vitesse <= -1001) {
            ball1->direction.setY(-ball1->direction.y());
        }

        if (position1.z() + ball1->getSize() + ball1->direction.z() * ball1->vitesse >= 1001 ||
            position1.z() - ball1->getSize()  + ball1->direction.z() * ball1->vitesse <= -1001) {
            ball1->direction.setZ(-ball1->direction.z());
            }
        }
    }
}

void  Viewer::drawInformation()
{
    glColor4f(1.,1.,0., 1.0);
    QFont font( "Arial", 10);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 1 );
    font.setStretch( 100 );

    // Affichage du texte 2D
    // ----------------------
    //   coord screen
    /// TODO - Ajouter l'affichage du texte 2D.
    /// ...
    int y = 0, dy = 30;


 //   drawText(10,  y+=dy, QString(" - exple texte en (%1)").arg( y ), Qt::white, font);
      drawText(10,  y+=dy, QString(" - nb target (%1)").arg( conteneurTarget.size()), Qt::white, font);
}



void  Viewer::drawScene()
{
    m_lights.front().setPosition( getCamera()->getPosition() + QVector3D(-30.f, 20.f, 1.0f));
 /// --- TODO - supprimer cette ligne et reprendre la version AS2MViewer et l'appliquer si besoin
        TrackingViewer::drawScene();
}

void Viewer::drawTargets()
{
    /// --- TODO - Dessin des cibles

    auto* cs = getStereoCamera();
    //m_ball->render(getCamera(), m_lights);
    foreach (BallTarget* ball, conteneurTarget){
        ball->render(cs, m_lights);
    }
}


float coefBall = 1.f;
void Viewer::drawHands()
{
    /// --- TODO - Dessin de l'avatar de la main
    /// ...

}


void Viewer::drawIemeViewInFBo( int iView, FBO * fbo )
{
    // A mettre en commentaire
    //TrackingViewer::drawIemeViewInFBo(iView, fbo);
//    auto * cs =  getStereoCamera();

/// --- TODO - Preparer votre environnement OpenGL, comme pour le TP précédent
/// ...

    auto * cs =  getStereoCamera();
    if ( cs != nullptr )
        cs->setIView( iView );

    if ( fbo )  fbo->bind();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // dessin des entity (grille + axe)
    foreach( Mesh * entity, getListEntityInScene() )
    {
        //m_lights.first().setPosition( entity->getPosition() - 1000*3. * getCamera()->getFrontDir());
        entity->render( getCamera(), m_lights );
    }


    drawTargets();


    /// --- TODO - Dessin de l'avatar de la main
    drawHands();

/// --- TODO - Terminer votre environnement OpenGL
/// ...
    if ( fbo )  fbo->release();


}




// Version Anaglyphe et stereo
void Viewer::drawStereo()
{
/// --- TODO - reprendre la version AS2MViewer et l'appliquer si besoin
    TrackingViewer::drawStereo();
}



// rendu monoscopic
void Viewer::drawMono()
{
 /// --- TODO - reprendre la version AS2MViewer et l'appliquer si besoin
   TrackingViewer::drawMono();
/*    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // dessin des entity (grille + axe)
    foreach( Mesh * entity, getListEntityInScene() )
    {
        //m_lights.first().setPosition( entity->getPosition() - 1000*3. * getCamera()->getFrontDir());
        entity->render( getCamera(), m_lights );
    }

*/
}


void Viewer::changeInteractionMode( InteractionMode m)
{
    m_interactionMode = m;
    // mettre à jour l'affichage OpenGL
    this->update();
}


void  Viewer::keyPressEvent     (QKeyEvent * event)
{
    switch( event->key() )
    {

    /// TODO - commande pour influencer l'angle de rotation de l'animation de la spirale
    /// ...

    case Qt::Key_Colon:
        if (m_animeBool){
            this->m_coefAngleSpirale += 0.1f;
        }
        break;
    case Qt::Key_Exclam :
        if (m_animeBool){
            this -> m_coefAngleSpirale -= 0.1f;
        }
         break;
    case Qt::Key_I :
        if (m_animeBool){
            m_coefAngleSpirale = 0;
            m_animeBool = false;
        }
        else{
            m_coefAngleSpirale = 1;
            m_animeBool = true;
        }
        qDebug() << "m_animeBool" << m_animeBool;
        break;
    case Qt::Key_M :
        m_animeNumber = int(rand()% 2);
        break;
    case Qt::Key_K:
        m_animeNumber = 1;
        break;
    case Qt::Key_L:
        m_animeNumber = 2;
        break;

    default: TrackingViewer::keyPressEvent(event);
    }

    m_renderingMode = static_cast<RenderingMode>( getCamera()->getRenderingMode() );
    qDebug() << " key : " <<  QKeySequence(event->key()).toString();

   // update();

}
