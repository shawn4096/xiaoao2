#include <ansi.h>

inherit ITEM;

void create()
{
      set_name(CYN "��������" NOR, ({ "xuantie lingp","ling pai","ling" }));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ö");
		set("long", CYN"����һö"HIG"л�̿�"CYN"��ɢ�������ϵ��������ơ�\n"NOR);
		set("value", 0);
		set("treasure",1);
		set("unique",1);
		set("material", "xuantie");
				set("no_drop",1);
		set("no_cun",1);
		set("no_get",1);

    }
	setup();
}
