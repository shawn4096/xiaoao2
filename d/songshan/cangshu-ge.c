// Room: /u/swl/songshan/csshi.c
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "藏书阁");
	set("long", @LONG
嵩山派的藏书阁，书架上放满了嵩山各种武功书籍、心法，由于嵩
山弟子众多，书有时也会供不应求。墙边竖立一排书架(shujia)，书架
摆放了各种武功秘籍。
LONG);
	set("exits", ([
            "south" : __DIR__"yushu-lou",
        ]));
	set("item_desc", ([
        "shujia": "大书架，上面摆放了\n"+
			CYN"嵩阳心诀(xinfa)，\n"+
			"嵩山鞭法精要(jingyao),\n"+
			"嵩山剑法残篇(canpian)，\n"NOR,
        ]) );
		set("xinfa",1);
		set("jingyao",1);
		set("canpian",1);

	setup();
}

int init()
{
	add_action("do_get",({"qu","na"}));
	add_action("do_search",({"find","search"}));
}

int do_get(string arg)
{
  object me,ob;
  string arg1,arg2;
  me=this_player();
  if (me->query("family/family_name")!="嵩山派") return notify_fail("你不是嵩山派的来此藏书阁作甚？\n");
 
  if(!arg || sscanf(arg, "%s from %s", arg1, arg2)!=2)
   return notify_fail("命令格式: na(qu) <书本名称> from shujia。\n");
  if (arg2!="shujia")
     return notify_fail("命令格式: na(qu) <书本名称> from shujia。\n");
  if (query("xinfa")<1)
     return notify_fail("书架上这本书已经被人拿走了，待会再来\n");

  if (query("jingyao")<1)
     return notify_fail("书架上这本书已经被人拿走了，待会再来\n");
  if (query("canpian")<1)
     return notify_fail("书架上这本书已经被人拿走了，待会再来\n");
   switch (arg1)
   {
          case "xinfa": ob=new("/d/songshan/obj/songyangjue"); add("xinfa",-1);break;             
          case "jingyao": ob=new("/d/songshan/obj/whip_book"); add("jingyao",-1);break;   
          case "canpian": ob=new("/d/songshan/obj/ssjf_book"); add("canpian",-1); break;         
          default :
                 return notify_fail("没有这本书。\n");
     }
	// if(present(ob, me) || present(ob, environment(this_object())))
	//	return notify_fail("已经有这样东西了。\n");
     if(ob) ob->move(me);
       message_vision("$N从书架上拿出一本$n。\n",me, ob);  
       return 1; 
}

int do_search(string arg)
{
	object me=this_player();
	object book;
	if (!arg || arg !="shujia")
	{
		return notify_fail("你要乱翻什么东西？\n");
	}
	if (!me->query("quest/ss/dichuan"))
	{
		return notify_fail("你不是嵩山嫡传弟子，是翻不出什么东西的？\n");
	}
	book=new("d/songshan/obj/songyangjue2");
	book->move(me);
	message_vision(HIC"\n$N从书房中搜到一本嵩阳心法下卷，急忙揣入怀中。\n"NOR,me);
	return 1;

}
