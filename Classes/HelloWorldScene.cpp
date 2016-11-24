#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#define  TRANSITION_DURATION (0.5f)

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;


CCSize vSize;				
CCPoint origin;				
float scaleX, scaleY;		
int tmprow, tmpcol;			
const int RED = 1, BLUE = 2, GREEN = 3, CYAN = 4, RAINBOW = 8, EXPLODE = 9, MINE = 10;
int PlayGame::pantemp[][14][19] =			
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
vector<Vertex> path;			
vector<Vertex> eatArr;			
int pathpan[14][19];			
bool success;					
int weight;						
bool lock;						
bool started;
bool gameover;					
vector<Vertex> eating;
int maxEating;					
CCParticleSun* mineExp[300];	
Vertex mineVer[300];			
CCParticleSun* explodePtl;		
int totalNum;					
int startTime;					
int endTime;					
bool continueGame;				
bool pushed;					

int posxy[2];					

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
	if(openGame->getScaleX()>0.95f*scaleX && openGame->getScaleY()>0.98f*scaleY)	
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

	this->seleditem = 0;			
	lock = false;					
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

	if(!life)				
	{
		this->lives --;
		if(this->lives>=0)			
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
	
	if(!gameover && tgrtotal == 0)				
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
		for(int i=0; i<7; i++)						
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
			if(this->tiles[i][j] != NULL && this->rect(i, j).containsPoint(location))			
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

void PlayGame::findMinPath(int fr, int fc, int er, int ec)			
{
	int pr[100], pc[100];	
	int cr[100], cc[100];	
	memset(cr, -1, 100);
	memset(cc, -1, 100);
	cr[0] = fr;
	cc[0] = fc;
	weight = 2;
	while(true)
	{
		memcpy(pr, cr, 100);			
		memcpy(pc, cc, 100);
		memset(cr, -1, 100);			
		memset(cc, -1, 100);
		int cnt = 0;
		for(int i=0; i<100; i++)		
		{
			if(pr[i] == -1 && pc[i] == -1)
				break;
			if(pc[i]+1 < 19 && pathpan[pr[i]][pc[i]+1] == 0)									   6
			{							
				pathpan[pr[i]][pc[i]+1] = weight;													4	0	1	
				if(pr[i]==er && pc[i]+1==ec)														  3   2
				{
					success = true;
					return;
				}		
				cr[cnt] = pr[i];
				cc[cnt] = pc[i]+1;
				cnt++;
			}
			if(pr[i]+1<14 && pc[i]+pr[i]%2<19 && pathpan[pr[i]+1][pc[i]+pr[i]%2] == 0)			
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
			if(pr[i]+1<14 && pc[i]-(pr[i]+1)%2>=0 && pathpan[pr[i]+1][pc[i]-(pr[i]+1)%2] == 0)	
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
			if(pc[i]-1>=0 && pathpan[pr[i]][pc[i]-1] == 0)														
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
			if(pr[i]-1>=0 && pc[i]-(pr[i]+1)%2>=0 && pathpan[pr[i]-1][pc[i]-(pr[i]+1)%2] == 0)	
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
			if(pr[i]-1>=0 && pc[i]+pr[i]%2<19 && pathpan[pr[i]-1][pc[i]+pr[i]%2] == 0)			
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
			if(gem)							
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

				if(this->particles[row][col] == NULL)		
				{
					this->particles[row][col] = CCParticleSun::create();
					this->particles[row][col]->setEmissionRate(25);
					this->particles[row][col]->setScaleX(0.7f*scaleX);
					this->particles[row][col]->setScaleY(0.7f*scaleY);
					this->particles[row][col]->setPosition(this->getPositionByij(row, col));
					this->addChild(this->particles[row][col], 9);
				}
			}else                          
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
						this->removeChild(this->mpan[i][j]);		
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
			if(row != tmprow || col != tmpcol)							
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

				for(int i=0; i<sizeof(PlayGame::pantemp[0])/sizeof(int)/(sizeof(PlayGame::pantemp[0][0])/sizeof(int)); i++)	
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
				while(sw>1)									
				{
					sw --;
					if(sc+1 < 19 && pathpan[sr][sc+1] == sw)												
					{							
						path.push_back(Vertex(sr, sc+1));
						sc = sc+1;
						sr = sr;
						continue;
					}
					if(sr+1<14 && sc+sr%2<19 && pathpan[sr+1][sc+sr%2] == sw)				
					{
						path.push_back(Vertex(sr+1, sc+sr%2));
						sc = sc+sr%2;
						sr = sr+1;
						continue;
					}
					if(sr+1<14 && sc-(sr+1)%2>=0 && pathpan[sr+1][sc-(sr+1)%2] == sw)		
					{
						path.push_back(Vertex(sr+1, sc-(sr+1)%2));
						sc = sc-(sr+1)%2;
						sr = sr+1;
						continue;
					}
					if(sc-1>=0 && pathpan[sr][sc-1] == sw)															
					{
						path.push_back(Vertex(sr, sc-1));
						sc = sc-1;
						sr = sr;
						continue;
					}
					if(sr-1>=0 && sc-(sr+1)%2>=0 && pathpan[sr-1][sc-(sr+1)%2] == sw)		
					{
						path.push_back(Vertex(sr-1, sc-(sr+1)%2));
						sc = sc-(sr+1)%2;
						sr = sr-1;
						continue;
					}	
					if(sr-1>=0 && sc+sr%2<19 && pathpan[sr-1][sc+sr%2] == sw)				
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
			if(!gem && success)							
			{
				SimpleAudioEngine::sharedEngine()->playEffect("unselect.wav");
				lock = true;
				CCPointArray *ptArray = CCPointArray::create(path.size()+2);			
				for(unsigned int i=0; i<path.size(); i++)
					ptArray->addControlPoint(this->getPositionByij(path.at(i).row, path.at(i).col));
				ptArray = ptArray->reverse();
				CCPoint tmppoint = this->getPositionByij(this->seledpos[0], this->seledpos[1]);
				ptArray->insertControlPoint(tmppoint, 0);
				ptArray->addControlPoint(this->getPositionByij(row, col));
				CCCatmullRomTo *moveAction = CCCatmullRomTo::create(0.08f*ptArray->count(), ptArray);			
				CCSequence *seq = CCSequence::create(moveAction, NULL);
				this->span[this->seledpos[0]][this->seledpos[1]]->runAction(seq);
				this->schedule(schedule_selector(PlayGame::checkMove), 0.001f);				
			}else
			{
				SimpleAudioEngine::sharedEngine()->playEffect("unselect.wav");
				this->removeChild(this->mpan[row][col]);	
				this->mpan[row][col] = NULL;
			}
		}else
		{
			this->seleditem = 0;
			for(int i=0; i<sizeof(PlayGame::pantemp[0])/sizeof(int)/(sizeof(PlayGame::pantemp[0][0])/sizeof(int)); i++)	
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
						this->removeChild(this->mpan[i][j]);		
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
	if(rw == tgrpos[0] && co == tgrpos[1])			
	{
		this->removeChild(this->mpan[tgrpos[0]][tgrpos[1]]);	
		this->mpan[tgrpos[0]][tgrpos[1]] = NULL;

		this->removeChild(this->span[this->seledpos[0]][this->seledpos[1]]);	
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
		}	return true;
	}
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
