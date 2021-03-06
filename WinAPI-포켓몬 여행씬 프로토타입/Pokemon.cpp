#include "stdafx.h"
#include "Pokemon.h"


Pokemon::Pokemon()
{
	m_equipItem.itemKind = ITEM_EMPTY;
	num = 0;
	isDied = false;
	alpha = 255;
}


Pokemon::~Pokemon()
{
	delete[] ani;
}

void Pokemon::EquipItem(int num)
{
	if (num == -1) {
		tagItemInfo beforeItem;
		beforeItem = GetEquipItem();

		tagItemInfo emptyItem;
		emptyItem.itemKind = ITEM_EMPTY;
		SetEquipItem(emptyItem);

		if (beforeItem.itemKind != ITEM_EMPTY)
			GAME->GetInventory().AddItem(beforeItem);
	}
	else {
		tagItemInfo beforeItem;
		//m_viItem = m_vItem.begin() + num;

		beforeItem = GetEquipItem();
		//SetEquipItem(*m_viItem);
		SetEquipItem(GAME->GetInventory().GetItem(num));
		//m_vItem.erase(m_viItem);
		GAME->GetInventory().DeleteItem(num);
		if (beforeItem.itemKind != ITEM_EMPTY)
			GAME->GetInventory().AddItem(beforeItem);
	}
}

void Pokemon::InitAni(int num)
{
	this->num = num;
	ani = new Image*[num];
}
