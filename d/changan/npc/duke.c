// Write By Yanyang@SJ 2001.9.27
// NPC: /d/changan/duke.c

inherit NPC;

void create()
{
        set_name("�Ŀ�", ({"du ke", "ke" }) );
        set("gender", "����" );
        set("age", 35);
        set("long", "���Ǹ�������̫�õĶĿͣ���������������ۣ�\n");

        set_temp("apply/attack", 25);
        set_temp("apply/defense", 25);
        set_skill("unarmed", 30);
        set_skill("dodge", 30);
        set_skill("parry", 30);
        set("combat_exp", 2000);
        set("str", 25);
        set("dex", 20);
        set("con", 15);
        set("int", 15);
        set("attitude","heroism");
        setup();

        set("chat_chance", 5);
        set("chat_msg", ({
                "�ĿͲ�����������´������㡣\n",
                "�ĿͲ��������Χ����ת��תȥ��\n",
        }) );
        carry_object(ARMOR_D("cloth"))->wear();
        add_money("coin", 100);
}