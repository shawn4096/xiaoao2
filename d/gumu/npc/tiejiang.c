// tiejiang.c ����

inherit NPC;
inherit F_VENDOR;
int ask_me(); 
 
void create()
{
	set_name("������", ({ "sun tiejiang", "sun", "tiejiang" }) );
	set("gender", "����" );
	set("age", 34);
	set("long", "����һλλ�������Ŵ����������������Ĵ�����������\n");
	set("combat_exp", 30000);
	set("attitude", "peaceful");
	set("rank_info/respect", "����");
	set("vendor_goods", ({
		(["name":"d/suzhou/npc/obj/changjian","number":15]),
		(["name":"d/suzhou/npc/obj/gangjian","number":20]),
		(["name":"d/suzhou/npc/obj/gangdao","number":15]),
		(["name":"d/suzhou/npc/obj/caidao","number":10]),
		(["name":"d/suzhou/npc/obj/tiechui","number":10]),
		(["name":"d/suzhou/npc/obj/bishou","number":10])
	}));
	set("inquiry", ([
		"ҩ��": (: ask_me :),
		//"��ͷ": "��ͷ... ��Ǹ����ͷ�Ѿ�������...", 
	]));
	setup();
	carry_object(ARMOR_D("cloth"))->wear();
}

void init()
{       
	object ob;

	::init();
	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	switch( random(2) ) {
		case 0:
			say( "����Ц�����˵������λ" + RANK_D->query_respect(ob) + "������ֻҪ�����ļһӦ�о��С�\n");
			break;
		case 1:
			say( "����Ц�Ǻǵ�˵����λ" + RANK_D->query_respect(ob) + "������Ҫ��ʲô��\n");
			break;
	}
}

int ask_me()
{
	object chu, me, ob;

	me = this_object();
	ob = this_player();
    if (ob->query("family/family_name")!="ȫ���"||!ob->query_temp("qz/caiyao"))
    {
		command("heng "+ob->query("id"));
		command("say ҩ���ҵ����У�ƾʲôҪ���㣿��\n");
		return 1;
    }     
	if ( present("yao chu", ob) ) {
		command("say �㲻�������𣬻���Ҫʲ�᣿\n");
		return 1;
	}
	command("look " + ob->query("id")); 
	command("say ��Ȼ��ȫ���¹������ָʾ���Ǿͺã�\n");

	command("say ����������һ������ûʲ���ã���Ҫ����ȥ�ɡ�\n");
	chu = new("/d/quanzhen/obj/yaochu");
	chu->set("no_sell", 1);
	chu->move(ob);
	message_vision("$N����$nһ����ҩר�õ�ҩ����\n", me, ob);
	ob->start_busy(1);

	return 1;
}
