#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjGameClear : public CObj
{
public:
	CObjGameClear() {};
	~CObjGameClear() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	int GetTime() { return m_time; }
	bool GetRankingInFlag() { return m_ranking_in_floag; }
private:
	int m_time; //時間管理
	int m_ani_time; //アニメーションフレーム動作感覚
	int m_ani_frame;//描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値
	bool m_o_tap_flag;  //oを押した時のフラグ

	bool m_audio_flag;  //音楽を鳴らすときのフラグ
	bool m_ranking_in_floag; //ランキング入りしたかどうかフラグ　ON:した　OFF：していない
	void Ranking();//スコアの結果がランキングの中にランクインしたかどうかを調べる関数
};
