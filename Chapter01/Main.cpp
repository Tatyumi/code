// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"

int main(int argc, char** argv)
{
	Game game;

	// ゲーム初期化結果
	bool success = game.Initialize();

	// 成功判別
	if (success)
	{
		// 成功した場合

		// ゲームループ
		game.RunLoop();
	}

	// ゲーム終了処理
	game.Shutdown();
	return 0;
}
