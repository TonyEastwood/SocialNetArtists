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
    object3d fromStlToObject(const QByteArray fileName);
    object3d fromObjToObject(const QByteArray fileName);

private:
    float toFloat(const QByteArray bytes);
    primitives::point3d to3dPoint(QByteArray bytes);
};

#endif // OBJECTPARSEMANAGER_H
