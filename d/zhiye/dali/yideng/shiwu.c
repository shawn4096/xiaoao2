// By River 2002.6.3

inherit ROOM;
#include <ansi.h>
int check_yideng(object me);

void create()
{
	set("short", "ʯ������");
	set("long", @LONG
����С���ϵ���һ¯̴�㣬������������һ��ɮ�ˡ�ֻ�������ֲ�ɮ�ۣ�
���������İ�ü���۽Ǵ�����������Ŀ���飬ü����������࣬��һ��Ӻ�ݸ�
������ɫ��ȴ��һ����֪��
LONG
	);
	set("exits", ([
		"east" : __DIR__"xiangfang",
		"south" : __DIR__"zhulin",
	]));

	set("objects", ([
		__DIR__"npc/yideng" : 1,
	]));

	setup();
}

void init()
{
	object me=this_player();
	if (me->query_temp("nqg/askyingok"))
    {
		tell_object(me,HIY"\n\n\n��ոյ����ſڣ�ȴ����������ĸ��˺�������ʦ����Σ�գ�\n"NOR);
		tell_object(me,HIY"\n\n\n����һ���Ϻ�����ϥ�����Ķ������з�ţ��������и�����\n"NOR);
       // call_out("check_yideng",1,me);
		return;
	}

}
/*
int check_yideng(object me)
{

	
	object yideng;
	yideng=present("yideng dashi",environment(me));
    if (!objectp(yideng)) 
    {
		return notify_fail("�ǳ��ź���һ�ƴ�ʦΪ������ɱ��\n");
    }
	
	if (!objectp(me)) return 0;
	
	if (me->query_temp("yideng/kill_yideng", 1)&& !objectp(yideng))
	{
		me->add("shen",-random(2000000));
		me->set("tls/killyideng",1);

		message_vision(HIC"\n\n$N����һ��������������ͺ¿�������������°ܽ���\n"NOR, me);

		message_vision(HIC"\n\n$N��������˵��Ҫ��ͷ֮�£������Ǹõ��˻�ȥ�����ý����ʱ���ˡ�\n"NOR, me);
        return 1;
	}
	
	return 1;

}*/