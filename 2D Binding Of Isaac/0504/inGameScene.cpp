#include "stdafx.h"
#include "inGameScene.h"

HRESULT inGameScene::init()
{
	//백그라운드 이미지 초기화
	//IMAGEMANAGER->addImage("백그라운드", "Images/background.bmp", WINSIZEX, WINSIZEY);
	//UFO 프레임 이미지 초기화
	//IMAGEMANAGER->addFrameImage("ufo", "Images/ufo.bmp", 530, 32, 10, 1);
	//총알 이미지
	//IMAGEMANAGER->addImage("bullet", "Images/bullet.bmp", 21, 21);
	miniMap = RectMake(WINSIZEX - 140, 15, 106, 94);
	itemstone = RectMakeCenter(WINSIZEX / 2 - 48, WINSIZEY / 2 +25, 54, 46);
	item = RectMakeCenter(WINSIZEX / 2 - 46, WINSIZEY / 2-15, 54, 46);
	room2item = false;
	count = 0;
	itemY = 40;
	itemy = false;

	for (int i = 0; i < 31; i++)
	{
		_map[i].clear = false;
		_map[i].mapNum = i;
		_map[i].open = false;
		_map[i].rc = RectMakeCenter(miniMap.left + (miniMap.right - miniMap.left) + (i % 10) * 18, 5 + (miniMap.bottom - miniMap.top) + (i / 10) * 16, 18, 16);
		if (i == 2 || i == 4 || i == 5 || i == 10 || i == 11 || i == 12 || i == 13 || i == 14 || i == 20 || i == 22 || i == 24 || i == 30) { _map[i].haveMap = true; }
		else { _map[i].haveMap = false; }
	}
	_map[30].rc.right += 18;
	_map[30].rc.bottom += 16;
	_overMap.clear = true;
	_overMap.haveMap = true;
	_overMap.mapNum = 34;
	_overMap.open = false;
	//플레이어 클래스 초기화
	_player = new player;
	_player->init();

	//적매니져 클래스 초기화
	_enemyManager = new enemyManager;
	_enemyManager->init();

	//상호참조
	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);
	mapNum = 11;
	_enemyManager->setMapNum(mapNum);
	_rcScreen = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 960, 540);
	mapSetting(mapNum);

	return S_OK;
}

void inGameScene::release()
{
	//플레이어 클래스 해제
	//_player->release();
	//SAFE_DELETE(_player);

	//적매니져 클래스 해제
	//_enemyManager->release();
	//SAFE_DELETE(_enemyManager);
}

