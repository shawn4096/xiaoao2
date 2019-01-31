// huacong.c
// By River@SJ 98/08/29

#include <ansi.h>
inherit ROOM;

void delete_hexiu(object me, object arg);

void create()
{
	set("short",HIR"红花丛"NOR);
	set("long", @LONG
这丛红花排开来长达数丈，密密层层，奇香扑鼻，但见花丛有如一座大屏
风，红瓣绿枝，煞是好看，四下里树荫垂盖，便似天然结成的一座花房树屋。
四周都是一片清幽，只闻泉声鸟语，杳无人迹，确是个上好的练功所在。
LONG        );

	set("exits", ([
		"west" : __DIR__"guolin4",
		"south" : __DIR__"guolin5",
	]));

	set("outdoors","古墓");

	set("no_fight", 1);
	setup();
}

void init()
{
	object me=this_player();

	add_action("do_hexiu", "hexiu");
	add_action("do_quit", "quit");
	if (me->query_temp("ynxj/hexiusun"))
	{
		if (!present("sun popo",environment(me)))
		{
			new("kungfu/class/gumu/sun")->move(environment(me));
		}
	}
}

int do_hexiu(string arg)
{
	object me = this_player();
	object ob, *inv;
	mapping fam;
	int ynlvl,i;

	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢。\n");
	
	if(!arg)
		return notify_fail("你要与谁和修内功？\n");

	if (!(fam = me->query("family")) || fam["family_name"] != "古墓派")
		return notify_fail("你不是古墓派传人，怎么能练古墓的内功？\n");

	if (me->query("gender") == "无性")
		return notify_fail("你无根无性，阴阳不调，难以领会高深的玉女心经神功。\n");
    
	if (!(ob = present(arg, this_object())))
		return notify_fail("这人现在不在这里！\n");

	if ( me == ob)
		return notify_fail("你想玩双手互搏吗？\n");

	if (!living(ob))
		return notify_fail("你必须先把" + ob->name() + "弄醒。\n");
	

	if( me->query_temp("weapon"))
		return notify_fail("你手中拿着武器，怎么双掌相对，合修玉女心经？\n");

	ynlvl = me->query_skill("yunu-xinjing",1);

	if ( me->query("potential") < 1 )
		return notify_fail("你的潜能消耗光了，暂时无法合修。\n");

	if( userp(ob) && ob->query("potential") < 1)
		return notify_fail( ob->name()+"的潜能消耗光了，暂时无法合修。\n");

	//if ( ob->query_skill("yunu-xinjing", 1) < (ynlvl - 100))
		//return notify_fail(ob->name() +"功夫与你相差太远，无法助你练功！\n");

	if (me->query("jing") < 30 || me->query("qi") < 30)
		return notify_fail("你太累了，还是先休息一会儿吧！\n");

	if (ob->query("jing") < 30 || ob->query("qi") < 30)
		return notify_fail(ob->name()+"太累了，还是先休息一会儿吧！\n");
	//和孙婆婆合修
	if (me->query_temp("ynxj/hexiusun"))
	{
		call_out("hexiu_sun",1,me,ob);
		return 1;
	}
	if (!userp(ob))
		return notify_fail("你只能与玩家和修练功！\n");
	if (me->query_temp("gumu_hexiu")
	 && me->query_temp("gumu_hexiu")!= ob->query("id"))
		return notify_fail("你正欲与别人和修呢！\n");

	inv= all_inventory(me);
	i = sizeof(inv);
	while (i--)
	if( inv[i]->query("equipped") && (! inv[i]->query_autoload() && inv[i]->query("id") != "lingpai"))
		return notify_fail("如果你不除去身上衣衫，练功极有可能会走火入魔。\n"); 

	me->set_temp("gumu_hexiu", ob->query("id"));
	ob->set_temp("gumu_hexiu", me->query("id"));
	tell_object(ob,"红花丛中，"+me->name()+"端坐于你面前，欲与你和修玉女心经。\n");
	tell_object(me,"红花丛中，你端坐于"+ob->name()+"面前，欲与其和修玉女心经。\n");

	if ( ob->query_temp("gumu_hexiu") 
	 && ob->query_temp("gumu_hexiu") != me->query("id"))
		return notify_fail(ob->name()+"没有要与你和修练功的意思！\n");

	if (!ob->query_temp("gumu_hexiu")) return 1;
	message_vision(HIW"\n$N左臂透过花丛，与$n右掌相抵，二人各处花丛一边，解开衣衫，修习起来。\n"NOR,me, ob);
	me->start_busy(15);
	ob->start_busy(15);
	call_out("delete_hexiu", 2+random(3), me, ob);
	return 1;
}

