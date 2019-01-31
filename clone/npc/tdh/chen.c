// chen.c �½���

inherit NPC;
#include <ansi.h>

string ask_ningxue();

void create()
{
	set_name("�½���", ({ "chen jinnan", "chen", "jinnan" }));
	set("gender", "����");
	set("age", 45);
	set("shen_type", 1);
	set("��ػ�/title","�ܶ���");
	set("title", HIW"��ػ��ܶ���"NOR);
	set("long", "��������ػ��ܶ����½��ϣ���νƽ�������½��ϣ����Ӣ��Ҳ��Ȼ��\n");

	set("str", 35);
	set("int", 35);
	set("con", 35);
	set("dex", 35);
	set("per", 28);

	set("max_qi", 42500);
	set("max_jing", 7500);
	set("neili", 38600);
	set("eff_jingli", 7500);
	set("max_neili", 38600);
	set("jiali", 250);
	set("combat_exp", 15850000);
	set("unique", 1);
	set("no_get", 1);
	set("no_bark", 1);

	set_skill("claw", 550);
	set_skill("dodge", 500);
	set_skill("parry", 500);
	set_skill("force", 500);
	set_skill("ningxue-shenzhua", 550);
	set_skill("literate", 300);
	set_skill("medicine", 150);
	set_skill("xiantian-gong", 500);
	set_skill("shaolin-shenfa", 500);

	map_skill("force", "xiantian-gong");
	map_skill("claw","ningxue-shenzhua");
	map_skill("dodge","shaolin-shenfa");
	map_skill("parry","ningxue-shenzhua");

	prepare_skill("claw", "ningxue-shenzhua");


	set("chat_chance", 50);
	set("chat_msg", ({
		(: random_move :),
	}));

	set("chat_chance_combat", 90);
	set("chat_msg_combat", ({
		(: perform_action, "claw.ningxue":),
		(: perform_action, "claw.shenzhua":),

	}));

	set("inquiry", ([
		"��Ѫ��צ":	(: ask_ningxue :),
	]));
	setup();

	carry_object(ARMOR_D("cloth"))->wear();
	carry_object(ARMOR_D("shoes"))->wear();
	add_money("silver", 10 + random(20));
}

string ask_ningxue()
{
	object ob, me = this_player();
	int j,k,total;
	int time, i, job = me->query("job_time/��ػ�");
	mapping quest;
    total=me->query("str")+me->query("con")+me->query("int")+me->query("dex");
	k=random(me->query("kar"));
	j=20;
	
	 if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
      j=random(j);


	if ( job <= 1000 || ! me->query("quest/ningxue/meet"))
		return "��Ѫ��צ�����������˵�ģ�";

	time = time() - me->query("quest/ningxue/time");
	if ( me->query("quest/ningxue/time") && time < 86400 && !me->query("quest/ningxue/pass"))
		return "�Ҳ��Ǻ���˵�ˣ�����ʱ�޷�ѧ����Ѫ��צô��";

	me->set("quest/ningxue/time", time());

	if ( me->query("con") < 15 )
		return "��Ѫ��צ�Ը�����һ����Ҫ�󣬿����㲢�����ʡ�";

	if ( me->query("dex") < 15 )
		return "��Ѫ��צ������һ����Ҫ�󣬿����㲢�����ʡ�";

	quest = me->query("quest/ningxue");
	
	i = me->query("combat_exp", 1) / 500000;
/*
	if ( quest["fail"] >= i)
		return "���������Ϊ�������ٴγ��ԣ����ǹ���ʱ�������ɡ�";
*/
	if ( quest["pass"]) {
		
		me->set("title",HBRED HIY"��Ѫ��ץ����"NOR);
		me->set("mytitle/quest/ningxuetitle",HBRED HIY"��Ѫ��ץ����"NOR);

		if ( present("ningxue shenzhuapu", me))
			return "����Ѫ��צ�ס�������������ô����������ʲô��";

		if ( me->query_skill("ningxue-shenzhua", 1) < 150 ) {
			ob = new(BOOK_D("ningxue"));
			ob->set("owner", me);
			message_vision("$n����$Nһ��"+ob->name()+"��\n", me, this_object());
			ob->move(me);
			return "�Ȿ����Ѫ��צ�ס������ȥ�о��°ɡ�";
		}
		else
			return "���Ѿ�������������Ѫ��צ����ֻ��Ҫ�ڼ����������ˡ�";
	}
//1/30*1/20
     if ( me->query("kar") < 31
		 && j<2
		 && random(total)>120
		 && random(me->query("int"))>40
		 && k > 28) 
	{
		command("look "+ me->query("id"));
		command("pat "+ me->query("id"));
		ob = new(BOOK_D("ningxue"));
		ob->set("owner", me);
		message_vision("$n����$Nһ��"+ob->name()+"��\n", me, this_object());
		ob->move(me);

		log_file("quest/ningxue",
			sprintf(HIR"%-18sʧ��%-2d�κ�ӳ½��ϴ��õ���Ѫ��צ�ף���ԴֵK��%d�������j��%d����ʵ��Դ����%d���������ԣ�%d����ǰgift����%d��\n"NOR,
				me->name(1)+"("+capitalize(getuid(me))+")", 
				me->query("quest/ningxue/fail"),
				k, 
				j,
				me->query("kar"),
				me->query("int"),
				total
			), me
		);
		me->set("quest/ningxue/pass", 1);
		me->set("title",HBRED HIY"��Ѫ��ץ����"NOR);
		me->set("mytitle/quest/ningxuetitle",HBRED HIY"��Ѫ��ץ����"NOR);
		return "�ţ����������ʲ����ǿ�ѧ����ϣ��Ȿ����Ѫ��צ�ס������ȥ�о��°ɡ�\n";
	}
	else {
		command("pat "+ me->query("id"));
		me->add("quest/ningxue/fail", 1);
		log_file("quest/ningxue",
			sprintf(HIR"%-18s������Ѫ��צʧ��%-2d�Σ���ԴֵK��%d�������j��%d����ʵ��Դ����%d����ǰgift����%d��\n"NOR,
				me->name(1)+"("+capitalize(getuid(me))+")", 
				me->query("quest/ningxue/fail"),
				k, 
				j,
				me->query("kar"),
				total
			), me
		);
		return "��λ"+RANK_D->query_respect(me)+"��������ҪŬ��һ�����У�������״̬��̫�ʺ�ѧϰ��Ѫ��צ��\n";
	}
}
                                                                                                                                                                                                                                                                                                         
