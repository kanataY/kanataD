//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "GameL\UserData.h"
#include "ObjTitle.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTitle::Init()
{
	m_key_flag = false;
	//key_select = 0;
	m_time = 0;
	m_mou_x = 0.0f;//位置
	m_mou_y = 0.0f;
	m_mou_l = false;//クリックされていない状態にする
	m_pic = 1;//初期画像位置
	m_pic_f = false;

	//ゲーム実行して一回のみ
	static bool init_point = false;
	if (init_point == false)
	{
		//ランキング初期化
		for (int i = 0; i < RANKING_MAX_COUNT - 1; i++)
		{
			((UserData*)Save::GetData())->m_ranking[i] = 0;
		}
		init_point = true;
	}

	//スコアを0にする
	((UserData*)Save::GetData())->m_point = 0;
}

//アクション
void CObjTitle::Action()
{
	m_time++;

	//アニメーションを進める
	if (m_time % 30 == 0 && m_pic < 8)
		m_pic++;

	//最後までアニメーションが進むと最初に戻る
	if (m_pic == 8)
	{
		m_pic = 1;
		m_pic_f = true;
	}

	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_l = Input::GetMouButtonL();

	if (Input::GetVKey('Z') == true || m_mou_l == true)
	{
		if (m_key_flag == true)
		{
			Scene::SetScene(new CSceneMenu());
			m_key_flag = false;
		}
	}
	else
	{
		m_key_flag = true;
	}
}

//ドロー
void CObjTitle::Draw()
{
	//タイトル画面
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画先切り取り位置
	RECT_F dst;	//描画先表示位置

				//タイトル画面--------
				//切り取り位置設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	if (m_pic_f == true)
	{
		//描画位置設定
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		//0番目に登録しているsrc・dst・cで描画する
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	//タイトル画面文字-----
	//描画位置設定
	dst.m_top = 0.0f;
	dst.m_left = 50.0f;
	dst.m_right = 750.0f;
	dst.m_bottom = 600.0f;

	//m_pic番目に登録しているsrc・dst・cで描画する
	Draw::Draw(m_pic, &src, &dst, c, 0.0f);


	//Font::StrDraw(L"タイトル", 10, 10, 100, c);
}