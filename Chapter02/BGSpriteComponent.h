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
#include "Math.h"
class BGSpriteComponent : public SpriteComponent
{
public:
	// �w�i�\��������̂ŕ`�揇���̏����l�͒��
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	// �`��A���l�͐e����I�[�o�[���C�h
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	// �w�i�p�e�N�X�`���̐ݒ�
	void SetBGTextures(const std::vector<SDL_Texture*>& textures);
	// �A�N�Z�T
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
private:
	// �X�̔w�i�摜�ƃI�t�Z�b�g���J�v�Z��������\����
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	// �w�i�摜�z��
	std::vector<BGTexture> mBGTextures;
	// ��ʃT�C�Y
	Vector2 mScreenSize;
	// �X�N���[�����x
	float mScrollSpeed;
};
