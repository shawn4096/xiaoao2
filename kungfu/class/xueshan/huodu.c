// huodu.c ����
// by sohu
// ���Ѹ�׹�

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name(HIW"����"NOR, ({ "huo du", "huodu" ,"huo","du"}));
	set("long",@LONG
���ǽ��ַ�����С���ӣ��õ������״����ڣ�һ������Ϊ�˵ã���
ü��Ŀ�㣬һ�����Ǽ����������֮��������ɫ��������ִһ������
����ҡ�Σ��Ե��������������Ը���թ������
LONG
	);
	set("title",  "�����µ�ʮ��������" );
	set("nickname","�ɹ�С��ү");
	set("gender", "����");
	set("age", 39);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 23);
	set("int", 38);
	set("con", 24);
	set("dex", 24);
	set("max_qi", 19000);
	set("eff_jing", 5000);
	set("max_jing", 5000);
	set("eff_jingli", 5000);
	set("max_jingli", 5000);

	set("neili", 20000);
	set("max_neili", 20000);
	set("jiali", 200);
	set("combat_exp", 8200000);
	set("score", 30000);
	//set("unique", 1);

	set_skill("mizong-fofa", 200);
	set_skill("literate", 200);
	set_skill("force", 450);
	set_skill("longxiang-boruo", 450);
	set_skill("dodge", 450);
	set_skill("yuxue-dunxing", 450);
	set_skill("hand", 450);
	set_skill("dashou-yin", 450);
	set_skill("claw", 450);
	set_skill("tianwang-zhua", 450);
	set_skill("wushang-dali",450);
	set_skill("staff",450);
	set_skill("parry", 450 );
	set_skill("brush",450);
	set_skill("kuangfeng-xunlei", 450 );

	map_skill("force", "longxiang-boruo");
	map_skill("dodge", "yuxue-dunxing");
	map_skill("hand", "dashou-yin");
	map_skill("parry", "kuangfeng-xunlei");
	map_skill("claw", "tianwang-zhua");
	map_skill("brush", "kuangfeng-xunlei");

	prepare_skill("hand","dashou-yin");
	prepare_skill("claw","tianwang-zhua");
    set("inquiry", ([
               // "����" : (: give_lun  :),
			   // "���ִ�" : (: wulun_dazhuan  :),
              //  "����" : (: give_lun  :),
            //    "�����" : (: give_lun2  :),
                
       ]));
	create_family("������", 11, "����");
	set("class", "mizong");
    set("chat_chance_combat", 60);
    set("chat_msg_combat", ({
                (: exert_function, "longxiang" :),
                (: perform_action, "brush.kuangfeng" :), 
				(: perform_action, "brush.xunleigong" :), 
	}));
	setup();
	carry_object("/d/xueshan/npc/obj/qinxiu-jiasha")->wear();
	carry_object("/clone/weapon/brush/baiyushan")->wield();
	add_money("silver",50);
}

void attempt_apprentice(object ob)
{
	if ((string)ob->query("family/family_name") != "������") {
		 command("say"+ RANK_D->query_respect(ob) +
			"���Ǳ��µ��ӣ������ﵷʲô�ң���");
		return;
	}

	if ((int)ob->query_skill("mizong-fofa", 1) < 150) {
	       command("say ���ڷ��Ǹ����书֮��������150�������ڼ������ɡ�");
		command("say"+ RANK_D->query_respect(ob) +
			"�ٰ�����ͨ��������������б��ŵ��ķ��ɡ�");
		return;
	}

	if ((string)ob->query("class") != "mizong") {
		message_vision("�������˿���ͷ�������������Լ��Ĺ�ͷ��",this_player());
		command("say �㻹û���ң����ܱ�ʾ���������̷��շ��Ҳ������㡣");
		command("say ��λ" + RANK_D->query_respect(ob) +
			"�������¾��ģ������̷��ҷ��������Ұɡ�");
		return;
	}
	if ((int)ob->query_skill("longxiang-boruo", 1) < 220) {
	    command("say ���������Ǵ����¸����书֮��������220�������ڼ������ɡ�");
		command("say"+ RANK_D->query_respect(ob) +
			"�ٰ�����ͨ��������������б��ŵ��ķ��ɡ�");
		return;
	}
	if ((int)ob->query_skill("dashou-yin", 1) < 220) {
	    command("say ����ӡ�Ǹ����书֮��������220�������ڼ������ɡ�");
		command("say"+ RANK_D->query_respect(ob) +
			"�ٰ�����ͨ��������������б��ŵ��ķ��ɡ�");
		return;
	}
	command("say �ðɣ����Ժ�����ҵĵ����ˣ���Ҫ�̿����ޣ�����͵��ѽ��");
	command("recruit " + ob->query("id"));
	ob->set("title",   "�����µ�ʮ��������"  );
}
