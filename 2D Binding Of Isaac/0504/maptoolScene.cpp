#include "stdafx.h"
#include "maptoolScene.h"

HRESULT maptoolScene::init()
{
	//타일맵 이미지 초기화
	//IMAGEMANAGER->addFrameImage("tilemap", "tilemap.bmp", 640, 256, SAMPLETILEX, SAMPLETILEY);
	_rcScreen = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 960, 540);
	//_rcPalette = RectMakeCenter((_rcScreen.left + _rcScreen.right) / 2, _rcScreen.bottom - 192, 936, 288);
	_rcPalette = RectMakeCenter(_rcScreen.right - 170 ,WINSIZEY/2+120, 330, 270);
	
	//_editMode = false;
	//_editMoveDirect = false;
	_setSaveLoad = false;
	_slideTool = true;
	_setSaveSlot = 3;
	//맵툴세팅
	this->maptoolSetup();

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(TILESIZEx * j, TILESIZEy * i, TILESIZEx, TILESIZEy);
			if (i > 1 && i < TILEY - 2 && j > 2 && j < TILEX - 3) { _tiles[i * TILEX + j]._type = TILE; }
			else { _tiles[i * TILEX + j]._type = OBJECT; }
			
		}
	}
	
	for (int i = 0; i < 7; i++)
	{
		if (i < 2) { _thorn[i] = RectMake(_rcPalette.left + i % 5 * 128 + 64, _rcPalette.top + 120, 48, 45); }
		if (i < 5) { _rcobject[i] = RectMake(_rcPalette.left + i * 64, _rcPalette.top + 0, 48, 45); }
		else { _rcobject[i] = RectMake(_rcPalette.left + i % 5 * 128 + 64, _rcPalette.top + 60, 48, 45); }
	}
	_rcComDoor[0] = RectMake(_rcPalette.left, _rcPalette.top, 48, 30);
	_rcComDoor[1] = RectMake(_rcPalette.left+48, _rcPalette.top, 32, 45);
	_rcComDoor[3] = RectMake(_rcPalette.left, _rcPalette.top+30, 32, 45);
	_rcComDoor[2] = RectMake(_rcPalette.left+32, _rcPalette.top+45, 48, 30);
	
	_rcLibDoor[0] = RectMake(_rcComDoor[1].right, _rcPalette.top, 48, 30);
	_rcLibDoor[1] = RectMake(_rcComDoor[1].right + 48, _rcPalette.top, 32, 45);
	_rcLibDoor[3] = RectMake(_rcComDoor[1].right, _rcPalette.top + 30, 32, 45);
	_rcLibDoor[2] = RectMake(_rcComDoor[1].right + 32, _rcPalette.top + 45, 48, 30);
	
	_rcBloodDoor[0] = RectMake(_rcLibDoor[1].right, _rcPalette.top, 48, 30);
	_rcBloodDoor[1] = RectMake(_rcLibDoor[1].right + 48, _rcPalette.top, 32, 45);
	_rcBloodDoor[3] = RectMake(_rcLibDoor[1].right, _rcPalette.top + 30, 32, 45);
	_rcBloodDoor[2] = RectMake(_rcLibDoor[1].right + 32, _rcPalette.top + 45, 48, 30);

	_rcSacriDoor[0] = RectMake(_rcBloodDoor[1].right, _rcPalette.top, 48, 30);
	_rcSacriDoor[1] = RectMake(_rcBloodDoor[1].right + 48, _rcPalette.top, 32, 45);
	_rcSacriDoor[3] = RectMake(_rcBloodDoor[1].right, _rcPalette.top + 30, 32, 45);
	_rcSacriDoor[2] = RectMake(_rcBloodDoor[1].right + 32, _rcPalette.top + 45, 48, 30);

	_rcTreasureDoor[0] = RectMake(_rcPalette.left, _rcComDoor[2].bottom+15, 48, 30);
	_rcTreasureDoor[1] = RectMake(_rcPalette.left + 48, _rcComDoor[2].bottom+15, 32, 45);
	_rcTreasureDoor[3] = RectMake(_rcPalette.left, _rcComDoor[2].bottom+15 + 30, 32, 45);
	_rcTreasureDoor[2] = RectMake(_rcPalette.left + 32, _rcComDoor[2].bottom+15 + 45, 48, 30);

	_rcDevilDoor[0] = RectMake(_rcTreasureDoor[1].right+16, _rcComDoor[2].bottom + 15, 48, 30);
	_rcDevilDoor[1] = RectMake(_rcTreasureDoor[1].right+16 + 48, _rcComDoor[2].bottom + 15, 32, 45);
	_rcDevilDoor[3] = RectMake(_rcTreasureDoor[1].right+16, _rcComDoor[2].bottom + 15 + 30, 32, 45);
	_rcDevilDoor[2] = RectMake(_rcTreasureDoor[1].right+16 + 32, _rcComDoor[2].bottom + 15 + 45, 48, 30);
	
	_rcBossDoor[0] = RectMake(_rcDevilDoor[1].right + 32, _rcComDoor[2].bottom + 15, 48, 30);
	_rcBossDoor[1] = RectMake(_rcDevilDoor[1].right + 32 + 48, _rcComDoor[2].bottom + 15, 32, 45);
	_rcBossDoor[3] = RectMake(_rcDevilDoor[1].right + 32, _rcComDoor[2].bottom + 15 + 30, 32, 45);
	_rcBossDoor[2] = RectMake(_rcDevilDoor[1].right + 32 + 32, _rcComDoor[2].bottom + 15 + 45, 48, 30);
		

	// 렉트 이중배열로만들어 커렌트타일 / 샘플타일로 사용해서 그려주고 / 포인트를 이용해서 실직적으로 도어타일로바꿔줄개채 선택시키기
	 
	_palettePage = 1;
	sprintf_s(_dataName, "MapData\\map%d.txt", _palettePage);
	//현재타일(0,0)좌표로 초기화
	_currentTile.pageNumber = _palettePage;
	_currentTile.x[0] = 0;
	_currentTile.y[0] = 0;

	//현재 드래그 좌표 초기화
	_currentTile.sampleStartX = _rcPalette.left;
	_currentTile.sampleStartY = _rcPalette.top;
	_currentTile.sampleEndX = 0;
	_currentTile.sampleEndY = 0;
	_currentTile.sampleSizeX = 1;
	_currentTile.sampleSizeY = 1;
	_currentTile.sampleStartPointX = 0;
	_currentTile.samplSetartPointY = 0;
	_dragRect.rc = RectMake(0, 0, 0, 0);
	//_layer[0] = true;
	//_layer[1] = false;
	//_layer[2] = false; 


	return S_OK;
}

void maptoolScene::release()
{
}

