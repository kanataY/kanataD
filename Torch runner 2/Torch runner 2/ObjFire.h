#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：炎
class CObjFire : public CObj
{
public:
	CObjFire(float x, float y, int b);
	~CObjFire() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	float GetX() { return m_px; }
	float GetY() { return m_py; }
	void  SetX(float x) { m_px = x; }
	void  SetY(float y) { m_py = y; }

private:
	float m_px;		//位置
	float m_py;
	int   m_time;   //タイム
	int  m_fire_hit; //0：一般的なもの　１：オカマ　２：ランナー

	int m_ani_time; //アニメーションフレーム動作感覚
	int m_ani_frame;//描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値
};