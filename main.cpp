#include<graphics.h>//����ege���ļ�

PIMAGE img[4];//����ͼƬ�ռ�
int map[15][15]={0};//��������
int nowplayer = 1; //��ǰ������   1Ϊ���壬2Ϊ����
int winner = 0;  //ʤ����  1Ϊ����ʤ����2Ϊ����ʤ��
int gameState = 0;  //��Ϸ״̬  0Ϊ��ʼ���棬1Ϊ���̽���

/*
	���ܣ�
		��ָ��λ������
	������
		x,y��Ҫ���ӵ�λ��
	����ֵ��
		1�����ӳɹ�
		0������ʧ��
*/
int GoChess(int x,int y,int nowplayer)
{
	if (x > 14 || x < 0 || y>14 || y < 0)
		return 0;
	if (map[x][y] != 0)
		return 0;
	map[x][y] = nowplayer;

	PlaySound(L"1.wav", NULL, SND_FILENAME | SND_ASYNC);//������Ч
	return 1;
}

/*
	���ܣ�
		������ϷͼƬ
*/
void LoadGameRes()
{

	img[0] = newimage();//��ʼ��
	img[1] = newimage();
	img[2] = newimage();
	img[3] = newimage();

	getimage_pngfile(img[0], "����.png");//����ͼƬ
	getimage_pngfile(img[1], "����.png");
	getimage_pngfile(img[2], "����.png");
	getimage_pngfile(img[3], "start.png");
}

/*
	���ܣ�
		������Ϸ��Դ
*/
void UnloadGameRes()
{
	//������Ϸ��Դ
	delimage(img[0]);
	delimage(img[1]);
	delimage(img[2]);
	delimage(img[3]);
}

/*
	���ܣ�
		������Ϸ�������������ͼ
*/
void View()
{
	switch (gameState)
	{
	case 0:
		putimage_withalpha(NULL, img[3], 0, 0);		//����ʼ����
		break;
	case 1:
		putimage_withalpha(NULL, img[0], 0, 0);		//������
		//������
		for (int x = 0; x < 15; x++)
		{
			for (int y = 0; y < 15; y++)
			{
				switch (map[x][y])
				{
				case 0:
					break;
				case 1:
					putimage_withalpha(NULL, img[1], 22 - 16 + x * 35, 22 - 16 + y * 35);//��ͼ��׼ȷλ��
					break;
				case 2:
					putimage_withalpha(NULL, img[2], 22 - 16 + x * 35, 22 - 16 + y * 35);
					break;
				default:
					break;
				}
			}
		}

		//��ʤ������
		if (winner == 1)
		{
			outtextxy(250, 250, L"����ʤ����");
			break;
		}
		else if (winner == 2)
		{
			outtextxy(250, 250, L"����ʤ����");
		}
		break;
	}
	
}

/*
	���ܣ�
		��ȡ�������������е�����
	������
		tx,ty����ȡ��������
	����ֵ��
		1�������������������ҳɹ���������
		0��û�а���������
*/
int MouseEvent(int *tx,int *ty)
{
	int x, y;
	if (GetAsyncKeyState(VK_LBUTTON) == 0x8001I16)	//���������������
	{
		mousepos(&x, &y);		//���������λ�ø�ֵ��xy
		*tx = (x + 17 - 22) / 35;
		*ty = (y + 17 - 22) / 35;
		return 1;
	}
	return 0;
}

