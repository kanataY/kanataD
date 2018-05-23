#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

#define OUTOFRANGE_UP 277.0f		  //範囲外かどうか調べる値
#define OUTOFRANGE_DOWN 536.0f
#define OUTOFRANGE_UP_PUDDLE 328.0f   //範囲外かどうか調べる値　水たまりバージョン
#define OUTOFRANGE_DOWN_PUDDLE 536.0f

//オブジェクト：補正
class CObjCorrection : public CObj
{
public:
	CObjCorrection();
	~CObjCorrection() {};
	void Init();									//イニシャライズ
	void Action();									//アクション
	void Draw();									//ドロー
	float RangeY(float y);							//範囲外にいるときにただす
	float RangeYPuddle(float y);					//範囲外にいるときにただす水たまりバージョン
	void  FireDisplay(float x, float y);			//炎を複数表示させる
	//void  FireDisplayTracking(float x, float y);		//炎を複数表示させる追尾バージョン
	bool  Screen_Out(float x);						//画面外に行くと消える処理
private:
	float m_px;		//位置
	float m_py;
	bool  m_screen_out;  //画面外にいったどうかを入れる変数
	bool m_hole_control;			//穴制御
};