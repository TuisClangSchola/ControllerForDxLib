#include "InputPad.hpp"
namespace ps = PadStick;



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------

int PadData::m_button[4][16];

int PadData::m_stick[4][6];
int PadData::m_stickCheck[4][8];
int PadData::m_trigger[4][2];

short PadData::stickLX_DeadMAX = 1000;
short PadData::stickLX_DeadMIN = -1000;
short PadData::stickLY_DeadMAX = 1000;
short PadData::stickLY_DeadMIN = -1000;
short PadData::stickRX_DeadMAX = 1000;
short PadData::stickRX_DeadMIN = -1000;
short PadData::stickRY_DeadMAX = 1000;
short PadData::stickRY_DeadMIN = -1000;

XINPUT_STATE PadData::m_input[4];

char PadData::m_padNum = -1;



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void PadData::SetDedZone(short thumbLX_MAX, short thumbLX_MIN, short thumbLY_MAX, short thumbLY_MIN
	, short thumbRX_MAX, short thumbRX_MIN, short thumbRY_MAX, short thumbRY_MIN)
{
	stickLX_DeadMAX = thumbLX_MAX;
	stickLX_DeadMIN = thumbLX_MIN;
	stickLY_DeadMAX = thumbLY_MAX;
	stickLY_DeadMIN = thumbLY_MIN;
	stickRX_DeadMAX = thumbRX_MAX;
	stickRX_DeadMIN = thumbRX_MIN;
	stickRY_DeadMAX = thumbRY_MAX;
	stickRY_DeadMIN = thumbRY_MIN;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void PadData::UpDate()
{
	// ゲームパッドの取得出来ているか
	if (m_padNum == -1) return;


	// ゲームパッドの個数だけ処理
	for (int i = 0; i < static_cast<int>(m_padNum); ++i)
	{
		// 入力状態を取得
		GetJoypadXInputState(i + 1, &m_input[i]);
	


		/// ボタン関係-----------------------------------------------------------
		{
			// 全ボタン入力処理
			for (int j = 0; j < 16; ++j)
			{
				// 押されていなかったら
				if (m_input[i].Buttons[j] == 0)
				{
					if (m_button[i][j] < 0)
					{
						m_button[i][j] = 0;
					}
					else if (m_button[i][j] > 0)
					{
						m_button[i][j] = -1;
					}
				}
				// i番のキーコードに対応するボタンが押されていたら
				else if (m_input[i].Buttons[j] == 1)
				{
					m_button[i][j]++;
				}
			}
		}
		/// ---------------------------------------------------------------------



		/// トリガー関係---------------------------------------------------------
		{
			// トリガーの入力数値を渡す
			m_trigger[i][ps::LEFT_TRIGGER] = m_input[i].LeftTrigger;
			m_trigger[i][ps::RIGHT_TRIGGER] = m_input[i].RightTrigger;
		}
		/// ---------------------------------------------------------------------



		/// スティック入力関係---------------------------------------------------
		{
			// スティックのデッドゾーンを考慮した入力数値を取得（デッドゾーンは受け付けない値
			if (m_input[i].ThumbLX > stickLX_DeadMAX || m_input[i].ThumbLX < stickLX_DeadMIN)
			{
				m_stick[i][ps::LEFT_STICK_X] = m_input[i].ThumbLX;
			}
			if (m_input[i].ThumbLY > stickLY_DeadMAX || m_input[i].ThumbLY < stickLY_DeadMIN)
			{
				m_stick[i][ps::LEFT_STICK_Y] = m_input[i].ThumbLY;
			}
			if (m_input[i].ThumbRX > stickRX_DeadMAX || m_input[i].ThumbRX < stickRX_DeadMIN)
			{
				m_stick[i][ps::RIGHT_STICK_X] = m_input[i].ThumbRX;
			}
			if (m_input[i].ThumbRY > stickRY_DeadMAX || m_input[i].ThumbRY < stickRY_DeadMIN)
			{
				m_stick[i][ps::RIGHT_STICK_Y] = m_input[i].ThumbRY;
			}
		}
		/// ---------------------------------------------------------------------



		/// スティック押し倒し関係-----------------------------------------------
		{
			// 左スティックを左右に押し倒しているかを調べる
			if (m_input[i].ThumbLX == ps::THUMB_MAX_VALUE)
			{
				m_stickCheck[i][static_cast<int>(EStickCheck::LEFT_STICK_RIGHT)]++;
			}
			else if (m_input[i].ThumbLX == ps::THUMB_MIN_VALUE)
			{
				m_stickCheck[i][static_cast<int>(EStickCheck::LEFT_STICK_LEFT)]++;
			}
			else
			{
				m_stickCheck[i][static_cast<int>(EStickCheck::LEFT_STICK_RIGHT)] = 0;
				m_stickCheck[i][static_cast<int>(EStickCheck::LEFT_STICK_LEFT)] = 0;
			}


			// 左スティックを上下に押し倒しているかを調べる
			if (m_input[i].ThumbLY == ps::THUMB_MAX_VALUE)
			{
				m_stickCheck[i][static_cast<int>(EStickCheck::LEFT_STICK_UP)]++;
			}
			else if (m_input[i].ThumbLY == ps::THUMB_MIN_VALUE)
			{
				m_stickCheck[i][static_cast<int>(EStickCheck::LEFT_STICK_DOWN)]++;
			}
			else
			{
				m_stickCheck[i][static_cast<int>(EStickCheck::LEFT_STICK_UP)] = 0;
				m_stickCheck[i][static_cast<int>(EStickCheck::LEFT_STICK_DOWN)] = 0;
			}


			// 右スティックを左右に押し倒しているかを調べる
			if (m_input[i].ThumbRX == ps::THUMB_MAX_VALUE)
			{
				m_stickCheck[i][static_cast<int>(EStickCheck::RIGHT_STICK_RIGHT)]++;
			}
			else if (m_input[i].ThumbRX == ps::THUMB_MIN_VALUE)
			{
				m_stickCheck[i][static_cast<int>(EStickCheck::RIGHT_STICK_LEFT)]++;
			}
			else
			{
				m_stickCheck[i][static_cast<int>(EStickCheck::RIGHT_STICK_RIGHT)] = 0;
				m_stickCheck[i][static_cast<int>(EStickCheck::RIGHT_STICK_LEFT)] = 0;
			}


			// 右スティックを上下に押し倒しているかを調べる
			if (m_input[i].ThumbRY == ps::THUMB_MAX_VALUE)
			{
				m_stickCheck[i][static_cast<int>(EStickCheck::RIGHT_STICK_UP)]++;
			}
			else if (m_input[i].ThumbRY == ps::THUMB_MIN_VALUE)
			{
				m_stickCheck[i][static_cast<int>(EStickCheck::RIGHT_STICK_DOWN)]++;
			}
			else
			{
				m_stickCheck[i][static_cast<int>(EStickCheck::RIGHT_STICK_UP)] = 0;
				m_stickCheck[i][static_cast<int>(EStickCheck::RIGHT_STICK_DOWN)] = 0;
			}
		}
		/// ---------------------------------------------------------------------
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int PadData::Get(const int& t_code, const int& t_padNum)
{
	return m_button[t_padNum][t_code];
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int PadData::GetStickCheck(const int& t_code, const int& t_padNum, const bool& t_leftOrDown)
{
	if (t_leftOrDown)
	{
		return m_stickCheck[t_padNum][t_code - 2];
	}
	else
	{
		return m_stickCheck[t_padNum][t_code - 2 + 4];
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int PadData::GetTrigger(const int& t_code, const int& t_padNum)
{
	return m_trigger[t_padNum][t_code];
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const bool PadData::IsCheckEnd()
{
	return
	{
		(m_button[0][XINPUT_BUTTON_START] > 1 && m_button[0][XINPUT_BUTTON_BACK] > 1) ||
		(m_button[1][XINPUT_BUTTON_START] > 1 && m_button[1][XINPUT_BUTTON_BACK] > 1) ||
		(m_button[2][XINPUT_BUTTON_START] > 1 && m_button[2][XINPUT_BUTTON_BACK] > 1) ||
		(m_button[3][XINPUT_BUTTON_START] > 1 && m_button[3][XINPUT_BUTTON_BACK] > 1)
	};
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int PadData::GetStick(const int& t_code, const int& t_padNum)
{
	return m_stick[t_padNum][t_code];
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const char PadData::GetPadNum()
{
	return m_padNum;
}