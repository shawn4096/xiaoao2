// NPC: /d/huashan/npc/cheng_by.c
// Date: Look 99/03/25
// Modify by Lklv 2001.10.18

inherit NPC;
#include <ansi.h>
void create()
{
        set_name("�ɲ���",({"cheng buyou", "cheng", "buyou" }));
        set("title","��ɽ�ɵ�ʮ�������ڵ���");
        set("nickname","����ʦ��С����");
        set("long", "է����ȥֻ������һ��ƽ����С���ӣ���Ŀ���׶���ˡ�\n");
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
        set("jiali", 150);
        set("combat_exp", 45000000);
        set("score", 30000);

        set_skill("cuff", 200);
        set_skill("zhengqi-jue",  200);
        set_skill("poyu-quan", 200);
        set_skill("sword",  350);
        set_skill("dodge",  200);
        set_skill("force",  200);
        set_skill("parry",  200);
        set_skill("huashan-qigong", 220);
        set_skill("huashan-jianfa",  350);
        set_skill("huashan-shenfa",  200);

        map_skill("dodge", "huashan-shenfa");
        map_skill("force","huashan-qigong");
        map_skill("sword","huashan-jianfa");
        map_skill("parry","huashan-jianfa");
        map_skill("strike","hunyuan-zhang");
        prepare_skill("cuff","poyu-quan");

        create_family("��ɽ��",13,"����");

        set("chat_chance_combat",40);
        set("chat_msg_combat", ({
		(: perform_action, "sword.feijian" :),
	}));
	setup();
	carry_object(BINGQI_D("sword/sword"))->wield();
	carry_object(ARMOR_D("armor/cloth"))->wear();
}
void attempt_apprentice(object ob)
{
        mapping fam;
        if (!ob->query("family") && ob->query("family/family_name")!= "��ɽ��"  && (int)ob->query("is/huashan")==1 ) {
                message_vision(CYN "$N���������ɽ�ɵ���ͽ��������ʲô ������\n"NOR, ob );
                command("slap "+ob->query("id"));
                return;
        }
		if (!ob->query_temp("jianzong/bijian"))
			 return;
		if ((int)ob->query_skill("huashan-jianfa",1) <= 100) {
                command("say �һ�ɽ�ɽ��������ӽ�����Ϊ����ĵȼ�̫���ˡ�");
               // command("say �ڵ��з��治��10k��" + RANK_D->query_respect(ob)+"�Ƿ����ò�����");
                return;
        }
		if ((int)ob->query("shen") <= 10000) {
                command("say �һ�ɽ�����������������ɣ��Ե���Ҫ���ϡ�");
                command("say �ڵ��з��治��10k��" + RANK_D->query_respect(ob)+"�Ƿ����ò�����");
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
        ob->set("title","��ɽ�ɽ����״�����");
        ob->set("quest/huashan","����");
		return;

}

/* void init()
{
        object me, ob;
        ::init();

        ob = this_player();
        me = this_object();

        if (interactive(ob) && !environment(ob)->query("no_fight")){
		command("say �ҽ����ҽ��ڽ���,ֻ����������\n");
		me->set_leader(ob);
		remove_call_out("kill_ob");
		call_out("kill_ob", 1, ob);
	}
}
*/