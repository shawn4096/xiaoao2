// lianzi-wan.c

inherit ITEM;

void setup()
{}

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name("������", ({"lianzi wan", "lianzi", "wan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�����������������ҩ��\n");
		set("value", 5000);
	}
	setup();
}

int do_eat(string arg)
{
	if (!id(arg))
		return notify_fail("��Ҫ��ʲôҩ��\n");
	if ((int)this_player()->query("eff_qi") == 
	    (int)this_player()->query("max_qi"))
		return notify_fail("�����ڲ���Ҫ�������衣\n");
	else {
		this_player()->receive_curing("qi", 50);
		message_vision("$N����һ�������裬��ɫ�������ö��ˡ�\n", this_player());
		destruct(this_object());
		return 1;
	}
}
