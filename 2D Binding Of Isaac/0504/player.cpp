#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

HRESULT player::init()
{
	//백그라운드, 공 이미지 초기화
	//_bgImg = IMAGEMANAGER->addImage("bgImg", "Images/bag.bmp", 1920, 1080);
	//_bag = IMAGEMANAGER->findImage("bag");
	//_map = IMAGEMANAGER->addImage("map", "Images/bag.bmp", 96, 54);
	_widthrun = IMAGEMANAGER->findImage("widthrun");
	_heightrun = IMAGEMANAGER->findImage("heightrun");
	_face = IMAGEMANAGER->findImage("face");
	_statUp = IMAGEMANAGER->findImage("statup");
	_statDown = IMAGEMANAGER->findImage("statdown");
	_pickUp = IMAGEMANAGER->findImage("pickup");
	_hit = IMAGEMANAGER->findImage("hit");
	//공 위치 초기화
	_cx = WINSIZEX / 2;
	_cy = WINSIZEY / 2 - 20;
	x = y = 0;
	Charicter = RectMakeCenter(_cx, _cy, 36, 28);
	Head = RectMakeCenter(_cx, _cy - 30, 56, 50);
	xm = _cx / 20;
	ym = _cy / 20;
	_rcCam = RectMakeCenter(_cx, _cy, 800, 400);
	playerRc = RectMakeCenter(_cx, _cy, 36, 28);
	_headIndex = _runIndexX = _runIndexY = 0;
	_face->setFrameY(0);

	//_probeY = Head.top;
	//_probeCY = Charicter.bottom;
	
	//_probeX = Head.left;
	//_probeCX = Head.right;
	_soulHeart.blackHeart = false;
	_blackHeart.blackHeart = true;
	_soulHeart._hp = 2;
	_blackHeart._hp = 2;
	blackheartAtt = false;
	_bh = IMAGEMANAGER->findImage("블랙하트소멸");
	_bhAlpha = 50;
	item = 0;

	sadbomb = false;
	ouijaBoard = false;
	blacklotus = false;
	quarter = false;

	tearDetonator = false;
	tearDetonatorCount = 54;

	invicount = 0;
	alpha = 255;
	count = 0;
	attSpeed = 10;
	attCount = 0;
	bulletSpeed = 5.0f;
	bulletRange = 200.f;
	moveSpeed = 4.0f;
	attPower = 40.0f;
	_state = NORMAL;
	_eternal = false;
	_hp = 6;
	_hpMax = 6;
	_penny = 0;
	_haveBomb = 10;
	_key = 0;

	_bullet = new bullet;
	_bullet->init("bullet",100,bulletRange);
	_bomb = new bomb;
	_bomb->init(1);
	//Y축으로 탐지(공의 하단에서 검사함)
	//_probeY = _y + _ball->getHeight() / 2;
	return S_OK;
}

void player::release()
{

}

