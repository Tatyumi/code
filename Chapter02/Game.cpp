// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include "SDL/SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "BGSpriteComponent.h"

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mIsRunning(true)
,mUpdatingActors(false)
{
	
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 2)", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	
	// PNG画像ファイルをロード
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicks();
	
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	// Process ship input
	mShip->ProcessKeyboard(state);
}

// ゲーム更新処理
void Game::UpdateGame()
{
	// 前のフレームから16ms経過するまで待機
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// 前フレームからの経過時間を取得
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// 指定の時間以上経過しているか判別
	if (deltaTime > 0.05f)
	{
		// 経過していた場合

		// 最大値代入
		deltaTime = 0.05f;
	}

	// チック更新
	mTicksCount = SDL_GetTicks();

	// 全アクター更新
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	// 更新終了
	mUpdatingActors = false;

	// 待機状態のアクターを活動状態アクター配列に移動
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	// 移動後空にする
	mPendingActors.clear();

	// 死んでいる状態のアクタを配列に格納
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// 死んでいる状態配列を削除
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
	
	// Draw all sprite components
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	// Create player's ship
	mShip = new Ship(this);
	mShip->SetPosition(Vector2(100.0f, 384.0f));
	mShip->SetScale(1.5f);

	// Create actor for the background (this doesn't need a subclass)
	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(512.0f, 384.0f));
	// Create the "far back" background
	BGSpriteComponent* bg = new BGSpriteComponent(temp);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	std::vector<SDL_Texture*> bgtexs = {
		GetTexture("Assets/Farback01.png"),
		GetTexture("Assets/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-100.0f);
	// Create the closer background
	bg = new BGSpriteComponent(temp, 50);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	bgtexs = {
		GetTexture("Assets/Stars.png"),
		GetTexture("Assets/Stars.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-200.0f);
}

void Game::UnloadData()
{
	// 全アクタ削除
	// 各アクタのデストラクタでRemoveActor()が呼び出されるので、別途ループで実行
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy textures
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	// Is the texture already in the map?
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		// ファイルをロード
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// サーフェスからテクスチャを生成
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

// アクター追加
void Game::AddActor(Actor* actor)
{
	// アクターが更新中か判別
	if (mUpdatingActors)
	{
		// 更新中の場合

		// 待ち状態のアクター配列に格納
		mPendingActors.emplace_back(actor);
	}
	else
	{
		// 更新中でない場合

		// 活動状態のアクター配列に格納
		mActors.emplace_back(actor);
	}
}

// アクター削除
void Game::RemoveActor(Actor* actor)
{
	// 待ち状態のアクター配列にアクターが格納されているか確認
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	
	// 格納されているか判別
	if (iter != mPendingActors.end())
	{
		// 格納されている場合

		// 末尾と交換
		std::iter_swap(iter, mPendingActors.end() - 1);
		// 削除
		mPendingActors.pop_back();
	}

	// 活動状態のアクター配列にアクターが格納されているか確認
	iter = std::find(mActors.begin(), mActors.end(), actor);

	// 格納されているか判別
	if (iter != mActors.end())
	{
		// 格納されている場合

		// 末尾と交換
		std::iter_swap(iter, mActors.end() - 1);
		// 削除
		mActors.pop_back();
	}
}

// スプライト追加
void Game::AddSprite(SpriteComponent* sprite)
{
	// 描画順を取得
	int myDrawOrder = sprite->GetDrawOrder();

	// 
	auto iter = mSprites.begin();
	for ( ;
		iter != mSprites.end();
		++iter)
	{
		// イテレータとの描画順を比較
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			// イテレータより小さい場合

			break;
		}
	}

	// イテレータの前の位置に挿入
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}
