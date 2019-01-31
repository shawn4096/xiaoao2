// king.c ������
// added by tangfeng@sj 2004

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

#define QUESTDIR1 "quest/�����˲�/�貨΢��ƪ/"
#define QUESTDIR2 "quest/�����˲�/����Ӫ��ƪ/"
#define QUESTDIR3 "quest/�����˲�/��������ƪ/"
#define QUESTDIR4 "quest/�����˲�/���ɾ�Ԯƪ/"
#define QUESTDIR5 "quest/�����˲�/��������ƪ/"

string enter();
string qinwang(object ob);
string askduanyu();
string tianlonghelp();
string asksave();
string askxiaofeng();
string askjiumozhi();
string ask_zhijian();
string ask_sandie();
string ask_yyz();
void create()
{
	set_name("������", ({ "duan zhengming", "duan", "master" }) );
	set("nickname", HIW"������"NOR);
	set("title","����ʵ�");
	set("gender", "����" );

	set("age", 48);
	set("str", 28);
	set("con", 28);
	set("dex", 28);
	set("int", 28);
	set("per", 26);

	set("max_qi", 34000);
	set("max_jing", 6000);
	set("eff_jingli", 6000);
	set("neili", 34000);
	set("qi", 34000);
	set("jingli", 6000);
	set("max_neili", 34000);
	set("jiali", 200);
	set("liumai-shenjian/guanchong",1);
    set("env/liumai","guanchong");

	set("rank_info/respect", "����");
	create_family("������", 13, "�׼ҵ���");
	set("long", "������ȥƽ�׽��������з�ȣ�����������üĿ֮��͸��һ�ɱ��˵�Ӣ����\n");
	set("combat_exp", 9600000);
	set("score", 20000);
//set liumai �س�
	set_skill("parry", 450);
	set_skill("dodge", 450);
	set_skill("qingyan-zhang", 450);
	set_skill("strike", 450);
	set_skill("buddhism",200);
	set_skill("force", 450);
	set_skill("literate", 150);
	set_skill("sword", 450);
	set_skill("duanjia-jianfa", 450);
	//set_skill("cuff", 450);
	set_skill("duanjia-quan", 450);
	set_skill("yiyang-zhi", 450);
	set_skill("finger", 450);
	set_skill("qiantian-yiyang", 450);
	set_skill("tianlong-xiang", 450);

	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "duanjia-jianfa");
	map_skill("sword", "duanjia-jianfa");
	map_skill("force", "qiantian-yiyang");
	map_skill("cuff", "duanjia-quan");
	map_skill("strike", "qingyan-zhang");
	map_skill("finger","yiyang-zhi");
	prepare_skill("finger","yiyang-zhi");
    set("chat_chance_combat",70);
    set("chat_msg_combat",({ 
		   (: exert_function, "yiyang" :),
           (: perform_action, "finger.sandie" :),
		   (: perform_action, "finger.yizhisanmai" :),
		  // (: perform_action, "finger.ciqu" :),
        }));
	set("inquiry", ([
		"���" : (: enter :),
		"����" : (: qinwang :),
		"ָ������" : (: ask_zhijian :),
		"һ��ָ��" : (: ask_yyz:),
		"name": "�޾��Ǳ����۶�������",
		"here": "������Ǵ���ʹ���",
		"����" : (: askduanyu :),
		"����" : "������Ǵ���",
		"������" : "���������Ҷμ���ѧ�����֮�أ���������������¿ɲ�����ô���׵�.",
		"��������" : (: tianlonghelp :),
		"Ӫ��" : (: asksave :),
		//"���" : (: asksave :),
		"����" : "�����˳���Ľ�ݡ������壬�˵�һ���ú���",
		"Ӫ�ȶ���" : (: asksave :),
		"Ӫ������" : (: askxiaofeng :),
		"Ľ�ݸ�" : "�����˳���Ľ�ݡ������壬��˵Ľ�ݹ����꼶���ᣬȴ����������",
		"Ľ�ݲ�" : "����Ľ�ݲ����Ľܲţ���ϧӢ�����š�",
		"�Ħ��" : (: askjiumozhi :),
		"��������" : (: ask_sandie :),
		"������" : "��˵������������߾�ѧ����Ҳδ�ܵü���",
	]));

	setup();
	carry_object("/d/dali/npc/obj/huangpao")->wear();
	carry_object("/clone/weapon/gangjian")->wield();
}

