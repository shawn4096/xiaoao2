// yinggu.c ���� �������
// created by campsun 2003/12/2
//�Ƿ��ڹ������״̬���ж�Ϊquery_temp("ggs/started") ��������޸ĵ�ʱ��Ҫ�ر�ע�⡣
//LinuX@SJ 2004.2.28


#include <ansi.h>
inherit NPC;

int ask_ggs();
int ask_ggso();
int ask_duan();
int ask_nqg();
int ask_nqgjj();
//int do_answer(string arg);
int do_huida(string arg);
int ask_fox();
int ask_zhou();
int accept_object(object who, object obj);

void create()
{
	seteuid( getuid() );
        set_name("����", ({ "ying gu","ying"}));
        set("nickname",HIW"�������ר��"NOR);
        set("title",HIR"������"NOR);
        set("gender", "Ů��");
        set("age", 35);
        set("long", "���Ǹ��������ƺ��м�����ò��Ů�ӡ�����ȷ��һͷ�׷���ѩ����ֻ�����ﶼ����Թ�͸��ˡ�\n");
        set("attitude", "peaceful");
        set("shen_type", 0);
	    set("no_get","���ö������̫���ˡ�");
        set("str", 30);
        set("int", 35);
        set("con", 30);
        set("dex", 26);
	set("per", 28);
	set("quest/dali/ailao/pass",1);
	
	set("jiali",200);
	set_skill("force", 450);
	set_skill("huntian-qigong", 450);
	set_skill("qiantian-yiyang", 450);
	set_skill("dodge", 450);
	set_skill("niqiu-gong", 450);
	set_skill("parry", 450);
	set_skill("strike", 450);
	set_skill("qingyan-zhang", 450);
	set_skill("sword", 450);
	set_skill("duanjia-jianfa", 450);
	set_skill("cuff", 450);
	set_skill("kongming-quan", 450);
	set_skill("literate",400);
	set_skill("qimen-bagua", 200);
	


	map_skill("force", "qiantian-yiyang");
	map_skill("dodge", "niqiu-gong");
	map_skill("strike", "qingyan-zhang");
	//map_skill("strike", "qingyan-zhang");
	map_skill("parry", "duanjia-jianfa");
	map_skill("sword", "duanjia-jianfa");
	map_skill("cuff", "kongming-quan");
	prepare_skill("strike", "qingyan-zhang");

	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: perform_action, "strike.qingyan" :),
		(: perform_action, "strike.piaomiao" :),
		(: exert_function, "yiyang" :),
		(: exert_function, "liao" :),
	}));

	set("combat_exp", 10500000);
	set("max_qi", 35000);
	set("max_jing", 8000);
	set("neili", 25000);
	set("max_jingli", 8000);
	set("eff_jingli", 8000);
	set("max_neili", 25000);


    set("inquiry", ([
                "rumors" : "�������ô��ô���㰡����֪���ϴ�����ҽ��С����ʲôʱ�����������",
                //"�ܲ�ͨ" : "��˵���������һ����ϣ��ҿ����о������������Ϊ����ȥ������",
                "���Ż�" : "���Ż���ԧ��֯����˫��....",
                "�������" : (: ask_ggs :),
                "��ʼ" 	: (: ask_ggs :),
                "start" : (: ask_ggs :),
                "����" 	: (: ask_ggso :),
                "��Ϣ" 	: (: ask_ggso :),
                "over" 	: (: ask_ggso :),
				//��Ȼ
				"��β���" : (: ask_fox :),
				"�ܲ�ͨ" : (: ask_zhou :),
				//ɱ��
				//"�λ�ү" : (: ask_duan :),
				//"������" : (: ask_nqg :),
				"����������" : (: ask_nqgjj :),
        ]));

        setup();
		carry_object("clone/weapon/bishou")->wield();
        carry_object(ARMOR_D("pink_cloth"))->wear();

}
void init()
{
	add_action("do_huida","answer");

}
//�н�ʷ���ֵ�׽���׽��ס
int ask_fox()
{
	object me=this_player();
	if (me->query_temp("quest/shendiao/��ѩ�����/askheal"))
	{
		command("say ��������Ҫ�����֮Ѫ���������ȥ���ܲ�ͨ������\n");
		command("say ֻҪ�����ˣ��Ҿ͸������֮Ѫ��\n");
		command("say ���������ɺ��������ʯ��٣�\n");
		me->set_temp("quest/shendiao/��ѩ�����/askyingfox",1);
	}else {
		command("��β���������˽�˵ĳ��ƾʲô���㣿\n");
	}
	return 1;

}
//�ҵ�����ͯ�����ȥ׽���겢����������
int ask_zhou()
{
	object me=this_player();
	if (me->query_temp("quest/shendiao/��ѩ�����/zhouok"))
	{
		command("say �������������˵�����������������\n");
		command("say ����������������ԩ�ң����ԩ�ң�����\n");
		command("thank "+me->query("id"));
		command("blush");
		command("say ��Ȼ��Ϊ�Ұ��������£��ҾͰ��������׽�������㡣\n");
		command("say ���β����˺���֮�Ҳ����ɱ�����Ͳɼ�����ͷ�ļ�����Ѫ���ɡ�\n");
		command("say ǰһ���׶Σ��ҽ������������������������С�\n");
		me->set_temp("quest/shendiao/��ѩ�����/yingok",1);
		me->set("quest/shendiao/��ѩ�����/yingok",1);

	}else
	{
		command("say �����ܲ�ͨ���벻������������������\n");
	}
	return 1;

}

