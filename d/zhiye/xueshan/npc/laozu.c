// laozu.c Ѫ������
// by iceland
// by emnil

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
#include "/d/suzhou/npc/lchj.h";

string ask_xuedao();
string ask_zijindao();
string ask_jiasha();
string ask_diyun();

void create()
{
	object weapon , armor;

	set_name("Ѫ������", ({ "xuedao laozu", "laozu","xuedaolaozu" }));
	set("long",@LONG
����ĸ��ݣ��������ݣ�һ˫�۾�����׺ݵĹ�â�����˲���ֱ�ӡ����ڽ���
���Բ��̺�ɫ�����ƣ���ƾһ��Ѫ�����Ĺ��򶷰�������ԭ�����ֺ��ܡ�
LONG
	);
	set("title", HIR "Ѫ��������" NOR);
	set("gender", "����");
	set("class", "huanxi");
	set("no_bark",1);
	set("age", 65);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 39);
	set("int", 30);
	set("con", 35);
	set("dex", 35);
	set("max_qi", 11500);
	set("max_jing", 8000);
	set("eff_jingli", 8000);
	set("neili", 20000);
	set("max_neili", 20000);
	set("jiali", 250);
	set("combat_exp", 4500000);
	set("score", 50000);
	set("unique", 1);

	set_skill("huanxi-chan", 200);
	set_skill("literate", 250);
	set_skill("sword", 250);
	//set_skill("blade", 250);
	set_skill("mingwang-jian", 250);
	set_skill("force", 451);
	set_skill("xuedao-dafa", 451);
	set_skill("dodge", 340);
	set_skill("yuxue-dunxing", 340);
	set_skill("claw", 350);
	set_skill("tianwang-zhua", 320);
	set_skill("hand", 350);
	set_skill("dashou-yin", 320);
	set_skill("blade", 451);
	set_skill("xuedao-jing", 451);
	set_skill("parry", 340 );

	map_skill("force", "xuedao-dafa");
	map_skill("dodge", "yuxue-dunxing");
	map_skill("hand", "dashou-yin");
	map_skill("parry", "xuedao-jing");
	map_skill("claw", "tianwang-zhua");
	map_skill("blade", "xuedao-jing");

	prepare_skill("hand","dashou-yin");
	prepare_skill("claw","tianwang-zhua");

	create_family("Ѫ����", 1, "����");
	set("class", "huanxi");

	set("env/jixue",10);
	set_temp("xd/chilian",1);
	set_temp("xuedao/yuxue",1);

	set("chat_chance", 2);
	set("chat_msg", ({
	       CYN"Ѫ������̧��ͷ��������˼�����������������Բ�ˣ�����ɽɱ���˼������ˡ���\n"NOR,
	       CYN"Ѫ������޺޵�˵����ʲôʱ��������ԭ�����ָ��췭�ظ�����\n"NOR,
	       CYN"Ѫ������ҧ���гݣ���¶�׹��˵�����´�����ն�ݳ�����һ�����Ҳ��������\n"NOR,
	       CYN"Ѫ���������������������ʹ��ˣ�������һ��Ҳ����������������Ϊ���⡣\n"NOR,
	       CYN"Ѫ�������������������Ѫ����ʮ���������Ŀ��Ǻö���ѽ��һ��Ҫ�غá�\n"NOR,
	}) );

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: perform_action, "blade.jixue" :),
		(: perform_action, "blade.shendao" :),
		(: perform_action, "blade.chilian" :),
		(: perform_action, "blade.wuying" :),
	}));

	set("inquiry", ([
		"Ѫ��":		(: ask_xuedao :),
		"xuedao":	(: ask_xuedao :),
		"�Ͻ�": 	(: ask_zijindao :),
		"zijin dao":	(: ask_zijindao :),
		"ʮ����������":	(: ask_jiasha :),
		"jiasha":	(: ask_jiasha :),
		"����":		"үү��û�գ���ȥ����ͽ�ܱ����������ʰɡ�",
		"job" :		"үү��û�գ���ȥ����ͽ�ܱ����������ʰɡ�",
		"��Ů":		"����ϲ����Ů������Ҫ����Ū������Т��үү���ٺ�...",
		"girl":		"����ϲ����Ů������Ҫ����Ū������Т��үү���ٺ�...",
		"beauty":	"����ϲ����Ů������Ҫ����Ū������Т��үү���ٺ�...",
// add quest by tangfeng
		"����" : (: ask_diyun :),
		"���վ�" : random(2)?"��˵������ī��÷���ϵ��ڹ��ķ���":"�Ҽǵ������֮�ھͿ������վ��ڹ��ķ���",
		"����ɽ" : "÷�����ϵĵ��ӡ�",
		"�Դ�ƽ" : "÷�����ϵĵ��ӡ�",
		"�ݳ���" : "÷�����ϵĵ��ӡ�",
		"÷����" : "����ī��÷���ϣ���ϧ����ԩ������",
		"�仨��ˮ":"��˵��ʲô�����棿�ߣ����˻���ͷ�������Ķ��Ѿ�����ɱ�ˣ�",
		"������":"����ƽǹ�����ɡ������Ǹ��޳ܵ�ų��",
		"���˷�":"�����ƽ����˷硱���������Ѿ��Ѿ�����ɱ�ˣ�",
		"½����":"������½�󵶡����������Ѿ�����ɱ�ˣ�",
		"ˮ�":"�����½�ˮᷡ����������Ѿ�����ɱ�ˣ�",
		"ˮ��":"��С���ĵ��Ǳ�־����ϧ�ܶ��ˣ�����Ҳ��������ѩ���ˣ�",
       ]));

	setup();
	if (clonep()){
		weapon = unew(BINGQI_D("zijin-dao"));
		if(!weapon) weapon=new(BINGQI_D("xinyuedao"));
		weapon->move(this_object());
		weapon->wield();
		set_temp("apply/damage",180);

		weapon=new(BINGQI_D("xinyuedao"));
		weapon->move(this_object());
		weapon=new(BINGQI_D("xinyuedao"));
		weapon->move(this_object());

		armor = unew(ARMOR_D("lx_cloth"));
		if(!armor) armor=new("/d/xueshan/npc/obj/longxiang-jiasha");
		armor->move(this_object());
		armor->wear();
		set_temp("apply/armor",300);

		armor=new("/d/xueshan/npc/obj/longxiang-jiasha");
		armor->move(this_object());
	}
	add_money("gold",3);
}

