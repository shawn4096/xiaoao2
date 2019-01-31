// miaodi.c ���к���
// by sohu

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_for_join();
int do_kneel();
string ask_job();
string ask_finish();
string ask_fail();
string ask_jobshu();
string ask_miji();

void create()
{
	set_name("����", ({"miao di","miao"}));
	set("long",@LONG
				"����Ѫ���ű����С���ӣ�Ƥ����𪣬��̬Ӻ�ݣ����ǰ���\n"
                "���Ƿ���Ϊ����֮����ż��̧ͷԶ�����ƺ���ɫ��Щ���ǡ�\n"
				"��ʦ��ί���ڴ˿���ɽ����������ͽ��\n"

LONG
	);

    set("title",  "Ѫ���ŵ���������");
	set("gender", "����");
	set("attitude", "peaceful");
	set("class", "huanxi");
	
	set("nick",HIC"����"HIG"����"NOR);
	
	set("inquiry",([
		"��������"	: (: ask_for_join :),
		"����"	: (: ask_job :),
		"��������"	: (: ask_jobshu :),
		"����"	: (: ask_fail :),
		"�ؼ�"	: (: ask_miji :),

	]));

	set("age", 30);
	set("shen_type", -1);
	set("str", 25);
	set("int", 15);
	set("con", 25);
	set("dex", 20);
	set("max_qi", 5450);
	set("eff_jing", 4200);
	set("max_jing", 4200);
	set("neili", 4500);
	set("max_neili", 4500);
	set("jiali", 100);
	set("combat_exp", 3500000);
	set("score", 1000);
	set("unique", 1);
	set_skill("force", 220);
	set_skill("xuedao-jing", 220);
	set_skill("dodge", 220);
	set_skill("xueying-dunxing", 220);
	set_skill("xuedao-daofa", 220);
	set_skill("blade", 220);
	//set_skill("hand", 220);
	set_skill("jingang-liantishu", 220);

	set_skill("strike", 220);
	set_skill("hongsha-zhang", 220);
	set_skill("parry", 220);
	set_skill("huanxi-chan", 100);
	set_skill("literate", 130);
	map_skill("blade", "xuedao-daofa");

	map_skill("force", "xuedao-jing");
	map_skill("dodge", "xueying-dunxing");
	map_skill("strike", "hongsha-zhang");
	map_skill("parry", "xuedao-daofa");

	prepare_skill("strike", "hongsha-zhang");

	create_family("Ѫ����", 6, "����");
	set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
		(: exert_function, "yuxue" :),
		(: perform_action, "blade.jixue" :),
		(: perform_action, "blade.shendao" :),
		(: perform_action, "blade.chilian" :),
		(: perform_action, "blade.wuying" :),
	}));

	setup();
    carry_object("clone/weapon/blade")->wield();

    carry_object("d/xuedao/obj/qinxiu-jiasha")->wear();
}

void init()
{
	add_action("do_kneel", "kneel");
}
//������Ĺ���
string ask_job()
{
	object me,ob;
	me=this_player();
	
	if (!me->query("quest/xuedao/shoujie"))
	{
		command("say ����δ�ܽ䣬�����������У�����������ʧ��\n");
		command("say ����Ҫ���������еĴ���ķ��ɣ�\n");
		return "���������쳾����\n";
	}
	command("say ��Ȼ���Ѿ��ܽ佫�������У���ö�ȥ����������������Ĳпᣡ\n");
	command("say ��������һ��С�������͸���!");
	ob=new("d/xuedao/obj/xiao_peidao");
	
	ob->set("owner",me->query("id"));
	if (me->query_conditon("job_busy"))
	{
		return "����������æ�ڹ������Ժ�Ƭ�̣�\n";
	}
	if (me->query("combat_exp")<100000)
	{
		command("say ���ô˵������ǹ�һ��Ĺ�ľ����Ѳ��һ����������������˳��������䵶�ɼ�Щ����ѪҺ��\n"
					+"��ѵ������Ƶģ������пգ�δ�ط�Ҫɱ�����ֻҪ����˵���ķ����ַ�ȥ�������ɼ�ЩҰ��\n"
					+"������ѪҺ���ǲ��ѵġ��мǣ���ֻ��Ҫ����ЩҰ�����ϲɼ�Щ��Ѫ������ɱ�����ǡ�\n"
					+"��ȶ���Ŀ��顣Ҳ�����ɴ�Щ����ɵ���Ѫ������Ϊ��������ҩ��֮�ã�\n");
		me->set_temp("xuedao/askcaixue",1);
		ob->set("job","��Ѫ");
	}else if (me->query("combat_exp")> 300000 && me->query("quest/xuedao/baishi/pass"))
	{
		command("say ��ľ���ֵ�Ѿ�����300k�������Ѿ���ʦ�˾Ͳ�Ҫ����ʦ�������������ˣ�\n");
		return "�����ӷ��������գ�\n";
	}
	else{
		command("say ���ô˵������ǹ�һ��Ĺ�ľ����Ѳ��һ�����������Ұ��˳�־�ɱ��\n"
			+"��ȶ���Ŀ��顣Ҳ�����ɴ�Щ����ɵ����������Ϊ��������ҩ��֮�ã�\n");
		me->set_temp("xuedao/askdalie",1);
		ob->set("job","����");
	}
	ob->move(me);
	me->apply_condition("job_busy",15);
	me->apply_condition("xddl_job",15);

	command("say ��ȥ��أ�С��Σ�գ�ǧ���ס�𲻶���Ե֮�ˣ�");
	return "�����쳾����Ϊ������\n��������������˭֪��\n";
}
string ask_jobshu()
{
	object me,ob;
	me=this_player();
	
	command("say �����ڴ��Թ������������Ϊ"+me->query("job_time/Ѫ������")+"�Σ�\n");

	command("say ��Ҫи����ֻҪ�������ã�����һ���̶��Ҿ�����Ϊͽ���úøɣ�");
	return "�������ڵ������ˣ�̫����͵����!\n";
}
//���Թ�������

