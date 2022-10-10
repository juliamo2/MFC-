#ifndef __IJZ_UIENGINEPROC_H__
#define __IJZ_UIENGINEPROC_H__
#include <IJZUIEngine.h>
#include <JZAutoLoader.h>

#define JZ_UIENGINE_DLL_NAME			_T("JZUIEngine")
#define JZ_UIENGINE_API_EXT_NAME		"JZUIE_GetAPIStuPtr"
#define JZ_UIENGINES_THIRD_PARTY		{}
#define JZ_UIENGINE_THIRD_PARTY_NUM		0


class CJZUIEngineDLLPos
{
public:
	LPCTSTR DLLName() const { return JZ_UIENGINE_DLL_NAME; }
	LPCSTR APIExtName() const { return JZ_UIENGINE_API_EXT_NAME; }
	int ThirdPartyNum()const { return JZ_UIENGINE_THIRD_PARTY_NUM; }
	LPCTSTR* ThirdParty() const
	{
		//LPCTSTR thirdParty[JZ_UIENGINE_THIRD_PARTY_NUM] = JZ_UIENGINE_THIRD_PARTY_NUM;
		return  NULL;
	}
};

//__declspec(selectany) JZAutoSetEnv g_BaseImageAutoSetEnv(_T("OpenCV"));	// �Զ��������ĵ�����������Ϊ��������
__declspec(selectany) JZLoader<JZUIEngineAPI, CJZUIEngineDLLPos> g_JZUIEngineAPI;  // ���������Ľӿ� 
#endif // __IJZ_UIENGINEPROC_H__

