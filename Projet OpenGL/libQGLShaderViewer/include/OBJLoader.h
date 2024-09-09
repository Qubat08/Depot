/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>
#include "define.h"

class Geometry;


/// ==============================================================
///   OBJLoader
/// -------------
///
/// Classe capable de charger un maillage de type obj
///

class DLL_SPEC  OBJLoader
{
	public:
        OBJLoader ();
        ~OBJLoader();

        static bool loadModel(const std::string & name,Geometry *model);

        static void setupForTextureCoordinates( Geometry * model );
        static void computeNormals            ( Geometry * model );
        static void computeTangents           ( Geometry * model );
};
#endif
