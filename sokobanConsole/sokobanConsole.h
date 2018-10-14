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

//������ �Է¹޾Ƽ� ������
void move(mobj *obj, int dx, int dy);
//������ �� �ִ��� üũ
bool canMove(mobj *obj, int dx, int dy);



