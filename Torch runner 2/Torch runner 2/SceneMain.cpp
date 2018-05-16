//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneMain.h"
#include "GameHead.h"


CSceneMain::CSceneMain()
{

}


//デストラクタ
CSceneMain::~CSceneMain()
{

}

//初期化メソッド
void CSceneMain::InitScene()
{
	//マップ作製
	int map[MAP_Y][MAP_X];
	MapCreate(map);

	//外部グラフィックファイルを読み込み0番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\hero\\hero1.png", 0, TEX_SIZE_256);    //人間1

	//外部グラフィックファイルを読み込み1番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back\\back1.png", 1, TEX_SIZE_1024); //背景仮  1

	//外部グラフィックファイルを読み込み2番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back\\back2.png", 2, TEX_SIZE_1024); //背景仮   2

	//外部グラフィックファイルを読み込み3番に登録(192ピクセル)
	Draw::LoadImageW(L"Image\\object\\Fire Gauge.png", 3, TEX_SIZE_192);    //ゲージ

	//外部グラフィックファイルを読み込み4番に登録(64ピクセル)
	Draw::LoadImageW(L"Image\\object\\Cratesx64.png", 4, TEX_SIZE_64);    //木箱

	//外部グラフィックファイルを読み込み4番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\object\\Smartphone.png", 5, TEX_SIZE_256);    //スマホ少年

	//外部グラフィックファイルを読み込み4番に登録(320ピクセル)
	Draw::LoadImageW(L"Image\\object\\Fire.png", 6, TEX_SIZE_320);    //炎

	//外部グラフィックファイルを読み込み4番に登録(64ピクセル)
	Draw::LoadImageW(L"Image\\object\\Puddle.png", 7, TEX_SIZE_64);    //水たまり

	//外部グラフィックファイルを読み込み0番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\hero\\hero2.png", 8, TEX_SIZE_256);    //人間2

	//外部グラフィックファイルを読み込み0番に登録(64ピクセル)
	Draw::LoadImageW(L"Image\\object\\torch.png", 9, TEX_SIZE_64);    //聖火の持つとこ

	//外部グラフィックファイルを読み込み0番に登録(800ピクセル)
	Draw::LoadImageW(L"Image\\back\\Rain\\rain1.png", 10, TEX_SIZE_800);    //雨１

	//外部グラフィックファイルを読み込み0番に登録(800ピクセル)
	Draw::LoadImageW(L"Image\\back\\Rain\\a3.png", 11, TEX_SIZE_800);    //雨２

	//外部グラフィックファイルを読み込み0番に登録(128ピクセル)
	Draw::LoadImageW(L"Image\\object\\okama.png", 12, TEX_SIZE_128);    //オカマ

	//主人公オブジェクト作成
	CObjRunner* obj = new CObjRunner();
	Objs::InsertObj(obj, OBJ_RUNNER, 13);

	//背景（ブロック）オブジェクト作成
	CObjBlock* block = new CObjBlock(map);
	Objs::InsertObj(block, OBJ_BLOCK, 10);

	//ゲージオブジェクト作成
	CObjGauge* gauge = new CObjGauge();
	Objs::InsertObj(gauge, OBJ_GAUGE, 13);

	//炎
	CObjFire* fi = new CObjFire(30.0f, 400.0f);
	Objs::InsertObj(fi, OBJ_FIRE, 13);

	//オカマバズーカ
	CObjOkama* o = new CObjOkama(800.0f, 450.0f);
	Objs::InsertObj(o, OBJ_OKAMA, 13);

	/*CObjOkama* o2 = new CObjOkama(800.0f, 500.0f);
	Objs::InsertObj(o2, OBJ_OKAMA, 13);

	CObjOkama* o3 = new CObjOkama(800.0f, 550.0f);
	Objs::InsertObj(o3, OBJ_OKAMA, 13);

	CObjOkama* o4 = new CObjOkama(800.0f, 600.0f);
	Objs::InsertObj(o4, OBJ_OKAMA, 13);

	CObjOkama* o5 = new CObjOkama(800.0f, 350.0f);
	Objs::InsertObj(o5, OBJ_OKAMA, 13);

	CObjOkama* o6 = new CObjOkama(800.0f, 300.0f);
	Objs::InsertObj(o6, OBJ_OKAMA, 13);*/

	//
	//CObjRain* r = new CObjRain(0.0f, 0.0f);
	//Objs::InsertObj(r, OBJ_RAIN, 1300);
}

//実行中メソッド
void CSceneMain::Scene()
{

}

//ステージごとのマップ作成
void CSceneMain::MapCreate(int map[][MAP_X])
{
	//外部データの読み込み（ステージ情報）
	unique_ptr<wchar_t> p; //ステージ情報ポインター
	int size;			   //ステージ情報の大きさ

	//ステージごとにステージの名前を格納
	switch (((UserData*)Save::GetData())->m_stage_count = 1)
	{
	case 1:
		p = Save::ExternalDataOpen(L"Stage1.csv", &size);//外部データ読み込み
		break;

		break;
	default:
		MessageBox(0, L"ステージ番号が正しくありません。", NULL, MB_OK);
		break;
	}

	//外部データが読み込めなかったらエラーメッセージを出す。
	if (p == NULL)
	{
		MessageBox(0, L"外部データが読み込めませんでした。", NULL, MB_OK);
	}
	int count = 1;
	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			if (w > 9)//10を超えた場合
				count += 3;//ずらす数を増やす
			else
				count += 2;
		}
	}
}