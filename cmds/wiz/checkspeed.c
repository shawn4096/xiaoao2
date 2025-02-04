
#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

mixed main(object me, string arg)
{
    object *list;
    string str,str2,cor;
    int t;
    int j;
    int i;
	
	if (!arg)
    {
		arg = me->query("id");
    }

	str = "◎ " + MUD_NAME + " 当前书剑玩家成长速度状态统计\n\n";
    str += "帐号      姓名                 上次经验          本次经验      平均速度(分/小时)       上线时间\n";
    str += "——————————————————————————————————————————————————\n";
    list = filter_array(objects(), (: userp :));
    j = sizeof(list);
    while( j-- ) {
        if( !environment(list[j]) 
        || !me->visible(list[j]) 
        || !interactive(list[j])  ) continue;
        
        if((list[j]->query("mud_age") - list[j]->query_temp("mud_age"))<=0) continue;
        i = (list[j]->query("combat_exp") - list[j]->query_temp("combat_exp")) * 60
                / (list[j]->query("mud_age") - list[j]->query_temp("mud_age"));
        str2 = sprintf("%d",i); 
        if (i < 20) continue;
        t = list[j]->query("mud_age") - list[j]->query_temp("mud_age");

		if(list[j]->query("id") == arg)
		{
			cor = HIY BRED;
		}
		else if (i > 500)
		{
			cor = HIR;
		}
		else if (i > 400)
		{
			cor = HIW;
		}
		else if (i > 200)
		{
			cor = HIY;
		}
		else
		{
			cor = "";
		}
        str += sprintf("%s%-9s%-23s%-16d %-16d%-3s／%-16d%s"NOR"\n",
				cor,
                list[j]->query("id"),
                list[j]->is_robot()?(HIG+list[j]->name(1)+NOR):list[j]->name(1),
                list[j]->query_temp("combat_exp"), 
                list[j]->query("combat_exp"),
                str2,
                i*60,
                CHINESE_D->chinese_time(t)
            );
        
    }      
    str += "——————————————————————————————————————————————————\n";
    str = sprintf("%s共有 %d 位使用者连线中，系统负担：%s\n", str, sizeof(list),
        query_load_average() + "\n");

    write(str);
    return 1;

}

int help()
{
write(@HELP
指令格式 : checkspeed

这个指令可以列出所有在线上的玩家的经验值的获取速度，可以查看有没有人利用BUG获取经验值。

相关指令： checkvip, checkggs
HELP
    );
    return 1;
}

