// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SDL/SDL.h"

// Vector2 struct just stores x/y coordinates
// (for now)
struct Vector2
{
	float x;
	float y;
};

// Game class
class Game
{
public:
	Game();
	// Initialize the game
	bool Initialize();
	// Runs the game loop until the game is over
	void RunLoop();
	// Shutdown the game
	void Shutdown();
private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// Window created by SDL
	SDL_Window* mWindow;
	// Renderer for 2D drawing
	SDL_Renderer* mRenderer;
	// �Q�[���J�n����̌o�ߎ���
	Uint32 mTicksCount;
	// Game should continue to run
	bool mIsRunning;
	
	// Pong specific
	// �p�h���̕���
	int mPaddleDir;
	// �p�h���̍��W
	Vector2 mPaddlePos;

	// 2P�̃p�h���̕���
	int mPaddle2Dir;
	// 2P�̃p�h���̍��W
	Vector2 mPaddle2Pos;

	// �{�[���̍��W
	Vector2 mBallPos;
	// �{�[���̑��x
	Vector2 mBallVel;
};
