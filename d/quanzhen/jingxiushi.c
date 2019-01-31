#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "静修室");
        set("long", @LONG
这里是全真教弟子静修参悟道情的房间，房间很小，但收
拾的干干净净，桌椅都摆放得整整齐齐，让人一看就心无杂念。
在墙角处放置几个大书架(jia)，上面摆放了各种书籍。
LONG);
        set("exits", ([
                "east" : __DIR__"houshan",
                "south" : __DIR__"diziju",
                "west" : __DIR__"houtang3",
        ]));
        set("objects", ([
                CLASS_D("quanzhen") + "/liuchuxuan" : 1,
        ]));
		set("item_desc", ([
        "jia": CYN"大书架，上面摆放了\n"+
			HIR"天罡正气诀(book)，\n"+
			"丹阳鞭法真解(zhenjie),\n"+
			"全真剑谱(jianpu)，\n"NOR,
        ]) );
		set("book",1);
		set("zhenjie",1);
		set("jianpu",1);
        setup();
}

int valid_leave(object me, string dir)
{
        mapping fam;
        object ob;

        if (! (fam = me->query("family"))
           || fam["family_name"] != "全真教")
        {
                if ((ob = present("liu chuxuan", environment(me)))
                   && living(ob)
                   && dir == "east")
                        return notify_fail(CYN "刘处玄伸手拦住你道：后面是本"
                                           "教祖师清修之地，请止步。\n" NOR);
        }
        return ::valid_leave(me, dir);
}

int init()
{
	add_action("do_get",({"qu","na"}));
}

int do_get(string arg)
{
  object me,ob;
  string arg1,arg2;
  me=this_player();
  if (me->query("family/family_name")!="全真教") return notify_fail("你不是全真教的来此藏书阁作甚？\n");

  if(!arg || sscanf(arg, "%s from %s", arg1, arg2)!=2)
   return notify_fail("命令格式: na(qu) <书本名称> from jia。\n");
  if (arg2!="jia")
     return notify_fail("命令格式: na(qu) <书本名称> from jia。\n");
  if (arg1=="book"&&query("book")<1)
     return notify_fail("书架上《天罡正气诀》这本书已经被人拿走了，待会再来\n");

  if (arg1=="jianpu"&&query("jianpu")<1)
     return notify_fail("书架上《全真剑谱》这本书已经被人拿走了，待会再来\n");
  if (arg1=="zhenjie"&&query("zhenjie")<1)
     return notify_fail("书架上《丹阳鞭法真解》这本书已经被人拿走了，待会再来\n");
   switch (arg1)
   {
          case "book": ob=new("/d/quanzhen/obj/qz_force"); add("book",-1);break;             
          case "zhenjie": ob=new("/d/quanzhen/obj/whip_book"); add("zhenjie",-1);break;   
          case "jianpu": ob=new("/d/quanzhen/obj/qzjf_book");add("jianpu",-1); break;         
          default :
                 return notify_fail("没有这本书。\n");
     }
	// if(present(ob, me) || present(ob, environment(this_object())))
	//	return notify_fail("已经有这样东西了。\n");
     if(ob) ob->move(me);
       message_vision("$N从书架上拿出一本$n。\n",me, ob);  
       return 1;
}
