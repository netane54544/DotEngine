#include "glm/glm.hpp"
#include "Math_H/mat4.h"
#include "Math_H/vector3.h"

class Transform
{
protected:
    //Local space information
    Vector3 m_pos = { 0.0f, 0.0f, 0.0f };
    Vector3 m_eulerRotDeg = { 0.0f, 0.0f, 0.0f };
    Vector3 m_scale = { 1.0f, 1.0f, 1.0f };

    Mat4 m_modelMatrix;

    bool is_dirty = false;

public:
    Mat4 getLocalModelMatrix() const;
    void computeModelMatrix();
    void computeModelMatrix(Mat4& parentGlobalModelMatrix);
    void setLocalPosition(const Vector3& newPosition);

    const Vector3& getLocalPosition();
    const Mat4& getLocalMatrix();
    const bool isDirty();

};
