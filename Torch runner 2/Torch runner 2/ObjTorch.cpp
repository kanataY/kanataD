//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjTorch.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjTorch::CObjTorch(float x,float y)
{
	m_px = x;
	m_py = y;
}

//イニシャライズ
void CObjTorch::Init()
{
	m_time = 0;

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 12, 12, ELEMENT_RUNNER, OBJ_TORCH, 1);
}

//アクション
void CObjTorch::Action()
{
	//ランナーの位置を取得
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	m_px = runner->GetX();
	m_py = runner->GetY();

	m_time++;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 55.0f, m_py + 28.0f);
	if (m_time > 30)
	{
		this->SetStatus(false);		//自身に削除命令を出す
		Hits::DeleteHitBox(this);	//敵が所有するHitBoxに削除する
	}
}

//描画
void CObjTorch::Draw()
{
	////-----------背景-----------
	////描画カラー情報
	//float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//RECT_F src; //描画元切り取り位置
	//RECT_F dst; //描画先表示位置

	//			//切り取り位置の設定
	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = 192.0f;
	//src.m_bottom = 32.0f;

	////表示位置の設定
	//dst.m_top = 0.0f + m_py;
	//dst.m_left = 0.0f + m_px;
	//dst.m_right = 192.0f + m_px;
	//dst.m_bottom = 32.0f + m_py;

	////描画
	//Draw::Draw(3, &src, &dst, c, 0.0f);
}