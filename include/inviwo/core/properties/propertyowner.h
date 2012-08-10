#ifndef IVW_PROPERTYOWNER_H
#define IVW_PROPERTYOWNER_H

#include "inviwo/core/inviwo.h"

namespace inviwo {

class Property;

class PropertyOwner {

public:
    PropertyOwner();
    virtual ~PropertyOwner();

    void addProperty(Property* property);
    void addProperty(Property& property);

    Property* getPropertyByIdentifier(std::string identifier);

    void invalidate();
    void setValid();
    bool isValid();

private:
    std::vector<Property*> properties_;
    bool invalid_;

};

} // namespace

#endif // IVW_PROPERTYOWNER_H
