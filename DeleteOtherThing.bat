@echo off
::********************** ע�� ************************
::�г���ǰĿ¼����Ŀ¼�а�����Debug�����ļ��У�Ȼ��ɾ����
::dir /s /b /a:d �����оٵ�ǰĿ¼����Ŀ¼����/s Ҳ�о���Ŀ¼��/b ���ر�����Ϣ��ժҪ��/a ֻ�г�ָ�����Ե��ļ���d��ʾ�ļ��С���
::findstr /i "\\Debug$" ���г���Ŀ¼���ҳ�ƥ�䡰\Debug�����ļ��У���/i �����ִ�Сд��
::for /f "usebackq tokens=1* delims=/" %%a in ...do remdir /s /q %%a ɾ�����ҵ����ļ��С�(/s ɾ����Ŀ¼,/q ����Ҫȷ�ϣ�
::******************************************************
::cd
for /f "usebackq tokens=1* delims=/" %%a in (`dir /s /b /a:d ^| findstr /i "\\Debug$"`) do rmdir /s /q "%%a"
for /f "usebackq tokens=1* delims=/" %%a in (`dir /s /b /a:a ^| findstr /i "\\*.vcproj.*.user$"`) do del /s /q "%%a"
for /f "usebackq tokens=1* delims=/" %%a in (`dir /s /b /a:a ^| findstr /i "\\*.aps$"`) do del /s /q "%%a"
for /f "usebackq tokens=1* delims=/" %%a in (`dir /s /b /a:a ^| findstr /i "\\*.suo$"`) do del /s /q "%%a"
for /f "usebackq tokens=1* delims=/" %%a in (`dir /s /b /a:a ^| findstr /i "\\*.ncb$"`) do del /s /q "%%a"
for /f "usebackq tokens=1* delims=/" %%a in (`dir /s /b /a:a ^| findstr /i "\\*.sln$"`) do del /s /q "%%a"