int accept_object(object who, object obj)
{
	object sil;
	int exp,pot,gold;
	
	if (obj->query("xuedao/caixue/ok"))
	{
		exp=250+random(100);
		pot=100+random(10);
		gold=50+random(10);
	}else if (obj->query("xuedao/cairou/ok"))
	{
		exp=300+random(100);
		pot=100+random(10);
		gold=50+random(10);

	}
	
	if (obj->query("id")=="xiao peidao" 
		&&obj->query("owner")==who->query("id")
		&&(obj->query("xuedao/cairou/ok")&&who->query_temp("xuedao/cairou/ok")||obj->query("xuedao/caixue/ok")&&who->query_temp("xuedao/caixue/ok")))
	{
		command("say û�뵽����С�����Ȼ����ڷܣ���Ѫ���Ž�����������\n");
		command("laugh ");
		command("say �������������˶����ʳ���ض����ĵĺܣ�\n");
		who->delete_temp("xuedao/cairou");
		who->delete_temp("xuedao/askdalie");
		who->delete_temp("xuedao");
		
		destruct(obj);
		//������ʼ who->query("job_time/Ѫ������")&&
		if (who->query("combat_exp")<300000) 
		{
			sil=new("clone/money/silver");
			sil->set("set_amount",gold);
			sil->move(who);
			who->add("combat_exp",exp);
			who->add("potential",pot);
			//command("give  to "+who->query("id"));
			message_vision(HIY"\n$N�����"+exp+"�㾭���"+pot+"��Ǳ��,��"+chinese_number(gold)+"�������Ľ�����\n"NOR,who);
			
			if (who->query_condition("db_exp"))
			{
				who->add("combat_exp",exp);

				message_vision(HBYEL+HIW"$N��˫�������ȡ�ֻ����"+exp+"�㾭�齱����\n"NOR,who);
			}

			
		}else message_vision(YEL"$N���鳬��300k��û�ܰ�ʦ��������Щ�ջ�û�н�����\n"NOR,who);

		who->apply_condition("job_busy",5);
		who->set("job_name","Ѫ������");
		who->add("job_time/Ѫ������",1);
		
		if (random(who->query("job_time/Ѫ������"))>300 &&!who->query("quest/xuedao/baishi/pass"))
		{
			command("say �ҿ�"+who->query("name")+"һֱ���๤�����������⣬�������飬�ҿ�������Ϊͽ��\n");
			command("say ��Ѫ���������ຣ��һ���ɣ�����������������Ҵ�Ѫ����");
			command("say �����Ը�⣬���԰���Ϊʦ��\n");

			who->set("quest/xuedao/baishi/pass",1);
		}
		return 1;
	}
	
}
//����ʧ��job
string ask_fail()
{
	object me,ob;
	me=this_player();
	if (me->query_temp("xuedao/askdalie"))
	{
		command("say ��Ȼ���겻�ɲ����������ʱ��ȥЪϢȥ��,�ߣ�\n");
		me->delete_temp("xuedao/askdalie");

	}
	else if (me->query_temp("xuedao/caixue"))
	{
		command("say ��Ȼ���겻�ɲ�Ѫ����ʱ��ȥЪϢȥ��,�ߣ�\n");

		me->delete_temp("xuedao/askcaixue");

		
	}else command("say ��ʲô��û����Ϲ����ʲô��\n");


	if (objectp(ob=present("xiao peidao",me)))
	{
		destruct(ob);
	}
	me->delete_temp("xuedao");
	me->apply_condtion("job_busy",15);
	return "������˴���������ӵ�������";
}

