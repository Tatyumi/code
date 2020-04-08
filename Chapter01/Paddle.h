#pragma once
class Paddle
{
	struct Vector2
	{
		float x;
		float y;
	};

public:
	// �R���X�g���N�^
	Paddle();
	// �f�X�g���N�^
	~Paddle();
	// �X�V����
	void Update();

private:
	// ����
	int mDir;
	// ���W
	Vector2 mPos;
	// �c��
	float mHeight;
	// ����
	float mWeight;
	// �ړ����x
	float mMoveSpeed;
};

