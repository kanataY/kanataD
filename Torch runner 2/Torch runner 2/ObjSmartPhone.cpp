//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjSmartphone.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjSmartphone::CObjSmartphone(int x, int y)
{
	m_px = x;
	m_py = y;
}

//イニシャライズ
void CObjSmartphone::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_time = 0;
}

//アクション
void CObjSmartphone::Action()
{
	m_time++;
	if (m_time < 60)  //60フレームになるまでは動かない
		;
	if (m_time > 60 && m_time < 120)//下に移動
	{
		m_vx += 0.25f;
		m_vy += 0.25f;
	}
	if (m_time > 120 && m_time < 240)//上に移動
	{
		m_vx += 0.25f;
		m_vy += -0.25f;
	}
	if (m_time > 240 && m_time < 300)//下に移動
	{
		m_vx += 0.25f;
		m_vy += 0.25f;
	}
	if(m_time > 300)//ループさせる
		m_time = 60;
	

	//摩擦
	m_vx += -(m_vx * 0.15f);
	m_vy += -(m_vy * 0.15f);

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;
}

//描画
void CObjSmartphone::Draw()
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
	src.m_bottom = 256.0f;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 64.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py;

	//描画
	Draw::Draw(5, &src, &dst, c, 0.0f);
}