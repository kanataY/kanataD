#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjGameOver : public CObj
{
public:
	CObjGameOver() {};
	~CObjGameOver() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	bool m_key_flag;//キーフラグ
	float m_mou_x;	//マウスの位置X
	float m_mou_y;	//マウスの位置Y
	bool  m_mou_l;	//マウスの左ボタン
	int   m_time;	//時間管理
};
