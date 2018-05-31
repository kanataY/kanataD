#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjTitle : public CObj
{
public:
	CObjTitle() {};
	~CObjTitle() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	int m_key_flag;//1:ステージセレクト2:ランキング3:タイトルに戻る4:操作説明
	bool m_key_control;//キーの制御用
	int m_key_control_time;//キーの制御のタイム
	bool m_enter_flag;//エンターをおしっぱの時のフラグ
	int m_enter_flag_time;//エンターキーの押してるときの時間を計測する変数

};