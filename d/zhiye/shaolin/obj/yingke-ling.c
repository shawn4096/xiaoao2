inherit ITEM;

void create()
{
	set_name( "迎客令", ({ "yingke ling", "ling", "yingke" }) );
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "块");
                set("long", "这是一块用于少林迎客服务用的令牌。\n");
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