string ask_for_join()
{
	object me;

	me = this_player();
	if (me->query("family")&&me->query("family/family_name")!="Ѫ����")
		return RANK_D->query_respect(me) + "�����ڿ���Ц�ɡ�\n";
	
	if (me->query("combat_exp")>10000)
		return RANK_D->query_respect(me) + "���Ȼ����10k�ĸ����ˣ��ѵ����������ɵ��Եף���\n";

	if( (string)me->query("class")=="huanxi" )
		return "���Ѿ����㿪̳�ܽ���ˣ�����ȱ��˶�һ�Σ���ɲ��С�\n";

	if( (string)me->query("gender") == "����" )
		return "ʩ�������ȱ����˵�����ն�������������Ѫ������ʱ����ȫ�������⣬.����\n";

   	if( (string)me->query("gender") != "����" ) {
		command("say"+ RANK_D->query_respect(me)+ "����ֻ�����Ե��ӣ�Ůʩ���ɷ�Ը������������ϲ����\n");
		return "�ٺ�``\n";
	}
  
	me->set_temp("pending/join_huanxi", 1);
	return "�������������̷ϲ�������(kneel)�ܽ䡣\n";
}

int do_kneel()
{
	object me = this_player();

	if( !me->query_temp("pending/join_huanxi") )
		return 0;

	message_vision("$N������ͷ�����������ع���������\n\n",me);
    message_vision("$n�ͳ�������������ü��Ŀ��Χ�������˼�Ȧ�����������дʡ�\n\n",me);
    message_vision("$n��Щ��ˮ����$Nͷ�ϣ�ɽ��һ����$N���ɵô��˼�����ս��\n\n",me);
    message_vision("$n����Խ��Խ�ߣ���ͷ�������ܵĺ�ˮ���ƺ����˺ܴ��������\n\n",me);
    message_vision("$n������һ�������ѷ����Żػ��У���������˲����ϵĺ�ˮ��\n\n",me);
	command("smile ");
	command("say �������ܽ䷨�������ˣ��ӽ��Ժ�ϲ����ᱣ����ġ�\n");
	me->delete_temp("pending/join_huanxi");
	me->set("class", "huanxi");
	me->set("quest/xuedao/shoujie",1);
	me->set("family/family_name","Ѫ����");
	me->set("family/generation",7);
	me->set("title","Ѫ�����ܽ�С����");
    return 1;
}



void attempt_apprentice(object ob)
{
	
	//Ԥ������job��������ӿ�

	if (ob->query("family") && (string)ob->query("family/family_name") != "Ѫ����") {
		command("say"+ RANK_D->query_respect(ob) + "���Ǳ��µ��ӣ������ﵷʲô�ң���");
		return;
	}
//���Ѫ��������60�Ͳ���ͽ
	if (ob->query("class")!="huanxi")
	{
		command("say �㲻���ҵ����ڻ�ϲ�ڵĵ��ӣ�û�¾Ͳ�Ҫ��ɧ���ҡ�\n");
		return;
	}
	if (!ob->query("quest/xuedao/shoujie"))
	{
		command("say ��û���ܽ䣬һ�����У���������Ʋ�ס�Լ���������\n");
		return;
	}
    if (!ob->query("quest/xuedao/baishi/pass"))
    {
		command("say ��û��ͨ�����ſ��飬һ�����У������������������ļ�ϸ����\n");
		return;

    }

	if( (string)ob->query("gender") == "����" ) {
		command("say"+ RANK_D->query_respect(ob)+ "�����ȱ��ȫ���������������\n");
		return;
	}
	if( (string)ob->query("gender") != "����" ) {
		command("say"+ RANK_D->query_respect(ob)+ "����ֻ�����Ե��ӣ�Ůʩ���ɷ�Ը������������ϲ����\n");
		return;
	}
//	if( ob->query("combat_exp")>200000 ) {
		//command("say"+ RANK_D->query_respect(ob)+ "���Ҳ����ܹ�������֮����Ѫ�������ͷ�������ɴ�ˣ�\n");
	//	return;
	//}

	if ((int)ob->query("shen") > -10000) {
		command("hmm");
		command("say ��Ѫ������������Զ���Щ��ν�Ľ��������ĸ�����������ӣ�");
		command("say ��������������-10000���������Ϊͽ�����»ᱻ�˳�Ц��");
		return;
	}
	command("say �Ҿ�ϲ��������������С���ˡ��ã�������Ϊ�ҵ��Ӱɡ�");
	command("recruit " + ob->query("id"));
	return;
	
}

string ask_miji()
{
	object me,ob;
	me=this_player();
	
	if (me->query("class")!="huanxi")
	{
		command("say ����δ�ܽ䣬�����������У�����������ʧ��\n");
		command("say ����Ҫ���������еĴ���ķ��ɣ�\n");
		return "���������쳾����\n";
	}
	command("say ��Ȼ���Ѿ��ܽ佫�������У��Ǻܺã�\n");
	command("say ��������һ��Ѫ���������ؼ��͸��㣬����˵��Ҫ����Ҫ�͸���Ե��!");
	ob=new("d/xuedao/obj/xdj_book1");
	
	//ob->set("owner",me->query("id"));

	ob->move(me);

	command("say �ú���������Ѫ������������,���ֵ�һ��");
	return "Ѫ�������µ�һ��\n";
}