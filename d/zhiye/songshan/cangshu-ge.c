// Room: /u/swl/songshan/csshi.c
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
��ɽ�ɵĲ��������Ϸ�������ɽ�����书�鼮���ķ���������
ɽ�����ڶ࣬����ʱҲ�ṩ��Ӧ��ǽ������һ�����(shujia)�����
�ڷ��˸����书�ؼ���
LONG);
	set("exits", ([
            "south" : __DIR__"yushu-lou",
        ]));
	set("item_desc", ([
        "shujia": "����ܣ�����ڷ���\n"+
			CYN"�����ľ�(xinfa)��\n"+
			"��ɽ�޷���Ҫ(jingyao),\n"+
			"��ɽ������ƪ(canpian)��\n"NOR,
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
  if (me->query("family/family_name")!="��ɽ��") return notify_fail("�㲻����ɽ�ɵ����˲����������\n");
 
  if(!arg || sscanf(arg, "%s from %s", arg1, arg2)!=2)
   return notify_fail("�����ʽ: na(qu) <�鱾����> from shujia��\n");
  if (arg2!="shujia")
     return notify_fail("�����ʽ: na(qu) <�鱾����> from shujia��\n");
  if (query("xinfa")<1)
     return notify_fail("������Ȿ���Ѿ����������ˣ���������\n");

  if (query("jingyao")<1)
     return notify_fail("������Ȿ���Ѿ����������ˣ���������\n");
  if (query("canpian")<1)
     return notify_fail("������Ȿ���Ѿ����������ˣ���������\n");
   switch (arg1)
   {
          case "xinfa": ob=new("/d/songshan/obj/songyangjue"); add("xinfa",-1);break;             
          case "jingyao": ob=new("/d/songshan/obj/whip_book"); add("jingyao",-1);break;   
          case "canpian": ob=new("/d/songshan/obj/ssjf_book"); add("canpian",-1); break;         
          default :
                 return notify_fail("û���Ȿ�顣\n");
     }
	// if(present(ob, me) || present(ob, environment(this_object())))
	//	return notify_fail("�Ѿ������������ˡ�\n");
     if(ob) ob->move(me);
       message_vision("$N��������ó�һ��$n��\n",me, ob);  
       return 1; 
}

int do_search(string arg)
{
	object me=this_player();
	object book;
	if (!arg || arg !="shujia")
	{
		return notify_fail("��Ҫ�ҷ�ʲô������\n");
	}
	if (!me->query("quest/ss/dichuan"))
	{
		return notify_fail("�㲻����ɽ�մ����ӣ��Ƿ�����ʲô�����ģ�\n");
	}
	book=new("d/songshan/obj/songyangjue2");
	book->move(me);
	message_vision(HIC"\n$N���鷿���ѵ�һ�������ķ��¾���æ���뻳�С�\n"NOR,me);
	return 1;

}