void player::update(){}
void player::update(float tileEndX, float tileEndY)
{
	if (INPUT->GetKeyDown(VK_NUMPAD5)) { this->hitDamage(1.f); }
	if (INPUT->GetKeyDown(VK_NUMPAD6)) { this->statUp(); }
	if (INPUT->GetKeyDown(VK_NUMPAD7)) { this->statDown(); }
	if (INPUT->GetKeyDown(VK_NUMPAD8)) { this->pickUp(); }
	if (INPUT->GetKeyDown(VK_NUMPAD3)) { plusHpMaxUp(true); }
	if (INPUT->GetKeyDown(VK_NUMPAD4)) { plusHpMaxUp(false); }
	if (INPUT->GetKeyDown('O')) { _hpMax -= 2; }
	if (INPUT->GetKeyDown('I')) { _key++; }
	if (INPUT->GetKeyDown('M')) { _haveBomb++; }
	if (INPUT->GetKeyDown('P')) { hpMaxUp(); }
	if (INPUT->GetKeyDown('L')) { attPower += 2; }
	if (INPUT->GetKeyDown('K')) { attPower -= 2; }

	if (INPUT->GetKeyDown('U')) { this->pickUpLotus(); }
	if (INPUT->GetKeyDown('Y')) { this->pickUpOuijaBoard(); }
	if (INPUT->GetKeyDown('T')) { this->pickUpQuarter(); }
	if (INPUT->GetKeyDown('J')) { this->pickUpSadbBmb(); }
	if (INPUT->GetKeyDown('H')) { this->pickUpTearDetonator(); }
	if (INPUT->GetKeyDown('N')) { this->eternalGet(); }

	//----------------------------------------------------테스트용------------------------------------------------------
	invicount++;
	count++;
	if (count % 2 == 0 && tearDetonatorCount <54) { tearDetonatorCount++; }
	this->animation();
	this->invi();
	_bullet->move(bulletRange);
	_bomb->update();

	if (_penny > 99) { _penny = 99; }
	if (_haveBomb > 99) { _haveBomb = 99; }
	if (_key > 99) { _key = 99; }
	if (_hpMax > 24) { _hpMax = 24; }
	if (_hpMax < 0) { _hpMax = 0; }
	if (_hp > _hpMax) { _hp = _hpMax; }
	//-----------------------------------------------------아이템등 상한선-------------------------------------------
	
	if (INPUT->GetKeyUp('A') || INPUT->GetKeyUp('D') || INPUT->GetKeyUp('W') || INPUT->GetKeyUp('S')) { _runIndexX = 0; }
	//if (INPUT->GetKeyDown(VK_LEFT) || INPUT->GetKeyDown(VK_RIGHT) || INPUT->GetKeyDown(VK_UP) || INPUT->GetKeyDown(VK_DOWN)) 
	//{
	//	if (attCount > attSpeed * 2) { attCount = attSpeed - 1; }
	//}
	if (_state == NORMAL && attCount % attSpeed < attSpeed-1 ) { attCount++; }
	if (attCount % (attSpeed*2) + 1 == attSpeed * 2) { attCount++; }

	//if (INPUT->GetKeyUp(VK_LEFT) || INPUT->GetKeyUp(VK_RIGHT) || INPUT->GetKeyUp(VK_UP) || INPUT->GetKeyUp(VK_DOWN)) { _state = NORMAL; }

	
	//----------------------------------------------------상호작용 혹은 예외처리-------------------------------------------------


	if (!(INPUT->GetKey(VK_LEFT) || INPUT->GetKey(VK_RIGHT) || INPUT->GetKey(VK_UP) || INPUT->GetKey(VK_DOWN)))
	{
		if (INPUT->GetKey('W')) { _headIndex = 4; }
		else if (INPUT->GetKey('A')) { _headIndex = 6; }
		else if (INPUT->GetKey('S')) { _headIndex = 0; }
		else if (INPUT->GetKey('D')) { _headIndex = 2; }
	}

	this->move();
	RECT rc;
	for (int i = 0; i < _em->getMinion().size(); i++)
	{
		if (IntersectRect(&rc, &playerRc, &_em->getMinion()[i]->getRect())) { this->hitDamage(1.f); }
	}
	for (int i = 0; i < _bomb->getBullet().size(); i++)
	{
		RECT _explosion;
		_explosion = _bomb->getBullet()[i].rc;

		_explosion.left += 15;
		_explosion.right -= 15;
		_explosion.top += 65;
		if (IntersectRect(&rc, &playerRc, &_explosion)) { this->hitDamage(2.f); }
	}
	//if (INPUT->GetKey('W') && Head.top > 0)
	//{
	//	_cy -= moveSpeed;
	//	if (_rcCam.top < 0 && y >= 0)
	//	{
	//		y -= moveSpeed;
	//
	//	}
	//}
	//
	//if (INPUT->GetKey('S') && Charicter.bottom < WINSIZEY)
	//{
	//	_cy += moveSpeed;
	//	if (_rcCam.bottom > WINSIZEY && y <= 540)
	//	{
	//		y += moveSpeed;
	//
	//	}
	//}
	//
	//if (INPUT->GetKey('A') && Head.left > 0)
	//{
	//	_cx -= moveSpeed;
	//
	//	if (_rcCam.left < 0 && x >= 0)
	//	{
	//		x -= moveSpeed;
	//
	//	}
	//
	//}
	//
	//if (INPUT->GetKey('D') && Head.right < WINSIZEX)
	//{
	//	_cx += moveSpeed;
	//	if (_rcCam.right > WINSIZEX && x <= 960)
	//	{
	//		x += moveSpeed;
	//	}
	//}
	
		if (INPUT->GetKey(VK_LEFT))
		{
			if (_headIndex != 6 && _headIndex != 7) { _headIndex = 6; }
			if (_state == NORMAL) 
			{
				attCount = attSpeed-1;
				//_bullet->fire(_cx, _cy - 30, 3.14f, bulletSpeed);
				_state = SHOT; 
			}
			if (attCount % (attSpeed*2) == attSpeed) { _bullet->fire(_cx, _cy - 25, 3.14f, bulletSpeed, attPower); }
		}
		else if (INPUT->GetKey(VK_RIGHT))
		{
			if (_headIndex != 2 && _headIndex != 3) { _headIndex = 2; }
			if (_state == NORMAL) 
			{
				attCount = attSpeed-1;
				//_bullet->fire(_cx, _cy - 30, 0.f, bulletSpeed);
				_state = SHOT;
			}
			if (attCount % (attSpeed * 2) == attSpeed) { _bullet->fire(_cx, _cy - 25, 0.f, bulletSpeed, attPower); }
		}
		else if (INPUT->GetKey(VK_UP))
		{
			if (_headIndex != 4 && _headIndex != 5) { _headIndex = 4; }
			if (_state == NORMAL) 
			{
				attCount = attSpeed-1;
				//_bullet->fire(_cx, _cy - 30, 3.14f / 2, bulletSpeed);
				_state = SHOT; 
			}
			if (attCount % (attSpeed * 2) == attSpeed) { _bullet->fire(_cx, _cy - 30, 3.14f / 2, bulletSpeed, attPower); }
		}
		else if (INPUT->GetKey(VK_DOWN))
		{
			if (_headIndex != 0 && _headIndex != 1) { _headIndex = 0; }
			if (_state == NORMAL) 
			{
				attCount = attSpeed-1;
				//_bullet->fire(_cx, _cy - 30, 3.14f / 2 * 3, bulletSpeed);
				_state = SHOT;
			}
			if (attCount % (attSpeed * 2) == attSpeed) { _bullet->fire(_cx, _cy, 3.14f / 2 * 3, bulletSpeed, attPower); }
		}


		if (INPUT->GetKeyDown('E')&& _haveBomb>0)
		{
			if (_bomb->getBullet().empty()) { _haveBomb--; }
			_bomb->fire(_cx, _cy - 10, sadbomb);
		}
		if (sadbomb == true)
		{
			for (int i = 0; i < _bomb->getBullet().size(); i++)
			{
				if (_bomb->getBullet()[i]._imageSwitching == 16)
				{
					for (int j = 0; j < 8; j++)
					{
						_bullet->fire(_bomb->getBullet()[i].x, _bomb->getBullet()[i].y, (PI / 4)*j, bulletSpeed, attPower);
					}
				}
			}
		}
		if (tearDetonator == true && tearDetonatorCount >= 54)
		{
			if (INPUT->GetKeyDown(VK_SPACE))
			{
				item = 1;
				this->pickUp();
				tearDetonatorCount = 0;
				int a;
				a = _bullet->getBullet().size();
				for (int i = 0; i < a; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						_bullet->fire(_bullet->getBullet()[i].x, _bullet->getBullet()[i].y, (PI / 4)*j, bulletSpeed, attPower);
					}
				}
				for (int i = 0; i < a; i++)
				{
					_bullet->removeBullet(0);
				}
			}
		}

		if (blackheartAtt == true)
		{
			if (_bhAlpha > 250) 
			{
				blackheartAtt = false; 
				_bhAlpha = 50;
			}
			_bhAlpha += 5;
			_bhrc = RectMakeCenter(WINSIZEX / 2 + RANDOM->Range(-3, -3) * 10, WINSIZEY / 2 + RANDOM->Range(-3, -3) * 10, _bh->getWidth(), _bh->getHeight());
		
		}
		//if (!_bomb-)
	//공의 렉트 움직이기
	//
	//if (_rcCam.right > WINSIZEX && x < 960)
	//{
	//	Charicter.left = 560 - 18;
	//	Charicter.right = 560 + 18;
	//	Head.left = 560 - 28;
	//	Head.right = 560 + 28;
	//
	//}
	//
	//if (_rcCam.bottom > WINSIZEY && x < 540)
	//{
	//	Charicter.top = 340 - 14;
	//	Charicter.bottom = 340 + 14;
	//	Head.top = 310 - 25;
	//	Head.bottom = 310 + 25;
	//
	//}


	Charicter = RectMakeCenter(_cx - x, _cy - y, 36, 28);
	Head = RectMakeCenter(_cx - x, _cy - y - 30, 56, 50);
	_rcCam = RectMakeCenter(_cx - x, _cy - y, 800, 400);

	//_probeY = _cy - 14;
	//_probeCY = _cy + 14;
	
	//_probeX = _cx - 28;
	//_probeCX = _cx + 28;

	xs = _cx - x;
	ys = _cy - y;


	/*for (int i = _probeX - 5; i < _probeX + 5; i++)
	{

		COLORREF color = GetPixel(_bag->getMemDC(), i, _cy - 10);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);



		if (!(r == 255 && g == 0 && b == 255))
		{
			_cx = i + 36;
			x = _cx - xs - 3;
			//if (!(x == 0 || x == 960))
			//{
			//	x -= 3.0f;
			//}


			break;
		}
	}

	for (int i = _probeCX + 5; i > _probeCX - 5; i--)
	{
		COLORREF color = GetPixel(_bag->getMemDC(), i, _cy - 10);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);



		if (!(r == 255 && g == 0 && b == 255))
		{
			_cx = i - 36;
			x = _cx - xs + 3;


			break;
		}
	}



	for (int i = _probeY - 5; i < _probeY + 5; i++)
	{
		COLORREF color = GetPixel(_bag->getMemDC(), _cx, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);



		if (!(r == 255 && g == 0 && b == 255))
		{
			_cy = i + 22;
			y = _cy - ys - 3;


			break;
		}
	}


	for (int i = _probeCY + 5; i > _probeCY - 5; i--)
	{
		COLORREF color = GetPixel(_bag->getMemDC(), _cx, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);



		if (!(r == 255 && g == 0 && b == 255))
		{
			_cy = i - 22;
			y = _cy - ys + 3;

			break;
		}
	}
	*/
	if (tileEndX < 960)
	{
		x = 0;
	}
	else if (x < 0)
	{
		x = 0;
	}
	else if (x > tileEndX - 960)
	{
		x = tileEndX - 960;
	}

	if (tileEndY < 480)
	{
		y =0;
	}
	else if (y < 0)
	{
		y = 0;
	}
	else if (y > tileEndY -540)
	{
		y = tileEndY - 540;
	}

	xm = _cx / 20;
	ym = _cy / 20;
	/*이부분이 픽셀충돌의 핵심*/


	//for (int i = _probeX - 5 ; i < _probeX +5 ; i++)
	//{
	//	COLORREF color = GetPixel(_bag->getMemDC(), _cx, i);
	//	int r = GetRValue(color);
	//	int g = GetGValue(color);
	//	int b = GetBValue(color);
	//
	//
	//
	//	if (!(r == 255 && g == 0 && b == 255))
	//	{
	//		if (INPUT->GetKey(VK_LEFT))
	//		{
	//			_cx += 3.0f;
	//			//if (_rcCam.left < 0 && x >= 0)
	//			//{
	//			//	x -= 3.0f;
	//			//	if (x < 0)
	//			//	{
	//			//		x = 0;
	//			//	}
	//			//}
	//		}
	//
	//		break;
	//	}
	//}

}