void maptoolScene::update()
{
	//if (_editMode)
	//{
		//if (INPUT->GetKeyDown(VK_D))
		//{
		//	_editMode = false;
		//	sprintf(_dataName, "MapData/map%d.txt", _currentTile.pageNumber);
		//	saveMapData(_dataName);
		//}
		//if (INPUT->GetKeyDown(VK_1))
		//{
		//	_editCanMove = true;
		//	_editMoveDirect = false;
		//}
		//if (INPUT->GetKeyDown(VK_2))
		//{
		//	_editCanMove = false;
		//	_editMoveDirect = true;
		//}

		//if (_editCanMove)
		//{
		//	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		//	{
		//		if (INPUT->GetKeyDown(VK_LBUTTON))
		//		{
		//			if (PtInRect(&_sampleTile[i].rc, _ptMouse))
		//			{
		//				_sampleTile[i].canMove = !_sampleTile[i].canMove;
		//				break;
		//			}
		//		}
		//	}
		//}
		//if (_editMoveDirect)
		//{
		//	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		//	{
		//		if (PtInRect(&_sampleTile[i].rc, _ptMouse))
		//		{
		//			if (INPUT->GetKeyUp(VK_UP)) { _sampleTile[i].direct[0] = !_sampleTile[i].direct[0]; }
		//			if (INPUT->GetKeyUp(VK_DOWN)) { _sampleTile[i].direct[1] = !_sampleTile[i].direct[1]; }
		//			if (INPUT->GetKeyUp(VK_LEFT)) { _sampleTile[i].direct[2] = !_sampleTile[i].direct[2]; }
		//			if (INPUT->GetKeyUp(VK_RIGHT)) { _sampleTile[i].direct[3] = !_sampleTile[i].direct[3]; }
		//			break;
		//		}
		//	}
		//}
		//}

	if (_setSaveLoad == true) // 세이브 확인창이 켜졌을때
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{

			if (PtInRect(&_rcSaveSlot[0], _ptMouse))
			{
				_setSaveSlot = 0;
			}	//슬롯1번선택
			if (PtInRect(&_rcSaveSlot[1], _ptMouse))
			{
				_setSaveSlot = 1;
			}	//슬롯2번선택
			if (PtInRect(&_rcSaveSlot[2], _ptMouse))
			{
				_setSaveSlot = 2;
			}	//슬롯3번선택

			if (_setSaveSlot == 0)
			{
				sprintf_s(_mapName, "save1.mapsave");
			}	//슬롯1번파일으로 이름변경
			else if (_setSaveSlot == 1) { sprintf_s(_mapName, "save2.mapsave"); }	//슬롯2번파일으로 이름변경
			else if (_setSaveSlot == 2) { sprintf_s(_mapName, "save3.mapsave"); }	//슬롯3번파일으로 이름변경

		}
		if (INPUT->GetKeyUp(VK_LBUTTON))
		{
			if (!PtInRect(&_rcSaveWindow, _ptMouse)) // 세이브 확인창 밖을 클릭하면 세이브창 닫기
			{
				_setSaveLoad = false;
				_setSaveSlot = 3;
				return;
			}
			else if (PtInRect(&_rcSave, _ptMouse))
			{
				this->save(_mapName);
				_setSaveLoad = false;
				_setSaveSlot = 3;
				return;
			}
			//세이브완료
			else if (PtInRect(&_rcLoad, _ptMouse))
			{
				this->load(_mapName);
				_setSaveLoad = false;
				_setSaveSlot = 3;
				return;
			}
			//로드완료
		}
	}
	else
	{
		_rcMouse = RectMakeCenter(_ptMouse.x, _ptMouse.y, 48, 45);
		
		//#====================================================================================================
		//#				※※※ 필독 ※※※ 사용 방법
		//#				에디터를 사용하기 전에 칠한 타일은 에디터를 사용하더라도 데이터 변경 X
		//#				추후에 적용 되도록 작업할 예정이며
		//#				그 전에 에디터 맵 저장하면 인게임에서 난리납니다
		//#=====================================================================================================
		//if (INPUT->GetKeyDown(VK_D))
		//{
		//	//샘플타일 데이터 에디트 
		//	loadMapData(_dataName);
		//	_editMode = true;
		//}

		if (_slideTool == false && _rcPalette.top < WINSIZEY + 17) // 최소화시=>화면밖까지 내리기 (맨위에 일정이상 내려갔을시 버튼이동하는 이프문있음)
		{
			_rcPalette.top += 5;
			_rcPalette.bottom += 5;
		}
		else if (_slideTool == true && _rcPalette.top > WINSIZEY / 2 - 15)
		{
			_rcPalette.top -= 5;
			_rcPalette.bottom -= 5;
		}

		this->maptoolSetup();

		if (_rcPalette.top > WINSIZEY) // 최소화시 화면밖으로 나가면서 이하만큼남앗을때 버튼생성(이동) ※맵툴 셋업보다 밑에있어야함
		{
			_rcslide = RectMake(WINSIZEX-110, WINSIZEY - 45, 110, 45);						//맵툴 UI
		}

		if (_palettePage == 4) { _rcArrow[1] = RectMake(-100, -100, 0, 0); }
		if (_palettePage == 5) { _rcArrow[0] = RectMake(-100, -100, 0, 0); }

		//화면 이동
		if (INPUT->GetKey(VK_UP))
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].rc.top += 10;
				_tiles[i].rc.bottom += 10;
			}
		}
		if (INPUT->GetKey(VK_DOWN))
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].rc.top -= 10;
				_tiles[i].rc.bottom -= 10;
			}

			_drawField.startY -= 10;//화면 이동시 선택영역 시작지점도 함께 이동
		}
		if (INPUT->GetKey(VK_RIGHT))
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].rc.left -= 10;
				_tiles[i].rc.right -= 10;
			}

			_drawField.startX -= 10;//화면이동시 선택영역 시작지점도 함께 이동
		}
		if (INPUT->GetKey(VK_LEFT))
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				_tiles[i].rc.left += 10;
				_tiles[i].rc.right += 10;
			}
		}
		if (INPUT->GetKeyDown(VK_SPACE))
		{
			for (int i = 0; i < TILEY; i++)
			{
				for (int j = 0; j < TILEX; j++)
				{
					_tiles[i * TILEX + j].rc = RectMake(TILESIZEx * j, TILESIZEy * i, TILESIZEx, TILESIZEy);
				}
			}
			
		}
		//포인터가 샘플타일 위에 있다면 샘플타일 선택
		//포인터가 맵타일 위에 있다면 선택되어 있는 샘플타일을 맵타일에 칠해준다.

		//버튼 클릭 부분
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&_rcTerrain, _ptMouse))
			{
				_currentTile.pageNumber = -1;
				//이부분 지우면 지우개 사이즈가 선택한 타일 사이즈만큼 들쑥날쑥해집니다
				_currentTile.sampleSizeX = 1;
				_currentTile.sampleSizeY = 1;
			}
			if (PtInRect(&_rcHome, _ptMouse))
			{
				SCENEMANAGER->loadScene("시작화면");	//게임 화면으로 돌아가기
			}
			if (PtInRect(&_rcObject, _ptMouse))
			{
			}

			
			//if (PtInRect(&_rcArrow5[0], _ptMouse) && _palettePage - 4 > 1)			//샘플타일의 번호가 1보다 클 때
			//{
			//	_palettePage -= 5;													//샘플타일의 번호를 1 감소시키고
			//	sprintf_s(_imageName, "map%d", _palettePage);
			//	sprintf_s(_dataName, "MapData\\map%d.txt", _palettePage);
			//	loadMapData(_dataName);											//해당 샘플타일을 팔레트에 그려준다.
			//}
			//if (PtInRect(&_rcArrow5[1], _ptMouse) && _palettePage + 4 < SMAPLETILECOUNT)			//샘플타일의 번호가 최대값보다 작을 때
			//{
			//	_palettePage += 5;													//샘플타일의 번호를 1 증가시키고
			//	sprintf_s(_imageName, "map%d", _palettePage);
			//	sprintf_s(_dataName, "MapData\\map%d.txt", _palettePage);
			//	loadMapData(_dataName);											//해당 샘플타일을 팔레트에 그려준다.
			//}
		


			//셈플타일 위에서 클릭했을 경우
			for (int i = 0; i < SAMPLETILEX*SAMPLETILEY; i++) {
				if (PtInRect(&_sampleTile[i].rc, _ptMouse)) {
					_currentTile.sampleStartX = _sampleTile[i].rc.left;		//시작 x좌표(타일 left)
					_currentTile.sampleStartY = _sampleTile[i].rc.top;	//시작 y좌표(타일 top)

					//프레임 시작 마우스 좌표
					_currentTile.sampleStartPointX = _sampleTile[i].tileFrameX;		//오른쪽으로 드래그 할때 시작 x프레임 좌표
					_currentTile.samplSetartPointY = _sampleTile[i].tileFrameY;		//아래로 드래그 할때 시작 y프레임 좌표
				}
			}
		}


		if (INPUT->GetKeyUp(VK_LBUTTON)) {
			if (PtInRect(&_rcslide, _ptMouse))
			{
				if (_slideTool == false) { _slideTool = true; }
				else if (_slideTool == true) { _slideTool = false; }
			}
			if (PtInRect(&_rcArrow[0], _ptMouse) && _palettePage > 1)			//샘플타일의 번호가 1보다 클 때
			{
				_palettePage--;													//샘플타일의 번호를 1 감소시키고
				//sprintf_s(_imageName, "map%d", _palettePage);
				//sprintf_s(_dataName, "MapData\\map%d.txt", _palettePage);
				loadMapData(_dataName);											//해당 샘플타일을 팔레트에 그려준다.
			}
			if (PtInRect(&_rcArrow[1], _ptMouse) && _palettePage < SMAPLETILECOUNT)			//샘플타일의 번호가 최대값보다 작을 때
			{
				_palettePage++;													//샘플타일의 번호를 1 증가시키고
				//sprintf_s(_imageName, "map%d", _palettePage);
				//sprintf_s(_dataName, "MapData\\map%d.txt", _palettePage);
				loadMapData(_dataName);											//해당 샘플타일을 팔레트에 그려준다.
			}
			if (PtInRect(&_rcTerrain, _ptMouse) && _palettePage > 4)
			{
				_palettePage = 1;
				loadMapData(_dataName);
			}
			if (PtInRect(&_rcObject, _ptMouse) && _palettePage < 5)
			{
				_palettePage = 5;
				loadMapData(_dataName);
			}
			if (PtInRect(&_rcSaveLoad, _ptMouse))
			{
				_setSaveLoad = true;
			}

			//셈플타일 위에서 마우스를 뗐을 경우 드래그의 마지막좌표를 가져온다(타일 드래그 끝점)
			for (int i = 0; i < SAMPLETILEX*SAMPLETILEY; i++) {
				if (PtInRect(&_sampleTile[i].rc, _ptMouse)) {
					_currentTile.sampleEndX = _sampleTile[i].rc.right;
					_currentTile.sampleEndY = _sampleTile[i].rc.bottom;

					if (_currentTile.sampleEndX <= _currentTile.sampleStartX) {
						int temp = _currentTile.sampleEndX - STILESIZEx;
						_currentTile.sampleEndX = _currentTile.sampleStartX + STILESIZEx;
						_currentTile.sampleStartX = temp;
						_currentTile.sampleStartPointX = _sampleTile[i].tileFrameX;		//왼쪽으로 드래그 할때 시작 x프레임 좌표
					}

					if (_currentTile.sampleEndY <= _currentTile.sampleStartY) {
						int temp = _currentTile.sampleEndY - STILESIZEy;
						_currentTile.sampleEndY = _currentTile.sampleStartY + STILESIZEy;
						_currentTile.sampleStartY = temp;
						_currentTile.samplSetartPointY = _sampleTile[i].tileFrameY;		//위로 드래그 할때 시작 y프레임 좌표
					}


					//면적에 따른 브러쉬 만들기
					this->setSample();
				}
			}
		}

		if (INPUT->GetKey(VK_LBUTTON)) this->setMap();//타일 채우기

		if (INPUT->GetKey('A') && INPUT->GetKey(VK_LBUTTON)) this->setAllMap();//타일 전부 채우기+지우기

		if (INPUT->GetKeyDown(VK_RBUTTON)) {
			//마우스 오른쪽을 눌러 칠하거나 지울 영역 선택하기
			for (int i = 0; i < TILEX*TILEY; i++) {
				if (PtInRect(&_tiles[i].rc, _ptMouse)) {
					_currentTile.sampleSizeX = 1;
					_currentTile.sampleSizeY = 1;

					_drawField.startX = _tiles[i].rc.left;
					_drawField.startY = _tiles[i].rc.top;

					_drawField.startIndex = i;
				}
			}
		}

		if (INPUT->GetKeyUp(VK_RBUTTON)) {
			//마우스 오른쪽을 떼서 채우기영역 설정 완료하기
			for (int i = 0; i < TILEX*TILEY; i++) {
				if (PtInRect(&_tiles[i].rc, _ptMouse)) {
					_drawField.endX = _tiles[i].rc.right;
					_drawField.endY = _tiles[i].rc.bottom;

					if (_drawField.endX < _drawField.startX) {
						_drawField.endX = _drawField.startX;
					}

					if (_drawField.endY < _drawField.startY) {
						_drawField.endY = _drawField.startY;
					}

					_drawField.sizeX = (_drawField.endX - _drawField.startX) / 48;
					_drawField.sizeY = (_drawField.endY - _drawField.startY) / 45;
					this->setFieldMap(); //범위 채우기로 이동
				}
			}
		}

		//샘플타일 내 드래그 상태 보이게 하기
		if (PtInRect(&_rcPalette, _ptMouse) && INPUT->GetKey(VK_LBUTTON)) {
			for (int i = 0; i < SAMPLETILEX*SAMPLETILEY; i++) {
				if (PtInRect(&_sampleTile[i].rc, _ptMouse)) {
					_dragRect.endX = _sampleTile[i].rc.right;
					_dragRect.endY = _sampleTile[i].rc.bottom;
				}
			}
			_dragRect.width = _dragRect.endX - _currentTile.sampleStartX;
			_dragRect.height = _dragRect.endY - _currentTile.sampleStartY;

			if (_dragRect.width > 0)
			{
				//드래그 우측 아래로
				if (_dragRect.height > 0)
					_dragRect.rc = RectMake(_currentTile.sampleStartX, _currentTile.sampleStartY, _dragRect.width, _dragRect.height);
				//드래그 우측 위로
				else
				{
					//_dragRect.endY는 top의 위치지만 bottom까지 내려와야 하므로 그만큼 내려준다.
					//_dragRect.height는 start의 top과 end의 bottom이므로 거꾸로 하면 48 * 2의 크기만큼 차이가 난다.
					//그것을 매꿔준다.
					if (_dragRect.height == 0)
						_dragRect.height = 1;
					_dragRect.rc = RectMake(_currentTile.sampleStartX, _dragRect.endY - STILESIZEy, _dragRect.width, -_dragRect.height + STILESIZEy * 2);
				}
			}
			else
			{
				//드래그 좌측 아래로
				if (_dragRect.height > 0)
				{
					if (_dragRect.width == 0)
						_dragRect.width = 1;
					//_dragRect.width = _currentTile.sampleStartX - _dragRect.endX;
					_dragRect.rc = RectMake(_dragRect.endX - STILESIZEx, _currentTile.sampleStartY, -_dragRect.width + STILESIZEx * 2, _dragRect.height);
				}
				//드래그 좌측 위로
				else
				{
					if (_dragRect.width == 0)
						_dragRect.width = 1;
					if (_dragRect.height == 0)
						_dragRect.height = 1;
					_dragRect.rc = RectMake(_dragRect.endX - STILESIZEx, _dragRect.endY - STILESIZEy, -_dragRect.width + STILESIZEx * 2, -_dragRect.height + STILESIZEy * 2);
				}
			}
		}
			if (_palettePage == 5)
			{
				
				for (int i = 0; i < 7; i++)
				{
					if (i < 2 && IntersectRect(&_rc, &_dragRect.rc, &_thorn[i])) 
					{
						_dragRect.rc = _thorn[i];
						_currentTile.sampleSizeX = _currentTile.sampleSizeY = 1;
					}
					else if (IntersectRect(&_rc, &_dragRect.rc, &_rcobject[i]))
					{
						_dragRect.rc = _rcobject[i]; 
						_currentTile.sampleSizeX = _currentTile.sampleSizeY = 1;
					}
				}
			}

			if (_palettePage == 6 || _palettePage == 7)
			{
				for (int i = 0; i < 4; i++)
				{
					if (IntersectRect(&_rc, &_dragRect.rc, &_rcComDoor[i]))
					{
						_dragRect.rc = _rcComDoor[i];
						if (i % 2 == 0)
						{
							_currentTile.sampleSizeX = 3;
							_currentTile.sampleSizeY = 2;
						}
						else
						{
							_currentTile.sampleSizeX = 2;
							_currentTile.sampleSizeY = 3;
						}
					}
					else if (IntersectRect(&_rc, &_dragRect.rc, &_rcLibDoor[i]))
					{
						_dragRect.rc = _rcLibDoor[i];
						if (i % 2 == 0)
						{
							_currentTile.sampleSizeX = 3;
							_currentTile.sampleSizeY = 2;
						}
						else
						{
							_currentTile.sampleSizeX = 2;
							_currentTile.sampleSizeY = 3;
						}
					}
					else if (IntersectRect(&_rc, &_dragRect.rc, &_rcBloodDoor[i]))
					{
						_dragRect.rc = _rcBloodDoor[i];
						if (i % 2 == 0)
						{
							_currentTile.sampleSizeX = 3;
							_currentTile.sampleSizeY = 2;
						}
						else
						{
							_currentTile.sampleSizeX = 2;
							_currentTile.sampleSizeY = 3;
						}
					}
					else if (IntersectRect(&_rc, &_dragRect.rc, &_rcSacriDoor[i]))
					{
						_dragRect.rc = _rcSacriDoor[i];
						if (i % 2 == 0)
						{
							_currentTile.sampleSizeX = 3;
							_currentTile.sampleSizeY = 2;
						}
						else
						{
							_currentTile.sampleSizeX = 2;
							_currentTile.sampleSizeY = 3;
						}
					}
					else if (IntersectRect(&_rc, &_dragRect.rc, &_rcTreasureDoor[i]))
					{
						_dragRect.rc = _rcTreasureDoor[i];
						if (i % 2 == 0)
						{
							_currentTile.sampleSizeX = 3;
							_currentTile.sampleSizeY = 2;
						}
						else
						{
							_currentTile.sampleSizeX = 2;
							_currentTile.sampleSizeY = 3;
						}
					}
					else if (IntersectRect(&_rc, &_dragRect.rc, &_rcDevilDoor[i]))
					{
						_dragRect.rc = _rcDevilDoor[i];
						if (i % 2 == 0)
						{
							_currentTile.sampleSizeX = 3;
							_currentTile.sampleSizeY = 2;
						}
						else
						{
							_currentTile.sampleSizeX = 2;
							_currentTile.sampleSizeY = 3;
						}
					}
					else if (IntersectRect(&_rc, &_dragRect.rc, &_rcBossDoor[i]))
					{
						_dragRect.rc = _rcBossDoor[i];
						if (i % 2 == 0)
						{
							_currentTile.sampleSizeX = 3;
							_currentTile.sampleSizeY = 2;
						}
						else
						{
							_currentTile.sampleSizeX = 2;
							_currentTile.sampleSizeY = 3;
						}
					}
				}
			}
	}
}



