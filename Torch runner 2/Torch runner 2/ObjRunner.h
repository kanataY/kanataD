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

private:
	float m_px;		//位置
	float m_py;
	float m_vx;		//移動ベクトル
	float m_vy;
	float qaajamp_memo;
	float jamp_memo; //ジャンプするさいに主人公がどこにいたかを調べる
	bool m_jamp_control; //ジャンプしているかどうかを調べる（制御する）
};