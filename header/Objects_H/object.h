#pragma once
#include "transform.h"

class Object
{
protected:
Object* parent = nullptr;
std::vector<Object*> children;

Transform transform;

void forceUpdateSelfAndChild();

public:
void addChild(std::initializer_list<Object*> objs);
const std::vector<Object*>& returnChildren();

void updateSelfAndChild();

virtual void draw() = 0;

};
