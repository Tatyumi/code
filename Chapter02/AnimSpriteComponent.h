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
	// アニメーション更新処理
	void Update(float deltaTime) override;
	// アニメーションのテクスチャを設定
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	// アクセサ
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
private:
	// アニメーションでのすべてのテクスチャ
	std::vector<SDL_Texture*> mAnimTextures;
	// 現在表示しているフレーム
	float mCurrFrame;
	// アニメーションFPS
	float mAnimFPS;
};
