//huyizhi.c
//��ʤ���� ����֮
// by sohu
//inherit F_MASTER;
inherit NPC;
//inherit FIGHTER;
#include <ansi.h>

void create()
{
	set_name("����֮", ({ "hu yizhi", "hu", "yizhi" }) );
	set("gender", "����" );
	set("title", HIC"��ʤ����"NOR);
	//set("nick","������");
	set("age", 26);
	set("long", 
	    "һ����������֮����������޳���һ���˲ţ������ھ����֡�\n"
	    "���˷���Ӣ��������˵�������е�һ�����ӣ������˳ơ���������\n"
		"������ʱ��Ȼ�����˸�ɵ��ɵ��������У�\n"NOR);
	set("str", 25+random(30));
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", 1);
	set("feidao",1);
	set("unique", 1); //ǧ�������Ⱒ������趨
  
	set_skill("force", 450);
    set("no_get", 1);
    set("no_bark", 1);
	set_skill("dodge", 450);
	set_skill("parry", 450);
	set_skill("blade", 530);
	set_skill("cuff",450); 
	set_skill("taxue-wuhen",450);
	set_skill("zhentian-quan",450);
	set_skill("lengquan-shengong",450);
	set_skill("hujia-daofa",500);
	map_skill("force","lengquan-shengong");
	map_skill("cuff","zhentian-quan");
	map_skill("dodge","taxue-wuhen");
	map_skill("blade","hujia-daofa");
	map_skill("parry","hujia-daofa");
	set("double_attack",1);
    prepare_skill("cuff", "zhentian-quan");
	set("combat_exp", 12000000);
	set("max_qi", 30000);
	set("max_jing", 30000);
	set("max_neili", 35000);
	set("eff_jingli",30000);
	set("qi",30000);
	set("jing",30000);
	set("jingli",30000);
	set("neili", 35000);
    set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
       (: exert_function, "lengquan" :),
       (: perform_action, "blade.feidao" :),
		   (: perform_action, "blade.yunlong" :),
		   (: perform_action, "blade.roudao" :),
		   (: perform_action, "blade.fanshen" :),
       (: perform_action, "blade.luandao" :)
     }));
    set("inquiry", ([
 //   "��һ��" : (: ask_huyidao :),
   // "hu yidao" : (: ask_huyidao :),
	]));
	setup();
	set("chat_chance", 1);
	set("chat_msg", ({
		"���������ҿ�һ��Ҳ�������㡣\n",
	}));
	carry_object("/clone/weapon/blade/blade.c")->wield();
	carry_object("/clone/weapon/blade/blade.c");
	carry_object("/clone/armor/baihu-qiu.c")->wear();
} 
