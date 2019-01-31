// Room: /d/huashan/shahong.c
// Date: Look 99/03/25
#include <ansi.h>

inherit ROOM;
int do_jump(string arg);
int do_kang(string arg);
int do_pai(string arg);


void create()
{
        set("short", "ɽ���ٲ�");
        set("long", @LONG
ת��һ��ɽϿ��ˮ�����������ֻ��ɽ���һ�������Ƶ��ٲ���к���£�
����һ��Ϫ������ʤ�������ļ��쳣��ˮ��Ю����֦ʯ�飬ת�۱����ò�֪
ȥ��Ϫ��(river)��������һ���ʯ(stone)��ˮ���ɽ����Ĺ�ˮ�����ɣ�
εΪ��ۡ���ɽ���Ƶ����ң��������о��⣬���Ǳ������ĺá�
LONG
        );
       set("exits", ([ 
        "southwest" : __DIR__"shaluo",
	]));
	set("item_desc", ([
        "river" : "ɽˮ���ٲ�����Ϫ���������쳣�ļ���\n",
        "stone" : "һ��޴����ʯ���������ر�ɽ���͸����ɣ��߼���ˮ����ʱ�й�һЩʯͷ��������\n",
	]));
       set("outdoors", "��ɽ" );

       set("coor/x",60);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}

void init()
{
	add_action("do_jump","jump");
	add_action("do_pai","pai");
	add_action("do_kang","kangheng");

}
int do_jump(string arg)
{
		object me=this_player();
		if (arg=="back")
		{
			message_vision(HIC"$N����һ�ݣ��ص����ߡ�\n"NOR,me);
			me->delete_temp("shpb");
			return 1;
		}
		if (me->query_skill("dodge",1)<50)
			return notify_fail("ˮ���߼�����Ļ����Ṧ̫��������50��������ȥ��\n");
		if (!arg || arg!="river")
			return notify_fail("��Ҫ���Ķ�����\n");
		message_vision(HIC"$N�����Ṧ������һ�ݣ�Խ��ˮ����������ʯ֮�ϡ�\n"NOR,me);
		tell_object(me,HIC"���ǽ��ĵ�һ�����ʯ����վ�������ˮ���߼������Գ�������������Ϊ��\n"NOR);
		tell_object(me,HIC"���Գ���Ծ��ˮ�����ڹ��������߼���ˮ������kangheng river����\n"NOR);
		tell_object(me,HIC"Ҳ���Գ����������ķ�����Ư������ɽʯ����pai stone����\n"NOR);
		tell_object(me,HIC"���ذ���ָ��Ϊ����jump back����\n"NOR);
		me->set_temp("shpb/yue",1);
		return 1;
}

int do_kang(string arg)
{
		object me=this_player();
		if (!me->query_temp("shpb/yue"))
				return notify_fail("ˮ���߼�������뽭��̫Զ���޷�������ˮ����\n");
        if (me->is_busy())
			 return notify_fail("������æµ�С�\n");
		if (me->query_skill("force",1)<50)
			return notify_fail("ˮ���߼�����Ļ����ڹ�̫��������50��������ȥ��\n");
		if (!arg || arg!="river")
			return notify_fail("��Ҫ�����￹�⣿��\n");

		message_vision(HIC"$N����һ����������ʯ������ˮ�У���סһ�������߼���ˮ�����⡣\n"NOR,me);
		
		me->add_busy(1+random(1));
		
		me->receive_damage("jingli",10+random(10),"Ī�������");
		if (me->query_skill("force",1)<120)
		{		
			message_vision(YEL"\n$N��ˮ���ĳ�ˢ�������ܿ����ģ�������ȴ�õ�������������\n"NOR,me);
			me->improve_skill("force",(int)me->query_int());

		}else {

			message_vision(CYN"$N��ˮ���������ߣ��������,��Ȼ�����ڹ���Ϊ�Ѿ��о�����˿�������ˡ�\n"NOR,me);

		}
		return 1;

}
int do_pai(string arg)
{
		object me=this_player();
		if (!me->query_temp("shpb/yue"))
				return notify_fail("ˮ���߼�������뽭��̫Զ���޷���ˮ�е���ʯ��\n");
        if (me->is_busy())
			 return notify_fail("������æµ�С�\n");
		if (me->query_skill("strike",1)<50)
			return notify_fail("��Ļ����Ʒ�̫��������50���Ĺ�ȥ��������������\n");
		if (!arg || arg!="stone")
			return notify_fail("��Ҫ��ʲô����\n");

		message_vision(HIY"������ˮ���Ĵ����£�һ��Сʯͷ������$N������\n"NOR,me);
		me->add_busy(1+random(1));
		message_vision(HIG"$N���������ƣ������ǿ�Сʯͷ��stone����һ���ķɣ�\n"NOR,me);
		if (random(me->query("neili"))<200)
		{
			message_vision(RED"���κ�Ȼ����һ��Ƚϴ���ʯͷ����ʱ���������������������������Ϊ���ʯ�����ˡ�\n"NOR,me);
			me->receive_damage("qi",20+random(10),"Ī�������");
		}
		me->receive_damage("jingli",15+random(10),"Ī�������");
		if (me->query_skill("strike",1)<120)
		{		
			
			me->improve_skill("strike",(int)me->query_int());

		}else {

			message_vision(HIC"$N��ˮ���������ߣ��������,��Ȼ�����ڹ���Ϊ�Ѿ��о�����˿�������ˡ�\n"NOR,me);

		}
		return 1;

}


int valid_leave(object me, string dir)
{
	
	if( dir=="southwest" && me->query_temp("shpb/yue") )
		return notify_fail(CYN"��λ"+RANK_D->query_respect(me)+"������Ϫˮ�����ء�\n"NOR);
	return ::valid_leave(me, dir);
}