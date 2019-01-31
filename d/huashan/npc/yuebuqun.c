// NPC: /d/huashan/npc/yuebuqun.c
// Date: Look 99/03/25
// Modify by Looklove 2000,12,15
// By Spdierii@ty ��Ҫnpc.ɱ����
// by lsxk@hsbbs  ͳһ�����㷨 2007/1/10

inherit NPC;
inherit F_MASTER;

#include <job_mul.h>
#include <ansi.h>
string ask_zhengqi();
string ask_zixia();
string ask_me1();
string ask_me2();
string ask_pay();
string ask_fail();
string ask_qizong();
string ask_jianzong();
string ask_fengyi();
string ask_hssb();
string ask_ziyin();
int ask_jianzong();
int do_huida(string arg);
void create()
{
	set_name("����Ⱥ",({"yue buqun", "yue", "buqun" }));
	set("title","��ɽ�ɵ�ʮ����������");
	set("nickname",HIG"���ӽ�"NOR);
	set("long", "������ڽ���������Զ����������𣬻�ɽ�������ˡ�\n");
	set("age", 40);
	set("attitude", "friendly");
	set("no_bark",1);
	set("shen_type", 1);
	set("job_npc", 1);
	set("no_get", 1);

	set("per", 25);
	set("pur", 10);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);

	set("max_qi",23800);
	set("qi", 23800);
	set("max_jing", 6400);
	set("jing",6400);
	set("eff_jingli", 5700);
	set("jingli", 5700);
	set("max_neili", 15500);
	set("neili", 15500);
	set("jiali", 200);
	set("combat_exp", 9800000);
	set("score", 30000);
	set("chat_chance_combat",60);
	set("chat_msg_combat", ({
		(: perform_action, "sword.jianzhang" :),
		//(: perform_action, "sword.kuaijian" :),
		(: perform_action, "sword.fengyi" :),
		(: exert_function, "zixia" :),
		//(: perform_action, "sword.kuaijian" :),
		(: perform_action, "sword.lianhuan" :),
		(: perform_action, "sword.cangsong" :),
		(: perform_action, "sword.shijiushi" :),
		(: exert_function, "zixia" :),
		(: exert_function, "jianyi" :),
		(: exert_function, "jianqi" :),
	}));

	set_skill("poyu-quan", 400);
	set_skill("cuff", 400);
	set_skill("sword",  460);
	set_skill("dodge",  400);
	set_skill("force",  480);
	set_skill("parry",  400);
	set_skill("literate",400);
	set_skill("zixia-gong", 480);
    set_skill("huashan-qigong", 450);
	set_skill("huashan-jianfa",  460);
	set_skill("huashan-shenfa",  400);
	set_skill("zhengqi-jue", 200);
	set_skill("ziyin-yin", 200);
    set_skill("hunyuan-zhang", 400);
    set_skill("strike", 400);
    map_skill("strike", "hunyuan-zhang");
	map_skill("dodge", "huashan-shenfa");
	map_skill("force","zixia-gong");
	map_skill("sword","huashan-jianfa");
	map_skill("parry","huashan-jianfa");
	map_skill("cuff","poyu-quan");
	prepare_skill("strike","hunyuan-zhang");
	create_family("��ɽ��",13,"����");

	set("inquiry", ([
		"��ϼ�ؼ�"	: (: ask_zixia :),
		"�����"	: (: ask_ziyin :),
		"ʧ��"		: (: ask_fail :),
		"fail"		: (: ask_fail :),
		"�Ͷ�����"	: (: ask_me1 :),
		"job"		: (: ask_me1 :),
		"����"		: (: ask_me2 :),
		"���"		: (: ask_me2 :),
		"finish"	: (: ask_me2 :),
		"������"	: (: ask_zhengqi :),
		"�з�����"	: (: ask_fengyi :),
        "����֮��"      : (: ask_qizong :),
        "��ɽ����"      : (: ask_jianzong :),
		"��ɽʯ��"      : (: ask_hssb :),
	]));

	setup();
	carry_object(BINGQI_D("sword"))->wield();
	carry_object(ARMOR_D("cloth"))->wear();
}

