inherit ROOM;

#include "zhongjun.h"

void create()
{
	set("short", "�о�ԯ��");
	set("long", @LONG
�����ɹŴ�����о�ԯ�ţ�Զ�����������ŽǺ�ս����˻��֮��������ʿ
������Χ������ȥ������ս��һ��������
LONG);
	set("exits", ([
        	"north" : __DIR__"zhongjun2",
        ]));
	set("objects", ([
        	__DIR__"npc/yuanbing-shiwei" : 1,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	object ob;
	ob = present("zhongjun shiwei",environment(this_player()) );
	if(ob)
	    	return notify_fail("�о�����һ�ѽ�����ס�������ܣ�\n" );
        return ::valid_leave(me, dir);
}