void maptoolScene::render()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_rcScreen, &_tiles[i].rc))
		{
			if (_tiles[i].imagePage[0] == -1)
			{
				Rectangle(getMemDC(), _tiles[i].rc);
				sprintf_s(_fileName, "map%d", _tiles[i].imagePage[1]);
				IMAGEMANAGER->scaleFrameRender(_fileName, getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].tileFrameX[1], _tiles[i].tileFrameY[1], 1.0f);
				sprintf_s(_fileName, "map%d", _tiles[i].imagePage[2]);
				IMAGEMANAGER->scaleFrameRender(_fileName, getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].tileFrameX[2], _tiles[i].tileFrameY[2], 1.0f);
			}
			else
			{
				sprintf_s(_fileName, "map%d", _tiles[i].imagePage[0]);
				IMAGEMANAGER->scaleFrameRender(_fileName, getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].tileFrameX[0], _tiles[i].tileFrameY[0], 1.0f);
				sprintf_s(_fileName, "map%d", _tiles[i].imagePage[1]);
				IMAGEMANAGER->scaleFrameRender(_fileName, getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].tileFrameX[1], _tiles[i].tileFrameY[1], 1.0f);
				sprintf_s(_fileName, "map%d", _tiles[i].imagePage[2]);
				IMAGEMANAGER->scaleFrameRender(_fileName, getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].tileFrameX[2], _tiles[i].tileFrameY[2], 1.0f);
			}
		}
		else { continue; }
	}
	
	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	RECT rc;
	//	if (IntersectRect(&rc, &_rcScreen, &_tiles[i].rc))
	//	{
 	//		if (_tiles[i].imagePage[0] == -1 && _tiles[i].imagePage[1] == -1) { continue; }
	//		else
	//		{
	//			sprintf_s(_fileName, "map%d", _tiles[i].imagePage[1]);
	//			IMAGEMANAGER->scaleFrameRender(_fileName, getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].tileFrameX[1], _tiles[i].tileFrameY[1], 1.0f);
	//		}
	//	}
	//	else { continue; }
	//}
	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	RECT rc;
	//	if (IntersectRect(&rc, &_rcScreen, &_tiles[i].rc))
	//	{
	//		if (_tiles[i].imagePage[0] == -1 && _tiles[i].imagePage[1] == -1 && _tiles[i].imagePage[2] == -1) { continue; }
	//		else
	//		{
	//			sprintf_s(_fileName, "map%d", _tiles[i].imagePage[2]);
	//			IMAGEMANAGER->scaleFrameRender(_fileName, getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].tileFrameX[2], _tiles[i].tileFrameY[2], 1.0f);
	//		}
	//	}
	//	else { continue; }
	//}


	//타일이 그려질 위치&범위 보이게 만들기
	for (int i = 0; i < TILEX*TILEY; i++) {
		if (PtInRect(&_tiles[i].rc, _ptMouse)) {
			selectRect = RectMake(_tiles[i].rc.left, _tiles[i].rc.top, _currentTile.sampleSizeX * 48, _currentTile.sampleSizeY * 45);

			//if (_dragRect.width > 0)
			//{
			//	//드래그 우측 아래로
			//	if (_dragRect.height > 0)
			//		selectRect = RectMake(_tiles[i].rc.left, _tiles[i].rc.top, _currentTile.sampleSizeX * 48, _currentTile.sampleSizeY * 48);
			//	//드래그 우측 위로
			//	else
			//	{
			//		//_dragRect.endY는 top의 위치지만 bottom까지 내려와야 하므로 그만큼 내려준다.
			//		//_dragRect.height는 start의 top과 end의 bottom이므로 거꾸로 하면 48 * 2의 크기만큼 차이가 난다.
			//		//그것을 매꿔준다.
			//		if (_dragRect.height == 0)
			//			_dragRect.height = 1;
			//		selectRect = RectMake(_tiles[i].rc.left, _tiles[i].rc.top, _currentTile.sampleSizeX * 48, _currentTile.sampleSizeY * 48);
			//	}
			//}
			//else
			//{
			//	//드래그 좌측 아래로
			//	if (_dragRect.height > 0)
			//	{
			//		if (_dragRect.width == 0)
			//			_dragRect.width = 1;
			//		//_dragRect.width = _currentTile.sampleStartX - _dragRect.endX;
			//		_dragRect.rc = RectMake(_dragRect.endX - TILESIZE, _currentTile.sampleStartY, -_dragRect.width + TILESIZE * 2, _dragRect.height);
			//	}
			//	//드래그 좌측 위로
			//	else
			//	{
			//		if (_dragRect.width == 0)
			//			_dragRect.width = 1;
			//		if (_dragRect.height == 0)
			//			_dragRect.height = 1;
			//		_dragRect.rc = RectMake(_dragRect.endX - TILESIZE, _dragRect.endY - TILESIZE, -_dragRect.width + TILESIZE * 2, -_dragRect.height + TILESIZE * 2);
			//	}
			//}

			if (INPUT->GetKey(VK_RBUTTON)) {
				_drawField.dragWidth = _tiles[i].rc.right - _drawField.startX;
				_drawField.dragHeight = _tiles[i].rc.bottom - _drawField.startY;
				selectRect = RectMake(_drawField.startX, _drawField.startY, _drawField.dragWidth, _drawField.dragHeight);
			}

			FrameRect(getMemDC(), selectRect, RGB(0, 255, 255));
			
		}
	}
	if (INPUT->GetToggleKey('G'))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			Rectangle(getMemDC(), _tiles[i].rc);
			if (_tiles[i]._type == OBJECT)
			{
				HBRUSH brush = CreateSolidBrush(RGB(50, 100, 100));
				HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
				FillRect(getMemDC(), &_tiles[i].rc, brush);
				SelectObject(getMemDC(), oldBrush);
				DeleteObject(brush);
			}
			else if (_tiles[i]._type == HITOBJECT)
			{
				HBRUSH brush = CreateSolidBrush(RGB(255, 20, 20));
				HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
				FillRect(getMemDC(), &_tiles[i].rc, brush);
				SelectObject(getMemDC(), oldBrush);
				DeleteObject(brush);
			}
			else if (_tiles[i]._type == TILE)
			{
				HBRUSH brush = CreateSolidBrush(RGB(125, 100, 250));
				HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
				FillRect(getMemDC(), &_tiles[i].rc, brush);
				SelectObject(getMemDC(), oldBrush);
				DeleteObject(brush);
			}
			else if (_tiles[i]._type == DOOR)
			{
				HBRUSH brush = CreateSolidBrush(RGB(0, 255, 255));
				HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
				FillRect(getMemDC(), &_tiles[i].rc, brush);
				SelectObject(getMemDC(), oldBrush);
				DeleteObject(brush);
			}
			else if (_tiles[i]._type == LOCKEDDOOR)
			{
				HBRUSH brush = CreateSolidBrush(RGB(65, 160, 220));
				HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
				FillRect(getMemDC(), &_tiles[i].rc, brush);
				SelectObject(getMemDC(), oldBrush);
				DeleteObject(brush);
			}
		}
	}
	//Rectangle(getMemDC(), _rcPalette);
	IMAGEMANAGER->findImage("textbox")->render(getMemDC(), _rcPalette.left, _rcPalette.top, 0, 0, 330, 270);
	//레이어 이미지 그리기
	//if (_layer[0]) { IMAGEMANAGER->findImage("Layer")->frameRender(getMemDC(), _rcScreen.right - 128, _rcScreen.top, 0, 0); }
	//else if (_layer[1]) { IMAGEMANAGER->findImage("Layer")->frameRender(getMemDC(), _rcScreen.right - 128, _rcScreen.top, 1, 0); }
	//else { IMAGEMANAGER->findImage("Layer")->frameRender(getMemDC(), _rcScreen.right - 128, _rcScreen.top, 2, 0); }


	for (int i = 0; i < SAMPLETILEX*SAMPLETILEY; i++)
	{
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		Rectangle(getMemDC(), _sampleTile[i].rc);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);


		_sampleTile[i].tileFrameX = i % 20;
		_sampleTile[i].tileFrameY = i / 20;
		_sampleTile[i].imagePage = _palettePage;

		sprintf(_pageNum, "page : %d", _palettePage);
		sprintf(_pageName, "smap%d", _palettePage);
		//IMAGEMANAGER->findImage(_pageName)->scaleFrameRender(getMemDC(), _sampleTile[i].rc.left, _sampleTile[i].rc.top, i % 20, i / 20, 0.5f);

		//if (_editMode && _editCanMove)
		//{
		//	if (_sampleTile[i].canMove == true) { sprintf_s(_canMoveChar, "%d", 1); }
		//	else { sprintf_s(_canMoveChar, "%d", 0); }
		//
		//	TextOut(getMemDC(), _sampleTile[i].rc.left, _sampleTile[i].rc.top, _canMoveChar, strlen(_canMoveChar));
		//}

		//if (_editMode && _editMoveDirect)
		//{
		//	for (int j = 0; j < 4; j++)
		//	{
		//		if (_sampleTile[i].direct[j] == true) { _moveDirectChar[j] = 'T'; }
		//		else { _moveDirectChar[j] = 'F'; }
		//	}
		//	TextOut(getMemDC(), _sampleTile[i].rc.left, _sampleTile[i].rc.top, _moveDirectChar, strlen(_moveDirectChar));
		//}
	}


	IMAGEMANAGER->findImage(_pageName)->render(getMemDC(), _sampleTile[0].rc.left, _sampleTile[0].rc.top);
	//Rectangle(getMemDC(), _rcSaveLoad);			//이미지 생기면 Rectangle 대신 이미지를 출력해야 함.
	//Rectangle(getMemDC(), _rcTerrain);			//이미지 생기면 Rectangle 대신 이미지를 출력해야 함.
	//Rectangle(getMemDC(), _rcHome);				//이미지 생기면 Rectangle 대신 이미지를 출력해야 함.
	//Rectangle(getMemDC(), _rcObject);			//이미지 생기면 Rectangle 대신 이미지를 출력해야 함.
	//Rectangle(getMemDC(), _rcslide);			//이미지 생기면 Rectangle 대신 이미지를 출력해야 함.
	//Rectangle(getMemDC(), _rcArrow[0]);			//이미지 생기면 Rectangle 대신 이미지를 출력해야 함.
	//Rectangle(getMemDC(), _rcArrow[1]);			//이미지 생기면 Rectangle 대신 이미지를 출력해야 함.

	if (PtInRect(&_rcSaveLoad, _ptMouse)) { IMAGEMANAGER->findImage("saveLoad")->render(getMemDC(), _rcSaveLoad.left, _rcSaveLoad.top); }
	else { IMAGEMANAGER->findImage("saveLoad_off")->render(getMemDC(), _rcSaveLoad.left, _rcSaveLoad.top); }

	if (PtInRect(&_rcTerrain, _ptMouse)) { IMAGEMANAGER->findImage("terrain")->render(getMemDC(), _rcTerrain.left, _rcTerrain.top); }
	else { IMAGEMANAGER->findImage("terrain_off")->render(getMemDC(), _rcTerrain.left, _rcTerrain.top); }

	if (PtInRect(&_rcObject, _ptMouse)) { IMAGEMANAGER->findImage("object")->render(getMemDC(), _rcObject.left, _rcObject.top); }
	else { IMAGEMANAGER->findImage("object_off")->render(getMemDC(), _rcObject.left, _rcObject.top); }

	if (PtInRect(&_rcHome, _ptMouse)) { IMAGEMANAGER->findImage("home")->render(getMemDC(), _rcHome.left, _rcHome.top); }
	else { IMAGEMANAGER->findImage("home_off")->render(getMemDC(), _rcHome.left, _rcHome.top); }

	if (PtInRect(&_rcslide, _ptMouse)) { IMAGEMANAGER->findImage("slide")->render(getMemDC(), _rcslide.left, _rcslide.top); }
	else { IMAGEMANAGER->findImage("slide_off")->render(getMemDC(), _rcslide.left, _rcslide.top); }

	if (!(_palettePage == 1)) { IMAGEMANAGER->findImage("arrL")->render(getMemDC(), _rcArrow[0].left, _rcArrow[0].top); }
	if (!(_palettePage == 7)) { IMAGEMANAGER->findImage("arrR")->render(getMemDC(), _rcArrow[1].left, _rcArrow[1].top); }

	//HBRUSH brush = CreateSolidBrush(RGB(140, 0, 250));
	//HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	//
	//FillRect(getMemDC(), &_rcTerrain, brush);
	//brush = CreateSolidBrush(RGB(140, 50, 50));
	//FillRect(getMemDC(), &_rcslide, brush);
	//brush = CreateSolidBrush(RGB(50, 140, 50));
	//FillRect(getMemDC(), &_rcHome, brush);
	//brush = CreateSolidBrush(RGB(50, 50, 140));
	//FillRect(getMemDC(), &_rcObject, brush);
	//brush = CreateSolidBrush(RGB(50, 140, 140));
	//FillRect(getMemDC(), &_rcSaveLoad, brush);
	//brush = CreateSolidBrush(RGB(140, 50, 140));
	//FillRect(getMemDC(), &_rcArrow[0], brush);
	//brush = CreateSolidBrush(RGB(140, 140, 50));
	//FillRect(getMemDC(), &_rcArrow[1], brush);
	//
	//SelectObject(getMemDC(), oldBrush);
	//DeleteObject(brush);

	//HBRUSH brush = CreateSolidBrush(RGB(16, 64, 168));
	//HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	//Rectangle(getMemDC(), _rcArrow5[0].left, _rcArrow5[0].top, _rcArrow5[1].right, _rcArrow5[1].bottom);
	//Rectangle(getMemDC(), _rcArrow[0].left, _rcArrow[0].top, _rcArrow[1].right, _rcArrow[1].bottom);
	//SelectObject(getMemDC(), oldBrush);
	//DeleteObject(brush);


	//샘플타일의 번호가 1보다 작은 경우는 없으므로 1보다 큰 경우에만 이전 타일로 넘어가는 화살표를 보여준다.
	//if (_palettePage > 1) { IMAGEMANAGER->findImage("leftArrow")->render(getMemDC(), _rcArrow[0].left, _rcArrow[0].top); }
	//if (_palettePage > 1) { IMAGEMANAGER->findImage("leftArrow5")->render(getMemDC(), _rcArrow5[0].left, _rcArrow5[0].top); }
	//샘플타일의 번호가 최대값보다 큰 경우는 없으므로 최대값보다 작은 경우에만 다음 타일로 넘어가는 화살표를 보여준다.
	//if (_palettePage < SMAPLETILECOUNT) { IMAGEMANAGER->findImage("rightArrow")->render(getMemDC(), _rcArrow[1].left, _rcArrow[1].top); }
	//if (_palettePage < SMAPLETILECOUNT) { IMAGEMANAGER->findImage("rightArrow5")->render(getMemDC(), _rcArrow5[1].left, _rcArrow5[1].top); }

	if (_setSaveLoad == true)
	{
	

		//Rectangle(getMemDC(), _rcSaveWindow);
		IMAGEMANAGER->findImage("textbox")->render(getMemDC(), _rcSaveWindow.left, _rcSaveWindow.top, 0, 0, 300, 250);
		//IMAGEMANAGER->findImage("textbox")->render(getMemDC(), _rcSaveWindow.left, _rcSaveWindow.top, 0, 0,
		//	_rcSaveWindow.right - _rcSaveWindow.left, _rcSaveWindow.bottom - _rcSaveWindow.top);
		
		//Rectangle(getMemDC(), _rcSaveSlot[0]);
		//Rectangle(getMemDC(), _rcSaveSlot[1]);
		//Rectangle(getMemDC(), _rcSaveSlot[2]);	



		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&_rcSaveSlot[i], _ptMouse))
			{
				IMAGEMANAGER->findImage("activetextbox")->render(getMemDC(), _rcSaveSlot[i].left, _rcSaveSlot[i].top, 0, 0,
					_rcSaveSlot[i].right - _rcSaveSlot[i].left, _rcSaveSlot[i].bottom - _rcSaveSlot[i].top);
			}//마우스 가져가면 활성화
		
			if (_setSaveSlot == i)
			{
				IMAGEMANAGER->findImage("activetextbox")->render(getMemDC(), _rcSaveSlot[i].left, _rcSaveSlot[i].top, 0, 0,
					_rcSaveSlot[i].right - _rcSaveSlot[i].left, _rcSaveSlot[i].bottom - _rcSaveSlot[i].top);
			}
		}


		FrameRect(getMemDC(), _rcSaveSlot[0], RGB(140, 60, 180));				 //세이브슬롯 구분해주기
		FrameRect(getMemDC(), _rcSaveSlot[1], RGB(140, 60, 180));				 //세이브슬롯 구분해주기
		FrameRect(getMemDC(), _rcSaveSlot[2], RGB(140, 60, 180));				 //세이브슬롯 구분해주기

		Rectangle(getMemDC(), _rcSave);
	
		IMAGEMANAGER->findImage("save")->render(getMemDC(), _rcSave.left, _rcSave.top);

		Rectangle(getMemDC(), _rcLoad);
		IMAGEMANAGER->findImage("load")->render(getMemDC(), _rcLoad.left, _rcLoad.top);
		char str[16];
		for (int i = 0; i < 3; i++)
		{
			sprintf(str, "slot %d", i+1);
			textOut(getMemDC(), _rcSaveSlot[i].left+10, _rcSaveSlot[i].top+10, str, strlen(str));
		}
		
		//IMAGEMANAGER->findImage("slot1")->render(getMemDC(), _rcSaveSlot[0].left + 10, _rcSaveSlot[0].top + 5);
		//IMAGEMANAGER->findImage("slot2")->render(getMemDC(), _rcSaveSlot[1].left + 10, _rcSaveSlot[1].top + 5);
		//IMAGEMANAGER->findImage("slot3")->render(getMemDC(), _rcSaveSlot[2].left + 10, _rcSaveSlot[2].top + 5);

	}

	RECT _rcDragPallette = RectMake(_rcPalette.left, _rcPalette.top, _rcPalette.right - _rcPalette.left - 48 * 2, _rcPalette.bottom - _rcPalette.top);
	if (_rcPalette.top == WINSIZEY/2-15 && IntersectRect(&_dragRect.rc,&_dragRect.rc,&_rcPalette))
	{
		FrameRect(getMemDC(), _dragRect.rc, RGB(255, 255, 0));
	}
	

}