void heart_beat()
{
	::heart_beat();

	clear_conditions_by_type("poison");
	if( !is_fighting() && living(this_object()))
		reincarnate();
}

void init()
{
	object ob;
	//add_action("do_huidai","answer");
	add_action("do_huida","answer");
	::init();
	ob = this_player();
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object me)
{
	int shen;
	if(!me) return;

	if ( file_name(environment(this_object())) != this_object()->query("startroom")) return;

	shen = me->query("shen");
    if(shen <= -200000 
		&& me->query("family/family_name") == "��ɽ��" 
		//&& me->query("quest/huashan")=="����"
		){
		command("disapp "+me->query("id"));
		command("say ���������������а�����ӽ������㲻���ǻ�ɽ�����ˣ�");
        command("expell " + me->query("id"));
		command("say �ã������ס���ˣ����Ѿ����ҿ�����"+me->query("expells")+"��!\n");

		if (!me->query("expells"))
		{			
			me->set("expells",1);
		}else me->add("expells",1);
       // me->delete("quest/huashan");
	}
	//���棡
	if(shen <0 && shen > -200000 && me->query("family/family_name") == "��ɽ��"){
		command("sigh "+me->query("id"));
		command("say �ҿ����������������а��������ǲ�������������ʲô���£�");
		command("say ������Ҳ鵽�����������һ�ɽ�������£��Ҷ������㣡");
	}
}

void attempt_apprentice(object ob)
{
	mapping fam;
	if ( mapp(fam=ob->query("family"))
	 && (string)fam["family_name"] != "��ɽ��"
	 && (int)ob->query("is/huashan")==1 ) {
		message_vision(CYN "$N���������ɽ�ɵ���ͽ��������ʲô ������\n"NOR, ob );
		command("kick "+ob->query("id"));
		return;
	}
	if ( ob->query("fengset")) {
		command("say �㲻���Ѿ����˽��ڵ�ǰ��Ϊʦ��ô��");
		return;
	}
	if(ob->query("quest/huashan")=="����"){
    command("heng");
    command("say �ߺߣ����ڵ��������뿪��ɽ�������ǻ�ɽ�ɵ��ӣ�����������ѵ���������������֮λ��");
    return;
    }
	if (!ob->query("quest/hs/dichuan"))
	{
		command("consider");
		command("look "+ob->query("id"));
		command("say �㲢���һ�ɽ�ĵմ����ӣ�����Ϊʦ�����ء��л������ȥΪ��ɽ�����");
		return ;
	}
	if ( ob->query("gender") != "����" ){
		command("say ��ֻ����ͽ��" + RANK_D->query_respect(ob) + "��ذɡ�");
		return;
	}
	if ( ob->query_skill("huashan-qigong",1) <300 ){
		command("say ��ֻ����ͽ��" + RANK_D->query_respect(ob) + "��Ļ�ɽ��������300��������ذɡ�");
		return;
	}
	if ((int)ob->query("shen") < 1000000) {
		command("say �һ�ɽ�����������������ɣ��Ե���Ҫ���ϣ�����1M����������������");
		command("say �ڵ��з��棬" + RANK_D->query_respect(ob) + "�Ƿ����ò�����");
		return;
	}
	command("say �ðɣ��Ҿ���������,���ҪΪ���ǻ�ɽ����������");
	command("recruit " + ob->query("id"));
	ob->set("title","��ɽ�������״�����");
    ob->set("quest/huashan","����");
}

