// NPC: /d/huashan/npc/gao.c
// Date: Look 99/03/25
// Lklv modify 2001.10.18

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
        set_name("������",({"gao laozhe","gao"}));
        set("title","��ɽ�ɵ�ʮ��������");
        set("long", "������ڽ��������ӵĻ�ɽ�ɸ����ߡ�");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 32);
        set("int", 32);
        set("con", 32);
        set("dex", 32);

        set("max_qi",3500);
        set("qi", 3500);
        set("max_jing", 2500);
        set("jing",2500);
        set("eff_jingli", 3000);
        set("max_neili", 4000);
        set("neili", 4000);
        set("jiali", 50);
        set("combat_exp", 3900000);
        set("score", 30000);

	set_skill("dodge",  450);
	set_skill("blade",  450);
	set_skill("force",  450);
	set_skill("cuff", 450);
	set_skill("sword", 450);
        set_skill("parry",  450);
	set_skill("poyu-quan", 450);
	set_skill("literate",190);
	set_skill("huashan-qigong", 450);
	set_skill("fanliangyi-dao", 450);
	set_skill("huashan-jianfa",  450);
	set_skill("huashan-shenfa",  450);
	set_skill("zhengqi-jue", 220);

        map_skill("dodge", "huashan-shenfa");
        map_skill("sword", "huashan-jianfa");
        map_skill("force","huashan-qigong");
        map_skill("parry","fanliangyi-dao");
        map_skill("cuff", "poyu-quan");
        prepare_skill("cuff","poyu-quan");
	set("chat_chance_combat",70);
	set("chat_msg_combat", ({
		(: perform_action, "blade.sanqingfeng" :),
		//(: perform_action, "sword.feijian" :),
		//(: perform_action, "sword.junzi" :),
		//(: perform_action, "sword.kuaijian" :),
		//(: perform_action, "sword.lianhuan" :),
		//(: perform_action, "sword.sanqing" :),
	}));
        create_family("��ɽ��",12,"����");

        setup();
	carry_object(ARMOR_D("cloth"))->wear();
	carry_object(BINGQI_D("blade"))->wield();
}
/*
void attempt_apprentice(object ob)
{
        mapping fam;
        if ( mapp(fam=ob->query("family"))
         && (string)fam["family_name"] != "��ɽ��"
         && (int)ob->query("is/huashan")==1||!ob->query("quest/huashan") ) {
		message_vision(CYN "$N���������ɽ�ɵ���ͽ��������ʲô ������\n"NOR, ob );
		command("slap "+ob->query("id"));
		return;
	}
	if ( ob->query("fengset")) {
		command("say �㲻���Ѿ����˷�����Ϊʦ��ô��");
		return;
	}
	if ((int)ob->query("shen") <= 2000000) {
		command("say �һ�ɽ�����������������ɣ��Ե���Ҫ���ϡ�");
		command("say �ڵ��з��治��2M��" + RANK_D->query_respect(ob)+"�Ƿ����ò�����");
		return;
        }
        if ((int)ob->query("max_pot") < 450) {
		command("say " + RANK_D->query_respect(ob)+"���ڲ���Ҫ����ָ������ȥ��������ʦ��ѧ��ȥ�ɡ�");
		return;
        }
        if( (int)ob->query_skill("huashan-qigong", 1) < 350 ) {
		command("say ��Ļ�ɽ������δ�����,�����ҿɲ�������Ϊͽ��\n");
		return;
        }
        if( (int)ob->query_skill("force") < 350 ) {
		command("say ����ڹ���δ�����,�����ҿɲ�������Ϊͽ��\n");
		return;
        }
        command("say �ðɣ��Ҿ���������,���ҪΪ���ǻ�ɽ����������");
        command("recruit " + ob->query("id"));
}
*/