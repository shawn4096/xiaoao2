// NPC wei.c ΤһЦ
// Modify By River@SJ 99.06
// been job_npc
// Update By lsxk@hsbbs 2007/7/18   ���ӵ�����߽��������

#include <ansi.h>
#include <job_mul.h>

inherit NPC;
inherit F_MASTER;
string *drugs = ({
	MEDICINE_D("sanhuang"),
	MEDICINE_D("huiyang"),
	MEDICINE_D("yuling"),
	MEDICINE_D("yuzhen"),
	MEDICINE_D("tianwang"),
});

string ask_dichuan();
string ask_jueji();

void destroy(object ob);
void create()
{
	set_name("ΤһЦ",({"wei yixiao","wei","yixiao"}));
	set("title","���̻��̷���");
	set("nickname",GRN"��������"NOR);
	set("long", "�������̵��Ĵ󻤷�֮һ������������\n"+
		"����ĸߴ�������ˣ�����һ����Ṧ��\n");
	set("age", 51);
	set("attitude", "peaceful");
	set("shen", -12000);
	set("str", 26);
	set("int", 26);
	set("con", 25);
	set("dex", 45);        

	set("max_qi", 30000);
	set("max_jing", 12000);
	set("eff_jingli", 12000);
	set("jiali", 170);
	set("combat_exp", 6400000);
	set("unique", 1);
	
	set("job_npc",1);

	set_skill("strike",400); 
	set_skill("literate",250);
	set_skill("dodge",500);
	set_skill("force", 400);
	set_skill("piaoyi-shenfa", 500);
	set_skill("hanbing-mianzhang",400);
	set_skill("shenghuo-shengong", 400);
	set_skill("parry", 400);
	map_skill("force", "shenghuo-shengong");
	map_skill("dodge", "piaoyi-shenfa");
	map_skill("strike", "hanbing-mianzhang");
	map_skill("parry", "hanbing-mianzhang");
	prepare_skill("strike","hanbing-mianzhang");
	set("inquiry", ([
		"�մ�����"  : (: ask_dichuan :),
		"�������"  : (: ask_jueji :),

	]));
	create_family("����", 36, "����");
	set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
		(: perform_action, "strike.xixue":),
		(: perform_action, "strike.mianzhang":),
		(: perform_action, "strike.hanbing":),
			(: exert_function, "shenghuo":),
	}));
	setup();
	carry_object("/d/mingjiao/obj/yel-cloth")->wear();
}

void init()
{
	::init();
        add_action("do_kill", "kill");
        add_action("do_kill", "tk");
        add_action("do_kill", "teamkill");
        add_action("do_kill", "hit");
}
string ask_dichuan()
{
	object me=this_player();
	if (me->query("quest/mj/dichuan"))
	{
		command("pat "+me->query("id"));
		command("say ���Ѿ����Ҵ����̵մ������ˣ��úøɰɣ��Ͼ������ǵ�һ��̡�\n");
		me->set("title","�����̵մ�����");
		return "ʥ�������̲���!";
	}else {
		command("angry "+me->query("id"));
		command("say ���Ѿ�Ѳ����ô���˻�û�г��մ����ǲ�����͵����\n");
		command("say �����������������кñ���\n");
		command("say �Ͻ�ȥѲ�߰ɡ�\n");
		return "��Ҫ������������ܣ�Ѳ����ʵ�������顣������\n";
	}


}

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping fam = ob->query("family");
        mapping my_fam = me->query("family");
        if(!fam || fam["family_name"] != "����"){
                command("say "+RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
                return;
        }
        if(fam["master_name"] == "���޼�"){
                command("haha");
                command("say "+RANK_D->query_respect(ob)+"���ǽ����״����ӣ�"+RANK_D->query_self(me)+"����������Ϊͽ��"); 
                return;
        }
        if (fam["generation"] == my_fam["generation"]){
                command("shake");
                command("say "+RANK_D->query_respect(ob)+"�Ѱݹ���ʹΪʦ��"+RANK_D->query_self(me)+"����������Ϊͽ��");
                return;
        }        
        if ((int)ob->query_skill("shenghuo-shengong", 1) < 200) {
                command("say Ҫѧ��Ϊ������书�������и�����ڹ���Ϊ������200����Ҫ�����ҡ�"); 
                command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ����ʥ�����϶��µ㹦��");
                return;
        }        
        if ((int)ob->query_skill("dodge",1) < 200) {
                command("say ��ѧ�ҵ��Ṧ����������һ�����Ṧ����������200����Ҫ�����ҡ�");
                command("say ���Ṧ���棬" + RANK_D->query_respect(ob)+"�Ƿ����ò�����");
                return;
        }
        command("say �ţ����㻹�Ǹ�ѧ����ϣ��Ҿ�������ɣ�");
        command("say ��л������ӣ����������ֵ�һ���ģ�Ϊ�������壬�������̷�����ɡ�");
        command("recruit " + ob->query("id"));
        ob->set("title", GRN"���������������½���"NOR);
}

