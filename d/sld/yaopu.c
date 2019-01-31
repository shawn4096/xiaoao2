// yaopu1.c
// ҩ��
inherit ROOM;
#include <ansi.h>

string* pos=({(["id":"northwest","name":"����"]),(["id":"northwest","name":"����"]),
	(["id":"north","name":"����"]),(["id":"south","name":"�Ϸ�"]),
	(["id":"west","name":"����"]),(["id":"east","name":"����"]),
	(["id":"southeast","name":"����"]),(["id":"southwest","name":"����"]),
});
string* pos1=({"northwest","north","northeast","east","southeast","south","southwest","west"}); 

void create()
{
	set("short","ҩ�����");
	set("long",@long
��������������ҩ�ԣ�ԶԶ��ȥ��ҩ�����ư���ͼ���У�ÿ��
ҩ���Ա߲���һ�����ӣ����￿������������,�ʺ�����ҩ�ĳɳ���
�˵�ҩ���˱ǡ�
long);
	set("exits",([
		"south" : __FILE__,
		"north" : __FILE__,
		"west" : __FILE__,
		"east" : __FILE__,
		"southeast" : __FILE__,
		"southwest" : __FILE__,
		"northwest" : __FILE__,
		"northeast" : __FILE__,
		"out" : "/d/sld/zl1",
	]));
	set("no_clean_up",1);
	
	set("outdoors", "������");
	setup();
}	    	
void init()
{
		object me=this_player();
		if (me->query("family/family_name")=="������")
		{        
			message_vision(CYN"Զ����һƬҩ�ԣ�ҩ���˱ǣ����˴�������$N�̲�ס���ñ������ţ�\n"NOR,me);
     		add_action("do_wen", ({"wen","xiu","smell",}));
		}
     	me->delete_temp("yaopu");
		
}
int do_wen()
{
	object me;
	string fx,arg;
	me=this_player();
	fx=pos1[random(sizeof(pos1))];
	if (me->is_busy())
		return notify_fail("������æµ��\n");
	switch (fx)
	{
		case "east":
			//me->set_temp("yaopu/path/");
			arg="����";
			break;
		case "west":
			arg="����";
			break;
		case "north":
			arg="����";
			break;
		case "south":
			arg="�Ϸ�";
			break;
		case "northwest":
			arg="������";
			break;
		case "northeast":
			arg="������";
			break;
		case "southeast":
			arg="���Ϸ�";
			break;
		case "southwest":
			arg="���Ϸ�";
			break;
	}

	tell_object(me,CYN"��о��Ǵ�"HIY+arg+CYN"��������ҩ��!\n"NOR);
	me->set_temp("yaopu/path",fx);
	me->start_busy(1);
	return 1;
}

int valid_leave(object me, string dir)
{
	
	if (dir == me->query_temp("yaopu/path"))
		me->add_temp("mark/lvl",1);
	else me->delete_temp("mark/lvl");
	
	if (me->query_temp("mark/lvl") == 5 )
	{
		me->move(__DIR__"yaopu1");
		me->delete_temp("mark");
		me->delete_temp("yaopu");
		return notify_fail("������ҩ��һ·���ˣ������ߵ���Ƭ���������ֺ��ҩ���С�\n");
	}
	
	return ::valid_leave(me, dir);
}