void player::render()
{
	//_bgImg->render(getMemDC(), -x, -y);
	//_bag->render(getMemDC(), -x, -y);
	//_map->render(getMemDC(), 850, 10);
	//if ()
	//{
	//
	//}


	//RECT mapRc = RectMakeCenter(850 + xm, 10 + ym, 5, 5);
	//Rectangle(getMemDC(), mapRc);
	//Rectangle(getMemDC(), Head);
	//Rectangle(getMemDC(), Charicter);
	//FrameRect(getMemDC(), _rcCam, RGB(140, 110, 60));
	_bomb->render(x, y);
	if (_state == NORMAL || _state == SHOT)
	{
		if (INPUT->GetKey('A') || INPUT->GetKey('D'))
		{
			_widthrun->frameRender(getMemDC(), Charicter.left, Charicter.top, _runIndexX, _widthrun->getFrameY(),alpha);
		}
		else
		{
			_heightrun->frameRender(getMemDC(), Charicter.left, Charicter.top, _runIndexX, _heightrun->getFrameY(), alpha);
		}

		_face->frameRender(getMemDC(), Head.left, Head.top, _headIndex, _face->getFrameY(), alpha);
	}
	else if (_state == HIT || _state == DEAD)
	{
		_hit->frameRender(getMemDC(), Head.left, Head.top, _hit->getFrameX(), _hit->getFrameY(), alpha);
	}
	else if ( _state == STATUP){ _statUp->frameRender(getMemDC(), Head.left, Head.top, _statUp->getFrameX(), _statUp->getFrameY(), alpha); }
	else if (_state == STATDOWN) { _statDown->alphaRender(getMemDC(), Head.left, Head.top, alpha); }
	else if ( _state == PICKUP){ _pickUp->alphaRender(getMemDC(), Head.left, Head.top, alpha); }

	if (tearDetonator == true) 
	{
		IMAGEMANAGER->findImage("눈물기폭제")->render(getMemDC(), 10, 10); 
		IMAGEMANAGER->findImage("충전바")->render(getMemDC(), 57, 10); 
		IMAGEMANAGER->findImage("충전")->render(getMemDC(), 57, 64-tearDetonatorCount,0,54-tearDetonatorCount,12,tearDetonatorCount);
	}
	if (_state == PICKUP)
	{
		if (item == 1) { IMAGEMANAGER->findImage("눈물기폭제")->render(getMemDC(), Head.left + 3, Head.top - 15); }
		else if (item == 2) { IMAGEMANAGER->findImage("눈물폭탄")->render(getMemDC(), Head.left - 5, Head.top - 15); }
		else if (item == 3) { IMAGEMANAGER->findImage("분신사바")->render(getMemDC(), Head.left + 3, Head.top - 15); }
		else if (item == 4) { IMAGEMANAGER->findImage("검은연꽃")->render(getMemDC(), Head.left + 3, Head.top - 15); }
		else if (item == 5) { IMAGEMANAGER->findImage("쿼터")->render(getMemDC(), Head.left + 3, Head.top - 15); }
	}				  
	maxHpRender(_hpMax);
	HpRender(_hp);
	plusHeart(_hpMax, _plusHp);
	EternalHpRender(_hpMax);

	if (blackheartAtt == true) { _bh->alphaRender(getMemDC(), _bhrc.left, _bhrc.top,_bhAlpha); }
	//IMAGEMANAGER->findImage("반칸하트")->render(getMemDC(), 10, 10);
	//IMAGEMANAGER->findImage("하트")->render(getMemDC(), 40, 10);
	//IMAGEMANAGER->findImage("반칸소울하트")->render(getMemDC(), 70, 10);
	//IMAGEMANAGER->findImage("소울하트")->render(getMemDC(), 100, 10);
	//IMAGEMANAGER->findImage("반칸블랙하트")->render(getMemDC(), 130, 10);
	//IMAGEMANAGER->findImage("블랙하트")->render(getMemDC(), 150, 10);
	//IMAGEMANAGER->findImage("이터널하트")->render(getMemDC(), 170, 10);
	//IMAGEMANAGER->findImage("빈하트")->render(getMemDC(), 190, 10);



	IMAGEMANAGER->findImage("페니")->render(getMemDC(), 10, 70);
	this->NumberRender(40,70,_penny);
	IMAGEMANAGER->findImage("폭탄아이콘")->render(getMemDC(), 10, 90);
	this->NumberRender(40,90, _haveBomb);
	IMAGEMANAGER->findImage("열쇠아이콘")->render(getMemDC(), 10, 110);
	this->NumberRender(40,110,_key);


	_bullet->render(x,y,bulletRange);
	//디버깅용
	//if (INPUT->GetToggleKey('A'))
	//{
	//	//충돌용 작은사각형
	//	RECT rcl = RectMakeCenter(_probeX, _cy - y - 10, 10, 10);
	//	RECT rcr = RectMakeCenter(_probeCX, _cy - y - 10, 10, 10);
	//	RECT rct = RectMakeCenter(_cx - x, _probeY, 10, 10);
	//	RECT rcb = RectMakeCenter(_cx - x, _probeCY, 10, 10);
	//	Rectangle(getMemDC(), rcl);
	//	Rectangle(getMemDC(), rcr);
	//	Rectangle(getMemDC(), rct);
	//	Rectangle(getMemDC(), rcb);
	//}


	//SetTextColor(getMemDC(), RGB(255, 0, 0));
	//TextOut(getMemDC(), 10, 10, "픽셀충돌", strlen("픽셀충돌"));
	//char str[10];
	//sprintf(str, "%0.0f", x);
	//TextOut(getMemDC(), 20, 30, str, strlen(str));
	//sprintf(str, "%0.0f", y);
	//TextOut(getMemDC(), 60, 30, str, strlen(str));
	//sprintf(str, "%0.0f", _cx);
	//TextOut(getMemDC(), 20, 50, str, strlen(str));
	//sprintf(str, "%0.0f", _cy);
	//TextOut(getMemDC(), 60, 50, str, strlen(str));
}

