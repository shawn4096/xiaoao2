// Npc: /kungfu/class/shaolin/cheng-xin.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;
#include <ansi.h>

string ask_qys();

void create()
{
	set_name("����", ({
		"chengxin luohan",
		"chengxin",
		"fuhu",
		"luohan",
	}));
	set("long",
		"����һλ�뷢���׵���ɮ����һϮ��ߺڲ����ġ�������ݸߣ�\n"
		"̫��Ѩ�߸߹����ƺ��������书��\n"
	);

	set("nickname", "�����޺�");
	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 60);
	set("shen", 5000);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);
	set("max_qi", 2500);
	set("max_jing", 1000);
	set("neili", 2500);
	set("max_neili", 2500);
	set("jiali", 100);
	set("combat_exp", 600000);
    set("unique", 1);

	set_skill("force", 120);
	set_skill("yijin-jing", 120);
	set_skill("dodge", 120);
	set_skill("shaolin-shenfa", 120);
	set_skill("hand", 120);
	set_skill("qianye-shou", 120);
	set_skill("parry", 120);
	set_skill("buddhism", 120);
	set_skill("literate", 120);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("hand", "qianye-shou");
	map_skill("parry", "qianye-shou");

	prepare_skill("hand", "qianye-shou");
	set("inquiry", ([
		"����ǧҶ�־���" : (: ask_qys :),
	
	]));

	create_family("������", 37, "����");

	setup();

        carry_object("/d/shaolin/obj/cheng-cloth")->wear();
}


#include "/kungfu/class/shaolin/cheng.h"

string ask_qys()
{
	mapping fam;
	object me=this_player();

	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player())+"�뱾��������������֪�˻��Ӻ�̸��";

	if (me->query_skill("qianye-shou",1)<450)
		return RANK_D->query_respect(this_player()) +"�������ǧҶ�ֵȼ�����450���������Ŭ����";

	if (time()-me->query("quest/sl/qys/time")<86400)
	{
		return RANK_D->query_respect(this_player()) +"�������ض���������̫Ƶ���ˣ������Ŭ����";

	}
	command("say ������ǧҶ������������ʮ�������ַ��еļ��¡�\n");
	command("say һ�Ʒֳ���һ��Ϊ��������Ϊ�ģ�ֱ���������޾���\n");
	command("say ��Ҳû�����ɣ���������������ʦ�����ֺ�������һս������ǧҶ���������¡�\n");
	command("say �������ѧ���ڴ��������(cancha ����ǧҶ��)�ɡ�\n");
	me->set_temp("qys/askchengxin",1);
	return "����ǧҶ�ִӲ������ˣ���Ҫ�ú���ϰ��\n";

}