void maptoolScene::maptoolSetup()
{

	//_rcPalette = RectMakeCenter((_rcScreen.left + _rcScreen.right) / 2, _rcScreen.bottom - 192, 576, 288);

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			_sampleTile[i * 20 + j].rc = RectMake(_rcPalette.left + (j * 16), _rcPalette.top + (i * 15), 16, 15);
			_sampleTile[i * 20 + j].tileFrameX = j;
			_sampleTile[i * 20 + j].tileFrameY = i;
		}
	}

	_rcSaveLoad		= RectMake(_rcPalette.left +220, _rcPalette.top + 180, 110, 45);		
	_rcTerrain		= RectMake(_rcPalette.left, _rcPalette.top + 180, 110, 45);				
	_rcObject		= RectMake(_rcPalette.left +110, _rcPalette.top + 180, 110, 45);				
	_rcHome			= RectMake(_rcPalette.left +220, _rcPalette.top + 225, 110, 45);		
	_rcslide		= RectMake(_rcPalette.left +110, _rcPalette.top + 225, 110, 45);		
	//_rcDummy3		= RectMake(_rcPalette.right -96, _rcPalette.top + 180, 96, 45);			
	//_rcArrow5[0]	= RectMake(_rcPalette.right -96, _rcPalette.top + 180, 48, 45);
	//_rcArrow5[1]	= RectMake(_rcPalette.right -48, _rcPalette.top + 180, 48, 45);
	_rcArrow[0]		= RectMake(_rcPalette.left, _rcPalette.top + 225, 55, 45);				
	_rcArrow[1]		= RectMake(_rcPalette.left+55, _rcPalette.top + 225, 55, 45);			

	_rcSaveWindow = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 50, 300, 250);				
	for (int i = 0; i < 3; i++)																
	{																						
		_rcSaveSlot[i] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 125 + i * 49, 250, 50);
	}																						
	_rcSave = RectMakeCenter(WINSIZEX / 2 - 70, WINSIZEY / 2 + 35, 80, 35);					
	_rcLoad = RectMakeCenter(WINSIZEX / 2 + 70, WINSIZEY / 2 + 35, 80, 35);					
}

