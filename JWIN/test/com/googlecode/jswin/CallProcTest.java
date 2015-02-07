package com.googlecode.jswin;

import java.io.File;

public class CallProcTest {
	public static void main(String[] args) {
		try (CallbackHelper callback = new CallbackHelper(4) {
			@Override
			public int callback(int[] params) {
				int result = 0;
				for (int i = 0; i < params.length; i ++) {
					result += CallProcHelper.getStr(params[i]).length();
				}
				return result;
			}
		}) {
			if (File.separatorChar == '\\') {
				System.out.println(new CallProcHelper("USER32.DLL",
						"CallWindowProcA").callProcEx(callback, "1", "12", "1234", "12345678"));
			} else {
				String soFile = ClassPath.append("../lib/libcallwindowproc.so").toString();
				System.out.println(new CallProcHelper(soFile,
						"CallWindowProc").callProcEx(callback, "1", "12", "1234", "12345678"));
			}
		}
	}
}