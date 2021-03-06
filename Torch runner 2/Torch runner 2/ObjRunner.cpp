//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjRunner.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjRunner::CObjRunner(int r)
{
	m_remaining = r; //残機
}

//イニシャライズ
void CObjRunner::Init()
{
	m_px = 250.0f;
	m_py = 500.0f;	//位置
	m_vx = 0.0f;
	m_vy = 0.0f;	//移動ベクトル
	m_invincible = 0;
	m_speed = 0.8f;
	m_jamp_speed = 0.0f;

	m_hole_fall = 0.0f;

	m_torch_control = false;
	m_torch_time_control = 0;
	m_puddle_control = false;
	m_smart_control = false;
	m_hole_control = false;
	m_check_control = false;
	m_check_control_x = false;
	m_homing = false;
	m_check_time = 0;
	m_check_transfer = false;
	m_check_s1 = false;
	m_death = false;
	m_stick_fire = false;
	m_check_vx = false;
	m_rain = false;
	m_rain_time = true;
	m_gool = false;

	jamp_memo = 0.0f;
	m_jamp_control = false;
	m_jamp_control_2 = false;
	m_time = 0;

	m_jamp_y_1 = 1.6f;
	m_jamp_y_2 = 0.8f;

	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期にする
	m_ani_max_time = 5; //アニメーション間隔幅

	m_ani_change = 2;//アニメーションを2に




	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 18, 64, ELEMENT_RUNNER, OBJ_RUNNER, 1);
}

