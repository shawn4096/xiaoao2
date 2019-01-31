// caoshangfei.c

//#include <armor.h>
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL"八段锦内功秘籍"NOR, ({ "baduanjin miji", "book", "shu"}));
        set_weight(2000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        "这是一本武林寻常的内功秘籍--“八段锦”,据说传自华山神剑轩辕。\n");
                set("value", 500);
				set("unique",1);
				set("no_drop", "这么珍贵的武林秘籍，你可不能随意丢弃！\n");
                set("no_get", "这样东西是那人的宝贝，连睡觉都要当枕头垫，你无法拿取！\n");
                set("no_give", "这么珍贵的武林秘籍，你可不能随意给人！\n");
                set("treasure", 1);
                set("unique", 1);

                set("material", "paper");
                set("skill", ([
                        "name": "baduan-jin",      // name of the skill
                        "exp_required": 150000,  // minimum combatexperience required
                        "jing_cost":    30,     // jing cost every time study this
                        "difficulty":   30,     // the base int to learn this skill
                        "max_skill":    220,      // the maximum level you can learn
                ]) );
        }
}