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
	int GetTime() { return m_time; }
	bool GetRankingInFlag() { return m_ranking_in_floag; }
private:
	bool m_key_flag;//キーフラグ
	int   m_time;	//時間管理
	bool m_ranking_in_floag;//ランキング入りを果たしたかどうかフラグ
};
