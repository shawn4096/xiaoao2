inherit ITEM;

void create()
{
	set_name( "�ټ���", ({ "jujian xin", "xin", "letter" }) );
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
                set("long", "����һ�������ɽ�������Ƽ��š�\n");
		set("value", 100);
		set("material", "paper");
	}
	setup();
}

void dest()
{
	destruct(this_object());
}
