// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SpriteComponent.h"
#include <vector>
class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	// �A�j���[�V�����X�V����
	void Update(float deltaTime) override;
	// �A�j���[�V�����̃e�N�X�`����ݒ�
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	// �A�N�Z�T
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
private:
	// �A�j���[�V�����ł̂��ׂẴe�N�X�`��
	std::vector<SDL_Texture*> mAnimTextures;
	// ���ݕ\�����Ă���t���[��
	float mCurrFrame;
	// �A�j���[�V����FPS
	float mAnimFPS;
};
