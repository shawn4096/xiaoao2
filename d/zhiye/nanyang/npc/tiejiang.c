// tiejiang.c ����
#include <ansi.h>

inherit NPC;
inherit F_VENDOR;
string ask_name();
 
void create()
{
	set_name("����", ({ "tie jiang", "tie", "jiang" }) );
	set("gender", "����" );
	set("age", 34);
	set("long", "����һλλ�������Ŵ����������������Ĵ�����������\n");
	set("combat_exp", 30000);
	set("attitude", "peaceful");
	set("rank_info/respect", "����");
	set("vendor_goods", ({
		(["name":__DIR__"obj/changjian","number":15]),
		(["name":__DIR__"obj/gangjian","number":20]),
		(["name":__DIR__"obj/gangdao","number":15]),
		(["name":__DIR__"obj/caidao","number":10]),
		(["name":__DIR__"obj/tiechui","number":10]),
		(["name":__DIR__"obj/bishou","number":10])
	}));
	set("inquiry", ([
		//"name" : "������������С��ס�����ݳǣ�������ɶ��\n",
		//"rumors" : "�ҵ�����͢��ȥ���˺ӣ������˼����ӹǲ��ã�ǰЩ�첻����ȥ�ˡ�\n",
		//"here" : "�����ǳ���Ψһ�Ĵ������ˣ�ʲô�˶�����������������\n",
		"name": (: ask_name :),
		//"������": "��ͷ... ��Ǹ����ͷ�Ѿ�������...", 
	]));
	setup();
	carry_object(ARMOR_D("cloth"))->wear();
}

void init()
{       
	object ob;

	::init();
	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	switch( random(2) ) {
		case 0:
			say( "����Ц�����˵������λ" + RANK_D->query_respect(ob) + "������ֻҪ�����ļһӦ�о��С�\n");
			break;
		case 1:
			say( "����Ц�Ǻǵ�˵����λ" + RANK_D->query_respect(ob) + "������Ҫ��ʲô��\n");
			break;
	}
}


string ask_name()
{
	object me,obj;
	me=this_player();

	if (!me->query_temp("quest/������/������/start"))
	{
		command("say �Ҹ����Ͳ���ʶ�㣬�������ң�\n");
		command("heng");
		return "������֣��ҷ�������в���İ���˳����ڱ���\n";
	}

	command("say �ߣ���Ȼ������֪���ˣ��Ǿͱ�����ĺ������ˣ���\n");
	message_vision(HIR"���ͨ��Ȼץ���¯�Աߵ�һ���ձ�����$N���˹�����\n"NOR,me);
	message_vision(HIY"\n$N������һ������ձ��䵽�����ȥ�����ͨ�漴һ��Խ�����⣬�����ȥ��\n"NOR,me);
	me->set_temp("quest/������/������/findwu",1);
	message_vision(CYN"\n\n\n����������ȥ����ʱ����Ȼ������ܽ���һ��ǿ������\n"NOR,me);
	message_vision(HIR"\n�����ȵ��������Һڷ�կ�ĵ����Ͼ�Ȼ��������������������\n"NOR,me);
    me->add_busy(1);
	obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
	 obj->set_name("ආ�", ({ "lou luo", "louluo", "lou" }) );	 
	 obj->set("title", "�ڷ�կආ�");
     obj->move(environment(me));
	 obj->kill_ob(me);
	
	return "";
}
