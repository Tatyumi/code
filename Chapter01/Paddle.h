#pragma once
class Paddle
{
	struct Vector2
	{
		float x;
		float y;
	};

public:
	// コンストラクタ
	Paddle();
	// デストラクタ
	~Paddle();
	// 更新処理
	void Update();

private:
	// 方向
	int mDir;
	// 座標
	Vector2 mPos;
	// 縦幅
	float mHeight;
	// 横幅
	float mWeight;
	// 移動速度
	float mMoveSpeed;
};

