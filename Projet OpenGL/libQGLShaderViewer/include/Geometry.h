/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */


#ifndef GEOMETRY_H
#define GEOMETRY_H


#include "glm/glm.hpp"

#include <vector>
#include <QOpenGLBuffer>
#include <QString>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include <QVector3D>

#include "define.h"



struct Face
{
    unsigned int s1,s2,s3;
};

/// ==============================================================
///    Geometry
/// -------------
///
/// Classe représentant la description geométrique d'un maillage triangulaire (pas de texture).
///
/// Ses paramètres sont :
///  - modelpath        : nom du fichier contenant le mesh
///  - withShift2Center : recentre le mesh en son centre.
///

class DLL_SPEC Geometry
{
public:
    Geometry  (const QString & modelpath ="" , bool withShift2Center = true);
    ~Geometry ();


    QOpenGLBuffer * vertexbuffer() const;
    void            setVertexbuffer(QOpenGLBuffer *vertexbuffer);

    QOpenGLBuffer * normal() const;
    void            setNormal(QOpenGLBuffer *normal);

    QOpenGLBuffer * uv() const;
    void            setUv(QOpenGLBuffer *uv);

    QOpenGLBuffer *indicebuffer() const;
    void           setIndicebuffer(QOpenGLBuffer *indicebuffer);

    QOpenGLBuffer *tangentesbuffer() const;
    void           setTangentesbuffer(QOpenGLBuffer *tangentesbuffer);

    QOpenGLBuffer *colorbuffer() const;
    void           setColorbuffer(QOpenGLBuffer *colorbuffer);

    void binds        ( GLuint attribPos, GLuint attribNorm, GLuint attribUvs , GLuint attribTang, GLuint attribColor);
    void bindVertices ( GLuint attrib );
    void bindNormals  ( GLuint attrib );
    void bindTextures ( GLuint attrib );
    void bindTangents ( GLuint attrib );
    void bindColors   ( GLuint attrib );

    void draw         ();

    QVector3D  getCenter     () const;
    void       getBoundingBox( QVector3D & leftBottomCorner, QVector3D & rightUpCorner ) const;
    void       shift2Center  ();


    std::vector < glm::vec3 >  listVertex;          // Liste des points
    std::vector < Face      >  listFaces;           // Liste des faces (regroupant de 3 sommets)
    std::vector < Face      >  listCoordFaces;      // Liste des coord textures des faces
    std::vector < glm::vec3 >  listNormals;         // Liste des normales
    std::vector < glm::vec3 >  listCoords;          // Liste des coords
    std::vector < glm::vec4 >  listTangents;        // Liste des tangentes
    std::vector < glm::vec4 >  listColors;          // Liste des couleurs (rgba) par vertex
    int                        nb_vertex;           // Nombre de sommets
    int                        nb_faces;            // Nombre de faces

    QOpenGLBuffer * main() const;


protected :
    void createOpenGLBuffers(bool withShift2Center = true);

    GLenum m_drawingMode = GL_TRIANGLES;

private:
    QOpenGLBuffer   *  m_main            = nullptr;
    QOpenGLBuffer   *  m_vertexbuffer    = nullptr;
    QOpenGLBuffer   *  m_normal          = nullptr;
    QOpenGLBuffer   *  m_uv              = nullptr;
    QOpenGLBuffer   *  m_indicebuffer    = nullptr;
    QOpenGLBuffer   *  m_tangentesbuffer = nullptr;
    QOpenGLBuffer   *  m_colorBuffer     = nullptr;
//    bool               isUV;
//    bool               isNormal;

    QOpenGLFunctions * gl;

};
#endif // GEOMETRY_H
