#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：ランキング
class CSceneRanking : public CScene
{
public:
	CSceneRanking();
	~CSceneRanking();
	void InitScene();//ランキングの初期化メソッド
	void Scene();	 //ランキングの実行中メソッド
private:
};