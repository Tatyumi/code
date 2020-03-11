// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"

// ��
const int thickness = 15;
// �p�h���̍���
const float paddleH = 100.0f;
// �p�h���̉���
const float paddleW = 5.0;
// �E�B���h�E�������x���W
const int windowTopLeftXPos = 100;
// �E�B���h�E�������y���W
const int windowTopLeftYPos = 100;
// �E�B���h�E�̉���
const int windowWidth = 1024;
// �E�B���h�E�̏c��
const int windowHeight = 768;
// ����t���[����
const int limitFrame = 16;
// �f���^�^�C���̍ő�l
const float maxDeltaTime = 0.05f;
// �p�h���̈ړ����x
const int paddleMoveSpeed = 1;
// �{�[���̏������x
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

// ����������
bool Game::Initialize()
{
	// SDL���C�u����(�r�f�I�T�u�V�X�e��)��������
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	// ����������������������
	if (sdlResult != 0)
	{
		// ���s�����ꍇ

		// ���O�o��
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// SDL�E�B���h�E����
	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)", // Window title
		windowTopLeftXPos,	// Top left x-coordinate of window
		windowTopLeftYPos,	// Top left y-coordinate of window
		windowWidth,	// Width of window
		windowHeight,	// Height of window
		0		// Flags (0 for no flags set)
	);

	// �E�B���h�E�̌Ăяo������������������
	if (!mWindow)
	{
		// ���s�����ꍇ

		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	//// �����_���[����
	mRenderer = SDL_CreateRenderer(
		mWindow, // �`��Ώۂ̃E�B���h�E�̃|�C���^
		-1,		 // �ʏ�� -1�i�E�B���h�E�����w�肷����̂ŁA1�̏ꍇ-1�ƂȂ�j
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // �������t���O
	);

	// �����_���[��������������������
	if (!mRenderer)
	{
		// ���s�����ꍇ

		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	// �p�h���̏������W
	mPaddlePos.x = 10.0f;
	mPaddlePos.y = windowHeight / 2.0f;

	// 2P�p�h���̏������W
	mPaddle2Pos.x = windowWidth - thickness;
	mPaddle2Pos.y = mPaddlePos.y;

	// �{�[���̃p�����[�^(���W�A���x)
	mBallPos.x = windowWidth / 2.0f;
	mBallPos.y = windowHeight / 2.0f;
	mBallVel.x = iniBallXVel;
	mBallVel.y = iniBallYVel;
	return true;
}

// �Q�[�����[�v
void Game::RunLoop()
{
	// �J��Ԃ����s���邩����
	while (mIsRunning)
	{
		// ���s��

		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

// ���͏���
void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		// �C�x���g�̃^�C�v����
		switch (event.type)
		{
			// �E�B���h�E������ꍇ
			// �u�~�v���N���b�N�AAlt+F4�Ȃ�
			case SDL_QUIT:

				// ���[�v�I��
				mIsRunning = false;
				break;
		}
	}

	// �L�[�{�[�h�̏�Ԋi�[�z��
	const Uint8* state = SDL_GetKeyboardState(NULL);

	// �uEsc�v�������ꂽ������
	if (state[SDL_SCANCODE_ESCAPE])
	{
		// ���[�v�I��
		mIsRunning = false;
	}

	// Update paddle direction based on W/S keys
	mPaddleDir = 0;

	// ���͔���
	if (state[SDL_SCANCODE_W])
	{
		// �uw�v�������ꂽ�ꍇ

		// ����
		mPaddleDir -= paddleMoveSpeed;
	}
	if (state[SDL_SCANCODE_S])
	{
		// �us�v�������ꂽ�ꍇ

		// ����
		mPaddleDir += paddleMoveSpeed;
	}

	mPaddle2Dir = 0;

	// ���͔���
	if (state[SDL_SCANCODE_I])
	{
		// �uI�v�������ꂽ�ꍇ

		mPaddle2Dir -= paddleMoveSpeed;
	}
	if (state[SDL_SCANCODE_K])
	{
		// �uK�v�������ꂽ�ꍇ

		mPaddle2Dir += paddleMoveSpeed;
	}

}

void Game::UpdateGame()
{
	// �O�t���[������w��̏���l���o�߂��Ă��邩����
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + limitFrame))
		;

	// �Ō�̃t���[������o�߂�������(deltaTime)���擾
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// �f���^�^�C���̍ő�l�𒴂���������
	// �t���[�����[�g���͂邩��ɐi�܂Ȃ�����
	if (deltaTime > maxDeltaTime)
	{
		// �������ꍇ

		// �ő�l�̑��
		deltaTime = maxDeltaTime;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();

	// �p�h���̈ړ�����
	if (mPaddleDir != 0)
	{
		// �ړ��A�܂�w��̓��͂��������ꍇ

		// y���W(�c��)�ł̒l�X�V
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;

		// �p�h������ʓ��ɐ���
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))
		{
			// ��ʏ㕔�ɒB�����ꍇ

			mPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlePos.y > (windowHeight - paddleH / 2.0f - thickness))
		{
			// ��ʉ����ɒB�����ꍇ

			mPaddlePos.y = windowHeight - paddleH / 2.0f - thickness;
		}
	}

	// 2P�p�h���̈ړ�����
	if (mPaddle2Dir != 0)
	{
		// �ړ��A�܂�w��̓��͂��������ꍇ

		// y���W(�c��)�ł̒l�X�V
		mPaddle2Pos.y += mPaddle2Dir * 300.0f * deltaTime;

		// �p�h������ʓ��ɐ���
		if (mPaddle2Pos.y < (paddleH / 2.0f + thickness))
		{
			// ��ʏ㕔�ɒB�����ꍇ

			mPaddle2Pos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddle2Pos.y > (windowHeight - paddleH / 2.0f - thickness))
		{
			// ��ʉ����ɒB�����ꍇ

			mPaddle2Pos.y = windowHeight - paddleH / 2.0f - thickness;
		}
	}

	// �{�[���̈ʒu���X�V
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	// �p�h���ƃ{�[����y���W�̋������擾
	float diffPaddleAndBall = mPaddlePos.y - mBallPos.y;
	float diffPaddle2AndBall = mPaddle2Pos.y - mBallPos.y;

	// �����̐�Βl���擾
	diffPaddleAndBall = (diffPaddleAndBall > 0.0f) ? diffPaddleAndBall : -diffPaddleAndBall;
	diffPaddle2AndBall = (diffPaddle2AndBall > 0.0f) ? diffPaddle2AndBall : -diffPaddle2AndBall;

	float paddleCollisionXPos = thickness + mPaddlePos.x;
	float paddle2CollisionXPos =  mPaddle2Pos.x - thickness;

	if (// ���̋������p�h����菬����
		diffPaddleAndBall <= paddleH / 2.0f &&
		// �{�[����x���W���p�h���ɐڐG���Ă���
		mBallPos.x <= paddleCollisionXPos && mBallPos.x >= paddleCollisionXPos - paddleW &&
		// �{�[�����������ɐi��ł���
		mBallVel.x < 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	else if (// ���̋�����2P�p�h����菬����
		diffPaddle2AndBall <= paddleH / 2.0f &&
		// �{�[����x���W��2P�p�h���ɐڐG���Ă���
		mBallPos.x <= paddle2CollisionXPos && mBallPos.x >= paddle2CollisionXPos - paddleW &&
		// �{�[�����E�����ɐi��ł���
		mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	// Did the ball go off the screen? (if so, end game)
	else if (mBallPos.x <= 0.0f)
	{
		mIsRunning = false;
	}
	// ��ʉE���Ƀ{�[�����o���ꍇ
	else if (mBallPos.x >= windowWidth)
	{
		mIsRunning = false;
	}

	// �㉺�̕ǂ̏Փ˔���
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		// ��̕ǂɏՓ˂��A���{�[����������ɐi��ł���ꍇ

		// �c�����𔽓]
		mBallVel.y *= -1;
	}
	else if (mBallPos.y >= (windowHeight - thickness) &&
		mBallVel.y > 0.0f)
	{
		// ���̕ǂɏՓ˂��A���{�[�����������ɐi��ł���ꍇ

		// �c�����𔽓]
		mBallVel.y *= -1;
	}
}

// �o�͐���
void Game::GenerateOutput()
{
	// ��`��
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G 
		255,	// B
		255		// A
	);

	// �o�b�N�o�b�t�@��ŃN���A
	SDL_RenderClear(mRenderer);

	// ���̕�
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	// ��ʏ㕔�̕�
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		windowWidth,		// Width
		thickness	// Height
	};

	// �E�B���h�E�ɕǂ̕`��
	SDL_RenderFillRect(mRenderer, &wall);

	// ��ʉ����̕ǂ̂��߂�y���W
	wall.y = windowHeight - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	// �p�h���̕`��
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	// 2P�p�h���̕`��
	paddle.x = static_cast<int>(mPaddle2Pos.x - thickness);
	paddle.y = static_cast<int>(mPaddle2Pos.y - paddleH / 2);
	SDL_RenderFillRect(mRenderer, &paddle);

	// �{�[���̕`��
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	// �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@������
	SDL_RenderPresent(mRenderer);
}

// �Q�[���I������
void Game::Shutdown()
{
	// �����_���[�j��
	SDL_DestroyRenderer(mRenderer);

	// �E�B���h�E�j��
	SDL_DestroyWindow(mWindow);

	// SDL�I��
	SDL_Quit();
}
