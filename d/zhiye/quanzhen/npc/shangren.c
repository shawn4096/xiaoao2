// waiter.c


inherit NPC;
inherit F_VENDOR;

void create()
{
	set_name("����", ({"shang ren","shangren" }) );
	set("gender", "����" );
	set("age", 22);
	set("long", "��λ������Ц�����æ�ţ�ӭ������������ʱ������ڲ����ϵ�Ĩ��������\n");
	set("combat_exp", 100);
	set("attitude", "friendly");
	set("rank_info/respect", "���");

	set("vendor_goods", ({
		//(["name": MISC_D("denglong"), "number":10]),
		(["name": MISC_D("fire"), "number":10]),
		(["name": "/d/quanzhen/npc/obj/guijia", "number":1]),
		//(["name": MISC_D("fire"), "number":10]),
	}));

	set("inquiry", ([
	//	"����ѧʿ" : (: ask_me :),
       //	"zhaxueshi" : (: ask_me :),
	]));
	set("per", 15);

	setup();/**/
}
void init()
{
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}
/*
void die()
{
	object ob;
	
	
	if (!query_temp("living"))
	{
		ob = new("/d/quanzhen/npc/shangren");
		
		
		   ob->move("/d/gumu/jishi");
	}
	::die();
}
*/