#pragma once
#include "gameNode.h"
#include "minion.h"  //�̴Ͼ� Ŭ���� ����ϱ� ����
#include "bullet.h"	 //�����Ѿ� Ŭ���� ����ϱ� ����


//��ȣ������ Ŭ���� ���漱��
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
	bullet* _bullet; //�����Ѿ� Ŭ����
	int flyCount; //�ĸ�����
	float count;
	float angle;
	char str[20];
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void bloodrender();

	//�̴Ͼ� ���� => �ʱ�ȭ�� �ִ´�
	void setDuke();
	void setFly(float x,float y);
	void setBFly(float x,float y);
	void setRace(float x,float y);
	void setblast(float x,float y);
	void setnomblast(float x,float y);
	void setsmallblast(float x,float y);
	//�̴Ͼ� �Ѿ˹߻�
	void minionBulletFire();
	//�̴Ͼ� ����
	void removeMinion(int index);

	void setMapNum(int num) { mapNum = num; }
	void setObject(int kind, int tileNum);

	//�̴Ͼ� ���� ��������
	vector<enemy*> getMinion() { return _vMinion; }
	vector<enemy*> getObject() { return _object; }

	//�浹�Լ� (�̴Ͼ���� �Ѿ˵�, �÷��̾�)
	void collision();
	void bloodClear() { _blood.clear(); }

	POINT tilesCenter(int i); //������Ʈ �߰���

	//��ȣ������ �÷��̾� �����͸� ���� �����Լ�
	void setPlayerLink(player* player) { _player = player; }

	enemyManager() {}
	~enemyManager() {}
};

