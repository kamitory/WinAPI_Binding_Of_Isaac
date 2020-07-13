#include "stdafx.h"
#include "bullet.h"

//=============================================================
//	## bullet ## (�����Ѿ� - ������� ������ ��)
//=============================================================
HRESULT bullet::init(const char * imageName, int bulletMax, float range, bool isFrameImg)
{
	//�Ѿ� �̹��� �ʱ�ȭ
	_imageName = imageName;
	//�Ѿ˰��� �� ��Ÿ� �ʱ�ȭ
	_bulletMax = bulletMax;
	_range = range;
	//�Ѿ��̹����� ������ �̹�����?
	_isFrameImg = isFrameImg;
	
	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	this->move();
}

void bullet::render()
{
	
	if (_isFrameImg)//������ �̹���
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			_vBullet[i].bulletImage->frameRender(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
		}
	}
	else//�Ϲ� �̹���
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
		}
	}
}

void bullet::render(float x, float y, int alpha, int xxx)					//���ɿ�
{

	if (_isFrameImg)//������ �̹���
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			_vBullet[i].bulletImage->frameRender(getMemDC(), _vBullet[i].rc.left-x, _vBullet[i].rc.top-y, _vBullet[i].bulletImage->getFrameX(), _vBullet[i].bulletImage->getFrameY(),alpha);
		}
	}
	else//�Ϲ� �̹���
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			_vBullet[i].bulletImage->alphaRender(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top,alpha);
		}
	}
}


void bullet::render(float x, float y,float range)	//�÷��̾��
{

	if (_isFrameImg)//������ �̹���
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			_vBullet[i].bulletImage->scaleFrameRender(getMemDC(), _vBullet[i].rc.left - x, _vBullet[i].rc.top - y, scale);
		}
	}
	else//�Ϲ� �̹���
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			_vBullet[i].bulletImage->scaleRender(getMemDC(), _vBullet[i].rc.left - x, _vBullet[i].rc.top - y, scale);
		}
	}
	
}

void bullet::fire(float x, float y, float angle, float speed,float damage)
{
	//�Ѿ� ���Ϳ� ��°��� �����Ѵ�
	if (_bulletMax < _vBullet.size() + 1) return;

	//�Ѿ� ����ü ����
	tagBullet bullet;
	//�Ѿ˱���ü �ʱ�ȭ
	//���θ޸�, ���
	//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.gravity = 1.f;
	if (damage < 3) { scale = 0.6f; }
	else if (damage < 15) { scale = 0.6f + damage / 10; }
	else { scale = 2.5f; }
	if (_isFrameImg)
	{
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getFrameWidth()*scale,
			bullet.bulletImage->getFrameHeight()*scale);
	}
	else
	{
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth()*scale,
			bullet.bulletImage->getHeight()*scale);
	}

	//���Ϳ� ���
	_vBullet.push_back(bullet);
}

void bullet::move()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
		_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed;

		if (_isFrameImg)
		{
			_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getFrameWidth(),
				_vBullet[i].bulletImage->getFrameHeight());
		}
		else
		{
			_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getWidth(),
				_vBullet[i].bulletImage->getHeight());
		}

		//�Ѿ��� ��Ÿ� ���� Ŀ������
		float distance = getDistance(_vBullet[i].fireX, _vBullet[i].fireY,
			_vBullet[i].x, _vBullet[i].y);
		if (_range < distance)
		{
			_vBullet.erase(_vBullet.begin() + i);
		}

	}
}void bullet::move(float range)  //�����۴�����
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
		_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed + _vBullet[i].gravity-1;
		if (_vBullet[i].y > _vBullet[i].fireY+150 ){ _vBullet[i].y -= 1.5f* _vBullet[i].gravity - 1;}
		if (_isFrameImg)
		{
			_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getFrameWidth()*scale,
				_vBullet[i].bulletImage->getFrameHeight()*scale);
		}
		else
		{
			_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getWidth()*scale,
				_vBullet[i].bulletImage->getHeight()*scale);
		}

		//�Ѿ��� ��Ÿ� ���� Ŀ������
		float distance = getDistance(_vBullet[i].fireX, _vBullet[i].fireY,
			_vBullet[i].x, _vBullet[i].y);
		if (range - (_vBullet[i].speed*20) < distance) { _vBullet[i].gravity *= 1.1f; }
		if (_range < distance|| _vBullet[i].gravity > 10.f)
		{
			_vBullet.erase(_vBullet.begin() + i);
		}

	}
}
//��ź ����
void bullet::removeBullet(int index)
{
	_vBullet.erase(_vBullet.begin() + index);
}

//=============================================================
//	## missile ## (missile[0] -> �迭ó�� �̸� �����صΰ� �Ѿ˹߻�)
//=============================================================
HRESULT missile::init(int bulletMax, float range)
{
	//�Ѿ� ��Ÿ� �� �Ѿ� ���� �ʱ�ȭ
	_range = range;
	_bulletMax = bulletMax;

	//�Ѿ��� ������ŭ ����ü�� �ʱ�ȭ �� �� ���Ϳ� ���
	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ� ����ü ����
		tagBullet bullet;
		//�Ѿ˱���ü �ʱ�ȭ
		//���θ޸�, ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("Images/missile.bmp", 26, 124, true, RGB(255, 0, 255));
		bullet.speed = 5.0f;
		bullet.fire = false;

		//���Ϳ� ���
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missile::release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}

