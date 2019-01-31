// box.c ������

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(RED "������" NOR, ({ "laji box", "xiang", "box" }) );
	set_weight(3000);
	set_max_encumbrance(500000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
                set("long", "����һ��·�߳����������䣬ר����������������\n");
		set("value", 1000);
		set("material", "wood");
		set("no_get",1);
		set("no_drop",1);
		set("amount",300000);
	}
	setup();
}

int is_container() { return 1; }

void init()
{

	add_action("do_put", "put");
}

int do_put(string arg)
{
	object me, obj;
	string item, target; 
	int amount;

	me = this_player();

	if( !arg || sscanf(arg, "%s in %s", item, target)!=2 
	||  sscanf(item, "%d %s", amount, item)!=2
	||  !objectp(obj = present(item, me)) )
		return 0;
		
		obj = find_object(item);
		if (!obj) obj = present(target, this_object());
	    if (!obj) obj = present(target, environment(this_object()));
		message_vision( sprintf(HIY "$N��һ%s%s����%s��\n" NOR,
		obj->query("unit"), obj->name(), 
		this_object()->name()),me );
		
	    destruct(obj);
		destruct(item);
	 return 1;
}
