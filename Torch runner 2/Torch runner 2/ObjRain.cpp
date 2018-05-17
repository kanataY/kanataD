//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjRain.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjRain::CObjRain(float x, float y)
{
	m_px = x;
	m_py = y;
}

//イニシャライズ
void CObjRain::Init()
{
	m_time = 0;

	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期にする
	m_ani_max_time = 10; //アニメーション間隔幅
}

//アクション
void CObjRain::Action()
{
	m_time++; //タイムを進める

	if (m_time > 500)//一定時間たったら消す
	{
		this->SetStatus(false);		//自身に削除命令を出す
	}

	m_ani_time++;//フレーム動作感覚タイムを進める
	if (m_ani_time > m_ani_max_time)//フレーム動作感覚タイムが最大まで行ったら
	{
		m_ani_frame++;//フレームを進める
		m_ani_time = 0;
	}
	if (m_ani_frame == 2)//フレームが最後まで進んだら戻
	{
		m_ani_frame = 0;
	}
}

//描画
void CObjRain::Draw()
{
	//-----------背景-----------
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,0.3f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

				//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + m_ani_frame * 64;
	src.m_right = 800.0f + m_ani_frame * 64;
	src.m_bottom = 800.0f;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px;
	dst.m_right = 800.0f + m_px;
	dst.m_bottom = 600.0f + m_py;

	//描画
	Draw::Draw(10 + m_ani_frame, &src, &dst, c, 0.0f);
}