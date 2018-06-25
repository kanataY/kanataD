#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

#define RANKING_MAX_COUNT 3
#define RETURN_SIZE 20

//オブジェクト：ランキング
class CObjRanking : public CObj
{
public:
	CObjRanking() {};
	~CObjRanking() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	float StringSize(wchar_t *str);
	void DrawNumber(float dst_top, float dst_left, float dst_size, int num);
private:
	float m_return_size;	//戻るときの文字のサイズ
};