string ask_ziyin()
{
    object me;
    mapping fam;
	string msg,arg;
    me=this_player();

    if ( mapp(fam=me->query("family"))
    && (string)fam["family_name"] != "��ɽ��"){
    command("? "+me->query("id"));
    return "��λ" + RANK_D->query_respect(me) + "����������ҥ����\n";
    }
    if (me->query("quest/huashan")=="����")
       return "�ߺߣ����ڵ��������뿪��ɽ�������ǻ�ɽ�ɵ��ӣ�����������ѵ���������������֮λ��\n";

   //if ((int)me->query("combat_exp")<4500000)
       //return "����������㾭��ֵ���ҿ��������˰ɡ���ɽ�ɲ��Ұ�����Щ������¸��㻹����������\n";
   if ((int)me->query_skill("force")<350)
       return "����������ڹ�����̫����,����350��������������������⣿\n";
   
   if(me->query_temp("zyy/askyue")){
       
       return "�ղŲ��Ƕ���������ô�����������ظ�˵һ�㣿�㵱��ͯ�����°���";
   }
   command("say �һ�ɽ��������ȫ���ڹ���ʤ�����ڻ������ԣ���Խ�����ڣ��������ζΪʦ��仰�����⣡");
   command("cry "+me->query("id"));
   command("say ǰһ�׶Σ���������ɽ���ڵ���������֮�������ܽᣬż���ĵã�");
   command("say ��������Ȥ����ȥ�����ҿ������Ƿ������Ե��");

   me->set_temp("zyy/askyue",1);
   return me->name(1)+"�����Ҫ�ӱ���������ʼ������ѭ��������а���";

}

string ask_qizong()
{
    object me;
    mapping fam;
	string msg,arg;
    me=this_player();

    if ( mapp(fam=me->query("family"))
    && (string)fam["family_name"] != "��ɽ��"){
    command("? "+me->query("id"));
    return "��λ" + RANK_D->query_respect(me) + "����������ҥ����\n";
    }
/*
   if (me->query("quest/huashan")=="����")
       return "���꽣��֮����������������ɽ���֣����Ҫ�ú����������ɽ�ɰ���\n";
*/
   if (me->query("quest/huashan")=="����")
       return "�ߺߣ����ڵ��������뿪��ɽ�������ǻ�ɽ�ɵ��ӣ�����������ѵ���������������֮λ��\n";

   if ((int)me->query("combat_exp")<4500000)
       return "����������㾭��ֵ���ҿ��������˰ɡ���ɽ�ɲ��Ұ�����Щ������¸��㻹����������\n";
   if ((int)me->query_skill("force")<350)
       return "����������ڹ�����̫���ˡ���ɽ�ɲ��Ұ�����Щ��������㻹����������\n";
   if ((int)me->query("int")<35)
       return "��ɽ������������ԣ����������Բ���35������˵��Ҳ�״\n";

   if (me->query("fengget"))
    {
		command("consider");
		return "��Ȼ���Ѿ��õ����ڴ��У�����͵ѧ�����ڵ���ϼ��";
	}
   if(me->query_temp("quest/huashan/xiangzheng")){
       add_action("do_huida","answer");
       return "��ô�����������ظ�˵һ�㣿�㵱��ͯ�����°���";
   }
   command("say �һ�ɽ�ɵ�ȷ�н���֮�֣����껪ɽ��Ů��һս��ͬ���ֵ�ȴ�໥˺ɱ���Ҳ��̶ð���");
   command("cry "+me->query("id"));
   msg="�����ڵ����˽���������Ԧ����������ν������������ľ��Ϊ��������Ϊ�أ���Ϊ����\n"
   +"�ڹ�һ���гɣ�����������Ȼ��ͬһ�ն���ټ��ϱ������������ġ���ϼ�񹦡���\n"
   +"������ʮ�أ�������Щֻ�Ứ�ν��У��ڹ�ƽƽ�Ľ��ڵ��ӿɱȵģ�\n";
   command("say "+msg);
  
   add_action("do_huida","answer");
   me->set_temp("quest/huashan/xiangzheng",1);
   return me->name(1)+"�����Ҫ�ӱ���������ʼ������ѭ��������а���";

}