//アクション
void CObjRunner::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//補正の情報を持ってくる
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);

	//穴情報を持ってくる
	CObjHole* hole = (CObjHole*)Objs::GetObj(OBJ_HOLE);

	//オカマの情報を持ってくる
	CObjOkama* okama = (CObjOkama*)Objs::GetObj(OBJ_OKAMA);

	//ゲージの情報を持ってくる
	CObjGauge* gau = (CObjGauge*)Objs::GetObj(OBJ_GAUGE);

	//チェックポイントを取得
	CObjCheckPoint* check = (CObjCheckPoint*)Objs::GetObj(OBJ_CHECK_POINT);


	//アニメーションーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
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
	//アニメーション終了−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−


	//ゲージがなくなった時----------------------------------------------------------------------
	//なくなる瞬間に
	if (gau->GetGauge() == 191)
	{
		//フレームを最初に戻して、フレーム速度を落とす
		m_ani_frame = 1;
		m_ani_max_time = 50;
	}
	else if (gau->GetGauge() == 192 && m_jamp_control_2 == false)
	{
		Audio::Stop(1);

		m_ani_change = 5;//ステージ1の死亡シーン

		//手をついたら
		if (m_ani_frame == 2)
		{
			//少し時間がたったら消す
			if (m_ani_time >= 45)
			{
				//残機ないときはゲームオーバーに
				if (m_remaining <= 1)
				{
					Scene::SetScene(new CSceneGameOver());
				}
				else//残機を減らしてシーンを再開する
				{
					m_remaining -= 1;
					Scene::SetScene(new CSceneMain(m_remaining));
				}
			}
		}
	}
	else if (gau->GetGauge() == 192 && m_jamp_control_2 == true)
	{
		m_ani_frame = 1;
		//ジャンプしたときに記録した場所に行くまで落ちる		
		if (m_py >= m_jamp_y_position)
			m_jamp_control_2 = false;
		m_py += m_jamp_y_1;
	}

	//----------------------------------------------------------------------------------------
	else     //ゲージがなくなってない時は動く
	{
		//死んだときーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
		if (m_death == true)//死んだとき
		{
			//穴に落ちてない時だけ
			if (m_hole_control == false)
			{
				//ジャンプしたときにそのまま行ってしまうので戻す。
				if (m_py <= 277) //道路より上に行かないようにする
					m_py = 277;

				m_vx = 0.0f; //復活した後動くのを防ぐ
				m_vy = 0.0f;

				m_stick_fire = false;
				m_hole_fall = 0.0;    //ランナーの描画をもとに戻す
				m_ani_max_time = 3;   //アニメーションの速度を上げる

				if (m_px < 300.0f)//３００の地点まで進む
					m_px += 2;
				else
				{
					m_death = false; //動かせるようにする
					m_ani_max_time = 5;//タイムを戻す
					m_invincible = 50; //しばらくの間無敵時間を設ける
					Audio::Stop(1);//走る音を止める
				}
			}
		}

		//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー

		//チェックポイントに入ってなければメインの行動ができる　　死んでなければ
		if (m_check_control == false && m_death == false && gau->GetGauge() != 192)
		{
			//画面外に行かないようにするーーーーーーーーーーーーーーーーーー

			if (m_py >= 536) //一番下より下に行かないようにする
				m_py = 536;
			if (m_jamp_control_2 == false)        //ジャンプをしてない時
			{
				if (m_py <= 277) //道路より上に行かないようにする
					m_py = 277;
			}

			m_px = cor->Screen_In(m_px);  //右に行き過ぎないようにする（右の画面外に行かないように）

			//−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
			//移動ーーーーーーーーーーーーーーーーーーーーー
			if (m_stick_fire == true)
			{
				m_speed = 1.6f;
				m_jamp_speed = 1.2f;
			}
			else
			{
				m_speed = 0.8f;
				m_jamp_speed = 0.6f;
			}

			if (Input::GetVKey('D') == true)  //右移動
			{
				m_vx += m_speed;
			}
			if (Input::GetVKey('A') == true)  //左移動
			{
				m_vx += -m_speed;
			}
			if (Input::GetVKey('W') == true && m_py > 277)//上移動
			{
				m_vy += -m_speed;
				if (m_jamp_control_2 == true) //ジャンプしてなければ通常移動　してれば遅くする
				{
					//ジャンプしているときにSを押したとき、影も動くようにする
					m_jamp_y_position += -m_speed - 0.8f;
				}
			}
			if (Input::GetVKey('S') == true && m_py < 536)//下移動
			{
				if (m_jamp_control_2 == false) //ジャンプしてなければ通常移動　してれば遅くする
				{
					m_vy += m_speed;
				}
				else
				{
					m_vy += m_speed - m_jamp_speed;
					//ジャンプしているときにSを押したとき、影も動くようにする

					m_jamp_y_position += m_speed + m_jamp_speed;
				}
			}

			//摩擦
			m_vx += -(m_vx * 0.15f);
			m_vy += -(m_vy * 0.15f);

			//移動終了---------------------------------------------------

			//聖火をかざす（火をうつす）---------------------------------------------

			if (m_hole_control == false)  //穴に落ちていない場合（当たっていない）
			{
				if (Input::GetVKey('O') == true)
				{
					if (m_torch_control == false)
					{

						m_ani_change = 3; //アニメーションの絵を3番に変える

						m_torch_control = true;
						//聖火を出現させる 
						if (m_jamp_control_2 == false)
						{
							CObjTorch* torch = new CObjTorch(m_px + 32.0f, m_py + 28.0f);
							Objs::InsertObj(torch, OBJ_TORCH, 20);
						}
					}
				}
				else
				{
					if (m_torch_time_control > 30) //30フレームたつと次が触れる
					{
						m_torch_control = false;

						m_ani_change = 2;//アニメーションを2に

						m_torch_time_control = 0;
					}
				}
			}

			if (m_torch_control == true) //降り下ろしてる状態なら
			{
				m_torch_time_control++;  //時間を進める。
			}

			//聖火をかざす終了-----------------------------------------------------------------------------

			//ジャンプ---------------------------
			//チェックポイントが出てきたらジャンプできない
			/*if (check == nullptr)
			{*/
			bool m_hag = false;
			if (okama != nullptr)
				m_hag = okama->GetHug();

			//ジャンプしていない
			if (m_jamp_control == false)
			{
				if (m_hag == false && m_hole_control == false) //抱きつかれてない、穴に落ちてない時ジャンプできる。
				{
					if (Input::GetVKey(VK_SPACE) == true)   //ジャンプする
					{
						m_jamp_y_position = m_py;
						m_jamp_control = true;		//ジャンプしている
						m_jamp_control_2 = true;
						Audio::Start(3);//ジャンプ音
					}
				}
			}

			if (m_jamp_control == true)//ジャンプしている
			{
				m_time++;
				if (m_time > 20 && m_time < 45) //ジャンプして最高点に到達
				{
					if (jamp_memo != 999.0f)    //ジャンプするとき上のほうにいなければWで少し移動できる
					{
						if (Input::GetVKey('W') == true)//上移動
						{
							if (m_py > 280)//道幅ギリギリ
								m_vy += m_jamp_y_1;
							else
								m_vy += -m_jamp_y_2;

						}
						else
						{
							m_vy += m_jamp_y_1;//自由落下運動
						}

					}
					else
						//ジャンプするとき上のほうにいた場合はただジャンプする
						m_vy += m_jamp_y_1;


				}
				else if (m_time < 20)
				{
					if (m_py < 280)//道幅ギリギリ
					{
						m_vy += -m_jamp_y_1;
						jamp_memo = 999.0f; //ジャンプする時上のほうにいた場合は記録する
					}
					else
					{
						if (Input::GetVKey('W') == true)//上移動
						{
							m_vy += -m_jamp_y_2;
						}
						else
						{
							m_vy += -m_jamp_y_1;//自由落下運動
						}
					}
				}
				if (m_time > 45 && m_time < 57)//時間が来たらジャンプを終了させる
				{
					m_jamp_control_2 = false;
					m_vy = 0.0f;
				}
				if (m_time > 90) //時間が来たら自由に動けるようになる (58デフォルト)
				{
					if (Input::GetVKey(VK_SPACE) == false)   //スペースを離さない限りジャンプさせない
					{
						m_jamp_control = false;
						m_time = 0;  //タイムを初期化
					}
				}
			}

			//}

			//ジャンプ終了ーーーーーーーーーーーーーーーーーーーーー

			//ブロック情報を持ってくる
			CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

			//穴関連ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
			if (m_hole_control == true)  //穴に落ちている場合（当たっている）
			{

				m_ani_change = 2;//アニメーションを2に
				m_stick_fire = false;//けつに火がついているフラグをオフにする
				m_vx = 0.0f; //ランナーを移動させないようにする。
				m_vy = 0.0f;
			}

			if (m_hole_fall > 3)
			{
				m_hole_control = true;
			}
			if (m_hole_fall < 5 && m_hole_fall > 3)
			{
				Audio::Start(4); //落ちている音を鳴らす
			}

			if (m_hole_fall > 50.0f)  //ランナーの描画が一番小さくなった時に
			{
				m_px = -80.0f;
				m_py = 410.0f;
				m_hole_control = false;
				m_death = true;
				Audio::Start(1);
				Audio::Stop(4);
			}
			//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー

			//後ろに行き過ぎた時ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー---

			if (m_px < -50.0f && m_death == false) //スクロールに遅れた時は真ん中で復活
			{
				//ジャンプ関連をすべて最初に戻す。
				m_time = 0;
				m_jamp_control = false;
				m_jamp_control_2 = false;
				//-----------------------------------------------
				m_death = true; //死んだ
				Audio::Start(1);
			}

			m_invincible--; //無敵時間減少


			//−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−

			//HitBoxの位置の変更
			CHitBox* hit = Hits::GetHitBox(this);
			hit->SetPos(m_px + 18.0f, m_py);

			//チェックポイントが生成されてるなら調べる
			if (check != nullptr)
			{
				//チェックポイントが指定の位置に
				if (check->GetX() + block->GetScroll() < 400)
				{
					m_check_vx = true; //強制スクロールをしなくさせないようにする
				}
			}
			if (m_check_vx == false)
			{
				//火がついているときは強制スクロールを二倍にする
				if (m_stick_fire == true)
					m_vx -= 0.6f; //強制スクロール用移動量
				else
					m_vx -= 0.3f;
			}

			//当たり判定関連
			HitBox();

			//位置の更新
			m_px += m_vx;
			m_py += m_vy;

			CObj::SetPrio((int)m_py); //描画優先順位変更
		}


		//チェックポイントに入ったら受け渡たすシーンを描画をする。
		else if (m_check_control == true && m_jamp_control_2 == false)
		{
			if (m_gool == false)
			{
				Audio::Start(7);
				Audio::Start(8);
				m_gool = true;
			}

			//チェックポイントを取得
			CObjCheckPoint* check = (CObjCheckPoint*)Objs::GetObj(OBJ_CHECK_POINT);

			//ステージ３の時はホーミングせずにそのまま突き進む
			if (((UserData*)Save::GetData())->m_stage_count == 3)
			{
				m_vx += 0.5f;

				//摩擦
				m_vx += -(m_vx * 0.15f);
				//位置の更新
				m_px += m_vx;
				m_py += m_vy;
			}
			else
			{
				if (m_check_control_x == true)
				{

					m_ani_change = 2;//アニメーションを2に


				//チェックポイントにいる第二のランナーの位置を取得する
					float okax = ((check->GetX() + block->GetScroll()) + 170.0f) - m_px;
					float okay = (check->GetY()  * 3.0f) - m_py;

					//atan2で角度を求める
					float r2 = atan2(okay, okax)*180.0f / 3.14f;

					//-180〜-0を180〜360に変換
					if (r2 < 0)
					{
						r2 = 360 - abs(r2);
					};

					float ar = r2;

					if (ar < 0)
					{
						ar = 360 - abs(ar);
					}

					//ランナーの現在の向いてる角度を取る
					float bor = atan2(m_vy, m_vx)*180.0f / 3.14f;

					//-180〜-0を180〜360に変換
					if (bor < 0)
					{
						bor = 360 - abs(bor);
					};
					float br = bor;

					//ランナーのほうにホーミングする
					if (m_homing == false)
					{
						//移動方向をランナーの方向にする
						m_vx = cos(3.14f / 180 * ar);
						m_vy = sin(3.14f / 180 * ar);
						m_vx *= 2; // 移動速度を2倍にする
						m_vy *= 2;
						m_homing = true;
					}


					//第二のランナーの目の前に来た時
					if (m_px > ((check->GetX() + block->GetScroll()) + 170.0f))
					{
						m_check_time++; //タイムを進める
						m_check_transfer = true;
						m_vx = 0.0f; //移動量を０にする
						m_vy = 0.0f;
						if (m_check_time < 50) //振り下ろす
							m_ani_change = 3;
						else
						{
							m_ani_change = 2;//通常の状態で待つ
						}
					}

					//位置の更新
					m_px += m_vx;
					m_py += m_vy;

					CObj::SetPrio((int)m_py); //描画優先順位変更
				}
			}
			// チェックポイントが指定の位置にある場合
			if (check->GetX() + block->GetScroll() < 400)
			{
				m_check_control_x = true; //ホーミングをONにする
			}
			else
			{
				// チェックポイントが指定のいちに行くまでは移動量を0にする
				if (m_px < 499 && m_px > 490)
				{
					m_vx = 0.0f;
				}
				else if (m_stick_fire == false) //火がついているときはスクロールに合わせた速度に。
					m_vx -= 0.3f; //強制スクロール用移動量
				else
					m_vx -= 0.6f; //強制スクロール用移動量

				//摩擦
				m_vx += -(m_vx * 0.15f);

				//HitBoxの位置の変更
				CHitBox* hit = Hits::GetHitBox(this);
				hit->SetPos(m_px + 18.0f, m_py);

				//位置の更新
				m_px += m_vx;
				m_py += m_vy;
			}
		}
		else if (m_jamp_control_2 == true) //ジャンプしてなければ通常移動　してれば遅くする
		{
			//スクロールが止まったら移動量を０にする
			if (check->GetX() + block->GetScroll() < 400)
			{
				//Xの移動量を０にする
				m_vx = 0.0f;
			}
			else if (m_stick_fire == false) //火がついているときはスクロールに合わせた速度に。
				m_vx -= 0.3f; //強制スクロール用移動量
			else
				m_vx -= 0.6f; //強制スクロール用移動量

			//摩擦
			m_vx += -(m_vx * 0.15f);

			//ジャンプしたときに記録した場所に行くまで落ちる		
			if (m_py >= m_jamp_y_position)
				m_jamp_control_2 = false;
			m_py += m_jamp_y_1;

			//位置の更新

			m_px += m_vx;
			m_py += m_vy;
		}
	}
}

