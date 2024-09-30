//
// Created by shams on 9/29/24.
//

#ifndef PHYZIX_CLASS_ID_H
#define PHYZIX_CLASS_ID_H

enum class ClassId {
    BASE,
    APPLICATION,
    STATIC_OBJECT,
    DYNAMIC_OBJECT,
    SCENE,
    CAMERA,
    BOUNDARY,
    LINE_SEGMENT_BOUNDARY,
    CIRCLE_BOUNDARY,
    VECTOR,
    DRAWABLE,
};


class ClassIdentifiable {
    virtual ClassId getId() const {
        return ClassId::BASE;
    }
};


#endif //PHYZIX_CLASS_ID_H
