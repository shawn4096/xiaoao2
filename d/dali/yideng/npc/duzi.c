// ���� by River@SJ 2002.6.5

inherit NPC;
#include <ansi.h>
inherit F_MASTER;

string ask_me();
string ask_question();
string ask_yiyangshu();
string ask_sanyinguan();
string ask_qingliang();

void create()
{
	set_name("����", ({ "shu sheng",  "zhu ziliu", "zhu","shu", "sheng" }) );
	set("long", "����ͷ����ң���ֻ��۵��ȣ����һ����ڵĳ��룬ȷ�Ǹ���ѧ����ģ����\n"
	+"����һ�ƴ�ʦ�Ĵ������������һ���йٱ����õĳ����뻯��\n");
	//set("title",HIC"����"NOR);
	set("gender", "����" );
	set("age", 45);
	set("str", 25);
	set("con", 25);
	set("dex", 30);
	set("int", 40);
	set("per", 28);
	set("unique", 1);
	set("attitude", "friendly");

	set("max_qi", 25000);
	set("max_jing", 5800);
	set("eff_jingli", 5600);
	set("neili", 12000);
	set("qi", 25000);
	set("jingli", 5600);
	set("max_neili", 12000);
	set("jiali", 200);

	set("combat_exp", 6500000);
	set("score", 5000);

	set_skill("parry", 400);
	set_skill("dodge", 400);
	set_skill("force", 400);
	set_skill("brush", 450);
	set_skill("sword", 400);
	set_skill("literate", 400);
	set_skill("qiantian-yiyang", 400);
	set_skill("yingou-bifa", 450);
	set_skill("duanjia-jianfa", 400);
	set_skill("tianlong-xiang", 400);
	set_skill("finger", 400);
	set_skill("yiyang-zhi", 400);
	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "yingou-bifa");
	map_skill("force", "qiantian-yiyang");
	map_skill("finger", "yiyang-zhi");
	map_skill("sword","duanjia-jianfa");
	map_skill("brush","yingou-bifa");

	prepare_skill("finger","yiyang-zhi");
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
				(: exert_function, "yiyang" :),
                (: perform_action, "brush.caoshu" :),
				(: perform_action, "brush.kaishu" :),
				(: perform_action, "brush.yiyangshu" :),
        	    (: perform_action, "brush.shiguwen" :),        
	    }));
	set("inquiry", ([
		"һ�ƴ�ʦ" : (: ask_me :),
		"��Ŀ" : (: ask_question :),
		"һ����ָ" : (: ask_yiyangshu :),
		"�����" : (: ask_sanyinguan :),
		"�����Ⱦ���" : (: ask_qingliang :),

	]));
	create_family("������", 13, "�׼ҵ���");
	setup();

	carry_object(BINGQI_D("panguanbi"))->wield();
	carry_object(ARMOR_D("b_cloth"))->wear();
	carry_object(ARMOR_D("caoxie"))->wear();
}

void init()
{
	::init();
	add_action("do_answer", "answer");
	add_action("do_jiaoliang", "jiaoliang");

}

string ask_me()
{
	object me = this_player();

	if ( me->query_temp("yideng/shusheng_pass"))
		return "��λ"+RANK_D->query_respect(me)+"����ʦ������ǰ�治Զ����ʯ���";

	if ( me->query_temp("yideng/ask_shusheng"))
		return "��ɻش�ĳ��ҵ����⣿";

	me->set_temp("yideng/ask_shusheng", 1);

	return "�ҳ�������Ŀ�����㣬���ǿ��ó����Ǿ�����ȥ����ʦ��������\n"+
		"һ�����У�ֻ����"+RANK_D->query_respect(me)+"��ԭ·��ȥ�ˡ�";
}

