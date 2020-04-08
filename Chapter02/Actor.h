// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include "Math.h"
class Actor
{
public:
	// 状態を表す列挙
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	// コンストラクタ
	Actor(class Game* game);
	// デストラクタ
	virtual ~Actor();

	// 更新処理
	void Update(float deltaTime);
	// コンポーネント更新処理
	void UpdateComponents(float deltaTime);
	// アクター更新処理
	virtual void UpdateActor(float deltaTime);

	// ゲッター、セッター
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }


	// コンポーネント追加
	void AddComponent(class Component* component);
	// コンポーネント削除
	void RemoveComponent(class Component* component);
private:
	// アクターの状態
	State mState;

	// Transform
	Vector2 mPosition;
	float mScale;
	float mRotation;

	// コンポーネント配列
	std::vector<class Component*> mComponents;
	class Game* mGame;
};
