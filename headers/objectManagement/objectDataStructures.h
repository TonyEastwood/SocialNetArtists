#ifndef OBJECTDATASTRUCTURES_H
#define OBJECTDATASTRUCTURES_H
namespace primitives {
struct point3d
{
    point3d(float _x, float _y, float _z)
        : x(_x)
        , y(_y)
        , z(_z){};
    float x;
    float y;
    float z;
};

struct triangles
{
    triangles(point3d _normal, point3d _point1, point3d _point2, point3d _point3)
        : normal(_normal)
        , point1(_point1)
        , point2(_point2)
        , point3(_point3){};
    point3d normal;
    point3d point1;
    point3d point2;
    point3d point3;
};
}
#endif // OBJECTDATASTRUCTURES_H
