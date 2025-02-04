// Update by lsxk@hsbbs  增加通宝物品提高解9jian的几率。

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "后山");
	set("long", @LONG
这里是玉女峰后山的一个小山谷，长年人迹罕至。谷中古树参天，绿荫森
森。偶尔从远处传来几声悠扬的鸟语，伴随着阵阵花香，简直让人疑心自己到
了世外桃源。
　　你远远的看见谷中有两间小屋，不过看来已经好久没住过人了。你心里不
禁发起愁来，该怎么办呢？你想离开的话就用(leave)吧。
LONG
	);
	set("exits", ([
		"northdown" : __DIR__"midong",
                 "leave"  :   __DIR__"siguoya",

	]));

	set("outdoors", "华山" );

	setup();
}

void init()
{
	add_action("do_shout","han");
}

int do_shout(string arg)
{
	object ob,me;
   int i, j, times;
	me = this_player();

	if (!me->query_temp("mb")) return 0;

	if ( !arg || arg!= "风老前辈")
	{
		write("你在瞎喊乱叫些什么?\n");
		return 1;
	}

	if (me->is_busy())
	{
		write("你正忙着呢，不能喊叫。\n");
		return 1;
	}

	if (me->is_fighting())
	{
		write("你还是专心打架吧。\n");
		return 1;
	}

	times = (time() - me->query_temp("mb"))/60;

	message_vision(HIY"\n$N运用丹田之气，纵声长啸道:“风老前辈。。。”\n"NOR,me);

        if (!wizardp(me) && times > 190000) 
		{

			me->delete_temp("han");
			me->delete_temp("mb");
			log_file("quest/jiujian",sprintf("%8s%-10s在后山，时间太久，未发生任何情况，福：%d，次：%d。\n",
			me->name(1), "("+capitalize(me->query("id"))+")", me->query("kar"), me->query("mianbi")),me);
			me->move(__DIR__"siguoya");
			tell_object(me, HIR"时间太久了，你觉得索然无趣，又回到了思过崖。\n");
			tell_room(environment(me), me->name() + "从后山走了过来。\n", ({ me }));
			return 1;
		}

		if ( me->query_temp("han") > 4 ) 
		{
			me->delete_temp("han");
			me->delete_temp("mb");
			log_file("quest/jiujian",sprintf("%8s%-10s在后山未发生任何情况，福：%d，次：%d。\n",
			me->name(1), "("+capitalize(me->query("id"))+")", me->query("kar"), me->query("mianbi")),me);
			me->move(__DIR__"siguoya");
			tell_object(me,HIR "你觉得索然无趣，又回到了思过崖。\n");
			tell_room(environment(me), me->name() + "从后山走了过来。\n", ({ me }));
			return 1;
		}

// by lsxk@hsbbs  增加通宝物品提高解9jian的几率。
   if(me->query_temp("sj_credit/quest/hs/jiujian")){

	   me->delete_temp("sj_credit/quest/hs/jiujian");
       i = 15;
	   
   }
   else i = 25;
      
	  if(me->query("m-card-vip")) i =  25;
      if(me->query("y-card-vip")) i =  22;
      if(me->query("buyvip"))     i =  18;

	// Modified by mxzhao 2004/05/01 for 降低难度
   if( random(me->query("kar")) < i || random(20) < 12 )
	{
	// End
		me->add_temp("han", 1);
		me->add_busy(1);
		tell_object(me, "四野寂静无声，唯有空谷回音随风飘散。\n");
		return 1;
	}
	log_file("quest/jiujian",sprintf("%s(%s)在后山遇到田伯光，福：%d，次：%d。\n",
		me->name(1), capitalize(me->query("id")), me->query("kar"), me->query("mianbi")));

	me->delete_temp("han");
	me->delete_temp("mb");

	ob=new(__DIR__"npc/tbg");
	ob->move(this_object());
	j = (int)me->query("max_pot") - 50;

	ob->set_skill("blade",j);
	ob->set_skill("parry",j);
	ob->set_skill("cuff",j);
	ob->set_skill("dodge",j);
	ob->set_skill("tianmo-dao",j);
	ob->set_skill("taizu-quan",j);
	ob->set_skill("force",j);
	ob->set_skill("tianmo-gong",j);
	ob->set_skill("shaolin-shenfa",j);

	ob->map_skill("dodge","shaolin-shenfa");
	ob->map_skill("blade","tianmo-dao");
	ob->map_skill("cuff","taizu-quan");
	ob->map_skill("parry","tianmo-dao");
	ob->map_skill("force","tianmo-gong");
	ob->prepare_skill("cuff","taizu-quan");

	ob->set("combat_exp",(int)me->query("combat_exp")*2);
	ob->set("max_qi", me->query("max_qi")*3/2);
	ob->set("max_neili",me->query("max_neili")*3/2);
	ob->set("neili",(int)me->query("max_neili")*2 - 1); 
	ob->set("eff_jingli", me->query("max_jingli")*2/3);
	message_vision("一条黑影从山后闪出,刀光霍霍，已经将$N笼罩在狂风快刀刀光之下。\n",me);
	ob->kill_ob(me);
	//remove_call_out("confirm");
	call_out("confirm", 30, me);
	return 1;
}

