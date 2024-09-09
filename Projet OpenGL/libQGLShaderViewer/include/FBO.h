/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef QGL_SHADERVIEWER_FBO_H
#define QGL_SHADERVIEWER_FBO_H

#include <QSize>
#include <QOpenGLFramebufferObject>
#include <QOpenGLExtraFunctions>

#include <QApplication>

#include "define.h"



/// ==============================================================
///    FBO
/// -------------
///
/// Classe représentant un fragment buffer object.
/// Un FBO est utilisé comme canneva pour dessiner lors d'un rendu indirect.
/// Il est conseillé de construire les FBO dans la méthode init()
/// Lorque la taille de la fenêtre OpenGL est changée, la méthode resize(...) doit être aussi appelée,
/// afin que les deux aient la même taille.
///
/// Ses paramètres sont :
///  - w, h : taille de la fenêtre OpenGL en pixel
///  - type : type des informations stockées.
///  - depth : indicateur pour signaler l'utilisateur des profondeurs
///

class DLL_SPEC FBO
{
public:
    static QSize               maxScreenSize;

    FBO(int w, int h, GLuint type = GL_RGBA8, bool depth =false);

    ~FBO();
    QSize getSize();

    void bind   ( bool inScreen = false, bool withDepthTest = true );
    void create ( int w,int h);
    void release();

    void resize ( int h,int w );

    // extra function,  to use if the order of fbo texture are not the same to the next pass
    // void bindTexture( unsigned int numTex,  int numFboTex  );

    // bind the textures in the same order of the generation in fbo
    void bindTextures();

    GLuint getGetexID() const;
    GLuint getTextures(int n);


//    GLuint GetexID;
//    GLuint fboTexture;

protected:
    static unsigned int m_nbMaxTex;
    QSize        m_size;                // Taille de la texture de rendu
    bool         m_withDepthTest;       // Mise en place du test de profondeur (utiliser dans bind)
    bool         m_screenRendered;      // Indicateur que le rendu est directement l'écran et non 1 FBO
    GLboolean    m_depthTestState;      // etat de la variable avant la mise ne place du FBO

    void create();


private:
    QOpenGLFunctions                * gl;
    QOpenGLExtraFunctions           * gl2;

    QOpenGLFramebufferObject        * m_qtFbo;
    QOpenGLFramebufferObjectFormat    m_fboFormat;
    GLuint                            m_fbo;
    GLuint                            m_texture;
    bool                              m_isDepth;
};


#endif // QGL_SHADERVIEWER_FBO_H
