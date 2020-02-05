#include "../headers/objectparsemanager.h"

ObjectParseManager::ObjectParseManager()
{
}

ObjectParseManager::~ObjectParseManager()
{
}

stlFormat ObjectParseManager::parseStlObject(const QByteArray fileName)
{
    if (!QFile(fileName).exists())
    {
        qDebug() << "File " + fileName + " non exist";
        return stlFormat();
    }

    stlFormat stlObject(fileName);
    return stlFormat();
}
