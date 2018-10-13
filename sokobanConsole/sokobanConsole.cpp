// sokobanConsole.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
//소코반 게임

#include "pch.h"
#include <iostream>
#include "sokobanConsole.h"

using namespace std;

enum mapObj {
	E_WALL,
	E_SPACE,
	E_BOX,
	E_GOAL,
	E_PLAYER,
};
struct mobj
{
	mapObj type;
	int x, y;
	bool status;
};

struct stageData
{
	char *mapData;
	int mapWidth;
	int mapHeight;
};

int *map;
mobj *player;


stageData stage1;


int main()
{
	init();
	for (int i = 0; stage1.mapData[i] != '\0'; i++)
		cout << stage1.mapData[i];

	render();
	/*while (true)
	{
		update();
		render();
	}*/

}

void init()
{
	char s1[] = "\
########\n\
# .. p #\n\
#      #\n\
# oo   #\n\
#      #\n\
########\n\
";

	//맵데이터 입력을 위해 동적할당
	stage1.mapData = (char*)malloc(strlen(s1) + 1);
	strcpy_s(stage1.mapData, strlen(s1) +1, s1);
	stage1.mapWidth = 8;
	stage1.mapHeight = 6; 
	
	//cout << sizeof(stage1.mapData);
	map = (int*)malloc(stage1.mapWidth* stage1.mapHeight);

	int mapCount = 0;
	//맵데이터를 읽어 초기 게임 세팅을 한다.
	for (int i = 0; stage1.mapData[i] != '\0'; i++)
	{
		//cout << stage1[i];
		switch (stage1.mapData[i])
		{
			case '#':
			{
				map[mapCount] = E_WALL;
				mapCount++;
				break;
			}
			case ' ':
			{
				map[mapCount] = E_SPACE;
				mapCount++;
				break;
			}
			case 'p':		//플레이어가 공백공간 위에 있을때
			{
				player = (mobj*)malloc(sizeof(struct mobj));
				player->type = E_PLAYER;
				player->x = i % (stage1.mapWidth+1);
				player->y = i / (stage1.mapWidth+1);
				cout << "ipos->" << i << endl;
				cout << "x->" << player->x << endl;
				cout << "y->" << player->y << endl;

				map[mapCount] = E_SPACE;
				mapCount++;
				break;
			}
			case 'P':		//플레이어가 골 위에 있을때
			{
				map[mapCount] = E_GOAL;
				mapCount++;
				break;
			}
			case 'o':		//박스가 공백공간 위에 있을때
			{
				map[mapCount] = E_SPACE;
				mapCount++;
				break;
			}
			case 'O':		//박스가 골 위에 있을때 
			{
				map[mapCount] = E_GOAL;
				mapCount++;
				break;
			}
			case '.':		//골
			{
				map[mapCount] = E_GOAL;
				mapCount++;
				break;
			}


		}
	}
	cout << mapCount << endl;
}

void update()
{
}
void render()
{
	for (int i = 0; i < stage1.mapHeight; i++)
	{
		for (int j = 0; j < stage1.mapWidth; j++)
		{
			switch (map[(i*stage1.mapWidth) + j])
			{
				case E_WALL:
				{
					cout << '#';
					break;
				}
				case E_GOAL:
				{
					cout << '.';
					break;
				}
				case E_SPACE:
				{
					cout << ' ';
					break;
				}
			}
		}
		cout << endl;
	}

}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
