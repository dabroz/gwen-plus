call "%VS90COMNTOOLS%\vsvars32.bat"

svn update

devenv Gwen.sln /Build "Debug DLL|Win32" > BuildDebugDLL.txt
devenv Gwen.sln /Build "Debug Static|Win32" > BuildDebugStatic.txt
devenv Gwen.sln /Build "Release DLL|Win32" > BuildReleaseDLL.txt
devenv Gwen.sln /Build "Release Static|Win32" > BuildReleaseStatic.txt