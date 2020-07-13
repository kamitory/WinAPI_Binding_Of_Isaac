#pragma once
#include "gameNode.h"

//�θ�Ŭ���� => �̳��� ��ӹ޾Ƽ� ����, �Ϲݸ��͸� �����
enum ENEMY
{
	FIRE,
	POOP,
	DUKE,
	FLY,
	BFLY,
	RACE,
	BLAST
};
enum ENEMYSTATE
{
	IDLE,
	PATTERN1,
	PATTERN2,
	KILLED
};
class enemy : public gameNode
{
private:
	//image* _image;		//���ʹ� �̹���
	//RECT _rc;			//�浹�� ��Ʈ
	//
	////������ �̹����� ������ ���� ����
	//int _count;
	//int _currentFrameX;
	//int _currentFrameY;
	//
	////�������� �Ѿ˹߻� ��Ÿ�� �ֱ�
	//int _fireCount;
	//int _rndFireConut;

public:
	virtual HRESULT init() = 0;
	virtual HRESULT init(const char* imageName, POINT position) = 0;
	virtual void release() = 0;
	virtual void update(float charx, float chary) = 0;
	virtual void render() = 0;
	 
	virtual void move() = 0;		//������Ʈ
	virtual void draw() = 0;		//����
	virtual void animation() = 0;	//������Ʈ

	virtual void pattern1()=0;	//�ĸ���ȯ
	virtual void pattern2()=0;	//�ĸ�����
	virtual bool bulletCountFire() = 0;
	 
	virtual int getFrameX() = 0;
	virtual float getEnemyX() = 0;
	virtual float getEnemyY() = 0;
	virtual void setEnemyX(float _x)= 0;
	virtual void setEnemyY(float _y)= 0;
	virtual float getEAngle() = 0;
	virtual void setAngle(float angle) = 0;


	virtual int getBombCount() = 0;
	virtual void hitBomb() = 0;
	virtual ENEMY getName() = 0;
	virtual ENEMYSTATE getState() = 0;
	virtual void setState(ENEMYSTATE state) = 0;

	virtual float getHp() = 0;
	virtual float getHpMax() = 0;
	virtual void hitDamage(float dam) = 0;
	virtual bool getDuke() = 0;
	virtual void duke() = 0;		//�ĸ��� �ĸ����� �ִ���
	 //�浹�� ��Ʈ ��������
	virtual RECT getRect() = 0;

	enemy() {}
	virtual ~enemy() {}
};

class dukeOfFlies : public enemy
{
private:
	image* _image;		//���ʹ� �̹���
	image* _killed;		//���ʹ� �̹���
	RECT _rc;			//�浹�� ��Ʈ
	RECT _rc2;			//�浹�� ��Ʈ
	ENEMY _name;
	ENEMYSTATE _state;

	//������ �̹����� ������ ���� ����
	int _count;
	int _bombCount;
	int _currentFrameX;
	int _currentFrameY;
	bool fly;

	float x, y;
	float speed;
	float angle;
	float hp;
	float hpMax;

	int pattern;

	//�������� �Ѿ˹߻� ��Ÿ�� �ֱ�
	int _fireCount;
	int _rndFireConut; 

public:
	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update(float charx, float chary);
	void render();
	void move();		//������Ʈ
	void draw();		//����
	void animation();	//������Ʈ

	void pattern1();	//�ĸ���ȯ
	void pattern2();	//�ĸ�����
	bool bulletCountFire();

	int getFrameX() { return _currentFrameX; }
	float getEnemyX() { return x; }
	float getEnemyY() { return y; }
	void setEnemyX(float _x) { x = _x; }
	void setEnemyY(float _y) { y = _y; }
	float getEAngle() { return angle; }
	void setAngle(float angle) { ; }

	ENEMY getName() { return _name; }
	ENEMYSTATE getState() { return _state; }
	void setState(ENEMYSTATE state) { _state = state; }

