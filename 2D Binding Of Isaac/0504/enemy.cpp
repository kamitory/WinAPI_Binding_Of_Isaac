#include "stdafx.h"
#include "enemy.h"

HRESULT dukeOfFlies::init()
{
	return S_OK;
}

HRESULT dukeOfFlies::init(const char * imageName, POINT position)
{
	//프레임 변수 초기화
	_bombCount = 30;
	_count = 0;
	_currentFrameX = _currentFrameY = 0;
	//이미지, 이미지렉트 초기화
	_image = IMAGEMANAGER->findImage(imageName);
	_killed = IMAGEMANAGER->findImage("적사망");
	_killed->setFrameX(0);
	x = position.x;
	y = position.y;
	speed = 2.0f;
	angle = RANDOM->Range(PI/4-0.2f,PI/4+0.2f);
	_rc = RectMakeCenter(position.x, position.y, _image->getFrameWidth(), _image->getFrameHeight());
	_state = IDLE;
	//랜덤으로 총알 쿨타임 주는 변수 초기화
	_fireCount = 100;
	_rndFireConut = RANDOM->Range(1, 1000);
	fly = false;
	_name = DUKE;

	hpMax = hp = 120;


	return S_OK;
}

void dukeOfFlies::release()
{
}

void dukeOfFlies::update(float x, float y)
{
	if (hp <= 0)
	{
		speed = 0;
		_state = KILLED;
	}
	_bombCount++;
	_fireCount++;
	if (INPUT->GetKeyDown(VK_DELETE)) { hp -= 10; }
	if (INPUT->GetKeyDown(VK_END)){this->pattern1();}
	if (_fireCount >250 && _state != KILLED){this->pattern1();}
	if (INPUT->GetKeyDown(VK_HOME)){this->pattern2();}

	this->move();
	this->animation();

}

void dukeOfFlies::render()
{
	this->draw();
}

//알아서 만들면 된다
void dukeOfFlies::move()
{


	x += cosf(angle) * speed;
	y += -sinf(angle) * speed;
	if (_state == KILLED) { _rc2 = RectMakeCenter(x, y, _killed->getFrameWidth(), _killed->getFrameHeight()); }
	if (_state != KILLED) { _rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight()); }
	if (_rc.left < 96)
	{
		x++;
		angle = PI - angle;
	}
	//오른쪽
	if (_rc.right > WINSIZEX-96)
	{
		x--;
		angle = PI - angle;
	}
	//위
	if (_rc.top < 45)
	{
		y++;
		angle = 2 * PI - angle;
	}
	//아래
	if (_rc.bottom > WINSIZEY-45)
	{
		y--;
		angle = 2 * PI - angle;
	}

}

void dukeOfFlies::draw()
{
	//_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _image->getFrameX(), _image->getFrameY());
	if (_state == KILLED) 
	{ 
		for (int i = 0; i < 3; i++)
		{
			_killed->scaleFrameRender(getMemDC(), _rc2.left+(RANDOM->Range(-3,3)*10), _rc2.top+(RANDOM->Range(-3, 3) * 10), _killed->getFrameX(), _killed->getFrameY(), 1.5f);
		}
	}
	//Rectangle(getMemDC(),_rc);
}

void dukeOfFlies::animation()
{
	_count++;
	switch (_state)
	{
	case IDLE:
	
		_image->setFrameX(0);
		_currentFrameX = 0;
	
		break;
	case PATTERN1:			//파리소환
		if (_count % 30 == 0)
		{
			_image->setFrameX(_image->getFrameX()+1);
			_currentFrameX++;
			if (_currentFrameX == _image->getMaxFrameX()) { fly = true; }
			if (_currentFrameX > _image->getMaxFrameX())
			{
				_currentFrameX = 0;
				_count = 0;
				_state = IDLE;
			}
		}
		break;
	case PATTERN2:			//파리방출
		if (_count % 30 == 0)
		{
			_image->setFrameX(_image->getFrameX() + 1);
			_currentFrameX++;
			if (_currentFrameX > _image->getMaxFrameX())
			{
				_currentFrameX = 0;
				_count = 0;
				_state = IDLE;
			}
		}
		break;
	case KILLED:
		if (_count % 6 == 0)
		{
			_killed->setFrameX(_killed->getFrameX() + 1);
			_currentFrameX++;
			if (_currentFrameX >= _killed->getMaxFrameX())
			{
				hp -= 20;
				_killed->setFrameX(0);
				x += RANDOM->Range(-10, 10);
				y += RANDOM->Range(-10, 10);
				_currentFrameX = 0;
				_count = 0;
			}
		}
		break;
	default:
		break;
	}
}

