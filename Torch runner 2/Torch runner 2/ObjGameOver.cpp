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
	
	m_time = 0;
	m_ranking_in_floag = false;


	//値交換用
	int w;

	//スコアをランキングの最後に入れる
	((UserData*)Save::GetData())->m_ranking[RANKING_MAX_COUNT - 1] = ((UserData*)Save::GetData())->m_point;

	//ランキング変動確認
	//バブルソート
	for (int i = 0; i < RANKING_MAX_COUNT - 1; i++)
	{
		for (int j = i + 1; j < RANKING_MAX_COUNT; j++)
		{
			if (((UserData*)Save::GetData())->m_ranking[i] < ((UserData*)Save::GetData())->m_ranking[j])
			{
				//値の変更・名前の変更
				w = ((UserData*)Save::GetData())->m_ranking[i];
				((UserData*)Save::GetData())->m_ranking[i] = ((UserData*)Save::GetData())->m_ranking[j];
				((UserData*)Save::GetData())->m_ranking[j] = w;
			
				//スコアがランキング入りを果たしたかどうか
				if (j == RANKING_MAX_COUNT - 1)
				{
					m_ranking_in_floag = true;
				}
			}
		}
	}

	//ステージ1で初期化する
	((UserData*)Save::GetData())->m_stage_count = 1;

	//セーブ
	Save::Seve();
}

//アクション
void CObjGameOver::Action()
{
	m_time++;

	//メニュー画面へ
	if (Input::GetVKey('Z') == true)
	{
		//ランキングに反映したスコアを初期化する
		((UserData*)Save::GetData())->m_point = 0;
		//メニューに移行
		Scene::SetScene(new CSceneMenu());
	}

	//ランキング画面へ
	if (Input::GetVKey('X') == true)
	{
		//ランキングに反映したスコアを初期化する
		((UserData*)Save::GetData())->m_point = 0;
		Scene::SetScene(new CSceneRanking());
	}
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
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	Draw::Draw(0, &src, &dst, c, 0.0f);

	//スコア
	//得点の描画ーーーーーーーーーーーーーーーーーーーーーーーーーーー
	wchar_t str[128];
	swprintf_s(str, L"スコア：%d点", ((UserData*)Save::GetData())->m_point);
	Font::StrDraw(str, 220, 210, 38, c);
	//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
	//メニュー遷移説明
	Font::StrDraw(L"Zでメニューへ", 20, 550, 24, c);

	//ランキング遷移説明
	Font::StrDraw(L"Xでランキングへ", 600, 550, 24, c);
	//----------------------------------------------------

}