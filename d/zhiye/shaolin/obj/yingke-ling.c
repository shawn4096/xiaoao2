inherit ITEM;

void create()
{
	set_name( "ӭ����", ({ "yingke ling", "ling", "yingke" }) );
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
                set("long", "����һ����������ӭ�ͷ����õ����ơ�\n");
		set("value", 100);
		set("material", "bamboo");
	}
	setup();
}

void init()
{
        call_out("dest", 900);
}

void dest()
{
	destruct(this_object());
}
