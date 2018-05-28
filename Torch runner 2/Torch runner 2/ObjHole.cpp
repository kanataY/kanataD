//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjPuddle.h"

//使用するネームスペース
using namespace GameL;

///////////////////////////////////////////////////////////上限五個
//コンストラクタ
CObjHole::CObjHole(int x, int y)
{
	m_px = (float)x;
	m_py = (float)y;
	m_rx = x / 64;
	m_ry = y / 64;
}

//イニシャライズ
void CObjHole::Init()
{
	m_drow_down = 1;
	m_map_con = false;
	m_hole_fall = false;

	for (int j = 1; j < 10; j++)  //マップのYの値だけ探す
	{
		//ブロック情報を持ってくる
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
		//マップ番号を取ってくる　
		if (block->GetMap(m_rx, m_ry + j) == 3)//穴が下にあるなら増やす
		{
			m_drow_down++;
		}

		if (block->GetMap(m_rx, m_ry - j) == 3)//穴が上にあるなら下にあるのを消す
		{
			this->SetStatus(false);		//自身に削除命令を出す
			Hits::DeleteHitBox(this);	//所有するHitBoxに削除する
		}
	}

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 30, 35 * (float)m_drow_down, ELEMENT_ITEM, OBJ_HOLE, 1);
}

//アクション
void CObjHole::Action()
{
	////ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//補正の情報を持ってくる
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);
	m_py = cor->RangeYPuddle(m_py); //Yの位置がおかしかったら調整する

	//ランナーが穴に落ちる時に使う

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 18.0f + block->GetScroll(), m_py + 17.0f * m_drow_down);
	
	HitBox(); //当たり判定関連

	//画面外に行くと死ぬ
	bool m_s_o = cor->Screen_Out(m_px);

	if (m_s_o == 1)
	{
		this->SetStatus(false);		//自身に削除命令を出す
		Hits::DeleteHitBox(this);	//所有するHitBoxに削除する
	}

}

//描画
void CObjHole::Draw()
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
	Draw::Draw(15, &src, &dst, c, 0.0f);
}

//当たり判定関連
void CObjHole::HitBox()
{
	//HitBoxの情報
	CHitBox* hit = Hits::GetHitBox(this);
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//ランナーの位置を取得
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//ランナーと当たっている場合
	if (runner->GetInvincible() < 0) //無敵時間でなければ判定を設ける。
	{
		if (hit->CheckObjNameHit(OBJ_RUNNER) != nullptr)
		{
			//ランナーの足の位置が穴にかかってない場合は判定をなくす
			if (m_py + (40.0f * ((float)m_drow_down - 1)) > runner->GetY())
			{
				m_hole_fall = true;//足場
			}

			if (m_hole_fall == true) //ランナーが穴に落ちている場合
			{
				runner->SetHoleFall(1.0f);									 //ランナーのほうで描画を小さくする
				runner->SetX(m_px + block->GetScroll() + 15.0f);			 //ランナーの位置を穴の真ん中にするようにする

				if (m_drow_down >= 4)//穴が四個分いじょうの大きさなら
					runner->SetY(m_py + 35.0f   * ((float)m_drow_down - 1)); //ランナーのｙ位置を真ん中に調整する
				else
					runner->SetY(m_py + 50.0f * ((float)m_drow_down - 1));
			}
		}
		else
		{
			m_hole_fall = false;
		}
	}
}