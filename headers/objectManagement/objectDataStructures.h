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

struct line3d
{
    line3d(point3d _point1, point3d _point2)
        : point1(_point1)
        , point2(_point2){};
    point3d point1;
    point3d point2;
};

struct triangle3d
{
    triangle3d(point3d _normal, point3d _point1, point3d _point2, point3d _point3)
        : normal(_normal)
        , point1(_point1)
        , point2(_point2)
        , point3(_point3){};
    point3d normal;
    point3d point1;
    point3d point2;
    point3d point3;
};

struct face3d
{
    face3d(point3d _normal, point3d _point1, point3d _point2, point3d _point3, point3d _point4)
        : normal(_normal)
        , point1(_point1)
        , point2(_point2)
        , point3(_point3)
        , point4(_point4){};
    point3d normal;
    point3d point1;
    point3d point2;
    point3d point3;
    point3d point4;
};
}
#endif // OBJECTDATASTRUCTURES_H
