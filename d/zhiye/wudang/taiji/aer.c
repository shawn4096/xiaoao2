#include <ansi.h>
inherit NPC;
void create()
{
        set_name("����", ({ "a er", "aer", "er" }) );
        set("title", HBWHT"�����԰˷�"NOR);
        set("long", "�������������е������������϶������ݣ�����԰���ͷ���Ļ����͵أ�\nͺ�ò�ʣ���ͷ��������̫��Ѩ���˽�ȥ�����ݰ��\n");
        set("gender", "����" );
        set("age", 54);
		set("con",25);
        set("dex",25);
        set("unique", 1);
        set("per", 20);
        set("no_get", 1);
        set("max_qi", 30000);
        set("max_jing", 7000);
        set("neili", 38000);
        set("max_neili", 20000);
        set("jiali", 200);
        set("combat_exp", 12500000);
        set("eff_jingli", 7000);

        set_skill("force", 480);
        set_skill("hunyuan-yiqi", 480);
        set_skill("dodge", 480);
        set_skill("shaolin-shenfa", 480);
        set_skill("finger", 500);
        set_skill("jingang-zhi", 520);
        set_skill("parry", 480);
        set_skill("literate", 150);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "jingang-zhi");
        map_skill("parry", "jingang-zhi");
        prepare_skill("finger", "jingang-zhi");
    	set("chat_chance", 60);
    	set("chat_msg_combat", ({
        	(: perform_action, "finger.fumo" :),
        	(: perform_action, "finger.jingangzhi" :),
        	(: perform_action, "finger.lianhuan" :),
        }));
        setup();
        carry_object("/d/wudang/obj/white-robe")->wear();
}
