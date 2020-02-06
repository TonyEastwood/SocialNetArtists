#ifndef OBJECTDATASTRUCTURES_H
#define OBJECTDATASTRUCTURES_H
namespace primitives {
struct point3d {
  point3d(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
  float x;
  float y;
  float z;
};

struct line3d {
  line3d(unsigned int _indexVertex1, unsigned int _indexVertex2)
      : indexVertex1(_indexVertex1), indexVertex2(_indexVertex2) {}
  unsigned int indexVertex1;
  unsigned int indexVertex2;
};

struct triangle3d {
  triangle3d(unsigned int _indexNormal, unsigned int _indexVertex1,
             unsigned int _indexVertex2, unsigned int _indexVertex3)
      : indexNormal(_indexNormal),
        indexVertex1(_indexVertex1),
        indexVertex2(_indexVertex2),
        indexVertex3(_indexVertex3) {}
  unsigned int indexNormal;
  unsigned int indexVertex1;
  unsigned int indexVertex2;
  unsigned int indexVertex3;
};

struct face3d {
  face3d(unsigned int _indexNormal, unsigned int _indexVertex1,
         unsigned int _indexVertex2, unsigned int _indexVertex3,
         unsigned int _indexVertex4)
      : indexNormal(_indexNormal),
        indexVertex1(_indexVertex1),
        indexVertex2(_indexVertex2),
        indexVertex3(_indexVertex3),
        indexVertex4(_indexVertex4) {}
  unsigned int indexNormal;
  unsigned int indexVertex1;
  unsigned int indexVertex2;
  unsigned int indexVertex3;
  unsigned int indexVertex4;
};
}  // namespace primitives
#endif  // OBJECTDATASTRUCTURES_H
