//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjSmartphone.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjSmartphone::CObjSmartphone(int x, int y)
{
	m_px = (float)x;
	m_py = (float)y;
}

//イニシャライズ
void CObjSmartphone::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_time = 0;
	m_middle = false;
	m_time_fire = 0;
	m_fire_control = false;

	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期にする
	m_ani_max_time = 20; //アニメーション間隔幅
	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 32, 32, ELEMENT_ENEMY, OBJ_SMARTPHONE, 1);
}

//アクション
void CObjSmartphone::Action()
{
	//ランナーの位置を取得
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	m_time++;

	//ステージ２なら
	if (((UserData*)Save::GetData())->m_stage_count == 2)
	{
		if (m_time < 60)  //60フレームになるまでは動かない
		{
			if (m_middle == true) //ランナー以外のHitBoxに当たった時真ん中よりしたなら
			{
				m_vx += 0.15f;    //上に動かせる
				m_vy += -0.15f;
			}
			if (m_middle == false)//ランナー以外のHitBoxに当たった時真ん中より上なら
			{
				m_vx += 0.15f;   //下に動かせる
				m_vy += 0.15f;
			}
		}
		if (m_time > 60 && m_time < 120)//下に移動
		{
			m_vx += 0.15f;
			m_vy += 0.15f;
		}
		if (m_time > 120 && m_time < 240)//上に移動
		{
			m_vx += 0.15f;
			m_vy += -0.15f;
		}
		if (m_time > 240 && m_time < 300)//下に移動
		{
			m_vx += 0.15f;
			m_vy += 0.15f;
		}
		if (m_time > 300)//ループさせる
			m_time = 60;
	}
	
	//ステージ３なら
	if (((UserData*)Save::GetData())->m_stage_count == 3)
	{
		float okax = runner->GetX() - (m_px + block->GetScroll());
		float okay = runner->GetY() - m_py;

		//atan2で角度を求める
		float r2 = atan2(okay, okax)*180.0f / 3.14f;

		//-180～-0を180～360に変換
		if (r2 < 0)
		{
			r2 = 360 - abs(r2);
		};

		float ar = r2;

		if (ar < 0)
		{
			ar = 360 - abs(ar);
		}

		//スマホの現在の向いてる角度を取る
		float bor = atan2(m_vy, m_vx)*180.0f / 3.14f;

		//-180～-0を180～360に変換
		if (bor < 0)
		{
			bor = 360 - abs(bor);
		};
		float br = bor;

		//ランナーのほうにホーミングする
		//移動方向をランナーの方向にする
		m_vy = sin(3.14f / 180 * ar);
		m_vy *= 7;

		m_vx += 0.15f;
	}
	//---------------------

	m_ani_time++;//フレーム動作感覚タイムを進める
	if (m_ani_time > m_ani_max_time)//フレーム動作感覚タイムが最大まで行ったら
	{
		m_ani_frame++;//フレームを進める
		m_ani_time = 0;
	}
	if (m_ani_frame == 4)//フレームが最後まで進んだら戻す
	{
		m_ani_frame = 0;
	}

	//補正の情報を持ってくる
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);
	m_py = cor->RangeY(m_py,true); //Yの位置がおかしかったら調整する

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 16.0f + block->GetScroll(), m_py+16.0f);

	HitBox(); //HitBox関連

	//摩擦
	m_vx += -(m_vx * 0.15f);
	m_vy += -(m_vy * 0.15f);

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

	//画面外に行くと死ぬ
	bool m_s_o = cor->Screen_Out(m_px + 250.0f);

	if (m_s_o == 1)
	{
		this->SetStatus(false);		//自身に削除命令を出す
		Hits::DeleteHitBox(this);	//所有するHitBoxに削除する
	}

	CObj::SetPrio((int)m_py); //描画優先順位変更


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
	src.m_left = 0.0f + m_ani_frame * 64;
	src.m_right = 64.0f + m_ani_frame * 64;
	src.m_bottom = 256.0f;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 64.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py;

	//描画
	Draw::Draw(8, &src, &dst, c, 0.0f);
}

void CObjSmartphone::HitBox()
{
	//HitBoxの情報
	CHitBox* hit = Hits::GetHitBox(this);

	//補正の情報を持ってくる
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);

	//炎の情報を取得
	CObjFire* fire = (CObjFire*)Objs::GetObj(OBJ_FIRE);

	if (hit->CheckObjNameHit(OBJ_CRATES) != nullptr) //木箱と当たっている
	{
		if (m_py >= 406.5f) //真ん中より下ならフラグをONにする
			m_middle = true;
		if (m_py < 406.5f)  //真ん中より上ならフラグをOFFにする
			m_middle = false;

		m_time = -60; //タイムを最初より前に戻して動かない時間を作る
		m_vx -= 0.7f; //バックさせる

	}

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
			m_vx = 0.0f; //火がついてる間は動けなくする
			m_vy = 0.0f;
			m_time_fire++; //一定時間たったらスマホ少年を消す。
			if (m_time_fire > 65)
			{
				//スコア増加
				((UserData*)Save::GetData())->m_point += 600;
				this->SetStatus(false);		//自身に削除命令を出す
				Hits::DeleteHitBox(this);	//所有するHitBoxに削除する
			}
		}
	}
	//穴に当たっていると後ずさる
	if (hit->CheckObjNameHit(OBJ_HOLE) != nullptr)
	{
		m_vx -= 0.5f; //後ずさり
	}
}