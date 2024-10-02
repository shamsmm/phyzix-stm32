//
// Created by shams on 8/7/24.
//

#ifndef PHYZIX_DRAWABLE_H
#define PHYZIX_DRAWABLE_H


#include "app/lib/rtti.h"

class Drawable: public RuntimeBaseTypeIdentifiable {
public:
    RuntimeBaseType getBaseType() const override {
        return RuntimeBaseType::DRAWABLE;
    }

    virtual void draw() const = 0;
};


#endif //PHYZIX_DRAWABLE_H
