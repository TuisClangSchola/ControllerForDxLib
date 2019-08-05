#pragma once
#include "DxLib.h"



#ifndef _INPUTCONTROLLER_H
#define _INPUTCONTROLLER_H
namespace PadStick
{
	const int LEFT_TRIGGER = 0;
	const int RIGHT_TRIGGER = 1;
	const int  LEFT_STICK_X = 2;
	const int  LEFT_STICK_Y = 3;
	const int  RIGHT_STICK_X = 4;
	const int  RIGHT_STICK_Y = 5;

	const int  THUMB_MAX_VALUE = 32767;
	const int  THUMB_MIN_VALUE = -32768;

	const int THUMB_PLUS = 0;
	const int THUMB_MINUS = 4;
}
#endif // !_INPUTCONTROLLER_H



// ゲームパッドの入力状態
class PadData 
{
private:
	static int m_button[4][16];		// ゲームパッドの入力状態格納用変数
	static int m_stick[4][6];		// ゲームパッドのスティック関連の入力状態収納用変数
	static int m_stickCheck[4][8];	// ゲームパッドのスティックの入力状態収納用変数の最大までの倒しチェック
	static int m_trigger[4][2];		// ゲームパッドのトリガーの入力状態収納用変数


	// ゲームパッドのスティックのデッドゾーン数値を保存
	static short stickLX_DeadMAX;
	static short stickLX_DeadMIN;
	static short stickLY_DeadMAX;
	static short stickLY_DeadMIN;
	static short stickRX_DeadMAX;
	static short stickRX_DeadMIN;
	static short stickRY_DeadMAX;
	static short stickRY_DeadMIN;


	static XINPUT_STATE m_input[4];	// ゲームパッドのナンバー
	static char m_padNum;			// 繋がってるゲームパッドの数


	enum class EStickCheck 
	{
		LEFT_STICK_LEFT, LEFT_STICK_DOWN, RIGHT_STICK_LEFT, RIGHT_STICK_DOWN
		, LEFT_STICK_RIGHT, LEFT_STICK_UP, RIGHT_STICK_RIGHT, RIGHT_STICK_UP
	};



public:
	static void SetDedZone(short thumbLX_MAX, short thumbLX_MIN, short thumbLY_MAX, short thumbLY_MIN
		, short thumbRX_MAX, short thumbRX_MIN, short thumbRY_MAX, short thumbRY_MIN);					// デッドゾーンの設定
	static void UpDate();																				// ゲームパッドの入力の状態更新

	static const int GetStickCheck(const int& t_code, const int& t_padNum, const bool& t_leftOrDown);											// ゲームパッドのスティックの押し倒し入力状態取得

	static const int GetTrigger(const int& t_code, const int& t_padNum);

	static const int Get(const int& t_code, const int& t_padNum);																// ゲームパッドの入力状態取得
	static const bool IsCheckEnd();																		// 強制終了
	static const int GetStick(const int& t_code, const int& t_padNum);										// ゲームパッドのスティックの入力状態取得
	static const char GetPadNum();																		// 接続されてるゲームパッドの数

	static inline void SetPadNum();																		// 接続されてるゲームパッドを取得する
};



/// ------------------------------------------------------------------------------------------------------------
inline void PadData::SetPadNum()
{
	if (GetJoypadNum() > 0)
	{
		m_padNum = static_cast<char>(GetJoypadNum());
	}
	else
	{
		m_padNum = -1;
	}
}