//��ϼ����һ����ʼ ���Ϊquest/huashan/zixia1,���ȥ˼������ڣ�Ѱ������
int do_huida(string arg)
{
    object me=this_player();
	if(!me->query_temp("quest/huashan/xiangzheng")) return 0;

    if(!arg) return notify_fail("����ش�ʲô��\n");
    
    if(arg!="��" && arg !="yes") return notify_fail("��ش��ǡ�����ʾ��ͬ��������������Ⱥ��������\n");
    if(arg == "��" || arg == "yes" ){
        me->set("quest/huashan","����");
		message_vision(HIM"$N���˵�ͷ�������ơ��ǣ�ʦ������\n"NOR,me);
		if (random(me->query("job_time/��ɽ")) > 1000 && me->query_temp("hs/askzixia"))
	    {   
		command("pat "+me->query("id"));
	    command("say [��ɽ�Ź�����ϼ��һ]����ϼ�������ƽ�������ҿ��㻹���ȵ�˼����ȥ��ھ����ɣ����ܷ���������\n");
		me->delete_temp("quest/huashan/xiangzheng");
		me->delete_temp("hs/askzixia");
		me->set_temp("quest/huashan/zixia1",1);
		return 1;
	    }
		message_vision(HIC"����Ⱥ��¶����֮ɫ���ƺ���$N�Ļش��������⡣\n"NOR,me);
       // return 0;
    }
	return 0;
}

string ask_me1()
{
	int i;
	object ob, me, name1, ling;
	me=this_player();
	ob = this_object();
	ling = present("ling pai", me);
	name1 = me->query("id");
	i = me->query("shen");
    if(me->query_temp("mb")) 
           return "�㻹����ȥ˼�������˼��ȥ�ɡ� ";
	if (!wizardp(me) && me->query("shen") < 1)
		return "����¶�׹�, ����ȥ�Ͷ�����? ";

	if (!wizardp(me) && me->query_temp("hs/jobji"))
		return "�㲻�ܹ�˵ѽ������������ɼ����ҿ�����\n";

	if (!wizardp(me) && (int)me->query("combat_exp") < 100000)
		return "���书δ�ɣ���ôΣ�յ������Ǳ����ˣ�\n";

	if (me->query("job_name") == "�Ͷ�����" && !wizardp(me))
		return "����û����˵�ж���Ϊ�����գ����Լ�ȥ��ϰ�书ȥ�ɣ�";

	if(!wizardp(me) && me->query_condition("job_busy"))
		return "��������æ�������������أ�";

	if(me->query_temp("quest/busy")) //added by tangfeng ��quest��ͻ
		return "����������û�и���������㻹���ȴ����������������˵�ɡ�";
    if ( me->query_condition("job_busy")){
                if (me->query("job_name")=="�Ͷ�����")
                  return "������ʱ��û�й�������ȥ����";
                if( me->query("job_name"))
                  return "�������"+me->query("job_name")+"���񣬻�������Ϣһ��ɡ�";
               return "����æ�ű�������أ��Ȼ�������";
        }

	ob = new(__DIR__"obj/ling");
	ob->set("ever_owner",getuid(me));
	me->set_temp("hs/jobji",1);
	command("nod "+me->query("id"));
	ob->move(me);
	ob->set_temp("hsjob", name1);
	me->apply_condition("hs_job", 30 + random(5));
	me->apply_condition("job_busy", 30);
	me->set_temp("hs_time", uptime());
	tell_object(me, "����Ⱥ������һ�����ơ�\n");
	return "��˵���ڻ�ɽ������������һЩ������ɧ�Ű��գ���ȥѲ��һ�£��������˲�������\n";
}

string ask_zhengqi()
{
	mapping fam;
	object me, ob;
	int shen, exp, i;
	me = this_player();
	ob = this_object();
	shen = (int)me->query("shen", 1);
	exp = (int)me->query("combat_exp", 1);
	i = (shen - exp);
	fam = me->query("family");

	if (!fam || fam["family_name"] !="��ɽ��")
		return RANK_D->query_respect(me)+"�뱾��������������֪�˻��Ӻ�̸��\n";
	if( i < 1000 )
		return "�������֮����������ν���ָ�������������\n";
	if( (int)me->query_skill("zhengqi-jue", 1) < 150 )
		return "���������δ����򣬿������޷�ָ���㡣\n";
	if( (int)me->query_skill("zhengqi-jue", 1) >= 200 )
		return "����������ѵ���򣬿������޷�ָ���㡣";
	if( (int)me->query("jing", 1) < 100 )
		return "����������״��̫���ˣ����޷������������ľ���֮����\n";
	if( (int)me->query("potential", 1) < 2 )
		return "������Ǳ�ܲ��㣬���޷�ָ���������������\n";
	me->improve_skill("zhengqi-jue", 100 + random(100));
	me->add("shen", -1000);
	me->add("potential", -1);
	me->receive_damage("jing", random(100));
	tell_object(me, HIC"��е����м���������������\n"NOR);
	return  "�ðɣ���Ȼ�����������������Ҿ�ָ����һ�¡�\n" ;
}

