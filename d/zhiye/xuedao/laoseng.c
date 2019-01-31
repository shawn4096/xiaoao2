// laoseng.c Ѫ����ɮ
// by iceland

#include <ansi.h>
inherit NPC;

string ask_for_join();
int do_kneel();

void create()
{
	set_name("��ɮ", ({"lao seng","seng"}));
	set("long",
                "����Ѫ�������ʦ�ܣ�����������������������������ĺ��⣬һ˫�̶�С��\n"
                "���������ش�����,�����������������ȴ��Ϊ��׳��\n"
	);

    set("title", HIY "Ѫ��������ʦ��" NOR);
	set("gender", "����");
	set("attitude", "peaceful");
	set("class", "huanxi");

	set("inquiry",([
		"����"	: (: ask_for_join :),
		"�ܽ�"	: (: ask_for_join :),
	]));

	set("age", 30);
	set("shen_type", -1);
	set("str", 25);
	set("int", 15);
	set("con", 25);
	set("dex", 20);
	set("max_qi", 22450);
	set("eff_jing", 6200);
	set("max_jing", 6200);
	set("neili", 12500);
	set("max_neili", 12500);
	set("jiali", 200);
	set("combat_exp", 9300000);
	set("score", 1000);
	set("unique", 1);

	set_skill("force", 350);
	set_skill("xuedao-dafa", 350);
	set_skill("dodge", 350);
	set_skill("yuxue-dunxing", 350);
	set_skill("claw", 350);
	set_skill("tianwang-zhua", 350);
	set_skill("parry", 350);
	set_skill("huanxi-chan", 150);
	set_skill("literate", 230);

	map_skill("force", "longxiang-boruo");
	map_skill("dodge", "yuxue-dunxing");
	map_skill("claw", "tianwang-zhua");
	map_skill("parry", "tianwang-zhua");

	prepare_skill("claw", "tianwang-zhua");

	create_family("Ѫ����", 1, "����ʦ��");

	setup();

    carry_object("d/xuedao/obj/qinxiu-jiasha")->wear();
}

void init()
{
	add_action("do_kneel", "kneel");
}

string ask_for_join()
{
	object me;

	me = this_player();

	if (me->query("family/family_name") != "Ѫ����")
		return RANK_D->query_respect(me) + "�����ڿ���Ц�ɡ�\n";

	if( (string)me->query("class")=="huanxi" )
		return "���Ѿ����㿪̳�ܽ���ˣ�����ȱ��˶�һ�Σ���ɲ��С�\n";

	if( (string)me->query("gender") == "����" )
		return "ʩ�������ȱ����˵�����ն�������������Ѫ������ȫ�������⣬.����\n";

	if (me->query_temp("pending/join_huanxi"))
		return "�ϵ㣬�����µ�ʱ������������ǡ�\n";
        
	me->set_temp("pending/join_huanxi", 1);
	return "�������������̷ϲ�������(kneel)�ܽ䡣\n";
}

int do_kneel()
{
	object me = this_player();

	if( !me->query_temp("pending/join_huanxi") )
		return 0;

	message_vision("$N������ͷ�����������ع���������\n\n",me);
    message_vision("$n�ͳ�������������ü��Ŀ��Χ�������˼�Ȧ�����������дʡ�\n\n",me);
    message_vision("$n��Щ��ˮ����$Nͷ�ϣ�ɽ��һ����$N���ɵô��˼�����ս��\n\n",me);
    message_vision("$n����Խ��Խ�ߣ���ͷ�������ܵĺ�ˮ���ƺ����˺ܴ��������\n\n",me);
    message_vision("$n������һ�������ѷ����Żػ��У���������˲����ϵĺ�ˮ��\n\n",me);
	command("smile ");
	command("say �������ܽ䷨�������ˣ��ӽ��Ժ�ϲ����ᱣ����ġ�\n");
	me->delete_temp("pending/join_huanxi");
	me->set("class", "huanxi");
    return 1;
}
