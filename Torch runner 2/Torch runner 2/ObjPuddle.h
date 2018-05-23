#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：水たまり
class CObjPuddle : public CObj
{
public:
	CObjPuddle(int x, int y);
	~CObjPuddle() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	void HitBox();  //当たり判定関連
	float GetX() { return m_px; }
	float GetY() { return m_py; }
	void  SetX(float x) { m_px = x; }
	void  SetY(float y) { m_py = y; }

private:
	float m_px;		//位置
	float m_py;
	int m_rx;		//最初の位置を記憶する
	int m_ry;

	bool m_map_con;  //マップ読み込みを一回だけにする
	int m_drow_down; //画像の下を伸ばす。
};