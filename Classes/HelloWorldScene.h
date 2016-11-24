#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;



class MainMenu : public cocos2d::CCLayer		//MainMenu
{
public:
	CCSprite* openGame;						//게임열기창
	CCMenuItemImage* continueMenu;
	CCMenuItemImage* newMenu;
	CCMenuItemImage* closeMenu;
	CCMenu* pm;								//게임시작메뉴
	CCLabelTTF* level;	

	virtual bool init();  
	static cocos2d::CCScene* scene();
    void onExitGame(CCObject* pSender);		//끝내기
	void onHelp(CCObject* pSender);			//도움말
	void onTop7(CCObject* pSender);			//최고기록
	void onPlayGame(CCObject* pSender);		//게임시작
	void openPlayGame();					//게임열기
	void checkScale(float delayTime);		//창커지기감시
	void onNew(CCObject* pSender);			//새게임
	void onContinue(CCObject* pSender);		//련이어
	void onCancel(CCObject* pSender);		
    CREATE_FUNC(MainMenu);
};

class HelpLayer : public cocos2d::CCLayer			//HelpLayer
{
public:
	static const int RULES = 1, BONUS = 2;

	cocos2d::CCSprite* helpback;				//배경
	cocos2d::CCMenuItemImage* nextitem;			//다음, 뒤로
	cocos2d::CCMenuItemImage* previtem;
	int state;									//도움말상태

	virtual bool init();
	static cocos2d::CCScene* scene();

	void onCancel(CCObject* pSender);		//되돌이
	void onNextPage(CCObject* pSender);			//다음
	void onPrevPage(CCObject* pSender);			//이전
	
	CREATE_FUNC(HelpLayer);
};

class Top7Layer : public cocos2d::CCLayer			//Top7Layer
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
	float bw, bh, dw, dh;		//블로크규격
	float le, top, ri, bot;		//게임판위치, 규격
	static int pantemp[][14][19];	//회전별모양
	int gamepan[14][19];			//게임상태
	int gametile[14][19];			//타일모임
	int selx, sely;					//selected row, col
	int seleditem;					//선택된 객체
	int seledpos[2];				//선택된 객체위치
	int tgrpos[2];					//목적한 이동위치

	CCSprite* span[14][19];			//상태에 따른는 sprite배렬
	CCSprite* tiles[14][19];		//배경타일
	CCSprite* tgrtls[14][19];		//없애야될 타일
	CCLabelTTF* levellab;			//회전표시
	CCLabelTTF* liveslab;			//목숨표시
	CCLabelTTF* scorelab;			//점수표시
	CCParticleSun* particles[14][19];				//현시되는 효과
	CCSprite* mpan[14][19];			//끌기시 표시되는 판
	CCSprite* nextLevel;			//회전끝
	
	virtual bool init();
	static cocos2d::CCScene* scene();
	void initGame();								//초기화
	void placeGame();								//돌배치
	CCPoint getPositionByij(int row, int col);		//위치얻기
	void getIJByPosition(CCPoint location);			//row, col얻기
	CCRect rect(int row, int col);					//tile의 rect얻기
	int isGem(int row, int col);					//빈칸이 아닌가?
	void findMinPath(int fr, int fc, int er, int ec);	//최단경로찾기
	void checkMove(float delayTime);					//이동감시
	int checkEat(int row, int col);						//먹을돌감시
	void checkExplode(float delayTime);					//폭발감시
	void checkAutoExplode(float delayTime);					//자동폭발감시
	void makeNewItems();								//새로운 보석만들기
	void checkNewEat(float delayTime);									//커진 보석들중에 먹을수 있는것 없애기
	void realCheck(float delayTime);					//실시간 감시기
	void checkMineExp(float delayTime);					//지뢰파편이 목표점에 도달하는가 검사
	void monitorExplode(float delayTime);				//대폭발감시
	void destoryVShape(int row, int col);				//V자모양폭발
	void destoryAShape(int row, int col);				//A자모양
	void nextLev(float delayTime);						//회전넘김

	void onMainmenu(CCObject* pSender);				//mainmenu단추
	CREATE_FUNC(PlayGame);

	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
};

class Vertex										//정점클라스
{
public:
	int row, col;
	Vertex(int rw, int cl);
	Vertex();
};

#endif // __HELLOWORLD_SCENE_H__
