#include "../../headers/supportedFormat/stlformat.h"

stlFormat::stlFormat()
{
}

stlFormat::stlFormat(const QByteArray fileName)
{
    QFile stlFile(fileName);
    if (stlFile.open(QIODevice::ReadOnly))
    {
        headerInfo = stlFile.read(80);
        quantityTriangles = *((unsigned int*)stlFile.read(4).toStdString().c_str());
    }
}

stlFormat::~stlFormat()
{
}
