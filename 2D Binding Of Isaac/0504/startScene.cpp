#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init()
{
	//��Ʈ ��ġ �ʱ�ȭ
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 200, 200, 100);
	_rc2 = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 400, 200, 100);
	
	return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rc, _ptMouse))
		{
			SCENEMANAGER->loadScene("����ȭ��");
		}
		if (PtInRect(&_rc2, _ptMouse))
		{
			SCENEMANAGER->loadScene("��������");
		}
	}

}

void startScene::render()
{
	Rectangle(getMemDC(), _rc);
	Rectangle(getMemDC(), _rc2);
	TextOut(getMemDC(), _rc.left + 50, _rc.top + 50, "START", strlen("START"));
}
