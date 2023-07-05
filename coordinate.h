#ifndef COORDINATE_H
#define COORDINATE_H

typedef struct{
    int x;
    int y;
}coordinate;

coordinate* buildCoordinate(int x, int y);
#endif