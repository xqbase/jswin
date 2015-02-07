package com.googlecode.jswin;

import java.io.File;
import java.net.URLDecoder;

class ClassPath {
	static String append(String path) {
		try {
			String absolute = URLDecoder.decode(ClassPath.class.getProtectionDomain().
					getCodeSource().getLocation().getPath(), "UTF-8");
			if (absolute.endsWith(".jar")) {
				absolute += File.separator + "..";
			} else if (absolute.endsWith(".class")) {
				int nParent = ClassPath.class.getPackage().getName().split("\\.").length + 1;
				for (int i = 0; i < nParent; i ++) {
					absolute += File.separator + "..";
				}
			}
			return new File(absolute + File.separator + path).getCanonicalPath();
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}
}