//描画
void CObjRunner::Draw()
{
	//ランナー-----------------------------------------------------------------
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	//影の描画のためのカラー情報
	float shadowcolor[4] = { 1.0f,1.0f,1.0f,0.4f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	RECT_F src2; //描画元切り取り位置
	RECT_F dst2; //描画先表示位置

	//ゲージの情報を持ってくる
	CObjGauge* gau = (CObjGauge*)Objs::GetObj(OBJ_GAUGE);

	//ランナーのびょうが----------------------------------------------------
	
		//切り取り位置の設定 //足の先が上から見えていたので１.0ｆから
		//チェックポイントに入っていたら立ち姿に変える
		if (m_check_transfer == false)
		{
			src.m_top = 1.0f;
			src.m_left = 0.0f + m_ani_frame * 64;
			src.m_right = 64.0f + m_ani_frame * 64;
			src.m_bottom = 257.0f;
		}
		else
		{
			src.m_top = 1.0f;
			src.m_left = 0.0f + 64.0f;
			src.m_right = 64.0f + 64.0f;
			src.m_bottom = 257.0f;
		}

		//表示位置の設定
		dst.m_top = 0.0f + m_py + (m_hole_fall / 3);   //穴に落ちた時は描画を小さくする
		dst.m_left = 0.0f + m_px + (m_hole_fall /3);
		dst.m_right = 64.0f + m_px - m_hole_fall;
		dst.m_bottom = 64.0f + m_py - m_hole_fall;

		if (m_ani_change == 5)
		{
			src.m_top = 1.0f;
			src.m_left = 0.0f + m_ani_frame * 64;
			src.m_right = 64.0f + m_ani_frame * 64;
			src.m_bottom = 193.0f;

			//表示位置の設定
			dst.m_top = 0.0f + m_py;
			dst.m_left = 0.0f + m_px;
			dst.m_right = 64.0f + m_px;
			dst.m_bottom = 64.0f + m_py;

		}//描画
		Draw::Draw(m_ani_change, &src, &dst, c, 0.0f);
	
	
	
	//--------------------------------無敵点滅-----------------------------------　
	if (m_invincible > 0 && m_death == false)
	{
		//切り取り位置の設定 //足の先が上から見えていたので１.0ｆから
		src.m_top = 1.0f;
		src.m_left = 0.0f + m_ani_frame * 64;
		src.m_right = 64.0f + m_ani_frame * 64;
		src.m_bottom = 257.0f;

		//表示位置の設定
		dst.m_top = 0.0f + m_py;
		dst.m_left = 0.0f + m_px;
		dst.m_right = 64.0f + m_px;
		dst.m_bottom = 64.0f + m_py;

		//ゲージが消えそうになっていたら描画をやめる
		if (gau->GetGauge() < 191)
			Draw::Draw(4, &src, &dst, c, 0.0f);
	}

	//ーーーーーーーーーーーーーーーーー聖火のもつとこーーーーーーーーーーーー
	//切り取り位置の設定 
	src2.m_top = 1.0f;
	src2.m_left = 0.0f;
	src2.m_right = 64.0f;
	src2.m_bottom = 64.0f;

	//表示位置の設定
	if (m_ani_change == 2) //腕を振り下ろしていない
	{
		if (m_hole_control == true)  //穴に落ちている場合（当たっている）
		{
			dst2.m_top = 0.0f + m_py - 10.0f + (m_hole_fall / 2);
			dst2.m_left = 0.0f + m_px + 25.0f;
			dst2.m_right = 20.0f + m_px + 40.0f - (m_hole_fall / 2) - 10.0f;
			dst2.m_bottom = 32.0f + m_py - 10.0f;
		}
		else
		{
			dst2.m_top = 0.0f + m_py - 10.0f;
			dst2.m_left = 0.0f + m_px + 40.0f;
			dst2.m_right = 20.0f + m_px + 40.0f;
			dst2.m_bottom = 32.0f + m_py - 10.0f;
		}

		//描画
		Draw::Draw(11, &src2, &dst2, c, 0.0f);
	}
	else //腕を振り下ろしている
	{
		//ゲージが最後まで減ってない時
		if (gau->GetGauge() != 192)
		{
			dst2.m_top = 0.0f + m_py + 18.0f;
			dst2.m_left = 0.0f + m_px + 38.0f;
			dst2.m_right = 20.0f + m_px + 38.0f - m_hole_fall;
			dst2.m_bottom = 32.0f + m_py + 18.0f - m_hole_fall;
		}
		else
		{
			dst2.m_top = 0.0f + m_py + 50.0f;
			dst2.m_left = 0.0f + m_px + 45.0f;
			dst2.m_right = 20.0f + m_px + 45.0f - m_hole_fall;
			dst2.m_bottom = 32.0f + m_py + 50.0f - m_hole_fall;
		}

		//描画
		Draw::Draw(11, &src2, &dst2, c, -100.0f);
	}

	//−−−−−−−−−−−−−−−−−−炎ーーーーーーーーーーーーーー
	//描画カラー情報

	//ゲージが最後まで減ってない時に描画する
	if (gau->GetGauge() != 192)
	{
		RECT_F src3; //描画元切り取り位置
		RECT_F dst3; //描画先表示位置

		//切り取り位置の設定
		src3.m_top = 0.0f;
		src3.m_left = 0.0f + m_ani_frame * 64;
		src3.m_right = 64.0f + m_ani_frame * 64;
		src3.m_bottom = 320.0f;

		if (m_ani_change == 2)//腕を振り下ろしていない
		{
			if (m_hole_control == true)  //穴に落ちている場合（当たっている）
			{
				//表示位置の設定
				dst3.m_top = 0.0f + m_py - 30.0f + (m_hole_fall);
				dst3.m_left = 0.0f + m_px + 27.0f;
				dst3.m_right = 25.0f + m_px + 37.0f - (m_hole_fall / 1.5f) - 10.0f;
				dst3.m_bottom = 25.0f + m_py - 30.0f + (m_hole_fall / 2.0f);
			}
			else
			{
				//表示位置の設定
				dst3.m_top = 0.0f + m_py - 30.0f;
				dst3.m_left = 0.0f + m_px + 37.0f;
				dst3.m_right = 25.0f + m_px + 37.0f;
				dst3.m_bottom = 25.0f + m_py - 30.0f;
			}

			//描画
			Draw::Draw(9, &src3, &dst3, c, 0.0f);
		}
		else//腕を振り下ろしている
		{
			//表示位置の設定
			dst3.m_top = 0.0f + m_py + 26.0f;
			dst3.m_left = 0.0f + m_px + 52.0f;
			dst3.m_right = 25.0f + m_px + 52.0f - m_hole_fall;
			dst3.m_bottom = 25.0f + m_py + 26.0f - m_hole_fall;

			//描画
			Draw::Draw(9, &src3, &dst3, c, -100.0f);
		}
	}
	//影-------------------------------------------------------------
	//ジャンプしていないとき
	if (m_jamp_control_2 == false)
	{
		//穴に落ちていなければ描画
		if (m_hole_control == false)
		{
			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			//表示位置の設定
			dst.m_top = 60.0f + m_py;
			dst.m_left = -30.0f + m_px;
			dst.m_right = 55.0f + m_px;
			dst.m_bottom = 68.0f + m_py;

			//描画
			Draw::Draw(25, &src, &dst, c, 1.0f);
		}
	}
	//ジャンプしてる時
	else
	{
		//穴に落ちていなければ描画
		if (m_hole_control == false)
		{
			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			//表示位置の設定
			dst.m_top = 60.0f + m_jamp_y_position;
			dst.m_left = -30.0f + m_px;
			dst.m_right = 55.0f + m_px;
			dst.m_bottom = 68.0f + m_jamp_y_position;

			//描画
			Draw::Draw(25, &src, &dst, shadowcolor, 1.0f);
		}
	}
	//--------------------------------------------------------------
	//残機-------------------------------------------------------------------------------
	if ((((UserData*)Save::GetData())->m_stage_count ==1))
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 192.0f;

		//表示位置の設定
		dst.m_top = 0.0f + 10.0f;
		dst.m_left = 0.0f + 680.0f;
		dst.m_right = 40.0f + 680.0f;
		dst.m_bottom = 40.0f + 10.0f;
	}
	if ((((UserData*)Save::GetData())->m_stage_count == 2))
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 64.0f;
		src.m_right = 128.0f;
		src.m_bottom = 192.0f;

		//表示位置の設定
		dst.m_top = 0.0f + 10.0f;
		dst.m_left = 0.0f + 680.0f;
		dst.m_right = 40.0f + 680.0f;
		dst.m_bottom = 40.0f + 10.0f;
	}
	if ((((UserData*)Save::GetData())->m_stage_count == 3))
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 128.0f;
		src.m_right = 192.0f;
		src.m_bottom = 192.0f;

		//表示位置の設定
		dst.m_top = 0.0f + 10.0f;
		dst.m_left = 0.0f + 680.0f;
		dst.m_right = 40.0f + 680.0f;
		dst.m_bottom = 40.0f + 10.0f;
	}
	//残りの数字を描画する
	static wchar_t  c_siro[8];
	static float cl_siro[4] = { 0.0f,0.0f,0.0f,1.0f };
	swprintf_s(c_siro, L"X %d", m_remaining);
	CDrawFont::StrDraw(c_siro, 735, 16, 32, cl_siro);

	//描画
	Draw::Draw(24, &src, &dst, c, 0.0f);
	//---------------------------------------------------------------------------------

	//得点の描画ーーーーーーーーーーーーーーーーーーーーーーーーーーー
	float cc[4] = { 0.0f,0.0f,0.0f,1.0f };
	wchar_t str[128];
	swprintf_s(str, L"得点：%d点", ((UserData*)Save::GetData())->m_point);
	Font::StrDraw(str, 350, 16, 32, cc);
	//−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
}

