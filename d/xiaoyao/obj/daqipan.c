// qipan.c ����

inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIC"��ʯ����"NOR, ({ "yushi qipan", "qipan", "qi pan"}));
	set_weight(500);
	set("no_get",1);
	set("no_drop",1);
	set("no_steal",1);
	//set();
	set_max_encumbrance(10000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ������Ĵ���ʯͷ���������类����ƽ��һ�㡣\n�����ݺύ��̻���һ���޴�����̣�\n��������˺ڰ���ɫ����,�ʽ���״̬��\n");
		set("value", 500);
		set("no_steal", 1);

	}
}

//int is_container() { return 1; }

