//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "Correction.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjCorrection::Init()
{
	m_py = 0.0f;
	m_px = 0.0f;
}

//オブジェクト生成したときにYが歩ける範囲より外か中だったら調整する
float CObjCorrection::RangeY(float y)
{

	if (y > OUTOFRANGE_DOWN)  //歩ける範囲より下にいる場合ギリギリまで戻す
		return OUTOFRANGE_DOWN;
	else if (y < OUTOFRANGE_UP)//歩ける範囲より上にいる場合ギリギリまで戻す
		return OUTOFRANGE_UP;

	return y;
}

//オブジェクト生成したときにYが歩ける範囲より外か中だったら調整する水たまりバージョン
float CObjCorrection::RangeYPuddle(float y)
{

	if (y > OUTOFRANGE_DOWN_PUDDLE)  //歩ける範囲より下にいる場合ギリギリまで戻す
		return OUTOFRANGE_DOWN_PUDDLE;
	else if (y < OUTOFRANGE_UP_PUDDLE)//歩ける範囲より上にいる場合ギリギリまで戻す
		return OUTOFRANGE_UP_PUDDLE;

	return y;
}

//炎を複数表示させる
void CObjCorrection::FireDisplay(float x, float y)
{
	//炎
	CObjFire* fi = new CObjFire(x - 10.0f , y -10.0f);
	Objs::InsertObj(fi, OBJ_FIRE, 20);
	//炎2
	CObjFire* fi2 = new CObjFire(x + 30.0f, y + 10.0f);
	Objs::InsertObj(fi2, OBJ_FIRE, 20);
	//炎3
	CObjFire* fi3 = new CObjFire(x + 12.0f, y + 35.0f);
	Objs::InsertObj(fi3, OBJ_FIRE, 20);
}