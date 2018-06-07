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
	Draw::LoadImageW(L"Image\\hero\\runner.png", 0, TEX_SIZE_256);    //第一走者
	//外部グラフィックファイルを読み込み1番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back\\back1.png", 1, TEX_SIZE_1024); //背景仮  1
	//外部グラフィックファイルを読み込み2番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back\\back2.png", 2, TEX_SIZE_1024); //背景仮   2
	//外部グラフィックファイルを読み込み3番に登録(192ピクセル)
	Draw::LoadImageW(L"Image\\object\\Fire Gauge.png", 3, TEX_SIZE_192);    //ゲージ
	//外部グラフィックファイルを読み込み4番に登録(64ピクセル)
	Draw::LoadImageW(L"Image\\object\\Cratesx64.png", 4, TEX_SIZE_64);    //木箱
	//外部グラフィックファイルを読み込み5番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\object\\Smartphone.png", 5, TEX_SIZE_256);    //スマホ少年
	//外部グラフィックファイルを読み込み6番に登録(320ピクセル)
	Draw::LoadImageW(L"Image\\object\\Fire.png", 6, TEX_SIZE_320);    //炎
	//外部グラフィックファイルを読み込み7番に登録(64ピクセル)
	Draw::LoadImageW(L"Image\\object\\Puddle.png", 7, TEX_SIZE_64);    //水たまり
	//外部グラフィックファイルを読み込み8番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\hero\\runner_transfer.png", 8, TEX_SIZE_256);    //一走者の火をうつすモーション
	//外部グラフィックファイルを読み込み9番に登録(64ピクセル)
	Draw::LoadImageW(L"Image\\object\\torch.png", 9, TEX_SIZE_64);    //聖火の持つとこ
	//外部グラフィックファイルを読み込み10番に登録(800ピクセル)
	Draw::LoadImageW(L"Image\\back\\Rain\\rain1.png", 10, TEX_SIZE_800);    //雨１
	//外部グラフィックファイルを読み込み11番に登録(800ピクセル)
	Draw::LoadImageW(L"Image\\back\\Rain\\a3.png", 11, TEX_SIZE_800);    //雨２
	//外部グラフィックファイルを読み込み12番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\object\\okama.png", 12, TEX_SIZE_512);    //オカマ
	//外部グラフィックファイルを読み込み13番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\object\\okama2.png", 13, TEX_SIZE_512);    //オカマ(目がハート)
	//外部グラフィックファイルを読み込み14番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\object\\okama_hug.png", 14, TEX_SIZE_512);    //オカマハグ
	//外部グラフィックファイルを読み込み15番に登録(64ピクセル)
	Draw::LoadImageW(L"Image\\object\\hole.png", 15, TEX_SIZE_64);    //穴
	//外部グラフィックファイルを読み込み16番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\object\\characterkey.png", 16, TEX_SIZE_256);    //文字キー
    //外部グラフィックファイルを読み込み17番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\object\\battered.png", 17, TEX_SIZE_256);    //押せ！！！の文字
	//外部グラフィックファイルを読み込み18番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\back\\checkpoint.png", 18, TEX_SIZE_256);    //チェックポイント
	//外部グラフィックファイルを読み込み19番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\hero\\youtuber.png", 19, TEX_SIZE_256);    //YouTubeｒ
	//外部グラフィックファイルを読み込み20番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\hero\\youtuber_transfer.png", 20, TEX_SIZE_256);    //YouTubeｒの振りかざし
	//外部グラフィックファイルを読み込み21番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\object\\Track.png", 21, TEX_SIZE_512);    //トラック
	//外部グラフィックファイルを読み込み22番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\hero\\runner_invincible.png", 22, TEX_SIZE_256);    //第一走者の点滅
	//外部グラフィックファイルを読み込み23番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\hero\\youtuber_invincible.png", 23, TEX_SIZE_256);    //YouTuberの点滅
	//外部グラフィックファイルを読み込み24番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\object\\warning.png", 24, TEX_SIZE_128);    //警告
																	  
	//主人公オブジェクト作成
	CObjRunner* obj = new CObjRunner();
	Objs::InsertObj(obj, OBJ_RUNNER, 13);

	//背景（ブロック）オブジェクト作成
	CObjBlock* block = new CObjBlock(map);
	Objs::InsertObj(block, OBJ_BLOCK, 10);

	//ゲージオブジェクト作成
	CObjGauge* gauge = new CObjGauge();
	Objs::InsertObj(gauge, OBJ_GAUGE, 13);

	//補正オブジェクト作成
	CObjCorrection* cor = new CObjCorrection();
	Objs::InsertObj(cor, CORRECTION, 13);

	//オカマバズーカ
	/*CObjOkama* o = new CObjOkama(800.0f, 450.0f);
	Objs::InsertObj(o, OBJ_OKAMA, 13);
*/
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

	/*
	CObjRain* r = new CObjRain(0.0f, 0.0f);
	Objs::InsertObj(r, OBJ_RAIN, 1300);*/

	//CObjTrack* t = new CObjTrack(600, 400);
	//Objs::InsertObj(t, OBJ_TRACK, 30);

	//CObjWarning* war = new CObjWarning(500, 400);
	//Objs::InsertObj(war, OBJ_WARNING, 20);
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