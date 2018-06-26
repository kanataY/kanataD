//使用するヘッダーファイル
#include <string.h>
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "GameL\UserData.h"
#include <mbstring.h>

#include "ObjRanking.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjRanking::Init()
{
	//戻るときの文字のサイズ
	//バイト数が１のとき0.5	２のとき1.0とする
	float m_interval = 6.5f;
}

//アクション
void CObjRanking::Action()
{
	//Zキーが押されたらシーンメニューへ
	if (Input::GetVKey('Z') == true)
	{
		Scene::SetScene(new CSceneMenu());
	}
}

//ドロー
void CObjRanking::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//ランキング専用背景描画
	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//最大桁数格納用変数
	int max_number = 0;

	//ランキングごとの桁数を格納用変数
	int number[RANKING_MAX_COUNT];

	//数値の最大桁数を調べる(左ぞろえをするため)
	for (int ranking_count = 0; ranking_count < RANKING_MAX_COUNT; ranking_count++)
	{
		//ランニングのranking_count番の数値を格納
		int ranking = ((UserData*)Save::GetData())->m_ranking[ranking_count];
		//数値が9桁～1桁の間で何桁あるかなどを調べる
		for (int num_max = 100000000, digit = 9; num_max >= 1; num_max /= 10, digit--)
		{
			//桁数を調べる
			if ((ranking / num_max != 0 && ranking > 0) || num_max == 1)
			{
				//桁を格納
				number[ranking_count] = digit;
				//桁が最大桁数以上なら上書き
				if (max_number < digit)
				{
					max_number = digit;
				}
				break;
			}
		}
	}

	//背景の描画----------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//描画
	Draw::Draw(1, &src, &dst, c, 0.0f);
	//-----------------------------------------------------------------

	//ランキングを文字列化
	for (int ranking_count = 0; ranking_count < RANKING_MAX_COUNT - 1; ranking_count++)
	{
		//ランキングのranking_count番の数値を格納
		int ranking = ((UserData*)Save::GetData())->m_ranking[ranking_count];
		
		//順位描画
		DrawNumber(128.0f* ranking_count + 128.0f, 64.0f + 64.0f, 64.0f, ranking_count + 1, m_interval, c);
		//ランキングの値描画処理
		DrawNumber(128.0f* ranking_count + 128.0f, 224.0f + (max_number - number[ranking_count]) * 64.0f, 64.0f, ranking, m_interval, c);
	}
	//位の描画-------------------------------------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//表示位置の設定
	dst.m_top = 138.0f;
	dst.m_left =175.0f;
	dst.m_right =dst.m_left+56.0f;
	dst.m_bottom =dst.m_top+56.0f;
	//描画
	Draw::Draw(2, &src, &dst, c, 0.0f);

	//表示位置の設定
	dst.m_top = 265.0f;
	dst.m_left = 175.0f;
	dst.m_right = dst.m_left + 56.0f;
	dst.m_bottom = dst.m_top + 56.0f;
	//描画
	Draw::Draw(2, &src, &dst, c, 0.0f);

	//表示位置の設定
	dst.m_top = 392.0f;
	dst.m_left = 175.0f;
	dst.m_right = dst.m_left + 56.0f;
	dst.m_bottom = dst.m_top + 56.0f;
	//描画
	Draw::Draw(2, &src, &dst, c, 0.0f);
	//------------------------------------------------------------------------------
	wchar_t str[128];
	//戻るときに使う文字設定
	swprintf_s(str, L"ZkeyでMenuへ");
	//戻るときに使う文字を描画
	Font::StrDraw(str, 5, 580, 20, c);

}


//数字を描画関数
//引数1	float dst_top	:Y位置情報	
//引数2	float dst_left	:X位置情報
//引数3	float dst_size	:描画させる値の大きさ
//引数4	int num			:描画させる値
//引数5	float　interval	:値と値の間の間隔幅を狭める値(大きすぎたらやばいことになるよ)
//引数6	float c[4]		:描画カラー情報
//数値を描画させる(Drawで描画)
void CObjRanking::DrawNumber(float dst_top, float dst_left, float dst_size, int num, float interval, float c[4])
{
	//数字の数　　例）1568なら数字の数は4
	int numeric_number = 0;

	//数字を分解した情報格納用
	int num_decomposition[100] = { 0 };

	//一桁でないかどうか	false=一桁　true=一桁では無い　
	bool not_one_digits = false;

	float a = 10.0f;

	//引数numが9桁～1桁の間で何桁あるかなどを調べる
	for (int num_max = 100000000; num_max >= 1; num_max /= 10)
	{
		//
		if (num / num_max >= 1 || not_one_digits == true)
		{
			//
			num_decomposition[numeric_number] = num / num_max;
			//
			num %= num_max;

			numeric_number++;
			not_one_digits = true;
		}
	}

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

				//引数numの桁数が０だったら
	if (numeric_number == 0)
	{
		//桁数を１増やす
		numeric_number++;
		//一桁目を０にする
		num_decomposition[0] = 0;
	}
	//桁数分ループする
	for (int number = 0; number < numeric_number; number++)
	{
		//桁ごとに数字調べる
		switch (num_decomposition[number])
		{
		case 0:
			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 1:
			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 64.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 2:
			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 64.0f * 2;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 3:
			//切り取り位置の設定
			src.m_top = 64.0f;
			src.m_left = 0.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 4:
			//切り取り位置の設定
			src.m_top = 64.0f;
			src.m_left = 64.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 5:
			//切り取り位置の設定
			src.m_top = 64.0f;
			src.m_left = 64.0f * 2;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 6:
			//切り取り位置の設定
			src.m_top = 64.0f * 2;
			src.m_left = 0.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 7:
			//切り取り位置の設定
			src.m_top = 64.0f * 2;
			src.m_left = 64.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 8:
			//切り取り位置の設定
			src.m_top = 64.0f * 2;
			src.m_left = 64.0f * 2;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 9:
			//切り取り位置の設定
			src.m_top = 64.0f * 3;
			src.m_left = 0.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		}

		//表示位置の設定
		dst.m_top = dst_top;
		dst.m_left = number * dst_size + dst_left - (number * a);
		dst.m_right = dst.m_left + dst_size;
		dst.m_bottom = dst.m_top + dst_size;

		//描画
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
}