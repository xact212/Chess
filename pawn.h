#ifndef PAWN_H
#define PAWN_H
#include <stdbool.h>

struct pawn {
    char display;
    struct coordinate** moves; //array of coordinates represents each valid move disregarding obstacles
    bool hasBeenMoved;
};

struct pawn* buildPawn();

#endif