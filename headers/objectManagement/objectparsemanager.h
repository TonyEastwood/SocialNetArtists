#ifndef OBJECTPARSEMANAGER_H
#define OBJECTPARSEMANAGER_H
#include <QDebug>

#include "object3d.h"
#include "stdio.h"
#include <QList>
class ObjectParseManager
{
public:
    ObjectParseManager();
    ~ObjectParseManager();

    Object3d fromStlToObject(const QByteArray fileName); // convert file stl to object
    Object3d fromObjToObject(const QByteArray fileName); // convert file obj to object

private:
    float toFloat(
        const QByteArray bytes); // convert bytes value to float value ( use in convertation of stal format)
    primitives::Point3d
    to3dPoint(QByteArray bytes); // convert bytes array to 3d point (use in convertation of stl format)
};

#endif // OBJECTPARSEMANAGER_H
