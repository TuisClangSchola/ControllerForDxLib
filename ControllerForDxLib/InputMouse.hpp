#pragma once
#ifndef _INPUTMOUSE_HPP
#define _INPUTMOUSE_HPP



// マウス
class MouseData
{
private:
	static int m_mouse[3];
	static int m_mouseInput;

public:
	//左クリックか右クリックか
	enum class ECLICK { LEFT, RIGHT, CENTER };


	//マウスのクリックの状態を更新する
	static void MouseUpDate();

	//マウスのクリックの状態を返す
	static int GetClick(int MouseCode);
};



// マウスホイール
class MouseWheelData
{
private:
	static int m_mouseWheel;
	static int m_oldMouseWheel;

public:
	//マウスのホイールの状態を更新
	static void MouseWheelUpdate();

	//マウスホイールの状態を返す
	static int GetMouseWheel(int MouseWheelCode);
};


#endif // !_INPUTMOUSE_HPP