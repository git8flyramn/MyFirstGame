#include "Transform.h"
Transform::Transform()
    :matTranslate_(XMMatrixIdentity()),
    matRotate_(XMMatrixIdentity()),
    matScale_(XMMatrixIdentity()),
    position_(0.0f, 0.0f, 0.0f),
    rotate_(0.0f, 0.0f, 0.0f),
    scale_(0.0f,0.0f,0.0f)
{
    position_ = XMFLOAT3(0.0f, 0.0f, 0.0f);
    rotate_ = XMFLOAT3(0.0f, 0.0f, 0.0f);
    scale_ = XMFLOAT3(0.0f, 0.0f, 0.0f);
}
Transform::~Transform()
{

}

//äeçsóÒÇÃåvéZ
void Transform::Calculation()
{

    matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.y);
    matRotate_ = XMMatrixRotationRollPitchYaw(XMConvertToRadians(rotate_.x),
        XMConvertToRadians(rotate_.y), XMConvertToRadians(rotate_.z));
    matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}


XMMATRIX Transform::GetWorldMatrix()
{
    return matScale_ * matRotate_ * matTranslate_;
}

XMMATRIX Transform::GetNomalMatrix()
{
    return matRotate_ * XMMatrixInverse(nullptr,matScale_);
}