void maptoolScene::setSample() {

	//선택된 x방향타일 갯수
	_currentTile.sampleSizeX = (_currentTile.sampleEndX - _currentTile.sampleStartX) / 16;
	//선택돤 y방향타일 갯수
	_currentTile.sampleSizeY = (_currentTile.sampleEndY - _currentTile.sampleStartY) / 15;

	if (_palettePage > 5) 
	{
		if (_dragRect.rc.right - _dragRect.rc.left > _dragRect.rc.bottom - _dragRect.rc.top)
		{
			_currentTile.sampleSizeX = 3;
			_currentTile.sampleSizeY = 2;
		}
		else 
		{
			_currentTile.sampleSizeX = 2;
			_currentTile.sampleSizeY = 3;
		}
	}

	_currentTile.pageNumber = _palettePage;


	//새로 선택했을 때 기존에 선택되어 있었던 타일은 지워지게 해야함
	//안그러면 이후에 선택한 타일이 선택한 타일보다 작을 경우 이전 타일이 같이 그려짐
	for (int i = 0; i < SAMPLETILEX; i++) {
		_currentTile.x[i] = -1;
	}

	for (int i = 0; i < SAMPLETILEY; i++) {
		_currentTile.y[i] = -1;
	}

	//좌표값 가져오기
		if (_palettePage > 5){_currentTile.sampleStartPointX = (_dragRect.rc.left-_rcPalette.left)/16; }
	for (int i = 0; i < _currentTile.sampleSizeX; i++) {
		_currentTile.x[i] = _currentTile.sampleStartPointX + i;
	}

		if (_palettePage > 5) { _currentTile.samplSetartPointY = (_dragRect.rc.top - _rcPalette.top)/15; }
	for (int i = 0; i < _currentTile.sampleSizeY; i++) {
		_currentTile.y[i] = _currentTile.samplSetartPointY + i;
	}
}

