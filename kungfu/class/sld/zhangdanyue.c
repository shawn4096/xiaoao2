// zdy.c �ŵ���
// Modified by Lklv add ask xionghuangjiu
#include <ansi.h>

inherit F_MASTER;
inherit NPC;
string ask_jiu();
string ask_xunshe();
string ask_fangqi();

void create()
{
	set_name("�ŵ���", ({ "zhang danyue","zhang" }));
	set("long", "����ʮ������ͣ��������̺���������ʹ,��ͨ�����ȷ������߱޷���\n");
	set("gender", "Ů��");
	set("title", "�����̺���������ʹ");
	set("age", 42);
	set("str", 20);
	set("int", 22);
	set("con", 22);
	set("dex", 22);
	set("per", 25);
	set("combat_exp", 200000);
	set("shen", -50000);
	set("attitude", "peaceful");
	set("max_qi",8000);
	set("max_jing",2000);
	set("neili",3000);
	set("max_neili",3000);
	set("jingli",2800);
	set("eff_jingli",2800);
	set("jiali",80);
	set("score", 20000);

	set_skill("force", 350);
	set_skill("dodge", 350);
	set_skill("parry",350);
	set_skill("whip",350);
	set_skill("lingshe-bianfa", 350);
	set_skill("youlong-shenfa",350);
	set_skill("dulong-dafa",350);
	set_skill("shenlong-yaoli",180);
    set_skill("leg", 350);

	set_skill("shenlong-tuifa", 350);
	map_skill("leg", "shenlong-tuifa");

	map_skill("force", "dulong-dafa");
	map_skill("dodge", "youlong-shenfa");
	map_skill("parry","huagu-mianzhang");
	prepare_skill("leg", "shenlong-tuifa");

	create_family("������",3, "����ʹ");
    set("inquiry", ([
            "������" : "����������������������ң���ڡ�\n",
            "�ۻƾ�" : (: ask_jiu :),
			"ѵ������" : (: ask_xunshe :),
			"����" : (: ask_fangqi :),
        ]));
	setup();
	carry_object("/d/sld/npc/obj/bcp")->wear();
}

void attempt_apprentice(object ob)
{
	mapping myfam;
	object ob1;

	myfam = (mapping)ob->query("family");
	if(!myfam || myfam["family_name"] != "������"){
		if(ob->query("app/sld")!=1){
			command("say �ðɣ��Ҿ����������ҵĵ��ӡ�");
			ob->set("app/sld",1);
			command("recruit " + ob->query("id"));
			tell_object(ob, "��������ۻƾƺ��ˣ��Ϳ��Բ�����ҧ�ˡ�\n");
			ob1 = new("/d/sld/npc/obj/xionghuangjiu");
			if(!ob1->move(ob))
				ob1->move(environment(ob));
			tell_room(environment(ob), "�ŵ��¸���"+ob->name()+"һ���ۻƾơ�\n");
		}
		else{
		command("say �����̲����������ѽ�֮�ˣ����߰�!");
		}
	}
}

int recognize_apprentice(object ob)
{
	mapping myfam;
	object hw;

	myfam = (mapping)ob->query("family");
	if(!myfam || (myfam["family_name"] != "������")) return 0;
	if(!ob->is_apprentice_of(this_object())) return 0;
	if(myfam 
		&& (myfam["family_name"] == "������")
		&&(ob->query("shen",1) >0))
	{
		command("say �ߣ��㾹Ȼ�ҺͰ׵����˸���һ���ǲ��ǲ�����ˣ���ȥ���ݺú÷�ʡ��ʡ�ɣ�");
		if(!objectp(hw=find_object("/d/sld/npc/obj/heiwu")))
			hw=load_object("/d/sld/npc/obj/heiwu");
		ob->set("in_heiwu",time());
		ob->move(hw);
		return 0;
	}
	return 1;
}

string ask_jiu()
{
        object ob, me = this_player();

	if (me->query("family/family_name") != "������")
                return "ȥ�ұ��˰ɣ��ҿɲ������㣡";
        if (me->query("xionghuangjiu"))
                return "������Ѿ��ȹ��ۻƾ��ˣ��ٺȲ��º����㣿";

        if (present("xionghuang jiu", me))
                return "�����ϻ����ۻƾưɡ�";

        ob = new("/d/sld/npc/obj/xionghuangjiu");
        ob->move(me);
        message_vision("�ŵ��µݸ�$Nһ���ۻƾơ�\n", me);
        return "��������ۻƾƺ��ˣ��Ͳ�����ҧ�ˡ�";
}


