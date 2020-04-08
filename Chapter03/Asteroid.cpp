// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game* game)
	:Actor(game)
	,mCircle(nullptr)
{
	// ランダムで初期位置を設定
	Vector2 randPos = Random::GetVector(Vector2::Zero,
		Vector2(1024.0f, 768.0f));
	SetPosition(randPos);

	// ランダムな向きで初期化
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	// スプライトコンポーネント生成
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	// ムーブコンポーネント生成
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);

	// Add to mAsteroids in game
	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}
