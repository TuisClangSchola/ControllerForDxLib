#pragma once
#include "DxLib.h"



#ifndef _INPUTCONTROLLER_H
#define _INPUTCONTROLLER_H
namespace PadStick
{
	const int XINPUT_LEFT_TRIGGER = 0;
	const int XINPUT_RIGHT_TRIGGER = 1;
	const int  XINPUT_LEFT_THUMB_X = 2;
	const int  XINPUT_LEFT_THUMB_Y = 3;
	const int  XINPUT_RIGHT_THUMB_X = 4;
	const int  XINPUT_RIGHT_THUMB_Y = 5;

	const int  XINPUT_THUMB_MAX = 32767;
	const int  XINPUT_THUMB_MIN = -32768;

	const int XINPUT_THUMB_PLUS = 0;
	const int XINPUT_THUMB_MINUS = 4;
}
#endif // !_INPUTCONTROLLER_H



// �Q�[���p�b�h�̓��͏��
class PadData 
{
private:
	static int button[4][16];		// �Q�[���p�b�h�̓��͏�Ԋi�[�p�ϐ�
	static int stick[4][6];			// �Q�[���p�b�h�̃X�e�B�b�N�֘A�̓��͏�Ԏ��[�p�ϐ�
	static int stickCheck[4][8];	// �Q�[���p�b�h�̃X�e�B�b�N�̓��͏�Ԏ��[�p�ϐ��̍ő�܂ł̓|���`�F�b�N


	// �Q�[���p�b�h�̃X�e�B�b�N�̃f�b�h�]�[�����l��ۑ�
	static short thumbLX_DeadMAX;
	static short thumbLX_DeadMIN;
	static short thumbLY_DeadMAX;
	static short thumbLY_DeadMIN;
	static short thumbRX_DeadMAX;
	static short thumbRX_DeadMIN;
	static short thumbRY_DeadMAX;
	static short thumbRY_DeadMIN;


	static XINPUT_STATE m_input[4];	// �Q�[���p�b�h�̃i���o�[
	static char m_padNum;			// �q�����Ă�Q�[���p�b�h�̐�



public:
	static void SetDedZone(short thumbLX_MAX, short thumbLX_MIN, short thumbLY_MAX, short thumbLY_MIN
		, short thumbRX_MAX, short thumbRX_MIN, short thumbRY_MAX, short thumbRY_MIN);					// �f�b�h�]�[���̐ݒ�
	static void UpDate();																				// �Q�[���p�b�h�̓��͂̏�ԍX�V
	static int GetStickCheck(int code, int padNum, bool plus);											// �Q�[���p�b�h�̃X�e�B�b�N�̉����|�����͏�Ԏ擾

	static const int Get(const int& t_code, const int& t_padNum);																// �Q�[���p�b�h�̓��͏�Ԏ擾
	static const bool IsCheckEnd();																		// �����I��
	static const int GetStick(const int& t_code, const int& t_padNum);										// �Q�[���p�b�h�̃X�e�B�b�N�̓��͏�Ԏ擾
	static const char GetPadNum();																		// �ڑ�����Ă�Q�[���p�b�h�̐�

	static inline void SetPadNum();																		// �ڑ�����Ă�Q�[���p�b�h���擾����
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