/*
����ֵ��
	1��ʤ��
	0��ʧ��
*/
int WinOrNot(int x, int y, int nowplayer)
{
	/*
	��֪��
	1.���ӵص�x��y
	2.���ӵ���ɫ
	3.��ǰ���������map
	��
	��nowplayer��x��y�����Ӻ��Ƿ���������ӻ����������
	*/
	int num = 0;
	//�����ж�
	for (int i = 1; i <= 4; i++)
	{
		if (y-i>=0 && map[x][y - i] == nowplayer)
			num++;
		else
			break;
	}
	//�����ж�
	for (int i = 1; i <= 4; i++)
	{
		if (y+i<=14 && map[x][y + i] == nowplayer)
			num++;
		else
			break;
	}

	if (num >= 4){return 1;}
		
	num = 0;

	//�����ж�
	for (int i = 1; i <= 4; i++)
	{
		if (x- i >= 0 && map[x-i][y] == nowplayer)
			num++;
		else
			break;
	}
	//�����ж�
	for (int i = 1; i <= 4; i++)
	{
		if (x + i <= 14 && map[x + i][y] == nowplayer)
			num++;
		else
			break;
	}

	if (num >= 4){ return 1; }

	num = 0;


	

	for (int i = 1; i <= 4; i++)
	{
		//�����ж�
		if (x - i >= 0 && y - i >= 0 && map[x - i][y - i] == nowplayer)
		{
			num++;
		}
		//�����ж�
		if (x + i <= 14 && y - i <= 14 && map[x + i][y + i] == nowplayer)
		{
			num++;
		}
	}
	
	

	if (num >= 4){ return 1; }

	num = 0;


	
	for ( int   i = 1; i <= 4; i++)
	{
		if (x - i >= 0 && y + i <= 14 && map[x - i][y + i] == nowplayer)//�����ж�
		{
			num++;
		}
		if (x + i <= 14 && y - i >= 0 && map[x + i][y - i] == nowplayer)//�����ж�
		{
			num++;
		}
	}
	
	

	if (num >= 4){ return 1; }



	return 0;
}

/*
	���ܣ�
		��Ϊ��ʼ���棬���������������
*/
void ReStart()
{
	//gameState = 0;
	winner = 0;
	nowplayer = 1;
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			map[x][y] = 0;
		}
	}
	
}
/*
	���ܣ�
		��Ϸ�Ŀ��Ʋ㣬���ڱ任����
*/
void Controller()
{
	switch (gameState)
	{
	case 0:
		if (GetAsyncKeyState(VK_RBUTTON) == 0x8001I16)
			gameState = 1;
		break;
	    case 1:
		
		if (winner != 0 && GetAsyncKeyState(VK_LBUTTON) == 0x8001I16)//
		{
            ReStart();
			break;
		}
	

		int x, y;
		if (MouseEvent(&x, &y) == 1)		
		{
			if (GoChess(x, y, nowplayer) == 1)		//������ӳɹ�
			{
				//ʤ���ж�
				if (WinOrNot(x, y, nowplayer) == 1)
				{
					nowplayer == 1 ? winner = 1 : winner = 2; //MessageBox(NULL, L"����ʤ��", L"��ϲ", MB_OK)
					PlaySound(L"2.wav", NULL, SND_FILENAME | SND_ASYNC);		//ʤ����Ч
				}
				//��ɫ
				if (nowplayer == 1)
					nowplayer = 2;
				else
					nowplayer = 1;
			}
		}
		break;
	}
	
	//MessageBox(getHWnd(), L"abc", L"123", MB_OK);
}


int main()
{

	setinitmode(INIT_ANIMATION);//��������������ó�ʼ��ͼ�ε�ѡ���ģʽ��
	initgraph(535, 535);//���ô��ڴ�С
	setcaption("������");//���ñ���
	LoadGameRes();		//������ϷͼƬ

	//���ű�������
	//mciSendString(L"open bgm.mp3 alias back", NULL, 0, NULL);
	//mciSendString(L"play back ", NULL, 0, NULL);


	//��Ϸ��ѭ�� ÿ��ѭ��30��
	for (; is_run(); delay_fps(30))
	{
		/*�߼�����*/
		Controller();

		/*ͼ�����*/
		//cleardevice();
		View();		//��ͼ
		
	}

	UnloadGameRes();//������Ϸ��Դ
	//�ر�ͼ�ν���
	ege::closegraph();
	return 0;
}