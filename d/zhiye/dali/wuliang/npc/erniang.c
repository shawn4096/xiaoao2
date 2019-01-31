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
        set_name("Ҷ����", ({ "ye erniang", "ye","erniang"}) );
		set("title",HIW"��"HIR"��"HIW"����"NOR);
        set("gender", "Ů��" );
		//set("nickname","���϶�");
        set("age", 42);
        set("str", 30);
        set("con", 30);
        set("dex", 40);
        set("int", 25);
        set("per", 10);
   		set("attitude", "peaceful");

		set("max_qi", 25000);
		set("max_jing", 4000);
		set("eff_jingli", 4000);
        set("max_neili", 15000);
        set("neili", 15000);
		set("jiali", 190);
        
        set("long","�������������ϸ�������Ѫ�ۣ���Ȼ��Ц��������Ц��֮���ƺ������������ࡢ�������ģ��������ж���������ͬ�顣\n",);
		//set("env/һ��ָ","����");
        set("combat_exp", 9000000+random(500000));
        set("shen", -180000);

        set("chat_chance_combat", 60);
        set("chat_msg_combat",({ 
			(: perform_action, "blade.daozhang" :), 
			(: exert_function, "huntian" :),
	    }));

        set_skill("parry", 450);
        set_skill("dodge", 450);
        set_skill("force", 450);
        set_skill("strike", 450);
        set_skill("tiezhang-zhangfa", 450);
        set_skill("literate", 200);
        set_skill("blade", 450);
        set_skill("liuye-daofa", 450);
        set_skill("shuishangpiao", 450);
        set_skill("guiyuan-tunafa", 450);
        //set_skill("tianlong-xiang", 450);

		map_skill("dodge", "shuishangpiao");
		map_skill("parry", "liuye-daofa");
		map_skill("blade", "liuye-daofa");
		map_skill("force", "guiyuan-tunafa");
		map_skill("strike","tiezhang-zhangfa");
		prepare_skill("strike","tiezhang-zhangfa");
		set("chat_chance_combat", 70);
		set("chat_msg_combat",({
			(: perform_action, "blade.daozhang" :),
			(: perform_action, "strike.qinna" :),
			(: perform_action, "strike.heyi" :),
			(: exert_function, "guiyuan" :)
		}));

		set("inquiry", ([
			//"����" : (: ask_duan2 :),
		//"name" : (: ask_duan1 :),
		//"������" : (: ask_duan1 :),
		]));

	    setup();
	    carry_object("/clone/weapon/blade")->wield();
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