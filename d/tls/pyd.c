//���ƶ�
//cool@SJ,990605

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short",HIY"���ƶ�"NOR);
	set("long",@LONG
ԭ�������Ƹ�����һ��Сɽ����һ�������ž�������Ϣ�Ĺر��ˣ���ǰ��
һ����Ȼ�γɵ�ʯ�������Ķ�����һ��������ʯ�죬�����������������
��Χ�ֲ��ż���ɽ����������Щ��Ӷ���͸����
LONG
	);
         
	set("exits", ([
		"out" : __DIR__"lsy",
		"north" : __DIR__"shangyang",
		"northup" : __DIR__"shaoshang",
		"northwest" : __DIR__"guanchong",
		"northeast" : __DIR__"zhongchong",
		"southwest" : __DIR__"shaoze",
		"southeast" : __DIR__"shaochong",
	]));
	set("no_fight",1);
	setup();
}
void init()
{
	object me;
	me=this_player();
	
	message_vision(HIC"����Ŀ��ٳ���ͻȻ�ȵ�����ֻ����ϰһ�������Ҫ����ˣ���\n"NOR, me);

	if (!me->query("liumai_pass") 
		|| me->query("family/family_name") != "������"
		|| (me->query_skill("liumai-shenjian") && !me->query("quest/tls/yyz/liumai/pass")))
		//|| (me->query("liumai-shenjian")&&!me->query("quest/tls/lmsj/ciqu/pass")))
	{
		message_vision(HIY"���ٳ���ͻȻ�������Ȼû��ͨ�����Ծͽ����ˣ���ʱ��ŭ���ȵ������ҳ�������\n"NOR, me);

		me->move("/d/tls/lsy");	
		return ;
	}

}

int valid_leave(object me, string dir)
{
		
	me=this_player();

	//if (!me->query("quest/tls/liumai/pass"))
	if (!me->query("liumai_pass") )
	{
		me->move("d/tls/road");
		me->unconscious();
		return notify_fail("���ٳ��ϴ��һ��������������ô�����ģ����һ�ɴ����������˳�ȥ����\n");
	}
	if ( dir != "out" 
		 && !me->query("quest/tls/yyz/liumai/pass")
		 && me->query_skill("liumai-shenjian",1)>29)
	{
		message_vision(HIC"\n\n���ٴ�ʦ�����⺰��������̫�಻�ã���ֻ��ѡ��һ����������߻���ħ����\n"NOR,me);
		return notify_fail("\n���ٴ�ʦ��ζ���˵����Ŀǰ��������ֻ�ж����޵�ȫ���������񽣡�\n");
	}
	
	return ::valid_leave(me, dir);
	
	
}
