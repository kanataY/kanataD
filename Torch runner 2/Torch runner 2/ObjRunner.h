#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ランナー
class CObjRunner : public CObj
{
public:
	CObjRunner(int r);
	~CObjRunner() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	void HitBox();  //当たり判定関連
	float GetX() { return m_px; }						//m_px,m_pyの値を渡す
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }						//m_vx,m_vyの値を渡す
	float GetVX() { return m_vx; }
	int   GetInvincible() { return m_invincible; }		//無敵時間の値を渡す
	bool  GetHoleFallCon(){ return m_hole_control; }	//穴に落ちている情報を渡す
	bool  GetCheckPoint() { return m_check_control; }	//チェックポイントに当たっているかどうかの情報を渡す
	int   GetCheckTime()  { return m_check_time; }		//チェックポイントに当たってからのタイムを渡す。
	bool  GetCheckTransfer() { return m_check_transfer; }//チェックポイントに到達して火をうつしているかどうかを渡す
	bool  GetDeath() { return m_death; }				//ランナーが死んでいるかどうかを入れる。
	bool  GetStickFire() {return m_stick_fire;}			//ランナーに火がついているかどうかを調べる変数
	bool  GetJamp() { return m_jamp_control_2; }			//ジャンプしているかどうかを渡す
	void  SetRain(bool rain) { m_rain = rain; }			//雨取得用
	void  SetRainTime(bool rain_time) { m_rain_time = rain_time; }//雨の降っている時間取得
	void  SetX(float x) { m_px = x; }					//m_px,m_pyの値をほかのcppでもいじれるようにする
	void  SetY(float y) { m_py = y; }
	void  SetVX(float x) { m_vx = x; }					//m_vx,m_vyの値をほかのcppでもいじれるようにする
	void  SetVY(float y) { m_vy = y; }
	void  SetHoleFall(float f) { m_hole_fall += f; }    //穴に落ちた時描画を変えるようSetHoleFallCon

private:
	float m_px;			//位置
	float m_py;
	float m_vx;			//移動ベクトル
	float m_vy;
	float m_speed;      //主人公の移動量のスピード管理
	float m_jamp_speed; //ジャンプ時のYの追加移動量管理
	int   m_invincible; //無敵時間
	int   m_check_time; //チェックポイントのタイム管理
	int   m_remaining;  //残機
	float m_jamp_y_1 ;	//ジャンプ量
	float m_jamp_y_2 ;	//ジャンプしてる時の上移動
	float m_jamp_y_position;//ジャンプするときの主人公のY位置取得用

	//描画関連
	float m_hole_fall;  //穴に落ちた時の描画するところを変える変数

	//制御系---------
	bool m_torch_control;			//松明制御
	int  m_torch_time_control;		//松明制御
	bool m_puddle_control;			//水たまり制御
	bool m_smart_control;			//スマホ少年制御
	bool m_hole_control;			//穴制御
	bool m_check_control;			//チェックポイント制御
	bool m_check_control_x;			//チェックポイント制御X
	bool m_homing;                  //第二のランナーに向かっていく
	bool m_check_transfer;			//チェックポイントに到達して火をうつしているかどうかを入れる変数
	bool m_check_s1;				//S1のチェックポイントを通過したかどうかを入れる変数
	bool m_death;					//ランナーが死んだとき
	bool m_stick_fire;              //火が付いたかどうか
	bool m_check_vx;				//チェックポイントによってスクロールができなくなったかどうか
	bool m_rain;					//雨を降らす
	bool m_rain_time;				//雨が降った時の時間
	bool m_gool;					//チェックポイントに入った時の歓声を一回だけにする
	//ジャンプ系（調整するので消すor帰る）
	float jamp_memo; //ジャンプするさいに主人公がどこにいたかを調べる
	bool m_jamp_control; //ジャンプしているかどうかを調べる（制御する）
	bool m_jamp_control_2; //ジャンプしているかどうかを調べる2
	int   m_time;

	//-アニメーション
	int m_ani_time; //アニメーションフレーム動作感覚
	int m_ani_frame;//描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値
	int m_ani_change; //アニメーション変更変数
};