void init()
{
	object ob,me;
	me=this_object();
	ob = this_player();
	::init();
	if (interactive(ob = this_player()) 
	 && living(this_object())
	 && (int)ob->query_temp("killqueen")) {
		command ("say �㾹��ɱ�ҵĻʺ���������\n");
		me->set_leader(ob);
		remove_call_out("kill_ob");
		call_out("kill_ob", 0, ob);
	}
}
string askjiumozhi()
{
	object me;
	me = this_player();
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "��˵�������µ�һ��ɮ�Ħ�ǽ����������·𷨽����������Ҵ���֮�Ұ���";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
  	  command("? "+me->query("id"));
		  return "��ħɮ��Ȼ����۸��Ҵ������ˣ���Ϊ��ެ����һ�𷨸�ɮ����ν����������ȫ��һ�ɺ��ԡ�";
  }
	if (me->query(QUESTDIR2+"start")&& me->query(QUESTDIR2+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "�Ħ����Ϊ�����һ�𷨸�ɮ����ν����������ȫ��һ�ɺ��ԡ�";
  }
  command("nod");
	return "���������Ħ������ެ���Ļ�������������˵���ߴ��ǻۣ���ͨ�𷨣������书Ҳ�Ǿ��ˡ�";
}
string askxiaofeng()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR3+"start"))
  {
  	  command("hoho");
  		return "�����˳���Ľ�ݡ������壬�˵�һ���ú�������Ԯ��֮˵��";
  }
	if (me->query(QUESTDIR3+"start") && !me->query(QUESTDIR3+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "��˵������飬ֻ���漰�����������֮����ʵ�ڲ��ò��֡�";
  }

	if (me->query(QUESTDIR3+"bad"))
	{
  	  command("heng");
  	  command("? "+me->query("id"));
	  return "���壬�Ѳ��������ȳ���ԭ��������ν��Ȳ�֪���⡣";
  }
	if (me->query(QUESTDIR3+"start") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR4+"start"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "��˵������飬ֻ���漰�����������֮����ʵ�ڲ��ò��֡�";
  }
	if (me->query(QUESTDIR4+"start")&& !me->query(QUESTDIR4+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "������Сֶ֮���֣���ȻҪ�ȡ���λ"+RANK_D->query_respect(me) +"������һ��������μҵ������Ԯ����";
  }
	if (me->query(QUESTDIR4+"start") && me->query(QUESTDIR4+"over"))
	{
  	  command("haha "+me->query("id"));
		  return "��һս����ʹ�죬"+me->query("name")+"�����������֣��˵���������";
  }
  command("hoho");
	return "�����˳���Ľ�ݡ������壬�˵�һ���ú�������Ԯ��֮˵��";
}
string asksave()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"start") &&!me->query(QUESTDIR2+"start"))
  {
  	  command("hoho");
  		return "����������ϲ��ѧ��ֻ�����׾���ƽ�׽��ˣ�����Ԯ��֮˵��";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "��˵��ǰ��ʱ������������ǳ���һ��������δ�лؼң���֪"+RANK_D->query_respect(me) +"�ɷ��������һ�¡�";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "����̽����Сֶ����ٹ������������»���"+RANK_D->query_respect(me) +"����ǰ����ٹ�һ�ˡ�";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "��л"+RANK_D->query_respect(me) +"���Сֶ��ֻ���Դ���ٹȻ�����Сֶ�����㱣���֪���кζ������ܺ������ˡ�";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "��������ٹȻ�����������Ѫ�������������죬�ű������������ȥ�ˡ�";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "��Ȼ�ǳ��Ħ����ȸ��֣���Ը�����������డ��";
  }
  command("hoho");
	return "����������ϲ��ѧ��ֻ�����׾���ƽ�׽��ˣ�����Ԯ��֮˵��";
}
string askduanyu()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"start" )&&!me->query(QUESTDIR2+"start"))
  {
  	  command("hoho");
  		return "����������֮Сֶ��������ϲ��ѧ��ֻ�����׾���";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "��˵��ǰ��ʱ������������ǳ���һ��������δ�лؼҡ�";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "����̽����Сֶ����ٹ���������������ֻ��Ҫ��һ���ˡ�";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "��л"+RANK_D->query_respect(me) +"���Сֶ��";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "��������ٹȻ�����������Ѫ�������������죬�ű������������ȥ�ˡ�";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "��Ȼ�ǳ��Ħ����ȸ��֣���Ը�����������డ��";
  }
  command("hoho");
	return "����������֮Сֶ��������֮�ӡ�";
}
string tianlonghelp()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"over"))
  {
  	  command("haha");
  		return "���������Ҷμ���ѧ�����֮�أ��������ƣ��벻ҪΣ��������";
  }
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "��˵�������¸�ɮ�Ħ�ǲ��ս����������£���֪��ϲ�ǻ���";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
		  return "��ħɮ��Ȼ����۸��Ҵ������ˣ���Ϊ��ެ����һ�𷨸�ɮ��";
  }
	if (me->query(QUESTDIR2+"over"))
	{
  	  command("thank "+me->query("id"));
		  return "��л"+RANK_D->query_respect(me) +"�����ⳡ����Σ����������ֶ�ӵ��Խ�ȡ�";
  }
  command("hoho");
	return "���������Ҷμ���ѧ�����֮�أ��������ƣ��벻ҪΣ��������";
}
string enter()
{
	object ob;
	string target;
	ob = this_player();
	if ( ob->query("combat_exp") < 100000)
		return "������󹬸���";
	if ( ob->query_temp("fan")){
		string book;
		book=ob->query_temp("book_target");
		return("����ȥ��"+book+CYN"��������ȥ��"NOR);
	}
	switch  (random(8)){
		case 0: target = HIW"����ƪ"NOR; break;
		case 1: target = HIW"����ƪ"NOR; break;
		case 2: target = HIW"ҹ��ƪ"NOR; break;
		case 3: target = HIW"Ǭ����ƪ"NOR; break;
		case 4: target = HIW"������ƪ"NOR; break;
		case 5: target = HIW"��¥��ƪ"NOR; break;
		case 6: target = HIW"������ƪ"NOR; break;
		case 7: target = HIW"Ħ������ƪ"NOR; break;
	}
	ob->set_temp("fan",1);
	ob->set_temp("book_target",target);
	return "����󹬣��Ȱ��Ұ������˲���"+target+CYN"������"NOR;
}

