// shihou.c ʨ����
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_job();

void create()
{
	set_name("ʨ����", ({ "shihou zi", "shihou", "zi" }));
	set("nickname", "�����ɶ�ʦ��");
	set("long", "��˫���ϸ�����һֻ���λεĻƴ󻷣�ʨ�����ڣ���ò��Ϊ�׺ݹ��졣\n");
	set("gender", "����");
	set("age", 43);
	set("attitude", "peaceful");
	set("str", 28);
	set("int", 20);
	set("con", 26);
	set("dex", 23);

	set("max_qi", 11900);
	set("max_jing", 5900);
	set("eff_jingli", 5400);
	set("combat_exp", 3600000);
	set("score", -8000);

	set_skill("force", 300);
	set_skill("huagong-dafa", 300);
	set_skill("dodge", 300);
	set_skill("zhaixingshu", 300);
	set_skill("strike", 300);
	set_skill("chousui-zhang", 300);
	set_skill("parry", 300);
	set_skill("staff", 300);
	set_skill("poison", 120);
	set_skill("tianshan-zhang", 300);
	set_skill("literate", 50);
	map_skill("force", "huagong-dafa");
	map_skill("dodge", "zhaixingshu");
	map_skill("strike", "chousui-zhang");
	map_skill("parry", "chousui-zhang");
	map_skill("staff", "tianshan-zhang");
	prepare_skill("strike", "chousui-zhang");
	set("chat_chance_combat", 5);
	set("chat_msg_combat", ({
		(: exert_function, "huagong" :),
		(: perform_action, "strike.yinhuo" :),
		(: perform_action, "strike.biyan" :),
	}));
	create_family("������", 2, "����");
	set("inquiry", ([
		"������" : "������룬�Ͱ���Ϊʦ��",
		"���޺�" : "ȥ���޺���ʲô������Ϊʦ�͹���ѧ���ˡ�",
		"������" : "����������е���û��ûС�ġ��Ժ�����ɣ�",
		"����"  : (: ask_job :),
	]));

	setup();
	UPDATE_D->get_cloth(this_object());
	carry_object("/d/xingxiu/obj/yao");
	carry_object("/d/xingxiu/obj/fire");
}

void attempt_apprentice(object ob)
{
	if(ob->query("family/family_name") != "������"){
		say("ʨ���Ӷ�"+ob->name()+"������\n");
		return;
	}
	if(ob->query_skill("huagong-dafa",1) < 150 || ob->query("shen") > -20000){
		command("say ����������������ҲŲ��������ء�");
		return;
	}
	if(ob->query_skill("poison",1) < 100 ){
		command("say ��Ķ��ƻ�����100���ҲŲ��������ء�");
		return;
	}
	command("say �ðɣ�������Ļ������е�����ˣ��Ҿ�������ɡ�");
	command("recruit " + ob->query("id"));
}

string ask_job()
{
	object me, ob;
	mapping fam;
  	int shen, exp;
  	me = this_player();
  	fam = (mapping)me->query("family");
  	shen = me->query("shen");
  	exp=me->query("combat_exp",1);

    	if(!fam) return "���ó��������̬�ȹ������β��������������أ�";
    	if(fam["family_name"] != "������" && !me->query_temp("ding_flatter"))
       		return "������ɵ�̬�ȿ���ȥ��̫��������";
    	if(exp < 100000)
    		return "�����������ټӰ��������ɡ�";
    	if(exp >= 500000)
    		return "�������������Ҳ�̫��������Լ�ȥ���������˼Ұɡ�";
    	if(me->query_condition("wait_xx_task"))
    		return "�ϴθ����ˣ������͵ȵȰɡ�";
		if( me->query("job_name") == "���ɷ���")
			return "�����������黹�ã���������Ϊ���ɷ��ǡ�";
    	if( me->query_temp("xx_job"))
    		return "����ô�������﷢����";
    	if( me->query_condition("wait_xx_task"))
    		return "�����������黹�ã���������Ϊ�����ǡ�";
    	ob = new("/d/xingxiu/obj/di");
    	ob->move(me);
    	ob->set("name", MAG "����̵�" NOR);
    	ob->set("long", MAG"����Ѷ̵ó��棬ֻ�����ߴ�������ͨ���Ϻ죬��Ө�ɰ���\n" NOR);
    	ob->set("xx_user", getuid(me));
    	if(fam["family_name"] != "������")
      		me->set_temp("title", MAG"�������ſ�"NOR);
    	me->set_temp("xx_job", 1);
    	message_vision("\n$N�ó�һֻ���ƶ̵ѣ�����$n��\n", this_object(), me);
    	return "����������鲻�ѣ����Ҫ���Ϊ�����˼ҷ��ǲ��ǣ�\n";
}
