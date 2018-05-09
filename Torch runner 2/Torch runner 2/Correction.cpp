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

	if (y > 536.0f)  //歩ける範囲より下にいる場合ギリギリまで戻す
		return 536.0f;
	else if (y < 277.0f)//歩ける範囲より上にいる場合ギリギリまで戻す
		return 277.0f;

	return y;
}