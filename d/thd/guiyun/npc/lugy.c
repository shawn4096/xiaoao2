// By jpei
// ��ͽ�� Modified by Numa 19990917
// Modified by Darken for taohua quest
// Modified by mxzhao 2004/05/12 for shen restrict to exp/10

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
#include "nadir.c"

string ask_yao2();
int ask_quest();
int ask_gold();

 object ob = this_object();
void create()
{
	set_name("½��Ӣ", ({"lu guanying", "lu", "guanying"}) );
	set("title","����ׯ��ׯ��");
	set("long", "���������޳��ۣ�������������׳����\n");
	set("gender", "����" );
	set("age", 27);
	set("attitude", "peaceful");
	
	set("str",25);
	set("int",25);
	set("con",27);
	set("dex",26);
	set("max_qi", 5200);
	set("max_jing", 3000);
	set("eff_jingli", 5200);
	set("neili", 4200);
	set("max_neili", 4200);
	set("jiali", 80);
	set("combat_exp", 300000);
	
	set_skill("force", 250);
	set_skill("bihai-chaosheng", 250);
	set_skill("dodge", 250);
	set_skill("suibo-zhuliu", 250);
	set_skill("qimen-baguazhen",100);
	set_skill("parry", 250);
	set_skill("strike", 250);
	set_skill("luoying-zhang", 250);
	set_skill("leg", 250);
	set_skill("xuanfeng-tui", 250);
	//set_skill("sword", 250);
	//set_skill("yuxiao-jian", 250);
	//set_skill("taoism", 100);
	set_skill("literate", 150);
	set_skill("qimen-bagua", 80);
	
	map_skill("force", "bihai-chaosheng");
	map_skill("dodge", "suibo-zhuliu");
	map_skill("strike", "luoying-zhang");
	map_skill("leg", "xuanfeng-tui");
	map_skill("parry", "luoying-zhang");
	//map_skill("sword", "yuxiao-jian");
	prepare_skill("strike", "luoying-zhang");
	prepare_skill("leg", "xuanfeng-tui");
	
	set("rank_info/respect", "��ׯ��");
	set("shen_type", 1);
	set("shen", 200);
	create_family("�һ���", 3, "����");
	set("class", "fighter");
	set("unique", 1);
	
	set("inquiry", ([
		"name": "����½��Ӣ�����������ׯ����",
        "rumors": (: ask_quest :),
		 "����": (: ask_quest :),
		"here": "�����ǹ���ׯ�������תת�ɣ������뵽�ͷ���Ϣ��",
		"��а": "��������ʦүѽ�����������˼Ҷ�׼���Ҳ��ܸ�����ѧ�ա�",
		"��ҩʦ": "��������ʦүѽ�����������˼Ҷ�׼���Ҳ��ܸ�����ѧ�ա�",
		"�һ���": "��˵��ʦ��ס�ĵط�����ϧû��ȥ������",
		"½�˷�": "���ҵĸ��ף��������˼���ʲô����",
		"½��Ӣ": "���ң��������¡�",
		"����ׯ": "�����ǻ����Ҹ���������Ѫ�Ž������ģ�����ׯԺ�����Σ�",
		"̫��": "����ׯǰ��Զ����һ���̲������Ĵ����",
		"ҩ" : "�������ұ�����ҩ���һ������ӿ��Ե���������ȡ��",
//		"���ž۾���": (: ask_yao1 :),
//		"���ɼ�����": (: ask_yao2 :),
		"���ɼ�����": "�ҽ����ҷ��˱����ˡ�",
		"�Ż���¶��":   "�Ż���¶�����������ޱȣ��������û��! ",
		"���߽���" : (: ask_gold :),
        ]) );
	
	setup();
	
	carry_object(__THD__"obj/wht-cloth.c")->wear();
}

// �˴�������ͽ
void attempt_apprentice(object ob)
{
	object me= this_object();
	mapping fam= ob->query("family");
	
	if ( fam && fam["family_name"] =="�һ���" && (int)ob->query("family/generation")==3){
		command("say "+RANK_D->query_respect(ob)+"�Ѿ��ǼҸ��ĵ��ӣ�"+RANK_D->query_self(me)+"����������Ϊͽ��");
		return;
	}
	if (fam && fam["family_name"] == "�һ���" && (int)ob->query("family/generation")==2){
		command("say "+RANK_D->query_respect(ob)+"�Ѿ�����ʦү�ĵ��ӣ�"+RANK_D->query_self(me)+"����������Ϊͽ��");
		return;
	}
	
	if (ob->query("shen") < -ob->query("combat_exp")/10 
		&& (int)ob->query("shen") < -200000) 
	{
		command("say ��ʦү��ƽ�����������ˣ����������޶�����аħ���������һ��");
		return;
	}
	if (ob->query("shen") > ob->query("combat_exp")/10 
		&& (int)ob->query("shen") > 200000) 
	{
		command("say ��ʦү��ƽ�����������ˣ������������������Ĺ�������֮ͽ������һ��");
		return;
	}
	// change app int from 28 -> 24
        if (ob->query("int") < 18) {
		command("say ��Ĳ���̫����ʺ�ѧ���һ������似��");
		return;
	}
	command("look " + ob->query("id"));
	command("say �ţ����㻹�Ǹ�ѧ����ϣ��Ҿ�������ɣ�");
	command("recruit " + ob->query("id"));
	ob->set("class", "fighter");
	ob->set("title","�һ������Ĵ�����");
}
int ask_quest()
{
          object ob = this_player();
           mapping fam = ob->query("family");
	command("consider");
	command("say ���������������˸�����ͷ�������澹Ȼ�����ָ�ס�");
	command("say ����һ������Ҫ���ͼ��˱���ȥ����֪��Ϊʲô��");
	command("kick");
         if (ob->query_temp("thd/onquest") ==4) 
    ob->set_temp("thd/onquest",5);
	return 1;
}
int ask_gold()
{
	object me;
	int skill, gold;
	mapping myfam;
	me = this_player();
	skill = me->query_skill("bihai-chaosheng", 1);
	myfam = (mapping)me->query("family");
	if( !myfam || myfam["family_name"] != "�һ���" ) {
		command("thumb "+(string)me->query("id"));
		command("say "+ RANK_D->query_respect(me) +"�����߽���һ��Ҫ�������ĳ�����");
		return 1;
	}
	if( (int)me->query("thd_given") >= (int)me->query("age") ) {
		command("@@");
		command("say ԭ��"+ RANK_D->query_respect(me) +"�㻹û�뿪����");
		return 1;
	}

        if( skill < 216 ) {
		command("thumb "+(string)me->query("id"));
		command("say "+ RANK_D->query_respect(me) +"��ͻ��ᣬ������ѧ���书�ɡ�\n");
		return 1;
	}

	gold = 500000 + skill * 5000;
	if( 100 >= skill ) gold += gold/2;
	me->add("balance", gold);
	me->set("thd_given", (int)me->query("age"));
	command("say �������һ������ӳ�Ĭ���꣬�Ǹ�ȥ�����߶��£�");
	command("say �ҽ���" + MONEY_D->money_str(gold) + "�������Ǯׯ�����뵺���Ҫ����С�İ���");
	return 1;
}
