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
	// 回転速度が０に近いか判別
	if (!Math::NearZero(mAngularSpeed))
	{
		// 近くない場合

		// 角度を取得
		float rot = mOwner->GetRotation();

		// 角度を加算
		rot += mAngularSpeed * deltaTime;

		// 角度をセット
		mOwner->SetRotation(rot);
	}
	
	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2 pos = mOwner->GetPosition();

		// 前進(位置座標から前に向けて移動)
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
		
		// 画面サイズを考慮したラッピング(本来はここじゃない)
		if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }

		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }

		mOwner->SetPosition(pos);
	}
}
