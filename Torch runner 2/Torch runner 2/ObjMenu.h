#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjMenu : public CObj
{
public:
	CObjMenu() {};
	~CObjMenu() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	int m_key_flag;//1:ステージセレクト2:ランキング3:タイトルに戻る4:操作説明
	bool m_key_control;//キーの制御用
	int m_key_control_time;//キーの制御のタイム
};