void maptoolScene::setMap()
{
	//팝업 아래에서 버튼눌렀을때 뒤에 칠 안되게 넘겨주기


	if (PtInRect(&_rcSaveLoad, _ptMouse)) { return; }
	else if (PtInRect(&_rcslide, _ptMouse)) { return; }
	//else if (PtInRect(&_rcArrow5[0], _ptMouse)) { return; }
	//else if (PtInRect(&_rcArrow5[1], _ptMouse)) { return; }
	else if (PtInRect(&_rcArrow[0], _ptMouse)) { return; }
	else if (PtInRect(&_rcArrow[1], _ptMouse)) { return; }



	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, _ptMouse) && !PtInRect(&_rcPalette, _ptMouse) && selectRect.right <= _tiles[TILEX - 1].rc.right && selectRect.bottom <= _tiles[TILEX * TILEY - 1].rc.bottom)
		{
			//가장 하단 레이어인가
			//if (_layer[0])
			//{
			if (_palettePage<5)
			{
				for (int j = 0; j < _currentTile.sampleSizeY; j++) {
					for (int n = 0; n < _currentTile.sampleSizeX; n++) {
						//_tiles[i + (j * TILEX + n)].canMove[0] = _canMove;
						_tiles[i + (j * TILEX + n)].tileFrameX[0] = _currentTile.x[n];
						_tiles[i + (j * TILEX + n)].tileFrameY[0] = _currentTile.y[j];
						_tiles[i + (j * TILEX + n)].imagePage[0] = _currentTile.pageNumber;
						_tiles[i + (j * TILEX + n)].imagePage[1] = -1;
						_tiles[i + (j * TILEX + n)].imagePage[2] = -1;
						_tiles[i + (j * TILEX + n)].terrain = terrainSelect(_currentTile.x[n], _currentTile.y[j]);
						if ((i + (j * TILEX + n)) % TILEX > 2 && (i + (j * TILEX + n)) % TILEX < TILEX-3 && (i + (j * TILEX + n)) / TILEX > 1 && (i + (j * TILEX + n)) / TILEX < TILEY-2)
						{
							_tiles[i + (j * TILEX + n)]._type = TILE;
						}
						else { _tiles[i + (j * TILEX + n)]._type = OBJECT; }
						//_tiles[i + (j * TILEX + n)]._type = OBJECT;
					}
			
				}
			}
			else if (_palettePage == 5)
			{
				for (int j = 0; j < _currentTile.sampleSizeY; j++) {
					for (int n = 0; n < _currentTile.sampleSizeX; n++) {
						//_tiles[i + (j * TILEX + n)].canMove[0] = _canMove;
						_tiles[i + (j * TILEX + n)].tileFrameX[1] = _currentTile.x[n];
						_tiles[i + (j * TILEX + n)].tileFrameY[1] = _currentTile.y[j];
						_tiles[i + (j * TILEX + n)].imagePage[1] = _currentTile.pageNumber;
						_tiles[i + (j * TILEX + n)].tileFrameX[2] = _currentTile.x[n];
						_tiles[i + (j * TILEX + n)].tileFrameY[2] = _currentTile.y[j];
						_tiles[i + (j * TILEX + n)].imagePage[2] = _currentTile.pageNumber;
						_tiles[i + (j * TILEX + n)].terrain = terrainSelect(_currentTile.x[n], _currentTile.y[j]);

						for (int k = 0; k < 7; k++)
						{
							if (k < 2 && IntersectRect(&_rc, &_dragRect.rc, &_thorn[k]))
							{
								_tiles[i + (j * TILEX + n)]._type = HITOBJECT;
							}
							else if (IntersectRect(&_rc, &_dragRect.rc, &_rcobject[k]))
							{
								_tiles[i + (j * TILEX + n)]._type = OBJECT;
							}
							
						}
					}

				}
			}
			else if (_palettePage == 6)
			{
				for (int j = 0; j < _currentTile.sampleSizeY; j++) {
					for (int n = 0; n < _currentTile.sampleSizeX; n++) {
						//_tiles[i + (j * TILEX + n)].canMove[0] = _canMove;
						_tiles[i + (j * TILEX + n)].tileFrameX[1] = _currentTile.x[n];
						_tiles[i + (j * TILEX + n)].tileFrameY[1] = _currentTile.y[j];
						_tiles[i + (j * TILEX + n)].imagePage[1] = _currentTile.pageNumber;
						_tiles[i + (j * TILEX + n)].terrain = terrainSelect(_currentTile.x[n], _currentTile.y[j]);

						RECT _rc;
						RECT _selRc;
						_selRc = RectMakeCenter(selectRect.left + (selectRect.right - selectRect.left) / 2, selectRect.top + (selectRect.bottom - selectRect.top) / 2, 30, 30);
						if (IntersectRect(&_rc, &_tiles[i +(j * TILEX + n)].rc, &_selRc))
						{
							 _tiles[i + (j * TILEX + n)]._type = DOOR; 
						}
					}

				}
			}
			else if (_palettePage == 7)
			{
				for (int j = 0; j < _currentTile.sampleSizeY; j++) {
					for (int n = 0; n < _currentTile.sampleSizeX; n++) {
						//_tiles[i + (j * TILEX + n)].canMove[0] = _canMove;
						_tiles[i + (j * TILEX + n)].tileFrameX[2] = _currentTile.x[n];
						_tiles[i + (j * TILEX + n)].tileFrameY[2] = _currentTile.y[j];
						_tiles[i + (j * TILEX + n)].imagePage[2] = _currentTile.pageNumber;
						_tiles[i + (j * TILEX + n)].terrain = terrainSelect(_currentTile.x[n], _currentTile.y[j]);
							RECT _rc;
						RECT _selRc;
						_selRc = RectMakeCenter(selectRect.left + (selectRect.right - selectRect.left) / 2, selectRect.top + (selectRect.bottom - selectRect.top) / 2, 30, 30);
						if (IntersectRect(&_rc, &_tiles[i + (j * TILEX + n)].rc, &_selRc))
						{
							if (IntersectRect(&_rc, &_dragRect.rc, &RectMake(_rcTreasureDoor[0].left, _rcTreasureDoor[0].top, 16 * 5, 15 * 5))) { _tiles[i + (j * TILEX + n)]._type = LOCKEDDOOR; }
						}
						//for (int k = 0; k < 7; k++)
						//{
						//	if (k < 2 && IntersectRect(&_rc, &_dragRect.rc, &_thorn[k]))
						//	{
						//		_tiles[i + (j * TILEX + n)]._type = HITOBJECT;
						//	}
						//	else if (IntersectRect(&_rc, &_dragRect.rc, &_rcobject[k]))
						//	{
						//		_tiles[i + (j * TILEX + n)]._type = OBJECT;
						//	}
						//
						//}
					}

				}
			}
			//}
			////중간 레이어인가
			//if (_layer[1])
			//{
			//	for (int j = 0; j < _currentTile.sampleSizeY; j++) {
			//		for (int n = 0; n < _currentTile.sampleSizeX; n++) {
			//		//	_tiles[i + (j * TILEX + n)].canMove[1] = _canMove;
			//			_tiles[i + (j * TILEX + n)].tileFrameX[1] = _currentTile.x[n];
			//			_tiles[i + (j * TILEX + n)].tileFrameY[1] = _currentTile.y[j];
			//			_tiles[i + (j * TILEX + n)].imagePage[1] = _currentTile.pageNumber;
			//			_tiles[i + (j * TILEX + n)].terrain = terrainSelect(_currentTile.x[n], _currentTile.y[j]);
			//		}
			//	}
			//}
			////가장 위 레이어인가
			//if (_layer[2])
			//{
			//	for (int j = 0; j < _currentTile.sampleSizeY; j++) {
			//		for (int n = 0; n < _currentTile.sampleSizeX; n++) {
			//		//	_tiles[i + (j * TILEX + n)].canMove[2] = _canMove;
			//			_tiles[i + (j * TILEX + n)].tileFrameX[2] = _currentTile.x[n];
			//			_tiles[i + (j * TILEX + n)].tileFrameY[2] = _currentTile.y[j];
			//			_tiles[i + (j * TILEX + n)].imagePage[2] = _currentTile.pageNumber;
			//			_tiles[i + (j * TILEX + n)].terrain = terrainSelect(_currentTile.x[n], _currentTile.y[j]);
			//		}
			//	}
			//}
		}
	}
}

