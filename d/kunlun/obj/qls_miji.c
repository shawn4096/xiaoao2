// �������ؼ�
// sohu 

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIC"�������ؼ�"NOR, ({ "qingliang miji", "miji" , "book" }));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һö������֧����۾��������ȵ��ؼ����ؼ��Ƚϳ¾ɣ�������д�ˡ��������������֡�\n");
		set("value", 1);
		set("no_sell", 1);
		set("no_steal", 1);
		set("no_give", 1);
		set("no_drop", 1);
		set("unique", 1);
		set("treasure", 1);

		set("material", "paper");
		set("base_weight", 50);
	}
	setup();
}
