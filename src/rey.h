#pragma once

#include "pieza.h"

class Rey : public Pieza {
public:
    Rey();
    virtual ~Rey();

    virtual void dibujaIndividual() const;
    bool mueve();
};