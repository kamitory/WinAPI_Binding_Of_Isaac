#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "progressBar.h"

//상호참조용 클래스 전방선언
class enemyManager;

enum STATE
{
	NORMAL,
	SHOT,
	HIT,
	DEAD,
	STATUP,
	STATDOWN,
	PICKUP
};

struct plusHp
{
	int _hp;
	bool blackHeart;
};

class player : public gameNode
{
private:
	enemyManager* _em;  //절대로 동적할당 놉!!
	//메인게임에서 생성한 EM과 플레이어에서 생성한 EM은
	//전혀 다른 메모리 주소라서 서로 참조할 수 없다!!!
	plusHp _blackHeart;
	plusHp _soulHeart;

	bullet* _bullet;
	bomb* _bomb;
	vector<plusHp> _plusHp;
private:
	//image* _bag;		//백그라운드 이미지
	//image* _bgImg;		//백그라운드 이미지
	image* _widthrun;			//공이미지
	image* _heightrun;			//공이미지
	image* _face;			//공이미지
	image* _hit;			//공이미지
	image* _statUp;			//공이미지
	image* _statDown;			//공이미지
	image* _pickUp;			//공이미지
	//image* _map;			//맵

	STATE _state;

	float _cx, _cy;			//위치좌표
	float x, y;				//랜더차이위한좌표
	float xs, ys;			//충돌시 x차이값저장
	float xm, ym;			//미니맵 좌표
	int count;
	int alpha;				//알파블랜더 무적용

	int item;
	bool blackheartAtt;
	image* _bh;
	RECT _bhrc;
	int _bhAlpha;

	bool sadbomb;
	bool tearDetonator;
	bool ouijaBoard;
	bool blacklotus;
	bool quarter;
	int tearDetonatorCount;

	float moveSpeed;		//아이작이동속도
	float attPower;			//공격력
	int attSpeed;			//눈물발사속도
	int attCount;			//공격
	int bulletSpeed;		//눈물날아가는속도
	int bulletRange;		//눈물사거리
	int invicount;

	bool _eternal;			//이터널하트여부

	
	int _hp;
	int _hpMax;
	int _penny;
	int _haveBomb;
	int _key;
	
	
	//int _probeY;			//픽셀충돌 탐지할 top값
	//int _probeCY;			//픽셀충돌 탐지할 bottob값
	//int _probeX;			//픽셀충돌 탐지할 left값
	//int _probeCX;			//픽셀충돌 탐지할 right값     픽셀충돌할차례

	RECT Head;
	RECT playerRc;
	RECT Charicter;
	RECT _rcCam;
	int _headIndex;
	int _runIndexX;
	int _runIndexY;


public:
	HRESULT init();
	void release();
	void update();
	void update(float tileEndX, float tileEndY);
	void render();

	void animation();


	void hitDamage(float damage); 
	void heartAtt(); 
	void invi();
	void statUp();
	void statDown();
	void pickUp();
	void move();
	void move(int direction);
	//image* getPlayerImg() { return _rocket; }

	float getCameraX() { return  x; }
	void setCameraX(float _x) { x = _x; }
	float getCameraY() { return  y; }
	void setCameraY(float _y) { y = _y; }
	float getCharX() { return _cx - x; }		 //랜더위치
	float getCharY() { return _cy - y; }		 //랜더위치
	float getCY() { return _cy; }				//실제위치
	float getCX() { return _cx; }				//실제위치

	float getAttPower() { return attPower; }
	void setAttPwer(float dam) { attPower = dam; }
	RECT getPlayerbody() { return playerRc;} //피격용렉트
	RECT getPlayerRect() { return RectMake(Head.left, Head.top, 56, 67); } //무빙용렉트
	
	bool getOuijaBoard() { return ouijaBoard; }

	int getKey() { return _key; }
	void setKey(int key) { _key = key; }
	void setbomb(int bomb) { _haveBomb = bomb; }

	float getSpeed() { return moveSpeed; }
	void setSpeed(float speed) { moveSpeed = speed; }
	
	//상호참조시 적매니져 포인터를 넘겨받을 셋터함수
	void setEMLink(enemyManager* em) { _em = em; }
	void NumberRender(int x, int y, int hp);
	void maxHpRender(int hpMax);
	void HpRender(int hp);
	void eternalGet();
	void EternalHpRender(int hpMax);
	void plusHeart(int hpMax,vector<plusHp> plusHp);
	bullet* getBullet() { return _bullet; }
	bomb* getBomb() { return _bomb; }
	void removeBullet(int index) { _bullet->removeBullet(index); }
	void hpMaxUp();
	void plusHpMaxUp(bool blackHeart);

	bool getItem(int itemNum);
	void pickUpTearDetonator();
	void pickUpSadbBmb();
	void pickUpOuijaBoard();
	void pickUpLotus();
	void pickUpQuarter();
	

	player() {}
	~player() {}
};

