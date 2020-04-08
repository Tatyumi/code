// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
:Component(owner, updateOrder)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
{
	
}

void MoveComponent::Update(float deltaTime)
{
	// ��]���x���O�ɋ߂�������
	if (!Math::NearZero(mAngularSpeed))
	{
		// �߂��Ȃ��ꍇ

		// �p�x���擾
		float rot = mOwner->GetRotation();

		// �p�x�����Z
		rot += mAngularSpeed * deltaTime;

		// �p�x���Z�b�g
		mOwner->SetRotation(rot);
	}
	
	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2 pos = mOwner->GetPosition();

		// �O�i(�ʒu���W����O�Ɍ����Ĉړ�)
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
		
		// ��ʃT�C�Y���l���������b�s���O(�{���͂�������Ȃ�)
		if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }

		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }

		mOwner->SetPosition(pos);
	}
}
