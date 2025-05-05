#pragma once

#include "pieza.h"

class Torre : public Pieza {
public:
    Torre();
    virtual ~Torre();

    virtual void dibujaIndividual() const;
    bool mueve();
};