#pragma once
#include "DxLib.h"



// �L�[�{�[�h�̓��͏��
class KeyData
{
private:
	static int m_key[256];		// �L�[�̓��͏�Ԋi�[�p�ϐ�
	static char m_tmpKey[256];	// ���݂̃L�[�̓��͏�Ԃ��i�[����

public:
	static void UpDate();			// �L�[���͂̏�ԍX�V


	// �L�[���͏�Ԏ擾
	static int Get(const int& t_keyCode)
	{
		return m_key[t_keyCode];
	}


	// �����I��
	static const bool IsCheckEnd()
	{
		return m_key[KEY_INPUT_ESCAPE] > 0;
	}
};