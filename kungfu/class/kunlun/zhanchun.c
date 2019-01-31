// zhanchun.c (kunlun)
// By Spiderii ��ʱ�رգ�����ͽ
inherit NPC;
inherit F_MASTER;
#include <ansi.h>

int ask_maiyao();
int ask_tanwang();
int ask_fangqi();
int ask_qingmingyi();
//Ů��ҵڶ���ʦ��

mapping *yao_name = ({ (["name":"С��","id": "xiao jindan"]),(["name":"�غ컨","id": "zang honghua"]),(["name":"����������","id": "wu longgao"]),
 (["name":"����۾���","id": "jujing dan"]),(["name":"�չ�","id": "ju geng"]),(["name":"����","id": "huang qi"]), (["name":"ѩ����","id": "xuelian dan"]),
	(["name":"������","id": "yang jingdan"]),(["name":"���ɼ�����","id": "liuren wan"]), (["name":"���Ʊ�����","id": "baola wan"]),(["name":"��Ԫɢ","id": "jinyuan san"]),
	(["name":"ҩ��","id": "yao cao"]), (["name":"����ɢ","id": "yuzhen san"]),(["name":"������","id": "heshou wu"]),(["name":"�赨ɢ","id": "shadan san"]),
	 (["name":"С����","id": "xiaohuan dan"]),(["name":"��Ϣ��","id": "neixi wan"]),(["name":"����������","id": "yannian dan"]),(["name":"���߲�����","id": "fuling wan"]),
(["name":"����������","id": "danggui dan"]),(["name":"������Ϣ��","id": "chuanbei wan"]),(["name":"���ɽ�ҩ","id": "chantui yao"]),(["name":"��Ѫ�ƾ���","id": "huoxue dan"]),
(["name":"�ⶾ��","id": "jiedu wan"]),(["name":"������","id": "xujing dan"]),(["name":"������","id": "lianzi wan"]),(["name":"ѩ��","id": "xue teng"]),(["name":"�ٻ�","id": "teng huang"]),
(["name":"����ɢ","id": "yuzhen san"]),(["name":"���","id": "ma huang"]),(["name":"Ѫ����","id": "xue puti"]),(["name":"ѩ��","id": "xue teng"]),(["name":"�ٻ�","id": "teng huang"]),

}); 

void create()
{
	set_name("ղ��", ({ "zhan chun", "zhan", "chun" }));
	set("long",
		"���Ǻ�̫����ϲ���ĵ��ӣ����õ�Ҳ��Ϊ������\n");
	set("gender", "Ů��");
	set("age", 24);
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 25);
	set("int", 24);
	set("con", 28);
	set("dex", 26);

	set("eff_jingli", 2850);
	set("max_qi", 5850);
	set("max_jing", 2600);
	set("neili", 5200);
	set("max_neili", 5200);
	set("jiali", 90);
	set("combat_exp", 3380000);
	set("score", 4000);

	set_skill("force", 300);
	set_skill("xuantian-wuji", 300);
	set_skill("dodge", 220);
	set_skill("taxue-wuhen", 300);
	set_skill("parry", 300);
	set_skill("sword", 300);
	set_skill("hand", 300);
	set_skill("sanyin-shou", 300);

	set_skill("liangyi-jian", 300);
	set_skill("leg", 300);
	set_skill("chuanyun-tui", 300);


	map_skill("force", "xuantian-wuji");
	map_skill("dodge", "taxue-wuhen");
	map_skill("sword", "liangyi-jian");
	map_skill("leg", "chuanyun-tui");
    map_skill("parry", "liangyi-jian");
	map_skill("hand", "sanyin-shou");
	prepare_skill("hand", "sanyin-shou");
	prepare_skill("leg", "chuanyun-tui");
	
	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
  		(: perform_action, "sword.jinzhen" :),
  		(: perform_action, "sword.duanyun" :),
		(: perform_action, "sword.feipu" :),
		(: exert_function, "wuji" :),			
  		(: perform_action, "dodge.taxue" :),
	}));
	set("inquiry", ([
		"��ҩ" : (: ask_maiyao :),
		//"����ҽ" : (: ask_qingmingyi :),

		"̽��" : (: ask_tanwang :),
		"����" : (: ask_fangqi :),

	]));


    create_family("������", 4, "����");
	setup();
	carry_object(BINGQI_D("changjian"))->wield();
	carry_object("/d/kunlun/obj/pao3")->wear();
}
void attempt_apprentice(object ob)
{
       if(ob->query("gender")=="����"){
	   command("fear");
	   command("say "+RANK_D->query_respect(ob)+"ʦ����׼�����е��ӣ���ȥ����ʦ��ȥ�ɡ�");
   	   return;
	 }
 
	 if(ob->query("appren_hezudao", 1) == 1) {
	   command("say ǰ�����ҿ������Ц��������ɱ�������ˡ�");
	   return;
	 }
	 if(ob->query_skill("xuantian-wuji",1) < 160){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"��������޼���̫��,����160�����ҿɲ������㡣");
		return;
	}
	if(ob->query_skill("chuanyun-tui",1) < 160){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"��Ĵ�����̫��,����160�����ҿɲ������㡣");
		return;
	}
	if(ob->query_skill("taxue-wuhen",1) < 160){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"���̤ѩ�޺�̫��,����160�����ҿɲ������㡣");
		return;
	}

	 command("say ��Ȼ"+RANK_D->query_respect(ob)+"��ôŬ�����Ҿ�������ɡ�");
	 command("recruit " + ob->query("id"));
	 ob->set("title","�����ɵ��������");
}

