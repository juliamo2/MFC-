#ifndef __JZ_AUTOSETENV_H__
#define __JZ_AUTOSETENV_H__
#include <Windows.h>
#include <tchar.h>
#include <io.h>
// ����ַ������ȶ���
#ifndef MAX_PATH
#	define MAX_PATH		260
#endif // !MAX_PATH

// ����������ȱʡ��󳤶ȣ����ϵͳ�����������ȴ��ڸ�ֵʱ����ѡ���޸Ĵ�ֵ��
#ifndef JZENV_MAX_LENGTH
#	define JZENV_MAX_LENGTH	4096
#endif // !JZENV_MAX_LENGTH

//	�����·������׺������
#define JZ_DLL						_T("\\dll")
#define JZDLL_POSTFIX_DEBUG			_T("d.dll")
#define JZDLL_POSTFIX_RELEASE		_T(".dll")
#define JZDIR_SEPARATOR				_T('\\')
#define JZDIR_SEPARATOR_S			_T("\\")
#define JZENV_SEPARATOR				_T(';')
#define JZENV_SEPARATOR_S			_T(";")
#ifdef _DEBUG
#		ifdef _WIN64
#			define JZDLL_DIR		_T("\\x64\\Debug")
#		else
#			define JZDLL_DIR		_T("\\Win32\\Debug")
#		endif // _WIN64
#	else
#		ifdef _WIN64
#			define JZDLL_DIR		_T("\\x64\\Release")
#		else
#			define JZDLL_DIR		_T("\\Win32\\Release")
#		endif // _WIN64
#endif // _DEBUG


// ��ָ��Ŀ¼�µ�������Ŀ¼����Ϊ��������
inline void JZDLL_SetEnv(LPCTSTR szImportDLLDir)
{
	if (NULL == szImportDLLDir) // �������·��Ϊ��ʱ���Զ�Ѱ��Import_dllĿ¼��������������Ŀ¼����Ϊ��������
	{
		TCHAR s_top[MAX_PATH] = { 0 };
		s_top[0] = '\0';
		GetModuleFileName(NULL, s_top, MAX_PATH - 1);
		LPCTSTR p_separator = NULL;
		for (int i = 0; i < 4; i++)
		{
			p_separator = _tcsrchr(s_top, JZDIR_SEPARATOR);
			if (NULL == p_separator)
			{
				return ;
			}
			*(LPTSTR)p_separator = '\0';
		}
		_tcscat(s_top, JZDIR_SEPARATOR_S);
		_tcscat(s_top, _T("dll\\Import_dll\\"));
		szImportDLLDir = s_top;

		// ��ȡ��������
		TCHAR s_env[JZENV_MAX_LENGTH] = { 0 };
		s_env[0] = '\0';
		GetEnvironmentVariable(_T("Path"), s_env, JZENV_MAX_LENGTH - 1);
		_tcscat(s_env, JZENV_SEPARATOR_S);

		// ����ָ��Ŀ¼�µ�������Ŀ¼
		TCHAR s_path[MAX_PATH] = { 0 };
		s_path[0] = '\0';
		_tfinddata_t info_file;
		intptr_t h_file;
		TCHAR s_search[MAX_PATH] = { 0 };
		s_search[0] = '\0';
		_tcscpy(s_search, szImportDLLDir);
		_tcscat(s_search, _T("*"));
		h_file = _tfindfirst(s_search, &info_file);
		if (-1 == h_file) // ���û���������ļ������ļ���
		{
			return;
		}
		else
		{
			// ������ҵĵ�һʱ�ļ�����������ӵ���������
			if (0 != (info_file.attrib & _A_SUBDIR)
				&& _tcscmp(info_file.name, _T("."))
				&& _tcscmp(info_file.name, _T("..")))
			{
				_tcscat(s_path, szImportDLLDir);
				_tcscat(s_path, info_file.name);
				_tcscat(s_path, JZDLL_DIR);
				_tcscat(s_path, JZENV_SEPARATOR_S);
				if (NULL == _tcsstr(s_env, s_path))
				{
					_tcscat(s_env, s_path);
					SetEnvironmentVariable(_T("Path"), s_env);
				}
				s_path[0] = '\0';
			}
			else // ����ҵ��ĵ�һ���ļ�������Բ���
			{
			}

			// ����ʣ�µ��ļ��л��ļ�
			while (-1 != _tfindnext(h_file, &info_file))
			{
				if (0 != (info_file.attrib & _A_SUBDIR)
					&& _tcscmp(info_file.name, _T("."))
					&& _tcscmp(info_file.name, _T(".."))) // ����ҵ������ļ���������Ϊ��Ҫ��ӵ�����������Ŀ¼
				{
					_tcscat(s_path, szImportDLLDir);
					_tcscat(s_path, info_file.name);
					_tcscat(s_path, JZDLL_DIR);
					_tcscat(s_path, JZENV_SEPARATOR_S);
					if (NULL == _tcsstr(s_env, s_path))
					{
						_tcscat(s_env, s_path);
						SetEnvironmentVariable(_T("Path"), s_env);
					}
					s_path[0] = '\0';
				}
				else // ����ҵ��������ļ�������Բ��ܣ��������²���
				{
				}
			}
			_findclose(h_file);
		}
	}
	else // �������·��Ϊ��ʱ����Import_dllĿ¼�µĸ��ļ�������Ϊ�����������磺�������OpenCVʱ����...../dll/Import_dll/x64/Debug����Ϊ��������
	{
		TCHAR s_top[MAX_PATH] = { 0 };
		s_top[0] = '\0';
		GetModuleFileName(NULL, s_top, MAX_PATH - 1);
		LPCTSTR p_separator = NULL;
		for (int i = 0; i < 4; i++)
		{
			p_separator = _tcsrchr(s_top, JZDIR_SEPARATOR);
			if (NULL == p_separator)
			{
				return;
			}
			*(LPTSTR)p_separator = '\0';
		}
		_tcscat(s_top, JZDIR_SEPARATOR_S);
		_tcscat(s_top, _T("dll\\Import_dll\\"));
		_tcscat(s_top, szImportDLLDir);
		_tcscat(s_top, JZDLL_DIR);

		// ��ȡ��������
		TCHAR s_env[JZENV_MAX_LENGTH] = { 0 };
		s_env[0] = '\0';
		GetEnvironmentVariable(_T("Path"), s_env, JZENV_MAX_LENGTH - 1);
		_tcscat(s_env, JZENV_SEPARATOR_S);
		if (NULL == _tcsstr(s_env, s_top))
		{
			_tcscat(s_env, s_top);
			SetEnvironmentVariable(_T("Path"), s_env);
		}	
	}
}


// �Զ����û�������
class JZAutoSetEnv
{
public:
	JZAutoSetEnv(LPCTSTR DLLDir) throw()
	{
		// ȱʡ���ã��Զ����û�������
		JZDLL_SetEnv(DLLDir);
	}

	~JZAutoSetEnv() 
	{
	}
};

#endif // __JZ_AUTOSETENV_H__

