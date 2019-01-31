
inherit F_CLEAN_UP;
#include <ansi.h>

int help(object me);


string check(object me)
{
	string msg;

	if (me->query("gmd_job/gmdscore") < 500)
		msg = HIY"系统提示："NOR"抱歉，您的积分不足以兑换。\n";
	if (me->is_ghost())
		msg = HIY"系统提示："NOR"抱歉，你的状态不稳定，现在无法兑换。\n";
	return msg;
}


int main(object me, string arg)
{
	string msg;
	int num,jobs;
	if (!me) return 0;
	if (!arg) return help(me);
	if ( stringp(msg = check(me)) )
		return notify_fail(msg);
	if (sscanf(arg, "%d", num) == 1){	
	   if (num<500 ) return notify_fail("检查一下，500分以下无法兑换。\n");
    if (me->query("gmd_job/gmdscore") < num)
			return notify_fail("你的积分没有这么多。\n");
		jobs=num /500;
		me->add("gmd_job/gmdscore",-jobs*500);
		me->add("job_time/围攻光明顶",jobs);
		write("您使用了"+jobs*500+"点光明顶积分兑换了"+jobs+"次围攻光明顶任务。\n");
		write("您还有光明顶积分"+me->query("gmd_job/gmdscore")+"点。\n");
		me->save();
	    log_file("static/gmdscore",
		me->query("name")+"("+capitalize(geteuid(me))+")"
		+"兑换"+num+"点，增加围攻光明顶job次数"+jobs+"次。\n",
		me,
		({ me })
	);
		
		return 1;
	}
	return help(me);
	
}

int help(object me)
{
	write("	本指令用来将万安寺积分兑换为勇闯万安寺job次数。\n");
    write("	500积分可兑换1次勇闯万安寺。\n\n");
	write("	您目前拥有积分"+me->query("gmd_job/gmdscore")+"点。\n\n");
	write("	若积分不足"+500+"则不能兑换。\n");
	write("	指令格式：\n");
	write("	duihuangmd 500\n");	
	write("	注意，因为是取500的整倍数，即使输入501这样的数值，也只会扣除500分。\n");
	return 1;
}