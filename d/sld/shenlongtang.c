// shenlongtang.c ������
// by sohu
//�ϴ�ס�ĵط�

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
���������̵������ã��������Ŵ����Σ������������Ű�ʣ�����
������ʹ���ڴ��������£�����ǽ��������ǲ����Խ���˵صġ�
LONG
	);
	set("exits", ([
		"east" : __DIR__"dt",
	]));
	set("objects", ([
		//CLASS_D("sld")+"/hongantong" : 1,
		CLASS_D("sld")+"/shoutoutuo" : 1,
	]));
	setup();
}
/*
void init()
{
	object *inv, me = this_player();

	if( !(me->query("family/family_name") == "������" ||
		me->query("sg/spy")) )
	{
		inv = all_inventory(this_object());
		for(int i = 0; i < sizeof(inv); i++ )
			if( (inv[i]->query("family/family_name") == "������" ||
				inv[i]->query("sg/spy")) && living(inv[i]) )
				inv[i]->kill_ob(me);
		me->start_busy(1);
	}
}
*/