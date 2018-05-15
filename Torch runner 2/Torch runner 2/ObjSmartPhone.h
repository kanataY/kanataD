#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：スマホ少年
class CObjSmartphone : public CObj
{
public:
	CObjSmartphone(int x, int y);
	~CObjSmartphone() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	void HitBox();  //HitBox関連
	float GetX() { return m_px; }//m_px,m_pyの値を渡す
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }//m_vx,m_vyの値を渡す
	float GetVX() { return m_vx; }

private:
	float m_px;		//位置
	float m_py;
	float m_vx;		//移動量
	float m_vy;
	int   m_time;     //タイム
	bool  m_middle;  //真ん中にいないかしらべる変数

	int m_time_fire;     //タイム

	//制御系
	bool m_fire_control; //火が付いた時の制御

	//-アニメーション
	int m_ani_time; //アニメーションフレーム動作感覚
	int m_ani_frame;//描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値
};
