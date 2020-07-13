#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "tileNode.h"
struct tagmap
{
	bool clear;				//��Ŭ�����
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
	player* _player; //�÷��̾� Ŭ����
	enemyManager* _enemyManager;	//���Ŵ��� Ŭ����
	tagTile _tiles[TILEX * TILEY];
	tagmap _map[31];
	tagmap _overMap;

	RECT itemstone;
	RECT item;

	int right;
	int count;
	int itemY;		//������ ��������ǥ
	bool itemy;		//������ ���Ʒ� �����̴°�

	int mapNum;						//���̵��þ� �� ��ȣ
	bool room2item;
	char _fileName[128] = { 0, };	//�� ������ �̸��� �޾ƿ� ���� 
	char _mapName[128] = { 0, };
	//���� �̸�(��, �� ������)�� �޾ƿ� ����
	char _imageName[128] = { 0, };	//�� �̹��� ������ �̸��� �޾ƿ� ����
	char _dataName[128] = { 0, };	//�� ������ ������ �̸��� �޾ƿ� ����
	
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