string ask_me2()
{
	return "��������أ�";
}

int accept_object(object me, object ling)
{
	object name1;
	int getshen, total_job_times, done,gold,gold2,total_job_times2, tb ;
	int i,j;
	name1 = me->query("id");

	if( ling->query("id") != "ling pai")
		return notify_fail("����Ⱥ˵��������ѽ����ɽ�ɾ�Ȼ������������ƭ�ӣ�\n");
	if( ling->query_temp("mmr") != name1 && !wizardp(me)){
		command("hmm "+ me->query("id"));
		me->add("shen", -(int)me->query("job_time/��ɽ",1));
		me->delete_temp("hs/jobji");
		me->delete_temp("hs/have");
		me->delete_temp("hs/power");
		me->delete_temp("hs/robot");
		call_out("destroying", 1, ling);
		return notify_fail("����Ⱥ˵��������ô��ôû�ã�û��ȥ�ҵ�������\n");
	}
	if( ling->query_temp("hsjob") != name1 && !wizardp(me)) {
		command("hmm "+ me->query("id"));
		me->add("shen", -(int)me->query("job_time/��ɽ",1) * 5);
		me->delete_temp("hs/jobji");
		me->delete_temp("hs/have");
		me->delete_temp("hs/power");
		me->delete_temp("hs/robot");
		call_out("destroying", 1, ling);
		return notify_fail("����Ⱥ˵���������������ô��\n");
	}
	done = (int)ling->query_temp("done", 1);
	if( done < 2 && !(done==1 && me->query_temp("hs/robot")) )
		return notify_fail("����Ⱥ˵�����㻹û���ʦ���������ء�\n");
	if ( !me->query_temp("hs/jobji") && !wizardp(me)){
		command("hmm "+ me->query("id"));
		me->add("shen", -(int)me->query("job_time/��ɽ",1) * 5);
		me->delete_temp("hs/jobji");
		me->delete_temp("hs/have");
		me->delete_temp("hs/power");
		me->delete_temp("hs/robot");
		call_out("destroying", 1, ling);
		return notify_fail("����Ⱥ˵����������ƴ�����͵���ģ�\n");
	}
	if ( !me->query_condition("hs_job") && !wizardp(me)){
		command("hmm "+ me->query("id"));
		me->add("shen", -(int)me->query("job_time/��ɽ",1) * 5);
		me->delete_temp("hs/jobji");
		me->delete_temp("hs/have");
		me->delete_temp("hs/power");
		me->delete_temp("hs/robot");
		call_out("destroying", 1, ling);
		return notify_fail("����Ⱥ˵��������ôȥ����ô��ʱ�䣿\n");
	}
	write("����Ⱥ���˿�������ơ�\n", me);
	command("thumb "+ me->query("id"));
	command("say ����" + RANK_D->query_respect(me) + "�պ�������£����кñ���\n");
    getshen = 1;
	if( me->query("family") && me->query("family/family_name") =="�һ���") getshen = 0;


   if(done!=2)
       TASKREWARD_D->get_reward(me,"��ɽ",getshen,0,0,random(2)-1,0,0,0,this_object());
   
   else
   {
       command("wa2 "+ me->query("id"));	   
       TASKREWARD_D->get_reward(me,"��ɽ",getshen,0,0,2+random(2),0,0,0,this_object());	
   }

	me->delete_temp("hs_time");
	me->clear_condition("hs_job");
	me->clear_condition("job_busy");
	me->set("job_name","�Ͷ�����");
              gold= 2000+random(1000);
      
        gold2=gold/5000+random(gold/5000);
              me->add("balance", gold);

	me->delete_temp("hs/jobji");
	me->delete_temp("hs/have");
	me->delete_temp("hs/power");
	me->delete_temp("hs/robot");
	me->delete_temp("mb");
	call_out("destroying", 1, ling);
//������ݱ��
      j = 25;
      if(me->query("m-card-vip")) j =  23;
      if(me->query("y-card-vip")) j =  20;
      if(me->query("buyvip"))     j =  18;


//edit by sohu
	// ������ quest ����
	// ����ֵ���� 10M �� ��ɽ�����ţ�ؤ�������������� 4000
	// ��ɽ�����ţ�ؤ�����֮��Ϊ 50 �ı���
	// ��Ե���������= 28
	// me->query("mianbi") < me->query("mianbi")/100000 + 1
	// by mxzhao 2004/05/07
	total_job_times = me->query("job_time/��ɽ") + me->query("job_time/����") + me->query("job_time/ؤ��");
	total_job_times2 = me->query("job_time/��ɽ") + me->query("job_time/�䵱");
	if (random(me->query("job_time/��ɽ")) >40000
		&& random(me->query("job_time/����")) >40000
		&& random(j)==7
		&& me->query("int")>40 //������������int���Ϸ�������ʾ
        &&( (me->query_temp("sj_credit/quest/hs/jiujian")&& random(me->query("kar")) >= 28 )|| random(me->query("kar")) > 28) //�޸�֮��
		&&( random(me->query("job_time/ؤ��")) >1000 || random(me->query("combat_exp"))>12000000 )
		&& random(me->query("combat_exp"))>10000000
		&& !me->query("fengset")
		&& !me->query_temp("mb")
       // && !me->query("quest/hsjf/fengyi4_time")
		&& (me->query("mianbi") < me->query("combat_exp")/1000 + 1)
		&& me->query("family/family_name")=="��ɽ��"
		&& total_job_times % 50 == 0 ) 
    	{
		    me->set_temp("mb", time());
		    me->add("mianbi", 1);
		    log_file("quest/jiujian",sprintf("%8s%-10s��%4d�λ�ɽ����ʱ����˼������ڣ����ţ�%4d��ؤ��%4d������%2d���Σ�%d��\n",
			me->name(1),"("+capitalize(me->query("id"))+")",me->query("job_time/��ɽ"), me->query("job_time/����"),
			me->query("job_time/ؤ��"), me->query("kar"), me->query("mianbi")),me);
		    command("say "+me->query("name")+"��ɱ�˲��ٶ��ˣ�δ��ɱ�����ز�����˼���������ڰɡ�\n");
     	}
     /*      
	  else if (wizardp(me)||random(me->query("job_time/��ɽ")) >4000
		&&( random(me->query("job_time/�䵱")) >4000 && random(me->query("combat_exp"))>8000000 )
        && random(me->query("kar")) >= 25

		&& !me->query_temp("mz_entrance")
		&& !me->query("quest/xxdf/pass")
		&& random(10)<5
		&& me->query("family/family_name")=="�������"
		&& total_job_times2 % 50 == 0 ) 
	{
		me->set_temp("mz_entrance", 1);
		command("say "+me->query("name")+"����˵ħ�̽��������ں����������ף���ȥ����ɱ�ˣ��Ҿ��������������ɡ�\n");
		log_file("quest/xixing",sprintf("%8s%-10s��ɽ����ʱ��ȥ÷ׯ����ɽ��%4d���䵱��%4d������%2d��\n",
			me->name(1),"("+capitalize(me->query("id"))+")",me->query("job_time/��ɽ"), 
			me->query("job_time/�䵱"), me->query("kar")),me);
	}
	*/
	
	return 1;
}

