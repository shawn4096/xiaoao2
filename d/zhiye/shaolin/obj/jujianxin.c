inherit ITEM;

void create()
{
	set_name( "举荐信", ({ "jujian xin", "xin", "letter" }) );
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "封");
                set("long", "这是一封弟子入山修炼的推荐信。\n");
		set("value", 100);
		set("material", "paper");
	}
	setup();
}

void dest()
{
	destruct(this_object());
}
