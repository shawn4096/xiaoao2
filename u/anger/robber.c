// Modify By River@SJ
//Modify By Renlai@xa

inherit FIGHTER;
//inherit F_UNIQUE;
#include <ansi.h>

int do_kill(object me);
int do_kick(string target);

string *first_title = ({"������","�׻���","��ȸ��","������","÷ׯ","������ʹ����","������ʹ����","��̳"});
string *second_title = ({ "����","����","����","����","����","����", "����"});

void create()
{
	string title;
	
	title = first_title[random(sizeof(first_title))];
	title += second_title[random(sizeof(second_title))];
	set_name("������",({"wuming shi"}));
		
	set("long","��һ�һ�������ɷ��ģ����\n");
	set("title", HIW+title+NOR);
	set("age", 30 + random(30));
	
	set("combat_exp", 8000000);
	set("meitude", "peaceful");
	set("str", 30);
	set("dex", 30);
	set("int", 30);
	set("con", 30);
	set("max_qi", 30000);
	set("max_jing", 20000);
	set("max_neili", 10000);
	set("neili", 10000);
	set("no_heal",1);
	set("no_ansuan",1);
    set("no_bark", 1);
	
	add_temp("apply/defense", 200);
	add_temp("apply/armor", 200);
	add_temp("apply/damage", 100);

	setup();
	carry_object(ARMOR_D("yexing-yi"))->wear();	
	set("chat_chance", 5);
	set("chat_msg", ({
		(: random_move :)
	}) );
	if (clonep())
		call_out("dest", 900);
}
void init()
{
	object ob;
	::init();
	//add_action("do_kick","kick");   
/*	if( interactive(ob = this_player())){
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}
	*/
}

void kill_ob(object ob)
{
	object me = this_object();
	
	if(!ob->query("ry/ry_job")) {		
		
		me->set("eff_jing",me->query("max_jing"));
		me->set("jing",me->query("max_jing"));
		me->set("eff_qi",me->query("max_qi"));
		me->set("qi",me->query("max_qi"));
		me->clear_conditions_by_type("poison");
		command("say ������������ԩ�������޳�");	
		return;
	}
	else command("say ���������������İɣ�");	
	::kill_ob(ob);
}


void dest()
{
	message_vision("$N����ͻȻ����ʲô�£�����ææ���߿��ˡ�\n", this_object());
	destruct(this_object());
}
