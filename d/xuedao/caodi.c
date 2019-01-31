// Room: /d/huashan/shulin2.c
// Date: Look 99/03/25
#include <ansi.h>

inherit ROOM;
string *dongwu=({"lu","tu","pig","zhangzi","ying"});  
void create()
{
        set("short", HIG"绿草地"NOR);
        set("long", @LONG
你眼前忽然开朗，在这山谷的深处竟然有一处绿草地，在这片白雪皑皑
大雪山深处竟然有如此绿地，实乃罕见，大概是因为四周山高林密，阻挡了寒
气，使得此地温度竟然比其他地方高不少，绿地四周有不少动物在自由自在的
活动，大概很少见人缘故，所以对人并不害怕。
LONG);

        set("exits", ([
              //  "east" : __DIR__"shulin3",
              //  "south" : __FILE__,
                "west" : __DIR__"shulin1",
                "north" : __DIR__"wangyougu",
        ]));

        set("outdoors", "xuedao");
		//set("");
        set("coor/x",40);
		set("coor/y",100);
		set("coor/z",0);
		setup();
}
int init()
{
	add_action("do_find","find");
	add_action("do_find","xunzhao");
	add_action("do_find","search");

}

int do_find(string arg)
{
	object me,ob;
	
	me=this_player();
	if (!arg||arg!="猎物")
	{
		return notify_fail("你在寻找什么？!\n");

	}
	if (!me->query_temp("xuedao/askdalie")&&!me->query_temp("xuedao/askcaixue"))
	{
		return notify_fail("你双手在草地上找来找去，似乎在寻找什么东西!\n");
	}
	if (me->query_temp("xuedao/liewu/findok"))
	{
		return notify_fail("你已经发现猎物，还不赶快赶过去看看!\n");
	}
	if ((objectp(ob=present("meihua lu",environment(me)))&&ob->query("owner")==me->query("id"))
		||(objectp(ob=present("ye zhu",environment(me)))&&ob->query("owner")==me->query("id"))
		||(objectp(ob=present("ye ying",environment(me)))&&ob->query("owner")==me->query("id"))
		||(objectp(ob=present("ye tu",environment(me)))&&ob->query("owner")==me->query("id"))
		||(objectp(ob=present("zhang zi",environment(me)))&&ob->query("owner")==me->query("id")))
	{
		return notify_fail("地上已经有你待杀的猎物了，还不赶紧杀掉采肉？!\n");

	}
	message_vision(HIY"$N进入此地后，小心翼翼聚精会神的在四周寻找猎物！\n"NOR,me);
	
	if (random(me->query("kar"))>15)
	{
		me->start_busy(3);
		message_vision(HIW"突然，$N听到远处传来一阵猎物的鸣叫声，顿时心中大喜！\n"NOR,me);
		me->set_temp("xuedao/liewu/findok",1);
		call_out("liewu_come",2+random(1),me);
		return 1;
	}else {

		message_vision(CYN"$N找了半天，依旧是两手空空，真是晦气！\n"NOR,me);
	
	}
	me->start_busy(2+random(2));
	return 1;
}
int liewu_come(object me)
{
	object ob,animal;
	string dw,msg;
	if (!me) return;
	dw=dongwu[random(sizeof(dongwu))];
	animal=new("d/xuedao/npc/"+dw+".c");
	msg=animal->query("long");
	animal->set("long",msg+"这是"+me->query("name")+"所发现的猎物！\n");
	animal->set("owner",me->query("id"));
	animal->set("combat_exp",(int)me->query("combat_exp")*5/4);
	animal->set("max_qi",(int)me->query("qi")*5/4);
	animal->set("eff_qi",(int)me->query("qi")*5/4);
	animal->set("max_jing",(int)me->query("qi")*5/4);
	animal->set("eff_jing",(int)me->query("jing")*5/4);
	animal->add_temp("apply/damage",10);

	animal->move(environment(me));
	message_vision(HIR"这时，忽然在草丛中窜出一头"+HIR+animal->query("name")+HIR"朝前奔去！\n"NOR,me);
	message_vision(HIC"$N急忙向那头猎物追去！\n"NOR,me);
	me->delete_temp("xuedao/liewu/findok");

	return 1;
}

