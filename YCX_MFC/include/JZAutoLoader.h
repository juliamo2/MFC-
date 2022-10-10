#ifndef __JZ_LOADER_H__
#define __JZ_LOADER_H__
#include <Windows.h>
#include <tchar.h>
#include <io.h>
#include <JZAutoSetEnv.h>

// dll�ͷź���
inline void JZDLL_Unload(HMODULE hDLL)
{
	if (NULL != hDLL)
	{
		FreeLibrary(hDLL);
		hDLL = NULL;
	}
}

// ���ؿ��Ӻ���
inline HMODULE _JZDLL_LoadLibrary(LPCTSTR szDLLName, // ��̬��������������չ�� 
								  LPCTSTR szPostfix, // ��׺������������չ��
								  LPCTSTR szDLLPath = NULL) // ��̬������Ŀ¼·�� 
{
	TCHAR s_name[MAX_PATH] = { 0 };
	s_name[0] = '\0';
	if (NULL == szDLLPath)
	{
		_tcscpy(s_name, szDLLName);
		_tcscat(s_name, szPostfix);
	}
	else
	{
		_tcscpy(s_name, szDLLPath);
		_tcscat(s_name, JZDIR_SEPARATOR_S);
		_tcscat(s_name, szDLLName);
		_tcscat(s_name, szPostfix);
	}
	
	return LoadLibrary(s_name);
}


typedef void* (*DefGetAPIStuPtr)();
// ��ȡAPIָ��
inline void _JZDLL_GetAPI(HMODULE& hDLL,			// �Ѽ��صĿ���
						  LPCSTR szAPIExportName,	// ���ؿ⵼���ӿڵ�����
						  void** ppAPI)				// ���������ӿ�ָ��
{
	DefGetAPIStuPtr pfnGet = reinterpret_cast<DefGetAPIStuPtr>(GetProcAddress(hDLL, szAPIExportName));
	*ppAPI = pfnGet();
	if (NULL == *ppAPI)
	{
		JZDLL_Unload(hDLL);	// ��������ӿڲ��ɹ������ͷ� DLL
		hDLL = NULL;
	}
}

// dll���غ���
inline HMODULE JZDLL_Load(
	LPCTSTR szDLLName,				// ���ؿ������
	LPCSTR szAPIExtName,			// ���ؿ⵼���ӿڵ�����
	void** ppAPI)					// ���������ӿ�ָ��
{
	// �������
	if (NULL == szDLLName || NULL == szAPIExtName)
	{
		return NULL;
	}

	HMODULE hDLL = NULL;
	// Ԥ�ȼ���һ�Σ������ظ�������ȱʡ·���������ǵ�������������������ʱ
#ifdef _DEBUG
	hDLL = _JZDLL_LoadLibrary(szDLLName, JZDLL_POSTFIX_DEBUG); // ���ϵͳ���� DEBUG ģʽ��ʱ�����Ե��� DEBUG �汾��
#endif // _DEBUG
	if (NULL == hDLL) // ������� DEBUG ģʽ�»��� DEBUG �汾��ʧ�ܣ����Ե��� RELEASE �汾��
	{
		hDLL = _JZDLL_LoadLibrary(szDLLName, JZDLL_POSTFIX_RELEASE);
	}

	if (NULL != hDLL) // ������سɹ���ֱ�ӷ��أ��������ִ����������������
	{
		_JZDLL_GetAPI(hDLL, szAPIExtName, ppAPI);
		return hDLL;
	}

	TCHAR s_top[MAX_PATH] = { 0 };
	TCHAR s_env[JZENV_MAX_LENGTH] = { 0 };
	s_top[0] = '\0';
	s_env[0] = '\0';

	LPCTSTR p_separator = NULL;
	GetModuleFileName(NULL, s_top, MAX_PATH - 1);
	for (int i = 0; i < 4; i++)
	{
		p_separator = _tcsrchr(s_top, JZDIR_SEPARATOR);
		if (NULL == p_separator)
		{
			return NULL;
		}
		*(LPTSTR)p_separator = '\0';
	}
	_tcscat(s_top, JZ_DLL);
	_tcscat(s_top, JZDLL_DIR);

	GetEnvironmentVariable(_T("Path"), s_env, JZENV_MAX_LENGTH - 1);
	_tcscat(s_env, JZENV_SEPARATOR_S);

	// ���ϵͳ��������ӵ�е�ǰ�����������ټ���
	if (NULL == _tcsstr(s_env, s_top))
	{
		_tcscat(s_env, s_top);
		SetEnvironmentVariable(_T("Path"), s_env);
	}
	
#ifdef _DEBUG
	hDLL = _JZDLL_LoadLibrary(szDLLName, JZDLL_POSTFIX_DEBUG); // ���ϵͳ���� DEBUG ģʽ��ʱ�����Ե��� DEBUG �汾��
#endif // _DEBUG
	if (NULL == hDLL) // ������� DEBUG ģʽ�»��� DEBUG �汾��ʧ�ܣ����Ե��� RELEASE �汾��
	{
		hDLL = _JZDLL_LoadLibrary(szDLLName, JZDLL_POSTFIX_RELEASE);
	}

	_JZDLL_GetAPI(hDLL, szAPIExtName, ppAPI);

	return hDLL;
}

// �Զ�������
template<class _Func, class _Pos>
class JZLoader
{
public:
	JZLoader() throw() : _Moudle(NULL), _Fpval(NULL)
	{
		// ���ؿ⣬����ȡ�ӿ�ָ��
		Load(NULL);
	}

	~JZLoader() throw()
	{
		// �ͷſ�
		if (NULL != _Moudle)
		{
			JZDLL_Unload(_Moudle);
		}
	}

	bool Load(LPCTSTR szDLLParentPath)
	{
		if (_IsLoaded())
		{
			return true;
		}
		else
		{
			_Pos _Pval;
			// �������ĵ�����������Ϊ��������
			for (int i = 0; i < _Pval.ThirdPartyNum(); i++)
			{
				JZDLL_SetEnv(_Pval.ThirdParty()[i]);
			}
			
			_Moudle = JZDLL_Load(_Pval.DLLName(), _Pval.APIExtName(), (void**)&_Fpval);
			return _IsLoaded();
		}	
	}

	// ���ر����Ͷ���bool����ʽת��
	operator bool() const
	{
		return (NULL != _Fpval);
	}

	operator _Func* ()
	{
		return _Fpval;
	}

	// ����->ָ�������
	_Func* operator ->() const
	{
		return _Fpval;
	}

private:
	JZLoader(JZLoader<_Func, _Pos> const&) throw();
	JZLoader<_Func, _Pos>& operator=(JZLoader<_Func, _Pos> const&) throw();
	bool _IsLoaded()
	{
		return (NULL != _Moudle);
	}

private:
	HMODULE _Moudle;
	_Func* _Fpval;
};
#endif // __JZ_LOADER_H__

