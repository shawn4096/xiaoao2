// dongfang.c ��������
// By River@SJ For kuihua-baodian Quest 2003.1.11

inherit NPC;

//inherit F_MASTER;

#include <ansi.h>

string ask_me();
string ask_rwx();
void create()
{
	object ob;
	set_name("��������", ({ "dongfang bubai", "dongfang", "bubai"}));
	set("long", "����������֮��һλ���춯�أ��������Ĺֽܡ�\n"+
		"�˿�������˺��룬���Ͼ�Ȼʩ��֬�ۣ������Ǽ�����ʽ���в��У�Ů��Ů��\n"+
		"��ɫ֮�����㴩����Ů���ϣ�Ҳ�Ե�̫���ޡ�̫������Щ��\n");

	set("title",HIY"������̽���"NOR);         
	set("nickname", HIR"�ճ����� Ψ�Ҳ���"NOR);
	set("gender", "����");
	set("age", 54);
	set("attitude", "friendly");
	set("str", 20);
	set("int", 35);
	set("con", 30);
	set("dex", 30);
	set("per", 28);
	set("class", "eunuch");
	set("unique", 1);

	set("max_qi", 55000);
	set("max_jing", 10500);
	set("eff_jingli", 8000);
	set("max_neili", 86000);
	set("neili", 86000);
	set("jiali", 200);
	set("combat_exp", 12500000);
	set("shen", -50000);

	set_skill("sword", 550); 
	set_skill("parry", 500);
	set_skill("dodge", 500);
	set_skill("claw", 500);
	set_skill("force", 550);
	set_skill("pixie-jian", 550);        
	set_skill("youming-zhao", 500);
	set_skill("literate", 280);
	set_skill("kuihua-shengong", 550);

	map_skill("sword", "pixie-jian");
	map_skill("parry", "pixie-jian");
	map_skill("dodge", "pixie-jian");
	map_skill("claw", "youming-zhao");
	map_skill("force", "kuihua-shengong");
	prepare_skill("claw", "youming-zhao");

	set("chat_chance_combat", 150);
	set("chat_msg_combat", ({
		(: exert_function, "guimei" :),
		(: perform_action, "sword.cimu" :),
		(: perform_action, "sword.jue" :),
		(: perform_action, "sword.feiying" :),
		(: perform_action, "sword.pixie" :),
	}));
/* ������������
	set_temp("apply/damage", 50);
	set_temp("apply/dodge", 120);
	set_temp("apply/attack", 80);
	set_temp("apply/armor", 170);
	*/
	set_temp("��ڤ", 1);

	set("inquiry", ([
		"��������": (: ask_me :),
		"������": (: ask_rwx :),
	]));

	setup();

	if (clonep()) {
		ob = unew(BOOK_D("kuihua"));
		if (!ob) ob = new("/clone/money/gold");
		ob->move(this_object());
		carry_object(BINGQI_D("xiuhua"))->wield();
		carry_object(ARMOR_D("xiupao2"))->wear();
	}
}
void init()
{
        object me=this_player();
		if (me->query_temp("xinxing/askren"))
        {
			command("heng "+me->query("id"));
			command("say ���������������ģ�");
			command("say ��������ô�����ˣ�����Ϊ�����ã��벻�������վ�����Ҫ�����֮λ������������������������\n");
			
        }
} 

void reset()
{
	object ob;

	if (clonep() && (ob = unew(BOOK_D("kuihua"))))
		ob->move(this_object());
}

