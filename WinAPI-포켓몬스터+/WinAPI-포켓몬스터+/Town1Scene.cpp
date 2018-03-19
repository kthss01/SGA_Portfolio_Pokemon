#include "stdafx.h"
#include "Town1Scene.h"


Town1Scene::Town1Scene()
{
}


Town1Scene::~Town1Scene()
{
}

HRESULT Town1Scene::Init()
{
	isDebug = false;

	bg = IMAGE->FindImage("Town1");
	bgPixel = IMAGE->FindImage("Town1Pixel");
	player = IMAGE->FindImage("Player");

	playerInfo.Init(DIRECTION_DOWN, WINSIZEX / 2, WINSIZEY / 2, 70, 100);
	playerInfo.SetMoveFrame(PLAYER_IDLE);

	bgX = -80;
	bgY = -114;

	sceneInfo[SCENE_EXIT].x = WINSIZEX / 2 + 75;
	sceneInfo[SCENE_EXIT].y = -270;
	sceneInfo[SCENE_EXIT].width = 180;
	sceneInfo[SCENE_EXIT].height = 50;
	sceneInfo[SCENE_EXIT].rc = RectMake(
		sceneInfo[SCENE_EXIT].x, sceneInfo[SCENE_EXIT].y, 
		sceneInfo[SCENE_EXIT].width, sceneInfo[SCENE_EXIT].height);

	return S_OK;
}

void Town1Scene::Release()
{
}

void Town1Scene::Update()
{
	PlayerMove();
	playerInfo.Probe(bgPixel, bgX, bgY, WINSIZEX / 2 + bgX, WINSIZEY / 2 + bgY);

	if (IntersectRect(&temp, &sceneInfo[SCENE_EXIT].rc, &playerInfo.GetRect())) {
		bgX = 45;
		bgY = -384;
		playerInfo.SetX(512);
		playerInfo.SetY(59);
		playerInfo.SetDirection(DIRECTION_DOWN);
		SCENE->ChangeScene("Town2");
	}

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_TAB)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void Town1Scene::Render()
{
	//=================================================
	{
		//bg->Render(GetMemDC());
		bg->Render(GetMemDC(), 0, 0, 
			WINSIZEX / 2 + bgX, WINSIZEY / 2 + bgY, WINSIZEX, WINSIZEY);
	}
	//==================   Debug   ====================
	if (isDebug)
	{
		bgPixel->Render(GetMemDC(), 0, 0,
			WINSIZEX / 2 + bgX, WINSIZEY / 2 + bgY, WINSIZEX, WINSIZEY);
		sprintf_s(str, "bg x,y %f %f", bgX, bgY);
		TextOut(GetMemDC(), 10, 10, str, strlen(str));
		sprintf_s(str, "player x,y %f %f", playerInfo.GetX(), playerInfo.GetY());
		TextOut(GetMemDC(), 10, 30, str, strlen(str));
		sprintf_s(str, "mouse : %d %d", g_ptMouse.x, g_ptMouse.y);
		TextOut(GetMemDC(), 10, 50, str, strlen(str));

		RectangleMake(GetMemDC(), sceneInfo[SCENE_EXIT].rc);
		RectangleMake(GetMemDC(), playerInfo.GetRect());
	}
	//=================================================

	player->FrameRender(GetMemDC(), playerInfo.GetX(), playerInfo.GetY(),
		playerInfo.GetMoveFrame(), playerInfo.GetDirection());
}

