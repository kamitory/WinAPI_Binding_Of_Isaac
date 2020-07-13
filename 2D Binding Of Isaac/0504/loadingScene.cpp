#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�ε� �̹��� �� ���� �ʱ�ȭ
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release()
{
	//�ε�Ŭ���� ����
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��Ϸ��� ȭ�� ����
	if (_loading->loadingDone())
	{
		//SCENEMANAGER->loadScene("����ȭ��");
		//SCENEMANAGER->loadScene("��������");
		SCENEMANAGER->loadScene("����ȭ��");
	}
}

void loadingScene::render()
{
	//�ε�Ŭ���� ����
	_loading->render();
}


//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	/*
	//��׶��� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addImage("��׶���", "Images/background.bmp", WINSIZEX, WINSIZEY);
	//UFO ������ �̹��� �ʱ�ȭ
	IMAGEMANAGER->addFrameImage("ufo", "Images/ufo.bmp", 530, 32, 10, 1);
	//�Ѿ� �̹���
	IMAGEMANAGER->addImage("bullet", "Images/bullet.bmp", 21, 21);
	*/
	//_loading->loadImage("��׶���", "Images/background.bmp", WINSIZEX, WINSIZEY);
	//_loading->loadFrameImage("ufo", "Images/ufo.bmp", 530, 32, 10, 1);
	_loading->loadImage("bullet", "Images/bullet.bmp", 21, 21);

	//=====================================������=============================================================


		_loading->loadFrameImage("map1", "Images/map/â���.bmp", 960, 540, 20, 12);
		_loading->loadImage("smap1", "Images/map/â���.bmp", 320, 180);
		_loading->loadFrameImage("map2", "Images/map/��������.bmp", 960, 540, 20, 12);
		_loading->loadImage("smap2", "Images/map/��������.bmp", 320, 180);
		_loading->loadFrameImage("map3", "Images/map/�����.bmp", 960, 540, 20, 12);
		_loading->loadImage("smap3", "Images/map/�����.bmp", 320, 180);
		_loading->loadFrameImage("map4", "Images/map/�ڱù�.bmp", 960, 540, 20, 12);
		_loading->loadImage("smap4", "Images/map/�ڱù�.bmp", 320, 180);
		_loading->loadFrameImage("map5", "Images/map/object2.bmp", 960, 540, 20, 12);
		_loading->loadImage("smap5", "Images/map/object.bmp", 320, 180);
		_loading->loadFrameImage("map6", "Images/map/door2.bmp", 960, 540, 20, 12);
		_loading->loadImage("smap6", "Images/map/door.bmp", 320, 180);
		_loading->loadFrameImage("map7", "Images/map/closedoor2.bmp", 960, 540, 20, 12);
		_loading->loadImage("smap7", "Images/map/closedoor.bmp", 320, 180);

		_loading->loadImage("saveLoad", "Images/UI/saveLoad.bmp", 110, 45);
		_loading->loadImage("terrain", "Images/UI/terrain.bmp", 110, 45);
		_loading->loadImage("object", "Images/UI/object.bmp", 110, 45);
		_loading->loadImage("slide", "Images/UI/slide.bmp", 110, 45);
		_loading->loadImage("home", "Images/UI/home.bmp", 110, 45);
		_loading->loadImage("save", "Images/UI/save.bmp", 80, 35);
		_loading->loadImage("load", "Images/UI/load.bmp", 80, 35);


		_loading->loadImage("saveLoad_off", "Images/UI/saveLoad_off.bmp", 110, 45);
		_loading->loadImage("terrain_off", "Images/UI/terrain_off.bmp", 110, 45);
		_loading->loadImage("object_off", "Images/UI/object_off.bmp", 110, 45);
		_loading->loadImage("slide_off", "Images/UI/slide_off.bmp", 110, 45);
		_loading->loadImage("home_off", "Images/UI/home_off.bmp", 110, 45);
		_loading->loadImage("save_off", "Images/UI/save_off.bmp", 80, 35);
		_loading->loadImage("load_off", "Images/UI/load_off.bmp", 80, 35);
		
		_loading->loadImage("arrL", "Images/UI/Arrow0.bmp", 55, 45);
		_loading->loadImage("arrR", "Images/UI/Arrow1.bmp", 55, 45);

		_loading->loadImage("textbox", "Images/UI/textbox.bmp", 600, 800);
		_loading->loadImage("activetextbox", "Images/UI/activetextbox.bmp", 600, 800);

		_loading->loadImage("firewood", "Images/map/firewood.bmp", 48, 50);
		_loading->loadFrameImage("bonfire", "Images/map/bonfire.bmp", 288, 50, 6, 1);
		_loading->loadFrameImage("poop", "Images/map/poop.bmp", 192, 45, 4, 1);