void delete_hexiu(object me, object ob)
{
	if ( !me || !ob) return;

	me->receive_damage("jing", 20+random(10),"走火入魔而");
	me->receive_damage("qi",  20+random(5),"走火入魔而");
	me->add("potential", -1);
	if ( me->query_skill("yunu-xinjing", 1) < 220 )
		me->improve_skill("yunu-xinjing", me->query_int()*2);
	
//	if (!me->query_temp("ynxj/hexiusun"))
	 //  me->add("combat_exp",1000+random(500));
	me->start_busy(1);
	me->delete_temp("gumu_hexiu");

	ob->receive_damage("jing", 20+random(10),"走火入魔而");
	ob->receive_damage("qi",  20+random(5),"走火入魔而");
	ob->add("potential", -1);
	//if ( ob->query_skill("yunu-xinjing", 1) < 130 )
    //ob->improve_skill("yunu-xinjing", ob->query_int()*( 8 + random(20))); 
	//if (!me->query_temp("ynxj/hexiusun"))
		//ob->add("combat_exp",1000+random(500));
	ob->start_busy(1);
	ob->delete_temp("gumu_hexiu");
	if (me->query("quest/gumu/ynxj/pass"))
	{
		message_vision(HIR"你已经洞彻了玉女心经第一段奥秘，合修对你来说已经没有什么意义。\n"NOR,me);
		return;
	}
	if (time()-me->query("quest/gumu/ynxj/time")>86400) 
	{
		//一天之内才有机会
		//write("eeeee");
		message_vision(HIY"$N和$n双掌相抵，劲气汹涌，对于内功的运行略有心得，眼前忽然出现一片豁然开朗的感觉。\n"NOR,me,ob);
      
		remove_call_out("lingwu_ynxj");
		call_out("lingwu_ynxj",1,me,ob);
	}
	
	message_vision(HIR"\n良久后，$N和$n受到感应，立时运功为助，全身热气蒸腾，收获颇丰。\n\n"NOR,me,ob);
	if (userp(ob)) message_vision(HIC"\n$N和$n感觉自己获得一定的经验值奖励。\n"NOR,me,ob);
	me->delete_temp("ynxj/hexiusun");
	return;
}

int do_quit()
{
	write("这里不准退出！\n");
	return 1;
}

int valid_leave(object me, string dir)
{
	me->delete_temp("gumu_hexiu");
	return ::valid_leave(me, dir);
}

int hexiu_sun(object me,object ob)
{
	object sun;	
	object *inv;
	int ynlvl,i;
	/*if (!objectp(sun=present("sun popo",find_object("d/gumu/rukou.c"))))
		if (!present("sun popo",environment(me)))
		{
			sun=new("kungfu/class/gumu/sun");
			sun->move(environment(me));
		}*/
	
	message_vision(HIY"\n$N左右看了看，此处无人，于是喊道，“孙婆婆~~~~~！！！！”\n"NOR,me);
	message_vision(HIC"\n\n孙婆婆喋喋怪笑一声道，小丫头，老身来了！\n"NOR,me);	
	

	if( me->query_temp("weapon"))
		return notify_fail("你手中拿着武器，怎么双掌相对，合修玉女心经？\n");
	ynlvl = me->query_skill("yunu-xinjing",1);

	if ( me->query("potential") < 1 )
		return notify_fail("你的潜能消耗光了，暂时无法合修。\n");

	//if( ob->query("potential") < 1)
		//return notify_fail( ob->name()+"的潜能消耗光了，暂时无法合修。\n");

//	if ( ob->query_skill("yunu-xinjing", 1) < (ynlvl - 100))
//		return notify_fail(ob->name() +"功夫与你相差太远，无法助你练功！\n");

	if (me->query("jing") < 30 || me->query("qi") < 30)
		return notify_fail("你太累了，还是先休息一会儿吧！\n");

	//if (ob->query("jing") < 30 || ob->query("qi") < 30)
	//	return notify_fail(ob->name()+"太累了，还是先休息一会儿吧！\n");
	if (me->query_temp("gumu_hexiu")
	 && me->query_temp("gumu_hexiu")!= ob->query("id"))
		return notify_fail("你正欲与别人和修呢！\n");

	inv= all_inventory(me);
	i = sizeof(inv);
	//while (i--)
	//if( inv[i]->query("equipped") && (! inv[i]->query_autoload() && inv[i]->query("id") != "lingpai"))
		//return notify_fail("如果你不除去身上衣衫，练功极有可能会走火入魔。\n"); 
	
	
	me->set_temp("gumu_hexiu", ob->query("id"));
	ob->set_temp("gumu_hexiu",me->query("id"));
	tell_object(ob,"红花丛中，"+me->query("name")+"端坐于你面前，欲与你和修玉女心经。\n");
	tell_object(me,"红花丛中，你端坐于"+ob->query("name")+"面前，欲与其和修玉女心经。\n");

	if ( ob->query_temp("gumu_hexiu") 
	 && ob->query_temp("gumu_hexiu") != me->query("id"))
		return notify_fail(ob->name()+"没有要与你和修练功的意思！\n");

	if (!ob->query_temp("gumu_hexiu")) return 1;
	message_vision(HIW"\n$N左臂透过花丛，与$n右掌相抵，二人各处花丛一边，解开衣衫，修习起来。\n"NOR,me, ob);
	me->start_busy(10);
	ob->start_busy(10);
	call_out("delete_hexiu", 2+random(3), me, ob);
	return 1;

}