int confirm(object me)
{
	object ob;
	ob=present("tian boguang",this_object());
	if (!me) return 0;
	if (!living(ob))
	{
	  message_vision(HIY"远处似乎有人暗自叹息了一声，你回首观看，却见空山寂寥，人际渺茫。\n"NOR, me);
	  message_vision(HIC"一阵风吹过，似乎人影从$N面前一闪，只见空山寂寥，山风呼啸。\n"NOR, me);

	  message_vision(HIW"田伯光已经被你失手打晕，战力强悍，错失风清扬指点，解密独孤九剑失败！\n"NOR, me);
	  log_file("quest/jiujian",sprintf("%s(%s)在后山遇到田伯光，失手打晕，风清扬暗自离开，解密失败，福：%d，次：%d。\n",
		me->name(1), capitalize(me->query("id")), me->query("kar"), me->query("mianbi")));
	//  destruct(ob);
	  me->move("d/huashan/siguoya");
	  return 0;
	}
	if (!ob)
	{
	  message_vision(HIY"远处似乎有人暗自叹息了一声，你回首观看，却见空山寂寥，人际渺茫。\n"NOR, me);
	  message_vision(HIC"一阵风吹过，似乎人影从$N面前一闪，只见空山寂寥，山风呼啸。\n"NOR, me);

	  message_vision(HIW"田伯光已经被你失手杀死，战力强悍，错失风清扬指点，解密独孤九剑失败！\n"NOR, me);
	  log_file("quest/jiujian",sprintf("%s(%s)在后山遇到田伯光，失手杀死，风清扬暗自离开，解密失败，福：%d，次：%d。\n",
		me->name(1), capitalize(me->query("id")), me->query("kar"), me->query("mianbi")));
	 // destruct(ob);
	  me->move("d/huashan/siguoya");
	  return 0;
	}

	message_vision(CYN"一道青影飘然而落，淡淡道：“我要指点$N几招，难道收拾不了$n这个笨蛋?\n"NOR, me,ob);
	message_vision(CYN"$N先使一招‘白虹贯日’，跟着便使‘有凤来仪’，再使一招‘金雁横空’。\n"
			+"接下来使‘截剑式’……”一口气滔滔不绝的使了三十招招式。\n"NOR,me);
	message_vision(CYN"$n招架不住，飞身向山下逃去。青衣人轻叹一声消失在山后。\n"NOR,me,ob);
	destruct(ob);
	if (!me->query("fengset")){
		write("你得到风清扬的指点，顿感功力大进。\n");
		log_file("quest/jiujian",sprintf("%8s%-10s在打跑田伯光后，得到风清扬的指点，次：%d。\n",
			me->name(1), "("+capitalize(me->query("id"))+")", me->query("mianbi")),me);
		me->add("combat_exp",1600000);
		me->set("fengset",1);
	}
	me->set_temp("met_feng",1);
	return 1;
}

int valid_leave(object me, string dir)
{
	if (me->query("family/family_name") == "华山派"
	 && me->query("fengset") 
	 && dir == "northdown") {
		me->move(__DIR__"siguoya");
		me->delete_temp("mark/steps");
		return notify_fail("你循着风清扬告诉的捷径一下子就来到了思过崖。\n");
	}
	return ::valid_leave(me, dir);
}
