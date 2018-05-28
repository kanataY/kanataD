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
	//値交換用変数
	int w;

	//バブルソート
	for (int i = 0; i < RANKING_MAX_COUNT - 1; i++)
	{
		for (int j = i + 1; j < RANKING_MAX_COUNT; j++)
		{
			if (((UserData*)Save::GetData())->m_ranking[i] < ((UserData*)Save::GetData())->m_ranking[j])
			{
				//値の変更
				w = ((UserData*)Save::GetData())->m_ranking[i];
				((UserData*)Save::GetData())->m_ranking[i] = ((UserData*)Save::GetData())->m_ranking[j];
				((UserData*)Save::GetData())->m_ranking[j] = w;
			}
		}
	}

	//戻るときの文字のサイズ
	//バイト数が１のとき0.5	２のとき1.0とする
	m_return_size = 0;
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
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//ランキング専用背景描画
	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

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

	wchar_t str[128];

	//ランキングを文字列化
	for (int ranking_count = 0; ranking_count < 3; ranking_count++)
	{
		//ランニングのranking_count番の数値を格納
		int ranking = ((UserData*)Save::GetData())->m_ranking[ranking_count];

	

		//順位描画
		DrawNumber(128.0f* ranking_count + 128.0f, 64.0f + 64.0f, 64.0f, ranking_count + 1);
		
		//ランキングの値描画処理
		DrawNumber(128.0f* ranking_count + 128.0f, 64.0f + 164.0f, 64.f, ranking);
	}

	//戻るときに使う文字設定
	swprintf_s(str, L"ZkeyでMenuへ");
	
	//戻るときに使う文字を描画
	Font::StrDraw(str, 5, 580, RETURN_SIZE, c);

	//位の描画
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
}

//文字列のサイズを返す関数
//引数１　wchar_t *str	:ワイルド文字列
//戻り値	引数で取ったワイルド文字列をマルチ文字列に変換してマルチ文字列にしたときのメモリ情報を返す
//マルチ文字列の長さが1のとき0.5　２のとき1を加算していった数字を返す	
float CObjRanking::StringSize(wchar_t *str)
{
	//マルチ文字列の変数を作成
	char wcs[100];
	//変換された文字数を記録する変数(wcstombs_s関数でしか使わない)
	size_t ret;

	//何かわからない
	setlocale(LC_CTYPE, "jpn");

	//ワイルド文字列をマルチ文字列に変換
	wcstombs_s(&ret, wcs, 100, str, _TRUNCATE);

	//*pにwcsの先頭ポインタを渡す
	char *p = wcs;

	//バイト数
	float bytes_count = 0.0000f;

	//文字数分ループ
	while (*p != '\0')
	{
		//バイト数を確認
		switch (_mbclen((BYTE*)p))
		{
			//バイト数が１のときbytes_countに0.5を加算
		case 1:
			*(p++);
			bytes_count += 0.5;
			break;
			//バイト数が２のときbytes_countに1.0を加算
		case 2:
			*(p++);
			*(p++);
			bytes_count += 1.0;
			break;
		default:
			//error
			break;
		}
	}

	return bytes_count;
}

void CObjRanking::DrawNumber(float dst_top, float dst_left, float dst_size, int num)
{
	//数字の数　　例）1568なら数字の数は4
	int numeric_number = 0;

	//数字を分解した情報格納用 & 初期化
	int num_decomposition[100] = { 0 };

	//一桁でないかどうか	false=一桁　true=一桁では無い　
	bool not_one_digits = false;

	//引数numが9桁〜1桁の間で何桁あるかなどを調べる
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
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

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
	for (int i = 0; i < numeric_number; i++)
	{
		//桁ごとに数字調べる
		switch (num_decomposition[i])
		{
		case 0://0の時0の画像描画
			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 1://1の時1の画像描画
			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 64.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 2://2の時2の画像描画
			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 64.0f * 2;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 3://3の時3の画像描画
			//切り取り位置の設定
			src.m_top = 64.0f;
			src.m_left = 0.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 4://4の時4の画像描画
			//切り取り位置の設定
			src.m_top = 64.0f;
			src.m_left = 64.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 5://5の時5の画像描画
			//切り取り位置の設定
			src.m_top = 64.0f;
			src.m_left = 64.0f * 2;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 6://6の時6の画像描画
			//切り取り位置の設定
			src.m_top = 64.0f * 2;
			src.m_left = 0.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 7://7の時7の画像描画
			//切り取り位置の設定
			src.m_top = 64.0f * 2;
			src.m_left = 64.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 8://8の時8の画像描画
			//切り取り位置の設定
			src.m_top = 64.0f * 2;
			src.m_left = 64.0f * 2;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 9://9の時9の画像描画
			//切り取り位置の設定
			src.m_top = 64.0f * 3;
			src.m_left = 0.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		}

		//表示位置の設定
		dst.m_top = dst_top;
		dst.m_left = i * dst_size + dst_left;
		dst.m_right = dst.m_left + dst_size;
		dst.m_bottom = dst.m_top + dst_size;

		//描画
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
}