void player::animation()
{
	switch (_state)
	{
	case NORMAL:
		if (_headIndex % 2 == 1) { _headIndex--; }
		if (INPUT->GetKey('A'))
		{

			_widthrun->setFrameY(0);
			if (count % 3 == 0)
			{
				_widthrun->setFrameX(_widthrun->getFrameX() - 1);
				_runIndexX--;
				if (_runIndexX < 0)
				{
					_runIndexX = 9;
				}
			}
		}
		else if (INPUT->GetKey('D'))
		{
			_widthrun->setFrameY(1);
			if (count % 3 == 0)
			{
				_widthrun->setFrameX(_widthrun->getFrameX() + 1);
				_runIndexX++;
				if (_runIndexX > 9)
				{
					_runIndexX = 0;
				}
			}
		}
		else if (INPUT->GetKey('W') || INPUT->GetKey('S'))
		{
			_heightrun->setFrameY(0);
			if (count % 3 == 0)
			{
				_heightrun->setFrameX(_heightrun->getFrameX() + 1);
				_runIndexX++;
				if (_runIndexX > 9)
				{
					_runIndexX = 0;
				}
			}
		}

		break;
	case SHOT:
		if (INPUT->GetKey('A'))
		{

			_widthrun->setFrameY(0);
			if (count % 3 == 0)
			{
				_widthrun->setFrameX(_widthrun->getFrameX() - 1);
				_runIndexX--;
				if (_runIndexX < 0)
				{
					_runIndexX = 9;
				}
			}
		}
		else if (INPUT->GetKey('D'))
		{
			_widthrun->setFrameY(1);
			if (count % 3 == 0)
			{
				_widthrun->setFrameX(_widthrun->getFrameX() + 1);
				_runIndexX++;
				if (_runIndexX > 9)
				{
					_runIndexX = 0;
				}
			}
		}
		else if (INPUT->GetKey('W') || INPUT->GetKey('S'))
		{
			_heightrun->setFrameY(0);
			if (count % 3 == 0)
			{
				_heightrun->setFrameX(_heightrun->getFrameX() + 1);
				_runIndexX++;
				if (_runIndexX > 9)
				{
					_runIndexX = 0;
				}
			}
		}


		if (INPUT->GetKey(VK_LEFT) || INPUT->GetKey(VK_RIGHT) || INPUT->GetKey(VK_UP) || INPUT->GetKey(VK_DOWN))
		{
			attCount++;
			
			if (attCount % attSpeed == 0 && _headIndex % 2 == 0) { _headIndex++; }
			else if (attCount % attSpeed == 0 && _headIndex % 2 == 1) 
			{
				_headIndex--; 	
				attCount = 0;
				//_state = NORMAL;
			}
		}
		else 
		{ 
			
				attCount++;
			if (attCount % attSpeed == 0 && _headIndex % 2 == 1) 
			{
				_headIndex--; 
				attCount = 0;
				_state = NORMAL;
			} 
		}

		break;
	case HIT:

		_hit->setFrameY(0);
		if (count < 5 )
		{
			_hit->setFrameX(0);
		}
		else
		{
			_hit->setFrameX(1);

			if (count > 35)
			{
				_state = NORMAL;
			}
		}
		break;
	case DEAD:

		_hit->setFrameY(0);
		if (count < 5)
		{
			_hit->setFrameX(0);
		}
		else if(count < 35)
		{
			_hit->setFrameX(1);
		}
		else
		{
			_hit->setFrameX(2);
		}
		break;
	case STATUP:
		_statUp->setFrameY(0);
		if (count < 5)
		{
			_statUp->setFrameX(0);
		}
		else
		{
			_statUp->setFrameX(1);

			if (count > 35)
			{
				_state = NORMAL;
			}
		}
		break;
	case STATDOWN:
		if (count > 35)
		{
			_state = NORMAL;
		}
		break;
	case PICKUP:
		if (count > 50)
		{
			item = 0;
			_state = NORMAL;
		}
		break;
	default:
		break;
	}
}