string ask_question()
{
	object me = this_player();

	if ( me->query_temp("yideng/shusheng_pass"))
		return "��λ"+RANK_D->query_respect(me)+"����ʦ������ǰ�治Զ����ʯ���";

	if ( ! me->query_temp("yideng/ask_shusheng"))
		return "��λ"+RANK_D->query_respect(me)+"������Ŀ������";

	if ( me->query_temp("yideng/quest_wait"))
		return "��λ"+RANK_D->query_respect(me)+"���ܴ���ҵ���Ŀ��";

	me->set_temp("yideng/quest_one", 1);
	me->set_temp("yideng/quest_wait", 1);
	return "������һ��ʫ��˵�������³������������ĸ��ֶ����㵹�²¿���\n\n"
		"\t\t�����̼����оã�һ��ʮ��ĥ���֡�\n"+
		"\t\t�ӻ�ͷ��һ֦�ᣬ��й���Ī¶�ڡ�\n"+
		"\t\tһ�����۴��綷��ȴ�ڰ봲�����С�\n"+
		"\t\t����ֱ���ҹڹ飬������Ŀ��֪��";
}
//�����
string ask_sanyinguan()
{
	object me = this_player();

	if ( !me->query_temp("qls/askjiuwen"))
		return "�Ҳ���ʶ�㣬��λ"+RANK_D->query_respect(me)+"������Ե�޹�����������\n";

	command("say ��Ȼ�������ص��ӣ��������ʿί�ж������Ҿ͸���������£�\n");
	command("say �ұ���������֧����۵��ӣ�������ʦһ�ƴ�ʦ���̷�������\n");
	me->delete_temp("qls/askjiuwen");
	me->set_temp("qls/askzhu", 1);
	return "�������̡�\n\n";
}
//��������
string ask_qingliang()
{
	object me = this_player();

	if ( !me->query_temp("qls/askzhu"))
		return "�Ҳ���ʶ�㣬��λ"+RANK_D->query_respect(me)+"������Ե�޹�����������\n";
	
	command("say ���Ȼ��ѧ�������ȣ��Ҿ��ȿ��Ͽ������������");
	command("say �������Ҵ���Ҿ�ָ����һ�������򣬻���ԭ·���أ�\n");
	message_vision(HIY"���׼�����˾�����"+HIR"jiaoliang"+"\n"NOR,me);

	me->delete_temp("qls/askzhu");
	me->set_temp("qls/askjueji", 1);
	return "��������,Ը����ǿ��\n\n";
}

