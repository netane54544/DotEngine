#include "Objects_H/transform.h"
#include "glm/gtc/matrix_transform.hpp"

Mat4 Transform::getLocalModelMatrix() const
{
    const glm::vec3 scale(m_scale.x, m_scale.y, m_scale.z);
    const glm::vec3 pos(m_pos.x, m_pos.y, m_pos.z);

    const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
                glm::radians(m_eulerRotDeg.x),
                glm::vec3(1.0f, 0.0f, 0.0f));
    const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
                glm::radians(m_eulerRotDeg.y),
                glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
                glm::radians(m_eulerRotDeg.z),
                glm::vec3(0.0f, 0.0f, 1.0f));

    const glm::mat4 rotationMatrix = transformY * transformX * transformZ;

    // TRS matrix
    glm::mat4 glmModelMatrix = glm::translate(glm::mat4(1.0f), pos) *
                rotationMatrix *
                glm::scale(glm::mat4(1.0f), scale);

    
    std::array<float, 16> elements;
    for (int i = 0; i < 16; ++i)
        elements[i] = glmModelMatrix[i / 4][i % 4];
    
    return Mat4(elements);
}

void Transform::computeModelMatrix()
{
    m_modelMatrix = getLocalModelMatrix();
    is_dirty = false;
}

void Transform::computeModelMatrix(Mat4& parentGlobalModelMatrix)
{
    Mat4 mat = getLocalModelMatrix();
    m_modelMatrix = parentGlobalModelMatrix * mat;
    is_dirty = false;
}

void Transform::setLocalPosition(const Vector3& newPosition)
{
    m_pos = newPosition;
    is_dirty = true;
}

const Vector3& Transform::getLocalPosition()
{
    return m_pos;
}

const Mat4& Transform::getLocalMatrix()
{
    return m_modelMatrix;
}

const bool Transform::isDirty()
{
    return is_dirty;
}
