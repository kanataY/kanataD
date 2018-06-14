#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjOperation : public CObj
{
public:
	CObjOperation() {};
	~CObjOperation() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	int m_scene_flag;//画像変更用 　0:操作説明 1:移すの説明
	bool m_enter_control;//エンターキーの制御用のフラグ
	bool m_zkey_control; //Zキーの制御用のフラグ
	bool m_scene_start_control;//操作説明に飛んだ時にscene_flagが1になるのを防ぐ変数
};