#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;



class MainMenu : public cocos2d::CCLayer		
{
public:
	CCSprite* openGame;						
	CCMenuItemImage* continueMenu;
	CCMenuItemImage* newMenu;
	CCMenuItemImage* closeMenu;
	CCMenu* pm;								
	CCLabelTTF* level;	

	virtual bool init();  
	static cocos2d::CCScene* scene();
    void onExitGame(CCObject* pSender);		
	void onHelp(CCObject* pSender);			
	void onTop7(CCObject* pSender);			
	void onPlayGame(CCObject* pSender);		
	void openPlayGame();					
	void checkScale(float delayTime);		
	void onNew(CCObject* pSender);			
	void onContinue(CCObject* pSender);		
	void onCancel(CCObject* pSender);		
    CREATE_FUNC(MainMenu);
};

class HelpLayer : public cocos2d::CCLayer	
{
public:
	static const int RULES = 1, BONUS = 2;

	cocos2d::CCSprite* helpback;			
	cocos2d::CCMenuItemImage* nextitem;		
	cocos2d::CCMenuItemImage* previtem;
	int state;								

	virtual bool init();
	static cocos2d::CCScene* scene();

	void onCancel(CCObject* pSender);		
	void onNextPage(CCObject* pSender);		
	void onPrevPage(CCObject* pSender);		
	
	CREATE_FUNC(HelpLayer);
};

class Top7Layer : public cocos2d::CCLayer	
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();

	CREATE_FUNC(Top7Layer);
};

class PlayGame : public cocos2d::CCLayer			//PlayGame
{
public:
	int level;
	int lives;
	int score;
	float bw, bh, dw, dh;		
	float le, top, ri, bot;		
	static int pantemp[][14][19];	
	int gamepan[14][19];			
	int gametile[14][19];			
	int selx, sely;					
	int seleditem;					
	int seledpos[2];				
	int tgrpos[2];					

	CCSprite* span[14][19];			
	CCSprite* tiles[14][19];		
	CCSprite* tgrtls[14][19];		
	CCLabelTTF* levellab;			
	CCLabelTTF* liveslab;			
	CCLabelTTF* scorelab;			
	CCParticleSun* particles[14][19];			
	CCSprite* mpan[14][19];			
	CCSprite* nextLevel;			
	
	virtual bool init();
	static cocos2d::CCScene* scene();
	void initGame();								
	void placeGame();								
	CCPoint getPositionByij(int row, int col);		
	void getIJByPosition(CCPoint location);			
	CCRect rect(int row, int col);					
	int isGem(int row, int col);					
	void findMinPath(int fr, int fc, int er, int ec);	
	void checkMove(float delayTime);					
	int checkEat(int row, int col);						
	void checkExplode(float delayTime);					
	void checkAutoExplode(float delayTime);			
	void makeNewItems();								
	void checkNewEat(float delayTime);				
	void realCheck(float delayTime);					
	void checkMineExp(float delayTime);					
	void monitorExplode(float delayTime);				
	void destoryVShape(int row, int col);				
	void destoryAShape(int row, int col);				
	void nextLev(float delayTime);						

	void onMainmenu(CCObject* pSender);				
	CREATE_FUNC(PlayGame);

	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
};

class Vertex										
{
public:
	int row, col;
	Vertex(int rw, int cl);
	Vertex();
};

#endif // __HELLOWORLD_SCENE_H__
