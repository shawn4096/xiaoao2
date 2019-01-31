// Room: /d/shaolin/banruo6.c
// Date: YZC 96/01/19

inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "����������");
	set("long", @LONG
����һ�伫Ϊ��ª���������������ܣ����˼�������⣬���ڿյ�����
���������������İڷ��ż��������ҷ��ڵĻƲ����ţ���λ�뷢���׵�
��ɮ�������������Ŀ�붨�������Ǳ���ʮ���޺��������еĵط������پ�
���书�����ڴ������
LONG
	);

	set("exits", ([
		"south" : __DIR__"banruo5",
		"north" : __DIR__"banruo7",
	]));

	set("objects",([
		CLASS_D("shaolin") + "/cheng-xin2" : 1,
		"d/shaolin/obj/muchai" : 1,
	]));
	set("coor/x",110);
	set("coor/y",280);
	set("coor/z",110);
	setup();
}
void init()
{
	object me=this_player();
	add_action("do_pi","pi");

}

int do_pi(string arg)
{
	object muchai,weapon;
	int i,j;
	object me=this_player();
	weapon=me->query_temp("weapon");
	if (!arg||arg!="ľ��")
		return notify_fail("�˵ؿ��ޣ���Ҫ��ʲô��\n");
	if (!me->query_temp("rmdf/askchengxin"))
	{
		return notify_fail("�˵����������°����õ���Ҫ�أ���Ͳ��������¾���׷ɱ��ô��\n");

	}
	if (!present("mu chai",environment(me)))
	{
		return notify_fail("�˵�û��ľ����Ҫ��ʲô��\n");
	}
	if (!weapon||weapon->query("id")!="mu dao")
	{
		return notify_fail("��ϰȼľ������Ҫľ��������ϰ��\n");
	}
	if( time()- me->query("quest/sl/rmdf/ranmu/time")<86400)
		return notify_fail("�������ڽ������Ƕ�����������̫Ƶ����\n");

	message_vision(HIY"$N�˹�ȫ�����һ�����������е�ľ����������ϵ�ľ��\n"NOR,me);
	
	i = 20;
	if(me->query("m-card-vip")) i =  18;
	if(me->query("y-card-vip")) i =  15;
	if(me->query("buyvip"))     i =  10;
	i=random(i);

	j=random(me->query("kar"));

	if( i<4 
		&& me->query("kar")<31
		&& j >=26 ) 
	{
		tell_object(me,HIY"\n��һ���������پ�����ľ��һ�����ȣ���ȼľ�����İ��������ĵá�\n"NOR);
		tell_object(me,HIG"\n���֮�䣬������ͨ�������Ͼ�����ͨ��������ȼľ������Ҫּ��\n"NOR);
		tell_object(me,HIR"��ϲ����ȼľ�����ɹ�!\n"NOR);
		me->set("quest/sl/rmdf/ranmu/pass",1);
		log_file("quest/rmdfranmu", sprintf("%8s(%8s) ʧ��%d�κ�ѧ��ȼľ����,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/sl/rmdf/ranmu/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		me->delete_temp("rmdf");
		return 1;
		
	}	
   else
	{
		log_file("quest/rmdfranmu", sprintf("%8s(%8s) ����ȼľ����ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/sl/rmdf/ranmu/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"����ζ���ŵ�ָ�㣬���Ƕ�ȼľ�İ���ȫȻ����Ҫ�졣\n\n"NOR);
		me->add("quest/sl/rmdf/ranmu/fail",1);
		me->set("quest/sl/rmdf/ranmu/time",time());
		me->start_busy(1+random(3));
		me->delete_temp("ranmu");
		tell_object(me,"�ǳ��ź�,����ȼľʧ��"+me->query("quest/sl/rmdf/ranmu/fail")+"�Ρ�\n");
		return 1;
	}

}


