// Room: /d/emei/cangjinglou.c
#include <ansi.h>

inherit ROOM;
int do_fan(string arg);
void create()
{
	set("short", "藏经楼");
	set("long", @LONG
这里是报国寺的藏经楼。阁楼上密密麻麻排了好多书架，架上摆满了经书。
有两个身穿白衣的小师太正在一角静静地读着经书。
LONG
	);

	set("exits", ([
	    "out" : __DIR__"daxiongdian",
	]));
	set("objects",([
		"/d/emei/obj/fojing1" : 1,
		"/d/emei/obj/fojing2" : 1,
		"/d/emei/npc/daoming" : 1,
	]));
	setup();
}
int valid_leave(object me, string dir)
{
	if (dir == "out" && present("shu", me) && objectp(present("daoming shifu", environment(me))))
		return notify_fail("道明小师傅喝道：“藏经楼内书籍不得外带。\n");

	return ::valid_leave(me, dir);
}
int init()
{
	 add_action("do_fan","fan");

}
int do_fan(string arg)
{
	object me=this_player();
	if (!arg||arg!="经书")
		return notify_fail("峨嵋派藏经阁重地，你乱翻什么？\n");
	
	//if(me->is_fighting()) return 0;
	
	if (me->query("quest/em/zzr/pass"))
	{
		return notify_fail("你已经解开这个秘诀了，此乃峨嵋派藏经阁重地，你乱翻什么？\n");

	}
	if (time()-me->query("quest/em/zzr/time")<86400)
	{
		return notify_fail("你来的太频繁了,此乃练武大忌讳!\n");

	}
    if (!me->query_temp("quest/em/zzr/askzhou"))
  		return notify_fail("此乃峨嵋重地，你来此乱翻什么？\n");


		
		if(me->query("family/family_name")!="峨嵋派")
			if (!me->query_temp("ryb/jiuyin_askdue"))
				return notify_fail("此乃峨嵋派藏经阁重地，你外派弟子乱翻什么？\n");
	 
		if(me->query("shen")<0)
			return notify_fail("你身上邪气凛然，与这藏经阁平和之气不符？\n");

		if(me->query("quest/em/zrr/fail")>=3 && me->query("registered")<3)
			return notify_fail("已经多次传授，你怎么都还没有领悟,真够笨的！？\n");	
	
		if (me->query_skill("yinlong-bian",1)<450)
			return notify_fail("你的银龙鞭法不足450，连飞都没有，反了也白搭！？\n");
		message_vision(HIC"$N在藏经阁中不断翻阅经书，似乎是在查找什么。\n"NOR, me);

	
	
		me->set("quest/em/zzr/time",time());
		me->set("quest/em/zzr/combat_exp",me->query("combat_exp")); 
	
		message_vision(HIY"忽然，$N似乎找到了一本经书，顿时欣喜若狂，情不自禁当场就翻阅开来，\n"NOR,me);
	
		me->start_busy(999);
		remove_call_out("think_ylbf");
		call_out("think_ylbf",1,me);
		return 1;
	
}

int think_ylbf(object me)
{
    int i;
	i=random(10);
	if(me->query_temp("canwu_ylbf")<(10+random(5)))
    {  
	  me->add_temp("canwu_ylbf",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你仔细回忆周芷若的讲述，将她所传授的招式彼此印证，只觉得耳目一新...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n忽然，你似乎抓住了一些明悟。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你陷入馄饨状态，大脑一片空明，似乎要抓住那个线索了！..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，甚是无聊，神情抑郁，似乎有些累了.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎遇到瓶颈了..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n你思维漂浮在空中，宛如婴儿沐浴.神清气爽.\n"NOR);
			break;
		default:tell_object(me,YEL"\n你叹了一口气，精神总是不能有效集中.\n"NOR);
			break;
	  }     

	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));

	  //remove_call_out("think_ssjf");
	  call_out("think_ylbf",3+random(3), me);
	  return 1;

   } 
	else if( i>=8 && random(me->query("kar"))>26)
	{
		tell_object(me,HIC"\n你按照周芷若的指点，结合自己演习所得，对银龙鞭法的奥妙似乎有些心得。\n"NOR);
		tell_object(me,HIY"\n你把银龙鞭的招式从头开始演练，一路演练下来，潇洒自如。越练越是纯熟。\n"NOR);
        tell_object(me,HIC"\n忽然间，你灵光一闪，以前无论如何也想不明白的问题忽然间豁然贯通，忍不住哈哈大笑.\n"NOR);		
		
		me->set("quest/em/zzr/pass",1);
		me->set("quest/em/zzr/time",time());
		log_file("quest/ylbfjueji", sprintf("成功！%8s(%8s) 失败%d次后，彻底领悟银龙鞭法融合的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/em/zzr/fail"),i,me->query("combat_exp")) );
		me->delete_temp("canwu_ylbf");
		me->delete_temp("ryb");
	}
	else
	{		
		tell_object(me,HIY"你翻看着这本经书半天，虽然看见了一些匪夷所思的厉害招式，可是对周芷若所提到的奥妙技巧全然不得要领。\n\n"NOR);
		tell_object(me,HIG"朦胧中远处一声幽怨的叹息传来，一道青色人影向远处飘然而去。\n\n"NOR);
		tell_object(me,HIY"忽然间，你感觉失去了什么。\n解密银龙鞭法技巧失败！\n\n"NOR);
		log_file("quest/ylbfjueji", sprintf("失败，%8s(%8s) 银龙鞭法技巧解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/em/zzr/fail"),i,me->query("combat_exp")) );
		me->set("quest/em/zzr/time",time());
		me->add("quest/em/zzr/fail",1);
		me->delete_temp("canwu_ylbf");	
		me->delete_temp("ryb");
	}
	me->start_busy(1);
	return 1;

}