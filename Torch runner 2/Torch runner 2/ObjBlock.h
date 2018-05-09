#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//マクロ　
#define MAP_X_MAX 200

//オブジェクト：ブロック＆背景
class CObjBlock : public CObj
{
public:
	CObjBlock(int map[10][MAP_X_MAX]);
	~CObjBlock() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	
	void  SetScroll(float s) { m_scroll = s; }
	float GetScroll() { return m_scroll; }

	void  SetMap(int x, int y, int m) { m_map[y][x] = m; }


private:
	float m_px;		//位置
	float m_py;
	float m_bx1;     //背景の動く値
	float m_bx2;     //背景の動く値2
	
	float m_scroll; //スクロール位置

	int m_map[10][MAP_X_MAX];//マップ情報
};