void Town1Scene::PlayerMove()
{
	// left
	if (INPUT->GetKeyDown(VK_LEFT)) {
		playerInfo.SetMoveFrame(0);
		playerInfo.SetDirection(DIRECTION_LEFT);
	}
	if (INPUT->GetKey(VK_LEFT)) {
		if (playerInfo.GetDirection() != DIRECTION_LEFT)
			playerInfo.SetDirection(DIRECTION_LEFT);

		playerInfo.AddMoveFrame(0.1f);
		
		//playerInfo.AddX(-2.5f);
		
		if (playerInfo.GetX() > WINSIZEX / 2) {
			playerInfo.AddX(-PLAYER_SPEED);
		}
		else {
			bgX -= PLAYER_SPEED;
			if (bgX > -WINSIZEX / 2)
				OtherMove(DIRECTION_RIGHT);
		}
		if (bgX < -WINSIZEX / 2) {
			bgX = -WINSIZEX / 2;
			playerInfo.AddX(-PLAYER_SPEED);
		}
		if ((int)playerInfo.GetMoveFrame() > 2)
			playerInfo.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_LEFT)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
	}

	// right
	if (INPUT->GetKeyDown(VK_RIGHT)) {
		playerInfo.SetMoveFrame(0);
		playerInfo.SetDirection(DIRECTION_RIGHT);
	}
	if (INPUT->GetKey(VK_RIGHT)) {
		if (playerInfo.GetDirection() != DIRECTION_RIGHT)
			playerInfo.SetDirection(DIRECTION_RIGHT);

		playerInfo.AddMoveFrame(0.1f);
		
		//playerInfo.AddX(2.5f);
		
		if (playerInfo.GetX() < WINSIZEX / 2) {
			playerInfo.AddX(PLAYER_SPEED);
		}
		else {
			bgX += PLAYER_SPEED;
			if (bgX < WINSIZEX / 2)
				OtherMove(DIRECTION_LEFT);
		}
		if (bgX > WINSIZEX / 2) {
			bgX = WINSIZEX / 2;
			playerInfo.AddX(PLAYER_SPEED);
		}
		if ((int)playerInfo.GetMoveFrame() > 2)
			playerInfo.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_RIGHT)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
	}

	// up
	if (INPUT->GetKeyDown(VK_UP)) {
		playerInfo.SetMoveFrame(0);
		playerInfo.SetDirection(DIRECTION_UP);
	}
	if (INPUT->GetKey(VK_UP)) {
		if (playerInfo.GetDirection() != DIRECTION_UP)
			playerInfo.SetDirection(DIRECTION_UP);

		playerInfo.AddMoveFrame(0.1f);
		//playerInfo.AddY(-2.5f);

		if (playerInfo.GetY() > WINSIZEY / 2) {
			playerInfo.AddY(-PLAYER_SPEED);
		}
		else {
			bgY -= PLAYER_SPEED;
			if (bgY > -WINSIZEY / 2)
				OtherMove(DIRECTION_DOWN);
		}
		if (bgY < -WINSIZEY / 2) {
			bgY = -WINSIZEY / 2;
			playerInfo.AddY(-PLAYER_SPEED);
		}
		if ((int)playerInfo.GetMoveFrame() > 2)
			playerInfo.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_UP)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
	}

	// down
	if (INPUT->GetKeyDown(VK_DOWN)) {
		playerInfo.SetMoveFrame(0);
		playerInfo.SetDirection(DIRECTION_DOWN);
	}
	if (INPUT->GetKey(VK_DOWN)) {
		if (playerInfo.GetDirection() != DIRECTION_DOWN)
			playerInfo.SetDirection(DIRECTION_DOWN);

		playerInfo.AddMoveFrame(0.1f);
		//playerInfo.AddY(2.5f);

		if (playerInfo.GetY() < WINSIZEY / 2) {
			playerInfo.AddY(PLAYER_SPEED);
		}
		else {
			bgY += PLAYER_SPEED;
			if (bgY < WINSIZEY / 2)
				OtherMove(DIRECTION_UP);
		}
		if (bgY > WINSIZEY / 2) {
			bgY = WINSIZEY / 2;
			playerInfo.AddY(PLAYER_SPEED);
		}
		if ((int)playerInfo.GetMoveFrame() > 2)
			playerInfo.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_DOWN)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
	}
}

void Town1Scene::OtherMove(Direction dir)
{
	switch (dir)
	{
	case DIRECTION_DOWN:
		sceneInfo[SCENE_EXIT].y += PLAYER_SPEED;
		break;
	case DIRECTION_UP:
		sceneInfo[SCENE_EXIT].y -= PLAYER_SPEED;
		break;
	case DIRECTION_LEFT:
		sceneInfo[SCENE_EXIT].x -= PLAYER_SPEED;
		break;
	case DIRECTION_RIGHT:
		sceneInfo[SCENE_EXIT].x += PLAYER_SPEED;
		break;
	}
	
	sceneInfo[SCENE_EXIT].rc = RectMake(
		sceneInfo[SCENE_EXIT].x, sceneInfo[SCENE_EXIT].y,
		sceneInfo[SCENE_EXIT].width, sceneInfo[SCENE_EXIT].height);
}
