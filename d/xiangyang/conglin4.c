// Room: /d/xiangyang/conglin4.c
#include <ansi.h>

inherit ROOM;
void create()
{
	set("short", "ɽ��յ�");
	set("long", @LONG
������ɽ´�ϵ�һ��յأ�·�Ե��Ӳݺ���ľ�����������ˡ�·����һ��
����ľ�����С�ݣ�С�ݵ��ſ���һЩ��������Ϣ��һЩ��������������·��
�����ϡ�����������һƬ���֣�ʷ�����ֵ������������Ҫץʲô���
LONG	);
        set("xyjob", 1);
		set("exits", ([
        	"eastdown" : __DIR__"conglin3",
        	"northwest" : "/d/gumu/xuantie/xiaolu4",

        ]));
        set("objects",([
              "/clone/npc/shijiqiang" : 1,
              "/clone/npc/shibowei" : 1,
              "/clone/npc/shimengjie" : 1,
              "/clone/npc/shishugang" : 1,
              "/clone/npc/shizhongmeng" : 1,
        ]));

        set("outdoors", "����");
		setup();
}
int init()
{
	//ask yang �󴥷�
	object me=this_player();
	if (me->query_temp("quest/shendiao/��ѩ�����/askanran"))
	{
		add_action("do_heal","heal");
	}
}

int do_heal(string arg)
{
	object me=this_player();
	object shi,shi1,linghu;
	if (!objectp(shi=present("shi shugang",this_object())))
	{
		tell_object(me,"��Ҫ���˵Ķ����ڣ�\n");
		return 1;
	}
	shi1=present("shi bowei",this_object());
	
	if (!arg||arg!="ʷ���")
	{
		return notify_fail("��ҪΪ˭���ˣ�\n");
	}
	if (!me->query_temp("quest/shendiao/��ѩ�����/askgui"))
	{
		message_vision(CYN"���ʷ�����Ե�޹ʣ�ƾɶΪ�����ˣ�\n"NOR,me);
		return 1;
	}

	if (objectp(linghu=present("jiuwei linghu",me)) && me->query_temp("anran/findfox"))
	{
		message_vision(HIG"$N�ӻ��н���β�����������Ҹ��󣬴Ӻ����Ȳ�����һ��Ѫ������ʷ������\n"NOR,me);
		message_vision(HIW"\nʷ������$N��ʾ��ϸ�л��\n"NOR,me);

		message_vision(HBYEL+HIR"\n\n$N��˼���ã������п���ǧ���⵱�еĶ�Թ���Ȼ����˵ĸ��Ӻ����ϣ�\n"NOR,me);
		message_vision(HBBLU+HIW"\n\n��ϲ�㣬����ˡ�������¡���ѩ�����ƪ�½����ݣ�"NOR,me);

		me->set_temp("quest/shendiao/��ѩ�����/healover",1);		
		me->delete_temp("quest/shendiao/��ѩ�����");
		destruct(linghu);
		me->set("quest/shendiao/��ѩ�����/healover",1);		
		return 1;
	}
	message_vision(HIC"$N˵�������Ҵ������������Ķ��õ����������Ϣ����æ������������Ϊʷ����������˵����\n"NOR,me);
	
	message_vision(HIC"\n\n$N��ϥ������˫������ʷ���յĺ󱳣��˹����ˡ�\n"NOR,me);
	message_vision(HIR"\n$Nͷ�������뵣�ʷ����۵��³�һ����Ѫ��\n"NOR,me);
	shi1->shi_say1();
	
	call_out("come_on",2+random(2),me);
	//me->set_temp("anran/askheal",1);
	shi->clear_condition("neishang");
	return 1;
}

int come_on(object me)
{
	message_vision(HIC"$N˵����������Ȼ��ת����Ȼʷ����˵Ҫ�о�β�����Ѫ����֪�����Ķ����Եõ���\n"NOR,me);
	message_vision(HIC"ʷ����˵�������������ԣ����������������֮�������ֹ����ޡ���\n"NOR,me);
	message_vision(HIC"ʷ����˵�����������ֵܼ������Ⱥ�׽����Σ��������伫Ϊ�ƻ�����Ϊ���ӵ�����\n"NOR,me);
	message_vision(HIC"ʷ����˵������������ȥ׽��һ��ҪС�Ľ��������޼�Ϊ��������\n"NOR,me);
	message_vision(HIC"ʷ����˵��������һ�����ǲ���ס���ޣ���ȴ��һ�������õĸ�������ֹ����\n"NOR,me);
	message_vision(HIC"ʷ����˵���������Ǹ����ý�������������˽�˻���֮�ֻ�ǲ�֪��١���\n"NOR,me);
	me->set_temp("quest/shendiao/��ѩ�����/askheal",1);
	return 1;
}
