#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	//로딩 이미지 및 사운드 초기화
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release()
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 화면 변경
	if (_loading->loadingDone())
	{
		//SCENEMANAGER->loadScene("게임화면");
		//SCENEMANAGER->loadScene("맵툴기초");
		SCENEMANAGER->loadScene("시작화면");
	}
}

void loadingScene::render()
{
	//로딩클래스 렌더
	_loading->render();
}


//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	/*
	//백그라운드 이미지 초기화
	IMAGEMANAGER->addImage("백그라운드", "Images/background.bmp", WINSIZEX, WINSIZEY);
	//UFO 프레임 이미지 초기화
	IMAGEMANAGER->addFrameImage("ufo", "Images/ufo.bmp", 530, 32, 10, 1);
	//총알 이미지
	IMAGEMANAGER->addImage("bullet", "Images/bullet.bmp", 21, 21);
	*/
	//_loading->loadImage("백그라운드", "Images/background.bmp", WINSIZEX, WINSIZEY);
	//_loading->loadFrameImage("ufo", "Images/ufo.bmp", 530, 32, 10, 1);
	_loading->loadImage("bullet", "Images/bullet.bmp", 21, 21);

	//=====================================맵툴용=============================================================


		_loading->loadFrameImage("map1", "Images/map/창고방.bmp", 960, 540, 20, 12);
		_loading->loadImage("smap1", "Images/map/창고방.bmp", 320, 180);
		_loading->loadFrameImage("map2", "Images/map/도서관방.bmp", 960, 540, 20, 12);
		_loading->loadImage("smap2", "Images/map/도서관방.bmp", 320, 180);
		_loading->loadFrameImage("map3", "Images/map/희생방.bmp", 960, 540, 20, 12);
		_loading->loadImage("smap3", "Images/map/희생방.bmp", 320, 180);
		_loading->loadFrameImage("map4", "Images/map/자궁방.bmp", 960, 540, 20, 12);
		_loading->loadImage("smap4", "Images/map/자궁방.bmp", 320, 180);
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


		_loading->loadImage("minimap", "Images/UI/미니맵.bmp", 106, 94);
		_loading->loadImage("minimapframe", "Images/UI/미니맵프레임.bmp", 106, 94);


		_loading->loadImage("tutorial", "Images/튜토리얼.bmp", 593, 129);



		_loading->loadImage("bloodstain1", "Images/enemy/bloodstain1.bmp",86,59);
		_loading->loadImage("bloodstain2", "Images/enemy/bloodstain2.bmp",72,82);
		_loading->loadImage("bloodstain3", "Images/enemy/bloodstain3.bmp",84,94);
		_loading->loadImage("bloodstain4", "Images/enemy/bloodstain4.bmp",84,46);



	//====================================플레이어==============================================================

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


		_loading->loadFrameImage("파란파리", "Images/isaac/bluefly.bmp", 160 * 1.11f, 31 * 1.1f, 4, 1);


		_loading->loadImage("반칸하트", "Images/UI/반칸하트.bmp", 24, 24);
		_loading->loadImage("하트", "Images/UI/하트.bmp", 24, 24);
		_loading->loadImage("반칸소울하트", "Images/UI/반칸소울하트.bmp", 24, 24);
		_loading->loadImage("소울하트", "Images/UI/소울하트.bmp", 24, 24);
		_loading->loadImage("반칸블랙하트", "Images/UI/반칸블랙하트.bmp", 24, 24);
		_loading->loadImage("블랙하트", "Images/UI/블랙하트.bmp", 24, 24);
		_loading->loadImage("이터널하트", "Images/UI/이터널하트.bmp", 24, 24);
		_loading->loadImage("빈하트", "Images/UI/빈하트.bmp", 24, 24);
		_loading->loadImage("블랙하트소멸", "Images/blackeffect.bmp", 560, 450);

		_loading->loadImage("충전", "Images/충전게이지.bmp", 12, 54);
		_loading->loadImage("충전바", "Images/충전바.bmp", 12, 54);
		
		
		_loading->loadImage("페니", "Images/UI/페니.bmp", 14, 18);
		_loading->loadImage("열쇠아이콘", "Images/UI/열쇠.bmp", 14, 18);
		_loading->loadImage("폭탄아이콘", "Images/UI/폭탄.bmp", 14, 18);

		_loading->loadFrameImage("숫자", "Images/UI/숫자.bmp", 140, 18, 10, 1);


		_loading->loadImage("눈물기폭제", "Images/눈물기폭제.bmp", 50, 50);
		_loading->loadImage("눈물폭탄", "Images/sadbomb.bmp", 50, 50);
		_loading->loadImage("검은연꽃", "Images/검은연꽃.bmp", 50, 50);
		_loading->loadImage("분신사바", "Images/분신사바.bmp", 50, 50);
		_loading->loadImage("쿼터", "Images/쿼터.bmp", 50, 50);
		_loading->loadImage("아이템받침대", "Images/아이템받침대.bmp", 54, 46);

//====================================적==============================================================

		_loading->loadFrameImage("파리사망", "Images/enemy/파리죽음.bmp",400,97,4,1);
		_loading->loadFrameImage("적사망", "Images/enemy/적사망.bmp",400,97,4,1);


		_loading->loadFrameImage("파리공자", "Images/enemy/dukeofflies/dukeofflies.bmp",276*1.8f,63*1.8f,4,1);
		_loading->loadFrameImage("파리", "Images/enemy/dukeofflies/fly.bmp", 160 * 1.1f, 31 * 1.1f, 4, 1);
		_loading->loadFrameImage("왕파리", "Images/enemy/dukeofflies/fly.bmp", 160 * 1.3f, 31 * 1.3f, 4, 1);
		
		_loading->loadFrameImage("검은파리", "Images/enemy/dukeofflies/blackfly.bmp", 160 * 1.1f, 31 * 1.1f, 4, 1);

		_loading->loadFrameImage("유령", "Images/enemy/race.bmp",212,222,4,4);

		_loading->loadFrameImage("bigblast", "Images/enemy/blast/blast1Idle.bmp",100,200,1,2);
		_loading->loadFrameImage("bigblastjump", "Images/enemy/blast/blast1jump.bmp",700,200,7,2);

		_loading->loadFrameImage("nomblast", "Images/enemy/blast/blast2Idle.bmp",70,140,1,2);
		_loading->loadFrameImage("nomblastjump", "Images/enemy/blast/blast2jump.bmp",490,140,7,2);

		_loading->loadFrameImage("smallblast", "Images/enemy/blast/blast3.bmp",210,70,6,2);







}

//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound()
{
}
