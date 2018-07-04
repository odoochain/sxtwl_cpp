#include <iostream>
#include <sstream>
#include<vector>
#include "const.h"
#include "lunar.h"


#ifdef _WIN32
class MBuf : public std::stringbuf {
public:
	int sync() {
		fputs(str().c_str(), stdout);
		str("");
		return 0;
	}
};
#endif

int main()
{

#ifdef _WIN32
	////http://m.blog.csdn.net/article/details?id=52789570
	////控制台显示乱码纠正
	////system("chcp 65001"); //设置字符集（使用SetConsoleCP(65001)设置无效，原因未知）
	//SetConsoleOutputCP(CP_UTF8);
	//CONSOLE_FONT_INFOEX info = { 0 }; // 以下设置字体来支持中文显示。
	//info.cbSize = sizeof(info);
	//info.dwFontSize.Y = 16; // leave X as zero
	//info.FontWeight = FW_NORMAL;
	//wcscpy(info.FaceName, L"Consolas");
	//SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);

	////_setmode(_fileno(stdout), _O_U8TEXT);
	
	//https://stackoverflow.com/questions/45575863/how-to-print-utf-8-strings-to-stdcout-on-windows
	setvbuf(stdout, nullptr, _IONBF, 0);
	MBuf buf;
	std::cout.rdbuf(&buf);
#endif
	
	static const char* Gan[] = { "甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸" };
	static const char* Zhi[] = { "子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥" };
	static const char* ShX[] = { "鼠", "牛", "虎", "兔", "龙", "蛇", "马", "羊", "猴", "鸡", "狗", "猪" };
	static const char* numCn[] = { "零", "一", "二", "三", "四", "五", "六", "七", "八", "九", "十" }; //中文数字
	static const char* jqmc[] = { "冬至", "小寒", "大寒", "立春", "雨水", "惊蛰", "春分", "清明", "谷雨", "立夏", "小满", "芒种", "夏至", "小暑", "大暑", "立秋", "处暑", "白露", "秋分", "寒露", "霜降", "立冬", "小雪", "大雪" };
	static const char* ymc[] = { "十一", "十二", "正", "二", "三", "四", "五", "六", "七", "八", "九", "十" }; //月名称,建寅
	static const char*  rmc[] = { "初一", "初二", "初三", "初四", "初五", "初六", "初七", "初八", "初九", "初十", "十一", "十二", "十三", "十四", "十五", "十六", "十七", "十八", "十九", "二十", "廿一", "廿二", "廿三", "廿四", "廿五", "廿六", "廿七", "廿八", "廿九", "三十", "卅一" };


	Lunar lunar;
    Month month = lunar.yueLiCalc(1990, 7);
	
	std::cout  << month.y << "年"  << (int)month.m << "月" << std::endl;
	std::cout << Gan[month.yearGan] << Zhi[month.yearZhi] << "年" << std::endl;
	std::cout << "生肖：" << ShX[month.ShX] << std::endl;


	std::vector<Day>& days = month.days;
	for (auto it = days.begin(); it != days.end(); ++it)
	{
		Day& day = (*it);
		std::cout << "\n===================================================" << std::endl;;
		std::cout << "公历：" << day.y << "年" << (int)day.m << "月" << day.d << "日" << std::endl;
		if (day.Lleap)
		{
			std::cout << "润" << ymc[day.Lmc] << "月" << rmc[day.Ldi] << "日" << std::endl;
		}
		else
		{
			std::cout << ymc[day.Lmc] << "月" << rmc[day.Ldi] << "日" << std::endl;
		}
		
		std::cout << "儒略历:JD" << J2000 + day.d0 << std::endl;
		std::cout << "星期" << numCn[day.week] << std::endl;
		
		std::cout << Gan[day.Lyear2.tg] << Zhi[day.Lyear2.dz] << "年" 
			<< Gan[day.Lmonth2.tg] << Zhi[day.Lmonth2.dz] << "月"
			<< Gan[day.Lday2.tg] << Zhi[day.Lday2.dz] << "日"
			<< std::endl;
		
		std::cout << "距冬至" << day.cur_dz << "天" << std::endl;
		std::cout << "距夏至" << day.cur_xz << "天" << std::endl;
		std::cout << "距立秋" << day.cur_lq << "天" << std::endl;
		std::cout << "距芒种" << day.cur_mz << "天" << std::endl;
		std::cout << "距小暑" << day.cur_xs << "天" << std::endl;
	}

	getchar();
}