void player::hitDamage(float damage)
{
	if (_state != DEAD)
	{
		if (alpha == 255)
		{
			alpha = 130;
			count = 0;
			invicount = 0;
			for (int i = 0; i < damage; i++)
			{
				if (_plusHp.empty() && _eternal) { _eternal = false; }
				else if (!_plusHp.empty())
				{
					_plusHp[_plusHp.size() - 1]._hp--;
					//if(_plusHp[_plusHp.size()-1].blackHeart == true)
					//{
					//	for (int i = 0; i < _em->getMinion().size(); i++)
					//	{
					//		_em->getMinion()[i].							//차후 전체 데미지
					//	}
					//}
					if (_plusHp[_plusHp.size() - 1]._hp == 0) 
					{
						if (_plusHp[_plusHp.size() - 1].blackHeart == true) 
						{
							for (int j = 0; j < _em->getMinion().size(); j++)
							{
								_em->getMinion()[j]->hitDamage(10);
							}
							blackheartAtt = true;
						}
						_plusHp.pop_back(); 
					}
				}
				else { _hp -= damage; }
			}

			if (_hp <= 0 && _plusHp.empty()) { _state = DEAD; }
			else { _state = HIT; }
		}
	}
}

void player::heartAtt()
{
	
}

void player::invi()
{
	if (invicount % 100 == 0) { alpha = 255; }
	else if (alpha != 255 && invicount % 3 == 0)
	{
		if (alpha == 130) { alpha = 254; }
		else  if (alpha == 254) { alpha = 130; }
	}
}   //알파이용해서 무적시간
	


