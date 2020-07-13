#pragma once
#include "gameNode.h"
#include "minion.h"  //미니언 클래스 사용하기 위해
#include "bullet.h"	 //공용총알 클래스 사용하기 위해


//상호참조용 클래스 전방선언
class player;

class enemyManager : public gameNode
{
private:
	player* _player;

private:
	vector<enemy*> _vMinion;
	vector<enemy*>::iterator _viMinion;
	vector<POINT> _blood;
	vector<int> _bloodtype;
	vector<enemy*> _object;

	int mapNum;

	//vector<enemy*> _vBoss;
	bullet* _bullet; //공용총알 클래스
	int flyCount; //파리개수
	float count;
	float angle;
	char str[20];
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void bloodrender();

	//미니언 세팅 => 초기화에 넣는다
	void setDuke();
	void setFly(float x,float y);
	void setBFly(float x,float y);
	void setRace(float x,float y);
	void setblast(float x,float y);
	void setnomblast(float x,float y);
	void setsmallblast(float x,float y);
	//미니언 총알발사
	void minionBulletFire();
	//미니언 삭제
	void removeMinion(int index);

	void setMapNum(int num) { mapNum = num; }
	void setObject(int kind, int tileNum);

	//미니언 벡터 가져오기
	vector<enemy*> getMinion() { return _vMinion; }
	vector<enemy*> getObject() { return _object; }

	//충돌함수 (미니언들의 총알들, 플레이어)
	void collision();
	void bloodClear() { _blood.clear(); }

	POINT tilesCenter(int i); //오브젝트 추가시

	//상호참조시 플레이어 포인터를 받을 셋터함수
	void setPlayerLink(player* player) { _player = player; }

	enemyManager() {}
	~enemyManager() {}
};

