// chongyangling.c
inherit ITEM;

void create()
{
	set_name( "重阳令", ({ "chongyang ling", "ling", "iron" }) );
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "块");
        set("long", "这是一块重阳真人昔日所做铁铸令牌，见令如见掌门。\n");
		set("value", 100);
		set("no_steal",1);
		//set("");
		set("material", "iron");
	}
	setup();
}

void init()
{
        call_out("dest", 1800);
}

void dest()
{
	destruct(this_object());
}
