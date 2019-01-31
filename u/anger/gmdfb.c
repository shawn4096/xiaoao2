// gmdfb.c  光明顶副本

// 添加围攻光明顶副本 by renlai
inherit FBROOM;
#include <ansi.h>
void create()
{ 
       set("short",HIR"光明顶-副本"NOR);
       set("long", "
    这里就是明教光明顶。你走到这里就可看见三个鲜红色大字。明教，少林，\n"+
"丐帮中明教是最大的教，少林是最大的门派，而丐帮则是最大帮派。明教自由\n"+
"波斯总教传至中原已有百多年的历史了。明教始终都以反元抗胡，行善去恶及\n"+
"除暴安良为自已的宗旨。但由于明教太大，门下教众难免莨莠不齐，至使被名\n"+
"门正派称为魔教。正中央一面红色火焰的大旗。北边是练武场，南边是巨木旗\n"+
"的所在地。此时却见六派已将光明顶上明教教众团团围困,正在逐一挑战(up)明教高手。\n\n"HIR"\t\t\t光    明    顶\n\n"NOR);	
        
		set("backroom","/d/mingjiao/gmd");
        set("quest",1);
		set("no_sleep_room",1);
		set("no_quit", 1);
        set("outdoors", "副本");		
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
	
	if(present("mingjiao jiaozhong", environment(me)))
	{
		write("敌人还没打败，你想找死吗?\n");	
		return 1;
	}
	if (me->query_temp("gmd_up"))
	{
		write("不要着急，先等一下吧。\n"); 	
		return 1;
	}
	
	if (me->query_temp("gmd_job/enter") ){	 	
        me->apply_condition("gmd_job", 3);
        me->set_temp("gmd_up", 1);			
		message_vision(BLU "你忽然大吼一声，谁敢来战！！！\n" NOR, me);	
	}
	else
	{
		write("围攻之势还没准备好呢。\n");	
	}
	return 1;	
}