void inGameScene::update()
{
	count++;

	if (mapNum == 2 && room2item == false) { itemstone = RectMakeCenter(-500,-500, 54, 46); }
	else if (mapNum == 2 && room2item == true) { itemstone = RectMakeCenter(WINSIZEX / 2 - 96, WINSIZEY / 2 + 25, 54, 46); }
	else if (mapNum == 14 && _map[14].clear == false) { itemstone = RectMakeCenter(-500, -500, 54, 46); }
	else { itemstone = RectMakeCenter(WINSIZEX / 2 - 48, WINSIZEY / 2+25, 54, 46); }
	
	item = itemstone;
	
	item.top -= itemY;
	item.bottom -= itemY;

	
	if (count % 6 == 0) 
	{
		if (itemy == false)
		{
			if (itemY > 40) { itemy = true; }
			itemY += 2; 
		}
		else if (itemy == true)
		{
			if (itemY < 34) { itemy = false; }
			itemY -= 2;
		}
	}
	_rcScreen = RectMakeCenter(WINSIZEX / 2 + _player->getCameraX(), WINSIZEY / 2 + _player->getCameraY(), 980, 560);
	_enemyManager->setMapNum(mapNum);
	
	//RECT rc;
	//for (int i = 0; i < TILEX*TILEY; i++)
	//{
	//	if (IntersectRect(&rc, &_player->getPlayerbody(), &_tiles[i].rc) && _tiles[i]._type == OBJECT)
	//	{
	//		if (_tiles[i].rc.left < _player->getPlayerbody().right && INPUT->GetKey('D')) { _player->move(6,_tiles[i].rc.left); }
	//		if (_tiles[i].rc.right > _player->getPlayerbody().left && INPUT->GetKey('A')) { _player->move(4,_tiles[i].rc.right); }
	//		if (_tiles[i].rc.top < _player->getPlayerbody().bottom && INPUT->GetKey('W')) { _player->move(8,_tiles[i].rc.bottom); }
	//		if (_tiles[i].rc.bottom > _player->getPlayerbody().top && INPUT->GetKey('S')) { _player->move(2,_tiles[i].rc.top); }
	//		break;
	//	}
	//}


	RECT rc;
	int crushX;
	int crushY;
	
		//if (INPUT->GetKey('W'))
		{
			crush = RectMakeCenter(_player->getPlayerbody().left + 18, _player->getPlayerbody().top - _player->getSpeed()  + 13, 24, 8);
			crushX = (crush.left + (crush.right - crush.left)) / 48;
			crushY = (crush.top + (crush.bottom - crush.top)) / 45;
			for (int i = 0; i < 2; i++)
			{
				if (IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*crushY) + i].rc) && _tiles[crushX + ((right / 48)*crushY) + i]._type == OBJECT || IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*crushY) + i].rc) && _tiles[crushX + ((right / 48)*crushY) + i]._type == LOCKEDDOOR)
				{
					//if (_tiles[i].rc.bottom > _player->getPlayerbody().top)
					//{
					if (_tiles[crushX + ((right / 48)*crushY) + i]._type == LOCKEDDOOR) { this->openDoor(crushX + ((right / 48)*crushY) + i); }
					_player->move(8);
					break;
					//}
				}
				if (IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*(crushY + 1) + i)].rc) && _tiles[crushX + ((right / 48)*(crushY + 1) + i)]._type == OBJECT || IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*(crushY + 1) + i)].rc) && _tiles[crushX + ((right / 48)*(crushY + 1) + i)]._type == LOCKEDDOOR)
				{
					//if (_tiles[i].rc.bottom > _player->getPlayerbody().top)
					//{
					if (_tiles[crushX + ((right / 48)*crushY) + i]._type == LOCKEDDOOR) { this->openDoor(crushX + ((right / 48)*crushY + 1) + i); }
					_player->move(8);
					break;
					//}
				}
				if (!(_enemyManager->getMinion().empty()))
				{
					if (IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*crushY) + i].rc) && _tiles[crushX + ((right / 48)*crushY) + i]._type == DOOR)
					{
						_player->move(8);
						break;
					}
				}
				if (!(_enemyManager->getMinion().empty()))
				{
					if (IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*(crushY + 1) + i)].rc) && _tiles[crushX + ((right / 48)*(crushY + 1) + i)]._type == DOOR)
					{
						_player->move(8);
						break;
					}
				}
			}
		}
		//if (INPUT->GetKey('S'))
		{
			crush = RectMakeCenter(_player->getPlayerbody().left + 18, _player->getPlayerbody().bottom+ _player->getSpeed(), 24, 8);
			crushX = (crush.left + (crush.right - crush.left)) / 48;
			crushY = (crush.top + (crush.bottom - crush.top)) / 45;
			for (int i = 0; i < 2; i++)
			{
				if (IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*crushY) + i].rc) && _tiles[crushX + ((right / 48)*crushY) + i]._type == OBJECT || IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*crushY) + i].rc) && _tiles[crushX + ((right / 48)*crushY) + i]._type == LOCKEDDOOR)
				{
					//if (_tiles[i].rc.bottom > _player->getPlayerbody().top)
					//{
					if (_tiles[crushX + ((right / 48)*crushY) + i]._type == LOCKEDDOOR) { this->openDoor(crushX + ((right / 48)*crushY) + i); }
					_player->move(2);
					break;
					//}
				}
				if (IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*(crushY + 1) + i)].rc) && _tiles[crushX + ((right / 48)*(crushY + 1) + i)]._type == OBJECT || IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*(crushY + 1) + i)].rc) && _tiles[crushX + ((right / 48)*(crushY + 1) + i)]._type == LOCKEDDOOR)
				{
					//if (_tiles[i].rc.bottom > _player->getPlayerbody().top)
					//{
					if (_tiles[crushX + ((right / 48)*crushY) + i]._type == LOCKEDDOOR) { this->openDoor(crushX + ((right / 48)*crushY + 1) + i); }
					_player->move(2);
					break;
					//}
				}
				if (!(_enemyManager->getMinion().empty()))
				{
					if (IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*crushY) + i].rc) && _tiles[crushX + ((right / 48)*crushY) + i]._type == DOOR)
					{
						_player->move(2);
						break;
					}
				}
				if (!(_enemyManager->getMinion().empty()))
				{
					if (IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*(crushY + 1) + i)].rc) && _tiles[crushX + ((right / 48)*(crushY + 1) + i)]._type == DOOR)
					{
						_player->move(2);
						break;
					}
				}
			}
		}
		//if (INPUT->GetKey('D'))
		{
			crush = RectMakeCenter(_player->getPlayerbody().right + _player->getSpeed(), _player->getPlayerbody().top + 36, 8, 20);
			crushX = (crush.left + (crush.right - crush.left)) / 48;
			crushY = (crush.top + (crush.bottom - crush.top)) / 45;
			for (int i = 0; i < 2; i++)
			{
				if (IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*crushY) + i].rc) && _tiles[crushX + ((right / 48)*crushY) + i]._type == OBJECT || IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*crushY) + i].rc) && _tiles[crushX + ((right / 48)*crushY) + i]._type == LOCKEDDOOR)
				{
					//if (_tiles[i].rc.bottom > _player->getPlayerbody().top)
					//{
					if (_tiles[crushX + ((right / 48)*crushY) + i]._type == LOCKEDDOOR) { this->openDoor(crushX + ((right / 48)*crushY) + i); }
					_player->move(6);
					break;
					//}
				}
				if (IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*(crushY + 1) + i)].rc) && _tiles[crushX + ((right / 48)*(crushY + 1) + i)]._type == OBJECT || IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*(crushY + 1) + i)].rc) && _tiles[crushX + ((right / 48)*(crushY + 1) + i)]._type == LOCKEDDOOR)
				{
					//if (_tiles[i].rc.bottom > _player->getPlayerbody().top)
					//{
					if (_tiles[crushX + ((right / 48)*crushY) + i]._type == LOCKEDDOOR) { this->openDoor(crushX + ((right / 48)*crushY + 1) + i); }
					_player->move(6);
					break;
					//}
				}
				if (!(_enemyManager->getMinion().empty()))
				{
					if (IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*crushY) + i].rc) && _tiles[crushX + ((right / 48)*crushY) + i]._type == DOOR)
					{
						_player->move(6);
						break;
					}
				}
				if (!(_enemyManager->getMinion().empty()))
				{
					if (IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*(crushY + 1) + i)].rc) && _tiles[crushX + ((right / 48)*(crushY + 1) + i)]._type == DOOR)
					{
						_player->move(6);
						break;
					}
				}
			}
		}
		//if (INPUT->GetKey('A'))
		{
			crush = RectMakeCenter(_player->getPlayerbody().left- _player->getSpeed(), _player->getPlayerbody().top + 36, 8, 20);
			crushX = (crush.left + (crush.right - crush.left)) / 48;
			crushY = (crush.top + (crush.bottom - crush.top)) / 45;
			for (int i = 0; i < 2; i++)
			{
				if (IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*crushY) + i].rc) && _tiles[crushX + ((right / 48)*crushY) + i]._type == OBJECT || IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*crushY) + i].rc) && _tiles[crushX + ((right / 48)*crushY) + i]._type == LOCKEDDOOR)
				{
					//if (_tiles[i].rc.bottom > _player->getPlayerbody().top)
					//{
					if (_tiles[crushX + ((right / 48)*crushY) + i]._type == LOCKEDDOOR) { this->openDoor(crushX + ((right / 48)*crushY) + i); }
					_player->move(4);
					break;
					//}
				}
				if (IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*(crushY + 1) + i)].rc) && _tiles[crushX + ((right / 48)*(crushY + 1) + i)]._type == OBJECT || IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*(crushY + 1) + i)].rc) && _tiles[crushX + ((right / 48)*(crushY + 1) + i)]._type == LOCKEDDOOR)
				{
					//if (_tiles[i].rc.bottom > _player->getPlayerbody().top)
					//{
					if (_tiles[crushX + ((right / 48)*crushY) + i]._type == LOCKEDDOOR) { this->openDoor(crushX + ((right / 48)*crushY + 1) + i); }
					_player->move(4);
					break;
					//}
				}
				if (!(_enemyManager->getMinion().empty()))
				{
					if (IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*crushY) + i].rc) && _tiles[crushX + ((right / 48)*crushY) + i]._type == DOOR)
					{
						_player->move(4);
						break;
					}
				}
				if (!(_enemyManager->getMinion().empty()))
				{
					if (IntersectRect(&rc, &crush, &_tiles[crushX + ((right / 48)*(crushY + 1) + i)].rc) && _tiles[crushX + ((right / 48)*(crushY + 1) + i)]._type == DOOR)
					{
						_player->move(4);
						break;
					}
				}

			}
		}



		//적매니져 업데이트
		_enemyManager->update();
		//플레이어 클래스 업데이트
		_player->update(_tiles[TILEX*TILEY - 1].rc.right, _tiles[TILEX*TILEY - 1].rc.bottom);

		if (_player->getBullet()->getBullet().size() > 0 && _player->getOuijaBoard() ==false)
		{

			for (int i = 0; i < _player->getBullet()->getBullet().size(); i++)
			{
				int x = _player->getBullet()->getBullet()[i].x / 48;
				int y = _player->getBullet()->getBullet()[i].y / 45;

				if (_tiles[x + ((right / 48)*y)]._type == OBJECT) { _player->getBullet()->removeBullet(i); }
			}
		}

		for (int i = 0; i < (right / 48)*TILEY; i++)
		{
			RECT PB;
			PB = _player->getPlayerbody();
			PB.top += 36;
			PB.left += 3;
			PB.right -= 3;
			if (IntersectRect(&rc, &PB, &_tiles[i].rc) && _tiles[i]._type == HITOBJECT)
			{
				_player->hitDamage(1);
				if ( mapNum ==2 )
				{
					int a = RANDOM->Range(1, 3);
					if (a == 2) { room2item = true; }
				}
				break;
			}
			//if (IntersectRect(&rc, &_player->getPlayerbody(), &_tiles[i].rc) && _tiles[i]._type == DOOR)
			if (PtInRect(&_tiles[i].rc, PointMake(_player->getCX(), _player->getCY())) && _tiles[i]._type == DOOR)
			{
				if (_player->getCY() > 150 && _player->getCY() < WINSIZEY - 150)
				{

					if (_player->getPlayerRect().right < _tiles[i].rc.right)
					{
						sprintf(_dataName, "save%d.mapsave", mapNum+1);
						save(_dataName);
						mapNum += 1;
						mapSetting(mapNum);
						for (int k = 0; k < 1000; k++)
						{
							_player->move(6);
							if (_player->getCX() < 150) 
							{
								_player->move(4);
								break; 
							}
						}

					}
					if (_player->getPlayerRect().left > _tiles[i].rc.left)
					{
						sprintf(_dataName, "save%d.mapsave", mapNum+1);
						save(_dataName);
						mapNum -= 1;
						mapSetting(mapNum);

						for (int k = 0; k < 1000; k++)
						{
							_player->move(4);
							if (_player->getCX() > right - 150) 
							{
								_player->move(6);
								break; 
							}
						}
					}
				}
				else
				{
					if (_player->getPlayerRect().bottom > _tiles[i].rc.bottom)
					{
						sprintf(_dataName, "save%d.mapsave", mapNum+1);
						save(_dataName);
						mapNum -= 10;
						mapSetting(mapNum);
						for (int k = 0; k < 1000; k++)
						{
							_player->move(8);
							if (_player->getCY() > _tiles[TILEX*TILEY - 1].rc.bottom - 95) 
							{
								_player->move(2);
								break; 
							}
						}

					}
					else if (_player->getPlayerRect().top < _tiles[i].rc.top)
					{
						sprintf(_dataName, "save%d.mapsave", mapNum+1);
						save(_dataName);
						mapNum += 10;
						mapSetting(mapNum);
						for (int k = 0; k < 1000; k++)
						{
							_player->move(2);
							if (_player->getCY() < 95) 
							{
								_player->move(8);
								break; 
							}
						}

					}
				}
				

				if (mapNum == 5 && _map[mapNum].clear==false)
				{
					_enemyManager->setDuke();
					_enemyManager->setFly(WINSIZEX / 2, 150);
				}
				else if (mapNum == 12 && _map[mapNum].clear == false)
				{
					_enemyManager->setFly(200, 150);
					_enemyManager->setFly(800, 150);
					_enemyManager->setFly(200, 350);
					_enemyManager->setFly(800, 350);
				}
				else if (mapNum == 14 &&_map[mapNum].clear == false)
				{
					_enemyManager->setRace(300,250);
					_enemyManager->setRace(300,250);
					_enemyManager->setRace(300,250);
				}
				else if (mapNum == 24 &&_map[mapNum].clear == false)
				{
					_enemyManager->setblast(400, 300);
				}
			}



			
				if (_tiles[i].rc.left > 90 && _tiles[i].rc.right < right - 90 && _tiles[i].rc.top >85 && _tiles[i].rc.bottom < _tiles[TILEX*TILEY - 1].rc.bottom - 85)
				{
					for (int j = 0; j < _player->getBomb()->getBullet().size(); j++)
					{
						if (_player->getBomb()->getBullet()[j]._imageSwitching == 17 || _player->getBomb()->getBullet()[j]._imageSwitching == 18)
						{
							RECT _explosion;
							_explosion = _player->getBomb()->getBullet()[j].rc;

							_explosion.left += 15;
							_explosion.right -= 15;
							_explosion.top += 65;

							if (IntersectRect(&rc, &_explosion, &_tiles[i].rc) && _tiles[i]._type == OBJECT)
							{
								_tiles[i]._type = TILE;
								_tiles[i].imagePage[1] = -1;

							}
						}
						
					}
				}
			


		}
		for (int i = 0; i < _player->getBomb()->getBullet().size(); i++)
		{
			if (mapNum > 31&& _player->getBomb()->getBullet()[i]._imageSwitching == 20) { _overMap._afterbomb.push_back(PointMake(_player->getBomb()->getBullet()[i].rc.left, _player->getBomb()->getBullet()[i].y + 5)); }
			else 
			{
				if (_player->getBomb()->getBullet()[i]._imageSwitching == 20)
				{
					_map[mapNum]._afterbomb.push_back(PointMake(_player->getBomb()->getBullet()[i].rc.left, _player->getBomb()->getBullet()[i].y + 5));
				}
			}
		}

		if (mapNum == 10)
		{
			for (int i = 0; i < _enemyManager->getObject().size(); i++)
			{
				if (_enemyManager->getObject()[i]->getHp() > 0) { _tiles[_enemyManager->getObject()[i]->getFrameX()]._type = OBJECT; }
				else if (_enemyManager->getObject()[i]->getHp() <= 0) { _tiles[_enemyManager->getObject()[i]->getFrameX()]._type = TILE;  }		

				if (_enemyManager->getObject()[i]->getHp() > 0 && _enemyManager->getObject()[i]->getName() == FIRE) 
				{
					RECT cRc;
					cRc = _tiles[_enemyManager->getObject()[i]->getFrameX()].rc;
					cRc.top -= 10;
					cRc.left -= 10;
					if (IntersectRect(&rc, &_player->getPlayerbody(), &cRc))
					{
						_player->hitDamage(1);
					}
				}
			}
		}

		if (IntersectRect(&rc, &_player->getPlayerRect(), &itemstone))
		{
			if (mapNum == 2 && _player->getItem(2) == false) { _player->pickUpSadbBmb(); }
			else if (mapNum == 10 && _player->getItem(1) == false) { _player->pickUpTearDetonator(); }
			else if (mapNum == 14 && _player->getItem(3) == false) { _player->pickUpOuijaBoard(); }
			else if (mapNum == 22 && _player->getItem(5) == false) { _player->pickUpQuarter(); }
			else if (mapNum == 34 && _player->getItem(4) == false) { _player->pickUpLotus(); }
		}

		for (int i = 0; i < 31; i++)
		{
			if (_map[i].haveMap == true && _map[i].clear == false && _enemyManager->getMinion().empty() &&_map[i].open == true)
			{
				_map[i].clear = true;
			}
		}
	

	if (INPUT->GetKeyDown(VK_RETURN))
	{
		SCENEMANAGER->loadScene("시작화면");
	}
	if (INPUT->GetKeyDown(VK_NUMPAD0))
	{
		mapSetting(0);
		//int start;
		//start = (WINSIZEX - _tiles[0].rc.left - _tiles[TILEX-1].rc.right);
		//if (start < 0) { start = 0; }
		//for (int i = 0; i < TILEX * TILEY; i++)
		//{
		//	if (_tiles[i].imagePage[0] == -1) { start = -100; }
		//	_tiles[i].rc.left += start/2;
		//	_tiles[i].rc.right += start / 2;
		//}
	}
	if (INPUT->GetKeyDown(VK_NUMPAD2))
	{
		mapSetting(2);
		//int start;
		//start = 0;
		//if (start < 0) { start = 0; }
		//for (int i = 0; i < TILEX * TILEY; i++)
		//{
		//	if (_tiles[i].imagePage[0] == -1) { start = -100; }
		//	_tiles[i].rc.left += start / 2;
		//	_tiles[i].rc.right +=start / 2;
		//}
	}
	if (INPUT->GetKeyDown(VK_NUMPAD1))
	{
		mapSetting(1);
		//int start;
		//start = (WINSIZEX - _tiles[0].rc.left - _tiles[TILEX-1].rc.right);
		//if (start < 0) { start = 0; }
		//for (int i = 0; i < TILEX * TILEY; i++)
		//{
		//	if (_tiles[i].imagePage[0] == -1) { start = -100; }
		//	_tiles[i].rc.left += start / 2;
		//	_tiles[i].rc.right += start / 2;
		//}
	}

}

