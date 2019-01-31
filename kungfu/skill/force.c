// force.c

#include <ansi.h>

inherit SKILL;

string exert_function_file(string func)
{
        return "/kungfu/skill/force/" + func;
}
/*
void skill_improved(object me)
{}*/
int force_effect(string skill)
{	
	//对抗效果是从-3 -> 3，分别是受伤最重到受伤很轻，唯一一个例外，是jiuyin-zhengong，吸收
	//当然，本身有吸收效果
	//不同内功性质的内功有相生相克的效果，dulong-dafa属于阴寒内功，
	//阳性的内功对抗这个的效果就好，但是阴性内功就无法对抗，还要附加伤害
	//没有列出来的内功，算是中性内功，无法区分了。:(
        switch (skill)
        {//阴阳属性判断
                case "jiuyang-shengong" : return 9;
				case "hamagong"         : return 9;
                case "yijin-jing"       : return 8;
				case "longxiang-boruo"  : return 2;
                case "huntian-qigong"   : return 3;
                case "qiantian-yiyang"  : return 3;
                case "guiyuan-tunafa"   : return 3;
                case "kurong-changong"  : return 1;
                case "shenghuo-shengong": return 2;
                case "huashan-qigong"   : return 2;
                case "huntian-qigong"   : return 0;
                case "linji-zhuang"     : return -1;
                case "shenzhao-jing"    : return -1;
                case "shenyuan-gong"    : return -1;
                
                case "dulong-dafa"      : return -2;
                case "huagong-dafa"     : return -2;
                case "xuantian-wuji"    : return -4;
                case "yunu-xinjing"     : return -3;
                case "hanbing-zhenqi"   : return -3;
                case "bihai-chaosheng"  : return -3;
				case "zixia-gong"       : return -2;
				case "yinyun-ziqi"      : return -2;
				case "lengquan-shengong"  : return -4;
				case "kuihua-shengong"  : return -4;
                case "jiuyin-zhengong"  : return -4;
                default: return 1;
        }
}