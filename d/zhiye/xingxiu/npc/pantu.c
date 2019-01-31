// Modify By River@SJ

inherit FIGHTER;
//inherit F_UNIQUE;
#include <ansi.h>

int do_kill(object me);
int do_kick(string target);


//string *first_title = ({"��ɽ��","�䵱��","������","������","ؤ��","������","ȫ���","�һ���"});
string *second_title = ({ "����","����","�״�����","�մ�����","����","��Ӣ����", "����"});

void create()
{
	string title;
	
	//title = first_title[random(sizeof(first_title))];
	title=WHT"������ͽ"NOR;
	//title=title+this_object()->query("family/family_name");
	//title += second_title[random(sizeof(second_title))];
	set_name("������",({"wuming shi"}));
		
	set("long","��һ�һ����ò��Ȼ��ģ������ɫƽ����ʱ��ʱ��¶΢Ц��\n");
	set("title", title);
	set("age", 20 + random(50));
	
	set("combat_exp", 8000000);
	set("meitude", "peaceful");
	set("str", 25);
	set("dex", 30);
	set("int", 30);
	set("con", 30);
	set("max_qi", 20000);
	set("max_jing", 20000);
	set("max_neili", 5000);
	set("neili", 5000);
	set("no_heal",1);
	set("no_ansuan",1);
    	set("no_bark", 1);

	setup();
/*	carry_object(BINGQI_D(weapon))->wield();*/
	carry_object(ARMOR_D("cloth"))->wear();
	add_money("silver", random(10)+50);
	set("chat_chance", 5);
	set("chat_msg", ({
		(: random_move :)
	}) );
	if (clonep())
		call_out("dest", 800);
}
void init()
{
	object ob;
	::init();
	add_action("do_kick","kick");   
	if( interactive(ob = this_player())){
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}
}
////���ÿ�������fighter�ĺ���
int do_kill(object ob)
{
	object me = this_object();
	if(!ob) return 0;
	if (me->query_temp("kicked")) {  
		message_vision(HIR""+me->name()+"��$N˵����" + RANK_D->query_rude(ob) +"����׷���ᣬ��Ȼ�Ӳ�����"+RANK_D->query_self_rude(me) +"����ƴ�ˣ�\n\n"NOR,ob);
		me->delete_temp("kicked");
	} else if (me->query_temp("fight_failed")) {
		message_vision(HIR""+me->name()+"����$N˵�����ٺ٣��е��Ҹ�������"+RANK_D->query_self_rude(me) +"�������ˣ�\n\n"NOR,ob);
		me->delete_temp("fight_failed");
	} else 
		message_vision(HIR""+me->name()+"����$N����һ����Ц��˵������Ȼ�������" + RANK_D->query_rude(ob)+ "ײ���ˣ���Ҳ��ֻ�����������ˣ�\n\n"NOR,ob);
	remove_call_out("checking");
	call_out("checking", 2, me, ob);
	//::do_kill(ob);
	me->kill_ob(ob);
}

int checking(object me, object ob)
{
	int ret =  ::checking(me,ob);
	if(!ret) return 0;
	remove_call_out("checking");
	call_out("checking", 1, me, ob);
        if(!living(ob) && living(me) && me->query("jing")>0 && me->query("jingli")>0 && me->query("qi")>0  ){
		remove_call_out("checking");
		ob->set_temp("xx/xx_job_lost",1);
		//ob->set("qi",100);																			//��ֹ�����������
		//ob->set("jing",100);
		//ob->set("jingli",100);
		tell_room(environment(me), "\n"+me->query("name")+"��һ�������Ӳ������ˣ�ת��������Ͳ����ˡ�\n");
		destruct(me);
		 return 1;
	}
	if(!ob || environment(ob)!= environment(me)){
		remove_call_out("checking");
		 remove_call_out("do_lost");
		 call_out("do_lost",0);
		 return 1;
	}
}

void greeting(object ob)
{
	object me = this_object();

	if (!ob
	 || !present(ob)
	 || me->query_temp("target") != ob->query("id"))
		return;

	if (ob->query_temp("xx/xx_job")){

		if (environment(me)->query("no_fight") || environment(me)->query("sleep_room")) {
			me->delete_temp("fight_failed");
			me->delete_temp("kicked");
			if (random(2)==0) {
				message_vision(HIR""+me->name()+"����$N�߹�������ɫ��Щ�쳣����æ������ͷ��\n"NOR,ob);
				tell_object(ob, HIR"���̲�ס��ݺ���(kick)����һ�һ�š�\n"NOR);
			} else {
				message_vision(HIR""+me->name()+"����$N����һ����Ц��˵����"+ RANK_D->query_rude(ob)+ "������ط�̫С�����ָ�"+ RANK_D->query_self_rude(me) +"������Ȼ��Ȼ���\n\n"NOR,ob);
				me->random_move();				
			}
			me->set_temp("fight_failed",1);
		} else {		
			ob->add_busy(1);
			me->start_busy(1);
			//remove_call_out("checking");
			//call_out("checking", 1, me, ob);
			remove_call_out("dest");
			call_out("dest", 600);
			remove_call_out("do_kill");
			call_out("do_kill", 0, ob);
		}
	}
}

int do_kick(string target)  
{
	object me = this_object();
	object ob = this_player();
	if (target && present(target, environment()) == me) {	
		if (!me->query_temp("fight_failed")) return 0;	

		message_vision(HIR"$N����"+me->name()+"һ���߹�ȥ��"+ RANK_D->query_rude(me) +"������������㣡"+me->name()+"���Ʋ������һ���������Ӵܡ�\n\n"NOR,ob);
		
		me->random_move();
		me->delete_temp("fight_failed");
		me->set_temp("kicked",1);
		return 1;
	} else {
		return 0;
	}
}

void dest()
{
	destruct(this_object());
}

void do_lost()
{
	object me,ob;
	me = this_object();
	ob = find_player(me->query_temp("target"));
	if(!ob) return;
	ob->set_temp("xx/xx_job_lost",1);
	tell_room(environment(me), "\n"+me->query("name")+"��һ�������Ӳ������ˣ�ת��������Ͳ����ˡ�\n");
	destruct(me);
}
/*
void unconcious()
{
	object me,ob;

	me = this_object();
	ob = find_player(me->query_temp("target"));
	if (!ob) {
		destruct(me);
		return;
	}
	if (!present(ob)) {
		ob->set_temp("xx/xx_job_lost2",1);
		ob->set_temp("xx/xx_job_lost2_man",this_player()->query("name")+"("+this_player()->query("id")+")");

		tell_room(environment(me), "\n"+me->query("name")+"��һ�������Ӳ������ˣ�ת��������Ͳ����ˡ�\n");
		destruct(me);
		return;
	}
	
	ob->set_temp("xx/xx_jobok",1);
	::die();
}
*/

void die()
{
	object me,ob;

	me = this_object();
	me->interrupt_me();
	ob = find_player(me->query_temp("target"));
	if (!ob) {
		destruct(me);
		return;
	}
	ob->delete_temp("xx/ob");//����ɾ��npc���� by renlai	
	tell_room(environment(me), "\n"+me->query("name")+"��һ�������Ӳ������ˣ�ת��������Ͳ����ˡ�\n");
	ob->set_temp("xx/xx_jobok",1);
	//::die();
	destruct(me);
}
