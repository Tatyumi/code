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

// 更新処理
void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	for (auto& bg : mBGTextures)
	{
		// オフセット更新
		bg.mOffset.x += mScrollSpeed * deltaTime;
		// If this is completely off the screen, reset offset to
		// the right of the last bg texture
		// 画面外か判別
		if (bg.mOffset.x < -mScreenSize.x)
		{
			// 画面外の場合

			// 最後の背景テクスチャの右にリセットする
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

// 背景用テクスチャを設定
void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		BGTexture temp;
		temp.mTexture = tex;
		// オフセット初期化(横スクロール想定のためx方向のサイズを持つ)
		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;
		// 追加
		mBGTextures.emplace_back(temp);
		count++;
	}
}
