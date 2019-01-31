//yunzhonghe.c ���к�
// cre by sohu

inherit NPC;
#include <ansi.h>
string ask_duan1();
string ask_duan2();
#define QUESTDIR1 "quest/�����˲�/�貨΢��ƪ/"

int do_kill(object me, object ob);

void create()
{
        set_name("�Ϻ�����", ({ "nanhai eshen", "eshen","yue"}) );
		set("title",HIW"����"HIR"��"HIW"ɷ"NOR);
        set("gender", "����" );
		set("nickname","���϶�");
        set("age", 42);
        set("str", 35);
        set("con", 30);
        set("dex", 40);
        set("int", 25);
        set("per", 10);
   		set("attitude", "peaceful");

		set("max_qi", 22000);
		set("max_jing", 4000);
		set("eff_jingli", 4000);
        set("max_neili", 14000);
        set("neili", 14000);
		set("jiali", 180);
        
        set("long","�����Ǹ������ݸ߸��������ˣ���ɫ���ƣ�һ˫�۾���Ϊ����������һվ���ƺ���һ������ӡ�\n",);
		//set("env/һ��ָ","����");
        set("combat_exp", 8000000+random(500000));
        set("shen", -180000);

        set("chat_chance_combat", 50);
        set("chat_msg_combat",({ 
			(: perform_action, "staff.feizhang" :), 
			(: exert_function, "huntian" :),
	    }));

        set_skill("parry", 430);
        set_skill("dodge", 430);
        set_skill("force", 450);
        set_skill("hand", 430);
        set_skill("suohou-shou", 430);
        set_skill("literate", 100);
        set_skill("whip", 430);
        set_skill("huifeng-bian", 430);
        set_skill("xiaoyaoyou", 430);
        set_skill("huntian-qigong", 450);
        //set_skill("tianlong-xiang", 450);

		map_skill("dodge", "xiaoyaoyou");
		map_skill("parry", "huifeng-bian");
		map_skill("whip", "huifeng-bian");
		map_skill("force", "huntian-qigong");
		prepare_skill("hand","huohou-shou");
		set("chat_chance_combat", 60);
		set("chat_msg_combat",({
			(: perform_action, "whip.huixuan" :),
			(: perform_action, "hand.suohou" :),
			(: perform_action, "hand.qinna" :),
			(: exert_function, "huntian" :)
		}));

		set("inquiry", ([
			//"����" : (: ask_duan2 :),
		//"name" : (: ask_duan1 :),
		//"������" : (: ask_duan1 :),
		]));

	    setup();
	    carry_object("/clone/weapon/whip")->wield();
	    carry_object("/d/dali/obj/blackcloth")->wear();
}
/*
 void init()
{       
        object me,ob;
        ob = this_player(); 
        me = this_object();
        ::init();
        if( interactive(ob)
          && ob->query_temp(QUESTDIR1+"kill")){
         me->query("kill_id",ob->query("id"));
         call_out("kill_ob",1, ob); 
         }
}

string ask_duan1()
{
	object me,ob;
	ob=this_player();
	me=this_object();

	//me->set_name("������", ({ "duan yanqing", "duan","yanqing"}) );
	//me->set("title",HIC"�Ĵ����"NOR);
	//me->set("nickname",HIG"�����ӯ"NOR);
	if(!ob->query_temp(QUESTDIR1+"kill")) ob->set_temp(QUESTDIR1+"ask1",1);
	return "�Ϸ�����Ĵ�����е��ϴ󣺶����죡";
}

string ask_duan2()
{
        object me,ob;
        ob=this_player();
        me=this_object();

	if( !ob->query(QUESTDIR1+"over") && ob->query(QUESTDIR1+"pass_shanlu") && ob->query_temp(QUESTDIR1+"ask1")) {
		command("hehe " + ob->query("id"));
		me->set("kill_id",ob->query("id"));
		call_out("do_kill", 1, me, ob);
		return "��ȶ������������ˣ�";
	}
	else return "���������ʲô��";
}

int do_kill(object me, object ob)
{
	me->kill_ob(ob);
	ob->fight_ob(me);
	call_out("checking", 0, me, ob);
 	return 1;
}

void checking(object me, object ob)
{
	if (!ob) return;
	if (!me) return;
	if (!ob->query_temp(QUESTDIR1+"kill")) {
		if (me->query("qi")*10/me->query("max_qi") < 5 
		|| me->query("eff_qi")*10/me->query("max_qi") < 5 ){
			ob->set_temp(QUESTDIR1+"kill",1);
			message_vision(HIR"$n����$N���һ��������һƬ�����֡�\n"NOR, me, ob);
			message_vision(HIG"$n�����ȵ��������ܣ�$n����׷�˹�ȥ��\n"NOR, me, ob);
			ob->move("/d/dali/wuliang/shanlin-1");
			destruct(me);
		}
		else 
			call_out("checking", 1, me, ob);
	}
}

void die()
{
	  object me;
	  object ob=this_object();
      if ( ob->query("kill_id")
                  && userp(me=present(ob->query("kill_id"),environment(ob)))
		  && me->query(QUESTDIR1+"pass_shanlu") 
		  && !me->query_temp(QUESTDIR1+"kill")
		  && !me->query(QUESTDIR1+"over")) {
		me->set("quest/�����˲�/time", time());
		me->set("quest/�����˲�/combat_exp", me->query("combat_exp"));
		me->delete_temp("quest/�����˲�");
		me->delete_temp("quest/busy");
		log_file("quest/TLBB", sprintf("%s(%s) ���������죬ʧ�ܡ����飺%d��\n", me->name(1),me->query("id"), me->query("combat_exp")) );
		command("sneer");
		message_vision(HIR"\n$N��Ц������ɱ���ң��Ⱳ�ӱ����ҵ������ˡ�\n"NOR, this_object());
		tell_object(me,HIG"\n������Ӫ�ȵ�����ֻ������������ɣ��㻹����ʱ�ر�һ�¡�\n"NOR);
	}
	::die();
}

void unconcious()
{
	die();
}
*/