int ask_ggs()
{
	object me,ob;
	int this_week = time()/86400/7;
	ob = this_object();
	me = this_player();
	
	
	if (me->query("registered")!=3)
	{
		tell_object(me, "�Բ��𰡣�Ŀǰ�������ֻ�Թ��VIP�û�����ǿ��ѧϰ���ܡ�\n");
		return 1;
	} 
	
	if(!me->query("ggs/last_week") || me->query("ggs/last_week")=="" || me->query("ggs/last_week")!=this_week)
	{
		me->set("ggs/last_week", this_week);
		me->set("ggs/started",0);
		me->set("ggs/start_time","");
		me->set("ggs/over_time","");
		me->set("ggs/left_time",10*3600);
	}

	//For all Bug By Ciwei@SJ
	while(me->query("ggs/left_time")>10*3600)
		me->add("ggs/left_time",-10*3600);

	if(me->query("ggs/left_time") < 1)
	{
		command("say ����Ȼ���ʴϻۣ�����̰������ã�������ð���ˣ�����������ѯ�ʰɡ�");
		return 1;
	}
	if(me->query("ggs/started")==1)
	{
		if(!me->query_temp("ggs/started"))
		{
			tell_object(me, "����Ҫ������Ϣ�������ٿ�ʼʹ�ù��������\n");
		}
		else
		{
			tell_object(me, "�㲻��������ϰ�������������ô���������ץ��ʱ�䡭��\n");
			command("kick " + me->query("id"));
		}
		return 1;
	}
	
	me->set("ggs/started",1); //ʹ��״̬���
	me->set_temp("ggs/started",1); //ʹ��״̬���
	me->set("ggs/start_time",time()); //ʹ��״̬���
	
	me->apply_condition("guigushu",1); //���condition �����Զ�����
	
	command("say ���������������Щ�꾫���о�������������ܲ��򣬿��Լӱ����ѧϰ�����������");
	command("say ���������������Ԩ���������ÿ�����Ҳ��Ӧ��ʮ��Сʱ�ɡ�");
	command("look " + me->query("id"));
	command("say ������ "+ CHINESE_D->chinese_date(time(),1) + "��");
	command("say �㱾�ܻ�����ʹ�ù������"+CHINESE_D->chinese_time(me->query("ggs/left_time"))+"�����ڿ�ʼ��ʱ�ˡ�");
	log_file( "quest/ggs",sprintf("%s(%s)�ڵ�%d�ܿ�ʼ�������,ʣ:%s.\n",
			me->name(),
			me->query("id"),
			this_week,
			CHINESE_D->chinese_time(me->query("ggs/left_time"))
			));
	
return 1;
}

