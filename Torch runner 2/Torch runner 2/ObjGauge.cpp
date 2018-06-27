//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjGauge.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjGauge::CObjGauge()
{

}

//イニシャライズ
void CObjGauge::Init()
{
	m_px = 10.0f;
	m_py = 10.0f;	//位置
	m_time = 0;
	m_gauge_decrease = 0.0f;
}

//アクション
void CObjGauge::Action()
{
	//ランナーの位置を取得
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//チェックポイントに到達しているときはゲージを減らさない。
	if (runner->GetCheckPoint() == false)
	{
		m_time++;
		if (m_time % 27 == 0) //27フレームごとにゲージが減るようにする
		{
			m_gauge_decrease++;
		}
		if (m_gauge_decrease > 192.0f)
		{
			m_gauge_decrease = 192.0f;
		}
	}
}

//描画
void CObjGauge::Draw()
{
	//-----------背景-----------
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 192.0f;
	src.m_bottom = 32.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px;
	dst.m_right = 192.0f + m_px - m_gauge_decrease;  //ゲージを減らす
	dst.m_bottom = 32.0f + m_py;

	//描画
	Draw::Draw(6, &src, &dst, c, 0.0f);
}