void dukeOfFlies::pattern1()		//파리소환
{
	_fireCount = 0;
	_count = 0;
	_image->setFrameX(2);
	_currentFrameX = 2;
	_state = PATTERN1;
	//왕파리 소환하거나 일반파리3마리소환
}

void dukeOfFlies::pattern2()		//파리방출
{
	_count = 0;
	_image->setFrameX(1);
	_currentFrameX = 1;
	_state = PATTERN2;
	//파리자율행동시켜주기
}

bool dukeOfFlies::bulletCountFire()
{
	_fireCount++;
	if (_fireCount % _rndFireConut == 0)
	{
		_rndFireConut = RANDOM->Range(1, 1000);
		_fireCount = 0;

		return true;
	}
	return false;
}

void dukeOfFlies::hitBomb()
{
	 _bombCount = 0; 
	 hp -= 40;
}

HRESULT fly::init()
{
	return S_OK;
}

HRESULT fly::init(const char * imageName, POINT position)
{
	//프레임 변수 초기화
	_bombCount = 30;
	_count = 0;
	_currentFrameX = _currentFrameY = 0;
	//이미지, 이미지렉트 초기화
	_image = IMAGEMANAGER->findImage(imageName);
	_killed = IMAGEMANAGER->findImage("파리사망");
	_killed->setFrameX(0);
	x = position.x;
	y = position.y;
	speed = 3.f;
	//angle = RANDOM->Range(PI / 4 - 0.2f, PI / 4 + 0.2f);
	angle = 0;
	_rc = RectMakeCenter(position.x, position.y, _image->getFrameWidth(), _image->getFrameHeight());
	_state = IDLE;
	//랜덤으로 총알 쿨타임 주는 변수 초기화
	_fireCount = 0;
	_rndFireConut = RANDOM->Range(1, 1000);

	_name = FLY;

	hpMax = hp = 8;

	_duke = true;
	return S_OK;
}

void fly::release()
{
}

void fly::update(float charx, float chary)
{
	if (hp <= 0)
	{
		speed = 0;
		_state = KILLED;
	}

	_bombCount++;
	if (_duke == true)
	{
		x += cosf(angle) * speed;
		y += -sinf(angle) * speed;
	}
	else if (_duke == false)
	{
		speed = 1.5f;
		if (angle != 0)
		{
			x += cosf(angle) * speed;
			y += -sinf(angle) * speed;
		}
		else {
			if (_count > 30) { angle = getAngle(x, y, charx, chary); }
			//angle = getAngle(x, y, charx, chary);
			x += cosf(angle) * speed;
			y += -sinf(angle) * speed;
		}
	}
	if (_state == KILLED) { _rc = RectMakeCenter(x, y, _killed->getFrameWidth(), _killed->getFrameHeight()); }
	else { _rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight()); }
	this->animation();
}

void fly::render()
{
	this->draw();
}

void fly::move()
{
	
}

void fly::draw()
{
	if (_state == KILLED) { _killed->frameRender(getMemDC(), _rc.left, _rc.top, _killed->getFrameX(), _killed->getFrameY()); }
	else { _image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY); }
	//_image->frameRender(getMemDC(), _rc.left, _rc.top, _image->getFrameX(), _image->getFrameY());
}

