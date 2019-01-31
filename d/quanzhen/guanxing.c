// guanxing 观星台
//重阳闭关创建掌法之地
// by sohu@xojh

#include <ansi.h>

inherit ROOM;


void create()
{
	set("short","观星台");
	set("long",@LONG
这里是终南山后山顶一处大平台。平台呈圆形，地上按二十八宿的方
位排布着一些石头，内呈八卦之势，中间嵌入一个巨大的太极图，阴阳相
融，此地天气高爽，若在晚上可以看见正北方的北斗七星。
LONG
);
	set("exits",([
		"down" : __DIR__"didao4",
	]));
	set("outdoors","quanzhen");
	set("no_clean_up",0);
	setup();
}

void init()
{

	add_action("do_guanwu",({"guanwu","lingwu","canwu"}) );
	
}

int do_guanwu(string arg)
{
	mixed *local;
	int night,level;

	object me ;
	me= this_player();
	if (!arg||arg!="北斗七星")
	{
		return notify_fail("你要观悟什么？\n");
	}
	night = 0;
	local = localtime(time() * 60);
	if (local[2] < 5 || local[2] >= 19) night = 1;
	
	if (!night)
	{
		return notify_fail("现在是白天，你无法观悟北斗七星阵势变化！\n");
	}

	if (!me->query_temp("quest/qz/htz/chongyang/askma"))
	{
		message_vision(YEL"$N盘膝而坐，呆了半晌，只觉星空灿烂无比！\n"NOR,me);
		return 1;
	}
	if (me->query_temp("quest/qz/htz/chongyang/start"))
	{
		message_vision(YEL"你正在观悟北斗七星中！\n"NOR,me);
		return 1;
	}
	if (time()-me->query("quest/qz/htz/chongyang/time")<86400)
	{
		message_vision(YEL"你来的太频繁了！\n"NOR,me);
		return 1;
	}
	if (me->is_busy())
	{
		return notify_fail("你正在忙碌中！\n");
	}
	message_vision(HIG"$N盘膝而坐，五心向天，观悟天上北斗七星运转变化，心中潮起潮落，万物寂寥！\n"NOR,me);
	me->set_temp("quest/qz/htz/chongyang/start",1);
	remove_call_out("guan_xing");
	call_out("guan_xing",1,me);
	return 1;
}

int guan_xing(object me)
{
	int i,j,total;
    if(!me) return 0;

    if(me->query_temp("guan_xing")<(10+random(3)))
    { 
	  me->add_temp("guan_xing",1);
      if(random(2)) tell_object(me,BLU"\n你仰首望天，天上繁星点点，你似乎觉得星斗的移动与你所学的昊天掌有莫大的联系..\n"NOR);
      else tell_object(me,HIY"\n突然间，你又掌握了一些在实战中运用昊天掌力的技巧..\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("guan_xing");
	  call_out("guan_xing",3+random(3), me);
    } else
    {  
	  me->delete_temp("guan_xing");
      total = me->query("int");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
      i=random(j);

    	if (i < 3 
		&& random(me->query("kar"))>26
		&& random(total) >= 40) 		 
		{
       
			  tell_object(me,HIM"$N按照马钰的指点，结合自己所悟，仰观天上北斗七星，观看北斗七星的奥秘！\n"NOR);
			  message_vision(HIC"$N熟能生巧，陡然间你忽然明白了这连环掌的意境。”\n"NOR,me); 
			  tell_object(me,HIR"$N又忽然懂得了北斗七星以及重阳祖师在此观悟北斗七星运转的道理，对于昊天掌的认识大大不同！\n"NOR);
			  tell_object(me,HIY"$N终于懂得了重阳连环掌的绝技奥秘，不禁连声大笑，原来如此，原来如此！\n"NOR);
			  tell_object(me,HIW"$N将方才的所得暗暗思索，顿觉脑中对昊天掌的理解进入了一个前所未有的新境\n"NOR);
			  
			  me->set("quest/qz/htz/chongyang/pass", 1);
			  me->set("title",HIG"全真教 昊天掌传人"NOR);
			  log_file("quest/qzchongyang", sprintf("%s(%s) 失败%d次后，成功解开昊天掌重阳连环掌的奥秘。富源：%d；经验：%d。\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/qz/htz/chongyang/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			  me->start_busy(1);
         }
         else
         {
			 tell_object(me,HIG"\n你沉思许久，脑子越来越混沌，始终不得要领。\n"NOR);
			 message_vision(HIC"\n$N摇了摇头，深深地叹了口气。\n"NOR,me); 
			 message_vision(HIY"$N抓耳挠腮，苦思冥想，发现自己还是无法理解昊天掌重阳连环掌奥意所在，脸上一筹莫展。\n"NOR,me);
			 tell_object(me,HBBLU"\n很可惜，你本次尝试昊天连环掌解密秘密失败！\n"NOR);
			 tell_object(me,HBBLU"你目前的经验是" + me->query("combat_exp") + "，现在时间是书剑"+ NATURE_D->game_time() + "，请记录。\n"NOR);
			 tell_object(me,HBBLU"你将在间隔24小时后获得下一次机会！。\n\n"NOR);
			 log_file("quest/qzchongyang", sprintf("%s(%s) 解密昊天掌重阳连环掌绝技失败%d次。富源：%d；经验：%d。\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/qz/htz/chongyang/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			 me->add("quest/qz/htz/chongyang/fail",1);
			 me->set("quest/qz/htz/chongyang/exp", me->query("combat_exp") );
			 me->start_busy(1);
			 me->set("quest/qz/htz/chongyang/time",time());
        }
		 me->delete_temp("quest");
		 me->delete_temp("quest/qz/htz/chongyang/start");
		 return 1;

	}
}
