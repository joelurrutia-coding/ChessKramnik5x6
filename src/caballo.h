#pragma once

#include "pieza.h"

class Caballo : public Pieza {
public:
    Caballo();
    virtual ~Caballo();

    virtual void dibujaIndividual() const;
    bool mueve();
};