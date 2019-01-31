// ���� by River@SJ 2002.6.5

inherit NPC;
#include <ansi.h>
inherit F_MASTER;

void create()
{
	set_name("����", ({ "jiao zi", "jiao", "zi" }) );
	set("long", "������ɫ��׳����̬������������������Ǵ󽫾��а������硣\n"+
		"�������ֲ����Ѷ�����ɽ�ּ��Բ񣬱ص����Ǹ�߳����Ƶ�ͳ����˧��\n");
	set("gender", "����" );
	set("age", 45);
	set("str", 35);
	set("con", 30);
	set("dex", 25);
	set("int", 25);
	set("per", 25);
	set("unique", 1);
	set("attitude", "friendly");

	set("max_qi", 25000);
	set("max_jing", 4800);
	set("eff_jingli", 3600);
	set("neili", 18000);
	set("qi", 25000);
	set("jingli", 3600);
	set("max_neili", 18000);
	set("jiali", 150);

	set("combat_exp", 4500000);
	set("score", 5000);

	set_skill("parry", 350);
	set_skill("dodge", 350);
	set_skill("force", 350);
	set_skill("axe", 350);
	set_skill("literate", 200);
	set_skill("qiantian-yiyang", 350);
	set_skill("pangen-fu", 350);
	set_skill("tianlong-xiang", 350);
	//set_skill("finger", 350);
	//set_skill("yiyang-zhi", 350);
	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "pangen-fu");
	map_skill("force", "qiantian-yiyang");
	map_skill("finger", "yiyang-zhi");
	map_skill("axe","pangen-fu");
	prepare_skill("finger","yiyang-zhi");
	set("chat_chance_combat",60);
	set("chat_msg_combat", ({
		(: perform_action, "axe.jingtian" :),
	
		(: perform_action, "axe.pangen" :),
		(: exert_function, "yiyang" :),
		
		(: perform_action, "axe.cuojie" :),
		
	}));
	create_family("������", 13, "�׼ҵ���");

	setup();
	carry_object(BINGQI_D("axe"))->wield();
	carry_object(ARMOR_D("b_cloth"))->wear();
	carry_object(ARMOR_D("caoxie"))->wear();
}

void init()
{
	object ob;

	::init();
	if (base_name(environment()) != query("startroom")) return;

	if( interactive(ob = this_player()) && visible(ob) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_answer", "answer");
}

void greeting(object me)
{
	if (! me || me->query_temp("yideng/answer")) return;
	command("say ������ϣ�ƾ��ң����������������ɥ�����Բԣ�ˮãã����̨\n"+
		"�������˽���ǧ��תͷ������������Ҳ���ó�������Ҳ���ó���");
	remove_call_out("greeting1");
	call_out("greeting1", 5, me);
}

void greeting1(object me)
{
	if (! me) return;
	command("say ������ۣ�������ŭ��ɽ�ӱ�������·���������������顣����\n"+
		"�غ����д���������䶼���������ˣ����տ࣡�������տ࣡");
	me->set_temp("yideng/answer", 1);
}

int do_answer(string arg)
{
	object jiaozi;
	object me = this_player();
    
	if (! me->query_temp("yideng/answer")) return 0;
	if ( me->query_temp("yideng/jiaozi_pass")) return 0; 

	if ( ! arg ) return 0;

	if ( arg != "��ɽ����������మ���β��������۹��ƽ����һéի��Ұ����������˭���˷�˭�ɰܣ�ª�ﵥư�����ա�ƶ�������ģ��־���ģ�"){
		command("shake");
		return 1;
	}
	message_vision(CYN"\n$N�ص�������ɽ����������మ���β��������۹��ƽ����һéի��Ұ������\n"+
		"����˭���˷�˭�ɰܣ�ª�ﵥư�����ա�ƶ�������ģ��־���ģ���\n"NOR, me);
   /*
	if (me->query_temp("nqg/askyingok"))
    {
	    if (!objectp(jiaozi=present("jiao zi",environment(me))))
	    {
			jiaozi=new("d/dali/yideng/npc/jiaozi");
			jiaozi->move(environment(me));
	    }
		command("hehe ");
		command("hehe "+me->query("id"));
		command("say �ش�ĵ�ͦ�ã�����������ô�����Ƶģ���Ȼ��һ����ò��Ȼ�����ӣ�\n");
		command("say ��С�ӣ����治������Ȼ�������Ǳ����˹�����\n");
		command("say �������ɣ�");
		tell_object(me,HIR"\n\n\n����Է�֪������ʲô�裬�������еĸ�ͷ���㿳ȥ��\n"NOR);
		jiaozi->kill_ob(me);
		me->kill_ob(jiaozi);
		me->add_busy(1);
		//call_out("check_jiaozi",1,me);
		return 1;
    }
    else {
*/
		message_vision(CYN"\n$N�������д��ã��Ŀ�����֮�ʣ���ɽ��һָ��������ȥ�գ�\n"NOR, this_object());
		me->set_temp("yideng/jiaozi_pass", 1);
	//}
	return 1;
}
/*
int check_jiaozi(object me)
{
	object jiaozi;
	
	jiaozi=present("jiao zi",environment(me));
    if (objectp(jiaozi)&& me->is_fighting(jiaozi))
    {
		//remove_call_out("check_jiaozi");
		call_out("check_jiaozi",1,me);
		//return 0;
    }
	if (!objectp(me)) return 0;
	
	me->set_temp("yideng/jiaozi_pass", 1);

	message_vision("�����һ������û����İ���������������ȥ����\n", me);
	return 1;
	

}*/


void attempt_apprentice(object ob)
{
	
	
	if ((string)ob->query("gender") != "����" ){
		command ("say ����������Ů���ӣ��������ң�");
		return;
	}
	if ((string)ob->query("class")=="bonze" ){
		command ("say �����ӷ��Ҳ��ճ��ҵ��ӡ�");
		return;
	}
	if ((int)ob->query_skill("qiantian-yiyang", 1) < 300 ){
		command("say ��ĳ���Ҳ�����������֮�ˣ��㻹�Ƕ��������Ǭ��һ����250�ɡ�");
		return;
	}
	if ((int)ob->query_skill("force", 1) < 300 ){
		command("say ��ĳ�˲�����������֮�ˣ��㻹�Ƕ�������Ļ����ڹ���250�ɡ�");
		return;
	}
	if ((int)ob->query("shen") < 1000000){
		command("say ������������������ɣ��㲻��1m����������ҡ�");
		return;
	}

	command("say �治���һ�����ӣ���ʦ��һ���书�㶼�������ͷ�ϣ����Ժ��Ҫ�ú������ˡ�\n");
	command("say ��Ȼ��Ե�Ҿ��������ˣ�\n");
	command("haha ");
	command("recruit " + ob->query("id"));
	ob->set("title", "�����µ�ʮ�Ĵ��׼ҵ���");
}