void attempt_apprentice(object ob)
{
	if ((string)ob->query("family/family_name") != "Ѫ����") {
		command("say"+ RANK_D->query_respect(ob) + "���Ǳ��µ��ӣ������ﵷʲô�ң���");
		return;
	}

	if ((int)ob->query_skill("xuedao-dafa", 1) < 150) {
		command("say ��Ѫ���Ÿ����书�����ڹ��ศ��ɡ�");
		command("say"+ RANK_D->query_respect(ob) + "�ٰ�����ͨ��������������б��ŵ��ķ��ɡ�");
		return;
	}

	if( (string)ob->query("gender") == "����" ) {
		command("say"+ RANK_D->query_respect(ob)+ "�����ȱ��ȫ���������������\n");
		return;
	}
	if ((int)ob->query("shen") > -100000) {
		command("hmm");
		command("say ��Ѫ����������Զ���Щ��ν�Ľ��������ĸ�����������ӣ�");
		command("say �������ڵ��������������Ϊͽ�����»ᱻ�˳�Ц��");
		return;
	}
	command("say �����Ҿ�ϲ���������������ˡ��ã�������Ϊ�ҵ��Ӱɡ�");
	command("recruit " + ob->query("id"));

	ob->set("title", HIR"Ѫ�������״�����" NOR);
}
/*
void reset()
{
	object me = this_object(), ob;

	if (clonep() && (ob = unew(BINGQI_D("xuedao")))) {
		ob->move(me);
		command("wield xue dao");
	}
	if (clonep() && (ob = unew(BINGQI_D("zijin-dao")))) {
		ob->move(me);
		command("wield zijin dao");
	}
	if (clonep() && (ob = unew("/d/xueshan/npc/obj/longxiang-jiasha"))) {
		ob->move(me);
		command("wear jiasha");
	}
}
*/
string ask_xuedao()
{
        object me=this_player() , weapon;
        int i;

        if ((string)me->query("family/family_name") != "Ѫ����")
                i = 3;
        else
                i = 1;

        if(me->query_temp("xs/xs_job") >= 1*i) {
                weapon = present("xue dao", this_object());
                if(!objectp(weapon))    weapon = unew(BINGQI_D("xuedao"));
                if(!objectp(weapon))
                        return "Ѫ�����ڲ��������";  

                command("unwield xue dao");
                weapon->move(me);
                command("emote ����һ��Ѫ����");
                command("wield xinyue dao");
                me->set_temp("xs/xs_job",0);
        }
        else
                return "����Ҫ��ѵ�������Ҫ��˵���Ȼ����г���Ŀ����ң�������Ҫ˵��ѽ��\n"+
                       "��˵���ҿ϶������ģ���������˵���Ҳ����㣬���㲻˵��ƫҪ����ɡ�\n";

        return "�ã����Ѫ������ȥ�ɣ����Ŷ�ɱ����������������";
}

