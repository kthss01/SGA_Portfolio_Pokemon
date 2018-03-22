#pragma once

#include "GameNode.h"

#include "Player.h"
#include "Pokemon.h"

#define PLAYER_SPEED 5.0f
#define POKEMON_COUNT 15

class TestScene : public GameNode
{
private:
	bool isDebug;
	//bool isToggle; // 필요 없어졌음
	bool isExit;

	Image * bg;

	float bgX, bgY;
	float speed;
	float distance;

	RECT exit;
	RECT temp;

	char str[128];

	Direction pattern[POKEMON_COUNT];

	Player player;
	Pokemon rattata[POKEMON_COUNT];
public:
	TestScene();
	~TestScene();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	void BgMove();
	void PlayerMove();
	void OtherMove(Direction dir);
	void PokemonIdle(Pokemon& pokemon, int maxNum);
	void PokemonMove(Pokemon& pokemon, int maxNum, 
		float speed, Direction dir, bool isStart = false);
};

