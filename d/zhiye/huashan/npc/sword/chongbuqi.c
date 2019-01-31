// NPC: /d/huashan/npc/cong_bq.c
// Date: Look 99/03/25
// Modify by Lklv 2001.10.18

inherit NPC;
#include <ansi.h>
void create()
{
        set_name("�Ӳ���",({"cong buqi", "cong", "buqi" }));
        set("title","��ɽ�ɵ�ʮ�������ڵ���");
        set("nickname","�񽣿�");
        set("long", "һ�������������о�С�ˣ�һ˫�ָ���ִ�\n");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("no_quest",1);

        set("max_qi",12500);
        set("qi", 12500);
        set("max_jing", 4400);
        set("jing",4400);
        set("eff_jingli", 4700);
        set("jingli", 4700);
        set("max_neili", 13500);
        set("neili", 13500);
        set("jiali", 200);
        set("combat_exp", 6400000);
        set("score", 30000);

        set_skill("zhengqi-jue",  200);
        set_skill("sword",  450);
        set_skill("dodge",  380);
        set_skill("force",  380);
        set_skill("parry",  380);
        set_skill("huashan-qigong", 300);
        set_skill("huashan-jianfa",  450);
        set_skill("huashan-shenfa",  380);

        map_skill("dodge", "huashan-shenfa");
        map_skill("force","huashan-qigong");
        map_skill("sword","huashan-jianfa");
        map_skill("parry","huashan-jianfa");

        prepare_skill("strike","hunyuan-zhang");

        set("chat_chance_combat",80);
	    set("chat_msg_combat", ({
		(: perform_action, "sword.lianhuan" :),
		(: perform_action, "sword.kuaijian" :),
		(: perform_action, "sword.fengyi" :),
			(: exert_function, "yujianshi" :),
			(: exert_function, "juli" :),
	}));

        create_family("��ɽ��",13,"����");

	setup();
	carry_object(BINGQI_D("sword/sword"))->wield();
	carry_object(ARMOR_D("armor/cloth"))->wear();
}
void attempt_apprentice(object ob)
{
        mapping fam;
        if (mapp(fam=ob->query("family")) && (string)fam["family_name"] != "��ɽ��"  && (int)ob->query("is/huashan")==1 ) {
                message_vision(CYN "$N���������ɽ�ɵ���ͽ��������ʲô ������\n"NOR, ob );
                command("slap "+ob->query("id"));
                return;
        }
		if (!ob->query_temp("jianzong/bijian"))
			 return ;
		if ((int)ob->query_skill("huashan-jianfa",1) <= 200) {
                command("say �һ�ɽ�ɽ��������ӽ�����Ϊ����ĵȼ�̫���ˡ�");
               // command("say �ڵ��з��治��10k��" + RANK_D->query_respect(ob)+"�Ƿ����ò�����");
                return;
        }
		if ((int)ob->query("shen") <= 80000) {
                command("say �һ�ɽ�����������������ɣ��Ե���Ҫ���ϡ�");
                command("say �ڵ��з��治��80k��" + RANK_D->query_respect(ob)+"�Ƿ����ò�����");
                return;
        }
       if(ob->query("quest/huashan")=="����"&&!ob->query_temp("jianzong/bijian")){
              
                command("heng");
                command("say �㲻�ǻ�ɽ���ڸ�ͽô����ô�������ǽ���������");
				return;
		}
		//ֻ�о������ܹ��̲��ܽ��˽��ڣ�����״���ա������bug
        if (ob->query("quest/huashan")!="����") {
               command("say ����˭���Ҳ���ʶ�㣬ץ�������ɡ�");
                return;
        }
      
        command("say �ðɣ��Ҿ���������,���ҪΪ���ǻ�ɽ�ɽ�����������");
        command("recruit " + ob->query("id"));
        ob->set("title",HIW"��ɽ�ɽ����״�����"NOR);
        ob->set("quest/huashan","����");
		return;

}


/*
void init()
{
        object me, ob;
        ::init();

        ob = this_player();
        me = this_object();

	if (interactive(ob) && !environment(ob)->query("no_fight")) {
		command("say �ҽ����ҽ��ڽ���,ֻ����������\n");
		me->set_leader(ob);
		remove_call_out("kill_ob");
		call_out("kill_ob", 1, ob);
	}
}
*/