int ask_ggso()
{
	object me,ob;
	int user_time;
	//int an_hour = 60*60*60;
	int this_week = time()/86400/7;
	ob = this_object();
	me = this_player();
	
	if (me->query("registered")!=3)
	{
		tell_object(me, "�Բ��𰡣�Ŀǰ�������ֻ�Թ��VIP�û�����ǿ��ѧϰ���ܡ�\n");
		return 1;
	}
	if(me->query("ggs/started")!=1)
	{
		command("say ��û�п�ʼ��Ҫ��Ϣ����");
		command("pig " + me->query("id"));
		return 1;
	}
	if(me->query_temp("ggs/started")!=1)
	{
		command("say ���ǲ���û����Ϣ�������ˣ�����ʱ��Ͱ������ϴ�����ʱ����ɡ�");
		me->set("ggs/over_time",FINGER_D->get_last_on(me->query("id")));		
	}
	else
	{	
		me->set("ggs/over_time",time());	
	}
	
	user_time=ABS((int)me->query("ggs/over_time")-(int)me->query("ggs/start_time"));
	command("say �ǰ������ݽ�ϣ�����������ˣ��Ǹ���Ϣ��Ϣ��");
	command("look " + me->query("id"));
	
	command("say ��Ĺ��������ʼʱ���ǣ�" + CHINESE_D->chinese_date((int)me->query("ggs/start_time"),1) + "��");
	command("say             ����ʱ���ǣ�" + CHINESE_D->chinese_date((int)me->query("ggs/over_time"),1) + "��");
	command("say �����һ�������ˣ�" + CHINESE_D->chinese_time(user_time)+"��");
	me->set("ggs/left_time",me->query("ggs/left_time") - user_time);

	log_file( "quest/ggs",sprintf("%s(%s)�ڵ�%d�ܽ���ggs,ʣ:%s,��:%s.\n",
			me->name(),
			me->query("id"),
			this_week,
			CHINESE_D->chinese_time(me->query("ggs/left_time")),
			CHINESE_D->chinese_time(user_time)
			));



	if (me->query("ggs/left_time") < 0 ) //��ֹbug
		me->set("ggs/left_time",0);
		
	if (me->query("ggs/left_time")) 	
		command("say �㱾�ܻ�����ʹ�ù������"+CHINESE_D->chinese_time(me->query("ggs/left_time"))+"��");
	else
		command("say ��Ĺ������ʱ�������ˣ����������ɡ�");
	
	me->set_temp("ggs/started",0);
	me->set("ggs/started",0);
	me->set("ggs/start_time","");
	me->set("ggs/over_time","");	
	
	me->clear_condition("guigushu"); //�����


return 1;	
}

//����
int accept_fight(object ob){
        command("say ��λ"+RANK_D->query_respect(ob)+"���书����������ģ����Ǻö��Σ�");
}
int hit_ob(object ob)
{
        command("say ��λ"+RANK_D->query_respect(ob)+"���书����������ģ����Ǻö��Σ�");
}


void kill_ob(object ob)
{
        ob->remove_killer(this_object());
        remove_killer(ob);
        command("swear");
}

void unconcious()
{
	message_vision(YEL"$NͻȻ���ù��֮����ȫ��������ɫ�ʣ�����ս����֮�ơ�\n"NOR, this_object());
        reincarnate();
        add("str",10); //Խ��Խ�£�^_^
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
        clear_conditions_by_type("poison");
}

void die()
{
        unconcious();
}

//����������

int ask_duan()
{
	command("say �ߣ���������������");
	command("angry ");
	command("say ���Ż���ԧ��֯����˫�ɣ�����δ��ͷ�Ȱף������̲ݣ�����������ԡ���¡�\n");
	command("cry ");
	command("consider ");
	this_player()->set_temp("nqg/askying",1);
	return 1;
}
int ask_nqg()
{
	object me,ob;	
	ob = this_object();
	me = this_player();
	
	if (!me->query_temp("nqg/askying"))
	{
		return notify_fail("���ò�Ը������㣬����̫���ˣ�\n");
	}
	if (me->query_skill("force",1)<450)
		return notify_fail("��Ļ����ڹ�̫����������ȥΪ������������\n\n\n");
	command("say ����������������̶�п��޶��귽��ϰ�ã��˵��������ޱȡ�\n\n\n");
	command("say ��ѧ�����񹦿��ԣ��������Ҫ����ɱһ����ȥ�����ô��\n\n\n");
	command("say ��������񼫣�����ɱ�����Ҿͽ��������񹦡�\n\n\n");
	write(HIG"��������������ɱһ���ˣ���Ը��(yes)���ǲ�Ը��(no)��\n");
	add_action("do_huida","answer");
	return 1; 
}
int do_huida(string arg)
{
	object me=this_player();
	if (!arg) return notify_fail("��ش�ʲô��");
	if (arg=="yes")
	{
		command("say �ðɣ���Ȼ��Ը������ҵ���Դ�أ�һ��ʯ����ɱ��һ���Ϻ���,��ͷ������\n");
		command("say һ·���գ������ĸ����Ӷ��ܻ���ÿһ���˶����Լ��ľ�������ҪС���ˡ���\n");
		me->set_temp("nqg/askyingok",1);
		me->delete_temp("nqg/askying");
		return 1;
	}else if(arg=="no")
	{
		command("say �ðɣ���Ȼ�㲻Ը��ȥɱ�˶����ˣ��Ǿ�����ȥ������ͯ��������������ѧϰ�������񹦣�\n");
		me->delete_temp("nqg/askying");

		return 1;
	}
	
}

