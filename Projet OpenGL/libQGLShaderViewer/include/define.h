/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef DEFINE_H_QGLShaderViewer_LIB
#define DEFINE_H_QGLShaderViewer_LIB


#include <QtGlobal>
#ifdef NO_LIB_QGLShaderViewer
    #define DLL_SPEC
#elif  BUILD_LIB_QGLShaderViewer
    #define DLL_SPEC Q_DECL_EXPORT
#else
    #define DLL_SPEC Q_DECL_IMPORT
#endif




#endif // DEFINE_H
