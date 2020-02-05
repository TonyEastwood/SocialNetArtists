#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <QByteArray>
#include <vector>
#include "objectinterface.h"
#include <QtMath>
class object3d : public ObjectInterface
{

public:
    object3d();
    ~object3d();

    QByteArray getHeaderInfo() const;
    void setHeaderInfo(const QByteArray &value);

    unsigned int getQuantitytriangle3d() const;
    void addtriangle3d(const primitives::triangle3d _triangle);
    std::vector<primitives::triangle3d> gettriangle3dData();
    primitives::point3d getMaxOriginAxis() const;

private:
    QByteArray headerInfo;
    std::vector<primitives::triangle3d> triangle3dData;
    primitives::point3d maxOriginAxis{
        0, 0, 0
    }; // max value on axis X,Y,Z (need to set start scale in openglViewer
    void setMaxOriginAxis(const primitives::point3d _point);
};

#endif // OBJECT3D_H
