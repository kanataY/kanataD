#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ランナー
class CObjRunner : public CObj
{
public:
	CObjRunner();
	~CObjRunner() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	void HitBox();  //当たり判定関連
	float GetX() { return m_px; }//m_px,m_pyの値を渡す
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }//m_vx,m_vyの値を渡す
	float GetVX() { return m_vx; }
	void  SetX(float x) { m_px = x; }//m_px,m_pyの値をほかのcppでもいじれるようにする
	void  SetY(float y) { m_py = y; }
	void  SetVX(float x) { m_vx = x; }//m_vx,m_vyの値をほかのcppでもいじれるようにする
	void  SetVY(float y) { m_vy = y; }

private:
	float m_px;		//位置
	float m_py;
	float m_vx;		//移動ベクトル
	float m_vy;

	//制御系---------
	bool m_torch_control;   //松明制御
	int  m_torch_time_control;   //松明制御
	bool m_puddle_control;  //水たまり制御
	bool m_smart_control;  //スマホ少年制御

	//ジャンプ系（調整するので消すor帰る）
	float qaajamp_memo;
	float jamp_memo; //ジャンプするさいに主人公がどこにいたかを調べる
	bool m_jamp_control; //ジャンプしているかどうかを調べる（制御する）
	int   m_time;

	//-アニメーション
	int m_ani_time; //アニメーションフレーム動作感覚
	int m_ani_frame;//描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値
	int m_ani_change; //アニメーション変更変数
};