#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
������ȫ��̵��Ӿ��޲������ķ��䣬�����С������
ʰ�ĸɸɾ��������ζ��ڷŵ��������룬����һ�����������
��ǽ�Ǵ����ü��������(jia)������ڷ��˸����鼮��
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
        "jia": CYN"����ܣ�����ڷ���\n"+
			HIR"���������(book)��\n"+
			"�����޷����(zhenjie),\n"+
			"ȫ�潣��(jianpu)��\n"NOR,
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
           || fam["family_name"] != "ȫ���")
        {
                if ((ob = present("liu chuxuan", environment(me)))
                   && living(ob)
                   && dir == "east")
                        return notify_fail(CYN "������������ס����������Ǳ�"
                                           "����ʦ����֮�أ���ֹ����\n" NOR);
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
  if (me->query("family/family_name")!="ȫ���") return notify_fail("�㲻��ȫ��̵����˲����������\n");

  if(!arg || sscanf(arg, "%s from %s", arg1, arg2)!=2)
   return notify_fail("�����ʽ: na(qu) <�鱾����> from jia��\n");
  if (arg2!="jia")
     return notify_fail("�����ʽ: na(qu) <�鱾����> from jia��\n");
  if (arg1=="book"&&query("book")<1)
     return notify_fail("����ϡ�������������Ȿ���Ѿ����������ˣ���������\n");

  if (arg1=="jianpu"&&query("jianpu")<1)
     return notify_fail("����ϡ�ȫ�潣�ס��Ȿ���Ѿ����������ˣ���������\n");
  if (arg1=="zhenjie"&&query("zhenjie")<1)
     return notify_fail("����ϡ������޷���⡷�Ȿ���Ѿ����������ˣ���������\n");
   switch (arg1)
   {
          case "book": ob=new("/d/quanzhen/obj/qz_force"); add("book",-1);break;             
          case "zhenjie": ob=new("/d/quanzhen/obj/whip_book"); add("zhenjie",-1);break;   
          case "jianpu": ob=new("/d/quanzhen/obj/qzjf_book");add("jianpu",-1); break;         
          default :
                 return notify_fail("û���Ȿ�顣\n");
     }
	// if(present(ob, me) || present(ob, environment(this_object())))
	//	return notify_fail("�Ѿ������������ˡ�\n");
     if(ob) ob->move(me);
       message_vision("$N��������ó�һ��$n��\n",me, ob);  
       return 1;
}
