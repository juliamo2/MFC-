//////////////////////////////////////////////////////////////////////////
// Name:	    CHARACTER Header
// Version:		1.0
// Date:	    2016-06-14
// Author:	    liuruoze
// Copyright:   liuruoze
// Desciption:
// An abstract class for car character in plate.
//////////////////////////////////////////////////////////////////////////
#ifndef EASYPR_CORE_CHARACTER_H_
#define EASYPR_CORE_CHARACTER_H_

#include "opencv2/opencv.hpp"

using namespace cv;

/*! \namespace easypr
Namespace where all the C++ EasyPR functionality resides
*/
namespace easypr
{

	class CCharacter
	{
	public:
		// 构造函数
		CCharacter()
		{
			m_characterMat = Mat();
			m_characterGrayMat = Mat();
			m_characterPos = Rect();
			m_characterStr = "";
			m_score = 0;
			m_isChinese = false;
			m_ostuLevel = 125;
			m_center = Point(0, 0);
			m_index = 0;
		}

		// 构造函数
		CCharacter(const CCharacter& other)
		{
			m_characterMat = other.m_characterMat;
			m_characterGrayMat = other.m_characterGrayMat;
			m_characterPos = other.m_characterPos;
			m_characterStr = other.m_characterStr;
			m_score = other.m_score;
			m_isChinese = other.m_isChinese;
			m_ostuLevel = other.m_ostuLevel;
			m_center = other.m_center;
			m_index = other.m_index;
		}

		// 参数设置/获取函数
		inline void setCharacterMat(Mat param) { m_characterMat = param; }
		inline Mat getCharacterMat() const { return m_characterMat; }

		inline void setCharacterGrayMat(Mat param) { m_characterGrayMat = param; }
		inline Mat getCharacterGrayMat() const { return m_characterGrayMat; }

		inline void setCharacterPos(Rect param) { m_characterPos = param; }
		inline Rect getCharacterPos() const { return m_characterPos; }

		inline void setCharacterStr(String param) { m_characterStr = param; }
		inline String getCharacterStr() const { return m_characterStr; }

		inline void setCharacterScore(double param) { m_score = param; }
		inline double getCharacterScore() const { return m_score; }

		inline void setIsChinese(bool param) { m_isChinese = param; }
		inline bool getIsChinese() const { return m_isChinese; }

		inline void setOstuLevel(double param) { m_ostuLevel = param; }
		inline double getOstuLevel() const { return m_ostuLevel; }

		inline void setCenterPoint(Point param) { m_center = param; }
		inline Point getCenterPoint() const { return m_center; }

		inline void setIndex(int param) { m_index = param; }
		inline int getIndex() const { return m_index; }

		inline bool getIsStrong() const { return m_score >= 0.9; }
		inline bool getIsWeak() const { return m_score < 0.9 && m_score >= 0.5; }
		inline bool getIsLittle() const { return m_score < 0.5; }

		bool operator < (const CCharacter& other) const
		{
			return (m_score > other.m_score);
		}

		bool operator < (const CCharacter& other)
		{
			return (m_score > other.m_score);
		}

	private:
		//! character mat
		Mat		m_characterMat;			// 字符分割后的图块

		//! character gray mat
		Mat		m_characterGrayMat;		// 字符分割后的灰度图块

		//! character rect
		Rect	m_characterPos;			// 字符图块在原图像中的矩形块位置

		//! character str
		String m_characterStr;			// 字符块对应的文字

		//! character likely
		double m_score;					// 该字符图块识别为该文字的可能性

		//! weather is chinese
		bool m_isChinese;				// 是否为中文

		//! ostu level
		double m_ostuLevel;

		//! center point
		Point m_center;

		//! the postion in the plate, from 1 to 7 normal
		int m_index;					// 该字符块在车牌中的位置，1~7之间的一个数字
	};

} /*! \namespace easypr*/

#endif  // EASYPR_CORE_PLATE_H_