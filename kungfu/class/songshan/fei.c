// fei.c ��ɽ�ɵ��������� �ѱ�
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
string ask_guanri();

void create()
{
        set_name("�ѱ�", ({ "fei bin", "fei", "bin" }));
        set("nickname", HIY"��������"NOR);
        set("long", "������ʮ���꣬�е���ģ������쳣���ϴ�������Ʋ���룬����ɽ
�������������ĵ���ʦ�ܷѱ�һ�״������������кպ�������\n");
        set("gender", "����");
        set("age", 49);
        set("per", 18);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 25);
        set("int", 23);
        set("con", 26);
        set("dex", 26);
        set("unique", 1);

        set("max_qi", 13000);
        set("max_jing", 6000);
        set("eff_jingli", 6000);
        set("jiali", 250);
        set("combat_exp", 65000000);
        set("shen", -1400000);

		set_skill("literate", 200);
		set_skill("force", 400);
		set_skill("parry", 460);
		set_skill("sword", 400);
		set_skill("dodge", 400);
		set_skill("hand", 460);
		set_skill("zhongyuefeng", 400);
		set_skill("songyang-shou", 460);
		set_skill("hanbing-zhenqi", 400);
		set_skill("songshan-jian", 400);
		set_skill("songyang-jue", 200);

		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("parry", "songyang-shou");
		map_skill("sword", "songshan-jian");
		prepare_skill("hand", "songyang-shou");
		create_family("��ɽ��", 3, "����");
		set("chat_chance", 25);
		set("chat_msg", ({
			(: random_move :)
		}) );
		set("chat_chance_combat", 80);
		set("chat_msg_combat", ({
			(: perform_action, "hand.yinyang" :),
			(: perform_action, "hand.junji" :),
			(: perform_action, "hand.tuota" :),
			(: perform_action, "hand.xianhe" :),
			(: exert_function, "hanbing" :),
			(: exert_function, "juhan" :),
		 }));
		set("inquiry", ([
			"��ɽ��" : "������ɽ������������֮�ף�\n",
			"��������" : "������������������֮�������޴󣬿������֡��䵱���⡣\n",
			"������" : "���������ǵ������ˣ�������ɲ⡣\n",
			 "���շ�" : (: ask_guanri :),
			//"�������" : (: ask_feiwu :),

		]) );
			setup();
			carry_object(ARMOR_D("changpao1"))->wear();
}
string ask_guanri()
{
	object me=this_player();
	if (me->query("family/family_name")!="��ɽ��")
	{
		command("say �㲻������ɽ���ӣ�����������");
		return "�ߣ�";
	}
	if (me->query_skill("songshan-jian",1)<200)
	{
		command("say ����ɽ��������200������������");
		return "�ߣ�";
	}
	if (!me->query("quest/ss/dichuan"))
	{
		command("say �������ɽ�մ����ӣ�����������");
		return "�ߣ�";
	}
	command("say �Ҵ���ɽ��һ�����ε�����֮�أ�����ɽ���Ӳ��ý��롣\n");
	command("say �Ķ������Ҵ���ɽ�Ĺ��շ塣\n");
	command("say �����Ž������������ڴ˴���Ħ���ζ�������������\n");
	command("say �����ǲ�����˲ţ��Ҿ͸�������Щ�����Լ�ȥ����ȥ�ɡ�\n");
	me->set_temp("feiwu/askfei",1);
	return "";

}
