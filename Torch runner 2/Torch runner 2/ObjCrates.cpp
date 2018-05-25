//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjCrates.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjCrates::CObjCrates(int x,int y)
{
	m_px = (float)x;
	m_py = (float)y;
}

//イニシャライズ
void CObjCrates::Init()
{
	m_time = 0;
	m_fire_control = false;

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ITEM, OBJ_CRATES, 1);
}

//アクション
void CObjCrates::Action()
{
	//ランナーの位置を取得
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//補正の情報を持ってくる
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);
	m_py = cor->RangeY(m_py); //Yの位置がおかしかったら調整する

	CObj::SetPrio((int)m_py); //描画優先順位変更

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py);

	//当たり判定関係
	HitBox();

	//画面外に行くと死ぬ
	bool m_s_o = cor->Screen_Out(m_px);

	if (m_s_o == 1)
	{
		this->SetStatus(false);		//自身に削除命令を出す
		Hits::DeleteHitBox(this);	//所有するHitBoxに削除する
	}
}

//描画
void CObjCrates::Draw()
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
	dst.m_left =0.0f + m_px + block->GetScroll();
	dst.m_right = 64.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py;

	//描画
	Draw::Draw(4, &src, &dst, c, 0.0f);
}

void CObjCrates::HitBox()
{
	//ランナーの位置を取得
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//聖火の情報を取得
	CObjTorch* torch = (CObjTorch*)Objs::GetObj(OBJ_TORCH);

	//炎の情報を取得
	CObjFire* fire = (CObjFire*)Objs::GetObj(OBJ_FIRE);

	//補正の情報を持ってくる
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);

	//Hitboxの情報を調べる
	CHitBox* hit = Hits::GetHitBox(this);

	//まだ炎がついてない状態
	if (m_fire_control == false)
	{
		//聖火と当たっている場合
		if (hit->CheckObjNameHit(OBJ_TORCH) != nullptr)
		{
			cor->FireDisplay(m_px, m_py); //炎を発生させる
			m_fire_control = true;
		}
	}
	//炎がついてる状態
	if (m_fire_control == true)
	{
		if (fire != nullptr)
		{
			m_time++; //一定時間たったら木箱を消す。
			if (m_time > 99)
			{
				this->SetStatus(false);		//自身に削除命令を出す
				Hits::DeleteHitBox(this);	//所有するHitBoxに削除する
			}
		}
	}

	//オカマと当たっている場合
	//if (hit->CheckObjNameHit(OBJ_OKAMA) != nullptr)
	//{
	//	this->SetStatus(false);		//自身に削除命令を出す
	//	Hits::DeleteHitBox(this);	//所有するHitBoxに削除する
	//}

	//ランナーと当たっている場合
	if (runner->GetInvincible() < 0) //無敵時間でなければ判定を設ける。
	{
		if (hit->CheckObjNameHit(OBJ_RUNNER) != nullptr)
		{
			//木箱とランナーがどの角度で当たっているかを確認
			HIT_DATA** hit_data;						//当たったときの細かな情報を入れるための構造体
			hit_data = hit->SearchObjNameHit(OBJ_RUNNER);	//hit_dataに木箱と当たっているほか全てのHitBoxとの情報を入れる

			for (int i = 0; i < hit->GetCount(); i++)
			{
				//hit_data[i]に情報が入っていたら処理
				if (hit_data[i] != NULL)
				{
					//左右に当たったら
					float r = hit_data[i]->r;

					//通り抜けないようにする       ※要調整
					//ランナーが上に当たっていたら
					if (r >= 45 && r < 135)
					{
						if (runner->GetY() > m_py - 35.0f)	//上側を通り抜けれるようにする
							runner->SetVY(-0.8f);
					}

					if ((r < 45 && r >= 0) || r >= 315)
					{
						//右
						if (runner->GetY() < m_py - 35.0f)//上側を通り抜けれるようにする
							;
						else if (runner->GetY() > m_py + 32.0f)//下側を通り抜けれるようにする
							;
						else
							runner->SetVX(0.8f);//真ん中だから通り抜けれないようにする
					}

					if (r >= 135 && r < 220)
					{
						//左
						if (runner->GetY() < m_py - 35.0f)//上側を通り抜けれるようにする
							;
						else if (runner->GetY() > m_py + 32.0f)//下側を通り抜けれるようにする
							;
						else
							runner->SetVX(-3.0f);//真ん中だから通り抜けれないようにする
					}
					if (r >= 220 && r < 315)
					{
						//下
						if (runner->GetY() < m_py + 32.0f)//下側を通り抜けれるようにする
							runner->SetVY(0.8f);
					}
				}
			}
		}
	}
}