void player::statUp()
{
	count = 0;
	_state = STATUP;
}

void player::statDown()
{
	count = 0;
	_state = STATDOWN;
}

void player::pickUp()
{
	count = 0;
	_state = PICKUP;
}

void player::move()
{


	if (INPUT->GetKey('W') && Head.top > 0)
	{
		_cy -= moveSpeed;
		if (_rcCam.top < 0 && y >= 0)
		{
			y -= moveSpeed;

		}
	}

	if (INPUT->GetKey('S') && Charicter.bottom < WINSIZEY)
	{
		_cy += moveSpeed;
		if (_rcCam.bottom > WINSIZEY && y <= 540)
		{
			y += moveSpeed;

		}
	}

	if (INPUT->GetKey('A') && Head.left > 0)
	{
		_cx -= moveSpeed;

		if (_rcCam.left < 0 && x >= 0)
		{
			x -= moveSpeed;

		}

	}

	if (INPUT->GetKey('D') && Head.right < WINSIZEX)
	{
		_cx += moveSpeed;
		if (_rcCam.right > WINSIZEX && x <= 960)
		{
			x += moveSpeed;
		}
	}
	playerRc = RectMakeCenter(_cx, _cy-13, 35, 48);
}

void player::move(int direction)
{
	if (direction == 2 && Head.top > 0)
	{
		//_cy = object -17;
		_cy -= moveSpeed;
		if (_rcCam.top < 0 && y >= 0)
		{
			y -= moveSpeed;

		}
	}

	if (direction == 8 && Charicter.bottom < WINSIZEY)
	{
		//_cy = object+17;
		_cy += moveSpeed;
		if (_rcCam.bottom > WINSIZEY && y <= 540)
		{
			y += moveSpeed;

		}
	}

	if (direction == 6 && Head.left > 0)
	{
		//_cx = object -22;
		_cx -= moveSpeed;

		if (_rcCam.left < 0 && x >= 0)
		{
			x -= moveSpeed;

		}

	}

	if (direction == 4 && Head.right < WINSIZEX)
	{
		//_cx = object + 22;
		_cx += moveSpeed;

		if (_rcCam.right > WINSIZEX && x <= 960)
		{
			x += moveSpeed;
		}
	}
}


