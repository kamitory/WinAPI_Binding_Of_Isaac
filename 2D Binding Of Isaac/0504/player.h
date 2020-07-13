#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "progressBar.h"

//��ȣ������ Ŭ���� ���漱��
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
	enemyManager* _em;  //����� �����Ҵ� ��!!
	//���ΰ��ӿ��� ������ EM�� �÷��̾�� ������ EM��
	//���� �ٸ� �޸� �ּҶ� ���� ������ �� ����!!!
	plusHp _blackHeart;
	plusHp _soulHeart;

	bullet* _bullet;
	bomb* _bomb;
	vector<plusHp> _plusHp;
private:
	//image* _bag;		//��׶��� �̹���
	//image* _bgImg;		//��׶��� �̹���
	image* _widthrun;			//���̹���
	image* _heightrun;			//���̹���
	image* _face;			//���̹���
	image* _hit;			//���̹���
	image* _statUp;			//���̹���
	image* _statDown;			//���̹���
	image* _pickUp;			//���̹���
	//image* _map;			//��

	STATE _state;

	float _cx, _cy;			//��ġ��ǥ
	float x, y;				//��������������ǥ
	float xs, ys;			//�浹�� x���̰�����
	float xm, ym;			//�̴ϸ� ��ǥ
	int count;
	int alpha;				//���ĺ��� ������

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

	float moveSpeed;		//�������̵��ӵ�
	float attPower;			//���ݷ�
	int attSpeed;			//�����߻�ӵ�
	int attCount;			//����
	int bulletSpeed;		//�������ư��¼ӵ�
	int bulletRange;		//������Ÿ�
	int invicount;

	bool _eternal;			//���ͳ���Ʈ����

	
	int _hp;
	int _hpMax;
	int _penny;
	int _haveBomb;
	int _key;
	
	
	//int _probeY;			//�ȼ��浹 Ž���� top��
	//int _probeCY;			//�ȼ��浹 Ž���� bottob��
	//int _probeX;			//�ȼ��浹 Ž���� left��
	//int _probeCX;			//�ȼ��浹 Ž���� right��     �ȼ��浹������

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
	float getCharX() { return _cx - x; }		 //������ġ
	float getCharY() { return _cy - y; }		 //������ġ
	float getCY() { return _cy; }				//������ġ
	float getCX() { return _cx; }				//������ġ

	float getAttPower() { return attPower; }
	void setAttPwer(float dam) { attPower = dam; }
	RECT getPlayerbody() { return playerRc;} //�ǰݿ뷺Ʈ
	RECT getPlayerRect() { return RectMake(Head.left, Head.top, 56, 67); } //�����뷺Ʈ
	
	bool getOuijaBoard() { return ouijaBoard; }

	int getKey() { return _key; }
	void setKey(int key) { _key = key; }
	void setbomb(int bomb) { _haveBomb = bomb; }

	float getSpeed() { return moveSpeed; }
	void setSpeed(float speed) { moveSpeed = speed; }
	
	//��ȣ������ ���Ŵ��� �����͸� �Ѱܹ��� �����Լ�
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

