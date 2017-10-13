// FileName: BrowsHistory.h  
// ------------------------------------------------------------------------------------------------------------------------  
// Remarks:  
//   BrowsHistory����Ӧ�����ó�ȫ�֣����߾�̬����ֹ��û�л�ȡ����ַ������������ˣ�  
// ------------------------------------------------------------------------------------------------------------------------  

#pragma once  
#include <iostream>  
#include <algorithm>  
#include <functional>  
#include <vector>  
#include "afxwin.h"  
struct BrowsData
{
public:
	// ��ַ  
	CString strURL;

	//��Ӧ����ʱ�䣬������Сʱ������
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;

	// ��Ӧ��ַ���ʴ���  
	unsigned int nCount;

	// ����<������  
	bool operator < (const BrowsData &m)const
	{
		return nCount > m.nCount;
	}
};
class BrowsHistory
{
private:

	// �����õ���ַ�ͷ��ʴ���  
	std::vector<BrowsData> m_BrowsHistroy;
private:
	// IE��ַ���ˣ���ֻȡ��ַcomǰ�ߵ�  
	void urlFiltrateIE(LPWSTR lpszSourceUrlName);

	// Chrome��ַ���ˣ���ֻȡ��ַcomǰ�ߵ�  
	void urlFiltrateChrome(CString strUrlName, __int64 SubtleSeconds);
	// Firefox��ַ���ˣ���ֻȥ��ַcomǰ�ߵ�  
	void urlFiltrateFirefox(CString strUrlName, __int64 SubtleSeconds);
	// ��ѯ�����Ƿ��Ѵ���, ����true��ʾ���ڣ��Զ����������  
	bool IsRunning(CString exe);
	// ����ת��  
	void ConvertUtf8ToGBK(CStringA &strUtf8);
	// ��ȡ�������ʷ��¼  
	void InitHistroy(void);
	// ��1960��1��1�յĺ���ת��Ϊ������
	void TimeTransformation(__int64 SubtleSeconds);
	// ���̺߳���  
	static void ThreadPro(LPVOID * ptr);
	// �Ի�õ���ַ��������  
	void Sort(void);
public:
	BrowsHistory();
	~BrowsHistory();
	// ��ȡ��ַ�Ľ��̣��Ƿ�ִ���ꣻִ����ʱΪtrue��  
	bool m_bStatus;
	// ��ʼ��  
	void Init(void);
	// ��ȡ�������ʷ��¼  
	std::vector<BrowsData> GetBrowsHistory(void) const;
};

// ����64λ����
#if defined(_WIN32) && !defined(CYGWIN)
typedef __int64 int64_t;
#else
typedef long long int64t;
#endif  // _WIN32
// ��1601��1��1��0:0:0:000��1970��1��1��0:0:0:000��ʱ��(��λ100ns)
#define EPOCHFILETIME   (116444736000000000UL)