string ask_xunshe()
{
        object ob, me;
		me= this_player();
		
		if (me->query("family/family_name") != "������")
                return "ȥ�ұ��˰ɣ��ҿɲ������㣡";
		if (me->query_temp("sld/qushe/start"))
                return "�����ղ��Ѿ������ˣ�\n";
		if (me->query_condition("job_busy")||me->is_busy()||me->query_condition("sldjob_xunshe"))
                return "������æ�ڹ�����,����������\n";
        if (present("zhu di",me))
                return "�����ϻ�����ѣ�Ϊɶ���Ͽ�ȥ��\n";
		if (me->query("job_name")=="����ѵ��")
                return "�����������ѵ������,����������\n";
        if (present("cuizhu di",me))
			return "�����ϲ�����һֻ�����ô����\n";
		
		ob = new("/d/sld/npc/obj/zhudi");
        ob->set("owner",me->query("id"));
		ob->move(me);
        message_vision(HIG"�ŵ��µݸ�$Nһ������ѣ�˵������������ѵ���Ǽ�Ϊ��Ҫ���������Ȼ����ȥ�ɡ���\n"NOR, me);
		command("say ����ʹ����look zhudi����ʹ��˵����\n");
		command("say ����ڶ��߾�����û������ȥѵ�ߣ�����������ô��Ҳ�в����ߣ�\n");
        message_vision(HIY"�ŵ��¶�$N˵�����������������������ɣ�����Ҫ���������������мǣ�����\n"NOR, me);

		me->set_temp("sld/qushe/start",1);

        return "������ֻ���ɴ˻�ã���Ҫ��ϧ�����,��Ϊ�˵������Ժ�Ĵ��¡�\n";
}
//������Ʒ
int accept_object(object who, object ob)
{
	
	int sum,gold,getshen,jobs;
	object sil;
	sum=40+random(10);
	jobs=who->query("job_time/����ѵ��");

	if (ob->query("taskok")
		&& ob->query("owner")==who->query("id")
		&& who->query_temp("sld/qushe/taskok")		
		&& ob->query("id")=="cuizhu di")
	{
		getshen=-1;
		gold=1+random(1);				
		
		who->set("job_name","����ѵ��");			
		who->apply_condition("job_busy",3);		
		who->delete_temp("sld/qushe");
		who->delete_temp("sld");
		command("thumb "+who->query("id"));

		tell_object(who,RED"\n�ŵ��µ��˵�ͷ����"+ob->query("name")+RED+"���뻳�У�\n"NOR);
		command("say �ܺã�"+who->query("name")+"����Ȼ�����������ˣ��Ҿ�Ӧ�ý����㣡\n");
		tell_object(who,GRN"\n�ŵ����ó����ɼ�¼��������"+who->query("name")+HIY+chinese_number(gold)+GRN"������ɹ����Ľ�����\n"NOR);
		who->add("party/gongji",gold);
		tell_object(who,GRN"\n�ŵ��������ó�Щ���ӣ��ݸ�"+who->query("name")+HIY+chinese_number(sum)+GRN"����������ȥ�Ⱦ�ȥ�ɣ�\n"NOR);

		sil=new("clone/money/silver");
		sil->set("set_amount",gold);
		sil->move(who);

		//Ԥ��������ʾ�ӿ�
		
		if (random(jobs)>1000
			&&random(who->query("kar"))>26 
			&& !who->query("quest/sld/dichuan"))
		{
			
				message_vision(HIC"�ŵ�����Զ����$N�����˴�Ĵָ��˵�������������飬�ҽ���$NΪ���������ĵմ����ӡ�\n"NOR,who);
				who->set("title","�����̵մ�����");
				who->set("quest/sld/dichuan",1);
		}
			
		TASKREWARD_D->get_reward(who,"����ѵ��",getshen,0,0,3+random(4),0,0,0,this_object());
		who->set("job_name", "����ѵ��");
	//	who->delete_temp("sldjob");
		who->apply_condition("job_busy",3);
		
		if (random(jobs)>10000
			&&random(who->query("kar"))>27
			&& jobs % 20 == 0
			&& who->query_skill("dulong-dafa",1)>350
			&& !who->query("quest/sld/dldf/dulong/start")
			&& who->query("quest/sld/dichuan"))
		{
			
				message_vision(HIY"�ŵ��¿���$Nһ�ۣ�����������˵���������Ž������˸���˵�ˣ�����֪ͨ��ȥ����˵��Ҫ�£���\n"NOR,who);
				
				who->set("quest/sld/dldf/dulong/start",1);
		}		
		destruct(ob);
		return 1;
	}

}
string ask_fangqi()
{
	object ob;
	object me=this_player();
	if (me->query_temp("sld/qushe/start"))
	{
		command("say ��Ȼ�����Ѷȣ�������Ҳûʲô����ȥЪϢ��ɣ�\n");
		me->delete_temp("sld");
		me->apply_condition("job_busy",5);
		me->apply_condition("sldjob_xunshe",5);
		if (objectp(ob=present("cuizhu di",me)))
		{
			destruct(ob);
		}
		return "���ڵ��µ�������һ������һ���ˣ�\n";
	}
	command("say û�²�Ҫ��ɧ���ң�\n");
	return "�ߣ�\n";

}