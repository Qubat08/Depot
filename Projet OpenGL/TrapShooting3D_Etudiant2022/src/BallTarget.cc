#include "BallTarget.h"


/// ==============================================================
///    BALL TARGET
/// -------------
/// Classe fille de cible 3D positionnée et représentant une sphère ayant une couleur


BallTarget::BallTarget(Mesh *shape, unsigned int id, const QVector3D & pt, float size) : Target(shape, id, pt, size)
{
}

BallTarget::~BallTarget()
{
}

BallTarget::BallTarget(Mesh * shape, unsigned int id,  float x, float y, float z, float size) : Target(shape, id, QVector3D(x,y,z), size)
{
}


void BallTarget::render(QGLCamera* cam, const QList<PointLight>& lights)
{
     m_material->setDiffuse(this->getColor());
     m_shape->render(cam, lights);
}

bool BallTarget::intersect(QVector3D const &pt) const
{
}

