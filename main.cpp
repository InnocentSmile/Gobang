#include<graphics.h>//引用ege库文件

PIMAGE img[4];//创建图片空间
int map[15][15]={0};//棋盘数组
int nowplayer = 1; //当前落子者   1为黑棋，2为白棋
int winner = 0;  //胜利者  1为黑棋胜利，2为白棋胜利
int gameState = 0;  //游戏状态  0为开始界面，1为棋盘界面

/*
	功能：
		在指定位置落子
	参数：
		x,y：要落子的位置
	返回值：
		1：落子成功
		0：落子失败
*/
int GoChess(int x,int y,int nowplayer)
{
	if (x > 14 || x < 0 || y>14 || y < 0)
		return 0;
	if (map[x][y] != 0)
		return 0;
	map[x][y] = nowplayer;

	PlaySound(L"1.wav", NULL, SND_FILENAME | SND_ASYNC);//落子音效
	return 1;
}

/*
	功能：
		加载游戏图片
*/
void LoadGameRes()
{

	img[0] = newimage();//初始化
	img[1] = newimage();
	img[2] = newimage();
	img[3] = newimage();

	getimage_pngfile(img[0], "棋盘.png");//加载图片
	getimage_pngfile(img[1], "黑棋.png");
	getimage_pngfile(img[2], "白棋.png");
	getimage_pngfile(img[3], "start.png");
}

/*
	功能：
		清理游戏资源
*/
void UnloadGameRes()
{
	//清理游戏资源
	delimage(img[0]);
	delimage(img[1]);
	delimage(img[2]);
	delimage(img[3]);
}

/*
	功能：
		用于游戏下棋点击画面的贴图
*/
void View()
{
	switch (gameState)
	{
	case 0:
		putimage_withalpha(NULL, img[3], 0, 0);		//画初始界面
		break;
	case 1:
		putimage_withalpha(NULL, img[0], 0, 0);		//画棋盘
		//画棋子
		for (int x = 0; x < 15; x++)
		{
			for (int y = 0; y < 15; y++)
			{
				switch (map[x][y])
				{
				case 0:
					break;
				case 1:
					putimage_withalpha(NULL, img[1], 22 - 16 + x * 35, 22 - 16 + y * 35);//贴图到准确位置
					break;
				case 2:
					putimage_withalpha(NULL, img[2], 22 - 16 + x * 35, 22 - 16 + y * 35);
					break;
				default:
					break;
				}
			}
		}

		//画胜利画面
		if (winner == 1)
		{
			outtextxy(250, 250, L"黑棋胜利！");
			break;
		}
		else if (winner == 2)
		{
			outtextxy(250, 250, L"白棋胜利！");
		}
		break;
	}
	
}

/*
	功能：
		获取鼠标相对于棋盘中的坐标
	参数：
		tx,ty：获取到的坐标
	返回值：
		1：按下了鼠标左键，并且成功返回坐标
		0：没有按下鼠标左键
*/
int MouseEvent(int *tx,int *ty)
{
	int x, y;
	if (GetAsyncKeyState(VK_LBUTTON) == 0x8001I16)	//如果鼠标左键按下了
	{
		mousepos(&x, &y);		//把鼠标坐标位置赋值给xy
		*tx = (x + 17 - 22) / 35;
		*ty = (y + 17 - 22) / 35;
		return 1;
	}
	return 0;
}

/*
返回值：
	1：胜利
	0：失败
*/
int WinOrNot(int x, int y, int nowplayer)
{
	/*
	已知：
	1.落子地点x，y
	2.落子的颜色
	3.当前的棋盘情况map
	求：
	当nowplayer在x，y处落子后，是否连成五个子或五个子以上
	*/
	int num = 0;
	//向上判断
	for (int i = 1; i <= 4; i++)
	{
		if (y-i>=0 && map[x][y - i] == nowplayer)
			num++;
		else
			break;
	}
	//向下判断
	for (int i = 1; i <= 4; i++)
	{
		if (y+i<=14 && map[x][y + i] == nowplayer)
			num++;
		else
			break;
	}

	if (num >= 4){return 1;}
		
	num = 0;

	//向左判断
	for (int i = 1; i <= 4; i++)
	{
		if (x- i >= 0 && map[x-i][y] == nowplayer)
			num++;
		else
			break;
	}
	//向右判断
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
		//上左判断
		if (x - i >= 0 && y - i >= 0 && map[x - i][y - i] == nowplayer)
		{
			num++;
		}
		//下右判断
		if (x + i <= 14 && y - i <= 14 && map[x + i][y + i] == nowplayer)
		{
			num++;
		}
	}
	
	

	if (num >= 4){ return 1; }

	num = 0;


	
	for ( int   i = 1; i <= 4; i++)
	{
		if (x - i >= 0 && y + i <= 14 && map[x - i][y + i] == nowplayer)//下左判断
		{
			num++;
		}
		if (x + i <= 14 && y - i >= 0 && map[x + i][y - i] == nowplayer)//上右判断
		{
			num++;
		}
	}
	
	

	if (num >= 4){ return 1; }



	return 0;
}

/*
	功能：
		变为初始界面，并且清空棋盘数据
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
	功能：
		游戏的控制层，用于变换落子
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
			if (GoChess(x, y, nowplayer) == 1)		//如果落子成功
			{
				//胜利判断
				if (WinOrNot(x, y, nowplayer) == 1)
				{
					nowplayer == 1 ? winner = 1 : winner = 2; //MessageBox(NULL, L"白棋胜利", L"恭喜", MB_OK)
					PlaySound(L"2.wav", NULL, SND_FILENAME | SND_ASYNC);		//胜利音效
				}
				//变色
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

	setinitmode(INIT_ANIMATION);//这个函数用于设置初始化图形的选项和模式。
	initgraph(535, 535);//设置窗口大小
	setcaption("五子棋");//设置标题
	LoadGameRes();		//加载游戏图片

	//播放背景音乐
	//mciSendString(L"open bgm.mp3 alias back", NULL, 0, NULL);
	//mciSendString(L"play back ", NULL, 0, NULL);


	//游戏主循环 每秒循环30次
	for (; is_run(); delay_fps(30))
	{
		/*逻辑更新*/
		Controller();

		/*图像更新*/
		//cleardevice();
		View();		//画图
		
	}

	UnloadGameRes();//清理游戏资源
	//关闭图形界面
	ege::closegraph();
	return 0;
}