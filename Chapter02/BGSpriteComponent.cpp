// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "BGSpriteComponent.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent(class Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	,mScrollSpeed(0.0f)
{
}

// �X�V����
void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	for (auto& bg : mBGTextures)
	{
		// �I�t�Z�b�g�X�V
		bg.mOffset.x += mScrollSpeed * deltaTime;
		// If this is completely off the screen, reset offset to
		// the right of the last bg texture
		// ��ʊO������
		if (bg.mOffset.x < -mScreenSize.x)
		{
			// ��ʊO�̏ꍇ

			// �Ō�̔w�i�e�N�X�`���̉E�Ƀ��Z�b�g����
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	// Draw each background texture
	for (auto& bg : mBGTextures)
	{
		SDL_Rect r;
		// Assume screen size dimensions
		r.w = static_cast<int>(mScreenSize.x);
		r.h = static_cast<int>(mScreenSize.y);
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y);

		// Draw this background
		SDL_RenderCopy(renderer,
			bg.mTexture,
			nullptr,
			&r
		);
	}
}

// �w�i�p�e�N�X�`����ݒ�
void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		BGTexture temp;
		temp.mTexture = tex;
		// �I�t�Z�b�g������(���X�N���[���z��̂���x�����̃T�C�Y������)
		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;
		// �ǉ�
		mBGTextures.emplace_back(temp);
		count++;
	}
}