string ask_zixia()
{
	mapping fam;
	object me;
	me = this_player();
	fam = me->query("family");

	if (!fam || fam["family_name"] !="��ɽ��")
		return RANK_D->query_respect(me)+"�뱾��������������֪�˻��Ӻ�̸��";
	if((int)me->query_skill("zhengqi-jue", 1) < 200 )
		return "���������δ��������ھ�������ϼ�ؼ���δ��Ϊʱ���硣";
	if((int)me->query_skill("huashan-qigong", 1) < 350 )
		return "��Ļ�ɽ����δ��������ھ�������ϼ�ؼ���δ��Ϊʱ���硣";

	if(me->query_temp("quest/huashan/zixia4"))
	{
	  me->delete_temp("quest/huashan/zixia4");
	  me->set_temp("quest/huashan/zixia5",1);   
	  return "����Ⱥ��ɫ����������ʶ��˵������������ɺ��Ѿͷ...!�ߣ�һ����ɽ�ڲ������ڹ�������˭�أ�";
	  }

	me->set_temp("hs/askzixia",1);
	return  "��ϼ�ؼ����һ�ɽ������ǰ��ʱ�䲻֪Ϊ�����䲻���������ѵ������û�ɽ�ɳ����������ɣ�" ;
}

string ask_fengyi()
{
	mapping fam;
	object me;
	me = this_player();
	fam = me->query("family");

	if (!fam || fam["family_name"] !="��ɽ��")
		return RANK_D->query_respect(me)+"�뱾��������������֪�˻��Ӻ�̸��";
	if((int)me->query_skill("zhengqi-jue", 1) < 200 )
		return "���������δ��������ھ������з����ǣ�δ��Ϊʱ���硣";
	if((int)me->query_skill("huashan-qigong", 1) < 350 )
		return "��Ļ�ɽ����δ��������ھ������з����ǣ�δ��Ϊʱ���硣";
	if((int)me->query_skill("huashan-jianfa", 1) < 350 )
		return "��Ļ�ɽ����δ��������ھ����ʡ��з����ǡ���δ��Ϊʱ���硣";
	if (me->query("quest/hsjf/fengyi4/time")=="pass") return "���Ѿ��⿪���з����ǡ�\n";
	if( (time() - (int)me->query("quest/hsjf/fengyi4/time"))<86400)		
     	  return "������Ҳ̫�ڿ���Ү������ȥ��Ϣһ�°ɡ�\n";
	if(me->query("quest/hsjf/fengyi4")=="pass")
	{
	  command("consider "+me->query("id"));
	  return "����Ⱥ��ɫ������˵�������⽣���Ǵ�������˵���ģ�����ô����û��������\n";
      }
	me->set_temp("hs/askyuefy4",1);
	me->set_temp("hssb/juejiasked",1);
	message_vision(HIC"����Ⱥ��̾һ�������������������ħ��ʮ����Χ����ɽ��һ����սʹ��������ǰ���㶼�������ܶ��似ʧ�������ǿ�ϧ��\n"NOR,me);
	return  "�з����������һ�ɽ��������ɱ��֮һ����ϧ����ȴʧ���ˣ���������������У����Ե�˼����ȥ�úò���һ����\n�����ܲ��������ΪʦҲ���Ǹ��ˡ��һ�ɽ�ֽ���һӢ�š�\n" ;
}
string ask_fail()
{
	object me,ling;
	me = this_player();
	ling = present("ling pai", me);
	if(! me->query_temp("hs/jobji"))
		return "����û������񣬺�νʧ�ܰ���";
	if( ling && ling->query_temp("hsjob") == me->query("id"))
		destruct(ling);
	me->delete_temp("hs/jobji");
	me->delete_temp("hs/have");
	me->delete_temp("hs/power");
	me->delete_temp("hs/robot");
	me->clear_condition("hs_job");
	me->apply_condition("job_busy", 3+random(4));
	me->add("combat_exp", -(20+random(10)));
	return "��Ȼ��ˣ�Ҳ������ǿ����������°ɡ�";
}

