//Room fengchantai.c 封禅台

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIY"封禅台"NOR);
	set("long", @LONG
封禅台为大麻石所建，每块大石都凿得极是平整，当年历代皇帝为了祭天
祀福，不知驱使多少民工、石匠始建成此巨构。封禅台下是可以容纳数千人的
广场，登临于此，可以望见大熊峰、小熊峰、双主峰、三尖峰和少林寺所在的
少室山，不禁让人想起杜甫“齐鲁青未了”的绝句。
LONG);
	set("exits", ([
	    "southdown" : __DIR__"peitian-fang",
	]));
	set("objects", ([
		CLASS_D("songshan") + "/zuo" : 1,
	      __DIR__"npc/ssdizi" : 3,
	]));
	set("outdoors", "嵩山");
   	setup();
}

void init()
{
	object me = this_player();
	if ( me->query("songshan_points")){
		me->add("job_time/嵩山", me->query("songshan_points"));
		me->delete("songshan_points");
	}
	add_action("do_enter","guan");
	add_action("do_qs","qi");
        add_action("do_jieti","jieti");
        add_action("do_decide","decide");
}

int do_enter(string arg)
{
	object me;

	me = this_player();
	if( !arg || arg=="" ) return 0;
	if( arg=="ri" ) {
		if (me->is_busy() || me->is_fighting())
			return notify_fail("你正忙着呢。\n");
		if (me->query("family/family_name")=="嵩山派") {
		       	message("vision",me->name()+"整了整衣服，向观日峰走了过去。\n",environment(me),({me}) );
		       	me->move("/d/songshan/guanrifeng");
		       	message("vision",me->name() + "从封禅台走了过来。\n",environment(me), ({me}) );
		       	return 1;
	   	}
     		return notify_fail("那边太阳好大，你不怕晒黑吗？\n");
	}
}
//嵩山砌石工作
int do_qs(string arg)
{
	object me,ob;
	int gold;
	me = this_player();
	ob = present("shi kuai",me);
	gold=10;
	if( !arg || arg=="" ) return notify_fail("你要干什么？\n");

	if(!ob) return notify_fail("修整需要石料，你要用什么来砌？\n");

	if(!me->query_temp("ss_qs/taked")) return notify_fail("你还没去搬石头呢吧？\n");
	if (arg!="shikuai"&&arg!="石块") return notify_fail("你要用石头做什么？");
	/*
		shen = me->query("max_pot")/2 + random(200);
		exp = me->query("max_pot")/2+random(20);
		exp = me->add_exp_combat(exp,this_object(),"嵩山砌石");
		pot = exp/5+random(exp/10);

		//me->add("combat_exp",exp);
		if (me->add("potential",pot) > me->query("max_pot"))
			me->set("potential", me->query("max_pot"));
		me->add("shen",-shen);

		me->improve_skill("hanbing-zhenqi",me->query("int"));*/
	if (me->query("quest/ss/rumen/pass")
		&&me->query("family/family_name")=="嵩山派"
		&&me->query_skill("hanbing-zhenqi",1)<100)
	{
		tell_object(me,"你猛然发力间，忽然一股真气由丹田爆发，寒冰真气修为似乎又增长了些！\n");
		me->improve_skill("hanbing-zhenqi",2*me->query("int"));
	}
	//me->set("job_name","嵩山砌石");


	me->add_condition("job_busy", 2+random(2));
	me->delete_temp("ss_qs");
	destruct(ob);
	message_vision("$N将一块石头砌在封禅台破损的一角上。\n",me);
	//me->apply_condition("ssjob/qishi",1);
	if (me->query("combat_exp")<200000)
	{
		tell_object(me,"狄修在远处喊道，“不错，这次搬石头工作做得很细心！好苗子，我很看好你。”\n");
		TASKREWARD_D->get_reward(me,"嵩山砌石",-1,0,0,1,0,0,0,"狄修");  
	}else{
		tell_object(me,"不错，好好干，我很看好你！\n");
		me->add("potential",10+random(10));
		me->add("shen",-100);
	}
	me->add("party/gongji",1+random(3));
//	tell_object(me,"你获得了"++);
	if (random(me->query("job_time/嵩山砌石"))>200
		&&!me->query("quest/ss/rumen/pass")
		&&random(me->query("kar"))>25 )
	{			
		message_vision(HIG"狄修在远处对$N喊道，“我观察你好久了，是个好苗子，如果你愿意就到关胜峰来拜我为师！”\n"NOR,me);
		me->set("quest/ss/rumen/pass",1);
	}	
	/*	me->add("job_time/嵩山砌石",1);
		tell_object(me,HIW" 你得到了：\n" +
	    	chinese_number(exp) + "点实战经验\n"+
	    	chinese_number(pot) + "点潜能和\n"+
	    	chinese_number(shen)+ "负神\n"NOR);*/
		return 1;
	
}
