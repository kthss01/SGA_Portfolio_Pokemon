#pragma once

#include "GameNode.h"

#include "Player.h"

#define PLAYER_SPEED 5.0f

enum ChangeSceneStatus2 {
	SCENE2_EXIT,
	SCENE2_SHOP,
	SCENE2_END
};

struct tagChangeSceneInfo2 {
	RECT rc;
	float x, y;
	float width, height;
};

class Town2Scene : public GameNode
{
private:
	bool isDebug;

	Image* bg;
	Image* bgPixel;
	Image* player;

	Player playerInfo;

	tagChangeSceneInfo2 sceneInfo[SCENE2_END];

	float bgX, bgY;
	char str[128];
	RECT temp;
public:
	Town2Scene();
	~Town2Scene();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	void PlayerMove();
	void OtherMove(Direction dir);
};

