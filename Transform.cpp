#include "Transform.h"

Transform::Transform() :position_(0.0f, 0.0f, 0.0f), rotate_(0.0f, 0.0f, 0.0f), scale_(0.0f, 0.0f, 0.0f)
{
    matTranslate_ = XMMatrixIdentity();
    matRotate_ = XMMatrixIdentity();
    matScale_ = XMMatrixIdentity();
}
Transform::~Transform()
{

}

//äeçsóÒÇÃåvéZ
void Transform::Calclation()
{
    position_ = matTranslate_();
}

XMMATRIX Transform::GetWorldMatrix(XMFLOAT3 worldmatrix)
{
    
    return XMMATRIX();
}


