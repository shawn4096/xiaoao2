// npc: /d/xingxiu/herdsman.c
// Jay 3/18/96

inherit NPC;
string ask_dizi();
void create()
{
        set_name("��ͯ", ({ "mutong", "kid"}));
        set("gender", "����");
        set("age", 8 + random(5));
        set("long", "һ����ͯ������ʮ��ֻ��\n");
        set("attitude", "friendly");
        set("env/wimpy", 60);
        set("combat_exp", 200);

        set_skill("unarmed", 5);
        set_skill("dodge", 5);
        set_skill("parry", 5);
        set_skill("whip", 5);

        set_temp("apply/attack", 5);
        set_temp("apply/defense", 5);
        set("inquiry", ([

	    "���": (: ask_dizi :),
	
	]));
        setup();
        set("chat_chance", 2);
        set("chat_msg", ({
              "��ͯ���ߵ��µ����ǰ������ɵ���������������˫�ס�\n",
              "��ͯ���췢�ģ��Ҵ���һ��Ҫ����\n",
        }));
        carry_object(BINGQI_D("bian"))->wield();
        carry_object(ARMOR_D("yangao"))->wear();
}

string ask_dizi()
{
	object me=this_player();
	command("say ������ͨ��һֻ��ѣ���û������������ѡ�\n");
	command("say ����Ҫ���͸���ɡ�\n");
	new("d/xingxiu/obj/zhudi")->move(me);
	return "��ͯ�ݸ���һֻ��ѡ�\n";
}


