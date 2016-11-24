#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#define  TRANSITION_DURATION (0.5f)

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;


CCSize vSize;				//화면령역
CCPoint origin;				//원점
float scaleX, scaleY;			//화면비
int tmprow, tmpcol;			//림시 행, 렬
const int RED = 1, BLUE = 2, GREEN = 3, CYAN = 4, RAINBOW = 8, EXPLODE = 9, MINE = 10;
int PlayGame::pantemp[][14][19] =			//회전모양
{
	{
		{-1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1},
		{-1, -1, -1, 0, 0, 0, 0, 0, -3, -3, 0, 0, 0, 0, 0, -1, -1, -1, -1},
		{-1, -1, -1, 0, 0, 0, 0, 0, -3, -3, -3, 0, 0, 0, 0, 0, -1, -1, -1},
		{-1, -1, 0, 0, 0, 0, 0, 0, -3, -3, 0, 0, 0, 0, 0, 0, -1, -1, -1},
		{-1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1},
		{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1},
		{-1, 0, 0, -3, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, -3, 0, 0, -1},
		{0, 0, -3, -3, -3, 0, 0, 0, 0, 0, 0, 0, 0, -3, -3, -3, 0, 0, -1},
		{-1, 0, 0, -3, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, -3, 0, 0, -1},
		{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1},
		{-1, -1, 0, 0, 0, 0, 0, 0, -3, -3, 0, 0, 0, 0, 0, 0, 0, -1, -1},
		{-1, -1, 0, 0, 0, 0, 0, -3, -3, -3, 0, 0, 0, 0, 0, 0, -1, -1, -1},
		{-1, -1, -1, 0, 0, 0, 0, 0, -3, -3, 0, 0, 0, 0, 0, 0, -1, -1, -1},
		{-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1}
	},
	{
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, 0, 0, 0, 0, -3, -3, 0, 0, 0, 0, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, -1, -1, -1, -1},
		{-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1},
		{-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1},
		{-1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1},
		{-1, -1, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, -1, -1},
		{-1, 0, -3, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, -3, 0, -1, -1},
		{-1, -1, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, -1, -1},
		{-1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1},
		{-1, -1, -1, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, -1, -1, -1},
		{-1, -1, -1, 0, 0, 0, 0, 0, -3, -3, 0, 0, 0, 0, 0, -1, -1, -1, -1},
		{-1, -1, -1, -1, 0, 0, 0, 0, -3, -3, -3, 0, 0, 0, 0, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
	},
	{
		{-1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, 0, 0, -3, -3, 0, 0, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, 0, 0, -3, -3, -3, 0, 0, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, 0, 0, 0, -3, -3, 0, 0, 0, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1},
		{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1},
		{-1, 0, 0, -3, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, -3, 0, 0, -1},
		{0, 0, -3, -3, -3, 0, 0, 0, 0, 0, 0, 0, 0, -3, -3, -3, 0, 0, -1},
		{-1, 0, 0, -3, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, -3, 0, 0, -1},
		{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1},
		{-1, -1, -1, -1, -1, 0, 0, 0, -3, -3, 0, 0, 0, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, 0, 0, -3, -3, -3, 0, 0, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, 0, 0, -3, -3, 0, 0, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1}
	}, 
	{
		{-1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, 0, 0, -3, -3, 0, 0, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, 0, 0, 0, 0, 0, -3, -3, -3, 0, 0, 0, 0, 0, -1, -1, -1},
		{-1, -1, 0, -3, 0, 0, 0, 0, -3, -3, 0, 0, 0, 0, -3, 0, -1, -1, -1},
		{-1, -1, 0, -3, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, -3, 0, -1, -1},
		{-1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1},
		{-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1},
		{-1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1},
		{-1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1},
		{-1, 0, -3, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, -3, 0, -1, -1},
		{-1, -1, 0, -3, 0, 0, 0, 0, -3, -3, 0, 0, 0, 0, 0, -3, 0, -1, -1},
		{-1, -1, 0, 0, 0, 0, 0, -3, -3, -3, 0, 0, 0, 0, 0, 0, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, 0, 0, -3, -3, 0, 0, 0, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1}
	}, 
	{
		{-1, -1, -1, -1, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, -1, -1, -1, -1},
		{-1, -1, -1, -3, 0, 0, 0, 0, -3, -3, 0, 0, 0, 0, -3, -1, -1, -1, -1},
		{-1, -1, -1, -3, 0, 0, 0, 0, -3, -3, -3, 0, 0, 0, 0, -3, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, 0, 0, -3, -3, 0, 0, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1},
		{-1, 0, 0, 0, 0, 0, 0, 0, -3, -3, 0, 0, 0, 0, 0, 0, 0, -1, -1},
		{-1, 0, 0, -3, -3, 0, 0, 0, 0, -3, 0, 0, 0, 0, -3, -3, 0, 0, -1},
		{0, 0, 0, -3, -3, 0, 0, 0, -3, -3, 0, 0, 0, -3, -3, 0, 0, 0, -1},
		{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
		{-1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, 0, 0, -3, -3, 0, 0, 0, -1, -1, -1, -1, -1, -1},
		{-1, -1, -3, 0, 0, 0, 0, -3, -3, -3, 0, 0, 0, 0, 0, -3, -1, -1, -1},
		{-1, -1, -1, -3, 0, 0, 0, 0, -3, -3, 0, 0, 0, 0, 0, -3, -1, -1, -1},
		{-1, -1, -1, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, -1, -1, -1, -1}
	},
	{
		{-1, -1, -1, -1, 0, 0, 0, -1, 0, 0, 0, -1, 0, 0, 0, -1, -1, -1, -1},
		{-1, -1, -1, 0, -3, -3, 0, 0, 0, 0, 0, 0, -3, -3, 0, -1, -1, -1, -1},
		{-1, -1, -1, 0, -3, -3, -3, 0, -1, 0, -1, 0, -3, -3, -3, 0, -1, -1, -1},
		{-1, -1, -1, 0, -3, -3, 0, -1, 0, 0, -1, 0, -3, -3, 0, -1, -1, -1, -1},
		{-1, -1, -1, -1, 0, 0, 0, -1, 0, -3, 0, -1, 0, 0, 0, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, 0, -3, -3, 0, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, 0, 0, 0, 0, -1, 0, -3, 0, -1, 0, 0, 0, 0, -1, -1, -1},
		{-1, -1, 0, -3, -3, -3, 0, -1, 0, 0, -1, 0, -3, -3, -3, 0, -1, -1, -1},
		{-1, -1, 0, -3, -3, -3, -3, 0, -1, 0, -1, 0, -3, -3, -3, -3, 0, -1, -1},
		{-1, 0, -3, -3, -3, -3, 0, -1, 0, 0, -1, 0, -3, -3, -3, -3, 0, -1, -1},
		{-1, -1, 0, -3, -3, -3, 0, -1, 0, -3, 0, -1, 0, -3, -3, -3, 0, -1, -1},
		{-1, -1, 0, 0, 0, 0, -1, 0, -3, -3, 0, -1, 0, 0, 0, 0, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, 0, 0, -3, -3, -3, 0, 0, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1}
	},
	{
		{-1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1},
		{-1, -1, -1, 0, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, 0, -1, -1, -1, -1},
		{-1, -1, -1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, -3, 0, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, -3, 0, -1, -1, -1},
		{-1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, -1, -1},
		{-1, 0, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, 0, -1, -1, -1},
		{-1, 0, -3,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1},
		{0, -3, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, 0, -3,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1},
		{-1, 0, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, 0, -1, -1, -1},
		{-1, -1, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, -3, 0, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, -3, 0, -1, -1, -1},
		{-1, -1, -1, 0, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, 0, -1, -1, -1},
		{-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1}
	}, 
	{
		{-1, -1, -1, -1, 0, -3, 0, -1, -1, -1, -1, -1, 0, -3, 0, -1, -1, -1, -1},
		{-1, -1, -1, 0, -3, -3, 0, -1, -1, -1, -1, 0, -3, -3, 0, -1, -1, -1, -1},
		{-1, -1, -1, 0, -3, 0, -3, 0, -1, -1, -1, 0, -3, 0, -3, 0, -1, -1, -1},
		{-1, -1, 0, -3, 0, 0, -3, 0, -1, -1, 0, -3, 0, 0, -3, 0, -1, -1, -1},
		{-1, -1, 0, -3, 0, -1, 0, -3, 0, -1, 0, -3, 0, -1, 0, -3, 0, -1, -1},
		{-1, 0, -3, 0, -1, -1, 0, -3, 0, 0, -3, 0, -1, -1, 0, -3, 0, -1, -1},
		{-1, 0, 0, 0, -1, -1, -1, 0, -3, -3, -3, 0, -1, -1, -1, 0, -3, 0, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -3, -3, -1, -1,-1, -1, -1, -1, -1, -1, -1},
		{-1, 0, -3, 0, -1, -1, -1, 0, -3, -3, -3, 0, -1, -1, -1, 0, -3, 0, -1},
		{-1, 0, -3, 0, -1, -1, 0, -3, 0, 0, -3, 0, -1, -1, 0, -3, 0, -1, -1},
		{-1, -1, 0, -3, 0, -1, 0, -3, 0, -1, 0, -3, 0, -1, 0, -3, 0, -1, -1},
		{-1, -1, 0, -3, 0, 0, -3, 0, -1, -1, 0, -3, 0, 0, -3, 0, -1, -1, -1},
		{-1, -1, -1, 0, -3, 0, -3, 0, -1, -1, -1, 0, -3, 0, -3, 0, -1, -1, -1},
		{-1, -1, -1, 0, -3, -3, 0, -1, -1, -1, -1, 0, -3, -3, 0, -1, -1, -1, -1}
	}
};
/*
{
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	}
};*/
vector<Vertex> path;						//경로
vector<Vertex> eatArr;						//먹은 돌무리
int pathpan[14][19];										//경로계산판
bool success;										//경로찾기 성공
int weight;									//무게
bool lock;									//계산중열쇠
bool started;
bool gameover;					//게임끝
vector<Vertex> eating;
int maxEating;					//특수알을 만들수있는 개수4이상
CCParticleSun* mineExp[300];			//지뢰터치는 효과모임
Vertex mineVer[300];					//지뢰로 터칠 좌표모임
CCParticleSun* explodePtl;				//폭탄효과
int totalNum;							//전체없앤개수
int startTime;							//시작시간
int endTime;							//끝시간
bool continueGame;						//게임계속
bool pushed;							//클릭

int posxy[2];							//위치에 따르는 row, col 값

CCTransitionScene* createTransitionL(float, CCScene*);
CCTransitionScene* createTransitionR(float, CCScene*);

		////////////////////////////////   MainMenu   //////////////////////////////////////////

CCScene* MainMenu::scene()
{
    CCScene *scene = CCScene::create();
    MainMenu *layer = MainMenu::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenu::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    vSize = CCDirector::sharedDirector()->getVisibleSize();
    origin = CCDirector::sharedDirector()->getVisibleOrigin();
	scaleX = vSize.width/800;
	scaleY = vSize.height/600;
	
	CCMenuItemImage *playgame = CCMenuItemImage::create("playgame.png", "playgame_d.png", this, menu_selector(MainMenu::onPlayGame));    
	playgame->setPosition(ccp(origin.x + vSize.width/2 , origin.y+vSize.height*3/4));
	playgame->setScaleX(scaleX);
	playgame->setScaleY(scaleY);

	CCMenuItemImage *top7 = CCMenuItemImage::create("top7.png", "top7_d.png", this, menu_selector(MainMenu::onTop7));    
	top7->setPosition(ccp(origin.x + vSize.width/2 , origin.y+vSize.height*4/7));
	top7->setScaleX(scaleX);
	top7->setScaleY(scaleY);

	CCMenuItemImage *help = CCMenuItemImage::create("help.png", "help_d.png", this, menu_selector(MainMenu::onHelp));    
	help->setPosition(ccp(origin.x + vSize.width/2 , origin.y+vSize.height*3/7));
	help->setScaleX(scaleX);
	help->setScaleY(scaleY);

    CCMenuItemImage *exitgame = CCMenuItemImage::create("exitgame.png", "exitgame_d.png", this, menu_selector(MainMenu::onExitGame));    
	exitgame->setPosition(ccp(origin.x + vSize.width/2, origin.y+vSize.height*2/7));
	exitgame->setScaleX(scaleX);
	exitgame->setScaleY(scaleY);


    CCMenu* pMenu = CCMenu::create(playgame, top7, help, exitgame, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    CCSprite* pSprite = CCSprite::create("background.png");
	pSprite->setPosition(ccp(vSize.width/2 + origin.x, vSize.height/2 + origin.y));
	pSprite->setScaleX(scaleX);
	pSprite->setScaleY(scaleY);
    this->addChild(pSprite, 0);

	setTouchEnabled(true);
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("menuback.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("gameback3.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("btn_click.wav");				//used
	SimpleAudioEngine::sharedEngine()->preloadEffect("unselect.wav");				//used
	SimpleAudioEngine::sharedEngine()->preloadEffect("bonk.wav");					//used
	SimpleAudioEngine::sharedEngine()->preloadEffect("bowl.wav");					//used
	SimpleAudioEngine::sharedEngine()->preloadEffect("glassbreaks.wav");			//used
	SimpleAudioEngine::sharedEngine()->preloadEffect("pop.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("select.wav");					//used
	SimpleAudioEngine::sharedEngine()->preloadEffect("shot.wav");					//used
	SimpleAudioEngine::sharedEngine()->preloadEffect("takeoff.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("waterdrop2.wav");				//used

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("menuback.mp3");
    
    return true;
}

void MainMenu::onHelp(CCObject* pSender)		//helpmenu
{
	SimpleAudioEngine::sharedEngine()->playEffect("btn_click.wav");
	CCScene* s = new CCScene();
	CCLayer* g = new HelpLayer();
	g->init();
	s->addChild(g);
	CCScene* pScene = createTransitionR(TRANSITION_DURATION, s);
	s->release();
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

void MainMenu::onTop7(CCObject* pSender)		//top7layer
{
	SimpleAudioEngine::sharedEngine()->playEffect("btn_click.wav");
	CCScene* s = new CCScene();
	CCLayer* g = new Top7Layer();
	g->init();
	s->addChild(g);
	CCScene* pScene = createTransitionR(TRANSITION_DURATION, s);
	s->release();
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

void MainMenu::onPlayGame(CCObject* pSender)		//playgame
{
	SimpleAudioEngine::sharedEngine()->playEffect("btn_click.wav");
	openGame = CCSprite::create("gamestart.png");
	openGame->setPosition(ccp(origin.x+vSize.width/2, origin.y+vSize.height/2));
	openGame->setScaleX(0.2f*scaleX);
	openGame->setScaleY(0.2f*scaleY);
	this->addChild(openGame, 4);

	CCActionInterval* openAction1 = CCScaleTo::create(0.2f, 1.0f*scaleX, 1.0f*scaleY);
	openGame->runAction(CCSequence::create(openAction1, NULL));
	this->schedule(schedule_selector(MainMenu::checkScale));
}

void MainMenu::checkScale(float delayTime)
{
	if(openGame->getScaleX()>0.95f*scaleX && openGame->getScaleY()>0.98f*scaleY)	//끝?
	{
		continueMenu = CCMenuItemImage::create("continuegame.png", "continuegame_d.png", this, menu_selector(MainMenu::onContinue));
		continueMenu->setPosition(ccp(origin.x+vSize.width*0.5f, origin.y+vSize.height*0.4f));
		continueMenu->setScaleX(scaleX);
		continueMenu->setScaleY(scaleY);

		newMenu = CCMenuItemImage::create("startnewgame.png", "startnewgame_d.png", this, menu_selector(MainMenu::onNew));
		newMenu->setPosition(ccp(origin.x+vSize.width*0.5f, origin.y+vSize.height*0.27f));
		newMenu->setScaleX(scaleX);
		newMenu->setScaleY(scaleY);

		closeMenu = CCMenuItemImage::create("cancel.png", "cancel_d.png", this, menu_selector(MainMenu::onCancel));
		closeMenu->setPosition(ccp(origin.x+vSize.width*0.7f, origin.y+vSize.height*0.16f));
		closeMenu->setScaleX(scaleX);
		closeMenu->setScaleY(scaleY);

		pm = CCMenu::create(continueMenu, newMenu, closeMenu, NULL);
		pm->setPosition(CCPointZero);
		this->addChild(pm, 5);

		int lev = CCUserDefault::sharedUserDefault()->getIntegerForKey("arabesque_level", 0);
		level = CCLabelTTF::create(CCString::createWithFormat("%d", lev+1)->getCString(), "Maker Felt", 22);
		level->setPosition(ccp(origin.x+vSize.width*0.56f, origin.y+vSize.height*0.54f));
		level->setScaleX(scaleX);
		level->setScaleY(scaleY);
		this->addChild(level, 5);

		this->unschedule(schedule_selector(MainMenu::checkScale));
	}
}

void MainMenu::onCancel(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("btn_click.wav");
	if(pm != NULL)
	{
		this->removeChild(pm);
		pm = NULL;
	}
	if(level != NULL)
	{
		this->removeChild(level);
		level = NULL;
	}
	if(openGame != NULL)
	{
		this->removeChild(openGame);
		openGame = NULL;
	}
}

void MainMenu::onContinue(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("btn_click.wav");
	continueGame = true;
	this->openPlayGame();
}

void MainMenu::onNew(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("btn_click.wav");
	continueGame = false;
	CCUserDefault::sharedUserDefault()->setIntegerForKey("arabesque_level", 0);
	this->openPlayGame();
}

void MainMenu::openPlayGame()
{
	SimpleAudioEngine::sharedEngine()->playEffect("btn_click.wav");
	CCScene* s = new CCScene();
	CCLayer* g = new PlayGame();
	g->init();
	s->addChild(g);
	CCScene* pScene = createTransitionR(TRANSITION_DURATION, s);
	s->release();
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

void MainMenu::onExitGame(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("btn_click.wav");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

CCTransitionScene* createTransitionL(float t, CCScene* s)
{
	CCDirector::sharedDirector()->setDepthTest(false);
	return CCTransitionSlideInL::create(t, s);
}

CCTransitionScene* createTransitionR(float t, CCScene* s)
{
	CCDirector::sharedDirector()->setDepthTest(false);
	return CCTransitionSlideInR::create(t, s);
}

			/////////////////////////////////   PlayGame   /////////////////////////////////////////

CCScene* PlayGame::scene()
{
	CCScene* scene = CCScene::create();
	PlayGame* layer = PlayGame::create();
	scene->addChild(layer);
	return scene;
}

bool PlayGame::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	started = false;

	CCSprite* background = CCSprite::create("playgame_back.png");
	background->setPosition(ccp(origin.x+background->getContentSize().width/2*scaleX, origin.y+background->getContentSize().height/2*scaleY));
	background->setScaleX(scaleX);
	background->setScaleY(scaleY);
	this->addChild(background, 0);

	CCMenuItemImage* mainmenuitem = CCMenuItemImage::create("mainmenu.png", "mainmenu_d.png", this, menu_selector(PlayGame::onMainmenu));
	mainmenuitem->setPosition(ccp(origin.x+vSize.width*9/10, origin.y+vSize.height/16));
	mainmenuitem->setScaleX(scaleX);
	mainmenuitem->setScaleY(scaleY);

	CCMenu* menu = CCMenu::create(mainmenuitem, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu, 1);

	setTouchEnabled(true);

	this->seleditem = 0;				//선택된객체 없음
	lock = false;						//열쇠초기화
	gameover = false;
	this->score = 0;
	totalNum = 0;

	this->initGame();
	this->placeGame();
	this->schedule(schedule_selector(PlayGame::realCheck), 0.1f);
	for(int i=0; i<300; i++)
		mineExp[i] = NULL;
	started = true;
	startTime = time(NULL);

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gameback3.mp3");
	return true;
}

void PlayGame::realCheck(float delayTime)
{
	this->scorelab->setString(CCString::createWithFormat("%d", this->score)->getCString());
	bool life = false;
	int tgrtotal = 0;
	for(int i=0; i<sizeof(PlayGame::pantemp[0])/sizeof(int)/(sizeof(PlayGame::pantemp[0][0])/sizeof(int)); i++)
	{
		for(int j=0; j<sizeof(PlayGame::pantemp[0][0])/sizeof(int); j++)
		{
			if(this->tgrtls[i][j] != NULL)
				tgrtotal ++;
			if(this->gamepan[i][j]==RED || this->gamepan[i][j]==BLUE || this->gamepan[i][j]==GREEN || this->gamepan[i][j]==CYAN || 
				this->gamepan[i][j]==RAINBOW || this->gamepan[i][j]==EXPLODE || this->gamepan[i][j]==MINE)
				life = true;
		}
	}

	if(!life)				//목숨감소
	{
		this->lives --;
		if(this->lives>=0)			//목숨0일때 게임끝
		{
			for(int i=0; i<sizeof(PlayGame::pantemp[0])/sizeof(int)/(sizeof(PlayGame::pantemp[0][0])/sizeof(int)); i++)
			{
				bool f = false;
				for(int j=0; j<sizeof(PlayGame::pantemp[0][0])/sizeof(int); j++)
				{
					if(PlayGame::pantemp[this->level][i][j] != -1 && this->gamepan[i][j] == 0)
					{
						this->gamepan[i][j] = RED;
						this->span[i][j] = CCSprite::create("red.png");
						this->span[i][j]->setPosition(this->getPositionByij(i, j));
						this->span[i][j]->setScaleX(scaleX);
						this->span[i][j]->setScaleY(scaleY);
						this->addChild(this->span[i][j], 6);
						f = true;
						break;
					}
				}
				if(f)
					break;
			}
		}else
		{
			tgrtotal = 0;
		}		
	}
	this->liveslab->setString(CCString::createWithFormat("%d", this->lives)->getCString());
	
	if(!gameover && tgrtotal == 0)				//게임끝
	{
		endTime = time(NULL);
		gameover = true;
		if(life)
		{
			continueGame = true;
			this->level += 1;
			if(this->level > 7)
				this->level = 0;
			CCUserDefault::sharedUserDefault()->setIntegerForKey("arabesque_level", this->level);
		}else
			CCUserDefault::sharedUserDefault()->setIntegerForKey("arabesque_level", this->level);
		int score[7];
		for(int i=0; i<7; i++)								//점수보관
			score[i] = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("arabesque_score%d", i)->getCString(), 0);
		for(int i=0; i<7; i++)
		{
			for(int j=i; j<7; j++)
			{
				if(score[i]<score[j])
				{
					int tmp = score[i];
					score[i] = score[j];
					score[j] = tmp;
				}
			}
		}
		if(score[6]<this->score)
			CCUserDefault::sharedUserDefault()->setIntegerForKey("arabesque_score6", this->score);
		nextLevel = CCSprite::create("gameend.png");
		nextLevel->setPosition(ccp(origin.x+vSize.width/2, origin.y+vSize.height/2));
		nextLevel->setScaleX(0.1f*scaleX);
		nextLevel->setScaleY(0.1f*scaleY);
		this->addChild(nextLevel, 10);

		CCActionInterval* nextAction = CCScaleTo::create(0.8f, 1.0f*scaleX, 1.0f*scaleY);
		nextLevel->runAction(CCSequence::create(nextAction, NULL));
		this->schedule(schedule_selector(PlayGame::nextLev));
		this->unschedule(schedule_selector(PlayGame::realCheck));
	}
}

void PlayGame::nextLev(float delayTime)
{
	if(nextLevel->getScaleX() >=0.98f*scaleX && nextLevel->getScaleY() >= 0.98f*scaleY)
	{
		CCLabelTTF* scorelab1 = CCLabelTTF::create(CCString::createWithFormat("%d", this->score)->getCString(), "Marker Felt", 24);
		scorelab1->setPosition(ccp(origin.x + vSize.width*0.7f, origin.y+vSize.height*0.535f));
		scorelab1->setScaleX(scaleX);
		scorelab1->setScaleY(scaleY);
		this->addChild(scorelab1, 11);

		CCLabelTTF* totallab1 = CCLabelTTF::create(CCString::createWithFormat("%d", totalNum)->getCString(), "Marker Felt", 24);
		totallab1->setPosition(ccp(origin.x + vSize.width*0.7f, origin.y+vSize.height*0.47f));
		totallab1->setScaleX(scaleX);
		totallab1->setScaleY(scaleY);
		this->addChild(totallab1, 11);

		int ttt = endTime-startTime;
		CCLabelTTF* timelab = CCLabelTTF::create(CCString::createWithFormat("%d: %d: %d", 
			ttt/60/60, ttt%(60*60)/60, ttt%(60*60)%60)->getCString(), "Marker Felt", 24);
		timelab->setPosition(ccp(origin.x + vSize.width*0.7f, origin.y+vSize.height*0.4f));
		timelab->setScaleX(scaleX);
		timelab->setScaleY(scaleY);
		this->addChild(timelab, 11);
		this->unschedule(schedule_selector(PlayGame::nextLev));
	}
}

CCRect PlayGame::rect(int row, int col)
{
	CCPoint tmp = this->getPositionByij(row, col);
	tmp.x -= this->bw/2;
	tmp.y -= this->bh/2;
	CCRect rect = CCRectMake(tmp.x, tmp.y, this->bw, this->bh);		//left, bottom, width, height
	return rect;
}

void PlayGame::getIJByPosition(CCPoint location)
{
	int row[2], col[2];
	int cnt = 0;
	for(int i=0; i<sizeof(this->gamepan)/sizeof(int)/(sizeof(this->gamepan[0])/sizeof(int)); i++)
	{
		for(int j=0; j<sizeof(this->gamepan[0])/sizeof(int); j++)
		{
			if(this->tiles[i][j] != NULL && this->rect(i, j).containsPoint(location))			//클릭한점을 포함하는가?
			{
				row[cnt] = i;
				col[cnt] = j;
				cnt ++;
			}
		}
	}
	if(cnt == 2)
	{
		float dist1 = location.getDistance(this->getPositionByij(row[0], col[0]));
		float dist2 = location.getDistance(this->getPositionByij(row[1], col[1]));

		if(dist1<dist2)
		{
			posxy[0] = row[0];
			posxy[1] = col[0];
			return;
		}else
		{
			posxy[0] = row[1];
			posxy[1] = col[1];
			return;
		}
	}else if(cnt == 1)
	{
		posxy[0] = row[0];
		posxy[1] = col[0];
		return;
	}
	posxy[0] = -1;
	posxy[1] = -1;
}

int PlayGame::isGem(int row, int col)
{
	switch (this->gamepan[row][col])
	{
	case RED:
		return RED;
	case BLUE:
		return BLUE;
	case GREEN:
		return GREEN;
	case CYAN:
		return CYAN;
	case RAINBOW:
		return RAINBOW;
	case EXPLODE:
		return EXPLODE;
	case MINE:
		return MINE;
	case 0:
	case 11:
	case 22:
	case 33:
	case 44:
	case 88:
		return 0;
	default:
		return -1;
	}
}

void PlayGame::findMinPath(int fr, int fc, int er, int ec)			//최단경로찾기
{
	int pr[100], pc[100];	//부모
	int cr[100], cc[100];		//자식
	memset(cr, -1, 100);
	memset(cc, -1, 100);
	cr[0] = fr;
	cc[0] = fc;
	weight = 2;
	while(true)
	{
		memcpy(pr, cr, 100);			//세대교체
		memcpy(pc, cc, 100);
		memset(cr, -1, 100);			//자식마당확보
		memset(cc, -1, 100);
		int cnt = 0;
		for(int i=0; i<100; i++)		//부모수만큼 순환
		{
			if(pr[i] == -1 && pc[i] == -1)
				break;
			if(pc[i]+1 < 19 && pathpan[pr[i]][pc[i]+1] == 0)	//1방									//				  5   6
			{							
				pathpan[pr[i]][pc[i]+1] = weight;														//				4	0	1	
				if(pr[i]==er && pc[i]+1==ec)															//				  3   2
				{
					success = true;
					return;
				}		
				cr[cnt] = pr[i];
				cc[cnt] = pc[i]+1;
				cnt++;
			}
			if(pr[i]+1<14 && pc[i]+pr[i]%2<19 && pathpan[pr[i]+1][pc[i]+pr[i]%2] == 0)				//2방
			{
				pathpan[pr[i]+1][pc[i]+pr[i]%2] = weight;
				if(pr[i]+1==er && pc[i]+pr[i]%2==ec)																				
				{
					success = true;
					return;
				}
				cr[cnt] = pr[i]+1;
				cc[cnt] = pc[i]+pr[i]%2;
				cnt++;
			}
			if(pr[i]+1<14 && pc[i]-(pr[i]+1)%2>=0 && pathpan[pr[i]+1][pc[i]-(pr[i]+1)%2] == 0)		//3방
			{
				pathpan[pr[i]+1][pc[i]-(pr[i]+1)%2] = weight;
				if(pr[i]+1==er && pc[i]-(pr[i]+1)%2==ec)																				
				{
					success = true;
					return;
				}
				cr[cnt] = pr[i]+1;
				cc[cnt] = pc[i]-(pr[i]+1)%2;
				cnt++;
			}
			if(pc[i]-1>=0 && pathpan[pr[i]][pc[i]-1] == 0)											//4방							
			{
				pathpan[pr[i]][pc[i]-1] = weight;
				if(pr[i]==er && pc[i]-1==ec)																				
				{
					success = true;
					return;
				}
				cr[cnt] = pr[i];
				cc[cnt] = pc[i]-1;
				cnt++;
			}
			if(pr[i]-1>=0 && pc[i]-(pr[i]+1)%2>=0 && pathpan[pr[i]-1][pc[i]-(pr[i]+1)%2] == 0)		//5방
			{
				pathpan[pr[i]-1][pc[i]-(pr[i]+1)%2] = weight;
				if(pr[i]-1==er && pc[i]-(pr[i]+1)%2==ec)																				
				{
					success = true;
					return;
				}
				cr[cnt] = pr[i]-1;
				cc[cnt] = pc[i]-(pr[i]+1)%2;
				cnt++;
			}
			if(pr[i]-1>=0 && pc[i]+pr[i]%2<19 && pathpan[pr[i]-1][pc[i]+pr[i]%2] == 0)				//6방
			{
				pathpan[pr[i]-1][pc[i]+pr[i]%2] = weight;
				if(pr[i]-1==er && pc[i]+pr[i]%2==ec)																				
				{
					success = true;
					return;
				}
				cr[cnt] = pr[i]-1;
				cc[cnt] = pc[i]+pr[i]%2;
				cnt++;
			}
		}
		if(cnt == 0)
			break;
		weight ++;
	}
}

void PlayGame::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if(!lock)
	{
		pushed = true;
		CCPoint location;
		CCSetIterator iter = pTouches->begin();
		for(; iter != pTouches->end(); iter ++)
		{
			CCTouch* pTouches = (CCTouch*)(*iter);
			location = pTouches->getLocation();
		}

		this->getIJByPosition(location);
		if(posxy[0] != -1 && posxy[1] != -1)				//game region?
		{
			int row = posxy[0];
			int col = posxy[1];
			tmprow = row;
			tmpcol = col;
			int gem = this->isGem(row, col);
			if(gem)							//보석이 있다면
			{
				SimpleAudioEngine::sharedEngine()->playEffect("select.wav");
				if(this->seleditem)
				{
					this->removeChild(this->particles[this->seledpos[0]][this->seledpos[1]]);
					this->particles[this->seledpos[0]][this->seledpos[1]] = NULL;
				}
				this->seleditem = gem;
				this->seledpos[0] = row;
				this->seledpos[1] = col;

				if(this->particles[row][col] == NULL)		//파티클이 없다면
				{
					this->particles[row][col] = CCParticleSun::create();
					this->particles[row][col]->setEmissionRate(25);
					this->particles[row][col]->setScaleX(0.7f*scaleX);
					this->particles[row][col]->setScaleY(0.7f*scaleY);
					this->particles[row][col]->setPosition(this->getPositionByij(row, col));
					this->addChild(this->particles[row][col], 9);
				}
			}else                          //보석이 없다면
			{
				SimpleAudioEngine::sharedEngine()->playEffect("bonk.wav");
				this->seleditem = 0;		
			}
		}else
		{
			this->seleditem = 0;
			for(int i=0; i<sizeof(PlayGame::pantemp[0])/sizeof(int)/(sizeof(PlayGame::pantemp[0][0])/sizeof(int)); i++)	//경로찾기초기화
			{
				for(int j=0; j<sizeof(PlayGame::pantemp[0][0])/sizeof(int); j++)
				{
					if(this->particles[i][j] != NULL)
					{
						this->removeChild(this->particles[i][j]);
						this->particles[i][j] = NULL;
					}
					if(this->mpan[i][j] != NULL)
					{
						this->removeChild(this->mpan[i][j]);		//끌기시 표시된 보석없애기
						this->mpan[i][j] = NULL;
					}
				}
			}
		}
	}
}

void PlayGame::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if(!lock && pushed)
	{
		CCPoint location;
		CCSetIterator iter = pTouches->begin();
		for(; iter != pTouches->end(); iter ++)
		{
			CCTouch* pTouches = (CCTouch*)(*iter);
			location = pTouches->getLocation();
		}

		this->getIJByPosition(location);
		if(posxy[0] != -1 && posxy[1] != -1 && this->seleditem)
		{
			int row = posxy[0];
			int col = posxy[1];
			if(row != tmprow || col != tmpcol)							//세포가 선택된 첫 순간
			{
				if(this->mpan[tmprow][tmpcol] != NULL)
				{
					this->removeChild(this->mpan[tmprow][tmpcol]);
					this->mpan[tmprow][tmpcol] = NULL;
				}
				switch (this->seleditem)
				{
				case RED:
					this->mpan[row][col] = CCSprite::create("red.png");
					break;
				case BLUE:
					this->mpan[row][col] = CCSprite::create("blue.png");
					break;
				case GREEN:
					this->mpan[row][col] = CCSprite::create("green.png");
					break;
				case CYAN:
					this->mpan[row][col] = CCSprite::create("cyan.png");
					break;
				case RAINBOW:
					this->mpan[row][col] = CCSprite::create("rainbow.png");
					break;
				case EXPLODE:
					this->mpan[row][col] = CCSprite::create("explode.png");
					break;
				case MINE:
					this->mpan[row][col] = CCSprite::create("mine.png");
					break;
				}
				this->mpan[row][col]->setPosition(this->getPositionByij(row, col));
				this->mpan[row][col]->setOpacity(0x90);
				this->mpan[row][col]->setScaleX(scaleX);
				this->mpan[row][col]->setScaleY(scaleY);
				this->addChild(this->mpan[row][col], 8);

				for(int i=0; i<sizeof(PlayGame::pantemp[0])/sizeof(int)/(sizeof(PlayGame::pantemp[0][0])/sizeof(int)); i++)	//경로찾기초기화
				{
					for(int j=0; j<sizeof(PlayGame::pantemp[0][0])/sizeof(int); j++)
					{
						pathpan[i][j] = 0;
						switch (this->gamepan[i][j])
						{
						case -1:
						case 1:
						case 2:
						case 3:
						case 4:
						case 8:
						case 9:
						case 10:
							pathpan[i][j] = -1;
							break;
						}
						if(this->particles[i][j] != NULL)
						{
							this->removeChild(this->particles[i][j]);
							this->particles[i][j] = NULL;
						}
					}
				}
				path = vector<Vertex>();
				success = false;
				weight = 1;
				pathpan[seledpos[0]][seledpos[1]] = weight;

				this->findMinPath(seledpos[0], seledpos[1], row, col);

				int sw = pathpan[row][col];
				int sr = row, sc = col;
				while(sw>1)									//경로종합
				{
					sw --;
					if(sc+1 < 19 && pathpan[sr][sc+1] == sw)								//1방					
					{							
						path.push_back(Vertex(sr, sc+1));
						sc = sc+1;
						sr = sr;
						continue;
					}
					if(sr+1<14 && sc+sr%2<19 && pathpan[sr+1][sc+sr%2] == sw)				//2방
					{
						path.push_back(Vertex(sr+1, sc+sr%2));
						sc = sc+sr%2;
						sr = sr+1;
						continue;
					}
					if(sr+1<14 && sc-(sr+1)%2>=0 && pathpan[sr+1][sc-(sr+1)%2] == sw)		//3방
					{
						path.push_back(Vertex(sr+1, sc-(sr+1)%2));
						sc = sc-(sr+1)%2;
						sr = sr+1;
						continue;
					}
					if(sc-1>=0 && pathpan[sr][sc-1] == sw)									//4방							
					{
						path.push_back(Vertex(sr, sc-1));
						sc = sc-1;
						sr = sr;
						continue;
					}
					if(sr-1>=0 && sc-(sr+1)%2>=0 && pathpan[sr-1][sc-(sr+1)%2] == sw)		//5방
					{
						path.push_back(Vertex(sr-1, sc-(sr+1)%2));
						sc = sc-(sr+1)%2;
						sr = sr-1;
						continue;
					}	
					if(sr-1>=0 && sc+sr%2<19 && pathpan[sr-1][sc+sr%2] == sw)				//6방
					{
						path.push_back(Vertex(sr-1, sc+sr%2));
						sc = sc+sr%2;
						sr = sr-1;
						continue;
					}
				}
				if(success)
				{
					vector<Vertex>::iterator iter = path.begin();
					for(; iter!=path.end(); iter++)
					{
						this->particles[iter->row][iter->col] = CCParticleSun::create();
						this->particles[iter->row][iter->col]->setEmissionRate(25);
						this->particles[iter->row][iter->col]->setScaleX(0.7f*scaleX);
						this->particles[iter->row][iter->col]->setScaleY(0.7f*scaleY);
						this->particles[iter->row][iter->col]->setPosition(this->getPositionByij(iter->row, iter->col));
						this->addChild(this->particles[iter->row][iter->col], 9);
					}
				}
			}
			tmprow = row;
			tmpcol = col;
		}
	}
}

void PlayGame::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if(gameover)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("btn_click.wav");
		gameover = false;
		continueGame = true;
		CCScene* s = new CCScene();
		CCLayer* g = new PlayGame();
		g->init();
		s->addChild(g);
		CCScene* pScene = createTransitionR(TRANSITION_DURATION, s);
		s->release();
		if (pScene)
		{
			CCDirector::sharedDirector()->replaceScene(pScene);
		}
	}
	if(!lock && pushed)
	{
		CCPoint location;
		CCSetIterator iter = pTouches->begin();
		for(; iter != pTouches->end(); iter ++)
		{
			CCTouch* pTouches = (CCTouch*)(*iter);
			location = pTouches->getLocation();
		}

		this->getIJByPosition(location);
		if(posxy[0] != -1 && posxy[1] != -1 && this->seleditem)
		{
			int row = tgrpos[0] = posxy[0];
			int col = tgrpos[1] = posxy[1];

			int gem = this->isGem(row, col);
			if(!gem && success)							//보석이 없다면
			{
				SimpleAudioEngine::sharedEngine()->playEffect("unselect.wav");
				lock = true;
				CCPointArray *ptArray = CCPointArray::create(path.size()+2);					//보석이동
				for(unsigned int i=0; i<path.size(); i++)
					ptArray->addControlPoint(this->getPositionByij(path.at(i).row, path.at(i).col));
				ptArray = ptArray->reverse();
				CCPoint tmppoint = this->getPositionByij(this->seledpos[0], this->seledpos[1]);
				ptArray->insertControlPoint(tmppoint, 0);
				ptArray->addControlPoint(this->getPositionByij(row, col));
				CCCatmullRomTo *moveAction = CCCatmullRomTo::create(0.08f*ptArray->count(), ptArray);				//일정한 시간동안 이동
				CCSequence *seq = CCSequence::create(moveAction, NULL);
				this->span[this->seledpos[0]][this->seledpos[1]]->runAction(seq);
				this->schedule(schedule_selector(PlayGame::checkMove), 0.001f);					//이동감시
			}else
			{
				SimpleAudioEngine::sharedEngine()->playEffect("unselect.wav");
				this->removeChild(this->mpan[row][col]);		//끌기시 표시되는 보석없애기
				this->mpan[row][col] = NULL;
			}
		}else
		{
			this->seleditem = 0;
			for(int i=0; i<sizeof(PlayGame::pantemp[0])/sizeof(int)/(sizeof(PlayGame::pantemp[0][0])/sizeof(int)); i++)	//경로찾기초기화
			{
				for(int j=0; j<sizeof(PlayGame::pantemp[0][0])/sizeof(int); j++)
				{
					if(this->particles[i][j] != NULL)
					{
						this->removeChild(this->particles[i][j]);
						this->particles[i][j] = NULL;
					}
					if(this->mpan[i][j] != NULL)
					{
						this->removeChild(this->mpan[i][j]);		//끌기시 표시된 보석없애기
						this->mpan[i][j] = NULL;
					}
				}
			}
		}
	}
}

void PlayGame::checkMove(float deltaTime)
{
	getIJByPosition(this->span[this->seledpos[0]][this->seledpos[1]]->getPosition());
	int rw = posxy[0];
	int co = posxy[1];
	if(this->particles[rw][co] != NULL)
	{
		this->removeChild(this->particles[rw][co]);
		this->particles[rw][co] = NULL;
	}
	if(rw == tgrpos[0] && co == tgrpos[1])			//이동끝?
	{
		this->removeChild(this->mpan[tgrpos[0]][tgrpos[1]]);		//끌기시 표시되는 보석없애기
		this->mpan[tgrpos[0]][tgrpos[1]] = NULL;

		this->removeChild(this->span[this->seledpos[0]][this->seledpos[1]]);		//이동된 객체바꾸기
		this->span[this->seledpos[0]][this->seledpos[1]] = NULL;
		if(this->span[tgrpos[0]][tgrpos[1]] != NULL)
		{
			this->removeChild(this->span[tgrpos[0]][tgrpos[1]]);
			this->span[tgrpos[0]][tgrpos[1]] = NULL;
		}
		switch (this->seleditem)
		{
		case RED:
			this->span[tgrpos[0]][tgrpos[1]] = CCSprite::create("red.png");
			break;
		case BLUE:
			this->span[tgrpos[0]][tgrpos[1]] = CCSprite::create("blue.png");
			break;
		case GREEN:
			this->span[tgrpos[0]][tgrpos[1]] = CCSprite::create("green.png");
			break;
		case CYAN:
			this->span[tgrpos[0]][tgrpos[1]] = CCSprite::create("cyan.png");
			break;
		case RAINBOW:
			this->span[tgrpos[0]][tgrpos[1]] = CCSprite::create("rainbow.png");
			break;
		case EXPLODE:
			this->span[tgrpos[0]][tgrpos[1]] = CCSprite::create("explode.png");
			break;
		case MINE:
			this->span[tgrpos[0]][tgrpos[1]] = CCSprite::create("mine.png");
			break;
		}
		this->span[tgrpos[0]][tgrpos[1]]->setPosition(this->getPositionByij(tgrpos[0], tgrpos[1]));
		this->span[tgrpos[0]][tgrpos[1]]->setScaleX(scaleX);
		this->span[tgrpos[0]][tgrpos[1]]->setScaleY(scaleY);
		this->addChild(this->span[tgrpos[0]][tgrpos[1]], 6);

		this->gamepan[this->seledpos[0]][this->seledpos[1]] = 0;				//값이동
		this->gamepan[tgrpos[0]][tgrpos[1]] = this->seleditem;		

		int total = checkEat(tgrpos[0], tgrpos[1]);				//이동후 먹을수 있는 돌세기
		if(total>=3)										//먹을수 있는 돌이 있으면
		{
			vector<Vertex>::iterator iter = eatArr.begin();			//먹을수 있는 돌 터치는 효과
			for(; iter!=eatArr.end(); iter++)
			{
				this->particles[iter->row][iter->col] = CCParticleSun::create();
				this->particles[iter->row][iter->col]->setScaleX(0.1f*scaleX);
				this->particles[iter->row][iter->col]->setScaleY(0.1f*scaleY);
				this->particles[iter->row][iter->col]->setPosition(this->getPositionByij(iter->row, iter->col));
				this->addChild(particles[iter->row][iter->col], 9);
				CCActionInterval* explodeAction = CCScaleTo::create(0.5f, 1.5f*scaleX, 1.5f*scaleY);
				explodeAction->retain();
				this->particles[iter->row][iter->col]->runAction(CCSequence::create(explodeAction, NULL));
				SimpleAudioEngine::sharedEngine()->playEffect("bowl.wav");
			}
			this->schedule(schedule_selector(PlayGame::checkExplode));
			if(seleditem == MINE)									//지뢰를 터칠때
			{
				lock = true;
				int mineTgr;
				for(unsigned int i=0; i<eatArr.size(); i++)
				{
					if(this->gamepan[eatArr.at(1).row][eatArr.at(1).col] != MINE)
					{
						mineTgr = this->gamepan[eatArr.at(1).row][eatArr.at(1).col];
						break;
					}
				}
				int k = 0;
				for(int i=0; i<sizeof(PlayGame::pantemp[0])/sizeof(int)/(sizeof(PlayGame::pantemp[0][0])/sizeof(int)); i++)
				{
					for(int j=0; j<sizeof(PlayGame::pantemp[0][0])/sizeof(int); j++)
					{
						if(this->gamepan[i][j] == mineTgr && PlayGame::pantemp[this->level][i][j] != -1)
						{
							CCActionInterval* mineExpAction = CCMoveTo::create(0.2f * CCPoint(i, j).getDistance(CCPoint(tgrpos[0], tgrpos[1])), this->getPositionByij(i, j));
							mineExpAction->retain();
							mineExp[k] = CCParticleSun::create();
							mineExp[k]->setPosition(this->getPositionByij(tgrpos[0], tgrpos[1]));
							mineExp[k]->setScaleX(scaleX*0.7f);
							mineExp[k]->setScaleY(scaleY*0.7f);
							this->addChild(mineExp[k], 8);
							mineExp[k]->runAction(CCSequence::create(mineExpAction, NULL));
							mineVer[k] = Vertex(i, j);
							k++;
						}
					}
				}
				this->schedule(schedule_selector(PlayGame::checkMineExp), 0.2f);			//지뢰파편이 목표점에 닿는가 검사
			}else if(seleditem == EXPLODE)							//폭탄을 터칠때
			{
				lock = true;
				SimpleAudioEngine::sharedEngine()->playEffect("shot.wav");
				CCActionInterval* explodeAction = CCScaleTo::create(1.0f, 6.0f*scaleX, 6.0f*scaleY);
				explodeAction->retain();
				explodePtl = CCParticleSun::create();
				explodePtl->setPosition(this->getPositionByij(tgrpos[0], tgrpos[1]));
				explodePtl->setScaleX(scaleX);
				explodePtl->setScaleY(scaleY);
				this->addChild(explodePtl, 8);
				explodePtl->runAction(CCSequence::create(explodeAction, NULL));
				this->schedule(schedule_selector(PlayGame::monitorExplode), 0.1f);
			}
		}else                                                   //먹을수 있는 돌이 없으면	
		{
			this->makeNewItems();
			lock = false;
		}

		/*this->seleditem = 0;						//선택된 객체 없음
		this->seledpos[0] = -1;
		this->seledpos[1] = -1;*/
		this->unschedule(schedule_selector(PlayGame::checkMove));
	}	
}

void PlayGame::monitorExplode(float delayTime)
{
	if(explodePtl->getScaleX() >= 5.8f*scaleX && explodePtl->getScaleY() >= 5.8f*scaleY)			//폭발끝
	{
		int row = tgrpos[0], col = tgrpos[1];
		int r2 = row, c2 = col;
		int r5 = row, c5 = col;
		int r3 = row, c3 = col;
		int r6 = row, c6 = col;
		for(int i=0; i<5; i++)
		{
			if(col-i>=0 && this->gamepan[row][col-i] != 0 && this->gamepan[row][col-i] != -1)		//4
			{
				this->gamepan[row][col-i] = 0;
				if(this->span[row][col-i] != NULL){
					if(this->tgrtls[row][col-i] != NULL)
					{
						this->removeChild(this->tgrtls[row][col-i]);
						this->tgrtls[row][col-i] = NULL;
					}
					this->removeChild(this->span[row][col-i]);
				}
				this->span[row][col-i] = NULL;
			}
			if(col+i<140 && this->gamepan[row][col+i] != 0 && this->gamepan[row][col+i] != -1)		//1
			{
				this->gamepan[row][col+i] = 0;
				if(this->span[row][col+i] != NULL){
					if(this->tgrtls[row][col+i] != NULL)
					{
						this->removeChild(this->tgrtls[row][col+i]);
						this->tgrtls[row][col+i] = NULL;
					}
					this->removeChild(this->span[row][col+i]);
				}
				this->span[row][col+i] = NULL;
			}
			if(r2+1<14 && c2+r2%2<19 && this->gamepan[r2+1][c2+r2%2] != 0 && this->gamepan[r2+1][c2+r2%2] != -1)		//2
			{
				this->gamepan[r2+1][c2+r2%2] = 0;
				if(this->span[r2+1][c2+r2%2] != NULL){
					if(this->tgrtls[r2+1][c2+r2%2] != NULL)
					{
						this->removeChild(this->tgrtls[r2+1][c2+r2%2]);
						this->tgrtls[r2+1][c2+r2%2] = NULL;
					}
					this->removeChild(this->span[r2+1][c2+r2%2]);
				}
				this->span[r2+1][c2+r2%2] = NULL;
				c2 = c2+r2%2;
				r2 = r2 + 1;
			}
			if(r5-1>=0 && c5-(r5+1)%2>=0 && this->gamepan[r5-1][c5-(r5+1)%2] != 0 && this->gamepan[r5-1][c5-(r5+1)%2] != -1)		//5
			{
				this->gamepan[r5-1][c5-(r5+1)%2] = 0;
				if(this->span[r5-1][c5-(r5+1)%2] != NULL){
					if(this->tgrtls[r5-1][c5-(r5+1)%2] != NULL)
					{
						this->removeChild(this->tgrtls[r5-1][c5-(r5+1)%2]);
						this->tgrtls[r5-1][c5-(r5+1)%2] = NULL;
					}
					this->removeChild(this->span[r5-1][c5-(r5+1)%2]);
				}
				this->span[r5-1][c5-(r5+1)%2] = NULL;
				c5 = c5-(r5+1)%2;
				r5 = r5 - 1;
			}
			if(r3+1<14 && c3-(r3+1)%2>=0 && this->gamepan[r3+1][c3-(r3+1)%2] != 0 && this->gamepan[r3+1][c3-(r3+1)%2] != -1)		//3
			{
				this->gamepan[r3+1][c3-(r3+1)%2] = 0;
				if(this->span[r3+1][c3-(r3+1)%2] != NULL){
					if(this->tgrtls[r3+1][c3-(r3+1)%2] != NULL)
					{
						this->removeChild(this->tgrtls[r3+1][c3-(r3+1)%2]);
						this->tgrtls[r3+1][c3-(r3+1)%2] = NULL;
					}
					this->removeChild(this->span[r3+1][c3-(r3+1)%2]);
				}
				this->span[r3+1][c3-(r3+1)%2] = NULL;
				c3 = c3 - (r3 + 1) % 2;
				r3 = r3 + 1;
			}
			if(r6-1>=0 && c6+r6%2<19 && this->gamepan[r6-1][c6+r6%2] != 0 && this->gamepan[r6-1][c6+r6%2] != -1)		//6
			{
				this->gamepan[r6-1][c6+r6%2] = 0;
				if(this->span[r6-1][c6+r6%2] != NULL){
					if(this->tgrtls[r6-1][c6+r6%2] != NULL)
					{
						this->removeChild(this->tgrtls[r6-1][c6+r6%2]);
						this->tgrtls[r6-1][c6+r6%2] = NULL;
					}
					this->removeChild(this->span[r6-1][c6+r6%2]);
				}
				this->span[r6-1][c6+r6%2] = NULL;
				c6 = c6 + r6 % 2;
				r6 = r6 - 1;
			}
		}
		int r1 = row-2, c1 = col;			
		this->destoryVShape(r1, c1);
		r1 = row+2; c1 = col-2;	
		this->destoryVShape(r1, c1);
		r1 = row+2; c1 = col+2;	
		this->destoryVShape(r1, c1);

		int r4 = row-2, c4 = col-2;
		this->destoryAShape(r4, c4);
		r4 = row-2; c4 = col+2;
		this->destoryAShape(r4, c4);
		r4 = row+2; c4 = col;
		this->destoryAShape(r4, c4);

		if(maxEating == 4)
		{
			this->gamepan[tgrpos[0]][tgrpos[1]] = MINE;	
			this->span[tgrpos[0]][tgrpos[1]] = CCSprite::create("mine.png");
			this->span[tgrpos[0]][tgrpos[1]]->setPosition(this->getPositionByij(tgrpos[0], tgrpos[1]));
			this->span[tgrpos[0]][tgrpos[1]]->setScaleX(scaleX);
			this->span[tgrpos[0]][tgrpos[1]]->setScaleY(scaleY);
			this->addChild(this->span[tgrpos[0]][tgrpos[1]], 6);
		}else if(maxEating == 5)
		{
			this->gamepan[tgrpos[0]][tgrpos[1]] = EXPLODE;	
			this->span[tgrpos[0]][tgrpos[1]] = CCSprite::create("explode.png");
			this->span[tgrpos[0]][tgrpos[1]]->setPosition(this->getPositionByij(tgrpos[0], tgrpos[1]));
			this->span[tgrpos[0]][tgrpos[1]]->setScaleX(scaleX);
			this->span[tgrpos[0]][tgrpos[1]]->setScaleY(scaleY);
			this->addChild(this->span[tgrpos[0]][tgrpos[1]], 6);
		}

		this->removeChild(explodePtl);			//폭발효과제거
		explodePtl = NULL;
		this->unschedule(schedule_selector(PlayGame::monitorExplode));
		lock = false;
	}
}

void PlayGame::destoryVShape(int row, int col)
{
	if(row>=0 && col>=0 && this->gamepan[row][col] != 0 && this->gamepan[row][col] != -1)		//자
	{
		this->gamepan[row][col] = 0;
		if(this->span[row][col] != NULL){
			if(this->tgrtls[row][col] != NULL)
			{
				this->removeChild(this->tgrtls[row][col]);
				this->tgrtls[row][col] = NULL;
			}
			this->removeChild(this->span[row][col]);
		}
		this->span[row][col] = NULL;
	}
	if(row-1>=0 && col-(row+1)%2>=0 && this->gamepan[row-1][col-(row+1)%2] != 0 && this->gamepan[row-1][col-(row+1)%2] != -1)		//5
	{
		this->gamepan[row-1][col-(row+1)%2] = 0;
		if(this->span[row-1][col-(row+1)%2] != NULL){
			if(this->tgrtls[row-1][col-(row+1)%2] != NULL)
			{
				this->removeChild(this->tgrtls[row-1][col-(row+1)%2]);
				this->tgrtls[row-1][col-(row+1)%2] = NULL;
			}
			this->removeChild(this->span[row-1][col-(row+1)%2]);
		}
		this->span[row-1][col-(row+1)%2] = NULL;
	}
	if(row-1>=0 && col+row%2<19 && this->gamepan[row-1][col+row%2] != 0 && this->gamepan[row-1][col+row%2] != -1)		//6
	{
		this->gamepan[row-1][col+row%2] = 0;
		if(this->span[row-1][col+row%2] != NULL){
			if(this->tgrtls[row-1][col+row%2] != NULL)
			{
				this->removeChild(this->tgrtls[row-1][col+row%2]);
				this->tgrtls[row-1][col+row%2] = NULL;
			}
			this->removeChild(this->span[row-1][col+row%2]);
		}
		this->span[row-1][col+row%2] = NULL;
	}
}

void PlayGame::destoryAShape(int row, int col)
{
	if(row>=0 && col>=0 && this->gamepan[row][col] != 0 && this->gamepan[row][col] != -1)		//자
	{
		this->gamepan[row][col] = 0;
		if(this->span[row][col] != NULL){
			if(this->tgrtls[row][col] != NULL)
			{
				this->removeChild(this->tgrtls[row][col]);
				this->tgrtls[row][col] = NULL;
			}
			this->removeChild(this->span[row][col]);
		}
		this->span[row][col] = NULL;
	}
	if(row+1<14 && col+row%2<19 && this->gamepan[row+1][col+row%2] != 0 && this->gamepan[row+1][col+row%2] != -1)		//2
	{
		this->gamepan[row+1][col+row%2] = 0;
		if(this->span[row+1][col+row%2] != NULL){
			if(this->tgrtls[row+1][col+row%2] != NULL)
			{
				this->removeChild(this->tgrtls[row+1][col+row%2]);
				this->tgrtls[row+1][col+row%2] = NULL;
			}
			this->removeChild(this->span[row+1][col+row%2]);
		}
		this->span[row+1][col+row%2] = NULL;
	}
	if(row+1<14 && col-(row+1)%2>=0 && this->gamepan[row+1][col-(row+1)%2] != 0 && this->gamepan[row+1][col-(row+1)%2] != -1)		//6
	{
		this->gamepan[row+1][col-(row+1)%2] = 0;
		if(this->span[row+1][col-(row+1)%2] != NULL){
			if(this->tgrtls[row+1][col-(row+1)%2] != NULL)
			{
				this->removeChild(this->tgrtls[row+1][col-(row+1)%2]);
				this->tgrtls[row+1][col-(row+1)%2] = NULL;
			}
			this->removeChild(this->span[row+1][col-(row+1)%2]);
		}
		this->span[row+1][col-(row+1)%2] = NULL;
	}
}

void PlayGame::checkMineExp(float delayTime)
{
	int endf = true;
	for(int i=0; i<300; i++)
	{
		if(mineExp[i] == NULL)
			continue;
		endf = false;
		//int* pos = this->getIJByPosition(mineExp[i]->getPosition());
		CCPoint pos = this->getPositionByij(mineVer[i].row, mineVer[i].col);
		//if(pos != NULL && pos[0]==mineVer[i].row && pos[1]==mineVer[i].col)		//목표에 도달했는가?
		if(mineExp[i]->getPosition().getDistance(pos) < this->bw/2)					//목표에 도달했는가?
		{
			SimpleAudioEngine::sharedEngine()->playEffect("glassbreaks.wav");
			this->removeChild(mineExp[i]);
			mineExp[i] = NULL;
			
			this->gamepan[mineVer[i].row][mineVer[i].col] = 0;
			this->removeChild(this->span[mineVer[i].row][mineVer[i].col]);
			this->span[mineVer[i].row][mineVer[i].col] = NULL;

			if(this->tgrtls[mineVer[i].row][mineVer[i].col] != NULL)
			{
				this->removeChild(this->tgrtls[mineVer[i].row][mineVer[i].col]);
				this->tgrtls[mineVer[i].row][mineVer[i].col] = NULL;
			}

			this->score += 12;
			totalNum ++;

			lock = false;
		}
	}
	if(endf)
		this->unschedule(schedule_selector(PlayGame::checkMineExp));
}

void PlayGame::makeNewItems()
{
	SimpleAudioEngine::sharedEngine()->playEffect("waterdrop2.wav");
	srand(time(NULL));
	for(int i=0; i<sizeof(PlayGame::pantemp[0])/sizeof(int)/(sizeof(PlayGame::pantemp[0][0])/sizeof(int)); i++)			//tile배치
	{
		for(int j=0; j<sizeof(PlayGame::pantemp[0][0])/sizeof(int); j++)
		{
			if(PlayGame::pantemp[this->level][i][j] == -1 && this->gamepan[i][j] != -1)
			{
				this->gamepan[i][j] = -1;
				if(this->span[i][j] != NULL)
				{
					this->removeChild(this->span[i][j]);
					this->span[i][j] = NULL;
				}
			}
			if(this->gamepan[i][j] == 0 && PlayGame::pantemp[this->level][i][j] != -1)			//빈공간이면 작은보석만들기
			{
				this->gamepan[i][j] = rand()%15;
				if(!(this->gamepan[i][j]>=1 && this->gamepan[i][j]<=4))
				{
					if(this->gamepan[i][j] == 5)			//special		
					{
						this->gamepan[i][j] = rand()%11;
						if(this->gamepan[i][j] != RAINBOW)
							this->gamepan[i][j] = 0;
						else
						{
							this->gamepan[i][j] = 88;
							this->span[i][j] = CCSprite::create("rainbow.png");
							this->span[i][j]->setPosition(this->getPositionByij(i, j));
							this->span[i][j]->setScaleX(0.5f*scaleX);
							this->span[i][j]->setScaleY(0.5f*scaleY);
							this->addChild(this->span[i][j], 6);
						}
					}
					else
					{
						this->gamepan[i][j] = 0;
					}
				}else
				{
					switch (this->gamepan[i][j])
					{
					case RED:
						this->gamepan[i][j] = 11;
						this->span[i][j] = CCSprite::create("red.png");
						this->span[i][j]->setPosition(this->getPositionByij(i, j));
						this->span[i][j]->setScaleX(0.5f*scaleX);
						this->span[i][j]->setScaleY(0.5f*scaleY);
						break;
					case BLUE:
						this->gamepan[i][j] = 22;
						this->span[i][j] = CCSprite::create("blue.png");
						this->span[i][j]->setPosition(this->getPositionByij(i, j));
						this->span[i][j]->setScaleX(0.5f*scaleX);
						this->span[i][j]->setScaleY(0.5f*scaleY);
						break;
					case GREEN:
						this->gamepan[i][j] = 33;
						this->span[i][j] = CCSprite::create("green.png");
						this->span[i][j]->setPosition(this->getPositionByij(i, j));
						this->span[i][j]->setScaleX(0.5f*scaleX);
						this->span[i][j]->setScaleY(0.5f*scaleY);
						break;
					case CYAN:
						this->gamepan[i][j] = 44;
						this->span[i][j] = CCSprite::create("cyan.png");
						this->span[i][j]->setPosition(this->getPositionByij(i, j));
						this->span[i][j]->setScaleX(0.5f*scaleX);
						this->span[i][j]->setScaleY(0.5f*scaleY);
						break;
					}
					this->addChild(this->span[i][j], 6);
				}
			}else if(this->gamepan[i][j] != -1)
			{
				CCActionInterval* increaseAction = CCScaleTo::create(0.3f, 1.0f*scaleX, 1.0f*scaleY);
				increaseAction->retain();
				switch (this->gamepan[i][j])
				{
				case 11:
					this->gamepan[i][j] = 1;
					this->span[i][j]->runAction(CCSequence::create(increaseAction, NULL));
					this->scheduleOnce(schedule_selector(PlayGame::checkNewEat), 0);
					break;
				case 22:
					this->gamepan[i][j] = 2;
					this->span[i][j]->runAction(CCSequence::create(increaseAction, NULL));
					this->scheduleOnce(schedule_selector(PlayGame::checkNewEat), 0);
					break;
				case 33:
					this->gamepan[i][j] = 3;
					this->span[i][j]->runAction(CCSequence::create(increaseAction, NULL));
					this->scheduleOnce(schedule_selector(PlayGame::checkNewEat), 0);
					break;
				case 44:
					this->gamepan[i][j] = 4;
					this->span[i][j]->runAction(CCSequence::create(increaseAction, NULL));
					this->scheduleOnce(schedule_selector(PlayGame::checkNewEat), 0);
					break;
				case 88:
					this->gamepan[i][j] = RAINBOW;
					this->span[i][j]->runAction(CCSequence::create(increaseAction, NULL));
					this->scheduleOnce(schedule_selector(PlayGame::checkNewEat), 0);
					break;
				}
			}
			
		}
	}
}

void PlayGame::checkNewEat(float delayTime)
{
	eating = vector<Vertex>();
	for(int i=0; i<sizeof(PlayGame::pantemp[0])/sizeof(int)/(sizeof(PlayGame::pantemp[0][0])/sizeof(int)); i++)			//tile배치
	{
		for(int j=0; j<sizeof(PlayGame::pantemp[0][0])/sizeof(int); j++)
		{
			if(this->gamepan[i][j] == 0 || this->gamepan[i][j] == -1)
				continue;
			else
			{
				this->seleditem = this->gamepan[i][j];
				this->seledpos[0] = i;
				this->seledpos[1] = j;
			}
			int total = checkEat(i, j);				//이동후 먹을수 있는 돌세기
			if(total < 3)
				continue;
			vector<Vertex>::iterator iter1 = eatArr.begin();			//먹을수 있는 돌 터치는 효과
			for(; iter1!=eatArr.end(); iter1++)
			{
				bool hasOne = false;
				vector<Vertex>::iterator iter2 = eating.begin();
				for(; iter2!=eating.end(); iter2++)
				{
					if(iter1->row == iter2->row && iter1->col == iter2->col)
					{
						hasOne = true;
						break;
					}
				}
				if(!hasOne)
					eating.push_back(*iter1);
			}		
		}
	}

	if(eating.size()>=3)										//먹을수 있는 돌이 있으면
	{
		lock = true;
		vector<Vertex>::iterator iter = eating.begin();			//먹을수 있는 돌 터치는 효과
		for(; iter!=eating.end(); iter++)
		{
			this->particles[iter->row][iter->col] = CCParticleSun::create();
			this->particles[iter->row][iter->col]->setScaleX(0.1f*scaleX);
			this->particles[iter->row][iter->col]->setScaleY(0.1f*scaleY);
			this->particles[iter->row][iter->col]->setPosition(this->getPositionByij(iter->row, iter->col));
			this->addChild(particles[iter->row][iter->col], 9);

			CCActionInterval* explodeAction = CCScaleTo::create(0.5f, 1.5f*scaleX, 1.5f*scaleY);
			explodeAction->retain();
			this->particles[iter->row][iter->col]->runAction(CCSequence::create(explodeAction, NULL));
		}
		this->schedule(schedule_selector(PlayGame::checkAutoExplode));
	}
}

void PlayGame::checkAutoExplode(float deltaTime)
{
	if(eating.size() < 3)
	{
		this->unschedule(schedule_selector(PlayGame::checkAutoExplode));
		this->seleditem = 0;
		lock = false;
	}else
	{
		bool endf = false;
		vector<Vertex>::iterator iter = eating.begin();
		for(; iter!=eating.end(); iter++)
		{
			if(this->particles[iter->row][iter->col] != NULL)
			{
				endf = true;
				if(this->particles[iter->row][iter->col]->getScaleX() > 1.45f*scaleX)
				{
					this->removeChild(this->particles[iter->row][iter->col]);		//폭발효과제거
					this->particles[iter->row][iter->col] = NULL;

					this->removeChild(this->span[iter->row][iter->col]);			//보석제거
					this->span[iter->row][iter->col] = NULL;
					this->gamepan[iter->row][iter->col] = 0;

					/*if(PlayGame::pantemp[this->level][iter->row][iter->col] == -3)
					{*/
					if(this->tgrtls[iter->row][iter->col] != NULL)
					{
						this->removeChild(this->tgrtls[iter->row][iter->col]);
						this->tgrtls[iter->row][iter->col] = NULL;
					}
					//}
				}
			}
		}
		if(!endf)
		{
			this->unschedule(schedule_selector(PlayGame::checkAutoExplode));
			this->seleditem = 0;
			lock = false;
		}
	}
}

int PlayGame::checkEat(int row, int col)
{
	int eatC[3] = {1, 1, 1};					//1-4방, 2-5방, 3-6방먹은돌수
	int total = 0;								//전체먹은돌수
	eatArr = vector<Vertex>();

	if(this->seleditem != RAINBOW && this->seleditem != EXPLODE && this->seleditem != MINE)			//일반알먹기
	{
		eatArr.push_back(Vertex(row, col));
		int r = row, c = col;
		for(int i=1; i<=2; i++)                     //1방
		{
			if(c+1 < 19 && this->gamepan[r][c+1] == this->seleditem)
			{
				eatC[0] ++;
				eatArr.push_back(Vertex(r, c+1));
				c = c + 1;
			}else
				break;
		}
		r = row;
		c = col;
		for(int i=1; i<=2; i++)						//4방
		{
			if(c-1>=0 && gamepan[r][c-1] == this->seleditem)
			{
				eatC[0] ++;
				eatArr.push_back(Vertex(r, c-1));
				c = c - 1;
			}else
				break;
		}
		if(eatC[0]<3)				//먹을개수안되면 뽑아버리기
		{
			for(int i=0; i<eatC[0]-1; i++)
				eatArr.pop_back();
		}

		r = row;
		c = col;
		for(int i=1; i<=2; i++)						//2방
		{
			if(r+1<14 && c+r%2<19 && gamepan[r+1][c+r%2] ==  this->seleditem)
			{
				eatC[1] ++;
				eatArr.push_back(Vertex(r+1, c+r%2));
				c = c+r%2;
				r = r + 1;
			}else
				break;
		}
		r = row;
		c = col;
		for(int i=1; i<=2; i++)						//5방
		{
			if(r-1>=0 && c-(r+1)%2>=0 && gamepan[r-1][c-(r+1)%2] == this->seleditem)
			{
				eatC[1] ++;
				eatArr.push_back(Vertex(r-1, c-(r+1)%2));
				c = c-(r+1)%2;
				r = r - 1;
			}else
				break;
		}
		if(eatC[1]<3)							//먹을개수안되면 뽑아버리기
		{
			for(int i=0; i<eatC[1]-1; i++)
				eatArr.pop_back();
		}

		r = row;
		c = col;
		for(int i=1; i<=2; i++)						//3방
		{
			if(r+1<14 && c-(r+1)%2>=0 && gamepan[r+1][c-(r+1)%2] == this->seleditem)
			{
				eatC[2] ++;
				eatArr.push_back(Vertex(r+1, c-(r+1)%2));
				c = c - (r + 1) % 2;
				r = r + 1;
			}else
				break;
		}
		r = row;
		c = col;
		for(int i=1; i<=2; i++)						//6방
		{
			if(r-1>=0 && c+r%2<19 && gamepan[r-1][c+r%2] == this->seleditem)
			{
				eatC[2] ++;
				eatArr.push_back(Vertex(r-1, c+r%2));
				c = c + r % 2;
				r = r - 1;
			}else
				break;
		}
		if(eatC[2]<3)				//먹을개수안되면 뽑아버리기
		{
			for(int i=0; i<eatC[2]-1; i++)
				eatArr.pop_back();
		}
	}else if(this->seleditem == RAINBOW || this->seleditem == EXPLODE || this->seleditem == MINE)			//특수알먹기
	{
		eatArr.push_back(Vertex(row, col));		//전체배렬에 원점주입
		
		vector<Vertex> ver = vector<Vertex>();
		int r = row, c = col;						//4-1방
		if(c-2>0)
			ver.push_back(Vertex(r, c-2));
		if(c-1>0)
			ver.push_back(Vertex(r, c-1));
		if(c+1<19)
			ver.push_back(Vertex(r, c+1));
		if(c+2<19)
			ver.push_back(Vertex(r, c+2));
		for(unsigned int i=0; i<ver.size(); i++)
		{
			eatC[0] = 1;
			for(unsigned int j=i; j<ver.size(); j++)
			{
				if(this->gamepan[ver.at(i).row][ver.at(i).col] != 88 && this->gamepan[ver.at(i).row][ver.at(i).col] != 44 && this->gamepan[ver.at(i).row][ver.at(i).col] != 33 && this->gamepan[ver.at(i).row][ver.at(i).col] != 22 && this->gamepan[ver.at(i).row][ver.at(i).col] != 11 && this->gamepan[ver.at(i).row][ver.at(i).col] != 0 && this->gamepan[ver.at(i).row][ver.at(i).col] == this->gamepan[ver.at(j).row][ver.at(j).col])
					eatC[0] ++;
				else
					break;
			}
			if(eatC[0] >=3)
			{
				for(unsigned int j=i; j<=i+eatC[0]-2; j++)
					eatArr.push_back(Vertex(ver.at(j).row, ver.at(j).col));
				break;
			}
		}
		
		ver = vector<Vertex>();
		r = row;
		c = col;									//2-5방
		int r1, c1, r2, c2;
		c1 = c+r%2; r1 = r + 1;
		c2 = c1+r1%2; r2 = r1 + 1;
		if(r2<14 && c2<19)
			ver.push_back(Vertex(r2, c2));
		if(r1<14 && c1<19)
			ver.push_back(Vertex(r1, c1));
		c1 = c-(r+1)%2; r1 = r - 1;
		c2 = c1-(r1+1)%2; r2 = r1 - 1;
		if(c1>=0 && r1>=0)
			ver.push_back(Vertex(r1, c1));
		if(c2>=0 && r2>=0)
			ver.push_back(Vertex(r2, c2));
		for(unsigned int i=0; i<ver.size(); i++)
		{
			eatC[1] = 1;
			for(unsigned int j=i; j<ver.size(); j++)
			{
				if(this->gamepan[ver.at(i).row][ver.at(i).col] != 88 && this->gamepan[ver.at(i).row][ver.at(i).col] != 44 && this->gamepan[ver.at(i).row][ver.at(i).col] != 33 && this->gamepan[ver.at(i).row][ver.at(i).col] != 22 && this->gamepan[ver.at(i).row][ver.at(i).col] != 11 && this->gamepan[ver.at(i).row][ver.at(i).col] != 0 && this->gamepan[ver.at(i).row][ver.at(i).col] == this->gamepan[ver.at(j).row][ver.at(j).col])
					eatC[1] ++;
				else
					break;
			}
			if(eatC[1] >=3)
			{
				for(unsigned int j=i; j<=i+eatC[1]-2; j++)
					eatArr.push_back(Vertex(ver.at(j).row, ver.at(j).col));
				break;
			}
		}

		ver = vector<Vertex>();
		r = row;								//6-3방
		c = col;
		c1 = c + r % 2; r1 = r - 1;
		c2 = c1 + r1 % 2; r2 = r1 - 1;
		if(r2>=0 && c2<19)
			ver.push_back(Vertex(r2, c2));
		if(r1>=0 && c1<19)
			ver.push_back(Vertex(r1, c1));
		r = row;
		c = col;
		c1 = c-(r+1)%2;r1 = r+1;
		c2 = c1-(r1+1)%2;r2 = r1+1;
		if(r1<14 && c1>=0)
			ver.push_back(Vertex(r1, c1));
		if(r2<14 && c2>=0)
			ver.push_back(Vertex(r2, c2));
		for(unsigned int i=0; i<ver.size(); i++)
		{
			eatC[2] = 1;
			for(unsigned int j=i; j<ver.size(); j++)
			{
				if(this->gamepan[ver.at(i).row][ver.at(i).col] != 88 && this->gamepan[ver.at(i).row][ver.at(i).col] != 44 && this->gamepan[ver.at(i).row][ver.at(i).col] != 33 && this->gamepan[ver.at(i).row][ver.at(i).col] != 22 && this->gamepan[ver.at(i).row][ver.at(i).col] != 11 && this->gamepan[ver.at(i).row][ver.at(i).col] != 0 && this->gamepan[ver.at(i).row][ver.at(i).col] == this->gamepan[ver.at(j).row][ver.at(j).col])
					eatC[2] ++;
				else
					break;
			}
			if(eatC[2] >=3)
			{
				for(unsigned int j=i; j<=i+eatC[2]-2; j++)
					eatArr.push_back(Vertex(ver.at(j).row, ver.at(j).col));
				break;
			}
		}
	}

	bool first = true;
	maxEating = 0;
	for(int i=0; i<3; i++)			//전체먹은 알수 계산
	{
		if(eatC[i] >= 3)
		{
			if(eatC[i] > maxEating)
				maxEating = eatC[i];
			if(first)
			{
				first = false;
				total += eatC[i];
			}else
			{
				total += eatC[i] - 1;
			}
		}
	}
	if(total>=3 && started)
	{
		this->score += total*12;				//점수증가
		totalNum += total;
	}
	return total;
}

void PlayGame::checkExplode(float deltaTime)
{
	if(eatArr.size() < 3)
	{
		this->unschedule(schedule_selector(PlayGame::checkExplode));
		lock = false;
	}else
	{
		bool endf = false;
		vector<Vertex>::iterator iter = eatArr.begin();
		for(; iter!=eatArr.end(); iter++)
		{
			if(this->particles[iter->row][iter->col] != NULL)
			{
				endf = true;
				if(this->particles[iter->row][iter->col]->getScaleX() > 1.45f*scaleX)			//폭발끝
				{
					this->removeChild(this->particles[iter->row][iter->col]);		//폭발효과제거
					this->particles[iter->row][iter->col] = NULL;

					this->removeChild(this->span[iter->row][iter->col]);			//보석제거
					this->span[iter->row][iter->col] = NULL;
					this->gamepan[iter->row][iter->col] = 0;	
					pushed = false;					

					if(this->tgrtls[iter->row][iter->col] != NULL)
					{
						this->removeChild(this->tgrtls[iter->row][iter->col]);
						this->tgrtls[iter->row][iter->col] = NULL;
					}

					if(iter->row == this->tgrpos[0] && iter->col == this->tgrpos[1] && maxEating == 4)
					{
						this->gamepan[iter->row][iter->col] = MINE;	
						this->span[iter->row][iter->col] = CCSprite::create("mine.png");
						this->span[iter->row][iter->col]->setPosition(this->getPositionByij(iter->row, iter->col));
						this->span[iter->row][iter->col]->setScaleX(scaleX);
						this->span[iter->row][iter->col]->setScaleY(scaleY);
						this->addChild(this->span[iter->row][iter->col], 6);
					}else if(iter->row == this->tgrpos[0] && iter->col == this->tgrpos[1] && maxEating == 5)
					{
						this->gamepan[iter->row][iter->col] = EXPLODE;	
						this->span[iter->row][iter->col] = CCSprite::create("explode.png");
						this->span[iter->row][iter->col]->setPosition(this->getPositionByij(iter->row, iter->col));
						this->span[iter->row][iter->col]->setScaleX(scaleX);
						this->span[iter->row][iter->col]->setScaleY(scaleY);
						this->addChild(this->span[iter->row][iter->col], 6);
					}
				}
			}
		}
		if(!endf)
		{
			this->unschedule(schedule_selector(PlayGame::checkExplode));
			lock = false;
		}
	}
}

void PlayGame::placeGame()
{	
	for(int j=0; j<sizeof(this->gamepan[0])/sizeof(int); j++)
	{
		for(int i=0; i<sizeof(this->gamepan)/sizeof(int)/(sizeof(this->gamepan[0])/sizeof(int)); i++)			//tile배치
		{
			if(this->gamepan[i][j] == 0)
			{
				this->span[i][j] = NULL;
			}else
			{
				CCActionInterval* initAction= CCScaleTo::create(1.0f, 1.0f*scaleX, 1.0f*scaleY);
				initAction->retain();
				switch (this->gamepan[i][j])
				{
				case RED:
					this->span[i][j] = CCSprite::create("red.png");
					this->span[i][j]->setPosition(this->getPositionByij(i, j));
					this->span[i][j]->setScaleX(1.5f*scaleX);
					this->span[i][j]->setScaleY(1.5f*scaleY);
					this->addChild(this->span[i][j], 6);
					this->span[i][j]->runAction(CCSequence::create(initAction, NULL));
					break;
				case BLUE:
					this->span[i][j] = CCSprite::create("blue.png");
					this->span[i][j]->setPosition(this->getPositionByij(i, j));
					this->span[i][j]->setScaleX(1.5f*scaleX);
					this->span[i][j]->setScaleY(1.5f*scaleY);
					this->addChild(this->span[i][j], 6);
					this->span[i][j]->runAction(CCSequence::create(initAction, NULL));
					break;
				case GREEN:
					this->span[i][j] = CCSprite::create("green.png");
					this->span[i][j]->setPosition(this->getPositionByij(i, j));
					this->span[i][j]->setScaleX(1.5f*scaleX);
					this->span[i][j]->setScaleY(1.5f*scaleY);
					this->addChild(this->span[i][j], 6);
					this->span[i][j]->runAction(CCSequence::create(initAction, NULL));
					break;
				case CYAN:
					this->span[i][j] = CCSprite::create("cyan.png");
					this->span[i][j]->setPosition(this->getPositionByij(i, j));
					this->span[i][j]->setScaleX(1.5f*scaleX);
					this->span[i][j]->setScaleY(1.5f*scaleY);
					this->addChild(this->span[i][j], 6);
					this->span[i][j]->runAction(CCSequence::create(initAction, NULL));
					break;
				case RAINBOW:
					this->span[i][j] = CCSprite::create("rainbow.png");
					this->span[i][j]->setPosition(this->getPositionByij(i, j));
					this->span[i][j]->setScaleX(1.5f*scaleX);
					this->span[i][j]->setScaleY(1.5f*scaleY);
					this->addChild(this->span[i][j], 6);
					this->span[i][j]->runAction(CCSequence::create(initAction, NULL));
					break;
				}
			}
		}
	}

}

CCPoint PlayGame::getPositionByij(int row, int col)
{
	if(row%2 == 0)		//even:짝수
	{
		return ccp(origin.x+this->le+this->dw+this->bw*col, origin.y+this->top-(this->bh/2+(this->bh+this->bh/2)*(row/2)));
	}else
	{
		return ccp(origin.x+this->le+this->bw*(col+1), origin.y+this->top-(this->dh*5+this->dh*6*((row-1)/2)));	
	}
}

void PlayGame::initGame()										//게임초기화
{
	if(continueGame)
		this->level = CCUserDefault::sharedUserDefault()->getIntegerForKey("arabesque_level", 0);
	else
		this->level = 0;
		pushed = false;

	this->levellab = CCLabelTTF::create(CCString::createWithFormat("%d", (this->level+1))->getCString(), "Marker Felt", 20);
	this->levellab->setPosition(ccp(origin.x+vSize.width*0.7/10, origin.y+vSize.height*7.87/10));
	this->levellab->setScaleX(scaleX);
	this->levellab->setScaleY(scaleY);
	this->addChild(this->levellab, 1);

	this->score = CCUserDefault::sharedUserDefault()->getIntegerForKey("arabesque_score", 0);
	this->scorelab = CCLabelTTF::create(CCString::createWithFormat("%d", (this->score))->getCString(), "Marker Felt", 20);
	this->scorelab->setPosition(ccp(origin.x+vSize.width*1/10, origin.y+vSize.height*9.525/10));
	this->scorelab->setScaleX(scaleX);
	this->scorelab->setScaleY(scaleY);
	this->addChild(this->scorelab, 1);

	this->lives = CCUserDefault::sharedUserDefault()->getIntegerForKey("arabesque_lives", 3);
	this->liveslab = CCLabelTTF::create(CCString::createWithFormat("%d", (this->lives))->getCString(), "Marker Felt", 20);
	this->liveslab->setPosition(ccp(origin.x+vSize.width*0.85/10, origin.y+vSize.height*8.7/10));
	this->liveslab->setScaleX(scaleX);
	this->liveslab->setScaleY(scaleY);
	this->addChild(this->liveslab, 1);

	this->le = vSize.width*0.02f;
	this->top = vSize.height*0.97f;
	this->ri = vSize.width;
	this->bot = 0;
	CCSprite* tmp = CCSprite::create("tile1.png");
	this->bw = tmp->getContentSize().width*scaleX;
	this->bh = tmp->getContentSize().height*scaleY;
	this->dw = this->bw/2;
	this->dh = this->bh/4;

	srand(time(NULL));
	for(int i=0; i<sizeof(PlayGame::pantemp[0])/sizeof(int)/(sizeof(PlayGame::pantemp[0][0])/sizeof(int)); i++)			//tile배치
	{
		for(int j=0; j<sizeof(PlayGame::pantemp[0][0])/sizeof(int); j++)
		{
			this->particles[i][j] = NULL;
			this->mpan[i][j] = NULL;
			this->tgrtls[i][j] = NULL;					//목표타일초기화

			this->gamepan[i][j] = PlayGame::pantemp[level][i][j];
			this->gametile[i][j] = PlayGame::pantemp[level][i][j];
			if(PlayGame::pantemp[this->level][i][j] == -1){					//빈공간만들기
				this->tiles[i][j] = NULL;
				continue;
			}

			if(PlayGame::pantemp[this->level][i][j] == -3)
			{
				this->gamepan[i][j] = 0;
				this->tgrtls[i][j] = CCSprite::create("tile2.png");
				this->tgrtls[i][j]->setPosition(this->getPositionByij(i, j));
				this->tgrtls[i][j]->setScaleX(scaleX);
				this->tgrtls[i][j]->setScaleY(scaleY);
				this->addChild(this->tgrtls[i][j], 2);
			}

			this->tiles[i][j] = CCSprite::create("tile1.png");
			this->tiles[i][j]->setPosition(this->getPositionByij(i, j));
			this->tiles[i][j]->setScaleX(scaleX);
			this->tiles[i][j]->setScaleY(scaleY);
			this->addChild(this->tiles[i][j], 1);
			
			this->gamepan[i][j] = rand()%10;
			if(!(this->gamepan[i][j]>=1 && this->gamepan[i][j]<=4))
			{
				if(this->gamepan[i][j] == 5)			//special		
				{
					this->gamepan[i][j] = rand()%11;
					if(this->gamepan[i][j] != RAINBOW)
						this->gamepan[i][j] = 0;
				}
				else
				{
					this->gamepan[i][j] = 0;
				}
			}
		}
	}
	
	for(int i=0; i<sizeof(PlayGame::pantemp[0])/sizeof(int)/(sizeof(PlayGame::pantemp[0][0])/sizeof(int)); i++)
	{
		for(int j=0; j<sizeof(PlayGame::pantemp[0][0])/sizeof(int); j++)
		{

			this->seleditem = this->gamepan[i][j];
			if(this->seleditem != -1)
			{
				int total = this->checkEat(i, j);
				if(total>=3)
				{
					for(int k=0; k<total; k++)
					{
						this->gamepan[eatArr.at(k).row][eatArr.at(k).col] = 0;
					}
				}
			}
			
		}
	}
	this->seleditem = 0;
}

void PlayGame::onMainmenu(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("btn_click.wav");
	CCScene* s = new CCScene();
	CCLayer* g = new MainMenu();
	g->init();
	s->addChild(g);
	CCScene* pScene = createTransitionL(TRANSITION_DURATION, s);
	s->release();
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

			/////////////////////////////////    Vertex   /////////////////////////////////////////

Vertex::Vertex(int rw, int cl)
{
	this->row = rw;
	this->col = cl;
}

Vertex::Vertex()
{
	this->row = 0;
	this->col = 0;
}
			////////////////////////////////   Top7Layer   //////////////////////////////////////////  (Accomplished)

CCScene* Top7Layer::scene()
{
	CCScene *scene = CCScene::create();
	Top7Layer *layer = Top7Layer::create();
	scene->addChild(layer);
	return scene;
}

bool Top7Layer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	CCSprite* top7back = CCSprite::create("topscore.png");
	top7back->setPosition(ccp(origin.x+top7back->getContentSize().width/2*scaleX, origin.y+top7back->getContentSize().height/2*scaleY));
	top7back->setScaleX(scaleX);
	top7back->setScaleY(scaleY);
	this->addChild(top7back, 0);

	CCMenuItemImage* closeitem = CCMenuItemImage::create("cancel.png", "cancel_d.png", this, menu_selector(HelpLayer::onCancel));		//close메뉴
	closeitem->setPosition(ccp(origin.x+vSize.width*6/8, origin.y+vSize.height/7));
	closeitem->setScaleX(scaleX);
	closeitem->setScaleY(scaleY);

	CCMenu* pMenu = CCMenu::create(closeitem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 2);

	// 점수 얻어 표시
	int score[7];
	for(int i=0; i<7; i++)
		score[i] = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("arabesque_score%d", i)->getCString(), 0);
	for(int i=0; i<7; i++){
		for(int j=i; j<7; j++)
		{
			if(score[i]<score[j])
			{
				int tmp = score[i];
				score[i] = score[j];
				score[j] = tmp;
			}
		}
	}
	for(int i=0; i<7; i++)
	{
		CCLabelTTF* scorelab = CCLabelTTF::create(CCString::createWithFormat("%d", score[i])->getCString(), "Marker Felt", 20);
		scorelab->setPosition(ccp(origin.x+vSize.width*0.7f, origin.y+vSize.height*(1.0f-16.8f/21.2f)+(6-i)*10.2f/21.2f*vSize.height/6));
		scorelab->setScaleX(scaleX);
		scorelab->setScaleY(scaleY);
		this->addChild(scorelab, 2);
	}
	return true;
}

			////////////////////////////////   HelpLayer   ////////////////////////////////////////// (Accomplished)

CCScene* HelpLayer::scene()
{
	CCScene *scene = CCScene::create();
	HelpLayer *layer = HelpLayer::create();
	scene->addChild(layer);
	return scene;
}

bool HelpLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	this->state = RULES;

	this->helpback = CCSprite::create("help_rules.png");
	this->helpback->setPosition(ccp(origin.x+this->helpback->getContentSize().width/2*scaleX, origin.y+this->helpback->getContentSize().height/2*scaleY));
	this->helpback->setScaleX(scaleX);
	this->helpback->setScaleY(scaleY);
	this->addChild(this->helpback, 0);

	CCMenuItemImage* closeitem = CCMenuItemImage::create("close.png", "close_d.png", this, menu_selector(HelpLayer::onCancel));
	closeitem->setPosition(ccp(origin.x+vSize.width*5/7, origin.y+vSize.height/7));
	closeitem->setScaleX(scaleX);
	closeitem->setScaleY(scaleY);

	this->nextitem = CCMenuItemImage::create("next.png", "next_d.png", this, menu_selector(HelpLayer::onNextPage));
	this->nextitem->setPosition(ccp(origin.x+vSize.width*2.0f/5.0f, origin.y+vSize.height/7.3f));
	this->nextitem->setScaleX(scaleX);
	this->nextitem->setScaleY(scaleY);

	this->previtem = CCMenuItemImage::create("prev.png", "prev_d.png", this, menu_selector(HelpLayer::onPrevPage));
	this->previtem->setPosition(ccp(origin.x+vSize.width/3.7f, origin.y+vSize.height/7.3f));
	this->previtem->setScaleX(scaleX);
	this->previtem->setScaleY(scaleY);

	CCMenu* pMenu = CCMenu::create(this->nextitem, this->previtem, closeitem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 2);

	this->previtem->setVisible(false);

	return true;
}

void HelpLayer::onNextPage(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("btn_click.wav");
	this->helpback = CCSprite::create("help_bonus.png");
	this->helpback->setPosition(ccp(origin.x+this->helpback->getContentSize().width/2*scaleX, origin.y+this->helpback->getContentSize().height/2*scaleY));
	this->helpback->setScaleX(scaleX);
	this->helpback->setScaleY(scaleY);
	this->addChild(this->helpback, 0);
	this->nextitem->setVisible(false);
	this->previtem->setVisible(true);
}

void HelpLayer::onPrevPage(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("btn_click.wav");
	this->helpback = CCSprite::create("help_rules.png");
	this->helpback->setPosition(ccp(origin.x+this->helpback->getContentSize().width/2*scaleX, origin.y+this->helpback->getContentSize().height/2*scaleY));
	this->helpback->setScaleX(scaleX);
	this->helpback->setScaleY(scaleY);
	this->addChild(this->helpback, 0);
	this->nextitem->setVisible(true);
	this->previtem->setVisible(false);
}

void HelpLayer::onCancel(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("btn_click.wav");
	CCScene* s = new CCScene();
	CCLayer* g = new MainMenu();
	g->init();
	s->addChild(g);
	CCScene* pScene = createTransitionL(TRANSITION_DURATION, s);
	s->release();
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}
