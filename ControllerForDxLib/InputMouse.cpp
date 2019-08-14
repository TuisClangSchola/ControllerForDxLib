#include "InputMouse.hpp"
#include "DxLib.h"



/// ------------------------------------------------------------------------------------------------------------

int MouseData::m_mouse[3];
int MouseData::m_mouseInput;



/// ------------------------------------------------------------------------------------------------------------
void MouseData::MouseUpDate()
{
	// PC�Q�[�ł���ȏ�A�}�E�X�̂Ȃ���Ԃ��z��ł��Ȃ��̂ŃG���[�����͏Ȃ�
	m_mouseInput = GetMouseInput();


	for (int i = 0; i != 3; ++i)
	{
		// ������Ă��Ȃ�������
		if ((m_mouseInput & 1 << i)/* ����1 / �E��2 / �^�񒆂�4 */ == 0)
		{
			if (m_mouse[i] < 0)
			{
				m_mouse[i] = 0;
			}
			else if (m_mouse[i] > 0)
			{
				m_mouse[i] = -1;
			}
		}
		// ������Ă�����
		else
		{
			m_mouse[i]++;
		}
	}
}



/// ------------------------------------------------------------------------------------------------------------
const int& MouseData::GetClick(const ECLICK& t_mouseCode)
{
	return m_mouse[static_cast<int>(t_mouseCode)];
}



/// ------------------------------------------------------------------------------------------------------------

int MouseWheelData::m_mouseWheel;
int MouseWheelData::m_oldMouseWheel;



/// ------------------------------------------------------------------------------------------------------------
void MouseWheelData::MouseWheelUpDate()
{
	m_oldMouseWheel = m_mouseWheel;


	if (m_oldMouseWheel - m_mouseWheel > 0)
	{
		m_mouseWheel++;
	}
	else if (m_oldMouseWheel - m_mouseWheel < 0)
	{
		m_mouseWheel--;
	}
	else
	{
		m_mouseWheel = 0;
	}
}



/// ------------------------------------------------------------------------------------------------------------
int MouseWheelData::GetMouseWheel(int MouseWheelCode)
{
	return m_mouseWheel += MouseWheelCode;
}