#ifndef AXISMESH_H
#define AXISMESH_H

#include "Mesh.h"
#include "ColorMaterial.h"

class CylinderGeometry;

class  DLL_SPEC  AxisMesh : public Mesh
{
public:
    AxisMesh();
    ~AxisMesh() override;

    void render(const QGLCamera *c, const QList<PointLight> & lights = QList<PointLight>(), Material *m = nullptr ) override;


private:
    CylinderGeometry * m_branchGeom;
    CylinderGeometry * m_pointerGeom;
    ColorMaterial      m_colorMaterial;

    QMatrix4x4 m_Tbranch, m_Tpointer, m_ry, m_rz;   // Transformation interne pour le positionnement des éléments du référentiel

    QMatrix4x4 m_modelAxeX, m_modelPointerX;
    QMatrix4x4 m_modelAxeY, m_modelPointerY;
    QMatrix4x4 m_modelAxeZ, m_modelPointerZ;

    constexpr static const float branchSize  = 1.2f;
    constexpr static const float pointerSize = 0.3f;

    void renderElement( Geometry & g, QMatrix4x4 & model, Material *m, const QGLCamera *c, const QList<PointLight> & lights );


};

#endif // AXISMESH_H
