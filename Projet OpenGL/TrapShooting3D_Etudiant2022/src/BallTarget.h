#ifndef BALLTARGET_H
#define BALLTARGET_H

#include <Material.h>
#include <glTexture.h>

#include "Target.h"

/// ==============================================================
///    BALL TARGET
/// -------------
/// Classe fille de cible 3D positionnée et
/// représentant une sphère ayant une couleur et une taille (rayon)
///
/// A écrire dans sa globalité par les étudiants

class BallTarget : public Target
{
public:
    BallTarget(Mesh *shape, unsigned int id, const QVector3D & pt, float size );
    BallTarget(Mesh *shape, unsigned int id, float x, float y, float z, float size);
    virtual ~BallTarget() override;

    void render(QGLCamera* cam, const QList<PointLight>& lights) override;
    bool intersect(const QVector3D& pt) const override;

    float vitesse = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 8.0f +1;
    QVector3D direction = QVector3D(static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f,
                                    static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f,
                                    static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f
                                    );

};

#endif
