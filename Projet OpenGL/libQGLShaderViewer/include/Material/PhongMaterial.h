/* Copyright (C) 2019 Stéphanie Prévost et Julien Gerhards- All Rights Reserved
 * This file is part of libQGLShaderViewer
 */

#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H


#include "Material.h"
#include <QVector4D>
#include <QColor>



/// ==============================================================
///    PhongMaterial
/// -------------------
///
/// Classe représentant un matériel qui réalise un éclairage de Phong
/// hérite de Matérial
///
/// Les paramètres sont :
///   - ambient : coef l'ambient
///   - diffuse : coef pour le difus
///   - f       : coef
///


class DLL_SPEC  PhongMaterial : public Material
{
public:
    PhongMaterial( const QVector4D &ambient, const QVector4D &diffuse, const float &f );
    PhongMaterial( const QColor    &ambient, const QColor    &diffuse, const float &f );

    QVector4D    getAmbiant() const;
    void         setAmbiant(const QVector4D &getAmbiant);

    QVector4D    getDiffuse() const;
    void         setDiffuse(const QVector4D &getDiffuse);
    void         setDiffuse(const QColor    &diffuse);


    float        getSpecPower() const;
    void         setSpecpower(float getSpecPower);

    void         render(const Mesh * mesh, const QGLCamera *c, const QList<PointLight> & lights ) override;

    virtual void bindSpecific( const QGLCamera *c )  override;

private:
    QVector4D m_ambiant;
    QVector4D m_diffuse;
    float     m_specpower;

};

#endif // PHONGMATERIAL_H
