#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：穴
class CObjHole : public CObj
{
public:
	CObjHole(int x, int y);
	~CObjHole() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	void HitBox();  //当たり判定関連
	float GetX() { return m_px; }
	float GetY() { return m_py; }
	int   GetDrowDown() { return m_drow_down; } //穴が何個分広がっているか調べる
	bool  GetHoleFall() { return m_hole_fall; } //穴にランナーが落ちているかどうかを返す
	void  SetX(float x) { m_px = x; }
	void  SetY(float y) { m_py = y; }

private:
	float m_px;		//位置
	float m_py;
	int m_rx;		//最初の位置を記憶する
	int m_ry;
	bool m_hole_fall;

	bool m_map_con;  //マップ読み込みを一回だけにする
	int m_drow_down; //画像の下を伸ばす。
};