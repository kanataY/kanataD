#pragma once

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記
	OBJ_RUNNER,				//ランナー
	OBJ_BLOCK,				//ブロック
	OBJ_GAUGE,				//ゲージ
	OBJ_CRATES,				//木箱
	OBJ_SMARTPHONE,			//スマホ少年
	OBJ_FIRE,				//炎
	OBJ_TORCH,				//聖火
	OBJ_PUDDLE,				//水たまり
	OBJ_RAIN,               //雨
	OBJ_OKAMA,              //オカマ
	OBJ_HOLE,				//穴
	OBJ_CHECK_POINT,		//チェックポイント

	//補正
	CORRECTION,				//補正

	//シーン
	OBJ_TITLE,				//タイトル
	OBJ_GAME_OVER,			//ゲームオーバー
	OBJ_GAME_CLEAR,			//ゲームクリア
	OBJ_RANKING,			//ランキング
	OBJ_MENU,				//メニュー
};
//------------------------------------------------

//当たり判定属性----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//属性無し 全ての属性と当たり判定が実行される
	//以下　同じ属性同士では当たり判定は実行されない
	//属性は追加可能だが、デバック時の色は初期設定分しか無い
	ELEMENT_RUNNER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
};
//------------------------------------------------

//------------------------------------------------
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	int mSeveData;	//サンプルセーブデータ
	int m_stage_count;//ステージの種類
	int m_ranking[10];	//ランキング格納配列
	int m_zainki;       //残機
	int m_point;		//GameMainで得たポイント
	
};
//------------------------------------------------


//ゲーム内で使用されるグローバル変数・定数・列挙--


//------------------------------------------------
//ゲーム内で使用するクラスヘッダ------------------


//------------------------------------------------

//ゲームシーンオブジェクトヘッダ------------------
#include "ObjRunner.h"			//ランナー
#include "ObjBlock.h"			//ブロック
#include "ObjGauge.h"			//ゲージ	
#include "ObjTitle.h"			//タイトル
#include "ObjCrates.h"			//木箱
#include "ObjSmartPhone.h"		//スマホ少年
#include "ObjFire.h"			//炎
#include "ObjTorch.h"			//聖火
#include "ObjPuddle.h"			//水たまり
#include "ObjRain.h"			//雨
#include "ObjOkama.h"			//オカマ
#include "ObjHole.h"			//穴
#include "ObjCheckPoint.h"		//チェックポイント

#include "ObjTitle.h"			//タイトル
#include "ObjGameOver.h"		//ゲームオーバー
#include "ObjRanking.h"			//ランキング
#include "ObjMenu.h"			//メニュー
#include "ObjGameClear.h"		//クリア
//補助系
#include "Correction.h"			//補正
//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
#include "SceneMain.h"			//シーンタイトル
#include "SceneTitle.h"			//シーンメイン
#include "SceneGameOver.h"		//シーンゲームオーバー
#include "SceneMenu.h"			//シーンメニュー
#include "SceneRanking.h"		//シーンランキング
#include "SceneGameClear.h"		//シーンクリア

//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
#define SET_GAME_START CSceneMain
//-----------------------------------------------