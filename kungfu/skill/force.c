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
	//�Կ�Ч���Ǵ�-3 -> 3���ֱ����������ص����˺��ᣬΨһһ�����⣬��jiuyin-zhengong������
	//��Ȼ������������Ч��
	//��ͬ�ڹ����ʵ��ڹ���������˵�Ч����dulong-dafa���������ڹ���
	//���Ե��ڹ��Կ������Ч���ͺã����������ڹ����޷��Կ�����Ҫ�����˺�
	//û���г������ڹ������������ڹ����޷������ˡ�:(
        switch (skill)
        {//���������ж�
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