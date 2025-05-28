#pragma once

#include "pieza.h"

class Caballo : public Pieza {
public:
    Caballo();
    virtual ~Caballo();

    virtual void dibuja() const override;
    bool mueve();
};
