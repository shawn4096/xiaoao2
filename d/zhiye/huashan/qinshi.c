// Room: /d/huashan/qinshi.c
// Date: Look 99/03/25
#include <ansi.h>

inherit ROOM;
int do_move(string arg);
int do_push(string arg);
int do_tiao(string arg);

void create()
{
        set("short", "����");
        set("long", @LONG
����������Ⱥ�����ң�����Ⱥ�ڽ������˳ơ����ӽ���������Ϊһ�������ţ�
����������ȴ���õĺܼ򵥡�����һ�Ŵ�����ֻ���ӣ�ǽ�����Ż�ױ̨��ֻ�п�ǽ
һ�ź�ľ����(desk)���Ե��������ɡ��ݱ�������һ�ȴ��������������ɽ���Х
������������ԼԼ����Ӱ�����ӳ��
LONG
        );
        set("exits", ([ 
		"north" : __DIR__"houtang",
	]));
        set ("item_desc", ([
                "desk" : 
"����һ�źܽ�ʵ�ĺ�ľ�����������ϰ��ż�ֻ�Ǻ��ʣ�ĥ��һ���ī��\n"
"����һ��δ�õİ�ֽ��\n",
	            "����" : 
"����һ��С�������������������ͱڣ��վ��쳣��\n"
"�������ϼ�ɽ���Х�������������ҡ�\n"
        ])  ) ;

	 set("objects",([
	 	__DIR__"obj/shengzi" : 1,
	 ]));

        set("no_clean_up", 0);
	    set("indoors", "��ɽ" );

        set("coor/x",80);
        set("coor/y",-40);
        set("coor/z",80);
        setup();
}

void init()
{
    add_action("do_push","tui");
    add_action("do_tiao","jump");
	add_action("do_move","move");
	add_action("do_tiao","tiao");
}

int do_move(string arg)
{
	object me=this_player();
	object xin;
	if (!arg || arg!="����")
	{
		return notify_fail("��Ҫ�ƶ�ʲô������\n");	
	}
	if (!me->query_temp("zyy/askyue"))
	{
		return notify_fail("�������ŵ�˽�˷��䣬������Ұᶯʲô������\n");	
	}
	xin=new("d/huashan/obj/ziyin_book");
	xin->move(this_player());	
	message_vision(YEL"$N�ڻ�ɽ�������ѵ�һ����ɽ�ؼ���\n"NOR,me);
	return 1;

}

int do_push(string arg)
{
   object me=this_player();
   if (!arg ||arg !="����")
     return notify_fail("��Ҫ��ʲô��\n");
   if (me->query_temp("hs/tuichuang"))
   {
	   return notify_fail("���Ѿ��ƿ�������\n");
   }
   if (me->query_temp("weapon"))
      return notify_fail("�����ձ���������ƴ�����\n");
   message_vision(HIC"\n\n$N�����ƿ�������ɽ�����������ڴ��������̲�ס���˸�������\n"NOR,me);
   message_vision(HIG"\n\n$N������ȥ�����¼�Ϊ�������£���ɲ⣬��Լ�ɼ�������һ��ǧ�����ɳ������±��ϡ�\n"NOR,me);


   //�����ν����ּ������⵽���١���
   me->set_temp("hs/tuichuang",1);
   return 1;
}
int do_tiao(string arg)
{
   object me=this_player();
   if (!arg ||arg !="ǧ������") return 0;

   if (me->query("quest/pxj/super2/pass")) 
   {
       	me->set("title",HIM"Ⱥа����"NOR);
		me->set("mytitle/quest/pxjtitle",HIM"Ⱥа����"NOR);
		return notify_fail("���Ѿ������˱�а�����������Ķ���ʲô��\n");

   }
   if (!me->query_temp("hs/tuichuang"))
      return notify_fail("�����Դ��򴰻���ײ��\n");
   if (me->query_skill("dodge",1)<350) 
      return notify_fail("����Ṧ̫�ͣ�����350������ˤ����\n");
	
   message_vision(HIC"\n\n$N����һ����Ӵ����з���Ծ��,���䵽�����������ϡ�\n"NOR,me);
   me->move("/d/huashan/song1");
   me->delete_temp("hs/tuichuang");
   me->set_temp("hs/tiaochuang",1);
   return 1;
}