void fly::animation()
{
	_count++;
	switch (_state)
	{
	case IDLE:
		if (_count%2== 0)
		{
			_image->setFrameX(_image->getFrameX() + 1);
			_currentFrameX++;
			if (_currentFrameX >= _image->getMaxFrameX())
			{
				_currentFrameX = 0;
				//_count = 0;
			}
		}
		break;
	case PATTERN1:			
		break;
	case PATTERN2:		
		break;
	case KILLED:
		if (_count % 4 == 0)
		{
			_killed->setFrameX(_killed->getFrameX() + 1);
			_currentFrameX++;
			if (_currentFrameX >= _killed->getMaxFrameX())
			{
				hp -= 100;
				_currentFrameX = 0;
				//_count = 0;
			}
		}
		break;
	default:
		break;
	}
}

void fly::pattern1()
{
}

void fly::pattern2()
{
}

bool fly::bulletCountFire()
{
	return false;
}

void fly::hitBomb()
{
	_bombCount = 0;
	hp -= 40;
}

void fly::duke()
{
	if (angle == 0) { _count = 30; }
	else { _count = 0; }
	_duke = false; 
}




HRESULT Bfly::init()
{
	return S_OK;
}

HRESULT Bfly::init(const char * imageName, POINT position)
{	
	//프레임 변수 초기화
	_bombCount = 0;
	_count = 0;
	_currentFrameX = _currentFrameY = 0;
	//이미지, 이미지렉트 초기화
	_image = IMAGEMANAGER->findImage(imageName);
	_killed = IMAGEMANAGER->findImage("파리사망");
	_killed->setFrameX(0);

	x = position.x;
	y = position.y;
	speed = 1.0f;
	//angle = RANDOM->Range(PI / 4 - 0.2f, PI / 4 + 0.2f);
	angle = 0;
	_rc = RectMakeCenter(position.x, position.y, _image->getFrameWidth(), _image->getFrameHeight());
	_state = IDLE;
	//랜덤으로 총알 쿨타임 주는 변수 초기화
	_fireCount = 0;
	_rndFireConut = RANDOM->Range(1, 1000);

	_name = BFLY;

	hpMax = hp = 15;

	_duke = false;
	return S_OK;
}

void Bfly::release()
{
}

void Bfly::update(float charx, float chary)
{
	if (hp <= 0) 
	{
		speed = 0;
		_state = KILLED; 
	}

	_bombCount++;
	if (angle != 0)
	{
		x += cosf(angle) * speed;
		y += -sinf(angle) * speed;
	}
	else
	{
		angle = getAngle(x, y, charx, chary);
		x += cosf(angle) * speed;
		y += -sinf(angle) * speed;
	}
	if (_state == KILLED){ _rc = RectMakeCenter(x, y, _killed->getFrameWidth(), _killed->getFrameHeight()); }
	else { _rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight()); }
	this->animation();
}

void Bfly::render()
{
	this->draw();
}

void Bfly::move()
{

}

void Bfly::draw()
{
	if (_state == KILLED) { _killed->frameRender(getMemDC(), _rc.left, _rc.top, _killed->getFrameX(), _killed->getFrameY()); }
	else { _image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY); }
	//_image->frameRender(getMemDC(), _rc.left, _rc.top, _image->getFrameX(), _image->getFrameY());
}

void Bfly::animation()
{
	_count++;
	switch (_state)
	{
	case IDLE:
		if (_count % 2 == 0)
		{
			_image->setFrameX(_image->getFrameX() + 1);
			_currentFrameX++;
			if (_currentFrameX >= _image->getMaxFrameX())
			{
				_currentFrameX = 0;
				_count = 0;
			}
		}
		break;
	case PATTERN1:
		break;
	case PATTERN2:
		break;
	case KILLED:
		if (_count % 4 == 0)
		{
			_killed->setFrameX(_killed->getFrameX() + 1);
			_currentFrameX++;
			if (_currentFrameX >= _killed->getMaxFrameX())
			{
				hp -= 100;
				_currentFrameX = 0;
				//_count = 0;
			}
		}
		break;
	default:
		break;
	}
}

void Bfly::pattern1()
{
}

void Bfly::pattern2()
{
}

