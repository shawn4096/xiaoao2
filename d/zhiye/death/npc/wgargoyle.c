// gargoyle.c

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("���޳�", ({ "bai wuchang", "bai", "wuchang" }) );
        set("long",
                "���޳����ų�������ͷ�����㣬���׵����Ͽ������κ�ϲŭ���֡�\n");
        set("attitude", "peaceful");
        set("chat_chance", 2);
        set("chat_msg", ({
                "���޳�����һ����������������������������ע��������ʱ�򣬵�����һ�ۡ�\n",
                "���޳��ѳ�������ͷ��������������������Լ��ְ��ֳ�����ָ��\n"
        }) );
        set("age", 217);
        set("combat_exp", 20000);
        set("max_jing", 900);
        set("max_qi", 900);
        set_skill("dodge", 40);
        set_skill("unarmed", 40);
        setup();
}