	bool getDuke() { return fly; } //�ĸ���ȯ
	void duke() { fly = false; }
	//�浹�� ��Ʈ ��������
	int getBombCount() { return _bombCount; }
	void hitBomb() ;
	float getHp() { return hp; }
	float getHpMax() { return hpMax; }
	void hitDamage(float dam) { hp -= dam; }
	RECT getRect() { return _rc; }

	dukeOfFlies() {}
	~dukeOfFlies() {}
};


class fly : public enemy
{
	
	private:
		image* _image;		//���ʹ� �̹���
		image* _killed;		//���ʹ� �̹���
		RECT _rc;			//�浹�� ��Ʈ
		ENEMY _name;
		ENEMYSTATE _state;

		//������ �̹����� ������ ���� ����
		int _count;
		int _bombCount;
		int _currentFrameX;
		int _currentFrameY;



		bool _duke;

		float x, y;
		float speed;
		float angle;
		float hp;
		float hpMax;

		int pattern;

		//�������� �Ѿ˹߻� ��Ÿ�� �ֱ�
		int _fireCount;
		int _rndFireConut;

	public:
		HRESULT init();
		HRESULT init(const char* imageName, POINT position);
		void release();
		void update(float charx, float chary);
		void render();
		void move();		//������Ʈ
		void draw();		//����
		void animation();	//������Ʈ

		void pattern1();	//�ĸ���ȯ
		void pattern2();	//�ĸ�����

		bool bulletCountFire();

		int getFrameX() { return _currentFrameX; }
		float getEnemyX() { return x; }
		float getEnemyY() { return y; }
		void setEnemyX(float _x) { x = _x; }
		void setEnemyY(float _y) { y = _y; }
		float getEAngle() { return angle; }
		void setAngle(float _angle) { angle = _angle; }

		ENEMY getName() { return _name; }
		ENEMYSTATE getState() { return _state; }
		void setState(ENEMYSTATE state) { _state = state; }

		int getBombCount() { return _bombCount; }
		void hitBomb();
		float getHp() { return hp; }
		float getHpMax() { return hpMax; }
		void hitDamage(float dam) { hp -= dam; }
		bool getDuke() { return _duke; }
		void duke();

		//�浹�� ��Ʈ ��������
		RECT getRect() { return _rc; }

		fly() {}
		~fly(){}
		
};


class Bfly : public enemy
{

private:
	image* _image;		//���ʹ� �̹���
	image* _killed;		//���ʹ� �̹���
	RECT _rc;			//�浹�� ��Ʈ
	ENEMY _name;
	ENEMYSTATE _state;

	//������ �̹����� ������ ���� ����
	int _count;
	int _bombCount;
	int _currentFrameX;
	int _currentFrameY;

	bool _duke;

	float x, y;
	float speed;
	float angle;
	float hp;
	float hpMax;

	int pattern;

	//�������� �Ѿ˹߻� ��Ÿ�� �ֱ�
	int _fireCount;
	int _rndFireConut;

public:
	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update(float charx, float chary);
	void render();
	void move();		//������Ʈ
	void draw();		//����
	void animation();	//������Ʈ

	void pattern1();	//�ĸ���ȯ
	void pattern2();	//�ĸ�����

	bool bulletCountFire();

	int getFrameX() { return _currentFrameX; }
	float getEnemyX() { return x; }
	float getEnemyY() { return y; }
	void setEnemyX(float _x) { x = _x; }
	void setEnemyY(float _y) { y = _y; }
	float getEAngle() { return angle; }
	void setAngle(float _angle) { angle = _angle; }

	ENEMY getName() { return _name; }
	ENEMYSTATE getState() { return _state; }
	void setState(ENEMYSTATE state) { _state = state; }

	int getBombCount() { return _bombCount; }
	void hitBomb();
	float getHp() { return hp; }
	float getHpMax() { return hpMax; }
	void hitDamage(float dam) { hp -= dam; }
	bool getDuke() { return _duke; }
	void duke() { _duke = false; }

