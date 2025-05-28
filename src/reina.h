#pragma once

#include "pieza.h"

class Reina : public Pieza {
public:
    Reina();
    virtual ~Reina();

    virtual void dibuja() const override;
    bool mueve();
};
