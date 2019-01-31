// laozu.c Ѫ������
// by iceland

#include <ansi.h>

inherit NPC;

void create()
{
	object weapon;
	set_name("Ѫ������", ({ "xuedao laozu", "laozu","xuedaolaozu" }));
	set("long",@LONG
����ĸ��ݣ��������ݣ�һ˫�۾�����׺ݵĹ�â�����˲���ֱ�ӡ����ڽ���
���Բ��̺�ɫ�����ƣ���ƾһ��Ѫ�����Ĺ��򶷰�������ԭ�����ֺ��ܡ�
LONG
	);
	set("title", HIR "Ѫ��������" NOR);
	set("gender", "����");
	set("class", "huanxi");
	set("age", 65);
	set("attitude", "friendly");
	set("shen_type", -1);
	set("str", 35);
	set("int", 30);
	set("con", 35);
	set("dex", 35);
	set("max_qi", 52100);
	set("eff_jing", 9600);
	set("max_jing",9600);
	set("max_jingli",8600);
	set("eff_jingli", 8600);
	set("no_bark",1);
	set("book",1);

	set("neili", 32500);
	set("max_neili", 32500);
	set("jiali", 250);
	set("combat_exp", 12500000);
	set("score", 500000);
	set("unique", 1);
	set("quest/xd/xddf/huaxue/pass",1);
	set("quest/xd/xddf/pizhi/pass",1);
	set("quest/xd/xdj/xuedao/pass",1);
	set("quest/xd/jglts/jingang/pass",1);
	set("quest/xd/xddf/chilian/pass",1);

	set_skill("huanxi-chan", 200);
	set_skill("literate", 250);
	set_skill("force", 500);
	set_skill("xuedao-daofa", 520);
	set_skill("dodge", 500);
	set_skill("xueying-dunxing", 500);
	set_skill("strike", 500);
	set_skill("hongsha-zhang", 500);
	set_skill("hand", 500);
	set_skill("lansha-shou", 500);
	set_skill("blade",520);
	set_skill("xuedao-jing",500);
	set_skill("parry", 500 );
	set_skill("jingang-liantishu", 500 );
	
//	map_skill("blade", "xuedao-daofa");
	map_skill("force", "xuedao-jing");
	map_skill("dodge", "xueying-dunxing");
	map_skill("hand", "lansha-shou");
	map_skill("parry", "jingang-liantishu");
	map_skill("strike", "hongsha-zhang");
	map_skill("blade", "xuedao-daofa");

	prepare_skill("hand","lansha-shou");
	prepare_skill("strike","hongsha-zhang");

	create_family("Ѫ����", 4, "����");
	set("class", "huanxi");
	set("chat_chance", 2);
	set("chat_msg", ({
		"Ѫ������̧��ͷ��������˼�����������������Բ�ˣ�����ɽɱ���˼������ˡ���\n",
		"Ѫ������޺޵�˵����ʲôʱ��������ԭ�����ָ��췭�ظ�����\n",
		"Ѫ������ҧ���гݣ���¶�׹��˵�����´�����ն�ݳ�����һ�����Ҳ��������\n",
		"Ѫ���������������������ʹ��ˣ�������һ��Ҳ����������������Ϊ���⡣\n",
	}) );
	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: exert_function, "yuxue" :),
		(: exert_function, "xuedao" :),
		(: exert_function, "xuesha" :),
		(: perform_action, "blade.chuanxin" :),
		(: perform_action, "blade.liuxing" :),
		(: perform_action, "blade.shendao" :),
		(: perform_action, "blade.chilian" :),
		(: perform_action, "blade.bafang" :),
		(: perform_action, "blade.huaxue" :),
		(: perform_action, "blade.pizhi" :),
		(: perform_action, "blade.jixue" :),

	}));

	setup();
	carry_object("/d/xueshan/npc/obj/longxiang-jiasha")->wear();
	if (clonep()){
		weapon = unew("clone/weapon/blade/xuedao");
		if(!weapon)weapon=new(BINGQI_D("xinyuedao"));
		weapon->move(this_object());
		weapon->wield();
	}
	//add_money("gold",5);
}
