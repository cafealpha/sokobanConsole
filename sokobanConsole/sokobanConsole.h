#pragma once

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

//링크드리스트 구현
struct node
{
	mobj *item;
	struct node *next;
};

node* createList();
node* createNode(mobj *item);
void deleteList(node *head);
void addNode(node *head, node *item);
void printList(node *head);


//맵데이터에서 맵을 추출한 맵
int *map;
//화면에 표시되는 맵
int *dMap;
//플레이어 데이터
mobj *player;


stageData stage1;



int main();

void init();
void update();
void render();
void drawMap();
void drawPlayer();