void inGameScene::render()
{

	//백그라운드 렌더
	//IMAGEMANAGER->render("백그라운드", getMemDC());
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_rcScreen, &_tiles[i].rc))
		{
			if (_tiles[i].imagePage[0] == -1)
			{
				//Rectangle(getMemDC(), _tiles[i].rc);
				//sprintf_s(_fileName, "map%d", _tiles[i].imagePage[1]);
				//IMAGEMANAGER->frameRender(_fileName, getMemDC(), _tiles[i].rc.left-_player->getCameraX(), _tiles[i].rc.top - _player->getCameraY(), _tiles[i].tileFrameX[1], _tiles[i].tileFrameY[1]);

			}
			else if (_enemyManager->getMinion().empty())
			{
				sprintf_s(_fileName, "map%d", _tiles[i].imagePage[0]);
				IMAGEMANAGER->frameRender(_fileName, getMemDC(), _tiles[i].rc.left - _player->getCameraX(), _tiles[i].rc.top - _player->getCameraY(), _tiles[i].tileFrameX[0], _tiles[i].tileFrameY[0]);
				if (_tiles[i]._type != TILE)
				{
					sprintf_s(_fileName, "map%d", _tiles[i].imagePage[1]);
					IMAGEMANAGER->frameRender(_fileName, getMemDC(), _tiles[i].rc.left - _player->getCameraX(), _tiles[i].rc.top - _player->getCameraY(), _tiles[i].tileFrameX[1], _tiles[i].tileFrameY[1]);
					if (_tiles[i]._type == LOCKEDDOOR)
					{
						sprintf_s(_fileName, "map%d", _tiles[i].imagePage[2]);
						IMAGEMANAGER->frameRender(_fileName, getMemDC(), _tiles[i].rc.left - _player->getCameraX(), _tiles[i].rc.top - _player->getCameraY(), _tiles[i].tileFrameX[2], _tiles[i].tileFrameY[2]);
					}
				}
			}
			else if (!(_enemyManager->getMinion().empty()))
			{
				sprintf_s(_fileName, "map%d", _tiles[i].imagePage[0]);
				IMAGEMANAGER->frameRender(_fileName, getMemDC(), _tiles[i].rc.left - _player->getCameraX(), _tiles[i].rc.top - _player->getCameraY(), _tiles[i].tileFrameX[0], _tiles[i].tileFrameY[0]);
				if (_tiles[i]._type != TILE)
				{
					sprintf_s(_fileName, "map%d", _tiles[i].imagePage[2]);
					IMAGEMANAGER->frameRender(_fileName, getMemDC(), _tiles[i].rc.left - _player->getCameraX(), _tiles[i].rc.top - _player->getCameraY(), _tiles[i].tileFrameX[2], _tiles[i].tileFrameY[2]);
				}
			}
		}
		else { continue; }
	}
	if (mapNum == 11) { IMAGEMANAGER->findImage("tutorial")->render(getMemDC(), 183, 205); }
	//플레이어 클래스 렌더
	_enemyManager->bloodrender();
	if (mapNum > 31)
	{
		for (int i = 0; i < _overMap._afterbomb.size(); i++)
		{
			IMAGEMANAGER->findImage("afterbomb")->alphaRender(getMemDC(), _overMap._afterbomb[i].x - _player->getCameraX(), _overMap._afterbomb[i].y - _player->getCameraY(), 70);
		}
	}
	else
	{
		for (int i = 0; i < _map[mapNum]._afterbomb.size(); i++)
		{
			IMAGEMANAGER->findImage("afterbomb")->alphaRender(getMemDC(), _map[mapNum]._afterbomb[i].x - _player->getCameraX(), _map[mapNum]._afterbomb[i].y - _player->getCameraY(), 70);
		}
	}
	if (mapNum == 2 || mapNum == 10 || mapNum == 14 || mapNum == 22 || mapNum == 34)
	{
		IMAGEMANAGER->findImage("아이템받침대")->render(getMemDC(), itemstone.left, itemstone.top);

		if	(mapNum == 2 && _player->getItem(2) == false)	{IMAGEMANAGER->findImage("눈물폭탄")->render(getMemDC(), item.left, item.top);}		//눈물폭탄
		else if (mapNum == 10 && _player->getItem(1) == false) { IMAGEMANAGER->findImage("눈물기폭제")->render(getMemDC(), item.left, item.top); }		//눈물기폭제
		else if (mapNum == 14 && _player->getItem(3) == false && _map[14].clear == true) { IMAGEMANAGER->findImage("분신사바")->render(getMemDC(), item.left, item.top); }		//분신사바
		else if (mapNum == 22 && _player->getItem(5) == false) { IMAGEMANAGER->findImage("쿼터")->render(getMemDC(), item.left, item.top); }		//쿼터
		else if (mapNum == 34 && _player->getItem(4) == false) { IMAGEMANAGER->findImage("검은연꽃")->render(getMemDC(), item.left, item.top); }		//검은연꽃
	}
	_enemyManager->render();
	_player->render();
	//Rectangle(getMemDC(), crush);
	//적매니져 클래스 렌더

	char str[32];
	sprintf_s(str, "%d", mapNum);
	//TextOut(getMemDC(), 450, 250, str, strlen(str));
	if (mapNum >= 0) 
	{
		IMAGEMANAGER->findImage("minimap")->alphaRender(getMemDC(), miniMap.left, miniMap.top, 50);
		IMAGEMANAGER->findImage("minimapframe")->render(getMemDC(), miniMap.left, miniMap.top);
	}
	for (int i = 0; i < 31; i++)
	{
		if (_map[i].haveMap == false) { continue; }
		char str[32];
		if (_map[i].open == true) 
		{
			if (i == 20) { sprintf(str, "openlongroom"); }
			else if (i == 30) { sprintf(str, "openbigroom"); }
			else { sprintf(str, "openroom"); }
		}
		else if (_map[i].open == false) 
		{
			if (i == 20) { sprintf(str, "closelongroom"); }
			else if (i == 30) { sprintf(str, "closebigroom"); }
			else { sprintf(str, "closeroom"); }
		}

		if (mapNum == i)
		{
			if (i == 20) { sprintf(str, "activelongroom"); }
			else if (i == 30) { sprintf(str, "activebigroom"); }
			else { sprintf(str, "activeroom"); }
		}

		//if (_map[i].haveMap == false) { continue; }
		RECT rc;
		RECT crushedRc = RectMake(miniMap.left + 15, miniMap.top + 15, 76, 64);
		if (IntersectRect(&rc,&crushedRc,&_map[i].rc)) { IMAGEMANAGER->findImage(str)->render(getMemDC(), _map[i].rc.left, _map[i].rc.top); }
	}


	
	if (INPUT->GetToggleKey('G'))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			Rectangle(getMemDC(), _tiles[i].rc);
			if (_tiles[i]._type == OBJECT)
			{
				HBRUSH brush = CreateSolidBrush(RGB(50, 100, 100));
				HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
				FillRect(getMemDC(), &_tiles[i].rc, brush);
				SelectObject(getMemDC(), oldBrush);
				DeleteObject(brush);
			}
			else if (_tiles[i]._type == HITOBJECT)
			{
				HBRUSH brush = CreateSolidBrush(RGB(255, 20, 20));
				HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
				FillRect(getMemDC(), &_tiles[i].rc, brush);
				SelectObject(getMemDC(), oldBrush);
				DeleteObject(brush);
			}
			else if (_tiles[i]._type == TILE)
			{
				HBRUSH brush = CreateSolidBrush(RGB(125, 100, 250));
				HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
				FillRect(getMemDC(), &_tiles[i].rc, brush);
				SelectObject(getMemDC(), oldBrush);
				DeleteObject(brush);
			}
			else if (_tiles[i]._type == DOOR)
			{
				HBRUSH brush = CreateSolidBrush(RGB(0, 255, 255));
				HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
				FillRect(getMemDC(), &_tiles[i].rc, brush);
				SelectObject(getMemDC(), oldBrush);
				DeleteObject(brush);
			}
			else if (_tiles[i]._type == LOCKEDDOOR)
			{
				HBRUSH brush = CreateSolidBrush(RGB(65, 160, 220));
				HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
				FillRect(getMemDC(), &_tiles[i].rc, brush);
				SelectObject(getMemDC(), oldBrush);
				DeleteObject(brush);
			}
		}
	}
}
void inGameScene::mapSetting(int mapLocation)
{
	HANDLE file;
	DWORD read;

	_enemyManager->bloodClear();

	for (int i = 0; i < TILEX*TILEY; i++) 
	{
		_tiles[i].imagePage[0] = -1; 
		_tiles[i].rc = RectMake(-100,-100,10,10); 
	}
	char map[32];
	sprintf_s(map, "save%d.mapsave", mapLocation+1);
	file = CreateFile(map, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//if (mapLocation == 0)
	//	file = CreateFile("save1.mapsave", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//else if (mapLocation == 1)
	//	file = CreateFile("save2.mapsave", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//else
	//	file = CreateFile("save3.mapsave", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	
	right = 0;
	for (int i = 0; i < TILEX; i++)
	{
		if (_tiles[i].rc.right > right) { right = _tiles[i].rc.right; }
	}
	int start;
	start = (WINSIZEX - _tiles[0].rc.left - right);
	if (start < 0) { start = 0; }
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].imagePage[0] == -1)
		{
			_tiles[TILEX*TILEY - 1].rc = _tiles[i - 1].rc;
			break;
		}
		_tiles[i].rc.left += start / 2;
		_tiles[i].rc.right += start / 2;
	}


	_map[mapLocation].open = true;
	for (int i = 0; i < 31; i++)
	{
		if (_map[i].haveMap == false) { continue; }
		_map[i].rc = RectMakeCenter((miniMap.left + (miniMap.right - miniMap.left)/2 + (i % 10) * 16)-(mapLocation%10)*18, 
			(5 + (miniMap.bottom - miniMap.top)/2 + (i / 10) * 15) - (mapLocation / 10) * 18, 18, 16);
	}

	if (_player->getBomb()->getBullet().empty() == false) { _player->getBomb()->resetbomb(); }
	if (_player->getBullet()->getBullet().empty() == false) { _player->getBullet()->resetBullet(); }

	CloseHandle(file);
}

void inGameScene::openDoor(int tilesNum)
{
	if (_enemyManager->getMinion().empty()&& _player->getKey() > 0)
	{
		_tiles[tilesNum]._type = DOOR; 
		_player->setKey(_player->getKey() - 1);
	}
}


void inGameScene::save(char* str)
{
	
	HANDLE file;
	DWORD write;

	file = CreateFile(str, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	CloseHandle(file);
}