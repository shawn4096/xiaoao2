// /u/beyond/hangzhou/jingcisi.c ������
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",HIW"������"NOR);
        set("long", @LONG
��������ǰ���У���������м�Ĵ��۱�����Ϊ׳�ۡ����۱����
�����㣬��ɫ�������ݶ����ر��Եľ�����ΰ�����ȵ������ڲ���ĺ���л�
�������ﶯ�������������ʮ��֮һ���������ӡ���������
LONG
);
	set("objects",([
			__DIR__"npc/you1" : 2,
			__DIR__"npc/kumu" : 1,
			
	]));
        set("exits", ([
			"southeast" : __DIR__"yuhuang",
			"northwest" : __DIR__"hubian1",
		]));
        set("coor/x",110);
	    set("coor/y",-360);
	    set("coor/z",0);
	    setup();
}

int init()
{
	object me;
	me=this_player();
	if (me->query_temp("quest/���Ӣ�۴�/�����߹�/jingcisi"))
	{
		
		message_vision(HIR"��ս��ž����������ƺ���Ů�������������˺��ǲ���Ը��˵����������������ǵ��˵Ķ��֡�\n"NOR,me);
		message_vision(HIC"\n����Ͼ����ҵ�ֶ���������������һ�⣬��ȥ���˻���������ʦ�ܽ�ľ��ʦ��������ʱ�����㣬��һ��Ҳ�ã�\n"NOR,me);
		me->set_temp("quest/���Ӣ�۴�/�����߹�/findkumu",1);
		
		me->set("quest/���Ӣ�۴�/�����߹�/findkumu",1);

		me->delete_temp("quest/���Ӣ�۴�/�����߹�/jingcisi");
	}

}
