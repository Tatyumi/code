// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"

// 幅
const int thickness = 15;
// パドルの高さ
const float paddleH = 100.0f;
// パドルの横幅
const float paddleW = 5.0;
// ウィンドウ左上隅のx座標
const int windowTopLeftXPos = 100;
// ウィンドウ左上隅のy座標
const int windowTopLeftYPos = 100;
// ウィンドウの横幅
const int windowWidth = 1024;
// ウィンドウの縦幅
const int windowHeight = 768;
// 上限フレーム数
const int limitFrame = 16;
// デルタタイムの最大値
const float maxDeltaTime = 0.05f;
// パドルの移動速度
const int paddleMoveSpeed = 1;
// ボールの初期速度
const float iniBallXVel = -200.0f;
const float iniBallYVel = 235.0f;

Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mTicksCount(0)
	, mIsRunning(true)
	, mPaddleDir(0)
{

}

// 初期化処理
bool Game::Initialize()
{
	// SDLライブラリ(ビデオサブシステム)を初期化
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	// 初期化が成功したか判別
	if (sdlResult != 0)
	{
		// 失敗した場合

		// ログ出力
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// SDLウィンドウ生成
	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)", // Window title
		windowTopLeftXPos,	// Top left x-coordinate of window
		windowTopLeftYPos,	// Top left y-coordinate of window
		windowWidth,	// Width of window
		windowHeight,	// Height of window
		0		// Flags (0 for no flags set)
	);

	// ウィンドウの呼び出しが成功したか判別
	if (!mWindow)
	{
		// 失敗した場合

		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	//// レンダラー生成
	mRenderer = SDL_CreateRenderer(
		mWindow, // 描画対象のウィンドウのポインタ
		-1,		 // 通常は -1（ウィンドウ数を指定するもので、1つの場合-1となる）
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // 初期化フラグ
	);

	// レンダラー生成が成功したか判別
	if (!mRenderer)
	{
		// 失敗した場合

		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	// パドルの初期座標
	mPaddlePos.x = 10.0f;
	mPaddlePos.y = windowHeight / 2.0f;

	// 2Pパドルの初期座標
	mPaddle2Pos.x = windowWidth - thickness;
	mPaddle2Pos.y = mPaddlePos.y;

	// ボールのパラメータ(座標、速度)
	mBallPos.x = windowWidth / 2.0f;
	mBallPos.y = windowHeight / 2.0f;
	mBallVel.x = iniBallXVel;
	mBallVel.y = iniBallYVel;
	return true;
}

// ゲームループ
void Game::RunLoop()
{
	// 繰り返し実行するか判別
	while (mIsRunning)
	{
		// 実行部

		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

// 入力処理
void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		// イベントのタイプ判別
		switch (event.type)
		{
			// ウィンドウを閉じた場合
			// 「×」をクリック、Alt+F4など
			case SDL_QUIT:

				// ループ終了
				mIsRunning = false;
				break;
		}
	}

	// キーボードの状態格納配列
	const Uint8* state = SDL_GetKeyboardState(NULL);

	// 「Esc」が押されたか判別
	if (state[SDL_SCANCODE_ESCAPE])
	{
		// ループ終了
		mIsRunning = false;
	}

	// Update paddle direction based on W/S keys
	mPaddleDir = 0;

	// 入力判別
	if (state[SDL_SCANCODE_W])
	{
		// 「w」が押された場合

		// 減少
		mPaddleDir -= paddleMoveSpeed;
	}
	if (state[SDL_SCANCODE_S])
	{
		// 「s」が押された場合

		// 増加
		mPaddleDir += paddleMoveSpeed;
	}

	mPaddle2Dir = 0;

	// 入力判別
	if (state[SDL_SCANCODE_I])
	{
		// 「I」が押された場合

		mPaddle2Dir -= paddleMoveSpeed;
	}
	if (state[SDL_SCANCODE_K])
	{
		// 「K」が押された場合

		mPaddle2Dir += paddleMoveSpeed;
	}

}

void Game::UpdateGame()
{
	// 前フレームから指定の上限値を経過しているか判別
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + limitFrame))
		;

	// 最後のフレームから経過した時間(deltaTime)を取得
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// デルタタイムの最大値を超えたか判別
	// フレームレートがはるか先に進まないため
	if (deltaTime > maxDeltaTime)
	{
		// 超えた場合

		// 最大値の代入
		deltaTime = maxDeltaTime;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();

	// パドルの移動判別
	if (mPaddleDir != 0)
	{
		// 移動、つまり指定の入力があった場合

		// y座標(縦軸)での値更新
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;

		// パドルを画面内に制御
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))
		{
			// 画面上部に達した場合

			mPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlePos.y > (windowHeight - paddleH / 2.0f - thickness))
		{
			// 画面下部に達した場合

			mPaddlePos.y = windowHeight - paddleH / 2.0f - thickness;
		}
	}

	// 2Pパドルの移動判別
	if (mPaddle2Dir != 0)
	{
		// 移動、つまり指定の入力があった場合

		// y座標(縦軸)での値更新
		mPaddle2Pos.y += mPaddle2Dir * 300.0f * deltaTime;

		// パドルを画面内に制御
		if (mPaddle2Pos.y < (paddleH / 2.0f + thickness))
		{
			// 画面上部に達した場合

			mPaddle2Pos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddle2Pos.y > (windowHeight - paddleH / 2.0f - thickness))
		{
			// 画面下部に達した場合

			mPaddle2Pos.y = windowHeight - paddleH / 2.0f - thickness;
		}
	}

	// ボールの位置を更新
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	// パドルとボールのy座標の距離を取得
	float diffPaddleAndBall = mPaddlePos.y - mBallPos.y;
	float diffPaddle2AndBall = mPaddle2Pos.y - mBallPos.y;

	// 距離の絶対値を取得
	diffPaddleAndBall = (diffPaddleAndBall > 0.0f) ? diffPaddleAndBall : -diffPaddleAndBall;
	diffPaddle2AndBall = (diffPaddle2AndBall > 0.0f) ? diffPaddle2AndBall : -diffPaddle2AndBall;

	float paddleCollisionXPos = thickness + mPaddlePos.x;
	float paddle2CollisionXPos =  mPaddle2Pos.x - thickness;

	if (// 差の距離がパドルより小さく
		diffPaddleAndBall <= paddleH / 2.0f &&
		// ボールのx座標がパドルに接触していて
		mBallPos.x <= paddleCollisionXPos && mBallPos.x >= paddleCollisionXPos - paddleW &&
		// ボールが左方向に進んでいる
		mBallVel.x < 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	else if (// 差の距離が2Pパドルより小さく
		diffPaddle2AndBall <= paddleH / 2.0f &&
		// ボールのx座標が2Pパドルに接触していて
		mBallPos.x <= paddle2CollisionXPos && mBallPos.x >= paddle2CollisionXPos - paddleW &&
		// ボールが右方向に進んでいる
		mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	// Did the ball go off the screen? (if so, end game)
	else if (mBallPos.x <= 0.0f)
	{
		mIsRunning = false;
	}
	// 画面右側にボールが出た場合
	else if (mBallPos.x >= windowWidth)
	{
		mIsRunning = false;
	}

	// 上下の壁の衝突判定
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		// 上の壁に衝突し、かつボールが上向きに進んでいる場合

		// 縦向きを反転
		mBallVel.y *= -1;
	}
	else if (mBallPos.y >= (windowHeight - thickness) &&
		mBallVel.y > 0.0f)
	{
		// 下の壁に衝突し、かつボールが下向きに進んでいる場合

		// 縦向きを反転
		mBallVel.y *= -1;
	}
}

// 出力生成
void Game::GenerateOutput()
{
	// 青を描画
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G 
		255,	// B
		255		// A
	);

	// バックバッファを青でクリア
	SDL_RenderClear(mRenderer);

	// 白の壁
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	// 画面上部の壁
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		windowWidth,		// Width
		thickness	// Height
	};

	// ウィンドウに壁の描画
	SDL_RenderFillRect(mRenderer, &wall);

	// 画面下部の壁のためのy座標
	wall.y = windowHeight - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	// パドルの描画
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	// 2Pパドルの描画
	paddle.x = static_cast<int>(mPaddle2Pos.x - thickness);
	paddle.y = static_cast<int>(mPaddle2Pos.y - paddleH / 2);
	SDL_RenderFillRect(mRenderer, &paddle);

	// ボールの描画
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	// フロントバッファとバックバッファを交換
	SDL_RenderPresent(mRenderer);
}

// ゲーム終了処理
void Game::Shutdown()
{
	// レンダラー破棄
	SDL_DestroyRenderer(mRenderer);

	// ウィンドウ破棄
	SDL_DestroyWindow(mWindow);

	// SDL終了
	SDL_Quit();
}
