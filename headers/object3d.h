#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <QByteArray>
#include <vector>
#include <headers/objectinterface.h>
class object3d : public ObjectInterface
{
    using triangles = primitives::triangles;

public:
    object3d();
    ~object3d();

    QByteArray getHeaderInfo() const;
    void setHeaderInfo(const QByteArray &value);

    unsigned int getQuantityTriangles() const;
    void addTriangles(const triangles _triangle);
    std::vector<triangles> getTrianglesData();

private:
    QByteArray headerInfo;
    std::vector<triangles> trianglesData;
};

#endif // OBJECT3D_H
