#include "InputPad.hpp"
namespace ps = PadStick;



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------

int PadData::m_button[4][16];

int PadData::m_stick[4][6];
int PadData::m_stickCheck[4][8];
int PadData::m_trigger[4][2];

short PadData::stickLX_DeadZoneMAX = 1000;
short PadData::stickLX_DeadZoneMIN = -1000;
short PadData::stickLY_DeadZoneMAX = 1000;
short PadData::stickLY_DeadZoneMIN = -1000;
short PadData::stickRX_DeadZoneMAX = 1000;
short PadData::stickRX_DeadZoneMIN = -1000;
short PadData::stickRY_DeadZoneMAX = 1000;
short PadData::stickRY_DeadZoneMIN = -1000;

XINPUT_STATE PadData::m_input[4];

char PadData::m_padNum = -1;



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void PadData::UpDate()
{
	// ゲームパッドの取得出来ているか
	if (m_padNum == -1) return;


	// ゲームパッドの個数だけ処理
	for (int padNumber = 0; padNumber < static_cast<int>(m_padNum); ++padNumber)
	{
		// 入力状態を取得
		GetJoypadXInputState(padNumber + 1, &m_input[padNumber]);
	


		/// ボタン関係-----------------------------------------------------------
		{
			// 全ボタン入力処理
			for (int j = 0; j < 16; ++j)
			{
				// 押されていなかったら
				if (m_input[padNumber].Buttons[j] == 0)
				{
					if (m_button[padNumber][j] < 0)
					{
						m_button[padNumber][j] = 0;
					}
					else if (m_button[padNumber][j] > 0)
					{
						m_button[padNumber][j] = -1;
					}
				}
				// i番のキーコードに対応するボタンが押されていたら
				else if (m_input[padNumber].Buttons[j] == 1)
				{
					m_button[padNumber][j]++;
				}
			}
		}
		/// ---------------------------------------------------------------------



		/// トリガー関係---------------------------------------------------------
		{
			// トリガーの入力数値を渡す
			m_trigger[padNumber][ps::LEFT_TRIGGER] = m_input[padNumber].LeftTrigger;
			m_trigger[padNumber][ps::RIGHT_TRIGGER] = m_input[padNumber].RightTrigger;
		}
		/// ---------------------------------------------------------------------



		/// スティック入力関係---------------------------------------------------
		{
			/// スティックのデッドゾーンを考慮した入力数値を取得（デッドゾーンは受け付けない値

			// 左スティック左右
			if (m_input[padNumber].ThumbLX > stickLX_DeadZoneMAX || m_input[padNumber].ThumbLX < stickLX_DeadZoneMIN)
			{
				m_stick[padNumber][ps::LEFT_STICK_X] = m_input[padNumber].ThumbLX;
			}
			else
			{
				if (m_stick[padNumber][ps::LEFT_STICK_X] != 0) m_stick[padNumber][ps::LEFT_STICK_X] = 0;
			}

			// 左スティック上下
			if (m_input[padNumber].ThumbLY > stickLY_DeadZoneMAX || m_input[padNumber].ThumbLY < stickLY_DeadZoneMIN)
			{
				m_stick[padNumber][ps::LEFT_STICK_Y] = m_input[padNumber].ThumbLY;
			}
			else
			{
				if (m_stick[padNumber][ps::LEFT_STICK_Y] != 0) m_stick[padNumber][ps::LEFT_STICK_Y] = 0;
			}

			// 右スティック左右
			if (m_input[padNumber].ThumbRX > stickRX_DeadZoneMAX || m_input[padNumber].ThumbRX < stickRX_DeadZoneMIN)
			{
				m_stick[padNumber][ps::RIGHT_STICK_X] = m_input[padNumber].ThumbRX;
			}
			else
			{
				if (m_stick[padNumber][ps::RIGHT_STICK_X] != 0) m_stick[padNumber][ps::RIGHT_STICK_X] = 0;
			}

			// 右スティック上下
			if (m_input[padNumber].ThumbRY > stickRY_DeadZoneMAX || m_input[padNumber].ThumbRY < stickRY_DeadZoneMIN)
			{
				m_stick[padNumber][ps::RIGHT_STICK_Y] = m_input[padNumber].ThumbRY;
			}
			else
			{
				if (m_stick[padNumber][ps::RIGHT_STICK_Y] != 0) m_stick[padNumber][ps::RIGHT_STICK_Y] = 0;
			}
		}
		/// ---------------------------------------------------------------------



		/// スティック押し倒し関係-----------------------------------------------
		{
			// 左スティックを右に押し倒していたら
			if (m_input[padNumber].ThumbLX == ps::STICK_MAX_VALUE)
			{
				m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_RIGHT)]++;
			}
			// 左スティックを左に押し倒していたら
			else if (m_input[padNumber].ThumbLX == ps::STICK_MIN_VALUE)
			{
				m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_LEFT)]++;
			}
			// 左スティックが押し倒されていなかったら
			else
			{
				if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_RIGHT)] < 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_RIGHT)] = 0;
				}
				else if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_RIGHT)] > 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_RIGHT)] = -1;
				}


				if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_LEFT)] < 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_LEFT)] = 0;
				}
				else if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_LEFT)] > 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_LEFT)] = -1;
				}
			}


			// 左スティックを上に押し倒していたら
			if (m_input[padNumber].ThumbLY == ps::STICK_MAX_VALUE)
			{
				m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_UP)]++;
			}
			// 左スティックを下に押し倒していたら
			else if (m_input[padNumber].ThumbLY == ps::STICK_MIN_VALUE)
			{
				m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_DOWN)]++;
			}
			// 左スティックが押し倒されていなかったら
			else
			{
				if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_UP)] < 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_UP)] = 0;
				}
				else if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_UP)] > 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_UP)] = -1;
				}


				if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_DOWN)] < 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_DOWN)] = 0;
				}
				else if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_DOWN)] > 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::LEFT_STICK_DOWN)] = -1;
				}
			}


			// 右スティックを右に押し倒していたら
			if (m_input[padNumber].ThumbRX == ps::STICK_MAX_VALUE)
			{
				m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_RIGHT)]++;
			}
			// 右スティックを左に押し倒していたら
			else if (m_input[padNumber].ThumbRX == ps::STICK_MIN_VALUE)
			{
				m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_LEFT)]++;
			}
			// 右スティックが押し倒されていなかったら
			else
			{
				if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_RIGHT)] < 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_RIGHT)] = 0;
				}
				else if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_RIGHT)] > 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_RIGHT)] = -1;
				}


				if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_LEFT)] < 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_LEFT)] = 0;
				}
				else if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_LEFT)] > 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_LEFT)] = -1;
				}
			}


			// 右スティックを上に押し倒していたら
			if (m_input[padNumber].ThumbRY == ps::STICK_MAX_VALUE)
			{
				m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_UP)]++;
			}
			// 右スティックを下に押し倒していたら
			else if (m_input[padNumber].ThumbRY == ps::STICK_MIN_VALUE)
			{
				m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_DOWN)]++;
			}
			// 右スティックが押し倒されていなかったら
			else
			{
				if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_UP)] < 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_UP)] = 0;
				}
				else if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_UP)] > 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_UP)] = -1;
				}


				if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_DOWN)] < 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_DOWN)] = 0;
				}
				else if (m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_DOWN)] > 0)
				{
					m_stickCheck[padNumber][static_cast<int>(EStickCheck::RIGHT_STICK_DOWN)] = -1;
				}
			}
		}
		/// ---------------------------------------------------------------------
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int& PadData::GetButton(const int& t_code, const int& t_padNum)
{
	return m_button[t_padNum][t_code];
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int& PadData::GetTrigger(const int& t_code, const int& t_padNum)
{
	return m_trigger[t_padNum][t_code];
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int& PadData::GetStick(const int& t_code, const int& t_padNum)
{
	return m_stick[t_padNum][t_code];
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int& PadData::GetStickCheck(const int& t_code, const int& t_padNum, const bool& t_leftAndDownIsTrue)
{
	if (t_leftAndDownIsTrue)
	{
		return m_stickCheck[t_padNum][t_code - 2];
	}
	else
	{
		return m_stickCheck[t_padNum][t_code - 2 + 4];
	}
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
const char& PadData::GetPadNum()
{
	return m_padNum;
}