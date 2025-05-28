#pragma once

#include "pieza.h"

class Torre : public Pieza {
public:
    Torre();
    virtual ~Torre();

    virtual void dibuja() const override;
    bool mueve();
};
