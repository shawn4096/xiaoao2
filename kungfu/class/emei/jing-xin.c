// /kungfu/class/emei/jing-xin.c
// Update by Lklv 2001.10.18
// lane 2004.12.24 add ����

#include "nigu.h"
inherit F_MASTER;
inherit NPC;
int ask_gold();

void create()
{
        set_name("����ʦ̫", ({"jingxin shitai", "jingxin", "shitai"}));
        set("long", "�����ڻ��������е�ʦ̫�������ڲ������������ҵ����������⡣\n");

        set("gender", "Ů��");
        set("attitude", "friendly");
	set("unique", 1);
        set("class", "bonze");

        set("age", 45);
	set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 11500);
        set("max_jing", 5500);
        set("neili", 11500);
        set("max_neili", 11500);
        set("jiali", 130);
        set("combat_exp", 4500000);
        set("score", 100);
	set("inquiry",([
                "���"  : (: ask_for_join :),
                "����"  : (: ask_for_join :),
	  	        "����ħ��" : (: ask_gold :),

        ]));
	set_skill("dacheng-fofa", 200);
	set_skill("hand", 350);
	set_skill("jieshou-jiushi", 350);
	set_skill("linji-zhuang", 330);
	set_skill("huifeng-jian", 330);
	set_skill("literate", 130);
	set_skill("sword", 330);
	set_skill("parry", 330);
	set_skill("dodge", 330);
	set_skill("force", 330);
	set_skill("anying-fuxiang", 330);

	map_skill("force", "linji-zhuang");
	map_skill("sword", "huifeng-jian");
	map_skill("parry", "huifeng-jian");
	map_skill("hand", "jieshou-jiushi");
	map_skill("dodge", "anying-fuxiang");

        create_family("������", 4, "����");

        setup();
	carry_object("/d/emei/obj/changjian")->wield();
	carry_object("/d/emei/obj/shoes")->wear();
	carry_object("/d/emei/obj/cloth")->wear();

}

int ask_gold()
{
	object me;
	int skill, gold;
	mapping myfam;
	me = this_player();
	skill = me->query_skill("linji-zhuang", 1);
	myfam = (mapping)me->query("family");

	if( !myfam || myfam["family_name"] != "������" ) {
		command("wa2 "+(string)me->query("id"));
		command("say "+ RANK_D->query_respect(me) +"�������뷨����̫����!");
		return 1;
	}

	if( (int)me->query("emei_given") >= (int)me->query("age") ) {
		command("innocent");
		command("say ������˵Ҫȥ����ħ�̵���");
		return 1;
	}

        if( skill < 216 ) {
		command("joke "+(string)me->query("id"));
		command("say "+ RANK_D->query_respect(me) +"��ͻ��ᣬ���ǰ���ѧ���书�ɡ�\n");
		return 1;
	}

	gold = 200000 + skill * 3000;
	if( 100 >= skill ) gold += gold/2;
	me->add("balance", gold);
	me->set("emei_given", (int)me->query("age"));
	command("say ���������뷨����̫���ˣ���ϧ����ħ������׳�󣬲���ħ�̿��²�����ô���װɣ�");
	command("say �ҽ���" + MONEY_D->money_str(gold) + "�������Ǯׯ������¶���ɽѲ���°ɣ�����ħ�̶�ͽ�в���������");
	return 1;
}