//=============================================UI==============================================	

		_loading->loadImage("closeroom", "Images/UI/closeroom.bmp", 18, 16);
		_loading->loadImage("closebigroom", "Images/UI/closebigroom.bmp", 34, 30);
		_loading->loadImage("closelongroom", "Images/UI/closelongroom.bmp", 18, 16);

		_loading->loadImage("openroom", "Images/UI/openroom.bmp", 18, 16);
		_loading->loadImage("openbigroom", "Images/UI/openbigroom.bmp", 34, 30);
		_loading->loadImage("openlongroom", "Images/UI/openlongroom.bmp", 18, 16);

		_loading->loadImage("activeroom", "Images/UI/activeroom.bmp", 18, 16);
		_loading->loadImage("activebigroom", "Images/UI/activebigroom.bmp", 34, 30);
		_loading->loadImage("activelongroom", "Images/UI/activelongroom.bmp", 18, 16);


		_loading->loadImage("minimap", "Images/UI/�̴ϸ�.bmp", 106, 94);
		_loading->loadImage("minimapframe", "Images/UI/�̴ϸ�������.bmp", 106, 94);


		_loading->loadImage("tutorial", "Images/Ʃ�丮��.bmp", 593, 129);



		_loading->loadImage("bloodstain1", "Images/enemy/bloodstain1.bmp",86,59);
		_loading->loadImage("bloodstain2", "Images/enemy/bloodstain2.bmp",72,82);
		_loading->loadImage("bloodstain3", "Images/enemy/bloodstain3.bmp",84,94);
		_loading->loadImage("bloodstain4", "Images/enemy/bloodstain4.bmp",84,46);



	//====================================�÷��̾�==============================================================

		_loading->loadFrameImage("widthrun", "Images/isaac/widthrun.bmp", 360, 56, 10, 2);
		_loading->loadFrameImage("heightrun", "Images/isaac/heightrun.bmp", 360, 28, 10, 1);
		_loading->loadFrameImage("face", "Images/isaac/face.bmp", 448, 50, 8, 1);
		_loading->loadFrameImage("statup", "Images/isaac/statup.bmp", 68*2, 67, 2, 1);
		_loading->loadFrameImage("hit", "Images/isaac/hit.bmp", 72*3, 67, 3, 1);
		_loading->loadImage("statdown", "Images/isaac/statdown.bmp", 56, 67);
		_loading->loadImage("pickup", "Images/isaac/pickup.bmp", 56, 67);

		
		_loading->loadFrameImage("bomb", "Images/isaac/bomb.bmp", 752, 55,16,1);
		_loading->loadFrameImage("sadbomb", "Images/isaac/sadbomb.bmp", 752, 55,16,1);
		_loading->loadFrameImage("explosion", "Images/isaac/explosion.bmp", 480, 160,3,1);
		_loading->loadImage("afterbomb", "Images/isaac/afterbomb.bmp", 160, 75);


		_loading->loadFrameImage("�Ķ��ĸ�", "Images/isaac/bluefly.bmp", 160 * 1.11f, 31 * 1.1f, 4, 1);


		_loading->loadImage("��ĭ��Ʈ", "Images/UI/��ĭ��Ʈ.bmp", 24, 24);
		_loading->loadImage("��Ʈ", "Images/UI/��Ʈ.bmp", 24, 24);
		_loading->loadImage("��ĭ�ҿ���Ʈ", "Images/UI/��ĭ�ҿ���Ʈ.bmp", 24, 24);
		_loading->loadImage("�ҿ���Ʈ", "Images/UI/�ҿ���Ʈ.bmp", 24, 24);
		_loading->loadImage("��ĭ����Ʈ", "Images/UI/��ĭ����Ʈ.bmp", 24, 24);
		_loading->loadImage("����Ʈ", "Images/UI/����Ʈ.bmp", 24, 24);
		_loading->loadImage("���ͳ���Ʈ", "Images/UI/���ͳ���Ʈ.bmp", 24, 24);
		_loading->loadImage("����Ʈ", "Images/UI/����Ʈ.bmp", 24, 24);
		_loading->loadImage("����Ʈ�Ҹ�", "Images/blackeffect.bmp", 560, 450);

		_loading->loadImage("����", "Images/����������.bmp", 12, 54);
		_loading->loadImage("������", "Images/������.bmp", 12, 54);
		
		
		_loading->loadImage("���", "Images/UI/���.bmp", 14, 18);
		_loading->loadImage("���������", "Images/UI/����.bmp", 14, 18);
		_loading->loadImage("��ź������", "Images/UI/��ź.bmp", 14, 18);

		_loading->loadFrameImage("����", "Images/UI/����.bmp", 140, 18, 10, 1);


		_loading->loadImage("����������", "Images/����������.bmp", 50, 50);
		_loading->loadImage("������ź", "Images/sadbomb.bmp", 50, 50);
		_loading->loadImage("��������", "Images/��������.bmp", 50, 50);
		_loading->loadImage("�нŻ��", "Images/�нŻ��.bmp", 50, 50);
		_loading->loadImage("����", "Images/����.bmp", 50, 50);
		_loading->loadImage("�����۹�ħ��", "Images/�����۹�ħ��.bmp", 54, 46);

