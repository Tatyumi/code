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

// 中点座標を取得
const Vector2& CircleComponent::GetCenter() const
{
	// オーナーの座標を返す
	return mOwner->GetPosition();
}

float CircleComponent::GetRadius() const
{
	return mOwner->GetScale() * mRadius;
}

// 2つの円の交差を判別
bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	// 2つの円の距離を算出
	Vector2 diff = a.GetCenter() - b.GetCenter();

	// 2乗
	float distSq = diff.LengthSq();

	// 2つの円の半径の和
	float radiiSq = a.GetRadius() + b.GetRadius();

	// 2乗
	radiiSq *= radiiSq;

	// 半径の和が2点間の距離より小さいか判別(2乗したのは、負の値の場合、正にするため)
	return distSq <= radiiSq;
}
