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

	int  GetMap(int x, int y);//マップ情報の取得
	void  SetMap(int x, int y, int m) { m_map[y][x] = m; }
	

private:
	float m_px;		//位置
	float m_py;
	int m_map[10][MAP_X_MAX];//マップ情報
	int m_map_Record[10][MAP_X_MAX];//マップ情報記録役
};