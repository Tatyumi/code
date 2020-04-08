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
	// ��Ԃ�\����
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	// �R���X�g���N�^
	Actor(class Game* game);
	// �f�X�g���N�^
	virtual ~Actor();

	// �X�V����
	void Update(float deltaTime);
	// �R���|�[�l���g�X�V����
	void UpdateComponents(float deltaTime);
	// �A�N�^�[�X�V����
	virtual void UpdateActor(float deltaTime);

	// �Q�b�^�[�A�Z�b�^�[
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }


	// �R���|�[�l���g�ǉ�
	void AddComponent(class Component* component);
	// �R���|�[�l���g�폜
	void RemoveComponent(class Component* component);
private:
	// �A�N�^�[�̏��
	State mState;

	// Transform
	Vector2 mPosition;
	float mScale;
	float mRotation;

	// �R���|�[�l���g�z��
	std::vector<class Component*> mComponents;
	class Game* mGame;
};
