inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "�鷿");
	set("long", @LONG
�������鷿����ǽһ�Ŵ���ܣ��ڷ��źܶ���鼮��������ʥ���������
����ų��ԡ�ʥ������������һֱ����Ϊ�٣���������ѧ�����ա�һ������ȥ��
�ƺ��й��ڲ������巽����顣
LONG
	);
	set("exits", ([
		"south" : __DIR__"lang",
		"west"  : __DIR__"shilu1",
	]));
	set("objects",([
              "d/kunlun/obj/string-book1" : 1,
	
				"d/kunlun/obj/string-book2" : 1,
				"kungfu/class/kunlun/kubai" : 1,

		]));
	set("qls_miji",10);//ֻ��һ�����ܲ������Ժ��ڲ�����������޷���
	setup();
}
int init()
{
	add_action("do_find","find");
	add_action("do_find","search");

}
int do_find(string arg)
{
	object me,obj;
	me=this_player();
	if (!arg||arg!="���")
	{
		return notify_fail("��Ҫ��Ѱʲô��\n");
	}
	if (me->is_busy())
	{
		return notify_fail("����æ���ң����������صأ��ĸ������������\n");
	}
	if (me->query_temp("qlsmiji"))
	{
		return notify_fail("���Ѿ��õ��ؼ���\n");
	}
	if (this_object()->query("qls_miji")<1)
	{
		return notify_fail("�ؼ��Ѿ�Ϊ�������ã�����������\n");

	}
	if (me->query("quest/kl/qls/pass"))
	{
		message_vision(HIY"$N������������������ʼ������ϲ�����Ѱ������Ѱ���Ǳ��������Ⱦ��������ؼ���\n"NOR,me);
		if (random(me->query("kar"))>26)
		{
			obj=new("d/kunlun/obj/qls_miji.c");
			obj->set("owner",me->query("id"));
			obj->move(me);
			me->set_temp("qlsmiji",1);
			this_object()->add("qls_miji",-1);
			message_vision(HIY"$N�������ͻȻ����һ���������Ⱦ��������ؼ���\n"NOR,me);
		}
		me->add_busy(1+random(3));

	}
	return 1;

}