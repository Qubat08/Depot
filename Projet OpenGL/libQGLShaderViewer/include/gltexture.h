/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef GLTEXTURE_H
#define GLTEXTURE_H


#include <QOpenGLTexture>

#include "define.h"


/// ==============================================================
///    glTexture
/// -------------
///
/// Classe représentant une texture chargée sur GPU
///
/// Ses paramètres sont :
///  - filePath : nom du fichier contenant la texture
/// soit
///  - texture  : une instance de glTexture.
///


class DLL_SPEC glTexture
{
public:
    glTexture ( QString     filePath );
    glTexture ( glTexture * texture );
    ~glTexture();

    void bind ();


private:
   QOpenGLTexture * data;

};

#endif // GLTEXTURE_H
