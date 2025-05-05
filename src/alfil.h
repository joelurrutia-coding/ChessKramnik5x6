#pragma once

#include "pieza.h"

class Alfil : public Pieza {
public:
    Alfil();
    virtual ~Alfil();

    virtual void dibujaIndividual() const;
    bool mueve();
};