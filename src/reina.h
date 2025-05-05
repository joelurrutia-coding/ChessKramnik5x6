#pragma once

#include "pieza.h"

class Reina : public Pieza {
public:
    Reina();
    virtual ~Reina();

    virtual void dibujaIndividual() const;
    bool mueve();
};