#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	//미니언 생성, 보스, 일반몬스터
	//따로 함수로 빼서 처리하면 관리및 보기에 편하다

	//미니언 생성
	//this->setDuke();
	//this->setFly(WINSIZEX/2,150);

	//보스생성
	//this->setBoss();
	flyCount = 0;
	
	this->setObject(1, 111);
	this->setObject(1, 112);
	this->setObject(1, 113);
	this->setObject(1, 131);
	this->setObject(1, 133);
	this->setObject(1, 151);
	this->setObject(1, 152);
	this->setObject(1, 153);


	this->setObject(2, 105);
	this->setObject(2, 106);
	this->setObject(2, 107);
	this->setObject(2, 125);
	this->setObject(2, 127);
	this->setObject(2, 145);
	this->setObject(2, 146);
	this->setObject(2, 147);
	
	//총알 클래스 초기화
	_bullet = new bullet;
	_bullet->init("bullet", 15, 250);
	mapNum = 0;
	count = 0;
	return S_OK;
	
}

void enemyManager::release()
{
	//총알 클래스 삭제
	_bullet->release();
	SAFE_DELETE(_bullet);
}

void enemyManager::update()
{
	
	count+=0.01f;
	flyCount = 0;
	//총알 업데이트
	_bullet->update();
	if (_vMinion.empty() == true){}
	
	else if (_vMinion.empty() == false)
	{
		if (_vMinion[0]->getName() == DUKE && _vMinion[0]->getDuke() == true)
		{
			_vMinion[0]->duke();
			int a = RANDOM->Range(1, 5);
			//a = 1;
			if (a == 1) { this->setBFly(cosf(angle) * 80.0f + _vMinion[0]->getEnemyX(), -sinf(angle) * 80.0f + _vMinion[0]->getEnemyY()); }
			else
			{
				for (int i = 0; i < 3; i++)
				{
					float angle;
					angle = ((_vMinion.size() + PI) / 2) + count;

					this->setFly
					(cosf(angle) * 80.0f + _vMinion[0]->getEnemyX()
						, -sinf(angle) * 80.0f + _vMinion[0]->getEnemyY());
				}
			}
		}



		//벡터에 담긴 미니언들 업데이트
		for (int i = 0; i < _vMinion.size(); i++)
		{
			for (int j = 0; j < _vMinion.size(); j++)
			{
				if (i == j) { continue; }
				float distance = getDistance(_vMinion[i]->getEnemyX(), _vMinion[i]->getEnemyY(), _vMinion[j]->getEnemyX(), _vMinion[j]->getEnemyY());

				if (30 < distance) { continue; }
				_vMinion[i]->setAngle(getAngle(_vMinion[j]->getEnemyX(), _vMinion[j]->getEnemyY(), _vMinion[i]->getEnemyX(), _vMinion[i]->getEnemyY()));
				_vMinion[j]->setAngle(getAngle(_vMinion[i]->getEnemyX(), _vMinion[i]->getEnemyY(), _vMinion[j]->getEnemyX(), _vMinion[j]->getEnemyY()));
			}
			//======================================안겹치게 하기위한 각도===================================
			if (_vMinion[0]->getName() != DUKE && _vMinion[i]->getDuke() == true) { _vMinion[i]->duke(); } //1번이 파리공자아니면 파리 자유행동
			if (_vMinion[i]->getName() == FLY && _vMinion[i]->getDuke() == true) //파리공자있을때 파리의행동
			{
				flyCount++;
				angle = ((PI + i) / 2) + count;
				
				float dukeAngle;

				dukeAngle = getAngle(_vMinion[i]->getEnemyX(),_vMinion[i]->getEnemyY(),
					cosf(angle) * 80.0f + _vMinion[0]->getEnemyX(), -sinf(angle) * 80.0f + _vMinion[0]->getEnemyY());
				_vMinion[i]->setAngle(dukeAngle);
				//_vMinion[i]->setEnemyX(cosf(angle) * 80.0f + _vMinion[0]->getEnemyX());
				//_vMinion[i]->setEnemyY(-sinf(angle) * 80.0f + _vMinion[0]->getEnemyY());
			}
			_vMinion[i]->update(_player->getCX(), _player->getCY());
			//=====================================파리공자가 소환할때 각도정해주기==========================
			if (_vMinion[i]->getName() == FLY && _vMinion[0]->getState() == PATTERN2 && _vMinion[0]->getFrameX() == 3)
			{
				angle = ((PI + i) / 2) + count;
				_vMinion[i]->setAngle(angle);
				if (_vMinion[i]->getDuke() == true) { _vMinion[i]->duke(); }
			}
			else if (_vMinion[i]->getName() == FLY) { _vMinion[i]->setAngle(0); }
			else if (_vMinion[i]->getName() == BFLY) { _vMinion[i]->setAngle(0); }
			//=====================================파리를 방출햇을때 파리의 각도를 바꿔주기=========================
			if (_vMinion[i]->getName() == RACE && _vMinion[i]->getState() == PATTERN1 && _vMinion[i]->getDuke() ==true)
			{
				_bullet->fire(_vMinion[i]->getEnemyX(),_vMinion[i]->getEnemyY(),_vMinion[i]->getEAngle(),3.0,1.0f);
				_vMinion[i]->duke();
			}
			//======================================레이스가 쏠준비 되있을때=======================================
			for (int j = 0; j < _player->getBullet()->getBullet().size(); j++)
			{
				RECT rc;
				if (IntersectRect(&rc, &_player->getBullet()->getBullet()[j].rc, &_vMinion[i]->getRect()) && _vMinion[i]->getHp() > 0)
				{
					_player->getBullet()->removeBullet(j);
					_vMinion[i]->hitDamage(_player->getAttPower());
					break;
				}
			}
			for (int j = 0; j < _player->getBomb()->getBullet().size(); j++)
			{
				RECT rc;
				RECT _explosion;
				_explosion = _player->getBomb()->getBullet()[j].rc;

				_explosion.left += 15;
				_explosion.right -= 15;
				_explosion.top += 65;
				if (_player->getBomb()->getBullet()[j]._imageSwitching == 17 || _player->getBomb()->getBullet()[j]._imageSwitching == 18)
				{
					if (IntersectRect(&rc, &_player->getBomb()->getBullet()[j].rc, &_vMinion[i]->getRect())&& _vMinion[i]->getBombCount ()>30)
					{
						_vMinion[i]->hitBomb();
					}
				}
			}
			if (_vMinion[i]->getHp() <= -100) // 몹사망
			{
				if (_vMinion[i]->getName() != RACE)
				{
					_blood.push_back(PointMake(_vMinion[i]->getEnemyX(), _vMinion[i]->getEnemyY()));
					_bloodtype.push_back(RANDOM->Range(1, 4));
				}
				if (_vMinion[i]->getName() == BLAST && _vMinion[i]->getHpMax() > 70)
				{
					this->setnomblast(_vMinion[i]->getEnemyX() - 30, _vMinion[i]->getEnemyY() - 30);
					this->setnomblast(_vMinion[i]->getEnemyX() + 30, _vMinion[i]->getEnemyY() + 30);
				}
				else if (_vMinion[i]->getName() == BLAST && _vMinion[i]->getHpMax() > 30)
				{

					this->setsmallblast(_vMinion[i]->getEnemyX() - 30, _vMinion[i]->getEnemyY() - 30);
					this->setsmallblast(_vMinion[i]->getEnemyX() + 30, _vMinion[i]->getEnemyY() + 30);
				}
				removeMinion(i); 
			}
		}
		if (flyCount > 4 && _vMinion[0]->getState() == IDLE) { _vMinion[0]->pattern2(); }


	}
	//미니언 총알발사
	//this->minionBulletFire();
	for (int i = 0; i < _object.size(); i++)
	{
		_object[i]->update(0,0);
		for (int j = 0; j < _player->getBullet()->getBullet().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_player->getBullet()->getBullet()[j].rc, &_object[i]->getRect()))
			{
				if (mapNum == 10)
				{
					if (_object[i]->getHp() > 0) { _player->getBullet()->removeBullet(j); }
					_object[i]->hitDamage(_player->getAttPower());
					break;
				}
			}
		}
	}
	//충돌함수
	this->collision();
}

