#ifndef PROPERTY_MANAGER
#define PROPERTY_MANAGER

class IPropertyManager {

	public:

        virtual float getf(int propertyID)=0;

        virtual void setf(int propertyID, float value)=0;

};

#endif // PROPERTY_MANAGER
