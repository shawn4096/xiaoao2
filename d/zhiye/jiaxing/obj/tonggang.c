#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY"铜缸"NOR, ({ "tong gang","tonggang","gang"}) );
        set_weight(30000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "个");
				set("value", 250000);
                set("material", "iron");
				set("armor_prop/armor", 6);
			   // set("weight",10000);
				set("water",100);

        }
        setup();
}
int init()
{
	add_action("do_ju","ju");

}

int do_ju(string arg)
{
	object me,gang;
	me=this_player();

	if (!arg||arg!="铜缸")
	{
		return notify_fail("你要举什么？\n");
	}
	
	gang=present("tong gang",environment(this_object()));
	if (!gang) return notify_fail("此地没有铜缸,你要举起什么来？\n");
	
	message_vision(HIR"$N俯下身来，怒喝一声，运劲于臂，将那个盛满水的大铜缸举起来!\n然后长啸一声，在众人惊愕的神情中，飘然而去！\n"NOR,me);

	gang->move(me);

	me->set_temp("quest/射雕英雄传/江南七怪/jugang",1);
	return 1;
}