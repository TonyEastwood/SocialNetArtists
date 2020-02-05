#ifndef OBJECTINTERFACE_H
#define OBJECTINTERFACE_H
#include "objectDataStructures.h"
#include <QByteArray>
#include <QFile>

class ObjectInterface
{

public:
    ObjectInterface();
    virtual ~ObjectInterface() = 0;
};

#endif // OBJECTINTERFACE_H
