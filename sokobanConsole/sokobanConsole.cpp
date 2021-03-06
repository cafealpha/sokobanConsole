// sokobanConsole.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
//소코반 게임

#include "pch.h"
#include <iostream>
#include "sokobanConsole.h"


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
		cout << "X: " << temp->item->x << endl;
		cout << "Y: " << temp->item->y << endl;
		temp = temp->next;
	}
}

int main()
{
	init();

	//for (int i = 0; stage1.mapData[i] != '\0'; i++)
	//	cout << stage1.mapData[i];
	while (true)
	{
		if (judge())
		{
			cout << "게임 클리어" << endl;
			break;
		}
		update();
		render();
	}
	release();
	
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

	boxList = createList();

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
				//개행문자때문에 폭이 1 추가됨.
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
				addNode(boxList, Node);

				mapCount++;
				break;
			}
			case 'O':		//박스가 골 위에 있을때 
			{
				map[mapCount] = E_GOAL;
				dMap[mapCount] = E_BOX;
				
				mobj *box = (mobj*)malloc(sizeof(mobj));
				box->type = E_BOX;
				box->x = i % (stage1.mapWidth + 1);
				box->y = i / (stage1.mapWidth + 1);

				node *Node = createNode(box);
				addNode(boxList, Node);
				
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
	printList(boxList);
}

void update()
{
	int dx = 0;
	int dy = 0;
	switch (getchar())
	{
		case 'a':
		{
			dx = -1;
			break;
		}
		case 'd':
		{
			dx = 1;
			break;
		}
		case 'w':
		{
			dy = -1;
			break;
		}
		case 's':
		{
			dy = 1;
			break;
		}
	}
	move(player, dx, dy);
	//이동된 데이터를 토대로 동적 맵을 다시 그린다.
	updateGameMap();
}
void render()
{

	drawMap();

	node *temp = boxList->next;
	while (temp != NULL)
	{
		cout << "x: " << temp->item->x << endl;
		cout << "y: " << temp->item->y << endl;
		temp = temp->next;
	}
	//drawPlayer();
}

void drawMap()
{
	for (int i = 0; i < stage1.mapHeight; i++)
	{
		for (int j = 0; j < stage1.mapWidth; j++)
		{
			switch (dMap[(i*stage1.mapWidth) + j])
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
			case E_BOX:
			{
				if(map[(i*stage1.mapWidth) + j] == E_GOAL)
					cout << 'O';
				else cout << 'o';
				break;
			}
			case E_PLAYER:
				if (map[(i*stage1.mapWidth) + j] == E_GOAL)
					cout << 'P';
				else cout << 'p';
				break;
			}
		}
		cout << endl;
	}
}

void drawPlayer()
{

}

void release()
{
	deleteList(boxList);
	free(player);
	free(stage1.mapData);
	free(map);
	free(dMap);

}

void updateGameMap()
{
	//free(dMap);
	//dMap = (int*)malloc(sizeof(int)*stage1.mapWidth* stage1.mapHeight);
	memcpy(dMap, map, sizeof(int)*stage1.mapWidth* stage1.mapHeight);

	node* temp = boxList->next;
	while (temp != NULL)
	{
		dMap[calcPosToIndex(temp->item->x, temp->item->y)] = E_BOX;
		temp = temp->next;
	}
	dMap[calcPosToIndex(player->x, player->y)] = E_PLAYER;
}

bool move(mobj *obj, int dx, int dy)
{
	//이동 가능한지 확인
	if (canMove(obj, dx, dy))
	{
		//이동 가능하면 이동
		//전방에 블럭이 존재하는지 확인하고 이동시킴
		pos boxPos = { obj->x + dx, obj->y + dy };
		mobj* box = findObjectAtPos(boxList, boxPos);
		if (box != nullptr)
		{
			if (!move(box, dx, dy))
				return false;
		}

		obj->x = obj->x + dx;
		obj->y = obj->y + dy;
		return true;
	}
	return false;
}


bool canMove(mobj *obj, int dx, int dy)
{
	int tx = obj->x + dx;
	int ty = obj->y + dy;
	//인덱스 변환
	int di = calcPosToIndex(tx, ty);
	
	//내가 박스인 경우 전방이 공백이 아니면 이동 불가능하다.
	if (obj->type == E_BOX)
	{
		if (dMap[di] == E_SPACE || dMap[di] == E_GOAL)
			return true;
		else return false;
	}

	//전방에 위치한게 박스인 경우 이동가능 체크
	if (dMap[di] == E_BOX)
	{
		//일단 해당 위치의 박스부터 찾음
		mobj* box = findObjectAtPos(boxList, indexToPos(di));
		if (box != nullptr)
		{
			//박스면 이동하려는 전방에 뭐가 있는지 확인함.
			if (canMove(box, dx, dy))
			{
				return true;
			}
			else return false;
		}
	}

	//옮기려는 지점이 공백이면 이동 가능하고 벽이면 이동 불가
	if (dMap[di] == E_SPACE)
		return true;
	if (dMap[di] == E_WALL)
		return false;
}

bool judge()
{
	node* temp = boxList->next;
	while (temp != NULL)
	{
		if (map[(temp->item->y*stage1.mapWidth) + temp->item->x] != E_GOAL) return false;
		temp = temp->next;
	}

	return true;
}

int calcPosToIndex(int x, int y)
{
	/*
	2차원 좌표를 1차원 배열좌표로 바꾸려면
	2차원 배열의 가로폭이 넘을 경우 y값이 한줄씩 늘어가는 형태
	ex)
	1234
	4567

	인 경우 가로폭4이므로.
	6의 위치 (2,1)을 1차원 배열 인덱스로 변환하기 위해서는
	(y값 1) * (가로폭 4) + (x값 2) = 6이 된다.

	*/
	return stage1.mapWidth*y + x ;
}

pos indexToPos(int index)
{
	/*
	index를 pos로 바꾸기 위해서는
	인덱스를 x폭으로 나누면 y값이 나옴.
	x폭으로 나머지 연산을 하면 값이 나온다.
	*/

	pos Pos;
	Pos.x = index/stage1.mapWidth;
	Pos.y = index%stage1.mapWidth;
	return Pos;
}
mobj * findObjectAtPos(node * head, pos Pos)
{
	node* temp = head->next;
	while (temp != NULL)
	{
		if (temp->item->x == Pos.x && temp->item->y == Pos.y)
		{
			return temp->item;
		}
		temp = temp->next;
	}
	return nullptr;
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
