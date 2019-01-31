//daxiong.c

inherit ROOM;
#include <ansi.h>
int do_tiao(string arg);

void create()
{
	set("short", HIY"大雄宝殿"NOR);
	set("long", @LONG
这里是少林寺的大雄宝殿。面阔五间，进深四间。正中供奉着如来三宝
，左右各是文殊、普贤诸位菩萨。一群僧侣正自焚香诵经，仰观我佛拈花微
笑的神态，令人顿感肃然起敬。这里殿堂宽大，亦是方丈大师召集阖寺群僧
议事之所。
LONG
	);
        set("no_fight",1);
       	
		set("exits", ([
		 "south" : __DIR__ "pingtai",
                 "north" : __DIR__ "stoneroad1",
       ]));

	
	set("coor/x",50);
  set("coor/y",300);
   set("coor/z",120);
   setup();
}
void init()
{
    object me=this_player();
	if (me->query_temp("klbs/askhe")
		&&me->query_temp("kl/baihe/fightwei")
		&&me->query_temp("kl/baihe/fightpan")
		&&me->query_temp("kl/baihe/fightfang"))
	{
		message_vision(YEL"$N久在西域，每日见到均为三清雕像，但从没见过如此高大的释迦摩尼神像，忍不住有下跪的冲动。\n"NOR,me);
		message_vision(YEL"$N想了下后忍不住哼了一声自言自语道，“少林寺好大的名气，师傅让我来送拜帖，但我看少林大和尚都稀松平常”。\n"NOR,me);
		message_vision(HIC"$N仰头看了下这神像，如此之高，到可以好好考究一番这少林寺众僧。\n"NOR,me);
		message_vision(HIC"$N想象着少林众僧的尴尬状态，不由地心中得意万分。\n"NOR,me);
		//me->delete_temp("kl/baihe/fightwei");
		//me->delete_temp("kl/baihe/fightfang");
		//me->delete_temp("kl/baihe/fightpan");
		//me->delete_temp("klbs/askhe");

		add_action("do_tiao","tiao");

	}
	
}
int do_tiao(string arg)
{
	object me=this_player();
    if (arg !="shenxiang" && arg !="神像")
		return notify_fail("大雄宝殿是一个神圣的地方，你在这儿上蹿下跳做什么？");
	if (me->query_skill("dodge",1)<350 || me->query_dex()<60)
	     return notify_fail("这神像很高，你身法不够。\n");
	tell_object(me,HIC+me->query("name")+"飞身跃起，嗖的一声跳到菩萨神像之上。\n"NOR);
	
	me->set_temp("kl/baihe/jump",1);
	me->move("d/shaolin/shenxiang");
	return 1;


}