void CObjRunner::HitBox()
{
	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//ゲージ情報を持ってくる
	CObjGauge* gauge = (CObjGauge*)Objs::GetObj(OBJ_GAUGE);

	//スマホ少年の位置を取得
	CObjSmartphone* sumaho = (CObjSmartphone*)Objs::GetObj(OBJ_SMARTPHONE);

	if (m_invincible < 0 && m_death == false) //無敵時間じゃなければ
	{
		if (m_hole_control == false)  //穴に落ちている場合（当たっている）
		{
			//スマホ少年と当たった場合
			if (hit->CheckObjNameHit(OBJ_SMARTPHONE) != nullptr && m_jamp_control_2 == false)
			{
				if ((sumaho->GetX() + block->GetScroll()) < m_px)
				{
					m_vx = 3.6f;//ランナーをずらす
				}
				else
				{
					m_vx = -5.6f;//ランナーをずらす
				}

				//ゲージを減らすーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
				if (m_smart_control == false) //まだ当たってなければゲージを減らす
				{
					//ゲージが減る
					gauge->SetGauge(1.0f);
					m_smart_control = true;
				}
			}
			else
				m_smart_control = false;//当たってない状態ならゲージを減らせる状態に戻す
		}
	}

	//チェックポイントと当たった場合
	if (hit->CheckObjNameHit(OBJ_CHECK_POINT) != nullptr)
	{
		m_check_control = true;
		m_vx = 0.0f;
		m_vy = 0.0f;
	}

	//炎に当たった場合
	if (hit->CheckObjNameHit(OBJ_FIRE) != nullptr)
	{
		//一個だけ火が付く
		if (m_stick_fire == false && m_rain_time == true)
		{

			CObjFire* fi = new CObjFire(m_px, m_py, 2);
			Objs::InsertObj(fi, OBJ_FIRE, 999);
			m_stick_fire = true;
		}
	}

	//水に当たった場合
	if (hit->CheckObjNameHit(OBJ_PUDDLE) != nullptr)
	{
		//ランナーに火がついてるなら消える
		if(m_jamp_control_2 == false) //ジャンプしているときは火は消えない
			m_stick_fire = false;
	}
	//雨が降った場合
	if (m_rain == true)
	{
		m_stick_fire = false;
		if (m_rain_time == true)
		{
			m_rain = false;
		}
	}
}