bool Bfly::bulletCountFire()
{
	return false;
}

void Bfly::hitBomb()
{
	_bombCount = 0;
	hp -= 40;
}



HRESULT race::init()
{
	return S_OK;
}

HRESULT race::init(const char * imageName, POINT position)
{
	//프레임 변수 초기화
	_bombCount = 0;
	_count = 0;
	_currentFrameX = _currentFrameY = 0;
	//이미지, 이미지렉트 초기화
	_image = IMAGEMANAGER->findImage(imageName);
	_killed = IMAGEMANAGER->findImage("적사망");
	_killed->setFrameX(0);
	alpha = 50;
	x = position.x;
	y = position.y;
	speed = 0.0f;
	//angle = RANDOM->Range(PI / 4 - 0.2f, PI / 4 + 0.2f);
	angle = 0;
	_rc = RectMakeCenter(position.x, position.y, _image->getFrameWidth(), _image->getFrameHeight());
	_state = IDLE;
	//랜덤으로 총알 쿨타임 주는 변수 초기화
	_fireCount = 0;
	_rndFireConut = RANDOM->Range(1, 1000);

	_name = RACE;

	hpMax = hp = 25;

	_fire = false;
	return S_OK;
}

void race::release()
{
}

void race::update(float charx, float chary)
{
	_fireCount++;
	if (hp <= 0)
	{
		hp = -101;
		speed = 0;
		_state = KILLED;
	}
	if (_fireCount > 400) { _fire = true; }
	else { _fire = false; }
	_bombCount++;
	if (alpha <= 10) 
	{
		x = RANDOM->Range(160, 800);
		y = RANDOM->Range(110, 430);
		_count = 0;
		angle = getAngle(x, y, charx, chary); 
		alpha = 255;
	}
	else if (alpha < 80) 
	{
		x = y = -100;
	}


	if (_count > 200 && _count % 7 == 0) { alpha -= alpha / 8; }
	float distance;
	distance = getDistance(x, y, charx, chary);
	if (distance < 300 && _fire == true) { _state = PATTERN1; }

	//if (angle > (PI / 4) * 7 && angle <= PI / 4) { _image->setFrameY(0); }
	//else if (angle > PI / 4 && angle <= (PI / 4) * 3) { _image->setFrameY(1); }
	//else if (angle > (PI / 4) * 3 && angle <= (PI / 4) * 5) { _image->setFrameY(2); }
	//else if (angle > (PI / 4) * 5 && angle <= (PI / 4) * 7) { _image->setFrameY(3); }

	if (angle < PI/4)
	{
		angle = 0;
		_image->setFrameY(0); 
	}
	else if(angle < (PI/4)*3)
	{ 
		angle = PI/2;
		_image->setFrameY(1);
	}
	else if(angle < (PI/4)*5)
	{ 
		angle = PI;
		_image->setFrameY(2); 
	}
	else if(angle < (PI/4)*7)
	{
		angle = (PI/2)*3;
		_image->setFrameY(3); 
	}
	else if(angle <= (PI/4)*8)
	{
		angle = 0;
		_image->setFrameY(0);
	}

	//if (angle != 0)
	//{
	//	x += cosf(angle) * speed;
	//	y += -sinf(angle) * speed;
	//}
	//else
	//{
	//	x += cosf(angle) * speed;
	//	y += -sinf(angle) * speed;
	//}
	if (_state == KILLED) { _rc = RectMakeCenter(x, y, _killed->getFrameWidth(), _killed->getFrameHeight()); }
	else { _rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight()); }
	this->animation();
}

void race::render()
{
	this->draw();
	char str[32];
	if (_state == IDLE) { sprintf(str, "IDLE"); }
	if (_state == PATTERN1) { sprintf(str, "pattern1"); }
	//TextOut(getMemDC(), 300, 300, str, strlen(str));
}

void race::move()
{

}

