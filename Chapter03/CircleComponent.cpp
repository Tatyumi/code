// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(class Actor* owner)
:Component(owner)
,mRadius(0.0f)
{
	
}

// ���_���W���擾
const Vector2& CircleComponent::GetCenter() const
{
	// �I�[�i�[�̍��W��Ԃ�
	return mOwner->GetPosition();
}

float CircleComponent::GetRadius() const
{
	return mOwner->GetScale() * mRadius;
}

// 2�̉~�̌����𔻕�
bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	// 2�̉~�̋������Z�o
	Vector2 diff = a.GetCenter() - b.GetCenter();

	// 2��
	float distSq = diff.LengthSq();

	// 2�̉~�̔��a�̘a
	float radiiSq = a.GetRadius() + b.GetRadius();

	// 2��
	radiiSq *= radiiSq;

	// ���a�̘a��2�_�Ԃ̋�����菬����������(2�悵���̂́A���̒l�̏ꍇ�A���ɂ��邽��)
	return distSq <= radiiSq;
}
