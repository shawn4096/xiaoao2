// sl_yingke.c

#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
        if (duration < 2) {
			         tell_object(me, HIC "虚明冲你微微笑了笑，拍了拍你的头说道，干的不错！\n" NOR);

                    tell_object(me, HIY "你在迎客亭帮忙迎接客人的时间已到，快回去和清无大师复命吧！\n" NOR);
					me->set_temp("sljob/qingwu/yingked",1);
                return 0;
        }
		if (!living(me))
		{
			write(HIR"虚明看你给累晕倒了，心中长长叹了一口气，还是嫩了点!\n"NOR);
			write("这修佛本质上还是修的心啊!\n");
			write("任务失败！回去找清无比丘再申请一次");
			me->delete_temp("sljob");
			me->clear_condition("sl_yingke");
			return 1;
		}
		switch (random(5))
		{
			case 0:
				message_vision(HIC"$N见有出家挂单的僧人来此询问路径，急忙上前帮忙指点！\n"NOR,me);
				me->add("jingli",-10);
				me->add_busy();
				break;
			case 1:
				write(MAG"一群游民路过，你急忙帮忙发放白粥，忙的满头大汗！\n");
				me->add("jingli",-10);
				me->add_busy();
				break;
			case 2:
				write(YEL"有几个武林人士意图挑战少林高僧，对你指手画脚，你尽量忍气吞声不断劝解，极为耗费心神！\n");
				me->add("jingli",-15);
				me->add("jing",-15);
				me->add_busy();
				break;
			default:
				write(CYN"人来人往，少林寺香火极为旺盛，你忙的满头大汗！\n"NOR);
				break;
		}
        me->apply_condition("sl_yingke", duration - 1);
        return 1;
}

string query_type(object me)
{
	return "job";
}
