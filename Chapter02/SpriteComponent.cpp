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
		// アクターのスケールに合わせる
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());

		// アクタの座標、サイズから矩形の座標を取得(矩形の座標は、左上の隅)
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		// 描画
		SDL_RenderCopyEx(renderer,	// レンダーターゲット
			mTexture,				// テクスチャ
			nullptr,				// 描画範囲(nullptrは全部)
			&r,						// レンダーターゲットでの描画範囲の矩形
			-Math::ToDegrees(mOwner->GetRotation()),	// 回転角※単位円
			nullptr,				// 回転中心(nullptrなら中央)
			SDL_FLIP_NONE);			// テクスチャ反転
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// Set width/height
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
