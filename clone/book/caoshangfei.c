// caoshangfei.c

//#include <armor.h>
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC"草上飞秘籍"NOR, ({ "caoshangfei", "book", "shu"}));
        set_weight(2000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        "这是一本武林寻常的轻功秘籍--“草上飞”。\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name": "caoshang-fei",      // name of the skill
                        "exp_required": 500,  // minimum combat experience required
                        "jing_cost":    10,     // jing cost every time study this
                        "difficulty":   10,     // the base int to learn this skill
                        "max_skill":    220,      // the maximum level you can learn
                ]) );
        }
}