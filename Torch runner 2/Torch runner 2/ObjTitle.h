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
	int m_key_flag;//1:メニューへ2:終了
	bool m_key_control;//キーの制御用
	bool m_enter_control;//エンターをおしっぱの時のフラグ
	int m_scene_start_control;//タイトルに飛んだ時にすぐMenuに飛ぶのを防ぐ変数

};