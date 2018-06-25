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
	int  m_scene_start_control_time;//二度押しないと進まない現象を改善するための変数

	//-アニメーション
	int m_ani_time; //アニメーションフレーム動作感覚
	int m_ani_frame;//描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値

	int m_okam_ani_time; //アニメーションフレーム動作感覚
	int m_okam_ani_frame;//描画フレーム
	float m_okam_ani_max_time;   //アニメーション動作間隔最大値
};