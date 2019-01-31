// Room: /d/xiangyang/conglin4.c
#include <ansi.h>

inherit ROOM;
void create()
{
	set("short", "山间空地");
	set("long", @LONG
这里是山麓上的一块空地，路旁的杂草和树木被人休整过了。路旁有一个
用树木搭起的小屋，小屋的门口有一些猎人在休息。一些弓箭和绳索挂在路旁
的树上。西北方向有一片树林，史家五兄弟正在这里好象要抓什么动物。
LONG	);
        set("xyjob", 1);
		set("exits", ([
        	"eastdown" : __DIR__"conglin3",
        	"northwest" : "/d/gumu/xuantie/xiaolu4",

        ]));
        set("objects",([
              "/clone/npc/shijiqiang" : 1,
              "/clone/npc/shibowei" : 1,
              "/clone/npc/shimengjie" : 1,
              "/clone/npc/shishugang" : 1,
              "/clone/npc/shizhongmeng" : 1,
        ]));

        set("outdoors", "襄阳");
		setup();
}
int init()
{
	//ask yang 后触发
	object me=this_player();
	if (me->query_temp("quest/shendiao/大雪风陵渡/askanran"))
	{
		add_action("do_heal","heal");
	}
}

int do_heal(string arg)
{
	object me=this_player();
	object shi,shi1,linghu;
	if (!objectp(shi=present("shi shugang",this_object())))
	{
		tell_object(me,"你要疗伤的对象不在！\n");
		return 1;
	}
	shi1=present("shi bowei",this_object());
	
	if (!arg||arg!="史叔刚")
	{
		return notify_fail("你要为谁疗伤？\n");
	}
	if (!me->query_temp("quest/shendiao/大雪风陵渡/askgui"))
	{
		message_vision(CYN"你和史叔刚无缘无故，凭啥为其疗伤？\n"NOR,me);
		return 1;
	}

	if (objectp(linghu=present("jiuwei linghu",me)) && me->query_temp("anran/findfox"))
	{
		message_vision(HIG"$N从怀中将九尾灵狐拎出来，找个腕，从狐狸腿部挤出一点血，交予史伯威。\n"NOR,me);
		message_vision(HIW"\n史伯威对$N表示真诚感谢。\n"NOR,me);

		message_vision(HBYEL+HIR"\n\n$N沉思良久，不禁感慨万千，这当中的恩怨情仇竟然是如此的复杂和难料！\n"NOR,me);
		message_vision(HBBLU+HIW"\n\n恭喜你，完成了《神雕侠侣》大雪风陵渡篇章节内容！"NOR,me);

		me->set_temp("quest/shendiao/大雪风陵渡/healover",1);		
		me->delete_temp("quest/shendiao/大雪风陵渡");
		destruct(linghu);
		me->set("quest/shendiao/大雪风陵渡/healover",1);		
		return 1;
	}
	message_vision(HIC"$N说道，“我从神雕侠杨大侠哪儿得到你这儿的消息，急忙赶来，先让我为史三侠疗伤再说”。\n"NOR,me);
	
	message_vision(HIC"\n\n$N盘膝而坐，双掌贴在史数刚的后背，运功疗伤。\n"NOR,me);
	message_vision(HIR"\n$N头顶蒸汽氤氲，史叔刚哇地吐出一口鲜血。\n"NOR,me);
	shi1->shi_say1();
	
	call_out("come_on",2+random(2),me);
	//me->set_temp("anran/askheal",1);
	shi->clear_condition("neishang");
	return 1;
}

int come_on(object me)
{
	message_vision(HIC"$N说道，伤势虽然好转，既然史大侠说要有九尾灵狐的血，不知道在哪儿可以得到？\n"NOR,me);
	message_vision(HIC"史伯威说道，“曾听人言，在襄阳郊外的树林之中曾发现过此兽。”\n"NOR,me);
	message_vision(HIC"史伯威说道，“我们兄弟几人曾先后捕捉过多次，但均因其极为狡猾，均为其逃掉。”\n"NOR,me);
	message_vision(HIC"史伯威说道，“您若想去捉，一定要小心谨慎，此兽极为机敏。”\n"NOR,me);
	message_vision(HIC"史伯威说道，“有一次我们差点逮住此兽，但却被一个叫瑛姑的高手所阻止。”\n"NOR,me);
	message_vision(HIC"史伯威说道，“据那个瑛姑讲，此兽乃是她私人豢养之物，只是不知真假。”\n"NOR,me);
	me->set_temp("quest/shendiao/大雪风陵渡/askheal",1);
	return 1;
}
