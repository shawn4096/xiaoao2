// item: fire.c
// by snowman@SJ , 01/05/1999.

inherit FIRE_ITEM;
void create()
{
        set_name("火折", ({"fire", "huozhe"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
         set("long", "这是一支用于引火的火折，到了黑暗的地方就用(use)得着了。\n");
                set("unit", "支");
                set("value", 100);
                set("light/time", 15);
        }
        setup();
}


