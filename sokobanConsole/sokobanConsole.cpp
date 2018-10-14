// sokobanConsole.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
//소코반 게임

#include "pch.h"
#include <iostream>
#include "sokobanConsole.h"

node* testList;

node* createList()
{
	node* List = (node*)malloc(sizeof(node));
	List->item = NULL;
	List->next = NULL;
	return List;
}

node* createNode(mobj * item)
{
	node *Node = (node*)malloc(sizeof(node));
	Node->item = item;
	Node->next = NULL;
	return Node;
}

void deleteList(node * head)
{
	node* temp = head;
	while (temp->next != NULL)
	{
		node *t = temp;
		temp = temp->next;
		delete(t);
	}
	free(temp);
}

void addNode(node * head, node * item)
{
	node* temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = item;
}

void printList(node * head)
{
	node* temp = head->next;
	while (temp != NULL)
	{
		cout << temp->item->x << endl;
		temp = temp->next;
	}
}

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
	deleteList(testList);
	free(player);
	free(stage1.mapData);
	free(map);
	free(dMap);
	
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

	testList = createList();


	//맵데이터 입력을 위해 동적할당
	stage1.mapData = (char*)malloc(strlen(s1) + sizeof(char));
	strcpy_s(stage1.mapData, strlen(s1) +sizeof(char), s1);
	stage1.mapWidth = 8;
	stage1.mapHeight = 6; 
	
	//cout << sizeof(stage1.mapData);
	map = (int*)malloc(sizeof(int)*stage1.mapWidth* stage1.mapHeight);
	dMap = (int*)malloc(sizeof(int)*stage1.mapWidth* stage1.mapHeight);

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
				dMap[mapCount] = E_WALL;
				mapCount++;
				break;
			}
			case ' ':
			{
				map[mapCount] = E_SPACE;
				dMap[mapCount] = E_SPACE;
				mapCount++;
				break;
			}
			case 'p':		//플레이어가 공백공간 위에 있을때
			{
				player = (mobj*)malloc(sizeof(mobj));
				player->type = E_PLAYER;
				player->x = i % (stage1.mapWidth+1);
				player->y = i / (stage1.mapWidth+1);
				cout << "ipos->" << i << endl;
				cout << "x->" << player->x << endl;
				cout << "y->" << player->y << endl;

				map[mapCount] = E_SPACE;
				dMap[mapCount] = E_SPACE;
				mapCount++;
				break;
			}
			case 'P':		//플레이어가 골 위에 있을때
			{
				map[mapCount] = E_GOAL;
				dMap[mapCount] = E_GOAL;
				mapCount++;
				break;
			}
			case 'o':		//박스가 공백공간 위에 있을때
			{
				map[mapCount] = E_SPACE;
				dMap[mapCount] = E_BOX;
				mobj *box = (mobj*)malloc(sizeof(mobj));
				box->type = E_BOX;
				box->x = i % (stage1.mapWidth + 1);
				box->y = i / (stage1.mapWidth + 1);

				node *Node = createNode(box);
				addNode(testList, Node);

				mapCount++;
				break;
			}
			case 'O':		//박스가 골 위에 있을때 
			{
				map[mapCount] = E_GOAL;
				dMap[mapCount] = E_BOX;
				mapCount++;
				break;
			}
			case '.':		//골
			{
				map[mapCount] = E_GOAL;
				dMap[mapCount] = E_GOAL;
				mapCount++;
				break;
			}
		}
	}


	cout << mapCount << endl;
	printList(testList);
}

void update()
{



}
void render()
{
	drawMap();
	//drawPlayer();
}

void drawMap()
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

void drawPlayer()
{

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
