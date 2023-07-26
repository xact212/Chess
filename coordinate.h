#ifndef COORDINATE_H
#define COORDINATE_H

typedef struct coordinate{
    int x;
    int y;
}coordinate;

coordinate* buildCoordinate(int x, int y);
#endif