int accept_object(object who, object ob,object me)
{
   int exp,job,pot,bonus,gold, i, j =0, k, x, p;
	object* ppl;

	me = this_object();
	if(ob->query("name") != "Ѳ����" || ob->query("id") != "xunluo ling") {
		command("? "+who->query("id"));  
		return 0;
	}
	if(ob->query("owner") != who->query("id") && ! wizardp(who)){
		command("say �ߣ������Ǵ���͵���ģ�");
		call_out("destroy", 1, ob);  
		return 1;
	}
	if(!ob->query("task_ok") && ! wizardp(who)){
		command("say �������㻹�����ø�����»�ɡ�");
		command("pat "+who->query("id"));  
		return 0;
	}
	if(!who->query_condition("mj_xunluo") && ! wizardp(who)){
		command("say ��ô��ʱ�䣬�㶼����ȥ�ˣ�");
		command("disapp "+who->query("id"));
		call_out("destroy", 1, ob);  
		return 1;
	}
	command("nod");
	command("say Ը�������������е��Ӷ�����ڷ����ϣ�");
	bonus = who->query_temp("mj/attacker1");
	if(bonus > 7) bonus = 7;
        exp = 1200 + random(200) + bonus * 100;

		exp=exp/2;
			job = who->query("job_time/����");
	if(job< (who->query("job_time/����Ѳ��")+who->query("job_time/��������")) ){
		who->set("job_time/����",(who->query("job_time/����Ѳ��")+who->query("job_time/��������")));
		job = who->query("job_time/����");
	}
	//������ԭ����  ����Ҫ�����
	//job = who->query("job_time/����Ѳ��");
	gold = job/50 + random(job/50);

	if( gold < 1) gold = 1;
	if( gold > 15) gold = 14 + random(3);

	if (who->query("combat_exp") > 2000000)	exp = random(100) + bonus * 50+100;//��΢��һ��
	
	exp = who->add_exp_combat(exp,this_object(),"����Ѳ��");	
	//who->add("job_time/����Ѳ��", 1);
	//GIFT_D->check_count(who,this_object(),"����Ѳ��");
	//who->add("combat_exp", exp);
	
	if (who->query("combat_exp") > 2000000)
		pot = 100 + random(60);
	else
		pot= exp/5 + random(exp/10);

	who->add("potential", pot);
	p = who->query("mingjiao_job");
	if ( p > 0 ) {
		who->add("job_time/����", p);
		who->delete("mingjiao_job");
	}
	who->add("job_time/����", 1);	
	who->delete_temp("mj/attacker1");
	who->delete_temp("mj/over");
	if(who->query("potential") > who->query("max_pot")) 
		who->set("potential", who->query("max_pot"));
	MONEY_D->pay_player(who, gold * 10000);
	message_vision("\n$N����$nһЩ"HIY"�ƽ�"NOR"��\n"NOR,this_object(),who);
	command("whisper "+who->query("id")+" �������ˣ���Щ������ȥ�úÿ��һ���ɡ�");
	job += 1;
	tell_object(who,"���Ѿ�Ϊ�������"+chinese_number(job)+"�ι����ˣ��ٺú�Ŭ���ɡ�\n");
	log_file("job/xunshan",sprintf("%8s%-10s��%4d����������������%4d��Ǳ��%3d�����ھ���%d��\n",
		who->name(1),"("+who->query("id")+")",job,exp,pot,who->query("combat_exp")), who);
	call_out("destroy", 1, ob);
	i = sizeof(ppl);
	//���������Ϊ��Ҫ�⿪ʥ���
	while(i--) {
		//if (userp(ppl[i]) && !wizardp(ppl[i]) && ppl[i]->query("jiuyang/wei"))
		if (userp(ppl[i]) && !wizardp(ppl[i]) && ppl[i]->query("lingfa/wei"))
		j++;
	}
   if ( who->query("combat_exp",1 ) > 2000000 && job > 400) //Update By lsxk ������������������û��ô������skills�ֵ������ˣ����Խ���Ҫ��
		x = job%20;
	else 
		x = job%50;

	if ( wizardp(who))
		tell_object(who,sprintf("x = %d\n", x ));

   if(me->query_temp("sj_credit/quest/mj/shlf")){
       k=20;
       me->delete_temp("sj_credit/quest/shlf");
   }
   else k=30;

// if(!QUEST_D->questing(who,1,0,1)) k=60;
    
	if (random(who->query("job_time/����"))>400 && random(who->query("kar"))>25 && !who->query("quest/mj/dichuan"))
	{
		message_vision(HIC"$N�ٺټ�Ц��������$n˵�������治�����ҿ��õ��˰������˿������ޣ�������ʱ��Ŀ��顣\n�Ž������Ҹ����㣬���Ѿ�Ϊ�Ҵ����̵ĺ��ĵ����е�һԱ��.��\n"NOR,this_object(),who);
		who->set("title","�����̵մ�����");
		who->set("quest/mj/dichuan",1);
	}
	if( random(job) > 400
	&& x == 0
    && random(who->query_int()) >= k
    && random(who->query_dex()) >= k
    && random(who->query("kar")+ who->query("pur")+ who->query("per")) >= 2*k
	//&& j < 100
	&& random(9+j)> j
	&& !who->query("quest/mj/shlf/wei")){
		command("whisper "+who->query("id")+" �������Ŭ��Ϊ���̲����Ϳ๤�������ȥ�Ž�������һ�Σ���Ӧ������Ҫ������Ҫ�����㡣");
		who->set("quest/mj/shlf/wei", 1);
		log_file("quest/shenhuolingfa",sprintf("%8s%-10s���������%s�ε�ʱ�򣬴�ΤһЦ���������й�ʥ����Ĵ��š�\n",
			who->name(1),"("+ capitalize(getuid(who))+")",chinese_number(job)), who);
	}
	return 1;
}

