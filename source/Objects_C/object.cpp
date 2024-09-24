#include "Objects_H/object.h"

void Object::forceUpdateSelfAndChild()
{
    if (parent)
    {
        Mat4 tempModel = parent->transform.getLocalMatrix();
        transform.computeModelMatrix(tempModel);
    }   
    else
    {
        transform.computeModelMatrix();
    }

    for (auto&& child : children)
        child->forceUpdateSelfAndChild();
}

void Object::updateSelfAndChild()
{
    if (transform.isDirty())
    {
        forceUpdateSelfAndChild();
        return;
    }

    for (auto&& child : children)
        child->updateSelfAndChild();
}

const std::vector<Object*>& Object::returnChildren()
{
    return children;
}

void Object::addChild(std::initializer_list<Object*> objs)
{
    for (Object* obj : objs)
    {
        obj->parent = this;
        children.push_back(obj);
    }
}
