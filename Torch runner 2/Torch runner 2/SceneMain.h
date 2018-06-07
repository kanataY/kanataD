#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

#define MAP_X 200
#define MAP_Y 10

//シーン：メイン
class CSceneMain : public CScene
{
public:
	CSceneMain(int r);
	~CSceneMain();
	void InitScene();//初期化メソッド
	void Scene();	 //実行中メソッド
private:
	int remaining;//残機管理
	void MapCreate(int map[][MAP_X]);	//ステージ番号ごとにマップ作成
};