//====================================��==============================================================

		_loading->loadFrameImage("�ĸ����", "Images/enemy/�ĸ�����.bmp",400,97,4,1);
		_loading->loadFrameImage("�����", "Images/enemy/�����.bmp",400,97,4,1);


		_loading->loadFrameImage("�ĸ�����", "Images/enemy/dukeofflies/dukeofflies.bmp",276*1.8f,63*1.8f,4,1);
		_loading->loadFrameImage("�ĸ�", "Images/enemy/dukeofflies/fly.bmp", 160 * 1.1f, 31 * 1.1f, 4, 1);
		_loading->loadFrameImage("���ĸ�", "Images/enemy/dukeofflies/fly.bmp", 160 * 1.3f, 31 * 1.3f, 4, 1);
		
		_loading->loadFrameImage("�����ĸ�", "Images/enemy/dukeofflies/blackfly.bmp", 160 * 1.1f, 31 * 1.1f, 4, 1);

		_loading->loadFrameImage("����", "Images/enemy/race.bmp",212,222,4,4);

		_loading->loadFrameImage("bigblast", "Images/enemy/blast/blast1Idle.bmp",100,200,1,2);
		_loading->loadFrameImage("bigblastjump", "Images/enemy/blast/blast1jump.bmp",700,200,7,2);

		_loading->loadFrameImage("nomblast", "Images/enemy/blast/blast2Idle.bmp",70,140,1,2);
		_loading->loadFrameImage("nomblastjump", "Images/enemy/blast/blast2jump.bmp",490,140,7,2);

		_loading->loadFrameImage("smallblast", "Images/enemy/blast/blast3.bmp",210,70,6,2);







}

//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound()
{
}
