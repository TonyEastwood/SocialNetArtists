#ifndef OBJECTPARSEMANAGER_H
#define OBJECTPARSEMANAGER_H
#include "headers/object3d.h"
#include <QDebug>
class ObjectParseManager
{
public:
    ObjectParseManager();

    ~ObjectParseManager();
    object3d fromStlToObject(const QByteArray fileName);

private:
    float toFloat(const QByteArray bytes);
    primitives::point3d to3dPoint(QByteArray bytes);
};

#endif // OBJECTPARSEMANAGER_H
