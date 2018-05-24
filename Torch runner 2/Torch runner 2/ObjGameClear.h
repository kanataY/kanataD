#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjGameClear : public CObj
{
public:
	CObjGameClear() {};
	~CObjGameClear() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	float m_x; //主人公のX位置
	float m_y;	//主人公のY位置
	float m_vx;//X方向の移動ベクトル
	float m_vy;//Y方向の移動ベクトル
	float m_sppde_power;//スピードパワー
	int m_time; //時間管理
};
