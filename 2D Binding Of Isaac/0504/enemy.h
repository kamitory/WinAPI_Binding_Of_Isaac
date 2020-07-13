#pragma once
#include "gameNode.h"

//부모클래스 => 이놈을 상속받아서 보스, 일반몬스터를 만든다
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
	//image* _image;		//에너미 이미지
	//RECT _rc;			//충돌용 렉트
	//
	////프레임 이미지를 돌리기 위한 변수
	//int _count;
	//int _currentFrameX;
	//int _currentFrameY;
	//
	////랜덤으로 총알발사 쿨타임 주기
	//int _fireCount;
	//int _rndFireConut;

public:
	virtual HRESULT init() = 0;
	virtual HRESULT init(const char* imageName, POINT position) = 0;
	virtual void release() = 0;
	virtual void update(float charx, float chary) = 0;
	virtual void render() = 0;
	 
	virtual void move() = 0;		//업데이트
	virtual void draw() = 0;		//렌더
	virtual void animation() = 0;	//업데이트

	virtual void pattern1()=0;	//파리소환
	virtual void pattern2()=0;	//파리방출
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
	virtual void duke() = 0;		//파리가 파리공자 있는지
	 //충돌용 렉트 가져오기
	virtual RECT getRect() = 0;

	enemy() {}
	virtual ~enemy() {}
};

class dukeOfFlies : public enemy
{
private:
	image* _image;		//에너미 이미지
	image* _killed;		//에너미 이미지
	RECT _rc;			//충돌용 렉트
	RECT _rc2;			//충돌용 렉트
	ENEMY _name;
	ENEMYSTATE _state;

	//프레임 이미지를 돌리기 위한 변수
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

	//랜덤으로 총알발사 쿨타임 주기
	int _fireCount;
	int _rndFireConut; 

public:
	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update(float charx, float chary);
	void render();
	void move();		//업데이트
	void draw();		//렌더
	void animation();	//업데이트

	void pattern1();	//파리소환
	void pattern2();	//파리방출
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

	bool getDuke() { return fly; } //파리소환
	void duke() { fly = false; }
	//충돌용 렉트 가져오기
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
		image* _image;		//에너미 이미지
		image* _killed;		//에너미 이미지
		RECT _rc;			//충돌용 렉트
		ENEMY _name;
		ENEMYSTATE _state;

		//프레임 이미지를 돌리기 위한 변수
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

		//랜덤으로 총알발사 쿨타임 주기
		int _fireCount;
		int _rndFireConut;

	public:
		HRESULT init();
		HRESULT init(const char* imageName, POINT position);
		void release();
		void update(float charx, float chary);
		void render();
		void move();		//업데이트
		void draw();		//렌더
		void animation();	//업데이트

		void pattern1();	//파리소환
		void pattern2();	//파리방출

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

		//충돌용 렉트 가져오기
		RECT getRect() { return _rc; }

		fly() {}
		~fly(){}
		
};


class Bfly : public enemy
{

private:
	image* _image;		//에너미 이미지
	image* _killed;		//에너미 이미지
	RECT _rc;			//충돌용 렉트
	ENEMY _name;
	ENEMYSTATE _state;

	//프레임 이미지를 돌리기 위한 변수
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

	//랜덤으로 총알발사 쿨타임 주기
	int _fireCount;
	int _rndFireConut;

public:
	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update(float charx, float chary);
	void render();
	void move();		//업데이트
	void draw();		//렌더
	void animation();	//업데이트

	void pattern1();	//파리소환
	void pattern2();	//파리방출

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

	//충돌용 렉트 가져오기
	RECT getRect() { return _rc; }

	Bfly() {}
	~Bfly() {}

};


class race : public enemy
{

private:
	image* _image;		//에너미 이미지
	image* _killed;		//에너미 이미지
	RECT _rc;			//충돌용 렉트
	ENEMY _name;
	ENEMYSTATE _state;
	//프레임 이미지를 돌리기 위한 변수
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

