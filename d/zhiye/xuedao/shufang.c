// nroad6.c
// Modified by Java Apr.27 1998

#include <ansi.h>
inherit ROOM;
int do_fankan(string arg);
int do_search(string arg);

void create()
{
        set("short","藏书洞");
        set("long",@LONG
血刀老祖征战各方，邀斗天下武林高手，打败后抢夺对方秘籍
然后全部陈列在此，供门中弟子参悟。南面的书架(shujia)上摆放
了一排排的修炼书籍。北面的正中央挂了一副佛祖的挂像，法相庄
严，佛像下摆放了一堆堆的佛家经典秘籍，其中大部分均为密宗的
欢喜宗(huanxi)经典著作。
LONG );
        set("exits",([
                "south"   : __DIR__"lingwushi",
                //"southup" : __DIR__"nroad5",
        ]));
        set("objects",([				
				"/d/xuedao/npc/laoseng" : 1,
        ]));
		set("item_desc", ([
			"huanxi" : YEL"案子上摆放着一排排的欢喜宗修炼的佛教典籍,可以通过fankan来阅读。\n"NOR,
			"shujia" : CYN"书架上放着一堆堆的修炼秘籍，大部分为各门派的刀谱和怪异武功，\n"
						"可以通过search来寻找部分秘籍。 \n"
					   HIM"	欢喜宗经典著作(huanxi)，\n"+
						   HIC"	血刀经心法精要(forcebook)，\n"+
						   HIR "	基本刀法入门(bladebook),\n"+
						    HIY"	基本掌法精要(strikebook),\n"NOR,
		]));

        //	set("no_clean_up", 0);
        set("strikebook", 1);
		set("bladebook",1);
		set("huanxi",1);
		set("forcebook",1);

        setup();
        replace_program(ROOM);
}
void init()
{	
	add_action("do_search","search");
	add_action("do_fankan","fankan");

}

//入门的欢喜禅修炼 60
int do_fankan(string arg)
{
	object ob;
	mapping fam;
	object me=this_player();
	if (!arg||arg!="huanxi")
	{
		return notify_fail("你要翻看什么东西？\n");
	}

	if(me->query("potential", 1) < 1)
		return notify_fail("你的潜能没了，不能再继续修习了\n");
	if(!(fam = me->query("family")) || fam["family_name"] != "血刀门")
		return notify_fail("你不是血刀门弟子，如何能领悟这种另类的欢喜禅要诀？\n");
	if(me->query("gender") == "无性")
		return notify_fail("你无根无性，阴阳不调，难以领会高深的血刀门经典著作。\n");
	if(me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着哪！\n");
	if(me->query("jing") < 25 )
		return notify_fail("你的精神很差, 该先去休息一会. \n");           
	if(me->query_skill("force", 1) < 20)
		return notify_fail("你的基本内功太低,不足20级，无法研习更高级的内功。\n");        
	//if(me->query_skill("xuedao-jing", 1) < 100)
		//return notify_fail("你的血刀经内功等级太低，无法领悟欢喜典籍的文字。\n");
    if(me->query_skill("huanxi-chan", 1) > 60)
		return notify_fail("你的欢喜禅精进一层，可以尝试学习高级的血刀门经典著作了了。\n");
	
	write(MAG"你开始研习案子上的欢喜禅经典著作，深有心得。\n"NOR);
	me->receive_damage("jing", 100 / (int)me->query("int"));
    me->improve_skill("huanxi-chan", me->query_int() + random(me->query_int() * 5 / 3));

	me->add("potential", -1);
	return 1;

}

int do_search(string arg)
{
	object ob;
	mapping fam;
	string arg1,arg2;
	object me=this_player();

	  if(!arg || sscanf(arg, "%s from %s", arg1, arg2)!=2)
		 return notify_fail("命令格式: search <书本名称> from shujia。\n");
	  
	  if (arg2!="shujia")
		 return notify_fail("命令格式: search <书本名称> from shujia。\n");
	  
	  if (arg1=="huanxi" && this_object()->query("huanxi",1)<1)
		 return notify_fail("书架上《两情相悦合欢经》这本书已经被人拿走了，待会再来\n");
	  if (arg1=="forcebook" && this_object()->query("forcebook",1)<1)
		 return notify_fail("书架上《血刀经心法精要》这本书已经被人拿走了，待会再来\n");

	  if (arg1=="bladebook"&& this_object()->query("bladebook")<1)
		 return notify_fail("书架上《基本刀法入门》这本书已经被人拿走了，待会再来\n");
	  if (arg1=="strikebook"&& this_object()->query("strikebook")<1)
		 return notify_fail("书架上《基本掌法精要》这本书已经被人拿走了，待会再来\n");

	   switch (arg1)
	   {
			  case "huanxi": 
				  ob=new("/d/xuedao/obj/huanxi_book1"); 
				  this_object()->add("huanxi",-1);
				 // ob->move(me);
				  break;             
			  case "strikebook": 
				  ob=new("/d/xuedao/obj/strike_book"); 
				  this_object()->add("strikebook",-1);
				 // ob->move(me);
				  break;   
			  case "bladebook": 
				  ob=new("/d/xuedao/obj/blade_rumen"); 
				  this_object()->add("bladebook",-1); 
				//  ob->move(me);
				  break;         
			  case "forcebook": 
				  ob=new("/d/xuedao/obj/xdj_book2"); 
				  this_object()->add("forcebook",-1); 
				//  ob->move(me);
				  break;   
			  default :
				  return notify_fail("没有这本书。\n");
		 }
	   if(present(ob, me) || present(ob, environment(me)))
		return notify_fail("你身上或地上已经有这样东西了。\n");

    // ob->move(me);
	   if(ob) ob->move(me);
			message_vision("$N从书架上拿出一本$n。\n",me, ob);  
       return 1; 

}