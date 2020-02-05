#ifndef STLFORMAT_H
#define STLFORMAT_H

#include "../../headers/objectinterface.h"
#include <QByteArray>
#include <QFile>
#include <QDebug>
class stlFormat : public ObjectInterface
{
public:
    stlFormat();
    stlFormat(const QByteArray fileName);
    ~stlFormat();

private:
    QByteArray headerInfo;
    unsigned int quantityTriangles;
};

#endif // STLFORMAT_H
