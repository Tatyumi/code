// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	// テクスチャが格納されているか判別
	if (mAnimTextures.size() > 0)
	{
		// 格納されている場合

		// 現在のフレームレートを算出
		mCurrFrame += mAnimFPS * deltaTime;
		
		// アニメーションを周期的に巻き戻す
		while (mCurrFrame >= mAnimTextures.size())
		{
			mCurrFrame -= mAnimTextures.size();
		}

		// 現状のフレームレートに合わせたテクスチャを設定
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}