int do_jiaoliang()
{
	object me, ob, weapon, weapon1;

	me = this_player();
	ob = this_object();

	weapon1 = ob->query_temp("weapon");

	if( !me->query_temp("qls/askjueji") ) return notify_fail("��Ҫ��ʲô��\n");

	if( me->is_busy() || me->is_fighting() ) return notify_fail("����æ���ء�\n");

	if( ob->is_busy() || ob->is_fighting() ) return notify_fail(ob->name()+"��æ���ء�\n");

	if (time()-me->query("quest/kl/qls/time")<86400)
	{
		command("say ������̫Ƶ���ˣ����е����ˣ�\n");
		return notify_fail("��������������㣡\n");
	}
	if( me->query("qi") < me->query("max_qi")*9/10 )
		return notify_fail("������״̬���ѣ����ǵȻ�����̰ɣ�\n");

	if( me->query("eff_qi") < me->query("max_qi")/2 )
		return notify_fail("�����������������ǵȻ�����̰ɣ�\n");
	

		me->start_busy(1);
		message_vision(CYN"$N����$n�Ϲ���˵����������ʦ��ָ��"+RANK_D->query_self(me)+"��������Ҫ������\n"NOR, me, ob);
		me->delete_temp("qls/askjueji");
		
		me->set("quest/kl/qls/time", time());
		me->set("quest/kl/qls/exp", me->query("combat_exp"));

		ob->set("neili", query("max_neili")*2 );
		ob->set("jingli", query("eff_jingli")*2 );
		message_vision(HIW"$nĬ��������Ҫ������ʱ�ʷ��ݺᣬշת��ϣ����������ȡ�������򡱾�������$N�������ֲ�����"NOR, me, ob);

		COMBAT_D->do_attack(ob, me, weapon, 1);
		COMBAT_D->do_attack(ob, me, weapon, 1);
		COMBAT_D->do_attack(ob, me, weapon, 1);
		
		COMBAT_D->do_attack(ob, me, 0, 1);

		 COMBAT_D->do_attack(ob, me, weapon, 1);
			COMBAT_D->do_attack(ob, me, weapon, 1);
		
		COMBAT_D->do_attack(ob, me, 0, 1);

		 COMBAT_D->do_attack(ob, me, weapon, 1);
			COMBAT_D->do_attack(ob, me, weapon, 1);

		if( me->query("qi") < me->query("max_qi")*1/20 ) {
			message_vision(CYN"$n�ǳ�ʧ���Ķ�$N˵������"+me->name()+"�����书δ�ɣ����ǵ����û�����˵����\n"NOR, me, ob);
			me->start_busy(1);
			me->set_temp("marks/ʧ��", 1);
			return 1;
		}
		
		message_vision(CYN"\n$n�����Ǳ���������$N������˵�ţ���"+me->name()+"�����Լ�������ĥ������ʹ�õĽ����ɣ���\n"NOR, me, ob);
		message_vision(HIY"\n$Nƴ���ػ����Ÿղŵ���������ʼ����˼����.........\n", me);
		
			if( random(me->query("kar")) > 26) {	// �����Դ
			message_vision(HIW"$NͻȻ��׽ס����˲���һĻ�����������һ��̣�һ���գ������鶯���������硣���������������������Ⱦ��������С�\n", me);
			tell_object(me, BYEL"��ϲ�㣬����" + NATURE_D->game_time() + "�����������������Ҫ����\n"NOR);
			command("say ��Ȼ�����ʿ��������Ҫ�����书��������Ұ����ž��մ������أ�\n");
			command("say �ҵ�����ʦ֮ǰҲ���������ž���ʧ������д��һ���ָ����������鷿�У���ȥ���ҿ������Ƿ����ҵ���\n");
			me->set("quest/kl/qls/pass", 1);

		} else {
			message_vision(HIC"$Nҡ��ҡͷ�������������Ǻ����ѵġ���˵�գ������̾�˿�����\n", me);
			me->set_temp("marks/ʧ��", 1);
		}
	me->delete_temp("qls");

	return 1;
}
int do_answer(string arg)
{
	object duzi;
	object me = this_player();

	if ( ! arg ) return 0;

	if ( !me->query_temp("yideng/quest_one")
	&& !me->query_temp("yideng/quest_two")
	&& !me->query_temp("yideng/quest_three")) return 0;

	if ( me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ء�\n");

	if ( me->query_temp("yideng/quest_one") && arg == "��δ״Ԫ"){
		me->delete_temp("yideng");
		message_vision(CYN"$N˵������������������һ����һ��һ����ʮ�����Ǹ��������֡����ӡ�����\n"+
			"�Ӻᡢ��ȥ���ڡ����Ǹ���δ���֡�����������ּӡ��󡯼�һ�㣬�Ǹ���״��\n"+
			"�֡����ꡯ�ҹڣ��Ǹ���Ԫ���֡���δ״Ԫ��ʧ��ʧ����ԭ����λ��δ�Ƶ�״\n"+
			"Ԫү����\n\n"NOR, me);
		command("smile "+ me->query("id"));
		command("say �úã���Ȼ������һ�⣬����һ����������"+RANK_D->query_respect(me)+"�Զԡ�\n\n"
			"\t\t�����鵣�ǧ�ַ�ҡ�۵��ȡ�");
		me->set_temp("yideng/quest_two", 1);
		me->set_temp("yideng/ask_shusheng", 1);
		me->set_temp("yideng/quest_wait", 1);
		return 1;
	}
	if ( me->query_temp("yideng/quest_two") && arg == "˪���Ҷ�����Ź����ң��"){
		me->delete_temp("yideng");
		message_vision(CYN"$N��Ŀ�Ĺˣ�ֻ������ƽ������һ��СС��Ժ����ǰ��һ����������ʱ���½�\n"+
				"������ɽ�纮����Ҷ��Ȼ���˴�룬����һ����Ц�������ã��ҵ������ǣ�˪\n"+
				"���Ҷ�����Ź����ң����\n\n"NOR, me);
		command("haha");
		command("say �������������̹�������������֮����");
		command("say �һ���һ������"+RANK_D->query_respect(me)+"�Ը�������\n\n"
			"\t\t��ɪ���ã��˴���һ��ͷ�档");
		me->set_temp("yideng/quest_three", 1);
		me->set_temp("yideng/ask_shusheng", 1);
		me->set_temp("yideng/quest_wait", 1);
		return 1;
	}
	if ( me->query_temp("yideng/quest_three") && arg == "�������ˣ���С����Զǳ�"){
		me->delete_temp("yideng");
		message_vision(CYN"$N˵��������һ����һ����Ҫ�����桢�ԡ���������λ���Ҹ������ȣ�������\n"+
				"�ǣ��������ˣ���С����Զǳ�����\n"NOR, me);
	
	//�����Ǹ������¼�������
	
	if (me->query_temp("nqg/askyingok"))
    {
	    if (!objectp(duzi=present("shu sheng",environment(me))))
	    {
			duzi=new("d/dali/yideng/npc/duzi");
			duzi->move(environment(me));
	    }
		command("hehe ");
		command("hehe "+me->query("id"));
		command("say �ش�ĵ�ͦ�ã�����������ô�����Ƶģ���Ȼ��һ����ò��Ȼ�����ӣ�\n");
		command("say ��С�ӣ����治������Ȼ������������߹������治���ף�\n");
		command("say �����֣��������ɣ�");
		tell_object(me,HIR"\n\n\n��������֪������ʲô�裬�������е��йٱ������ȥ��\n"NOR);
		duzi->kill_ob(me);
		me->kill_ob(duzi);
		me->add_busy(1);
		//call_out("check_jiaozi",1,me);
		return 1;
    }
	else{
		message_vision(CYN"\n$N�󾪣�վ������������һ�ӣ���$nһҾ���أ�˵���������°ݷ�������ת\n"+
				"���ݹ�Сȱ�ڣ���������ա���\n", this_object(), me);
		me->set_temp("yideng/shusheng_pass", 1);
		return 1;
	  }		
		
	}
	command("shake");
	return 1;
}

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
	if ((int)ob->query_skill("qiantian-yiyang", 1) < 250 ){
		command("say ��ĳ���Ҳ�����������֮�ˣ��㻹�Ƕ��������Ǭ��һ����250�ɡ�");
		return;
	}
	if ((int)ob->query_skill("force", 1) < 250 ){
		command("say ��ĳ�˲�����������֮�ˣ��㻹�Ƕ�������Ļ����ڹ���250�ɡ�");
		return;
	}
	if ((int)ob->query("shen") < 1000000){
		command("say ������������������ɣ��㲻��1m����������ҡ�");
		return;
	}

	command("say �治���һ�����ӣ���ʦ��һ���书�㶼����֧���ϣ����Ժ��Ҫ�ú������ˡ�\n");
	command("say ��Ȼ��Ե�Ҿ��������ˣ�\n");
	command("haha ");
	command("recruit " + ob->query("id"));
	ob->set("title", "�����µ�ʮ�Ĵ��׼ҵ���");
}