void destroy(object ob)
{
	destruct(ob);
	return;
}

int do_kill(string arg)
{
	object ob,ob2; 
	object me = this_player();
	ob2 = this_object();

	if (!arg) return 0;
	ob = present(arg, environment(me));
	if (ob == this_object() || ob == me) return 0;
	if (!ob || !ob->is_character()) return 0;
        
	if (userp(ob)&& ob->query("family/family_name") == "����") {
		if (me->query("family/family_name") == "����") { 
		        message_vision(ob2->name()+"��$N�ȵ�����Ϊ���̵��ӣ���Ȼɱ�Լ���ͬ�ţ��������㣡\n", me);
                }
                else {
                        message_vision(ob2->name()+"��$N�ȵ����󵨿�ͽ����Ȼ����������Ұ��\n", me);
                        kill_ob(me);
                }
                me->set("vendetta/����", 1);
                return 1;
        }
        return 0;
}


string ask_jueji()
{
	object me,ob;
	int i,j,k; 

	me = this_player();
	if (time()-me->query("quest/mj/pysf/time")<86400)
	{
		//command("say ��");
		return "������̫Ƶ���ˣ��书��ɻ��������ꣿ��\n";
	}
	if (me->query("family/family_name")!="����")
	{
		return "�㲻�����̵��ӣ�������ǲ��ô��\n";
	}


	if (me->query("quest/mj/pysf/pass"))
	{
		me->set("title",HIG"������������"NOR);
		return "���Ѿ��⿪���������Ṧ�����ˣ���\n";
	}
	if (me->query("dex")<33)
	{
		
		return "������������33��ѧ���������似����\n";
	}
	if (me->query_skill("piaoyi-shenfa",1)<500)
	{
		//command("say ��");
		return "���Ʈ��������500��ѧ���������书����\n";
	}

	if (!me->query("quest/mj/dichuan"))
	{
		//command("say ��");
		return "��ǵմ������ܴ�����߼��书����\n";
	}

		command("say ���̸��ֱ����������죬��ɢ�ˣ��Ĵ�������ң���ɵ������㶼���𽭺���\n");
		command("say ÿ���˶��ж��ص��书�����������ı��²��Ǻ������ƶ�����Ʈ������\n");

		command("say ���Ȼ���Ŭ�����ڷܣ��Ҿʹ������㣬�����ܷ�������\n");

	i=random(me->query("kar"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	j=random(j);
	k=me->query("dex");
	if (i>23
	  && j<5
	  && k>30
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 message_vision(HIG"\n$N����Τ������ָ�㣬������ת������ӿȪѨ��Ȼһʹ�����澭������ĩ�Ҿ����Ȼ��ͨ����\n"NOR,me); 
		 message_vision(HIC"\n��Τ������ָ���£����Ȼ���ֻ���ƮȻ���ɣ���Ȼ��������\n"NOR,me); 

         message_vision(HIY"\n$N�������飬��ת��������Щ�¾�������ת��Ϣ��\n�̲�ס���������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N���������������������������Ĵ������������������־����Ṧ�İ��أ���\n"NOR,me); 
		 command("chat* laugh "+me->query("id"));
		 command("chat* thumb "+me->query("id"));
		 command("chat* pat "+me->query("id"));
		 command("chat ��ϲ�����̵���"+me->query("id")+"�޳�Ʈ����������\n");
		 log_file("quest/mjpysf", sprintf("%s(%s) ���Τ�������ͨ�ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ�����������İ��أ��������ֵ��%d,��ǰ���ֵ��%d,��ǰ����ֵ��%d,��ǰ���飺%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/mj/pysf/fail"),
		 i,
		 j,
		 k,
         me->query("combat_exp"),
		 ));

		 me->set("quest/mj/pysf/time",time());
		 me->set("quest/mj/pysf/pass",1);
		 me->set("title",HIG"������������"NOR);
		 return "��������";
     }
	 else {
	     message_vision(HIG"\n$N�����ɥ�����������˵��������������������ǲ��ýⰡ������Ŭ���ɡ���\n"NOR,me); 
		 message_vision(HIY"\n�����������������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/mjpysf", sprintf("%s(%s) ʧ�ܣ������������%d��ʧ�ܣ��������ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/mj/pysf/fail",1),
		 i,
		 j,
		 k,
         me->query("combat_exp"),));        
		 me->add("quest/mj/pysf/fail",1);
		 me->set("quest/mj/pysf/time",time());
		 me->start_busy(2);
		 return "�������㣬�������Ѽ�ȥ�ˣ�\n";
   }
	
}
