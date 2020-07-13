#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	//Ŭ���� �ʱ�ȭ�� �̰����� �Ѵ�
	
	/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
	//������ ������ ���ΰ��� ������ �Ѵ�

	/*���߰�*/
	SCENEMANAGER->addScene("����ȭ��", new startScene);
	SCENEMANAGER->addScene("����ȭ��", new inGameScene);
	SCENEMANAGER->addScene("INI�׽�Ʈ", new iniTestScene);
	SCENEMANAGER->addScene("�ε�ȭ��", new loadingScene);
	SCENEMANAGER->addScene("�ȼ��浹", new pixelCollisionScene);
	SCENEMANAGER->addScene("����", new soundTestScene);
	SCENEMANAGER->addScene("��������", new maptoolScene);
	SCENEMANAGER->addScene("���̼Ҹ�Ʈ��", new isometricTestScene);
	SCENEMANAGER->addScene("���̽�Ÿ", new astarTestScene);
	

	/*����� ����*/
	SCENEMANAGER->loadScene("�ε�ȭ��");


	return S_OK;
}

//=============================================================
//	## ���� ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();

}

//=============================================================
//	## ������Ʈ ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	
	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();
	//����Ŵ��� ������Ʈ(�̳�����ָ� ���尡 �����۵�����)
	SOUNDMANAGER->update();
}

//=============================================================
//	## ���� ## render()
//=============================================================
void mainGame::render()
{
	//��� �� ��Ʈ��
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================	

	//���Ŵ��� ����
	SCENEMANAGER->render();
	//Ÿ�ӸŴ��� ����
	TIMEMANAGER->render(getMemDC());

	//���ڹ����
	SetBkMode(getMemDC(), TRANSPARENT);
	//�ؽ�Ʈ ���� ����
	SetTextColor(getMemDC(), RGB(0, 0, 0));

//=============================================================
	//������� ������ ȭ��DC�� �׸���
	this->getBackBuffer()->render(getHDC());
}
