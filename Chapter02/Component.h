// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
class Component
{
public:
	// コンストラクタ
	Component(class Actor* owner, int updateOrder = 100);
	// デストラクタ
	virtual ~Component();
	// 更新処理
	virtual void Update(float deltaTime);
	// ゲッター
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	// コンポーネントを所有するアクター
	class Actor* mOwner;
	// コンポーネントの更新順序
	int mUpdateOrder;
};
