//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjPuddle.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjPuddle::CObjPuddle(int x,int y)
{
	m_px = (float)x;
	m_py = (float)y;
	m_rx = x / 64;
	m_ry = y / 64;
}

//イニシャライズ
void CObjPuddle::Init()
{
	m_drow_down = 1;
	m_map_con = false;
}

//アクション
void CObjPuddle::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	if (m_map_con == false) //一回目ならマップを読み込む
	{
		for (int j = 1; j < 10; j++)  //マップのYの値だけ探す
		{
			//マップ番号を取ってくる　
			if (block->GetMap(m_rx, m_ry + j) == 3)//水たまりが下にあるなら増やす
			{
				m_drow_down++;
			}

			if (block->GetMap(m_rx, m_ry - j) == 3)//水たまりが上にあるなら下にあるのを消す
			{
				this->SetStatus(false);		//自身に削除命令を出す
				//Hits::DeleteHitBox(this);	//敵が所有するHitBoxに削除する
			}
		}
	}
	m_map_con = true;  //マップを読み込めないようにする

	//補正の情報を持ってくる
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);
	m_py = cor->RangeYPuddle(m_py); //Yの位置がおかしかったら調整する

}

//描画
void CObjPuddle::Draw()
{
	//-----------背景-----------
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

				//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 64.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f * m_drow_down + m_py;

	//描画
	Draw::Draw(7, &src, &dst, c, 0.0f);
}