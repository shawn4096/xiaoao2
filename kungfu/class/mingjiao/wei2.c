// NPC wei.c ΤһЦ
// Modify By River@SJ 99.06
// been job_npc
// Update By lsxk@hsbbs 2007/7/18   ���ӵ�����߽��������

#include <ansi.h>
#include <job_mul.h>

inherit NPC;
inherit F_MASTER;

string ask_dichuan();
void create()
{
	set_name("ΤһЦ",({"wei yixiao","wei","yixiao"}));
	set("title","���̻��̷���");
	set("nickname",GRN"��������"NOR);
	set("long", "�������̵��Ĵ󻤷�֮һ������������\n"+
		"����ĸߴ�������ˣ�����һ����Ṧ��\n");
	set("age", 51);
	set("attitude", "peaceful");
	set("shen", -12000);
	set("str", 26);
	set("int", 26);
	set("con", 25);
	set("dex", 45);        

	set("max_qi", 30000);
	set("max_jing", 12000);
	set("eff_jingli", 12000);
	set("jiali", 170);
	set("combat_exp", 6400000);
	set("unique", 1);
	
	set("job_npc",1);

	set_skill("strike",400); 
	set_skill("literate",250);
	set_skill("dodge",500);
	set_skill("force", 400);
	set_skill("piaoyi-shenfa", 500);
	set_skill("hanbing-mianzhang",400);
	set_skill("shenghuo-shengong", 400);
	set_skill("parry", 400);
	map_skill("force", "shenghuo-shengong");
	map_skill("dodge", "piaoyi-shenfa");
	map_skill("strike", "hanbing-mianzhang");
	map_skill("parry", "hanbing-mianzhang");
	prepare_skill("strike","hanbing-mianzhang");
	set("inquiry", ([
		"�մ�����"  : (: ask_dichuan :),
	
	]));
	create_family("����", 36, "����");
	set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
		(: perform_action, "strike.xixue":),
		(: perform_action, "strike.mianzhang":),
		(: perform_action, "strike.hanbing":),
			(: exert_function, "shenghuo":),
	}));
	setup();
	carry_object("/d/mingjiao/obj/yel-cloth")->wear();
}
