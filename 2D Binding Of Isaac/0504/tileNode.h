#pragma once

//����ȭ�� Ÿ��
#define TILESIZEx 48			//Ÿ�� �ȼ�
#define TILESIZEy 45			//Ÿ�� �ȼ�
#define TILEX 40			//�� Ÿ���� ���ΰ� �� ĭ����
#define TILEY 24			//�� Ÿ���� ���ΰ� �� ĭ����
#define TILESIZEX (TILEX * TILESIZEx)		//�� Ÿ���� ������ �ȼ� ��
#define TILESIZEY (TILEY * TILESIZEx)		//�� Ÿ���� ������ �ȼ� ��

//�̹��� Ÿ��(ȭ�� ������ܿ� �ٿ����� ����Ÿ��)
#define SAMPLETILEX 20
#define SAMPLETILEY 12
#define STILESIZEx 48/3			//Ÿ�� �ȼ�
#define STILESIZEy 45/3			//Ÿ�� �ȼ�

//����Ÿ�� ���� ����
//���� Ÿ���� �� 69������ �ֽ��ϴ�
#define SMAPLETILECOUNT 7

//���̾� ���� ����
#define LAYERCOUNT 3

enum TILETYPE
{
	TILE,
	OBJECT,
	HITOBJECT,
	BREAKOBJECT,							//��
	LOCKEDDOOR,								//�����ʿ�
	DOOR

};
//����
struct TERRAIN
{
	int x, y;		//Ÿ��(x, y)���� ����.
};

//Ÿ�ϱ���ü
//�� Ÿ�ϴ� ���̾� ���� 3������
struct tagTile
{
	TILETYPE _type;
	TERRAIN terrain;
	RECT rc;
	bool canMove[LAYERCOUNT] = { false, };	//�� Ÿ�� ���� �̵��� �� �ִ��� Ȯ�����ִ� bool ����
											//�⺻�� false
											//�ϳ��� false�� �� Ÿ�� ���δ� �̵��� �� ����
	bool direct[4] = { false, };			//�̵��� �����ϴٸ� � �������� �̵��� �� �ִ��� ����
											//true�� ��쿡�� �̵� ����.
											//�⺻�� == false
											//0: ��, 1: �Ʒ�, 2: ��, 3: ��
	int imagePage[LAYERCOUNT] = { -1, };	//� ���ø��� �׷ȴ��� �����ϴ� ����
	int tileFrameX[LAYERCOUNT];				//imagePage�� ���η� �� ��° Ÿ������ �����ϴ� ����
	int tileFrameY[LAYERCOUNT];				//imagePage�� ���η� �� ��° Ÿ������ �����ϴ� ����
};

//�̹��� Ÿ�� ����ü
struct tagSampleTile
{
	RECT rc;

	int imagePage;							//����Ÿ�� ��ȣ
	int tileFrameX;							//���� �� ��°�� �׷��������� ������ ����
	int tileFrameY;							//���� �� ��°�� �׷��������� ������ ����

	bool canMove = false;					//�� Ÿ�Ϸ� �̵��� �����Ѱ�?
											//�⺻�� : �̵��Ұ�
	bool direct[4] = { false, };			//�� Ÿ�Ͽ��� � �������� �̵��� �����Ѱ�?
											//�⺻�� : �̵��Ұ�
											//0:��  1:�Ʒ�  2:��  3:��
};

//����Ÿ�� ����ü
struct tagCurrentTile
{
	int pageNumber;							//����Ÿ�� ��ȣ
	int sampleSizeX;						//����Ÿ�� x������
	int sampleSizeY;						//����Ÿ�� y������
	int sampleStartX;						//�巡�׽� ����Ÿ�� �����ϴ� X��ġ
	int sampleStartY;						//�巡�׽� ����Ÿ�� �����ϴ� Y��ġ
	int sampleStartPointX;
	int samplSetartPointY;
	int sampleEndX;							//�巡�׽� ����Ÿ�� ������ X��ġ
	int sampleEndY;							//�巡�׽� ����Ÿ�� ������ Y��ġ
	int sampleEndPointX;
	int sampleEndPointY;
	int x[SAMPLETILEX], y[SAMPLETILEY];						//Ÿ�� ��ǥ�� ����� (x, y�迭)
};

//�巡�׿� ��Ʈ
struct dragRect
{
	int endX;
	int endY;
	int width;
	int height;
	RECT rc;
};

//�巡�׿� ������Ʈ
struct drawField
{
	int startX;			//���� �׸��� ���� x��ǥ
	int startY;			//���� �׸��� ���� y��ǥ
	int endX;			//���� �׸��� �� x��ǥ
	int endY;			//���� �׸��� �� y��ǥ
	int startIndex;		//�׸��⸦ ������ Ÿ�� ��ȣ
	int sizeX;
	int sizeY;
	int dragWidth;
	int dragHeight;
};