	//랜덤으로 총알발사 쿨타임 주기
	int _fireCount;
	int _rndFireConut;

public:
	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update(float charx, float chary);
	void render();
	void move();		//업데이트
	void draw();		//렌더
	void animation();	//업데이트

	void pattern1();	//파리소환
	void pattern2();	//파리방출

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
	bool getDuke() { return _fire; }				  //함수재활용
	void duke() { _fireCount = 0; }					  //함수재활용

	//충돌용 렉트 가져오기
	RECT getRect() { return _rc; }

	race() {}
	~race() {}

};

class blast : public enemy
{

private:
	image* _image;		//에너미 이미지
	image* _idle;		//에너미 이미지
	image* _killed;		//에너미 이미지
	RECT _rc;			//충돌용 렉트
	RECT _rc2;			//충돌용 렉트
	ENEMY _name;
	ENEMYSTATE _state;
	//프레임 이미지를 돌리기 위한 변수
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

	//랜덤으로 총알발사 쿨타임 주기
	int _fireCount;
	int _rndFireConut;

public:
	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update(float charx, float chary);
	void render();
	void move();		//업데이트
	void draw();		//렌더
	void animation();	//업데이트

	void pattern1();	//파리소환
	void pattern2();	//파리방출

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
	bool getDuke() { return _fire; }				  //함수재활용
	void duke() { _fireCount = 0; }					  //함수재활용

	//충돌용 렉트 가져오기
	RECT getRect() { return _rc; }

	blast() {}
	~blast() {}

};









//=========================================OBJECT============================================================





class fire : public enemy
{
private:
	image* _image;		//에너미 이미지
	image* _fireWood;		//에너미 이미지
	RECT _rc;			//충돌용 렉트
	RECT _rc2;			//충돌용 렉트
	RECT _rc3;			//충돌용 렉트
	ENEMY _name;
	ENEMYSTATE _state;

	//프레임 이미지를 돌리기 위한 변수
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

	//랜덤으로 총알발사 쿨타임 주기
	int _fireCount;
	int _rndFireConut;

public:
	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update(float charx, float chary);
	void render();
	void move();		//업데이트
	void draw();		//렌더
	void animation();	//업데이트

	void pattern1();	//파리소환
	void pattern2();	//파리방출
	bool bulletCountFire();

	int getFrameX() { return inTile; }	//인트함수가 프레임x밖에없어서 사용 프레임x 가아니라 타일번호 보내줌
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
	bool getDuke() { return fly; } //파리소환
	void duke() { fly = false; }
	//충돌용 렉트 가져오기
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
	image* _image;		//에너미 이미지
	RECT _rc;			//충돌용 렉트
	ENEMY _name;
	ENEMYSTATE _state;

	//프레임 이미지를 돌리기 위한 변수
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

	//랜덤으로 총알발사 쿨타임 주기
	int _fireCount;
	int _rndFireConut;

public:
	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update(float charx, float chary);
	void render();
	void move();		//업데이트
	void draw();		//렌더
	void animation();	//업데이트

	void pattern1();	//파리소환
	void pattern2();	//파리방출
	bool bulletCountFire();

	int getFrameX() { return inTile; }	//인트함수가 프레임x밖에없어서 사용 프레임x 가아니라 타일번호 보내줌
	float getEnemyX() { return x; }
	float getEnemyY() { return y; }
	void setEnemyX(float _x) { x = _x; }
	void setEnemyY(float _y) { y = _y; }
	float getEAngle() { return angle; }
	void setAngle(float angle) { ; }

	ENEMY getName() { return _name; }
	ENEMYSTATE getState() { return _state; }
	void setState(ENEMYSTATE state) { _state = state; }

	bool getDuke() { return fly; } //파리소환
	void duke() { fly = false; }
	//충돌용 렉트 가져오기
	int getBombCount() { return 0; }
	void hitBomb() { }
	float getHp() { return hp; }
	float getHpMax() { return hpMax; }
	void hitDamage(float dam) { hp -= dam; }
	RECT getRect() { return _rc; }

	poop() {}
	~poop() {}
};