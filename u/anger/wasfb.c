//万安寺副本 by renlai

#include <ansi.h>

inherit FBROOM;

void create()
{
        set("short", HIM"万安寺塔-副本"NOR);
        set("long", @LONG
万安寺塔内，塔内人影绰绰，每一层中都有人来回巡查，塔下
更有二三十人守着，在塔内一侧有一处盘旋而上的石阶(up)。
LONG);
        //set("outdoors", "万安寺");
		set("backroom","/d/was/was");
        set("quest",1);
		set("no_sleep_room",1);
		set("no_quit", 1);		
        
		
   setup();
}
#include "fuben.h";

int do_up()
{
	object me=this_player();
	
	if (me->is_busy())
	{
		write("你正忙着呢。\n");	
		return 1;
	}
	
	if (me->is_fighting()) 
	{
		write("敌人没杀死还想跑?\n");	
		return 1;
	}
	
	if(present("menggu wushi", environment(me)))
	{
		write("敌人没杀死还想跑?\n");	
		return 1;
	}
	if (me->query_temp("was_up"))
	{
		write("不要惊动了巡逻武士，先等一下吧。\n"); 	
		return 1;
	}
	
	if (me->query_temp("was_job/enter") ){	 	
        me->apply_condition("was_job", 3);
        me->set_temp("was_up", 1);			
		message_vision(BLU "你见已无人看守，闪身便往楼上走去。\n" NOR, me);	
	}
	else
	{
		write("你还没进塔呢。\n");	
	}
	return 1;	
}