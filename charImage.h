#ifndef CHAR_IMAGE_H
#define CHAR_IMAGE_H

struct CharImage {
  int size;
  int cols;
  int offset;  // the offset of each image is depending on all images before the current one;
  bool* imagePtr;
};


#endif