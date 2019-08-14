#include "InputKey.hpp"
#include "InputPad.hpp"
#include "InputMouse.hpp"
#include "DxLib.h"



/// --------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウサイズを決める
	int winWidth = 640;
	int winHeight = 480;
	int bitColor = 32;


#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ログテキスト出力する
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ログテキスト出力しない
#endif


	SetWindowText("ControllerForDxLib");					// メインウインドウのウインドウタイトルを変更する
	SetBackgroundColor(0, 0, 0);			// 背景色を白に変更
	ChangeWindowMode(TRUE);						// ウィンドウズモードにさせる


	SetGraphMode(winWidth, winHeight, bitColor);			// 画面サイズ設定
	GetDefaultState(&winWidth, &winHeight, &bitColor);		// デフォルトウィンドウ値を得る
	SetWindowSize(winWidth / 2, winHeight / 2);						// デフォルトウィンドウサイズに合わせてゲームサイズを変更


	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;			// エラーが起きたら直ちに終了
	}


	SetDrawScreen(DX_SCREEN_BACK);	// 背景描画

	// キーボードの初期化
	KeyData::UpDate();


	// ゲームパッドの初期化
	PadData::SetPadNum();
	PadData::SetDedZone(20000, -20000, 20000, -20000, 20000, -20000, 20000, -20000);
	PadData::UpDate();


	// マウスの初期化
	MouseData::MouseUpDate();
	// マウスホイールの初期化
	MouseWheelData::MouseWheelUpDate();


	// demo
	int x = 100;
	int y = 100;
	int red = 255;
	int green = 0;
	int blue = 0;
	

	// メインループ
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !KeyData::IsCheckEnd() && !PadData::IsCheckEnd())
	{
		KeyData::UpDate();						// キーボードのループ処理
		PadData::UpDate();						// ゲームパッドのループ処理
		MouseData::MouseUpDate();				// マウスのループ処理
		MouseWheelData::MouseWheelUpDate();		// マウスホイールのループ処理

		printfDx("%d\n", MouseData::GetClick(MouseData::ECLICK::CENTER));


		/// demo---------------------------------------------------------------------------------
		if (KeyData::Get(KEY_INPUT_W) > 0 || PadData::GetStickCheck(PadStick::LEFT_STICK_Y, 0, false) > 0)
		{
			y--;
		}
		if (KeyData::Get(KEY_INPUT_S) > 0 || PadData::GetStickCheck(PadStick::LEFT_STICK_Y, 0, true) > 0)
		{
			y++;
		}
		if (KeyData::Get(KEY_INPUT_A) > 0 || PadData::GetStickCheck(PadStick::LEFT_STICK_X, 0, true) > 0)
		{
			x--;
		}
		if (KeyData::Get(KEY_INPUT_D) > 0 || PadData::GetStickCheck(PadStick::LEFT_STICK_X, 0, false) > 0)
		{
			x++;
		}
		if (PadData::GetTrigger(PadStick::LEFT_TRIGGER, 0) == 255)
		{
			if (green < 255) green++;
		}
		if (PadData::GetTrigger(PadStick::RIGHT_TRIGGER, 0) == 255)
		{
			if (green > 0) green--;
		}
		if (PadData::GetStick(PadStick::RIGHT_STICK_X, 0) > 0)
		{
			if (blue < 255) blue++;
		}
		if (PadData::GetStick(PadStick::RIGHT_STICK_X, 0) < 0)
		{
			if (blue > 0) blue--;
		}
		DrawBox(x - 20, y - 20, x + 20, y + 20, GetColor(red, green, blue), true);
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%dx%d, GetColor(255, %d, %d)", x, y, green, blue);
		/// -------------------------------------------------------------------------------------
	}

	// 削除
	DxLib_End();		// DXライブラリの後始末


	return 0;
}