string ask_yiyangshu()
{
	int j,i,k;
	object me = this_player();

	if ( me->query("quest/tls/yiyangshu/pass"))
		return "��λ"+RANK_D->query_respect(me)+"�����Ѿ��⿪һ����ָ�����ҿ�ʲô��Ц��\n";

	
	
	if (!me->query("family")||me->query("family/family_name")!="������")
	{
  	      command("heng "+me->query("id"));
		  return "�㲻���Ҵ�����ӣ���Ϊ�������ѵ��Ǽ�ϸ���ɣ�\n";
    }
	if (me->query_skill("qiantian-yiyang",1)<300)
	{
  	  command("sigh");
  	  command("? "+me->query("id"));
		  return "һ����ָȫƾһ��Ǭ��һ�����������Ǭ��һ����������300�����ʩչ�����Ͻ�Ŭ��ȥ�ɡ�";
    }
	if (me->query_skill("yingou-bifa",1)<300)
	{
  	  command("sigh");
  	  command("? "+me->query("id"));
		  return "��������ʷ���������300�����ʩչ����һ����ָ���Ͻ�Ŭ��ȥ�ɡ���";
    }
	
	if (time()-me->query("quest/tls/yiyangshu/time")<86400)
	{
  	  command("nod "+me->query("id"));
		  return "������Ҳ̫�ڿ��ˣ���������";
    }
    k=random(me->query("kar"));
	j = 20;
      if(me->query("m-card-vip")) j =  16;
      if(me->query("y-card-vip")) j =  12;
      if(me->query("buyvip"))     j =  10;
	i=random(j);
	
	if (me->query("kar")<31
		&& k >26
		&& i<5)
	{
       message_vision(HIC"\n\n$N���ڽ���Ǭ��һ���������鷨�ڻ��ͨ����������һ����ָ�������ʷ�����������\n"NOR,me);
	 
	   log_file("quest/yiyangshu",sprintf("%s(%s) ��������������һ����ָ����Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),k,i,me->query("quest/tls/yiyangshu/fail"),me->query("combat_exp"),me));
	   me->set("quest/tls/yiyangshu/pass",1);
	   command("congra "+me->query("id"));
	   return "��ϲ�������һ����ָ���⡣\n";
	}
	else
	{
		message_vision(HIY"\n\n$N��Ȼ��������˵����һ����ָ���������������ʹ�õľ�������һʱ֮��ȴ��������⡣\n"NOR,me);
		log_file("quest/yiyangshu",sprintf("%8s%-10s���һ����ָ������û�гɹ�������Ŭ������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),k,i,me->query("quest/tls/yiyangshu/fail"),me->query("combat_exp"),me));
		me->add("quest/tls/yiyangshu/fail",1);
		me->set("quest/tls/yiyangshu/time",time());
		return "����һ����ָ����ʧ�ܡ�\n";

	}     
  
}

int prevent_learn(object ob, string skill)
{
	if (skill == "yiyang-zhi"){
		command("һ��ָ�����Ҵ�������֮�����������޴����߲��ö�����\n");
		return 1;
	}
	return 0;
}
/*
int check_jiaozi(object me)
{
	object duzi;
	
	duzi=present("shu sheng",environment(me));
    if (objectp(duzi)&& me->is_fighting(duzi))
    {
		remove_call_out("check_jiaozi");
		call_out("check_jiaozi",2,me);
		return 0;
    }
	if (!objectp(me)) return 0;


	me->set_temp("yideng/shusheng_pass", 1);
	return 1;	

}*/