string qinwang(object ob)
{
	string new_title,title,*title1,*title2;
	mapping fam;
	ob=this_player();
	fam = ob->query("family");
	title1 =({ "��","ƽ","��","Ǭ","��" });
	title2 =({ "��","��","��","��" });
	if ((!fam)||(fam["family_name"] != "������"))
		return RANK_D->query_respect(ob)+"�뱾��������������֪�˻��Ӻ�̸��";
	if (ob->query("tls") || ob->query("class")=="bone")
		return RANK_D->query_respect(ob) + "�Ѿ���Ϊ�����¸�ɮ�����������Ȼ�ǲ��ʺ���ġ�";
	if (ob->query("job_time/����") < 3000 && ob->query_skill("qiantian-yiyang",1) < 160)
		return RANK_D->query_respect(ob) + "Ϊ�������Ļ������������Ϊ��ү�ˣ�";
	if (stringp(ob->query("qinwang")))
		return RANK_D->query_respect(ob) + "�Ѿ����ҳ������ˣ���ô����������";
	title= title1[random(sizeof(title1))]+title2[random(sizeof(title2))]+"��";
	new_title= "�����"+title;
	ob->set("title",HIW + new_title + NOR);
	ob->set("qinwang", title);
	command("chat ���������������޷�" + ob->query("name")+"Ϊ��"+new_title+"��");
	return "�ðɣ������Ϳ๦�ߣ��޾ͷ���Ϊ"+ new_title +"��";
}