string ask_zijindao()
{
        object me=this_player() , weapon;

        if ((string)me->query("family/family_name") != "������")
                return "����������ˣ���ѵ���ô�ܸ����أ�";

        if ((int)me->query("xs_job") < 50 )
                return "�Ķ������ж����õ�ʵ�ʳɼ������ҿ��\n";

        weapon = present("zijin dao", this_object());
        if(!objectp(weapon))    weapon = unew(BINGQI_D("zijin-dao"));
        if(!objectp(weapon))
                return "�Ͻ����ڲ��������";        

        command("unwield zijin dao");
        weapon->move(me);
        command("emote ����һ���Ͻ𵶡�");
        command("wield xinyue dao");

        return "�ã�����Ͻ�����ȥ�ɣ���ס��Ҫ������ѽ��";
}

string ask_jiasha()
{
        object me=this_player() , armor;
        int i;

        if ((string)me->query("family/family_name") != "������")
                i = 5;
        else
                i = 1;

        if(me->query_temp("xs/xs_job") >= 1*i) {
                armor = present("shisan longxiang", this_object());
                if(!objectp(armor))     armor = unew(ARMOR_D("lx_cloth"));
                if(!objectp(armor))
                        return "ʮ�������������ڲ��������";  

                command("remove shisan longxiang");
                armor->move(me);
                command("emote ����һ��ʮ���������ġ�");
                command("wear jiasha");
                me->set_temp("xs/xs_job",0);
        }
        else
                return "�Ķ������ж����õ�ʵ�ʳɼ������ҿ��\n";

        return "�ã����ʮ��������������ȥ�ɣ����Ŷ�����Ҽ������ﰡ��";
}
void destroying(object obj)
{
	if (!obj) return;
	if (userp(obj))
		command("drop "+obj->parse_command_id_list()[0]);
	else
		destruct(obj);
}
string ask_diyun()
{
	object me,ob;
	me = this_player();
	ob = this_object();
	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
	   return ""+RANK_D->query_respect(me) +"�����Լ�С��ͨ���ɣ�";
	}
	if(me->query(QUESTDIR1+"over" ))
	{
	   command("claw "+me->query("id"));
	   return "�Ǹ����ͷ��С����ôͻȻ��ô�����ˣ�";
	}
	if(!me->query(QUESTDIR1+"start" ))
	{
	   command("say");
	   return "���Ҵ�ѩ���ȥ�ˣ�������Ͷ����ˡ�";
	}
	if(!me->query_temp(QUESTDIR1+"askbaoxiang" ))
	{
	   command("say");
	   command("claw "+me->query("id"));
	   return "�ĸ����ƣ�����˭��";
	}
	if(me->query_temp(QUESTDIR1+"asklaozu"))
	{
	   command("en");
	   return "�Ǹ����ͷ��Ҳ�����Ҳ�������Ӧ�ö����ˣ�";
	}
	command("smash");
	message_vision(HIY"$N��ɫ�԰��ؿ���$n��\n", ob,me);
	command("noshame");
	me->set_temp(QUESTDIR1+"asklaozu",1);
	return "����Ȼ�������ԣ�ֻ�����ֿ�ԣ����Ҵ�ѩ���ȥ�ˣ�������Ͷ����ˡ�";
}
