//
// Created by shams on 8/7/24.
//

#ifndef PHYZIX_DRAWABLE_H
#define PHYZIX_DRAWABLE_H


#include "app/lib/class_id.h"

class Drawable: public ClassIdentifiable {
public:
    ClassId getId() const override {
        return ClassId::DRAWABLE;
    }

    virtual void draw() const = 0;
};


#endif //PHYZIX_DRAWABLE_H
