#pragma once

#include "pieza.h"

class Peon : public Pieza {
public:
    Peon();
    virtual ~Peon();

    virtual void dibuja() const override;
    bool mueve();
};