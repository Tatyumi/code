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
	// 背景表示をするので描画順序の初期値は低め
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	// 描画、公人は親からオーバーライド
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	// 背景用テクスチャの設定
	void SetBGTextures(const std::vector<SDL_Texture*>& textures);
	// アクセサ
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
private:
	// 個々の背景画像とオフセットをカプセル化する構造体
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	// 背景画像配列
	std::vector<BGTexture> mBGTextures;
	// 画面サイズ
	Vector2 mScreenSize;
	// スクロール速度
	float mScrollSpeed;
};
