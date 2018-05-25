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
	float m_mou_x;	//マウスの位置X
	float m_mou_y;	//マウスの位置Y

	bool  m_mou_l;	//マウスの左ボタン false:押していない true:押している
	bool m_key_flag;//キーフラグ false:押せない true:押せる
	bool  m_pic_f;	//背景が最後までいったかどうか false:いってない true:いった

					//int  key_select;//ゲーム選択キーがどこに居るか調べる
	int  m_time;	//時間管理
	int  m_pic;		//使う画像の登録番号1管理
};