	//�浹�� ��Ʈ ��������
	RECT getRect() { return _rc; }

	Bfly() {}
	~Bfly() {}

};


class race : public enemy
{

private:
	image* _image;		//���ʹ� �̹���
	image* _killed;		//���ʹ� �̹���
	RECT _rc;			//�浹�� ��Ʈ
	ENEMY _name;
	ENEMYSTATE _state;
	//������ �̹����� ������ ���� ����
	int _count;
	int alpha;
	int _bombCount;
	int _currentFrameX;
	int _currentFrameY;

	bool _fire;

	float x, y;
	float speed;
	float angle;
	float hp;
	float hpMax;

	int pattern;

	//�������� �Ѿ˹߻� ��Ÿ�� �ֱ�
	int _fireCount;
	int _rndFireConut;

public:
	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update(float charx, float chary);
	void render();
	void move();		//������Ʈ
	void draw();		//����
	void animation();	//������Ʈ

	void pattern1();	//�ĸ���ȯ
	void pattern2();	//�ĸ�����

	bool bulletCountFire();

	int getFrameX() { return _currentFrameX; }
	float getEnemyX() { return x; }
	float getEnemyY() { return y; }
	void setEnemyX(float _x) { x = _x; }
	void setEnemyY(float _y) { y = _y; }
	float getEAngle() { return angle; }
	void setAngle(float _angle) { angle = _angle; }

	ENEMY getName() { return _name; }
	ENEMYSTATE getState() { return _state; }
	void setState(ENEMYSTATE state) { _state = state; }

	int getBombCount() { return _bombCount; }
	void hitBomb();
	float getHp() { return hp; }
	float getHpMax() { return hpMax; }
	void hitDamage(float dam) { hp -= dam; }
	bool getDuke() { return _fire; }				  //�Լ���Ȱ��
	void duke() { _fireCount = 0; }					  //�Լ���Ȱ��

	//�浹�� ��Ʈ ��������
	RECT getRect() { return _rc; }

	race() {}
	~race() {}

};

class blast : public enemy
{

private:
	image* _image;		//���ʹ� �̹���
	image* _idle;		//���ʹ� �̹���
	image* _killed;		//���ʹ� �̹���
	RECT _rc;			//�浹�� ��Ʈ
	RECT _rc2;			//�浹�� ��Ʈ
	ENEMY _name;
	ENEMYSTATE _state;
	//������ �̹����� ������ ���� ����
	int _count;
	int alpha;
	int _bombCount;
	int _currentFrameX;
	int _currentFrameY;

	bool _fire;

	float x, y;
	float speed;
	float angle;
	float hp;
	float hpMax;

	int pattern;

	//�������� �Ѿ˹߻� ��Ÿ�� �ֱ�
	int _fireCount;
	int _rndFireConut;

public:
	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update(float charx, float chary);
	void render();
	void move();		//������Ʈ
	void draw();		//����
	void animation();	//������Ʈ

	void pattern1();	//�ĸ���ȯ
	void pattern2();	//�ĸ�����

	bool bulletCountFire();

	int getFrameX() { return _currentFrameX; }
	float getEnemyX() { return x; }
	float getEnemyY() { return y; }
	void setEnemyX(float _x) { x = _x; }
	void setEnemyY(float _y) { y = _y; }
	float getEAngle() { return angle; }
	void setAngle(float _angle) { angle = _angle; }

	ENEMY getName() { return _name; }
	ENEMYSTATE getState() { return _state; }
	void setState(ENEMYSTATE state) { _state = state; }

	int getBombCount() { return _bombCount; }
	void hitBomb();
	float getHp() { return hp; }
	float getHpMax() { return hpMax; }
	void hitDamage(float dam) { hp -= dam; }
	bool getDuke() { return _fire; }				  //�Լ���Ȱ��
	void duke() { _fireCount = 0; }					  //�Լ���Ȱ��

	//�浹�� ��Ʈ ��������
	RECT getRect() { return _rc; }