int accept_object(object who, object obj)
{
	
	if (who->query_temp("nqg/killyideng")&& obj->query("id")=="shouji"&&obj->query("name")=="һ�ƴ�ʦ���׼�")
	{
		who->delete_temp("nqg/killyideng");
		//���
		who->set("quest/shediao/nqg/over",1);
		tell_object(who,HIY"���ü�����öһ�ƴ�ʦ���׼�����ҧ���гݣ��ֲ�ʤ��ϲ���ƺ�������״̬��\n"NOR);
        command("laugh ");
		command("chat ��������Ҳ�н��죡");
		command("chat �ҿ����ĺ��Ӱ�����ĳ���������㱨���ˣ�");
		command("chat ��л"+who->query("name")+"������ԩ��");

		obj->move(this_object());
		destruct(obj);
		message_vision(HIC"����˳�ִӿڴ����ͳ�һ���𶧸�$n��˵��������ȥ�Ⱦ�ȥ�ɡ�\n"NOR,who);
		who->add("combat_exp",random(500));
		who->add("shen",-2000000);
		new("clone/money/gold")->move(this_object());
		message_vision(HIC"$N�ľ��������ˣ�\n"NOR,who);
		command("give "+who->query("id")+" 1 gold");
		return 1;
	}

}

int ask_nqgjj()
{
	object me,ob;
	int j,i,k;
	ob = this_object();
	me = this_player();
	if (!me->query("quest/shediao/nqg/over") && !me->query("quest/shendiao/��ѩ�����/healover"))
	{
		command("say ��̫���ˣ���Ը������㣬�벻�Ͷ�����˶��ǿɳܵġ�\n");
		return 1;
	}

	if (me->query_skill("force",1)<450)
	{
		command("say ��Ļ����ڹ�̫����������ȥΪ������������\n");
		return 1;
	}
	if (me->query("quest/shediao/nqg/pass"))
	{
  		 command("nod "+me->query("id"));
		 if (me->query_skill("niqiu-gong",1)<450)
		 {
			message_vision(HIC"$N������Ц��$n��̹�����������֪ʶ��\n"NOR,me,this_object());
			me->improve_skill("niqiu-gong",me->query_int());
			return 1;
		 }else
			message_vision(HIC"$n��$N�����˵�����Ҿͽ̵������ˣ�ʣ�µľͿ����Լ�ȥ��ϰ��!\n"NOR,me,this_object());
		 command("say ���Ѿ��������������ž�ѧ���������ʲô��\m");
		 return 1;
    }
	if (time()-me->query("quest/shediao/nqg/time")<86400)
	{
  		command("nod "+me->query("id"));
		command("say ������Ҳ̫�ڿ��ˣ�����������\n");
		return 1;
    }
    j=random(me->query("kar"));
	k=random(25);
	if(me->query("m-card-vip")) k =  20;
    if(me->query("y-card-vip")) k =  18;
    if(me->query("buyvip"))     k =  15;
	
	
	i=random(k);
	if (me->query("kar")<31
		&&j>27
		&&i<2)
	{
       message_vision(HIC"\n\n$N�����õ�ָ���£����ڽ����������ڻ��ͨ��������������������\n"NOR,me);
	 
	   log_file("quest/niqiugong",sprintf("%s(%s) �����ô����������������������Դj��%d�������i��%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),j,i,me->query("quest/shediao/nqg/fail"),me->query("combat_exp"),me));
	   me->set("quest/shediao/nqg/pass",1);
	   me->improve_skill("niqiu-gong",10);
	   command("congra "+me->query("id"));
	   command( "say ��ϲ�����������������!\n");
	   return 1;
	}
	else
	{
		message_vision(HIY"\n\n$N��Ȼ�����ý��������������İ��أ����������ʹ�õľ�������һʱ֮��ȴ��������⡣\n"NOR,me);
		message_vision(HIG"\n\n$N�о��Ͳ�һ�㴰��ֽ���·������ǰ����ȴ������ġ�\n"NOR,me);
		log_file("quest/niqiugong",sprintf("%8s%-10s���ֱ��ţ�������ۣ�����������ʧ�ܣ�����Ŭ������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),j,i,me->query("quest/shediao/nqg/fail"),me->query("combat_exp"),me));
		me->add("quest/shediao/nqg/fail",1);
		me->set("quest/shediao/nqg/time",time());
		command( "say �湻���ģ�����������ʧ��!\n");
	    return 1;
	}
	
}