void enemyManager::bloodrender()
{
	for (int i = 0; i < _blood.size(); i++)
	{
		image* _image;
		char str[32];
		sprintf(str, "bloodstain%d",_bloodtype[i]);
		_image = IMAGEMANAGER->findImage(str);
	
		RECT blood;
		blood = RectMakeCenter(_blood[i].x, _blood[i].y, _image->getWidth(),_image->getHeight());
		_image->alphaRender(getMemDC(), blood.left, blood.top, 100);
	}
}
void enemyManager::render()
{
	//총알클래스 렌더
	_bullet->render();

	//벡터에 담긴 미니언들 렌더
	for (int i = 0; i < _vMinion.size(); i++)
	{
		_vMinion[i]->render();
	}
	if (mapNum == 10)
	{
		for (int i = 0; i < _object.size(); i++)
		{
			_object[i]->render();
		}
	}
}

void enemyManager::setDuke()
{
		enemy* _duke = new dukeOfFlies;
		_duke->init("파리공자", PointMake(WINSIZEX / 2, 150));
		_vMinion.push_back(_duke);
}
void enemyManager::setFly(float x, float y) //파리소환시 시작위치주기
{
	enemy* _fly = new fly;
	_fly->init("파리", PointMake(x,y));
	_vMinion.push_back(_fly);
}
void enemyManager::setBFly(float x, float y) //파리소환시 시작위치주기
{
	enemy* _Bfly = new Bfly;
	_Bfly->init("왕파리", PointMake(x, y));
	_vMinion.push_back(_Bfly);
}
void enemyManager::setRace(float x, float y)
{
	enemy* _race = new race;
	_race->init("유령", PointMake(x, y));
	_vMinion.push_back(_race);
}
void enemyManager::setblast(float x, float y)
{
	enemy* _blast = new blast;
	_blast->init("bigblastjump", PointMake(x, y));
	_vMinion.push_back(_blast);
}
void enemyManager::setnomblast(float x, float y)
{
	enemy* _blast = new blast;
	_blast->init("nomblastjump", PointMake(x, y));
	_vMinion.push_back(_blast);
}
void enemyManager::setsmallblast(float x, float y)
{
	enemy* _blast = new blast;
	_blast->init("smallblast", PointMake(x, y));
	_vMinion.push_back(_blast);
}
void enemyManager::minionBulletFire()
{
	//_viMinion = _vMinion.begin();
	//for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	//{
	//	//int a = 10;
	//	//int* p = &a;
	//	//cout << p << endl; //a의 주소
	//	//cout << *p << endl; //a의 값
	//	if ((*_viMinion)->bulletCountFire())
	//	{
	//		RECT rc = (*_viMinion)->getRect();
	//		_bullet->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 30, -(PI_2), 3.0f);
	//	}
	//}
}

void enemyManager::removeMinion(int index)
{
	_vMinion.erase(_vMinion.begin() + index);
}

void enemyManager::setObject(int kind, int tileNum)
{
	if (kind == 1)
	{
		enemy* _fire = new fire;
		_fire->init("bonfire", tilesCenter(tileNum));
		_object.push_back(_fire);
	}
	else if (kind == 2)
	{
		enemy* _poop = new poop;
		_poop->init("poop", tilesCenter(tileNum));
		_object.push_back(_poop);
	}
}

void enemyManager::collision()
{
	//충돌함수 (미니언들의 총알들, 플레이어)
	for (int i = 0; i < _bullet->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_bullet->getBullet()[i].rc,
			&_player->getPlayerRect()))
		{
			//공용총알 삭제
			_bullet->removeBullet(i);
			//플레이어 피통깍기
			_player->hitDamage(1);
			break;
		}
	}
}

POINT enemyManager::tilesCenter(int i)
{
	return POINT(PointMake((i % 20 * 48) + 24, (i / 20 * 45) + 22));
}
