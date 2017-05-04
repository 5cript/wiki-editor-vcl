JEDI Dependency:
	(Install)
	jcl : http://jcl.sourceforge.net/daily/
	jvcl: http://jvcl.sourceforge.net/daily/
	
	Fixups:
		- Components -> install packages -> add bpl's from Documents/Studio/18.0/Bpl
		- New Environment Variables:
			- JVCL_INCLUDEPATH: D:\JEDI\jvcl\common;D:\JEDI\jvcl\run;D:\JEDI\jcl\source\common;D:\JEDI\jcl\source\vcl;D:\JEDI\jcl\source\visclx;D:\JEDI\jcl\source\windows
			- JVCL_RESPATH: D:\JEDI\jvcl\run;D:\JEDI\jvcl\resources;D:\JEDI\jvcl\lib\d24\win32;D:\JEDI\jcl\lib\d24\win32
			- Add include and link paths as $(JVCL_INCLUDEPATH) and $(JVCL_RESPATH)
	