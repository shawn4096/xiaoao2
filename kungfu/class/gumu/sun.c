// sun.c ������
// By River@SJ 2001.02.28

#include <ansi.h>
inherit NPC;
string ask_job();
int ask_hexiu();
void create()
{
	set_name("������", ({ "sun popo", "sun", "popo" }));
	set("long","��λ�ϸ�����һ��������Ƥ���ĳ����������������㡣\n");
	set("gender", "Ů��");
	set("age", 60);
	set("attitude", "friendly");
	set("no_bark",1);
	set("per", 10);
	set("str", 30);
	set("dex", 30);
	set("con", 25);
	set("int", 40);
	set("shen", 1000);

	set("combat_exp", 6700000);
	set("max_qi", 13500);
	set("max_jing", 3600);
	set("eff_jingli",2000);
	set("max_neili", 15000);
	set("neili", 5000);
	set("jiali",30);
	set("unique", 1);

	set_skill("parry", 400);
	set_skill("force", 400);
	set_skill("dodge", 400);
	set_skill("sword", 400);
	set_skill("throwing", 400);
	set_skill("whip", 400);
	set_skill("meinu-quanfa", 400);
	set_skill("cuff", 400);
	set_skill("yunu-shenfa", 400);
	set_skill("yinsuo-jinling", 400);
	set_skill("yunu-jianfa", 400);
	set_skill("yunu-xinjing", 400);
	set_skill("literate", 140);

	map_skill("force", "yunu-xinjing");
	map_skill("dodge", "yunu-shenfa");
	map_skill("cuff", "meinu-quanfa");
	map_skill("sword", "yunu-jianfa");
	map_skill("whip", "yinsuo-jinling");
	map_skill("parry","yinsuo-jinling");
	prepare_skill("cuff", "meinu-quanfa");

	set("inquiry", ([
		//"���" : (: ask_job :),
		"����" : (: ask_hexiu :),
	]));
      
	setup();
	carry_object("/d/gumu/obj/buxue1")->wear();
	carry_object(ARMOR_D("cloth"))->wear(); 
}

int ask_hexiu()
{
	object me=this_player();
	if (me->query("family/family_name")!="��Ĺ��")
	{
		command("hehe");
		command("say ����ҹ�Ĺ��Ե�޹ʣ���ô���ޣ�");
		command("say ��...");
		return 1;
	}
	if (me->query_skill("yunu-xinjing",1)<100)
	{
		command("say �����Ů�ľ���Ϊ����100���Ͻ�Ŭ��ȥ�ɣ�");
		command("say ��...");
		return 1;
	}
	if (me->query("quest/gumu/ynxj/pass"))
	{
		command("say ���Ѿ��⿪����Ů�ľ���һ���书����������ˣ�\n");
		command("say �ú�Ŭ����������������ʧ����\n");
		return 1;
	}
	if (me->query("gender")=="����")
	{
		command("say ���ޣ���һ�������˺��Һ��ޣ�����");
		command("say �����̬���޳�...");
		return 1;
	}
	
		command("hehe");
		command("say ��Ȼ��û�飬����������Ҳ�������ģ������������.");
		command("say ���ȵ���԰��һ���ĺ컨���У��Ķ��ȽϿ����������͵���\n");
		command("hehe");
		me->set_temp("ynxj/hexiusun",1);
		return 1;
}