string ask_me()
{
	object ob, me = this_player();
	mapping quest;
	int i, time;

	if ( is_busy() || is_fighting())
	 	return "��û��������æ��ô��";

	if ( me->query("gender") == "Ů��")
		return "�����Һ���һ������ΪŮ�����Ǿͺ��ˡ�";

	if ( me->query("int") < 20 )
		return "������Բ��������������䡹���ʺ�����ϰ��";

	if ( me->query("dex") < 15 )
		return "���������䡹����������Ų֮���������ʵ��̫���ˡ�";

	if ( me->query("combat_exp", 1) < 5000000)
		return "���ʵս���黹���������������䡹�����ʺ���������";

	if ( present("kuihua baodian", me))
		return "�ף����������䡹������������ô��������������";

	ob = present("kuihua baodian", this_object());

	if ( ! ob)
		return "Ү�����������䡹���ҷŵ�����ȥ�ˣ�";

	time = time() - me->query("quest/pixie/pxj_time");
	if ( me->query("quest/pixie/pxj_time") && time < 86400 && !wizardp(me))
	 	return "�����ں�æ��û��Ȥ��������¡�";

	quest = me->query("quest/pixie");

	if ( ! quest || ! quest["pxj_passwd"])
	{
		command("grin");	
        ::kill_ob(me);
		return "���������˵�����������䡹�ģ�";
	}

	if ( quest["pass"] ) {
		if ( ob ) {
			ob->set("owner", me);
			ob->move(me);
			return "�ðɣ��Ȿ���������䡹���û�ȥ�ú��о��о���";
		}
		else
			return "��Ҫ�ġ��������䡹�Ѿ������������ˡ�";
	}

	i = me->query("combat_exp", 1) - 4500000;
	i /= 500000;

        if ( me->query("registered")< 3 && quest["fail"] >= i)
	 	return "�����ں�æ��û��Ȥ��������£�";
        if ( quest["fail"] >= i && !me->query("cw_exp") )
	 	return "�����ں�æ��û��Ȥ��������£�";
	me->set_temp("pxj_quest", 1);
	kill_ob(me);
	me->kill_ob(this_object());
	return "��ƾ����"+RANK_D->query_rude(me)+"Ҳ���������ҵġ��������䡹��";
}

string ask_rwx()
{
	object obj,me;
	me = this_player();
	obj=this_object();
	if ( is_busy() || is_fighting())
	 	return "��û��������æ��ô��";

	if (me->query_temp("xixing/askren"))
	 {  
	    kill_ob(me);
	    me->kill_ob(this_object());
	   }
       me->delete_temp("xixing/askren");
	   me->set_temp("xixing/kdf",1);
	  return "��ƾ����"+RANK_D->query_rude(me)+"Ҳ���������������£����У�";
}


void kill_ob(object me)
{	
	command("grin");	
    ::kill_ob(me);
   return;
}


void die()
{
	int total,i,j;
	object me = query_temp("last_damage_from");
	object ob = present("kuihua baodian", this_object());
	
	if (objectp(me)) {

     if (me->query_temp("xixing/kdf")) 
	{
		me->set_temp("xixing/killeddf",1);
		me->delete_temp("xixing/kdf");
		destruct(ob);
	}
	else if (me->query_temp("pxj_quest"))
    {
		if (QUEST_D->questing(me,10,190,0,"kuihua/book"))
			  
                {
			     message_vision("\n", me);
			     command("say ����������Ҳ������Ե֮�ˣ��Ȿ���������䡹�ͽ�����ɡ�");		         
			me->delete_temp("pxj_quest");
			QUEST_D->setmytitle(me,"kuihuatitle",HBMAG+HIG"�����񹦡������Թ�"NOR);			
			ob->set("owner", me);
			ob->move(me);
		}
		else {
			message_vision(CYN"\n$Nŭ�е�������ʹ�����ˣ����Ҳ����õ����������䡹����������������\n"NOR, this_object());
			message_vision("$N���ǡ��������䡹����˫����һ�꣬����������һ��ԭ��ʮ�ֳ¾ɵĲ�ҳ��ʱ������Ƭ��\n\n", this_object());			
			ob->set("name", HIW"�����������Ƭ"NOR);
			ob->move(environment(this_object()));
		}
          
	}
	else destruct(ob);
	}	
	else
	{
		
		destruct(ob);
	}	
	::die();
}

void unconcious()
{
	die();
}
                                                                                              
