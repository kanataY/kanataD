//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameHead.h"
#include "ObjGameOver.h"
#include "GameL\UserData.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjGameOver::Init()
{
	m_key_flag = false;
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_l = false;
	m_time = 0;
}

//アクション
void CObjGameOver::Action()
{
	m_time++;

	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//マウスのボタンの状態
	m_mou_l = Input::GetMouButtonL();

	if (Input::GetVKey('A') == true || m_mou_l == true)
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

	//スコアをランキングの最後に入れる
	((UserData*)Save::GetData())->m_ranking[RANKING_MAX_COUNT - 1] = ((UserData*)Save::GetData())->m_point;
}

//ドロー
void CObjGameOver::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//Font::StrDraw(L"GAMEOVER", 10, 10, 100, c);

	RECT_F src;	//描画先切り取り位置
	RECT_F dst;	//描画先表示位置

				//背景--------------------------------
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	Draw::Draw(7, &src, &dst, c, 0.0f);

	//GAMEOVER文字移動処理-----------

	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	dst.m_top = 130.0f;
	dst.m_left = 100.0f;
	dst.m_right = 690.0f;
	dst.m_bottom = 450.0f;

	//Draw::Draw(1, &src, &dst, c, 0.0f);

	//-----点滅から移動-----
	if (200 <= m_time && m_time < 330)
	{
		dst.m_top = 130.0f - m_time + 200;
		dst.m_left = 100.0f;
		dst.m_right = 690.0f;
		dst.m_bottom = 450.0f - m_time + 200;
	}
	else if (m_time >= 330)
	{
		dst.m_top = 0.0f;
		dst.m_left = 100.0f;
		dst.m_right = 690.0f;
		dst.m_bottom = 320.0f;
	}

	if (0 < m_time && m_time < 200 && m_time % 50 == 0)//GameOver点滅
		;
	else //GameOver移動
		Draw::Draw(1, &src, &dst, c, 0.0f);

	if (m_time >= 350)
	{
		Font::StrDraw(L"score", 330, 270, 38, c);
	}

	if (m_time >= 400)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0f;
		src.m_bottom = 512.0f;

		dst.m_top = 380.0f;
		dst.m_left = 120.0f;
		dst.m_right = 370.0f;
		dst.m_bottom = 580.0f;

		Draw::Draw(8, &src, &dst, c, 0.0f);

		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0f;
		src.m_bottom = 512.0f;

		dst.m_top = 360.0f;
		dst.m_left = 420.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 580.0f;

		Draw::Draw(6, &src, &dst, c, 0.0f);

		//Font::StrDraw(L"Zでメニュー画面へ", 170, 500, 24, c);
	}

	//---------------------------------------

	/*src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	dst.m_top = 130.0f;
	dst.m_left = 100.0f;
	dst.m_right = 690.0f;
	dst.m_bottom = 450.0f;

	//---画像切り替え---
	if (0 < m_time && m_time <= 10)		//画像1表示時間
	Draw::Draw(2, &src, &dst, c, 0.0f);
	else if (100 < m_time && m_time <= 200) //画像2表示時間
	Draw::Draw(3, &src, &dst, c, 0.0f);
	else if (200 < m_time && m_time <= 300) //画像3表示時間
	Draw::Draw(4, &src, &dst, c, 0.0f);
	else if (300 < m_time && m_time <= 400)//画像4表示時間
	Draw::Draw(5, &src, &dst, c, 0.0f);
	else if (400 < m_time)//表示時間を越えると0に戻す
	m_time = 0;*/
}