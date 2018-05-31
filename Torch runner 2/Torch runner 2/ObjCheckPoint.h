#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：チェックポイント
class CObjCheckPoint : public CObj
{
public:
	CObjCheckPoint(int x, int y);
	~CObjCheckPoint() {};
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
	float m_vx;			//移動ベクトル
	float m_vy;
	float m_pos;    //立ち位置
	int   m_time; //後ろに向くさいの時間管理

	//-アニメーション
	int m_ani_time; //アニメーションフレーム動作感覚
	int m_ani_frame;//描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値
	int m_ani_change; //アニメーション変更変数
};