//
// Created by Quintin Dunn on 12/12/24.
//

#ifndef VERTEX_H
#define VERTEX_H

typedef unsigned short attribute;

//   https://paulbourke.net/dataformats/stl/
struct vector3 {
  float x;
  float y;
  float z;
};

typedef struct vector3 vector3;

struct face {
  vector3 normal_vector;
  vector3 a;
  vector3 b;
  vector3 c;
  attribute attributes;
};

typedef struct face face;

#endif //VERTEX_H
