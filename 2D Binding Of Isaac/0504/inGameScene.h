#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "tileNode.h"
struct tagmap
{
	bool clear;				//맵클리어여부
	bool haveMap;
	bool open;
	int mapNum;
	RECT rc;
	vector<POINT> _afterbomb;
	//vector<POINT> 
};
class inGameScene : public gameNode
{
private:
	player* _player; //플레이어 클래스
	enemyManager* _enemyManager;	//적매니져 클래스
	tagTile _tiles[TILEX * TILEY];
	tagmap _map[31];
	tagmap _overMap;

	RECT itemstone;
	RECT item;

	int right;
	int count;
	int itemY;		//아이템 움직일좌표
	bool itemy;		//아이템 위아래 움직이는거

	int mapNum;						//방이동시쓸 맵 번호
	bool room2item;
	char _fileName[128] = { 0, };	//맵 파일의 이름을 받아올 변수 
	char _mapName[128] = { 0, };
	//파일 이름(맵, 맵 데이터)을 받아올 변수
	char _imageName[128] = { 0, };	//맵 이미지 파일의 이름을 받아올 변수
	char _dataName[128] = { 0, };	//맵 데이터 파일의 이름을 받아올 변수
	
	RECT crush;
	RECT miniMap;

	RECT _rcScreen;

	bool clearMap[100] = { false, };
	bool usedKey[100] = { false, };

public:
	HRESULT init();
	void release();
	void update();
	void render();
	void mapSetting(int mapLocation);
	void openDoor(int tilesNum);
	void save(char* str);
	inGameScene() {}
	~inGameScene() {}
};