void race::draw()
{
	//if (_state == KILLED) { _killed->frameRender(getMemDC(), _rc.left, _rc.top, _killed->getFrameX(), _killed->getFrameY()); }
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _image->getFrameY(),alpha);
	//_image->frameRender(getMemDC(), _rc.left, _rc.top, _image->getFrameX(), _image->getFrameY());
}

void race::animation()
{
	_count++;
	switch (_state)
	{
	case IDLE:
		_image->setFrameX(0);
		_currentFrameX = 0;
		//if (_count % 2 == 0)
		//{
		//	_image->setFrameX(_image->getFrameX() + 1);
		//	_currentFrameX++;
		//	if (_currentFrameX >= _image->getMaxFrameX())
		//	{
		//		_currentFrameX = 0;
		//		_count = 0;
		//	}
		//}
		break;
	case PATTERN1:
		if (_count % 10 == 0)
		{
			_image->setFrameX(_image->getFrameX() + 1);
			_currentFrameX++;
			if (_currentFrameX > _image->getMaxFrameX())
			{
				_currentFrameX = 0;
				_state = IDLE;
			}
		}
		break;
	case PATTERN2:
		break;
	case KILLED:
		//if (_count % 4 == 0)
		//{
		//	_killed->setFrameX(_killed->getFrameX() + 1);
		//	_currentFrameX++;
		//	if (_currentFrameX >= _killed->getMaxFrameX())
		//	{
		//		hp -= 100;
		//		_currentFrameX = 0;
		//		//_count = 0;
		//	}
		//}
		break;
	default:
		break;
	}
}

void race::pattern1()
{
}

void race::pattern2()
{
}

bool race::bulletCountFire()
{
	return false;
}

void race::hitBomb()
{
	_bombCount = 0;
	hp -= 40;
}




HRESULT blast::init()
{
	return S_OK;
}

HRESULT blast::init(const char * imageName, POINT position)
{
	//프레임 변수 초기화
	_bombCount = 0;
	_count = 0;
	_currentFrameX = _currentFrameY = 0;
	//이미지, 이미지렉트 초기화
	_image = IMAGEMANAGER->findImage(imageName);
	_killed = IMAGEMANAGER->findImage("적사망");
	_killed->setFrameX(0);
	alpha = 50;
	x = position.x;
	y = position.y;
	//angle = RANDOM->Range(PI / 4 - 0.2f, PI / 4 + 0.2f);
	angle = RANDOM->Range(0,6);
	_rc = RectMakeCenter(position.x, position.y, _image->getFrameWidth(), _image->getFrameHeight());
	_state = IDLE;
	//랜덤으로 총알 쿨타임 주는 변수 초기화
	_fireCount = 0;
	_rndFireConut = RANDOM->Range(1, 1000);
	//inTile = (position.y / 45) * 20 + position.x / 48;
	_name = BLAST;
	if (_image->getFrameWidth() < 40) 
	{
		speed = 2.5f;
		hpMax = hp = 25; 
	}
	else if (_image->getFrameWidth() < 80)
	{
		speed = 3.0f;
		_idle = IMAGEMANAGER->findImage("nomblast");
		hpMax = hp = 50; 
	}
	else
	{
		speed = 4.0f;
		_idle = IMAGEMANAGER->findImage("bigblast");
		hpMax = hp = 80;
	}

	_fire = false;
	return S_OK;
}

void blast::release()
{
}