int ask_tanwang()
{
	object me;
	me=this_player();
	message_vision(HIY"$NС���������ղ������������õĲ��飡\n"NOR,me);
	if (me->query("family/family_name")!="������") //���������ӿ�
	{
		command("say һ�����������������������ӾͲ��Ǻ��ˣ�\n");
		return 1;
	}
	if (me->query_temp("quest/kl/buyyao/name"))
	{
		command("say ���ϴ�������������Ƿ�"+me->query_temp("quest/kl/buyyao/name")+"��Ϊɶ����ȥ��\n");
		return 1;
	}
	
	if (me->query("combat_exp")>100000)
	{
		command("say ��ľ���ֵ��˸��ˣ�����100k�����쾭�飬��������û�취��\n");
		return 1;
	}
	if (me->query_condition("job_busy")||me->is_busy())
	{
		command("say ������æµ�У�\n");
		return 1;
	}

	command("say �����ʦ���İ��ķ��ˣ���һ�����ù�ϵ�ܺá�\n");
	command("say �����֪��Ϊ�Σ���õ�����������Խ��Խ���ء�\n");
	command("say ʦ���Ѿ����˺ܶ���ҽ������û���á�\n");
	command("say ʦ�����鲻�ã����ǵ��ģ���Ҳ�����ǡ�\n");

	me->set_temp("quest/kl/buyyao/start",1);
	return 1;
}

int ask_maiyao()
{
	object me;
	mapping ob;
	int i;
	
	if (arrayp(yao_name))
		ob=yao_name[random(sizeof(yao_name))];		
	//write(ob["name"]);
	me=this_player();
	message_vision(HIC"$N˵��������Ҳ�����þ�һ����������֪ղ������ʲô�Ը�����\n"NOR,me);
	if (!me->query_temp("quest/kl/buyyao/start"))
	{
		command("say һ�������û��û�ε��������һ��ȥ��\n");
		return 1;
	}
	if (me->query_condition("job_busy"))
	{
		command("say ��������æµ��,�Ժ�Ƭ�̣�\n");
		return 1;
	}
	me->delete_temp("quest/kl/buyyao/start");

	command("say ��Ȼ�д��ģ��ҷǳ����ģ��ȴ����лл���ˡ�\n");
	command("say ������������һ��Ҫ���ӣ��м�ζҩ��׼�����ˣ������ǲ�һ����ҩ���ӡ�\n");
	command("say �Ǿ��鷳����һ�ˣ�ȥ�������ˣ��ҽ��ǳ���л��\n");
	
	command("say �����ﻹ��һ��"HIY"["+ob["name"]+"]��\n");
	me->set_temp("quest/kl/buyyao/name",ob["id"]);
	me->set_temp("quest/kl/buyyao/buy",1);
	return 1;
}

int ask_fangqi()
{
	object me;
	mapping ob;
	string name;
	me=this_player();

	command("say ��Ȼ���겻�ɾ���ʱ��ȥЪϢȥ�ˣ������Ǽ�ס���ˡ�������\n");
	if (!me->query_temp("quest/kl/buyyao/name"))
	{
		command("say ��ʲô��û����Ϲ����ʲô��\n");
		return 1;
	}
	me->delete_temp("quest/kl/buyyao/name");
	me->delete_temp("quest/kl/buyyao/buy");
	me->apply_condtion("job_busy",15);

	return 1;
}


int accept_object(object who, object obj)
{
	int exp,pot,gold;
	object sil;
	exp=200+random(100);
	pot=40+random(10);
	
	gold=30+random(10);
	//������������������Ȿ
	gold=gold+(int)obj->query("value")/100;
	if (obj->query("id")==who->query_temp("quest/kl/buyyao/name")	)
	{
		
		command("say �ǳ���������������Ҫ���Ƿ�ҩҮ��\n");
		command("say ����̫��л���ˣ�\n");
		command("say �����ҵ�һ��С���⣬������ø�л���ˣ�\n");
		
		
		sil=new("clone/money/silver");
		
		sil->set_amount(gold);
		sil->move(who);
		

		who->add("combat_exp",exp);
		who->add("potiental",pot);
	//	command("give sil to "+who->query("id"));
		message_vision(HIY"$N�����"+exp+"�㾭���"+pot+"��Ǳ��,��"+chinese_number(gold)+"�������Ľ�����\n"NOR,who);
		if (who->query_condition("db_exp"))
		{
			who->add("combat_exp",exp);

			message_vision(HBYEL+HIW"$N��˫�������ȡ�ֻ����"+exp+"�㾭�齱����\n"NOR,who);
		}
		who->apply_condition("job_busy",3);
		who->set("job_name","������ҩ");
	//�������ɹ���ֵ
	//	who->add("job_time/����",1);
		who->add("job_time/������ҩ",1);
		who->delete_temp("quest/kl/buyyao/name");
		who->delete_temp("quest/kl/buyyao/buy");
		
		//who->add_temp("quest/����������/��������ƪ/buyyao",1);
		destruct(obj);
		return 1;
	}
	
	
}
