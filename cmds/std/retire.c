// retire.c 金盆洗手
// by augx@sj 3/15/2002

#include <ansi.h>
inherit F_CLEAN_UP;

void abandon(object me)
{
	if( !me->query("prepare_retire") ) {
		tell_object(me,"你并没有准备金盆洗手啊。\n");
		return;
	}
	me->delete("prepare_retire");
	tell_object(me,"你放弃了金盆洗手。\n");
}

int main(object me, string arg)
{
	if( arg && arg=="abandon" ) {
		abandon(me);
		return 1;
	}
	//return notify_fail("金盆洗手正在重新整理中，暂时关闭。\n");
	
	if (me->query("no_pk") || me->query("no_pk_disable"))
		return notify_fail("你不是已经金盆洗手了吗？\n");
				
	if ( me->query("registered") < 3 )
		return notify_fail("只有贵宾用户才能金盆洗手。\n");
		
	//if (me->query_temp("user_type") == "worker")
		//return notify_fail("你又不是武林人士，如何金盆洗手？\n");

	if (me->query("prepare_retire")) {
        if( time()- me->query("pk_time") < 86400 )
	
	{
			me->delete("prepare_retire");
			me->delete("prepare_retire_time");
			return notify_fail("由于你又参与了江湖的是非，所以你决定取消你的金盆洗手。\n");
		}
   if( (time()-me->query("prepare_retire_time")) < 86400 )
 
			return notify_fail("你金盆洗手的时间还未到，你可以在"+CHINESE_D->chinese_time(86400-time()+me->query("prepare_retire_time"))+"后正式金盆洗手。\n");

	    CHANNEL_D->do_channel(me,"chat",HIY"我今日正式金盆洗手，从此退出江湖，不再过问江湖纷争！"NOR);
		me->delete("prepare_retire");
		me->delete("prepare_retire_time");
		me->set("no_pk",me->query("combat_exp"));
		me->save();
		log_file("static/RETIRE",sprintf("金盆洗手：%8s(%-8s) ；exp：%d \n",me->name(1),me->query("id"),me->query("combat_exp")),me);
	} else {
                if( (time()-me->query("prepare_retire_time")) < 604800 )
					return notify_fail("你不是刚刚才放弃金盆洗手吗？\n");
                if( time()- me->query("pk_time") < 86400)
		{
					return notify_fail("你正在江湖争斗中恐怕难以自拔。\n");
		}				
		CHANNEL_D->do_channel(me,"chat",HIY"我已厌倦无尽的江湖争斗，准备金盆洗手，从此不再过问江湖纷争！"NOR);
		me->set("prepare_retire",1);
		me->set("prepare_retire_time",time());
	}
	
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : retire

金盆洗手，退出江湖，从此不再参与江湖争斗。

如果你决定金盆洗手，在第一次输入此命令后，有一天的时间了结
江湖恩怨，在此期间，如果发生主动PK，将视为你放弃金盆洗手。
一天之后再次输入本命令，将正式退出江湖。

如果在一天内你决定放弃金盆洗手，请输入“retire abandon”命令。
如果你放弃，在之后的7天里，你将不能再次金盆洗手。

如果你在最近的一天内内参与了江湖争斗那将不能金盆洗手，同样
你在准备金盆洗手的一天内参与了江湖争斗，那金盆洗手就会被
取消。

注意！！！！！！！
发现正式金盆洗手后的玩家以任何形式参与玩家争斗，将处罚以减少
该玩家10%-30%的经验值。

其他相关指令: rejoin(重出江湖)

HELP);
	return 1;
}