void attempt_apprentice(object ob)
{
	string name, new_name, *prename;
	prename = ({ "��", "��" });
	if (ob->query("tls")&&ob->query("class")=="bone") {
		command ("say ���Ѿ��������³��ҵ����ˣ��Ҳ����������ˣ�");
		return;
	}
	if( (int)ob->query_skill("qiantian-yiyang",1) < 350 ){
		command ("hmm");
		command ("say ��Ǭ��һ�������֮��ҿɲ����㣡");
		return;
	}
	if(ob->query_int() < 50){
		command("say ��ѧ֮���������Ըߣ����ҿ�" + RANK_D->query_respect(ob) + "�����Բ���50���ƺ�������");
		return;
	}
	if(ob->query("shen") < 2000000){
		command("say ���������û��ң�����λ" + RANK_D->query_respect(ob) + "����2m�����ҿ����ʺ����Ҵ������ȥ�ˡ�");
		return;
	}
	if ((int)ob->query("shen") < 1000000){
		command ("say  �Ҵ���������������ɣ����ҿ�" + RANK_D->query_respect(ob) +"������1m�����ʺ����Ҵ�����ϡ�");
		return;
	}
	command("smile");
	command("say �ܺã�" + RANK_D->query_respect(ob) + "���Ŭ�������ձض��гɡ�");
	name = ob->query("name");
	new_name = prename[random(sizeof(prename))] + name[<4..<1];
	command("say ���Ҵ���μң��ӽ��Ժ�������־ͽ���" + new_name + "��");
	ob->set("name", new_name);
	command("recruit " + ob->query("id") );
	if (!ob->query("qinwang")) ob->set("title","�������ǰ����");
}

void recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
	ob->set("class", "officer");
}

int accept_object(object who, object ob)
{
	string bookname;
	bookname=ob->query("name");
	if ((bookname!=HIW"����ƪ"NOR)
	 &&(bookname!=HIW"����ƪ"NOR)
	 &&(bookname!=HIW"ҹ��ƪ"NOR)
	 &&(bookname!=HIW"Ǭ����ƪ"NOR)
	 &&(bookname!=HIW"������ƪ"NOR)
	 &&(bookname!=HIW"��¥��ƪ"NOR)
	 &&(bookname!=HIW"������ƪ"NOR)
	 &&(bookname!=HIW"Ħ������ƪ"NOR))
		return notify_fail("����������ҡͷ������Ҫ�ⶫ��û�ð���\n");
	if ( bookname==this_player()->query_temp("book_target")){
		if ( ob->query_temp("find") == who->query("id")){
			command("smile");
			command("say �ܺã�����Խ����ˡ�");
			who->set_temp("enter",1);
			who->delete_temp("book");
			call_out("destroying", 1, ob);
			return 1;
		}
		command("hmm");
		command("say ����������ҵ��İɡ�");
		call_out("destroying", 1, ob);
		return 1;
	}
	else {
		command("hmm");
		command("say �ⲻ����Ҫ���飬����ȥ�ҡ�");
		call_out("destroying", 1, ob);
		return 1;
	}
}

void destroying(object ob)
{
	destruct(ob);
	return;
}

int prevent_learn(object ob, string skill)
{
	if (skill == "yiyang-zhi"){
		command("һ��ָ�����Ҵ�������֮�����������޴����߲��ö�����\n");
		return 1;
	}
	return 0;
}