void maptoolScene::setAllMap() {
	for (int i = 0; i < TILEX * TILEY; i++) {
		//가장 하단 레이어
		//if (_layer[0])
		//{
			//_tiles[i].canMove[0] = _canMove;
			_tiles[i].imagePage[0] = _currentTile.pageNumber;
			_tiles[i].tileFrameX[0] = _currentTile.x[0];
			_tiles[i].tileFrameY[0] = _currentTile.y[0];
			_tiles[i].terrain = terrainSelect(_currentTile.x[0], _currentTile.y[0]);
		//}
		////중간 레이어
		//if (_layer[1])
		//{
		//	//_tiles[i].canMove[1] = _canMove;
		//	_tiles[i].tileFrameX[1] = _currentTile.x[0];
		//	_tiles[i].tileFrameY[1] = _currentTile.y[0];
		//	_tiles[i].imagePage[1] = _currentTile.pageNumber;
		//	_tiles[i].terrain = terrainSelect(_currentTile.x[0], _currentTile.y[0]);
		//}
		////가장 위 레이어
		//if (_layer[2])
		//{
		//	//_tiles[i].canMove[2] = _canMove;
		//	_tiles[i].tileFrameX[2] = _currentTile.x[0];
		//	_tiles[i].tileFrameY[2] = _currentTile.y[0];
		//	_tiles[i].imagePage[2] = _currentTile.pageNumber;
		//	_tiles[i].terrain = terrainSelect(_currentTile.x[0], _currentTile.y[0]);
		//}
	}
}

