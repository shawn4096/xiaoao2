// caoshangfei.c

//#include <armor.h>
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL"�˶ν��ڹ��ؼ�"NOR, ({ "baduanjin miji", "book", "shu"}));
        set_weight(2000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",
                        "����һ������Ѱ�����ڹ��ؼ�--���˶ν���,��˵���Ի�ɽ����ԯ��\n");
                set("value", 500);
				set("unique",1);
				set("no_drop", "��ô���������ؼ�����ɲ������ⶪ����\n");
                set("no_get", "�������������˵ı�������˯����Ҫ����ͷ�棬���޷���ȡ��\n");
                set("no_give", "��ô���������ؼ�����ɲ���������ˣ�\n");
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