#include "Transform.h"

Transform::Transform()
{

}
Transform::~Transform()
{

}

//äeçsóÒÇÃåvéZ
void Transform::Calculation()
{

    matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.y);
    matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}


XMMATRIX Transform::GetWorldMatrix(XMMATRIX worldmatrix)
{
    worldmatrix =  matTranslate_ * matScale_ * matRotate_;
    return XMMATRIX(worldmatrix);
}