void player::NumberRender(int x, int y, int num)
{
	int a = x;
	int b;
	//char str[32];
	if (num < 10) { IMAGEMANAGER->findImage("숫자")->frameRender(getMemDC(), x - 12, y, 0, 0); }
	for (int i = 1; i < 100; i *= 10)
	{
		if (num < i - 1) { break; }
		b = (num / i) % 10;
		IMAGEMANAGER->findImage("숫자")->frameRender(getMemDC(), a, y, b, 0);
		a -= 12;

	}

}

void player::maxHpRender(int hpMax)
{
	int a = 70;
	int b = 15;

	for (int i = 0; i < (hpMax + 1) / 2; i++)
	{

		IMAGEMANAGER->findImage("빈하트")->render(getMemDC(), a, b);
		a += 24;
		if (i == 5)
		{
			b += 24;
			a -= 144;
		}
	}
}

void player::HpRender(int hp)
{
	int a = 70;
	int b = 15;

	for (int i = 0; i < hp / 2; i++)
	{

		IMAGEMANAGER->findImage("하트")->render(getMemDC(), a, b);
		a += 24;
		if (i == 5)
		{
			b += 24;
			a -= 144;
		}
	}
	if (hp % 2 == 1) { IMAGEMANAGER->findImage("반칸하트")->render(getMemDC(), a, b); }
}

