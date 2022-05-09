/**
 * @file AttributeEntity.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief The AttributeEntity class.
 * Is responsible for class diagram attribute storage
 * Attribute can be either a field or a method.
 *
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __ATTRIBUTE_ENTITY_H__
#define __ATTRIBUTE_ENTITY_H__

#include "../Common/enums.h"

#include <string>

class AttributeEntity
{
private:
    Enums::Attrib_type type;
    //*******************
    Enums::AccessModifiers access;
    std::string data;

public:
    /**
     * @brief Checks if the attribute contains valid data
     *
     * @return true if is well formated
     * @return false if it isn't
     */
    bool IsOK();
    /**
     * @brief Parses the string of the attribute and determines, if it contains a valid method
     *
     * @return true if is well formated
     * @return false if it isn't
     */
    bool IsMethod();

    /**
     * @brief Set the Data of the attribute
     *
     */
    void SetData(std::string);

    /**
     * @brief Get the Data of the attribute
     *
     * @return std::string data representation
     */
    std::string GetData();

    /**
     * @brief Switches the type of the attribute
     * if is contains a method, it becomes a field and otherwise
     *
     */
    void SwitchType();

    /**
     * @brief Set the Access modifier to the attribute
     *
     * @param access enum value of access modifier
     */
    void SetAccess(Enums::AccessModifiers access);

    /**
     * @brief Get the Access modifier
     *
     * @return Enums::AccessModifiers value
     */
    Enums::AccessModifiers GetAccess();

    /**
     * @brief Get the type of attribute (field/method)
     *
     * @return Enums::Attrib_type representation
     */
    Enums::Attrib_type GetType();

    /**
     * @brief Construct a new Attribute Entity object
     *
     * @param type initial type of attribute
     * @param data string data
     */
    AttributeEntity(Enums::Attrib_type type, std::string data);
    ~AttributeEntity();
};

#endif
