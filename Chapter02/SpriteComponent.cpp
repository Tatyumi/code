// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	,mTexture(nullptr)
	,mDrawOrder(drawOrder)
	,mTexWidth(0)
	,mTexHeight(0)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
		// �A�N�^�[�̃X�P�[���ɍ��킹��
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());

		// �A�N�^�̍��W�A�T�C�Y�����`�̍��W���擾(��`�̍��W�́A����̋�)
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		// �`��
		SDL_RenderCopyEx(renderer,	// �����_�[�^�[�Q�b�g
			mTexture,				// �e�N�X�`��
			nullptr,				// �`��͈�(nullptr�͑S��)
			&r,						// �����_�[�^�[�Q�b�g�ł̕`��͈͂̋�`
			-Math::ToDegrees(mOwner->GetRotation()),	// ��]�p���P�ʉ~
			nullptr,				// ��]���S(nullptr�Ȃ璆��)
			SDL_FLIP_NONE);			// �e�N�X�`�����]
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// Set width/height
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
