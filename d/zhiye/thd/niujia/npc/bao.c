//bao.c

inherit NPC;
#include <ansi.h>
string ask_likai();
string ask_jiya();

#define QUESTDIR "quest/���Ӣ�۴�/"
#define QUESTDIR1 "quest/���Ӣ�۴�/��ѩ����/"

void create()
{
	set_name("��ϧ��", ({ "bao xiruo", "bao", "xiruo" }) );
	set("gender", "Ů��" );
	set("age", 25);
	set("long",
"����ļ��ã���Ȼ���е�ڣ����ǻ��ǿ������޵����Ķ��ˡ�\n");
	set("str", 10);
	set("dex", 10);
	set("con", 5);
	set("int", 5);
	set("per", 30);
	set("shen_type", 1);
	set_skill("unarmed", 5);
    
	set("combat_exp", 15000);
	set("max_qi", 100);
	set("max_jing", 100);
	set("max_neili", 0);
	set("eff_jingli",200);
	set("qi",100);
	set("jing",100);
	set("jingli",200);
	set("neili", 0);

  set("inquiry", ([
    "��Х��" : "�����ҷ�����֡�",
    "�" : "����һ�����˸���δ�����Ķ�Ůȡ�����֡�",
    "����" : "�����ҷ�����ֹ�Х��Ĺ��⡣",
    "�����뿪��ʲôȥ��" : (:ask_likai:),
	"ɱ��ɱѼ" : (:ask_jiya:),
	]));

    setup();
	carry_object("/clone/armor/cloth.c")->wear();
	carry_object(ARMOR_D("shoes"))->wear();
} 


string ask_likai()
{
	object me;
	me=this_player();

	message_vision(HIC"$N����ǰȥ���ս���ϧ����ǰ�������ʵ������������뿪��ȥ��ʲô����\n	"NOR,me);
	if (me->query(QUESTDIR1+"yestongyin")||me->query(QUESTDIR+"yestongyin"))
	{
		command("shake ");
		command("say ������׼���þƣ����뵽ǰԺ�úúȾ�\n");
		return "�Ͻ���ȥʹ����\n";
	}
	if (me->query(QUESTDIR1+"notongyin"))
	{
		command("blush ");
		command("say �ң��ң���........��\n");
		me->set_temp(QUESTDIR1+"askbao",1);
		return ".........";

	}
	
	return "����һ�����ǺȾƺȶ��ˣ�\n";
}

string ask_jiya()
{
	object me;
	me=this_player();
	
	if (me->query(QUESTDIR1+"yestongyin")||!me->query_temp(QUESTDIR1+"askbao"))
	{
		command("say ��һ�����������쵽Ů����ǰ�ֹ�ʲô��\n ");
		command("say һ���Ͳ��Ǻö�����\n");
		command("pei ");
		return "���ޣ�";
	}	
	message_vision(HIC"$NС���԰�ϧ����ݺݵ�˵��������Ҫ�ǲ�˵�ҾͰ���������С��СѼȫ��ɱ������\n	"NOR,me);

	
		command("fear ");
		command("sigh ");
		command("say �ҷ���ȥ�ü����������ֺ���é�����к����쳣���Һ��Ǻ���!\n");
		command("say �ֲ���˵����Ӱ�������ǺȾƣ�������.....!\n");
		me->set_temp(QUESTDIR1+"weihebao",1);

	return "��������ɱ�ˣ���ܲ���!\n";

}