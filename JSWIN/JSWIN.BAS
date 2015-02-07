Attribute VB_Name = "mdlJsWin"
Option Explicit
' JSWIN.BAS - Visual Basic Part for JsWin
'
' JsWin - a JavaScript Framework for Win32 DLL Access
' Designed by Morning Yellow, Version: 1.0, Last Modified: May. 2009
' Copyright (C) 2004-2009 www.elephantbase.net
'
' This library is free software; you can redistribute it and/or
' modify it under the terms of the GNU Lesser General Public
' License as published by the Free Software Foundation; either
' version 2.1 of the License, or (at your option) any later version.
'
' This library is distributed in the hope that it will be useful,
' but WITHOUT ANY WARRANTY; without even the implied warranty of
' MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
' Lesser General Public License for more details.
'
' You should have received a copy of the GNU Lesser General Public
' License along with this library; if not, write to the Free Software
' Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

Private Declare Sub Sleep Lib "KERNEL32.DLL" (ByVal dwMilliseconds As Long)
Private Declare Function GetProcessHeap Lib "KERNEL32.DLL" () As Long

Private Declare Function SetWindowsHookExA Lib "USER32.DLL" (ByVal idHook As Long, ByVal lpfn As Long, ByVal hMod As Long, ByVal dwThreadId As Long) As Long
Private Declare Function CallNextHookEx Lib "USER32.DLL" (ByVal hhk As Long, ByVal iCode As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Private Declare Sub UnhookWindowsHookEx Lib "USER32.DLL" (ByVal hhk As Long)
Private Declare Function GetKeyState Lib "USER32.DLL" (ByVal nVirtKey As Long) As Integer

Private Const WH_KEYBOARD As Long = 2
Private Const VK_CONTROL As Long = &H11

Public App_hProcessHeap As Long

Private App_hhkPrev As Long

Public Function NewKeyboardProc(ByVal iCode As Long, ByVal wParam As Long, ByVal lParam As Long) As Long

If iCode < 0 Then
    NewKeyboardProc = CallNextHookEx(App_hhkPrev, iCode, wParam, lParam)
    Exit Function
End If
If (lParam And &H80000000) = 0 Then
    If wParam = vbKeyF5 Then
        NewKeyboardProc = 1
        Exit Function
    End If
    If GetKeyState(VK_CONTROL) < 0 Then
        If wParam = vbKeyN Or wParam = vbKeyP Or wParam = vbKeyR Then
            NewKeyboardProc = 1
            Exit Function
        End If
    End If
End If
NewKeyboardProc = CallNextHookEx(App_hhkPrev, iCode, wParam, lParam)

End Function

Public Function GenericCallback(ByVal fnCallback As Object, ByVal lpParam As Long) As Long

On Error Resume Next
GenericCallback = fnCallback(lpParam)
On Error GoTo 0

End Function

Public Sub Main()

App_hProcessHeap = GetProcessHeap

Dim szPath As String
szPath = App.Path
szPath = szPath + IIf(Right(szPath, 1) = "\", "", "\")

Dim newWindow As New frmJsWin
Set newWindow.Param = Nothing
newWindow.WebBrowser.Navigate2 szPath + "DEFAULT.HTM"

App_hhkPrev = SetWindowsHookExA(WH_KEYBOARD, AddressOf NewKeyboardProc, App.hInstance, 0)
Do While Forms.Count > 0
    Sleep 1
    DoEvents
Loop
UnhookWindowsHookEx App_hhkPrev

End Sub
