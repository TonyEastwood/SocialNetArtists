#ifndef OBJECTPARSEMANAGER_H
#define OBJECTPARSEMANAGER_H
#include "headers/supportedFormat/stlformat.h"
#include <QDebug>
class ObjectParseManager
{
public:
    ObjectParseManager();

    ~ObjectParseManager();
    stlFormat parseStlObject(const QByteArray fileName);
};

#endif // OBJECTPARSEMANAGER_H
