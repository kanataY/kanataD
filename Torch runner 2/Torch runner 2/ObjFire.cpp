//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjFire.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjFire::CObjFire(float x,float y ,int b)
{
	m_px = x;
	m_py = y;
	m_fire_hit = b;
}

//イニシャライズ
void CObjFire::Init()
{
	m_time = 0;

	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期にする
	m_ani_max_time = 4; //アニメーション間隔幅

	//HitBox
	if(m_fire_hit == 0)
		Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_NULL, OBJ_FIRE, 1);
}

//アクション
void CObjFire::Action()
{
	//ランナーの位置を取得
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	m_time++; //タイムを進める

	if (m_time < 2)//
	{
		if (m_fire_hit != 2)
		{
			Audio::Start(2);
		}
	}

	//ランナー以外に火が付いた場合はこっち
	if (m_fire_hit != 2)
	{
		//HitBoxの位置の変更
		if (m_fire_hit == 0)
		{
			CHitBox* hit = Hits::GetHitBox(this);
			hit->SetPos(m_px + block->GetScroll(), m_py);
		}

		if (m_time > 71)//一定時間たったら消す
		{
			if (m_fire_hit == 1) //人間関係だったら雨を降らす
				block->SetRain(true);
			this->SetStatus(false);		//自身に削除命令を出す
			if (m_fire_hit == 0)
				Hits::DeleteHitBox(this);	//所有するHitBoxに削除する
		}
	}
	else      //ランナーも火が付いた場合
	{
		//火の位置をランナーの位置にする
		m_px = runner->GetX() - block->GetScroll();
		m_py = runner->GetY();

		//ランナーについている火が消えたなら
		if (runner->GetStickFire() == false)
		{
			this->SetStatus(false);		//自身に削除命令を出す
		}
	}

	m_ani_time++;//フレーム動作感覚タイムを進める
	if (m_ani_time > m_ani_max_time)//フレーム動作感覚タイムが最大まで行ったら
	{
		m_ani_frame++;//フレームを進める
		m_ani_time = 0;
	}
	if (m_ani_frame == 5)//フレームが最後まで進んだら戻す
	{
		m_ani_frame = 0;
	}

}

//描画
void CObjFire::Draw()
{
	//-----------背景-----------
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + m_ani_frame * 64;
	src.m_right = 64.0f +m_ani_frame * 64;
	src.m_bottom = 320.0f;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//ランナー以外に火が付いた場合はこっち
	if (m_fire_hit != 2)
	{
		//表示位置の設定
		dst.m_top = 0.0f + m_py - 10.0f;
		dst.m_left = 0.0f + m_px + block->GetScroll() - 10.0f;
		dst.m_right = 50.0f + m_px + block->GetScroll() - 10.0f;
		dst.m_bottom = 50.0f + m_py - 10.0f;

		//描画
		Draw::Draw(9, &src, &dst, c, 0.0f);

		//表示位置の設定
		dst.m_top = 0.0f + m_py + 30.0f;
		dst.m_left = 0.0f + m_px + block->GetScroll() + 10.0f;
		dst.m_right = 50.0f + m_px + block->GetScroll() + 10.0f;
		dst.m_bottom = 50.0f + m_py + 30.0f;

		//描画
		Draw::Draw(9, &src, &dst, c, 0.0f);

		//表示位置の設定
		dst.m_top = 0.0f + m_py + 12.0f;
		dst.m_left = 0.0f + m_px + block->GetScroll() + 35.0f;
		dst.m_right = 50.0f + m_px + block->GetScroll() + 35.0f;
		dst.m_bottom = 50.0f + m_py + 12.0f;

		//描画
		Draw::Draw(9, &src, &dst, c, 0.0f);
	}

	else //ランナーの場合は火を小さくしておしりにつける
	{
		//表示位置の設定
		dst.m_top = 0.0f + m_py + 18.0f;
		dst.m_left = 0.0f + m_px + block->GetScroll();
		dst.m_right = 25.0f + m_px + block->GetScroll();
		dst.m_bottom = 25.0f + m_py + 18.0f;

		//描画
		Draw::Draw(9, &src, &dst, c, 0.0f);
	}
}