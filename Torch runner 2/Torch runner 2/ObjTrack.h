#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ゲージ
class CObjTrack : public CObj
{
public:
	CObjTrack(int x, int y);
	~CObjTrack() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	float GetX() { return m_px; }
	float GetY() { return m_py; }
	void  SetX(float x) { m_px = x; }
	void  SetY(float y) { m_py = y; }
	void HitBox();  //HitBox関連

private:
	float m_px;		//位置
	float m_py;

	float m_vx;		//移動量
	float m_vy;

	int m_rx;		//最初の位置を記憶する
	int m_ry;

	int m_ani_change; //描画を変える用の変数

	int   m_time_warning; //警告出してるタイム

	int m_ani_time; //アニメーションフレーム動作感覚
	int m_ani_frame;//描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値

};