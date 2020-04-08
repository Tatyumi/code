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
	// �R���X�g���N�^
	Component(class Actor* owner, int updateOrder = 100);
	// �f�X�g���N�^
	virtual ~Component();
	// �X�V����
	virtual void Update(float deltaTime);
	// �Q�b�^�[
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	// �R���|�[�l���g�����L����A�N�^�[
	class Actor* mOwner;
	// �R���|�[�l���g�̍X�V����
	int mUpdateOrder;
};
