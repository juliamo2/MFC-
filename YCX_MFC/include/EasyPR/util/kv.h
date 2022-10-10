#ifndef EASYPR_UTIL_KV_H_
#define EASYPR_UTIL_KV_H_

#include <map>
#include <string>
#include "basedef.h"
namespace easypr
{
	// ����ӳ����
	class EASYPR_API Kv
	{
	public:
		// ���캯��
		Kv();
		// ����xml�ļ���ȡ����ӳ���
		void load(const std::string &file);
		// ������ӳ����У��õ���-ֵ��
		std::string get(const std::string &key);
		// ������ӳ����У����ĳһ����-ֵ��
		void remove(const std::string &key);
		// �������ӳ���
		void clear();

	private:
		// ������ӳ��Լ�������ӳ���
		void _add(const std::string &key, const std::string &value);
	private:
		std::map<std::string, std::string>	 m_data;	// ����ӳ���
	};

}

#endif // EASYPR_UTIL_KV_H_