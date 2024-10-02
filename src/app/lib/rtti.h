//
// Created by shams on 9/29/24.
//

#ifndef PHYZIX_RTTI_H
#define PHYZIX_RTTI_H

/**
 * @class RuntimeBaseType
 * @brief Enum class to identify the base type of a class for runtime type identification
 * @details This enum class is used to identify the base type of a classes that inherit from RuntimeBaseTypeIdentifiable in runtime
 * @see RuntimeBaseTypeIdentifiable
 * @note This is specially implemented for low-memory embedded systems where RTTI is not available, `-fno-rtti` flag is used
 * @note This is not intended for exact runtime type identification, but to identify the base type of a class,
 * for example RectangleDynamicObject and CircleDynamicObject both inherit from DynamicObject, so both have the same informative base type
 */
enum class RuntimeBaseType {
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


/**
 * @class RuntimeBaseTypeIdentifiable
 * @brief Base class for runtime type identification
 * @see RuntimeBaseType
 * @details Inherit from this class to enable runtime base type identification for a class
 */
class RuntimeBaseTypeIdentifiable {
    virtual RuntimeBaseType getBaseType() const {
        return RuntimeBaseType::BASE;
    }
};


#endif //PHYZIX_RTTI_H
