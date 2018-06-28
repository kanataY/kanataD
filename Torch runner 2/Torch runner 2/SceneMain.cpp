//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneMain.h"
#include "GameHead.h"


CSceneMain::CSceneMain(int r)
{
	remaining = r;	//残機
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
	//ステージごとに主人公と背景を格納
	switch (((UserData*)Save::GetData())->m_stage_count)
	{
	case 1://ステージが1の時
		//背景の画像登録-------------------------------------------------------------------
		//外部グラフィックファイルを読み込み0番に登録(1024ピクセル)
		Draw::LoadImageW(L"Image\\back\\back\\back1-1.png", 0, TEX_SIZE_1024); //背景1
		//外部グラフィックファイルを読み込み1番に登録(1024ピクセル)
		Draw::LoadImageW(L"Image\\back\\back\\back2-1.png", 1, TEX_SIZE_1024); //背景2  
		//外部グラフィックファイルを読み込み29番に登録(1024ピクセル)
		Draw::LoadImageW(L"Image\\back\\back\\back_final.png", 26, TEX_SIZE_1024); //背景最後
		//----------------------------------------------------------------------------------

		//ランナーの画像登録-------------------------------------------------------------------------------------
		//外部グラフィックファイルを読み込み2番に登録(256ピクセル)
		Draw::LoadImageW(L"Image\\hero\\runner.png", 2, TEX_SIZE_256);    //第一走者
		//外部グラフィックファイルを読み込み3番に登録(256ピクセル)
		Draw::LoadImageW(L"Image\\hero\\runner_transfer.png", 3, TEX_SIZE_256);    //一走者の火をうつすモーション
		//外部グラフィックファイルを読み込み4番に登録(256ピクセル)
		Draw::LoadImageW(L"Image\\hero\\runner_invincible.png", 4, TEX_SIZE_256);    //第一走者の点滅
		//外部グラフィックファイルを読み込み5番に登録(192ピクセル)
		Draw::LoadImageW(L"Image\\hero\\runner_death.png", 5, TEX_SIZE_192);  //第一走者の死亡

		//ランナ--------------------------------------------------------------------------------------
		//外部グラフィックファイルを読み込み27番に登録(256ピクセル)
		Draw::LoadImageW(L"Image\\hero\\youtuber.png", 27, TEX_SIZE_256);    //YouTuber
		//外部グラフィックファイルを読み込み28番に登録(256ピクセル)
		Draw::LoadImageW(L"Image\\hero\\youtuber_transfer.png", 28, TEX_SIZE_256);  //YouTuberの振りかざし
		//---------------------------------------------------------------------------------------------

		//おかま系--------------------------------------------------------------------------------------------
		//外部グラフィックファイルを読み込み14番に登録(512ピクセル)
		Draw::LoadImageW(L"Image\\object\\okama.png", 14, TEX_SIZE_512);    //オカマ
		//外部グラフィックファイルを読み込み15番に登録(512ピクセル)
		Draw::LoadImageW(L"Image\\object\\okama2.png", 15, TEX_SIZE_512);    //オカマ(目がハート)
		//外部グラフィックファイルを読み込み16番に登録(512ピクセル)
		Draw::LoadImageW(L"Image\\object\\okama_hug.png", 16, TEX_SIZE_512);    //オカマハグ
		//-----------------------------------------------------------------------------------－－－－－－－－－－－-------

		break;

	case 2://ステージが2の時
		//背景の画像登録-------------------------------------------------------------------
		//外部グラフィックファイルを読み込み0番に登録(1024ピクセル)
		Draw::LoadImageW(L"Image\\back\\back\\back1-2.png", 0, TEX_SIZE_1024); //背景1
		//外部グラフィックファイルを読み込み1番に登録(1024ピクセル)
		Draw::LoadImageW(L"Image\\back\\back\\back2-2.png", 1, TEX_SIZE_1024); //背景2
		//外部グラフィックファイルを読み込み26番に登録(1024ピクセル)
		Draw::LoadImageW(L"Image\\back\\back\\back_final2.png", 26, TEX_SIZE_1024); //背景最後
		//---------------------------------------------------------------------------------------------

		//ランナ--------------------------------------------------------------------------------------
		//外部グラフィックファイルを読み込み2番に登録(256ピクセル)
		Draw::LoadImageW(L"Image\\hero\\youtuber.png", 2, TEX_SIZE_256);    //YouTuber
		//外部グラフィックファイルを読み込み3番に登録(256ピクセル)
		Draw::LoadImageW(L"Image\\hero\\youtuber_transfer.png", 3, TEX_SIZE_256);  //YouTuberの振りかざし
		//外部グラフィックファイルを読み込み4番に登録(256ピクセル)
		Draw::LoadImageW(L"Image\\hero\\youtuber_invincible.png", 4, TEX_SIZE_256);    //YouTuberの点滅
		//外部グラフィックファイルを読み込み5番に登録(192ピクセル)
		Draw::LoadImageW(L"Image\\hero\\youtuber_death.png", 5, TEX_SIZE_192);    //YouTuberの死亡
		//-------------------------------------------------------------------------------------

		//ゴール地点のランナ--------------------------------------------------------------------------------------
		//外部グラフィックファイルを読み込み27番に登録(256ピクセル)
		Draw::LoadImageW(L"Image\\hero\\grandfather.png", 27, TEX_SIZE_256);    //おじいさん
		//外部グラフィックファイルを読み込み28番に登録(256ピクセル)
		Draw::LoadImageW(L"Image\\hero\\grandfather_transfer.png", 28, TEX_SIZE_256);  //おじいさんの振りかざし
		//---------------------------------------------------------------------------------------------

		//おかま系--------------------------------------------------------------------------------------------
		//外部グラフィックファイルを読み込み14番に登録(512ピクセル)
		Draw::LoadImageW(L"Image\\object\\fan.png", 14, TEX_SIZE_512);    //ファン
		//外部グラフィックファイルを読み込み15番に登録(512ピクセル)
		Draw::LoadImageW(L"Image\\object\\fan2.png", 15, TEX_SIZE_512);    //ファン目がハート
		//外部グラフィックファイルを読み込み16番に登録(512ピクセル)
		Draw::LoadImageW(L"Image\\object\\fan_hug.png", 16, TEX_SIZE_512);    //ファンハグ
	
		//---------------------------------------------------------------------------------------------

		break;
	case 3://ステージが3の時
		//背景の画像登録-------------------------------------------------------------------
		//外部グラフィックファイルを読み込み0番に登録(1024ピクセル)
		Draw::LoadImageW(L"Image\\back\\back\\back1.png", 0, TEX_SIZE_1024); //背景1
		//外部グラフィックファイルを読み込み1番に登録(1024ピクセル)
		Draw::LoadImageW(L"Image\\back\\back\\back2.png", 1, TEX_SIZE_1024); //背景2
		//外部グラフィックファイルを読み込み26番に登録(1024ピクセル)
		Draw::LoadImageW(L"Image\\back\\back\\back_final3.png", 26, TEX_SIZE_1024); //背景最後
		//---------------------------------------------------------------------------------------------

		//ランナ--------------------------------------------------------------------------------------
		//外部グラフィックファイルを読み込み2番に登録(256ピクセル)
		Draw::LoadImageW(L"Image\\hero\\grandfather.png", 2, TEX_SIZE_256);    //主人公3
		//外部グラフィックファイルを読み込み3番に登録(256ピクセル)
		Draw::LoadImageW(L"Image\\hero\\grandfather_transfer.png", 3, TEX_SIZE_256);    //主人公3の移す
		//外部グラフィックファイルを読み込み4番に登録(256ピクセル)
		Draw::LoadImageW(L"Image\\hero\\grandfather_invincible.png", 4, TEX_SIZE_256);    //主人公3の無敵
		//外部グラフィックファイルを読み込み5番に登録(256ピクセル)
		Draw::LoadImageW(L"Image\\hero\\grandfather_death.png", 5, TEX_SIZE_192);    //主人公3の死亡
		//----------------------------------------------------------------------------------------

		//おかま系--------------------------------------------------------------------------------------------
		//外部グラフィックファイルを読み込み14番に登録(512ピクセル)
		Draw::LoadImageW(L"Image\\object\\grandmother.png", 14, TEX_SIZE_512);    //ばあさん
		//外部グラフィックファイルを読み込み15番に登録(512ピクセル)
		Draw::LoadImageW(L"Image\\object\\grandmother2.png", 15, TEX_SIZE_512);    //ばあさん(目がハート)
		//外部グラフィックファイルを読み込み16番に登録(512ピクセル)
		Draw::LoadImageW(L"Image\\object\\grandmother_hug.png", 16, TEX_SIZE_512);    //ばあさんハグ
		//---------------------------------------------------------------------------------------------

		break;
	}
	
	
	//外部グラフィックファイルを読み込み6番に登録(192ピクセル)
	Draw::LoadImageW(L"Image\\object\\Fire Gauge.png", 6, TEX_SIZE_192);    //ゲージ
	//外部グラフィックファイルを読み込み7番に登録(64ピクセル)
	Draw::LoadImageW(L"Image\\object\\Cratesx64.png", 7, TEX_SIZE_64);    //木箱
    //外部グラフィックファイルを読み込み8番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\object\\Smartphone.png", 8, TEX_SIZE_256);    //スマホ少年
	//外部グラフィックファイルを読み込み9番に登録(320ピクセル)
	Draw::LoadImageW(L"Image\\object\\Fire.png", 9, TEX_SIZE_320);    //炎
	//外部グラフィックファイルを読み込み10番に登録(64ピクセル)
	Draw::LoadImageW(L"Image\\object\\Puddle.png", 10, TEX_SIZE_64);    //水たまり
	//外部グラフィックファイルを読み込み11番に登録(64ピクセル)
	Draw::LoadImageW(L"Image\\object\\torch.png", 11, TEX_SIZE_64);    //聖火の持つとこ
	//外部グラフィックファイルを読み込み12番に登録(800ピクセル)
	Draw::LoadImageW(L"Image\\back\\Rain\\rain1.png", 12, TEX_SIZE_800);    //雨１
	//外部グラフィックファイルを読み込み13番に登録(800ピクセル)
	Draw::LoadImageW(L"Image\\back\\Rain\\a3.png", 13, TEX_SIZE_800);    //雨２
	//外部グラフィックファイルを読み込み17番に登録(64ピクセル)
	Draw::LoadImageW(L"Image\\object\\hole.png", 17, TEX_SIZE_64);    //穴
	//外部グラフィックファイルを読み込み18番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\object\\characterkey.png", 18, TEX_SIZE_256);    //文字キー
	//外部グラフィックファイルを読み込み19番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\object\\battered.png", 19, TEX_SIZE_256);    //押せ！！！の文字
	//外部グラフィックファイルを読み込み20番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\back\\checkpoint.png", 20, TEX_SIZE_256);    //チェックポイント
    //外部グラフィックファイルを読み込み21番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\object\\Track.png", 21, TEX_SIZE_512);    //トラック
	//外部グラフィックファイルを読み込み22番に登録(128ピクセル)
	Draw::LoadImageW(L"Image\\object\\warning.png", 22, TEX_SIZE_128);    //警告
	//外部グラフィックファイルを読み込み23番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\object\\Track2.png", 23, TEX_SIZE_512);    //トラック2
	//外部グラフィックファイルを読み込み24番に登録(128ピクセル)
	Draw::LoadImageW(L"Image\\hero\\remaining.png", 24, TEX_SIZE_192);    //残機
	//外部グラフィックファイルを読み込み28番に登録(64ピクセル)
	Draw::LoadImageW(L"Image\\hero\\Shadow.png", 25, TEX_SIZE_64);    //影

	//主人公オブジェクト作成
	CObjRunner* obj = new CObjRunner(remaining);
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


	//音楽読み込み
	Audio::LoadAudio(0, L"BGM&SE\\BGMGameMain_.wav", BACK_MUSIC);

	Audio::LoadAudio(1, L"BGM&SE\\dashu_.wav", EFFECT); // 走る音
	Audio::LoadAudio(2, L"BGM&SE\\Fier2__.wav", EFFECT); // 燃える音
	Audio::LoadAudio(3, L"BGM&SE\\jump_.wav", EFFECT);  // ジャンプ
	Audio::LoadAudio(4, L"BGM&SE\\rakka_.wav", EFFECT); // 落ちる音
	Audio::LoadAudio(5, L"BGM&SE\\water_.wav", EFFECT); // 水に落ちた音
	Audio::LoadAudio(6, L"BGM&SE\\track_.wav", EFFECT); // トラック
	Audio::LoadAudio(7, L"BGM&SE\\gool.wav", EFFECT); // チェックポイントの歓声
	Audio::LoadAudio(8, L"BGM&SE\\gool2.wav", EFFECT); // チェックポイントの歓声2
	Audio::LoadAudio(9, L"BGM&SE\\himei.wav", EFFECT); // オカマの悲鳴
	Audio::LoadAudio(10, L"BGM&SE\\kiss.wav", EFFECT); // オカマのキス


	////ボリュームを1.5増やす
	//float v = Audio::VolumeMaster(1.5);

	//音楽スタート
	Audio::Start(0);
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
	switch (((UserData*)Save::GetData())->m_stage_count)
	{
	case 1:
		p = Save::ExternalDataOpen(L"Stage01.csv", &size);//外部データ読み込み
		break;
	case 2:
		p = Save::ExternalDataOpen(L"Stage02.csv", &size);//外部データ読み込み
		break;
	case 3:
		p = Save::ExternalDataOpen(L"Stage03.csv", &size);//外部データ読み込み
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