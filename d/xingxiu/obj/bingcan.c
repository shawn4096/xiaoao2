// by sohu
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW"��ɽ����"NOR, ({"tianshan bingcan", "bingcan", "can"}));
        set("unit", "ֻ");
		set("unique", 1);
		set("poison", 100);
        set("treasure",1);
        set("long", WHT"��ϳ洿������΢����ɫ����Ѱ���϶�����һ�����࣬����һ����򾣬����͸��ֱ��ˮ����\n"NOR);
        set("value", 2000000);
        setup();
}