void missile::update()
{
	this->move();
}

void missile::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
	}
}

void missile::fire(float x, float y)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());
		break;
	}
}

void missile::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());
		
		//�Ѿ��� ��Ÿ����� Ŀ������
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		if (_range < distance)
		{
			_viBullet->fire = false;
		}
	}
}

//=============================================================
//	## bomb ## (��źó�� �ѹ߾� �߻��ϰ� �����ϰ� �ڵ�����)
//=============================================================
HRESULT bomb::init(int bulletMax, float range)
{
	//�Ѿ˰���, ��Ÿ� �ʱ�ȭ
	_bulletMax = bulletMax;
	_range = range;
	_loop = false;
	//_viBullet->_imageSwitching = 0;
	return S_OK;
}
HRESULT bomb::init(int bulletMax)
{
	//�Ѿ˰���, ��Ÿ� �ʱ�ȭ
	_bulletMax = bulletMax;
	_range = 0;
	_loop = false;
	//_viBullet->_imageSwitching = 0;
	return S_OK;
}
void bomb::release()
{
}

void bomb::update()
{
	this->move();
}

void bomb::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
		
		_viBullet->count++;
		if (_viBullet->count % 3 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}


void bomb::render(float x, float y)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left-x, _viBullet->rc.top-y);
			
		//RECT rc;
		//rc = RectMake(_viBullet->rc.left - x, _viBullet->rc.top -y ,10,10);
		//Rectangle(getMemDC(), rc);

		_viBullet->count++;
		
		if (_viBullet->count % 5 == 0)
		{
			_viBullet->_imageSwitching++;
			if (_viBullet->_imageSwitching == 8 && _loop == false) 
			{
				_loop = true; 
				_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX()-4);
				_viBullet->_imageSwitching -= 4; 
			}
			else if (_viBullet->_imageSwitching == 14 && _loop == true)
			{
				_loop = false;
				_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() - 4);
				_viBullet->_imageSwitching -= 4;
			}
			char str[32];
			sprintf(str, "%d", _viBullet->_imageSwitching);
			TextOut(getMemDC(), 321, 321, str, strlen(str));

			 _viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1); 
	//		if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
	//		{
	//			_viBullet->bulletImage->setFrameX(0);
	//		}
			
		}
		//Rectangle(getMemDC(), _viBullet->rc);
	}
}

void bomb::fire(float x, float y,bool sadbomb)
{
	//�Ѿ� ���Ϳ� ��°��� �����Ѵ�
	if (_bulletMax < _vBullet.size() + 1) return;

	//�Ѿ� ����ü ����
	tagBullet bullet;
	//�Ѿ˱���ü �ʱ�ȭ
	//���θ޸�, ���
	//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
	ZeroMemory(&bullet, sizeof(tagBullet));
	//bullet.bulletImage = new image;
	//bullet.bulletImage->init("Images/missile1.bmp", 416, 64, 13, 1);
	if (sadbomb == false) { bullet.bulletImage = IMAGEMANAGER->findImage("bomb"); }
	else if (sadbomb == true) { bullet.bulletImage = IMAGEMANAGER->findImage("sadbomb"); }
	//bullet.bulletImage = IMAGEMANAGER->findImage("explosion");
	bullet.bulletImage->setFrameX(0);
	bullet.speed = 0.0f;
	bullet._imageSwitching = 0;
	bullet.x = bullet.fireX = x-3;
	bullet.y = bullet.fireY = y-3;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	//���Ϳ� ���
	_vBullet.push_back(bullet);
}

void bomb::move()
{
	
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
	//	_viBullet->y -= _viBullet->speed;
	
		if (_viBullet->_imageSwitching == 16 && _viBullet->count % 5 != 0)
		{
			_viBullet->_imageSwitching++;
		}
		else if (_viBullet->_imageSwitching == 16) 
		{
			_viBullet->bulletImage = IMAGEMANAGER->findImage("explosion");
			_viBullet->y -= 45;
			_viBullet->bulletImage->setFrameX(0);
		}
		if (_viBullet->_imageSwitching == 19) 
		{
			_viBullet->_imageSwitching++;
			_viBullet->y += 25;	
		}


			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getFrameWidth(),
				_viBullet->bulletImage->getFrameHeight());
		
	//
	//	//��ź�� ��Ÿ����� Ŀ������
	//	float distance = getDistance(_viBullet->fireX, _viBullet->fireY,
	//		_viBullet->x, _viBullet->y);
	//	if (_range < distance)
	//	{
	//		_viBullet->bulletImage->release();
	//		SAFE_DELETE(_viBullet->bulletImage);
	//		_viBullet = _vBullet.erase(_viBullet);
	//	}
	//	else
	//	{
	//	++_viBullet;
	//	}


	if (_viBullet->_imageSwitching == 21) { _viBullet = _vBullet.erase(_viBullet); }
	else { ++_viBullet; }

	}
}
//��ź ����
void bomb::removeBomb(int index)
{
	_vBullet.erase(_vBullet.begin() + index);
}
