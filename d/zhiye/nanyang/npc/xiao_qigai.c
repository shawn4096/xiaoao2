// qigai.c
// ����ʯ����
inherit NPC;
string ask_shaobing();
string ask_name();

#include <ansi.h>

#define XKX_QUEST2 "quest/������/������/"

void create()
{
	set_name("С��ؤ", ({ "xiao qigai","beggar","qigai" }) );
	set("title", "����");
//	set("title", "��ؤ");
	set("gender", "����" );
	set("age", 16);
	set("long", "����һ��ʮ�������С�л��ӣ����Ѷ���һ���죬����û��������ǽ�Ǳߡ�\n");

	set("str", 25);
	set("cor", 25);
	set("cps", 25);
	set("int", 25);

	set("max_qi", 500);
	set("max_jing", 100);
	set("neili", 500);
	set("max_neili", 500);
	set("jiali", 50);
	set("shen_type", 0);

	set_temp("apply/attack",  20);
	set_temp("apply/defense", 20);
	set_temp("apply/damage",  20);

	set("combat_exp", 20000);
	set("str", 27);
	set("kar", 100);
	set("thief", 0);
	set("force", 200);
	set("shaobing", 1);

	set("max_force", 200);
	set("force_factor", 2);

	set_skill("unarmed", 50);
	set_skill("sword", 50);
	set_skill("dodge", 80);
	set_skill("parry", 80);
	set_skill("stealing", 100);
	setup();
	set("inquiry", ([
		"name": (: ask_name :),
		 "�ձ�": (: ask_shaobing :),
		// "������": (: ask_shaobing :),
	]));        carry_object("/clone/food/jitui");
        carry_object("/clone/food/jiudai");
	add_money("silver", 10);
}

string ask_name()
{
	object me;
	me=this_player();

	if (!me->query_temp(XKX_QUEST2+"findqigai")) return "�Һ��£���....\n";
	if (me->query_temp(XKX_QUEST2+"askqgname"))
	{
		return "���Ѿ��ʹ��ˣ���������\n";
	}
	command("say �ҽС������֡�\n");
	message_vision(HIY"$N�������������ֺ�Ц���ȵ������Ҳ����㿪��Ц���㵽�׽�ɶ���֣���\n"NOR,me);
	command("say �������֡�");
	me->set_temp(XKX_QUEST2+"askshiname",1);
	//��������ɱ֮
	
	call_out("an_come",3+random(4),me);

	return "����~~������~��\n";
}

//���ٴγ��֣��Ȼ�ʯ����
int an_come()
{
	object me;
	me=this_player();
	message_vision(HIY"\n˭֪���ڴ�ʱ�����ͻ��\n"NOR,me);
	message_vision(CYN"��ǰ�Ѿ����������ͨ��Ȼ�λ����Ƶ�վ����������ͼһ�Ѷ����С��ؤ���е��ձ���\n"NOR,me);
	message_vision(HIY"���ͨ���д󼱣�Ŀ¶�׹⣬���Ǹ�С��ؤ�ȵ������Ͻ�������ù�������\n"NOR,me);
	message_vision(HIM"˵�꣬���ͨ�����йٱʣ��������Ǹ�С��ؤ����ʱ���Ȼ��ǲ��ȣ�"HIY"(baohu)��\n"NOR,me);
	me->set_temp(XKX_QUEST2+"wucome",1);
	//add_action("do_help","jiuhu");
	return 1;
}



//Ȼ��ask �ձ�
string ask_shaobing()
{
	object me,ob;
	me=this_player();
	if (!me->query_temp(XKX_QUEST2+"askshiname")||!me->query_temp(XKX_QUEST2+"helpshi"))
	{
		command("say �Ҳ���ʶ�㣬�����ҵ��ձ�������");
		command("say �����Ҫ���ҵ��ձ���");
		return "";
	}
	message_vision(YEL"$NС��������ߵ�С��ؤ�ĸ�ǰ��˵���������ɻ����̬˵���������ձ�����\n"NOR,me);
	command("say �Ҳ��ܸ��㣬�����ҵ������Ҷ��ˣ�");
	command("consider ");
	command("think ");
	message_vision(YEL"С��ؤ�����Ƕ����ˣ��������е��ձ�һ��ҧ����ȥ��\n"NOR,me);

	if (me->query_temp(XKX_QUEST2+"haoren")
		&&this_object()->query("shaobing")
		&&!me->query(XKX_QUEST2+"giveshaobing"))
	{

		command("say ����������ң�һ�����Ǻ���");
		command("say ��λƯ��������Ҳ�Ǻ���");
		command("say ���Ƕ��Ǻ���");
		this_object()->add("shaobing",-1);
		command("say ����Ҫ�кñ��ģ��㷽�ž����ң�����ձ��͸����\n");
		message_vision(CYN"С��ؤ��������Ŀ���һ���ձ��������¿�ˮ����Ҫ�����ձ��ݸ���$N��\n"NOR,me);
		ob=new("d/nanyang/obj/shaobing");
		ob->set("owner",me->query("id"));
		ob->move(me);
		me->set(XKX_QUEST2+"giveshaobing",1);
		me->set_temp(XKX_QUEST2+"giveshaobing",1);

	}
	return "����ձ���������Ӧ�úܺóԣ�\n";

}

