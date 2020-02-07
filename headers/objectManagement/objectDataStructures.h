#ifndef OBJECTDATASTRUCTURES_H
#define OBJECTDATASTRUCTURES_H
namespace primitives {
struct Point3d // point that contain its coords (x,y,z)
{
    Point3d(float _x, float _y, float _z)
        : x(_x)
        , y(_y)
        , z(_z)
    {
    }
    float x;
    float y;
    float z;
};

struct Line3d // line that contain index on vertex that form it (index mean index in vertex array)
{
    Line3d(unsigned int _indexVertex1, unsigned int _indexVertex2)
        : indexVertex1(_indexVertex1)
        , indexVertex2(_indexVertex2)
    {
    }
    unsigned int indexVertex1; // index first point
    unsigned int indexVertex2; // index second point
};

struct Triangle3d // triangle that contain index on vertex that form it
{
    Triangle3d(unsigned int _indexNormal, unsigned int _indexVertex1, unsigned int _indexVertex2,
               unsigned int _indexVertex3)
        : indexNormal(_indexNormal)
        , indexVertex1(_indexVertex1)
        , indexVertex2(_indexVertex2)
        , indexVertex3(_indexVertex3)
    {
    }
    unsigned int indexNormal;  // normal direction
    unsigned int indexVertex1; // index first point
    unsigned int indexVertex2; // index second point
    unsigned int indexVertex3; // index third point
};

struct Face3d // face that contain index on vertex that form it
{
    Face3d(unsigned int _indexNormal, unsigned int _indexVertex1, unsigned int _indexVertex2,
           unsigned int _indexVertex3, unsigned int _indexVertex4)
        : indexNormal(_indexNormal)
        , indexVertex1(_indexVertex1)
        , indexVertex2(_indexVertex2)
        , indexVertex3(_indexVertex3)
        , indexVertex4(_indexVertex4)
    {
    }
    unsigned int indexNormal;  // normal direction
    unsigned int indexVertex1; // index first point
    unsigned int indexVertex2; // index second point
    unsigned int indexVertex3; // index third point
    unsigned int indexVertex4; // index fourth point
};
} // namespace primitives
#endif // OBJECTDATASTRUCTURES_H
