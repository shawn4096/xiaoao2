// tonggui-jianpu.c
//同归剑法剑谱
// by sohu@xojh

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name( "同归剑谱", ({ "tonggui jianpu", "jianpu", "book"  }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "这是一册全真七子所编著的同归剑法精要，乃是全真弟子对付强敌时所用剑法招式。\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name": "tonggui-jian",       // name of the skill
                        "exp_required": 100000,      // minimum combat experience required
                        "jing_cost": 20,        // jing cost every time study this
                        "difficulty":   20,     // the base int to learn this skill
                        "max_skill":    100,     // the maximum level you can learn
                ]) );
        }
}
