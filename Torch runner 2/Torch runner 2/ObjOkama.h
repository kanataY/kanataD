#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：オカマ
class CObjOkama : public CObj
{
public:
	CObjOkama(int x, int y);
	~CObjOkama() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	void HitBox();  //HitBox関連
	float GetX() { return m_px; }//m_px,m_pyの値を渡す
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }//m_vx,m_vyの値を渡す
	float GetVX() { return m_vx; }
	bool  GetHug() { return m_hug; } //抱きついているかどうかを渡す
	int   GetRebagacha() { return m_rebagacha; } //レバガチャの回数を渡す
	void  SetCratesHit(int c) { m_crates_hit = c; }//m_px,m_pyの値をほかのcppでもいじれるようにする

private:
	float m_px;		//位置
	float m_py;
	float m_vx;		//移動量
	float m_vy;
	int   m_time;     //タイム
	int   m_time_warning; //警告出してるタイム
	int   m_time_hole;     //穴を回避するタイム
	bool  m_hole_out;
	float ar;
	int  m_rebagacha;//レバガチャ
	int  m_r_time;   //レバガチャした後の後ずさる距離に使う
	int m_time_fire;     //タイム
	bool m_hug;  //抱きついたか調べる変数
	bool m_avoidance;       //回避したかどうかを入れる変数
	int  m_avoidance_time;  //回避するときのタイムで管理する。
	int  m_crates_hit;      //木箱のどこに当たったかを調べる変数
	bool m_crates_vy;       //木箱に当たった際に移動するYの量を一定にするための変数
	//制御系
	bool m_fire_control; //火が付いた時の制御
	bool m_homing;       //ホーミングする回数を制御
	bool m_rebagacha_cotrol_r; // Rレバガチャを制御
	bool m_rebagacha_cotrol_l; // Lレバガチャを制御
	bool m_rebagacha_cotrol_u; // Uレバガチャを制御
	bool m_rebagacha_cotrol_d; // Dレバガチャを制御
	bool m_crates_jamp; //木箱をジャンプして回避

	//-アニメーション
	int m_ani_time; //アニメーションフレーム動作感覚
	int m_ani_frame;//描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値
	int m_ani_key_time; //キーボードのアニメーションフレーム動作感覚
	int m_ani_key_frame;//キーボードの描画フレーム
	float m_ani_key_max_time;   //キーボードのアニメーション動作間隔最大値
};