void destroying(object ling)
{
	if (ling) destruct(ling);
}
void die()
{
	object ob;
	if (!query_temp("living"))
	{
		ob = new("/d/huashan/npc/yuebuqun");
		ob->move("/d/huashan/zhengqi");
	}
	::die();
}

int prevent_learn(object ob, string skill)
{
	if (skill == "zixia-gong")
		return 1;
	if (skill=="ziyin-yin"||skill=="zhengqi-jue")
	{
		write("���ֹ���ֻ�ܿ����˴����в������ã����ʦ�������ѧ��ʲô?\n");
		return 1;
	}
	return 0;
}

string ask_jianzong()
{
	  object me=this_player();
      if (me->query("family/family_name")!="��ɽ��" )
         return "�㲻�ǻ�ɽ���ӣ�������������⣬��Ҫ��Ϊ��";
      if (me->query("quest/huashan")=="����" )
         return "���Ѿ��ǽ��ڵ��ӣ����ѱ���������ɽ�����˺�Ϊ��";
      if (!me->query_temp("jianzong/askning"))
         return "���ǴӺδ���˵��������µģ�";
      command("sigh "+me->query("id"));
      command("say �������ں����ڱ���һ�ң�������Ϊ�������ͣ����±����ڽ���֮�֡�\n");
      command("say �������ַ���Խ��Խ�������γ����ɴ��֮�ƣ������ڵ�����Ů��һս��\n");
      command("say ˫��һ���Ƚ������ֱ˴����˲��٣�������ܣ�����ɽ��ʵ��Ҳ����\n");
      command("say ��ʦүүƾ����ϼ�����˽�����λ���ϣ�һս��Ǭ�����������������ڵĻ�ɽ�ɣ�\n");
      message_vision(HIR"����Ⱥһ��˵�����£�������Ȼ����Ȼ���Լ����½��ƿ�����$N�ȵ���"NOR,me);
      command("say �����Ϊʦ��ʱ���µ��˿ڣ�Ҫ���ǵ�ʱΪʦ�����С���н�����ԣ��ٺ�...��\n");
      command("say �һ�ɽ�����������⽣�ں�����֮�֣��������Ǹ٣���������Ŀ���վٷ���Ŀ�š�");
      command("look "+me->query("id"));
      command("say �����ǻ��������Ŀ֮�֣����Ѿ�����ħ�����ݹ�Ϊʦ��������\n");
      me->delete_temp("jianzong/askning");
      me->set_temp("jianzong/askyue",1);
      return "����Ⱥ�ƺ�������һ���������£������˼֮�С�\n\n\n��������Ƶ�̾������������Ů��һս���ǲ��ң����������ż�����\n";
}