void blast::update(float charx, float chary)
{
	if (_state == KILLED) { _rc2 = RectMakeCenter(x, y, _killed->getFrameWidth(), _killed->getFrameHeight()); }
	
	_fireCount++;
	if (hp <= 0)
	{
		speed = 0;
		_state = KILLED;
	}
	_bombCount++;

	if (angle == 0) { angle = getAngle(x, y, charx, chary); }
	if (_fireCount == 5 && hpMax >40) 
	{
		int a;
		a = RANDOM->Range(1,2); 
		if (a == 1) { _idle->setFrameY(0); }
		else if (a == 2) { _idle->setFrameY(1); }
	}
	if (_fireCount > 80 && _state != KILLED) 
	{
		if (angle > PI / 2 && angle < (PI / 2) * 3) { _image->setFrameY(1); }
		else { _image->setFrameY(0); }
		_state = PATTERN1; 
	}
	
	if (_state == PATTERN1)
	{
		int a;
		if (_currentFrameX < 4) { a = -2; }
		else { a = 2; }
		x += cosf(angle) * speed;
		y += -sinf(angle) * speed + a;
	}

	if (_rc.left < 150)
	{
		x+= 5;
		angle = PI - angle;
	}
	//오른쪽
	if (_rc.right > WINSIZEX - 150)
	{
		x-=5;
		angle = PI - angle;
	}
	//위
	if (_rc.top < 95)
	{
		y+= 5;
		angle = 2 * PI - angle;
	}
	//아래
	if (_rc.bottom > WINSIZEY - 95)
	{
		y-= 5;
		angle = 2 * PI - angle;
	}
	//if (angle != 0)
	//{
	//	x += cosf(angle) * speed;
	//	y += -sinf(angle) * speed;
	//}
	//else
	//{
	//	x += cosf(angle) * speed;
	//	y += -sinf(angle) * speed;
	//}
	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight()); 
	this->animation();
}

void blast::render()
{
	this->draw();
	
}

void blast::move()
{

}

void blast::draw()
{
	if (hpMax < 30) { _image->frameRender(getMemDC(), _rc.left, _rc.top, _image->getFrameX(), _image->getFrameY()); }
	else 
	{
		if (_state == IDLE) { _idle->frameRender(getMemDC(), _rc.left, _rc.top, _image->getFrameX(), _image->getFrameY()); }
		else if (_state == KILLED)
		{
			_idle->frameRender(getMemDC(), _rc.left, _rc.top, _image->getFrameX(), _image->getFrameY());
				for (int i = 0; i < 3; i++)
				{
					_killed->scaleFrameRender(getMemDC(), _rc2.left + (RANDOM->Range(-3, 3) * 10)-20, _rc2.top + (RANDOM->Range(-3, 3) * 10)-20, _killed->getFrameX(), _killed->getFrameY(), 1.5f);
				}
		}
		else { _image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _image->getFrameY()); }
	}
	
}

void blast::animation()
{
	_count++;
	switch (_state)
	{
	case IDLE:
		_image->setFrameX(0);
		_currentFrameX = 0;
		
		break;
	case PATTERN1:
		if (_count % 5 == 0)
		{
			_image->setFrameX(_image->getFrameX() + 1);
			_currentFrameX++;
			if (_currentFrameX > _image->getMaxFrameX())
			{
				angle = 0;
				_fireCount = 0;
				_currentFrameX = 0;
				_state = IDLE;
			}
		}
		break;
	case PATTERN2:
		break;
	case KILLED:
		if (hpMax > 40)
		{
			if (_count % 6 == 0)
			{
				_killed->setFrameX(_killed->getFrameX() + 1);
				_currentFrameX++;
				if (_currentFrameX >= _killed->getMaxFrameX())
				{
					hp -= 30;
					_killed->setFrameX(0);
					_currentFrameX = 0;
					_count = 0;
				}
			}
		}

		else 
		{
			if (_count % 4 == 0)
			{
				_killed->setFrameX(_killed->getFrameX() + 1);
				_currentFrameX++;
				if (_currentFrameX >= _killed->getMaxFrameX())
				{
					hp -= 100;
					_currentFrameX = 0;
					//_count = 0;
				}
			}
		}
		break;
	default:
		break;
	}
}

void blast::pattern1()
{
}

void blast::pattern2()
{
}

bool blast::bulletCountFire()
{
	return false;
}

void blast::hitBomb()
{
	_bombCount = 0;
	hp -= 40;
}


//=============================================OBJECT===========================================



HRESULT fire::init()
{
	return S_OK;
}

