#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公
class CObjRunner : public CObj
{
public:
	CObjRunner();
	~CObjRunner() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	float GetX() { return m_px; }
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }
	float GetVX() { return m_vx; }
	void  SetX(float x) { m_px = x; }
	void  SetY(float y) { m_py = y; }
	void  SetVX(float x) { m_vx = x; }
	void  SetVY(float y) { m_vy = y; }

private:
	float m_px;		//位置
	float m_py;
	float m_vx;		//移動ベクトル
	float m_vy;

	//制御系---------
	bool m_torch_control;

	//ジャンプ系（調整するので消すor帰る）
	float qaajamp_memo;
	float jamp_memo; //ジャンプするさいに主人公がどこにいたかを調べる
	bool m_jamp_control; //ジャンプしているかどうかを調べる（制御する）
	int   m_time;
};