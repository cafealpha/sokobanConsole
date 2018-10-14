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

//��ũ�帮��Ʈ ����
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
//��ǥ��ġ�� ���ϴ� ������Ʈ�� �ִ��� ã���ִ� �Լ�
mobj* findObjectAtPos(node* head, pos Pos);

node* boxList;



//�ʵ����Ϳ��� ���� ������ ��
int *map;
//ȭ�鿡 ǥ�õǴ� ��
int *dMap;
//�÷��̾� ������
mobj *player;
//�������� ������(����)
stageData stage1;

int main();

void init();
void update();
void render();
void drawMap();
void drawPlayer();
void release();

void updateGameMap();

//������ �Է¹޾Ƽ� ������
void move(mobj *obj, int dx, int dy);
//������ �� �ִ��� üũ
bool canMove(mobj *obj, int dx, int dy);

//��ǥ�� �Է¹޾� �迭�ε����� ��ȯ�ϴ� �Լ�
int calcPosToIndex(int x, int y);
pos indexToPos(int index);