string ask_zhijian()
{
	object me, ob;
	int i,j,x;
	
	ob = this_object();
	me = this_player();       
	if (!me->query("family")
		|| me->query("family/family_name")!="������")
		return "������ɵ��ӣ����ʴ�����������";

	
    if( me->query_skill("yiyang-zhi", 1) < 300 )
		return "���һ��ָ���費��300�����޷���������һ��ָ�Ծ�����Ϊָ��������Ҫ���ڣ�";
	
	if( me->query("quest/tls/zhijian/pass") )
		return "���Ѿ����������ָ���������ֺιʿ�����Ц�أ�";

	if ((int)me->query("int")<30)
		return "��һ��ָ�ܿ����ԣ�����������30���������ң�\n";
	
	
	if( time()- me->query("quest/tls/zhijian/time")<86400)
		return "�ţ��㲻�Ǹ�����̹������ž����İ����𣿻�����Ŭ����ʱ��ɣ�";

   
	message_vision(HIC"$N����Ŀ���$n������˵���������ɵ�һ��ָ����������ǧ���򻯣��Ծ�����Ϊʵ�ʽ���������һ���˵У�\n"
						"�㿴���ˣ��Ҹ�����ʾһ�飬�����Լ��������ˡ�\n"+
						HIR"\n\n\n$N������ѣ�������ӿ������������������磬Ѹ���ޱȡ�����$n�ۻ�����\n"NOR,this_object(),me);
	
 
    i=random(10);
	j=random(me->query("kar"));
	x=random(me->query("int"));
	command("say ����һ��ָ�˵�����������һ����ǧ��Ҫ��ס��\n");
	command("pat "+me->query("id"));
	if( i>=6 
		&& me->query("kar")<31
		&& x >= 20
		&& j >= 26 ) 
	{
		tell_object(me,HIY"\n�����˶�������ָ�㣬��һ��ָ����Ϊ���İ��������ĵá�\n"NOR);
		tell_object(me,HIG"\n����ͼ����Ϣ�嵽����Ѩ�У�ͻȻֻ������������һ������ֱͨ˫�֣����Ͼ���������Ȼһ�ᡣ\n"
			             +"������ʶ��˳��һ�ӣ�һ���ƿ�������������һ����������ָ������˲�佫ǰ����ǽ�ϵ��˸�����\n"
						 +"���������������������������������÷��š����д�ϲ��\n"NOR);
		me->set("quest/tls/zhijian/pass",1);
		log_file("quest/yyzzhijian", sprintf("%8s(%8s) ʧ��%d�κ�ѧ��һ��ָ������,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/tls/zhijian/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "��ϲ����һ��ָָ�����������ɹ�!\n";
		
	}	
   else
	{
		log_file("quest/yyzzhijian", sprintf("%8s(%8s) ����һ��ָָ����������ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/tls/zhijian/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"�����˶�������ָ�㣬���Ƕ�һ��ָָ�������İ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/tls/zhijian/fail",1);
		me->set("quest/tls/zhijian/time",time());
		me->start_busy(1+random(3));
		
		return "�ǳ��ź�����һ��ָָ������ʧ��"+me->query("quest/tls/zhijian/fail")+"�Ρ�\n";
	}

}


string ask_sandie()
{
	object me, ob;
	int i,j,x;
	
	ob = this_object();
	me = this_player();       
	if (!me->query("family")
		|| me->query("family/family_name")!="������")
		return "������ɵ��ӣ����ʴ�����������";

	
    if( me->query_skill("yiyang-zhi", 1) < 250 )
		return "���һ��ָ���費��250�����޷���������һ��ָ�Ծ�����Ϊ��������������Ҫ���ڣ�";
	
	if( me->query("quest/tls/yyz/sandie/pass") )
		return "���Ѿ�����������������������������ֺιʿ�����Ц�أ�";

	if ((int)me->query("int")<30)
		return "��һ��ָ�ܿ����ԣ�����������30���������ң�\n";
	
	
	if( time()- me->query("quest/tls/yyz/sandie/time")<86400)
		return "�ţ��㲻�Ǹ�����̹������ž����İ����𣿻�����Ŭ����ʱ��ɣ�";

   
	message_vision(HIY"$Nһ��ƽ�͵ض�$n����˵�������������������Ҵ���һ��ָ�ľ���֮һ��������ɷ�����񡢽������У�\n"
						"���Թ�Ч��ͬ����ɷ������������˺��Է������������������öԷ����б�����Ч������Ĺ���\n"+
							"ȴ��Ϊ��ͬ������Чǣ�ƶԷ����ж����㿴���ˣ��Ҹ�����ʾһ�飬�����Լ��������ˡ�\n"+
						HIC"\n\n\n$N������ѣ�������ӿ������������������磬Ѹ���ޱȡ�����$n�ۻ�����\n"NOR,this_object(),me);
	
 
    i=random(10);
	j=random(me->query("kar"));
	x=random(me->query("int"));
	command("say ����һ��ָ�˵�����������һ����ǧ��Ҫ��ס��\n");
	command("say �⿪��Ҫ��ϸ�鿴�����似���ص㣬����������һ���̻塣\n");
	command("pat "+me->query("id"));
	if( i>=5 
		&& me->query("kar")<31
		&& x >= 20
		&& j >= 22 ) 
	{
		tell_object(me,HIC"\n�����˶�������ָ�㣬��һ��ָ���������İ��������ĵá�\n"NOR);
		tell_object(me,HIG"\n����ͼ����Ϣ�嵽�س�Ѩ�У�ͻȻֻ������������һ������ֱͨ˫�֣����Ͼ���������Ȼһ�ᡣ\n"
			             +"������ʶ��˳���������У�һ���ƿ������������졢���졢������������������������Ѹ���ޱȡ�\n"
						 +"���������������������������������÷��š����д�ϲ��\n"NOR);
		me->set("quest/tls/yyz/sandie/pass",1);
		log_file("quest/yyzsandie", sprintf("%8s(%8s) ʧ��%d�κ�ѧ��һ��ָ������������,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/tls/yyz/sandie/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "��ϲ����һ��ָ�������������ɹ�!\n";
		
	}	
   else
	{
		log_file("quest/yyzsandie", sprintf("%8s(%8s) ����һ��ָ����������������ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/tls/yyz/sandie/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"�����˶�������ָ�㣬���Ƕ�һ��ָ�������������İ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/tls/yyz/sandie/fail",1);
		me->set("quest/tls/yyz/sandie/time",time());
		me->start_busy(1+random(3));
		
		return "�ǳ��ź�����һ��ָ������������ʧ��"+me->query("quest/tls/yyz/sandie/fail")+"�Ρ�\n";
	}

}


string ask_yyz()
{
	object me, ob;
	int i,j,x;
	
	ob = this_object();
	me = this_player();       
	
	if (!me->query("family")
		|| me->query("family/family_name")!="������")
		return "������ɵ��ӣ����ʴ�����������";
	if (!me->query("quest/tls/yyz/start/helpnhsover"))
	{
		return "���������ɵ��ӣ�������һ��ָֻ�������ӵܣ�\n";
	}
	
    if( me->query_skill("qiantian-yiyang", 1) < 450 )
		return "���Ǭ��һ�����費��450�����޷���������һ��ָ������Ҫ���ڣ�";
	
	if( me->query("quest/tls/yyz/pass") )
		return "���Ѿ����������һ��ָ�񹦾������ֺιʿ�����Ц�أ�";

	if ((int)me->query("int")<30)
		return "��һ��ָ�ܿ����ԣ����������Բ���30���������ң�\n";
	if ((int)me->query("str")<30)
		return "��һ��ָ�ܿ��������������������30���������ң�\n";
	
	if( time()- me->query("quest/tls/yyz/time")<86400)
		return "�ţ��㲻�Ǹ�����̹������ž����İ����𣿻�����Ŭ����ʱ��ɣ�";

   
	message_vision(HIC"$Nһ��ƽ�͵ض�$n����˵������һ��ָ�����Ҵ������֮һ��Ҳ�������ϴ�����֮�ء�����������Ӳ����⴫\n"
						"�����Ȼ���Ҵ��������Ĵ���ˣ��������Ҵ����Σ�������͵�ȷ�ܴ��ҺͶ����������£�Ψ�н������书\n"+
							"�������㣬�㿴���ˣ��Ҹ�����ʾһ�飬�ܷ�����Ϳ����Լ��������ˡ�\n"+
						HIR"\n\n\n$N������𣬡��͡���һ�����һ���������޵ľ�����˲�����У�����$n�ۻ�����\n"NOR,this_object(),me);
	
 
	j=random(me->query("kar"));
	command("say ����һ��ָ�˵�����������һ����ǧ��Ҫ��ס��\n");
	command("say Ҫ��ϸ�鿴�����似���ص㣬����������һ���̻塣\n");
	command("pat "+me->query("id"));
	if( me->query("kar")<31
		&& j >= 25 ) 
	{
		tell_object(me,HIC"\n�����˶�������ָ�㣬��һ��ָ�İ��������ĵá�\n"NOR);
		tell_object(me,HIG"\n����ͼ����Ϣ�嵽�س�Ѩ�У�ͻȻֻ������������һ������ֱͨ˫�֣����Ͼ���������Ȼһ�ᡣ\n"
			             +"������ʶ��˳���������У�һ���ƿ������������졢���졢������������������������Ѹ���ޱȡ�\n"
						 +"����������������һ��ָ�񹦾��������÷��š����д�ϲ��\n"NOR);
		me->set("quest/tls/yyz/pass",1);
		log_file("quest/yyzpass", sprintf("%8s(%8s) ʧ��%d�κ�ѧ��һ��ָ����,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/tls/yyz/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "��ϲ����һ��ָ�����ɹ�!\n";
		
	}	
   else
	{
		log_file("quest/yyzpass", sprintf("%8s(%8s) ����һ��ָ����ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/tls/yyz/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"�����˶�������ָ�㣬���Ƕ�һ��ָ�������������İ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/tls/yyz/fail",1);
		me->set("quest/tls/yyz/time",time());
		me->start_busy(1+random(3));
		
		return "�ǳ��ź�����һ��ָ����ʧ��"+me->query("quest/tls/yyz/fail")+"�Ρ�\n";
	}

}