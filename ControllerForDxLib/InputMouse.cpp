#include "InputMouse.hpp"
#include "DxLib.h"



/// ------------------------------------------------------------------------------------------------------------

int MouseData::m_mouse[3];
int MouseData::m_mouseInput;



/// ------------------------------------------------------------------------------------------------------------
void MouseData::MouseUpDate()
{
	m_mouseInput = GetMouseInput();    //�}�E�X�̉�������Ԏ擾


	for (int i = 0; i != 3; ++i)
	{
		if ((m_mouseInput & 1 << i) != 0)
		{
			m_mouse[i]++;   //������Ă�����J�E���g�A�b�v
		}
		else
		{
			m_mouse[i] = 0; //������ĂȂ�������0
		}
	}
}



/// ------------------------------------------------------------------------------------------------------------
int MouseData::GetClick(int MouseCode)
{
	return m_mouse[MouseCode];
}



/// ------------------------------------------------------------------------------------------------------------

int MouseWheelData::m_mouseWheel;
int MouseWheelData::m_oldMouseWheel;



/// ------------------------------------------------------------------------------------------------------------
void MouseWheelData::MouseWheelUpdate()
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