//huacong 参悟

int lingwu_ynxj(object me,object ob)
{
	int i,j;
	object sun;
	if (me->query("quest/gumu/ynxj/pass"))
	{
		return notify_fail("你已经解开了谜题，还瞎参悟什么？");
	}
	message_vision(HIM"这丛红花排开来长达数丈，密密层层，奇香扑鼻,静夜之中，花香更是浓郁。$N和$n隔著花丛各自用功，\n"HIY"$N与$n全身热气蒸腾，将那花香一薰，更是芬芳馥郁。\n"NOR,me,ob);
	
	if(me->query_temp("canwu_hexiu")<(10+random(5)))
    { 
	  me->add_temp("canwu_hexiu",1);
      if(random(2)) tell_object(me,HIG"\n这玉女心经单数行功是「阴进」，双数为「阳退」。你练的是「阳退」功夫，随时可以休止，\n"NOR);
             else tell_object(me,HIY"\n对方练的「阴进」却须一气呵成，中途不能微有顿挫。突然间，你似乎抓到了什么...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  //remove_call_out("lingwu_ynxj");
	  call_out("lingwu_ynxj",3+random(3), me,ob);
	  return 1;
	}
   else
   {  
	  me->delete_temp("canwu_hexiu");
      if (userp(ob)) j=15;
      else j=20;

	  
      if(me->query("m-card-vip")) j =  j-1;
      if(me->query("y-card-vip")) j =  j-3;
      if(me->query("buyvip"))     j =  j-5;
	  if (me->query("gender")=="女性")
	     j=j-1;
	 
	  i= random(j);

     if(i<3
		 && random(me->query_int())>40
		 && random(me->query("kar"))>20)
	 {
		tell_object(me,HIM"\n你按照古墓中玉女心经精要的指点，对阴进阳退之道又有所了解，玉女心经的奥妙似乎有些得心应手。\n"NOR);
        tell_object(me, HIG"突然间，你只觉得内息起自“尾闾穴”，随后自腰俞、阳关、命门、悬枢\n"+
"诸穴，一路沿着脊椎上升，走的都是背上督任各个要穴，然后是脊中、中枢、筋缩、至阳、\n"+
"灵台、神道、身柱、陶道、大椎、痖门、风府、脑户、强间、后顶、而至顶门的“百会穴”。\n"NOR);
		tell_object(me,HIY"\n你历尽千辛万苦，终于得偿所愿，将玉女心经初有小成。\n"NOR);
       	
		me->improve_skill("yunu-xinjing", 15+random(10));
		
		me->set("quest/gumu/ynxj/pass",1);
		me->set("quest/gumu/ynxj/time",time());
		me->start_busy(1);

		log_file("quest/ynxjronghe", sprintf("%8s(%8s) 失败%d次后，领悟玉女心经的融合绝技第一段。i取值：%d|经验：%d。\n", me->query("name"),me->query("id"), me->query("quest/gumu/ynxj/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/gumu/ynxj/fail",1);
		
		tell_object(me,HBYEL+HIW"\n你和对方演练了玉女心经融合的奥秘，始终全然不得要领。\n\n"NOR);
		tell_object(me,HIG"\n解密玉女心经第一段失败。再接再厉！\n\n"NOR);
		me->start_busy(1);
		me->add("quest/gumu/ynxj/fail",1);
		me->set("quest/gumu/ynxj/time",time());
//		write("222");

		if (objectp(sun=present("sun popo",environment(me))))
			destruct(sun);	
		log_file("quest/ynxjronghe", sprintf("%8s(%8s) 玉女心经第一段解密失败%d次。i取值：%d|经验：%d。\n", me->query("name"),me->query("id"),me->query("quest/gumu/ynxj/fail"),i,me->query("combat_exp")) );
	  }
	return 1; 
  }

}
