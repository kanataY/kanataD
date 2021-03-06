//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjBlock.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBlock::CObjBlock(int map[10][MAP_X_MAX])
{
	//マップデータをコピー
	memcpy(m_map, map, sizeof(int)*(10 * MAP_X_MAX));
	//マップデータを記録するほうにコピー
	memcpy(m_map_Record, map, sizeof(int)*(10 * MAP_X_MAX));
}

//イニシャライズ
void CObjBlock::Init()
{
	m_px = 0.0f;
	m_py = 0.0f;	//位置
	m_bx1 = 0.0f;
	m_bx2 = 800.0f;
	m_rain = false;

	m_scroll = 0.0f;
	m_scroll_run = 800.0f;
	m_scroll_num = 0;
}

//アクション
void CObjBlock::Action()
{
	//背景関連ーーーーーーーーーーーーーーーーーーーーーーーー
	//ランナーの位置を取得
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);
	//チェックポイントを取得
	CObjCheckPoint* check = (CObjCheckPoint*)Objs::GetObj(OBJ_CHECK_POINT);
	//火の取得
	CObjFire* fire = (CObjFire*)Objs::GetObj(OBJ_FIRE);
	//ゲージの情報を持ってくる
	CObjGauge* gau = (CObjGauge*)Objs::GetObj(OBJ_GAUGE);

	float rx = runner->GetX();
	float ry = runner->GetY();

	//チェックポイントのが出てなかったらとまらないようにする
	float m_check_x = 999.0f;
	//チェックポイントが出現しているなら位置をとる
	if (check != nullptr)
		m_check_x = check->GetX() + m_scroll ;

	//チェックポイントの描画がすべてWindowに収まっている場合
	if (m_check_x < 400.0f)
	{
		//背景1の動作
		m_bx1 -= 0.0f;

		//背景2の動作
		m_bx2 -= 0.0f;
	}

	//後方
	else if (runner->GetCheckPoint() == true && m_check_x < 400.0f || gau->GetGauge() == 192)
	{
		//背景1の動作
		m_bx1 -= 0.0f;

		//背景2の動作
		m_bx2 -= 0.0f;
	}

	else if (rx < -50 || runner->GetHoleFallCon() == true || runner->GetDeath() == true) //画面より左側に行けないようにする
	{
		//背景1の動作
		m_bx1 -= 0.0f;

		//背景2の動作
		m_bx2 -= 0.0f;
	}
	//前方スクロールライン
	else if (rx > -50 && runner->GetHoleFallCon() == false)
	{
		// 主人公が炎に当たっている場合スクロールを二倍にする
		if(runner->GetStickFire() == true)
		{
			m_scroll -= 4.0f;//主人公が本来動くべき分の値をm_scrollに加える

			//背景1の動作
			m_bx1 -= 4.0f;
			if (m_bx1 < -800.0f)
			{
				m_bx1 = 800.0f;
				m_scroll_num++;//背景1が終わればカウントする
			}
			//背景2の動作
			m_bx2 -= 4.0f;
			if (m_bx2 < -800.0f)
				m_bx2 = 800.0f;
		}
		else
		{
			m_scroll -= 2.0f;//主人公が本来動くべき分の値をm_scrollに加える

			//背景1の動作
			m_bx1 -= 2.0f;
			if (m_bx1 < -800.0f)
			{
				m_bx1 = 800.0f;
				m_scroll_num++;//背景1が終わればカウントする
			}
			//背景2の動作
			m_bx2 -= 2.0f;
			if (m_bx2 < -800.0f)
				m_bx2 = 800.0f;
		}
		
	}
	

	//マップ関連ーーーーーーーーーー
	float line = 0.0f;

	//敵出現ライン
	//主人公の位置+800 - ランナーの位置を敵出現ラインにする
	line = rx + (-m_scroll) + (800 - rx);

	//敵出現ラインを要素番号化
	int ex = ((int)line) / 64;

	//敵出現ラインの列を検索
	for (int i = 0; i < 10; i++)
	{
		//列の中から１を探す
		if (m_map[i][ex] == 1)
		{
			
		}
		//列の中から２を探す
		if (m_map[i][ex] == 2)
		{
			
		}

		//列の中から3を探す
		if (m_map[i][ex] == 3)
		{
			
		}

		//列の中から4を探す
		if (m_map[i][ex] == 4)
		{
			//オカマを生成
			
		}

		//列の中から5を探す
		if (m_map[i][ex] == 5)
		{
			
		}

		//列の中から6を探す
		if (m_map[i][ex] == 6)
		{
			
		}

		
	}

	//雨のフラグがONになったなら雨を降らす
	if (m_rain == true)
	{
		CObjRain* r = new CObjRain(0.0f, 0.0f);
		Objs::InsertObj(r, OBJ_RAIN, 1300);
		runner->SetRain(true);
		m_rain = false;
	}
	else
	{
		runner->SetRain(false);
	}
}

//描画
void CObjBlock::Draw()
{
	//チェックポイントを取得
	CObjCheckPoint* check = (CObjCheckPoint*)Objs::GetObj(OBJ_CHECK_POINT);
	//-----------背景-----------
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;
	//背景1が4回スクロールした時
	if (m_scroll_num>=4)
	{
		//表示位置の設定
		//ゴ−ル背景描画
		dst.m_top = 0.0f;
		dst.m_left = 0.0f + m_bx1;
		dst.m_right = 806.0f + m_bx1;
		dst.m_bottom = 700.0f;

		//描画
		Draw::Draw(26, &src, &dst, c, 0.0f);
	}
	else
	{

		//表示位置の設定
		//背景１
		dst.m_top = 0.0f;
		dst.m_left = 0.0f + m_bx1;
		dst.m_right = 806.0f + m_bx1;
		dst.m_bottom = 700.0f;

		//描画
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	//背景２
	dst.m_top = 0.0f;
	dst.m_left = 0.0f + m_bx2;
	dst.m_right = 806.0f + m_bx2;
	dst.m_bottom = 700.0f;

	//描画
	Draw::Draw(1, &src, &dst, c, 0.0f);
}

//調べたいマップの位置にあるマップ番号を返す
int CObjBlock::GetMap(int x, int y)
{
	if (0 <= y && y < 10 && 0 <= x && x < MAP_X_MAX)

		return m_map_Record[y][x];

	return -99999;//無かった場合
}