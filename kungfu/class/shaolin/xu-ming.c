// Npc: /kungfu/class/shaolin/xu-ming.c
// Date: YZC 96/01/19

inherit NPC;


void create()
{

	set_name("����", ({
		"xu ming",
		"xu",
		"ming",
	}));
	set("long",
		"����һλ���Ʋ����ĵ�����ɮ�ˡ���������δ�ѣ�����ȴ����\n"
		"���ýݣ������ƺ�ѧ��һ���书��\n"
	);

	set("nickname", "֪��ɮ");
	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 20);
	set("shen_type", 1);
	set("str", 20);
	set("int", 20);
	set("con", 35);
	set("dex", 20);
	set("max_qi", 550);
	set("max_jing", 400);
	set("neili", 500);
	set("max_neili", 500);
	set("jiali", 20);
	set("combat_exp", 15000);
	
	set_skill("force", 50);
	set_skill("yijin-jing", 50);
	set_skill("dodge", 50);
	set_skill("shaolin-shenfa", 50);
	set_skill("strike", 50);
	set_skill("banruo-zhang", 50);
	set_skill("parry", 50);
	set_skill("sword", 50);
	set_skill("damo-jian", 50);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("strike", "banruo-zhang");
	map_skill("parry", "damo-jian");
	map_skill("sword", "damo-jian");

	prepare_skill("strike", "banruo-zhang");

	create_family("������", 41, "����");

	setup();

        carry_object("/d/shaolin/obj/changjian")->wield();
        carry_object("/d/shaolin/obj/xu-cloth")->wear();

}
int accept_object(object who, object ob,object me)
{
        mapping fam; 
        me=this_object();

        if (ob->query("owner")!=who->query("id")
			||!ob->query_temp("sljob/qingwu/yingke"))
		{
                command("hehe "+who->query("id"));
                command("say ����Ҷ�����ʲô��ͼ����");
        		return 0;
        }
		if(!who->query_temp("sljob/qingwu/yingke"))
		{
			command("say ��������������ģ���ֵ����õ����޴�ʦ������");
			return 0;
		}
		if(!userp(ob) && ob->query("id") == "yingke ling")
		{
			command("say �ðɣ����Ȼ�����޴�ʦ�����ƣ��������������������æ�ɣ���æ�����ˡ�");
			who->apply_condition("sl_yingke",random(4)+7);
			who->set_temp("sljob/qingwu/yingking",1);
			call_out("dest", 1, ob);
			return 1;
		}
	return 1;
}