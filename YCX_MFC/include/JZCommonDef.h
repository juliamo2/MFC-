#ifndef __JZ_COMMONDEF_H__
#define __JZ_COMMONDEF_H__
#include <Windows.h>
#ifndef MAX_PATH
#	define MAX_PATH          260
#endif
// ���ؽ������
enum JZ_RESULT
{
	JZ_UNKNOW = -1,
	JZ_SUCCESS,
	JZ_FAILED,
	JZ_INVAILD_PARAM,
};

#endif // !__JZ_COMMONDEF_H__