void player::eternalGet()
{
	if (_eternal == false) { _eternal = true; }
	else 
	{
		_eternal = false; 
		_hp += 2;
		_hpMax += 2;
	}
}

void player::EternalHpRender(int hpMax)
{
	int a = 70;
	int b = 15;

	for (int i = 0; i < (hpMax + 1) / 2; i++)
	{
		if (_eternal && i == ((hpMax + 1) / 2)-1) { IMAGEMANAGER->findImage("이터널하트")->render(getMemDC(), a, b); }
		a += 24;
		if (i == 5)
		{
			b += 24;
			a -= 144;
		}
	}
}

void player::plusHeart(int hpMax, vector<plusHp> plusHp)
{
	int a = 70 + (24 * ((hpMax + 1) / 2));
	if (((hpMax + 1) / 2) > 6) { a -= 144; }
	int b = 15;
	if (((hpMax + 1) / 2) > 6) { b += 24; }

	for (int i = 0 / 2; i < plusHp.size(); i++)
	{
		if (i + (hpMax + 1) / 2 == 6)
		{
			a -= 144;
			b += 24;
		}
		if (plusHp[i].blackHeart == false)
		{
			if (plusHp[i]._hp == 1) { IMAGEMANAGER->findImage("반칸소울하트")->render(getMemDC(), a, b); }
			else if (plusHp[i]._hp == 2) { IMAGEMANAGER->findImage("소울하트")->render(getMemDC(), a, b); }
		}
		else if (plusHp[i].blackHeart == true)
		{
			if (plusHp[i]._hp == 1) { IMAGEMANAGER->findImage("반칸블랙하트")->render(getMemDC(), a, b); }
			else if (plusHp[i]._hp == 2) { IMAGEMANAGER->findImage("블랙하트")->render(getMemDC(), a, b); }
		}
		a += 24;

		
	}
}

void player::hpMaxUp()
{	
	_hpMax+=2; 
	if (((_hpMax + 1) / 2) + _plusHp.size() > 10 && !_plusHp.empty()) { _plusHp.pop_back(); }
}

void player::plusHpMaxUp(bool blackHeart)
{
	
	if (blackHeart && ((_hpMax + 1) / 2) + _plusHp.size() < 12) 
	{
		if (_plusHp.empty()||_plusHp[_plusHp.size() - 1]._hp == 2){ _plusHp.push_back(_blackHeart); }
		else if (_plusHp[_plusHp.size() - 1]._hp == 1) 
		{
			_plusHp[_plusHp.size() - 1]._hp += 1;
			_plusHp.push_back(_blackHeart);
			_plusHp[_plusHp.size() - 1]._hp -= 1;
		}
	}
	
	else if (!blackHeart && ((_hpMax + 1) / 2) + _plusHp.size() < 12)
	{ 
		
		if (_plusHp.empty() || _plusHp[_plusHp.size() - 1]._hp == 2) { _plusHp.push_back(_soulHeart); }
		else if (_plusHp[_plusHp.size() - 1]._hp == 1)
		{
			_plusHp[_plusHp.size() - 1]._hp += 1;
			_plusHp.push_back(_soulHeart);
			_plusHp[_plusHp.size() - 1]._hp -= 1;
		}
		
	}
}

bool player::getItem(int itemNum)
{
	if ( itemNum==1) { return tearDetonator; }
	else if (itemNum == 2) { return sadbomb; }
	else if (itemNum == 3) { return ouijaBoard; }
	else if (itemNum == 4) { return blacklotus; }
	else if (itemNum == 5) { return quarter; }
}

void player::pickUpTearDetonator()
{
	if (tearDetonator == false)
	{
		tearDetonator = true;
		item = 1;
		this->pickUp();
	}
}

void player::pickUpSadbBmb()
{
	if (sadbomb == false)
	{

		_haveBomb += 5;
		sadbomb = true;
		item = 2;
		this->pickUp();
	}
}

void player::pickUpOuijaBoard()
{
	if (ouijaBoard == false)
	{
		ouijaBoard = true;
		item = 3;
		this->pickUp();
	}
}

void player::pickUpLotus()
{
	if (blacklotus == false)
	{
		plusHpMaxUp(false);
		plusHpMaxUp(true);
		_hpMax += 2;
		_hp += 2;
		blacklotus = true;
		item = 4;
	this->pickUp();
	}
}

void player::pickUpQuarter()
{
	if (quarter == false)
	{
		_penny += 25;
		quarter = true;
		item = 5;
		this->pickUp();
	}
}