string ask_hssb()
{
	  object me=this_player();
	  if (me->query("family/family_name")!="��ɽ��" )
         return "�㲻�ǻ�ɽ���ӣ�������������⣬��Ҫ��Ϊ��";
      if (me->query("quest/huashan")=="����" )
         return "���Ѿ��ǽ��ڵ��ӣ����ѱ���������ɽ�����˺�Ϊ��";
      if (me->query("quest/hs/hssb/pass"))
         return "�㲻���Ѿ���������ɽʯ�ڵİ�����ô�����������ʲô��\n";
	  if (me->query_skill("huashan-jianfa",1)<450)
	     return "�㻪ɽ��������450��ȥ��Ҳ�����ˡ�\n";

	  if (time()-me->query("quest/hs/hssb/time")<86400)
         return "������̫�ڿ��˵��ˣ���\n";
	  
	  if (me->query_skill("huashan-jianfa",1)<450)
         return "�㻪ɽ��������450��ȥ�˻�ɽʯ��Ҳ�������ˡ�\n";
	  command("sigh ");
	  command("say ˵������£����ò�˵�³��������ˡ�\n");
	  command("say ���Ȼ��������⣬Ӧ�����Ѿ���˵��ʮ����Χ����ɽ֮�ۡ�\n");
	  command("say �������Ҳ����ʦ��˵�����˫��ս���ļ�Ϊ���ҡ�\n");
	  command("say ��ɽ����ɽ����ɽ����ɽ��̩ɽ��λ�����뼯��ɽ����ħ��ʮ���Ͻ���һ����ս��\n");
	  command("say ������������������ʤ�������գ����ˣ��һ�ɽ�ɵ���������������������ħ��ȴһ�겻��\n");
	  command("say �ص���ڻ�ɽ��������ʦ��˵�����ں�ɽ���������ҵ�ʱ��С���в�֪���顣\n");
	  command("say ���Ȼ������������£�ʦ���ҾͰ�����¸���˵˵���ұ����̳���ʦ��ѵ������ħ�̡�\n");
	  me->set_temp("hssb/juejiasked",1);
	  return "";

}