	blast() {}
	~blast() {}

};









//=========================================OBJECT============================================================





class fire : public enemy
{
private:
	image* _image;		//���ʹ� �̹���
	image* _fireWood;		//���ʹ� �̹���
	RECT _rc;			//�浹�� ��Ʈ
	RECT _rc2;			//�浹�� ��Ʈ
	RECT _rc3;			//�浹�� ��Ʈ
	ENEMY _name;
	ENEMYSTATE _state;

	//������ �̹����� ������ ���� ����
	int _count;
	int _currentFrameX;
	int _currentFrameY;
	bool fly;

	float scale;
	float x, y;
	float speed;
	float angle;
	float hp;
	float hpMax;

	int inTile;

	//�������� �Ѿ˹߻� ��Ÿ�� �ֱ�
	int _fireCount;
	int _rndFireConut;

public:
	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update(float charx, float chary);
	void render();
	void move();		//������Ʈ
	void draw();		//����
	void animation();	//������Ʈ

	void pattern1();	//�ĸ���ȯ
	void pattern2();	//�ĸ�����
	bool bulletCountFire();

	int getFrameX() { return inTile; }	//��Ʈ�Լ��� ������x�ۿ���� ��� ������x ���ƴ϶� Ÿ�Ϲ�ȣ ������
	float getEnemyX() { return x; }
	float getEnemyY() { return y; }
	void setEnemyX(float _x) { x = _x; }
	void setEnemyY(float _y) { y = _y; }
	float getEAngle() { return angle; }
	void setAngle(float angle) { ; }

	ENEMY getName() { return _name; }
	ENEMYSTATE getState() { return _state; }
	void setState(ENEMYSTATE state) { _state = state; }

	int getBombCount() { return 0; }
	void hitBomb() { }
	bool getDuke() { return fly; } //�ĸ���ȯ
	void duke() { fly = false; }
	//�浹�� ��Ʈ ��������
	float getHp() { return hp; }
	float getHpMax() { return hpMax; }
	void hitDamage(float dam) { hp -= dam; }
	RECT getRect() { return _rc; }

	fire() {}
	~fire() {}
};

class poop : public enemy
{
private:
	image* _image;		//���ʹ� �̹���
	RECT _rc;			//�浹�� ��Ʈ
	ENEMY _name;
	ENEMYSTATE _state;

	//������ �̹����� ������ ���� ����
	int _count;
	int _currentFrameX;
	int _currentFrameY;
	bool fly;

	float x, y;
	float speed;
	float angle;
	float hp;
	float hpMax;

	int inTile;

	//�������� �Ѿ˹߻� ��Ÿ�� �ֱ�
	int _fireCount;
	int _rndFireConut;

public:
	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update(float charx, float chary);
	void render();
	void move();		//������Ʈ
	void draw();		//����
	void animation();	//������Ʈ

	void pattern1();	//�ĸ���ȯ
	void pattern2();	//�ĸ�����
	bool bulletCountFire();

	int getFrameX() { return inTile; }	//��Ʈ�Լ��� ������x�ۿ���� ��� ������x ���ƴ϶� Ÿ�Ϲ�ȣ ������
	float getEnemyX() { return x; }
	float getEnemyY() { return y; }
	void setEnemyX(float _x) { x = _x; }
	void setEnemyY(float _y) { y = _y; }
	float getEAngle() { return angle; }
	void setAngle(float angle) { ; }

	ENEMY getName() { return _name; }
	ENEMYSTATE getState() { return _state; }
	void setState(ENEMYSTATE state) { _state = state; }

	bool getDuke() { return fly; } //�ĸ���ȯ
	void duke() { fly = false; }
	//�浹�� ��Ʈ ��������
	int getBombCount() { return 0; }
	void hitBomb() { }
	float getHp() { return hp; }
	float getHpMax() { return hpMax; }
	void hitDamage(float dam) { hp -= dam; }
	RECT getRect() { return _rc; }

	poop() {}
	~poop() {}
};