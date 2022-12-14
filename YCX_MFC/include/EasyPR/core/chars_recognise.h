//////////////////////////////////////////////////////////////////////////
// Name:	    chars_recognise Header
// Version:		1.0
// Date:	    2014-09-28
// Author:	    liuruoze
// Copyright:   liuruoze
// Reference:	Mastering OpenCV with Practical Computer Vision Projects
// Reference:	CSDN Bloger taotao1233
// Desciption:
// Defines CCharsRecognise
//////////////////////////////////////////////////////////////////////////
#ifndef EASYPR_CORE_CHARSRECOGNISE_H_
#define EASYPR_CORE_CHARSRECOGNISE_H_

#include "core/chars_segment.h"
#include "core/chars_identify.h"
#include "core/core_func.h"
#include "util/util.h"
#include "core/plate.hpp"
#include "config.h"
#include "basedef.h"
namespace easypr
{

	class EASYPR_API CCharsRecognise
	{
	public:
		// 构造函数
		CCharsRecognise();
		// 析构函数
		~CCharsRecognise();
		// 字符识别
		int charsRecognise(cv::Mat plate, std::string& plateLicense);
		int charsRecognise(CPlate& plate, std::string& plateLicense);
		// 获取车牌颜色
		inline std::string getPlateColor(cv::Mat input) const
		{
			std::string color = "未知";
			Color result = getPlateType(input, true);
			if (BLUE == result) color = "蓝牌";
			if (YELLOW == result) color = "黄牌";
			if (WHITE == result) color = "白牌";
#ifdef OS_WINDOWS
			color = utils::utf8_to_gbk(color.c_str());
#endif
			return color;
		}
		// 获取车牌颜色
		inline std::string getPlateColor(Color in) const
		{
			std::string color = "未知";
			if (BLUE == in) color = "蓝牌";
			if (YELLOW == in) color = "黄牌";
			if (WHITE == in) color = "白牌";
#ifdef OS_WINDOWS
			color = utils::utf8_to_gbk(color.c_str());
#endif
			return color;
		}
		// 字符分割器设置函数
		inline void setLiuDingSize(int param)
		{
			m_charsSegment->setLiuDingSize(param);
		}
		inline void setColorThreshold(int param)
		{
			m_charsSegment->setColorThreshold(param);
		}
		inline void setBluePercent(float param)
		{
			m_charsSegment->setBluePercent(param);
		}
		inline float getBluePercent() const
		{
			return m_charsSegment->getBluePercent();
		}
		inline void setWhitePercent(float param)
		{
			m_charsSegment->setWhitePercent(param);
		}
		inline float getWhitePercent() const
		{
			return m_charsSegment->getWhitePercent();
		}

	private:
		CCharsSegment*		m_charsSegment; // 字符分割器指针
	};

} /* \namespace easypr  */

#endif  // EASYPR_CORE_CHARSRECOGNISE_H_