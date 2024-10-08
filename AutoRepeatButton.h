#pragma once
#include "ButtonEx.h"

// CAutoRepeatButton

class CAutoRepeatButton : public CButtonEx
{
    DECLARE_DYNAMIC(CAutoRepeatButton)

private:
    bool TimerActive;
    bool MessageSent;
    bool KeyPress;
    bool MousePress;
    CWnd *Parent;
    UINT InitialTime;
    UINT RepeatTime;

public:
    CAutoRepeatButton();
    virtual ~CAutoRepeatButton();
    void SetTimes(UINT Initial, UINT Repeat);

protected:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
    virtual void PreSubclassWindow();
};


