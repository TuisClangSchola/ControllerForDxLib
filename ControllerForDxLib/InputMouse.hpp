#pragma once
#ifndef _INPUTMOUSE_HPP
#define _INPUTMOUSE_HPP



// �}�E�X
class MouseData
{
private:
	static int m_mouse[3];
	static int m_mouseInput;

public:
	//���N���b�N���E�N���b�N��
	enum class ECLICK { LEFT, RIGHT, CENTER };


	//�}�E�X�̃N���b�N�̏�Ԃ��X�V����
	static void MouseUpDate();

	//�}�E�X�̃N���b�N�̏�Ԃ�Ԃ�
	static int GetClick(int MouseCode);
};



// �}�E�X�z�C�[��
class MouseWheelData
{
private:
	static int m_mouseWheel;
	static int m_oldMouseWheel;

public:
	//�}�E�X�̃z�C�[���̏�Ԃ��X�V
	static void MouseWheelUpdate();

	//�}�E�X�z�C�[���̏�Ԃ�Ԃ�
	static int GetMouseWheel(int MouseWheelCode);
};


#endif // !_INPUTMOUSE_HPP