HRESULT fire::init(const char * imageName, POINT position)
{
	//프레임 변수 초기화
	_count = 0;
	_currentFrameX = _currentFrameY = 0;

	//이미지, 이미지렉트 초기화
	_image = IMAGEMANAGER->findImage(imageName);
	_fireWood = IMAGEMANAGER->findImage("firewood");
	x = position.x;
	y = position.y;
	speed = 0.0f;
	//angle = RANDOM->Range(PI / 4 - 0.2f, PI / 4 + 0.2f);
	angle = 0;
	_rc = RectMakeCenter(position.x, position.y-15, _image->getFrameWidth(), _image->getFrameHeight()+15);
	_rc2 = RectMakeCenter(position.x, position.y+10, _fireWood->getWidth(), _fireWood->getHeight());
	_rc3 = RectMakeCenter(position.x, position.y-15, _image->getFrameWidth(), _image->getFrameHeight());
	_state = IDLE;
	//랜덤으로 총알 쿨타임 주는 변수 초기화
	_fireCount = 0;
	scale = 0;
	_rndFireConut = RANDOM->Range(1, 1000);
	inTile = (position.y / 45) * 20 + position.x / 48;
	_name = FIRE;

	hpMax = hp = 20;

	
	return S_OK;
}

void fire::release()
{
}

void fire::update(float charx, float chary)
{
	if (hp > 15)		{ scale = 1.1f; }
	else if (hp > 10)	{ scale = 0.8f; }
	else if (hp > 5)	{ scale = 0.6f; }
	else if (hp > 0)	{ scale = 0.4f; }
	else if (hp <= 0)	{ scale = 0.f; }
	_rc3 = RectMakeCenter(x, y-5, _image->getFrameWidth()*scale, _image->getFrameHeight()*scale);
	this->animation();
}

void fire::render()
{
	this->draw();
}

void fire::move()
{

}

void fire::draw()
{
	_fireWood->render(getMemDC(), _rc2.left-2, _rc2.top-10);
	if (scale > 0.f) { _image->scaleFrameRender(getMemDC(), _rc3.left-2, _rc3.top-(18*scale), _currentFrameX, _currentFrameY, scale); }
}

void fire::animation()
{
	_count++;
	if (_count % 4 == 0)
	{
		_image->setFrameX(_image->getFrameX() + 1);
		_currentFrameX++;
		if (_currentFrameX >= _image->getMaxFrameX())
		{
			_currentFrameX = 0;
			//_count = 0;
		}
	}
}

void fire::pattern1()
{
}

void fire::pattern2()
{
}

bool fire::bulletCountFire()
{
	return false;
}



HRESULT poop::init()
{
	return S_OK;
}

HRESULT poop::init(const char * imageName, POINT position)
{
	//프레임 변수 초기화
	_count = 0;
	_currentFrameX = _currentFrameY = 0;

	//이미지, 이미지렉트 초기화
	_image = IMAGEMANAGER->findImage(imageName);
	x = position.x;
	y = position.y;
	speed = 0.0f;
	//angle = RANDOM->Range(PI / 4 - 0.2f, PI / 4 + 0.2f);
	angle = 0;
	_rc = RectMakeCenter(position.x, position.y, _image->getFrameWidth(), _image->getFrameHeight());
	_state = IDLE;
	//랜덤으로 총알 쿨타임 주는 변수 초기화
	_fireCount = 0;
	_rndFireConut = RANDOM->Range(1, 1000);

	_name = POOP;
	inTile = (position.y / 45) * 20 + position.x / 48;
	hpMax = hp = 20;


	return S_OK;
}

void poop::release()
{
}

void poop::update(float charx, float chary)
{
	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());
	//_rc = RectMakeCenter(x, y, 48,45);
	this->animation();
}

void poop::render()
{
	this->draw();
}

void poop::move()
{

}

void poop::draw()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	//Rectangle(getMemDC(), _rc);
}

void poop::animation()
{
	if (hp > 15) { _currentFrameX = 0; }
	else if (hp > 8) { _currentFrameX = 1; }
	else if (hp > 0) { _currentFrameX = 2; }
	else if (hp <= 0) { _currentFrameX = 3; }
}

void poop::pattern1()
{
}

void poop::pattern2()
{
}

bool poop::bulletCountFire()
{
	return false;
}