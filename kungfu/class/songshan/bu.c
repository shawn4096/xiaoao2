// bu.c ��ɽ�ɵ��������� ����
// Creat by Lklv 2001.10.18

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("����", ({ "bu chen", "bu", "chen" }));
        set("nickname", WHT"��ͷ����"NOR);
        set("long", "����һ����ͷ�׷������ߡ�\n");
        set("gender", "����");
        set("unique", 1);
        set("age", 45);
        set("per", 20);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 26);
        set("int", 26);
        set("con", 26);
        set("dex", 27);
        set("unique", 1);

        set("max_qi", 13000);
        set("max_jing", 4000);
        set("eff_jingli", 4000);
        set("jiali", 120);
        set("combat_exp", 4600000);
        set("eff_neili", 14000);
        set("shen", -150000);
		set_skill("songyang-jue", 150);

		set_skill("literate", 100);
		set_skill("force", 350);
		set_skill("parry", 350);
		set_skill("blade", 350);
		set_skill("dodge", 350);
		set_skill("hand", 350);
		set_skill("zhongyuefeng", 350);
		set_skill("songyang-shou", 350);
		set_skill("hanbing-zhenqi", 350);
		set_skill("fenshui-daofa", 350);

		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("parry", "fenshui-daofa");
		map_skill("blade", "fenshui-daofa");

		prepare_skill("hand", "songyang-shou");

		create_family("��ɽ��", 3, "����");
		set("class", "songshan");
		set("chat_chance_combat", 10);
		set("chat_msg_combat", ({
			(: perform_action, "blade.fenshui" :),
			(: perform_action, "hand.junji" :),
			(: exert_function, "juhan" :),
		}));
		set("inquiry", ([
			"��ɽ��" : "������ɽ������������֮�ף�\n",
			"��������" : "������������������֮�������޴󣬿������֡��䵱���⡣\n",
			"������" : "���������ǵ������ˣ�������ɲ⡣\n",
		]) );
			setup();
			carry_object(ARMOR_D("changpao1"))->wear();
			carry_object(BINGQI_D("blade"))->wield();
}
#include "app3.h";

