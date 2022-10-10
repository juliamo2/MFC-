#ifndef __IJZ_RUNTIMEOGLPROC_H__
#define __IJZ_RUNTIMEOGLPROC_H__

#include <IJZRuntimeOGL.h>
#include <JZAutoLoader.h>

#define JZ_RUNTIMEOGL_DLL_NAME			_T("JZRuntimeOGL")
#define JZ_RUNTIMEOGL_API_EXT_NAME		"JZRTOGL_GetAPIStuPtr"
#define JZ_RUNTIMEOGL_THIRD_PARTY		{_T("OpenGL")}
#define JZ_RUNTIMEOGL_THIRD_PARTY_NUM	1

class JZRuntimeOGLDLLPos
{
public:
	LPCTSTR DLLName() const { return JZ_RUNTIMEOGL_DLL_NAME; }
	LPCSTR APIExtName() const { return JZ_RUNTIMEOGL_API_EXT_NAME; }
	int ThirdPartyNum() const { return JZ_RUNTIMEOGL_THIRD_PARTY_NUM; }
	LPCTSTR* ThirdParty() const
	{
		LPCTSTR thirdParty[JZ_RUNTIMEOGL_THIRD_PARTY_NUM] = JZ_RUNTIMEOGL_THIRD_PARTY;
		return  thirdParty;
	}
};

//__declspec(selectany) JZAutoSetEnv g_BaseRenderAutoSetEnv(_T("OpenGL"));	// �Զ��������ĵ�����������Ϊ��������
__declspec(selectany) JZLoader<JZRuntimeOGLAPI, JZRuntimeOGLDLLPos> g_JZRuntimeOGLAPI;  // ���������Ľӿ�

#endif // !__IJZ_RUNTIMEOGLPROC_H__