void maptoolScene::setFieldMap() {
	for (int i = 0; i < _drawField.sizeY; i++) {
		for (int j = 0; j < _drawField.sizeX; j++) {
			//가장 하단 레이어
			//if (_layer[0])
			//{
				//_tiles[_drawField.startIndex + (i * TILEX + j)].canMove[0] = _canMove;
				_tiles[_drawField.startIndex + (i * TILEX + j)].imagePage[0] = _currentTile.pageNumber;
				_tiles[_drawField.startIndex + (i * TILEX + j)].tileFrameX[0] = _currentTile.x[0];
				_tiles[_drawField.startIndex + (i * TILEX + j)].tileFrameY[0] = _currentTile.y[0];
				_tiles[_drawField.startIndex + (i * TILEX + j)].terrain = terrainSelect(_currentTile.x[0], _currentTile.y[0]);
			//}
			//중간 레이어
			//if (_layer[1])
			//{
			//	//_tiles[_drawField.startIndex + (i * TILEX + j)].canMove[1] = _canMove;
			//	_tiles[_drawField.startIndex + (i * TILEX + j)].tileFrameX[1] = _currentTile.x[0];
			//	_tiles[_drawField.startIndex + (i * TILEX + j)].tileFrameY[1] = _currentTile.y[0];
			//	_tiles[_drawField.startIndex + (i * TILEX + j)].imagePage[1] = _currentTile.pageNumber;
			//	_tiles[_drawField.startIndex + (i * TILEX + j)].terrain = terrainSelect(_currentTile.x[0], _currentTile.y[0]);
			//}
			////가장 위 레이어
			//if (_layer[2])
			//{
			//	//_tiles[_drawField.startIndex + (i * TILEX + j)].canMove[2] = _canMove;
			//	_tiles[_drawField.startIndex + (i * TILEX + j)].tileFrameX[2] = _currentTile.x[0];
			//	_tiles[_drawField.startIndex + (i * TILEX + j)].tileFrameY[2] = _currentTile.y[0];
			//	_tiles[_drawField.startIndex + (i * TILEX + j)].imagePage[2] = _currentTile.pageNumber;
			//	_tiles[_drawField.startIndex + (i * TILEX + j)].terrain = terrainSelect(_currentTile.x[0], _currentTile.y[0]);
			//}
		}
	}
}

void maptoolScene::uiMove()
{

}

void maptoolScene::save(char* str)
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(TILESIZEx * j, TILESIZEy * i, TILESIZEx, TILESIZEy);
		}
	}
	HANDLE file;
	DWORD write;

	file = CreateFile(str, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	CloseHandle(file);
}
void maptoolScene::load(char* str)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(str, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}

void maptoolScene::saveMapData(char *str)
{
	HANDLE file;
	DWORD write;

	file = CreateFile(str, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
	{
		file = CreateFile(str, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(file, _sampleTile, sizeof(tagSampleTile) * (SAMPLETILEX - 2) * SAMPLETILEY, &write, NULL);
	}
	else
	{
		WriteFile(file, _sampleTile, sizeof(tagSampleTile) * (SAMPLETILEX - 2) * SAMPLETILEY, &write, NULL);
	}
	CloseHandle(file);
}

void maptoolScene::loadMapData(char* str)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(str, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
	{
		saveMapData(str);
	}
	else
	{
		ReadFile(file, _sampleTile, sizeof(tagSampleTile) * (SAMPLETILEX - 2) * SAMPLETILEY, &read, NULL);
	}
	CloseHandle(file);
}


//void maptoolScene::selectLayer1()
//{
//	_layer[0] = true;
//	_layer[1] = false;
//	_layer[2] = false;
//}
//void maptoolScene::selectLayer2()
//{
//	_layer[0] = false;
//	_layer[1] = true;
//	_layer[2] = false;
//}
//void maptoolScene::selectLayer3()
//{
//	_layer[0] = false;
//	_layer[1] = false;
//	_layer[2] = true;
//}

TERRAIN maptoolScene::terrainSelect(int frameX, int frameY)
{
	TERRAIN t;
	t.x = frameX;
	t.y = frameY;

	return t;
}
