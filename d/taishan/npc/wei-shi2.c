// wu-shi2.c ������ʿ

#include <ansi.h>

inherit NPC;

void create()
{
	set_name(HIR "������ʿ" NOR, ({ "wei shi", "shi", "guard" }) );
	set("gender", "����");
	set("age", 35);
	set("long",
		"����λ������ʿ�������ּף���ִ������˫Ŀ���⾼���������Ѳ�������ܵ����Ρ�\n");
	set("combat_exp", 80000);
        set("shen_type", 1);
	set("attitude", "heroism");
        set("unique", 3);

	set("str", 28);
	set("con", 23);
	set("int", 20);
	set("dex", 26);

	set("max_qi", 450);
	set("eff_qi", 450);
	set("qi", 450);
	set("max_jing", 200);
	set("jing", 200);
	set("neili", 400);
	set("max_neili", 400);
	set("jiali", 25);
	set("shen_type", 0);

	set_temp("apply/attack",  40);
	set_temp("apply/defense", 40);

	set_skill("sword", 80);
	set_skill("unarmed", 60);
	set_skill("parry", 80);
	set_skill("dodge", 80);

	setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/armor/armor")->wear();
}

void init()
{
	object ob1;
	string mengzhu;
	
	if(!( ob1 = find_living("zhong shentong")) )
	ob1 = load_object("/clone/npc/zhong-shentong");
	mengzhu = ob1->query("winner");

	if( this_player()->query("id") == mengzhu ) {
		message_vision(HIY "������ʿ���𳤽�����$N�����󺰣��������꣬���꣬�����꣡\n" NOR, 
		this_player());
		return;
	}	
	::init();
}