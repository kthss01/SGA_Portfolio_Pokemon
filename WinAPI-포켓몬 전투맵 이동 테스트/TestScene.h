#pragma once

#include "GameNode.h"

#include "Player2.h"

class TestScene : public GameNode
{
private:
	bool isDebug;

	Image * bg;
	Image * player;

	float x, y;
	char str[128];

	Player2 playerInfo;
public:
	TestScene();
	~TestScene();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	void PlayerMove();
};

