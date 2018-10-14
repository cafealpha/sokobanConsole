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

struct pos
{
	int x;
	int y;
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
//좌표위치에 원하는 오브젝트가 있는지 찾아주는 함수
mobj* findObjectAtPos(node* head, pos Pos);

node* boxList;



//맵데이터에서 맵을 추출한 맵
int *map;
//화면에 표시되는 맵
int *dMap;
//플레이어 데이터
mobj *player;
//스테이지 데이터(샘플)
stageData stage1;

int main();

void init();
void update();
void render();
void drawMap();
void drawPlayer();
void release();

void updateGameMap();

//방향을 입력받아서 움직임
void move(mobj *obj, int dx, int dy);
//움직일 수 있는지 체크
bool canMove(mobj *obj, int dx, int dy);

//좌표를 입력받아 배열인덱스를 반환하는 함수
int calcPosToIndex(int x, int y);
pos indexToPos(int index);
