#include <ansi.h>
inherit NPC;
void greeting(object ob);
int accept_fight(object ob);
int ask_kuaidao();
string ask_yilin();
string ask_linghuchong();


void create()
{
	seteuid(getuid());
	set_name("�ﲮ��", ({ "tian boguang", "tian","boguang" }));
	set("long", "��һ��Ʈ�ݵİ�ɫ�������������š�\n");
	set("nickname", HIM "�������" NOR);
	set("gender", "����");
	set("age", 37);
	set("attitude", "peaceful");
	set("shen_type", -1);

       set("per", 23);
	set("str", 25);
	set("int", 24);
	set("con", 25);
	set("dex", 35);

	set("qi", 25000);
	set("max_qi", 25000);	
	set("combat_exp", 12500000);
	set("score", 40000);

	set("jing", 3800);
	set("max_jing", 3800);

	set("jingli", 4800);
	set("max_jingli", 4800);
	set("eff_jingli",4800);

	set("neili", 20000);
	set("max_neili", 20000);
	
	set("jiali", 200);
	set("quest/hmy/tmd/kuaidao/pass",1);

	set_skill("blade",500);
	set_skill("parry", 450);
	set_skill("force", 450);
	set_skill("strike", 500);
	set_skill("dodge", 450);

	set_skill("lingxu-bu", 450);
	set_skill("tianmo-jue", 200);

	set_skill("tianmo-zhang", 450);
	set_skill("tianmo-gong", 450);
	set_skill("tianmo-dao", 500);

	map_skill("dodge", "lingxu-bu");
	map_skill("parry", "tianmo-dao");
	map_skill("blade", "tianmo-dao");
    map_skill("strike","tianmo-zhang");
	map_skill("force","tianmo-gong");
	prepare_skill("strike","tianmo-zhang");
    set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
                (: perform_action, "blade.pi" :),
				(: perform_action, "blade.jingshen" :),
				(: perform_action, "blade.huashen" :),
				(: perform_action, "blade.kuaidao" :),
				(: exert_function, "tianmo" :),
				(: exert_function, "jieti" :),
        }) );
		
	set("chat_chance", 10);
	set("chat_msg", ({
		CYN "�ﲮ��Ц�������Ҳû��ϵ�����ͷ���������¾���С�����ˡ�\n" NOR,
		CYN "����һ�������������ʶŮ�ˣ�ֻҪ���Ź�һ�飬��Բʮ��֮���Ҿ����ҵ�����\n" NOR,
		CYN "������У��������ƺ��ģ���\n" NOR,
		CYN "������������ӣ���\n" NOR,

	}) );
	set("inquiry",([
		"���쵶����" : (: ask_kuaidao :),
		"����" : (: ask_yilin :),
		"�����" : (: ask_linghuchong :),
		//"�������" : (: ask_dragon :),
        ]) );

	setup();
	carry_object(BINGQI_D("blade"))->wield();
	carry_object(ARMOR_D("cloth"))->wear();
	add_money("gold",10);
}

void init()
{
	object ob;

	::init();

	if( interactive(ob = this_player()) && !is_fighting() ) 
       {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}
void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	if ((string)ob->query("gender")=="Ů��")
	{
	if (ob->query("age")<26) 
		say(CYN "�ﲮ��Ц����С���ӣ����г��㡭����������֮�ݡ���һ���¥����Ϊ�㿪�ġ����Ǻȸ�������ҿ����ա�\n" NOR);     
	else 
		say(CYN "�ﲮ��Ц������������ϧ̫���˵㣬�ҿ�ûθ�ڡ�\n" NOR);     
	}
	else 
		say(CYN "�ﲮ��Ц�������֣���λ"+RANK_D->query_respect(ob) + "����"
                    "���������С��������Ҳûʲô�£����������ž��ǡ�\n" NOR);									
					
	return;
}

int accept_fight(object ob)
{
	if ((string)ob->query("gender") == "Ů��")
	{
		write(CYN "�ﲮ��Ц���������ɱ��̫��ϧ�˵ġ�\n" NOR);
		return 0;
        }
	return 1;
}
string ask_yilin()
{
	object me=this_player();
	if (me->query("family/family_name")!="�������")
	{
		command("say �㲻���Ҵ�������̵��ӣ�����������\n");
		command("blade "+me->query("id"));
		return "�ߣ�";
	}
	if (me->query("quest/hmy/tmd/kuaidao/pass"))
	{
		command("say ���Ѿ��⿪���⵶��������������ǲ����ү��ô��\n");
		command("blade "+me->query("id"));
		return "�ߣ�";
	}
	if (me->query_skill("tianmo-dao",1)<450)
	{
		command("say �����ħ������450������Ҳ��ⲻ�ˣ�\n");
		command("blade "+me->query("id"));
		return "�ߣ�";
	}
	if (me->query("str")<35)
	{
		command("say ��������������35������Ҳ��ⲻ�ˣ�\n");
		command("blade "+me->query("id"));
		return "�ߣ�";
	}

	command("say ��������·����������Сʦ����һ�����ġ�\n");
	if (present("yi lin",environment(me)))
	{
		command("say ������λС��Ůʦ̫�������������ô��\n");
		command("18mo ");
	}
	//command("say �������������˻�ɽ��ͽ����壬����Ȼ�������ң����ҵ��ܾ�������\n");
	command("say �����Һ�����ʦ����һ��̸�����������ʱ������������ɵĲ�Ӭ��\n");
	me->set_temp("kuaidao/askyilin",1);
	command("say ��Ը�����ҵֵ�ס��һ��ô��"+HIY"annswer yes |answer no\n");

	return "��Щ��Ӭ��Ȼ�������кųơ�������㡱���ҿ��ǡ�������ޡ�����࣡\n";
}


string ask_linghuchong()
{
	object me=this_player();
	
	if (!me->query_temp("kuaidao/answeryes"))
	{
		command("say �ϴ�����������һ��С���㶼�������ң�������\n");

		command("say �����ں�����ʦ̫���죬̸���룬̸����������ɧ���ң�\n");
		return "һѽ���������������õ�ͷ����.......!\n";
	}
	if (present("hou renying",environment(me)))
	{
		command("say ����Ӣ������֮һ�����Ķ��Աߣ����ķ���\n");
		return "һѽ���������������õ�ͷ����.......!\n";
	}
	if (present("hong renxiong",environment(me)))
	{
		command("say ������������֮һ�����Ķ��Աߣ����ķ���\n");
		return "һѽ���������������õ�ͷ����.......!\n";
	}
	if (present("yu renhao",environment(me)))
	{
		command("say ���˺�������֮һ�����Ķ��Աߣ����ķ���\n");
		return "һѽ���������������õ�ͷ����.......!\n";
	}
	if (present("yu renjie",environment(me)))
	{
		command("say ���˽�������֮һ�����Ķ��Աߣ����ķ���\n");
		return "һѽ���������������õ�ͷ����.......!\n";
	}
	if (present("yuling zi",environment(me)))
	{
		command("say ̩ɽ�ϵ������������ʿ�����Ķ��Աߣ����ķ���\n");
		return "һѽ���������������õ�ͷ����.......!\n";
	}

	command("say ��������ǻ�ɽ��ͽ���Һ�����ʱ�����������棡\n");
	command("say ��ʱ��������һ��������������üƽ��ҽ�ס��\n");
	command("say ��Ը������������������һ��ô�������ͨ��"HIY"answer yes | no���ش�\n");
	me->delete_temp("kuaidao/askyilin");
	if (!present("yi lin",environment(me)))
	{
		command("say ������λС��Ůʦ̫�������������ô��\n");
		command("18mo ");
	}
	command("say ����嵱ʱ˵�����Ŵ����µڶ����Ҳ�������������������ս��\n");
	//command("say ");
	me->set_temp("kuaidao/asklhc",1);
//	call_out("qingcheng_dizi",3,me);
	return "�����˵�����Ž����С�é�޽����������Ժ��ҵĿ쵶����һս��\n";

}


int ask_kuaidao()
{
	int i,j,k;
	object me=this_player();
	if (!me->query_temp("kuaidao/answerlhcyes"))
	{
		command("say ���ҷ��׷ǹʣ���ƾʲô������[�쵶����]����\n");
		return 1;
	
	}
	if (!me->query("quest/hmy/tmd/pass"))
	{
		command("say ����ħ���Ļ���û��ã���������ǧ���ж����ᣬ����Ҳ�״\n");
		return 1;
	}
	if (present("hou renying",environment(me)))
	{
		command("say ����Ӣ������֮һ�����Ķ��Աߣ����ķ���\n");
		return 1;
	}
	if (present("hong renxiong",environment(me)))
	{
		command("say ������������֮һ�����Ķ��Աߣ����ķ���\n");
		return 1;
	}
	if (present("yu renhao",environment(me)))
	{
		command("say ���˺�������֮һ�����Ķ��Աߣ����ķ���\n");
		return 1;
	}
	if (present("yu renjie",environment(me)))
	{
		command("say ���˽�������֮һ�����Ķ��Աߣ����ķ���\n");
		return 1;
	}
    
	if (present("linghu chong",environment(me)))
	{
		command("say ��������Ķ��Աߣ����ķ���\n");
		return 1;
	}
	if (me->query("family/family_name")!="�������")
	{
		command("say �㲻���Ҵ�������̵��ӣ�����������\n");
		command("blade "+me->query("id"));
		return 1;
	}
	if (me->query("quest/hmy/tmd/kuaidao/pass"))
	{
		command("say ���Ѿ��⿪���⵶��������������ǲ����ү��ô��\n");
		command("blade "+me->query("id"));
		return 1;
	}
	if (me->query_skill("tianmo-dao",1)<450)
	{
		command("say �����ħ������450������Ҳ��ⲻ�ˣ�\n");
		command("blade "+me->query("id"));
		return 1;
	}
	if (time()-me->query("quest/hmy/tmd/kuaidao/time")<86400)
	{
		command("say ������̫Ƶ���ˣ�\n");
		command("blade "+me->query("id"));
		return 1;
	}
	
	message_vision(HIY"�ﲮ�⣿��\n"NOR,me);
	 j = 20;
     if(me->query("m-card-vip")) j =  18;
     if(me->query("y-card-vip")) j =  15;
     if(me->query("buyvip"))     j =  10;
	i=random(j);
	
	k=random(me->query("kar"));
	if (me->query("kar")<31
		&&k>26
		&&i<4)
	{
       message_vision(HIC"\n\n$N��Ȼ���򣬻�Ȼ��������Ҫȫ���Ը���������죬ʹ�Է��������ֵ�����\n"
	   +"�ﲮ���ͷ˵��������һ��ȫƾһ��������ת�����ٳ��У����ж��Ҫ��죬���򣬶Է����Ʒ��������Σ���ˡ���\n"NOR,me);
	    message_vision(HIR"\n\n��ϲ�㣡�����������˽���ʮ���Ƶľ����似��ϰ�ÿ����лھ�����\n"NOR,me);
		command("chat* haha"+me->query("id"));
	   command("chat "+me->query("name")+"������ô��ʱ�����������˿쵶������");
	   command("chat "+"����������ﲮ��Ŀ쵶���������д����ˣ���\n");
	   command("chat* congra"+me->query("id"));
	  
	   log_file("quest/tmdkuaidao",sprintf("%s(%s) �ں�������¥���õ��ﲮ�������ָ��쵶��������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),k,i,me->query("quest/hmy/tmd/kuaidao/fail"),me->query("combat_exp"),me));
	   
	   me->set("quest/hmy/tmd/kuaidao/pass",1);
	   me->set("title",HIW"�쵶��������"NOR);
	   me->start_busy(1);

	   return 1;
	}
	else
	{
		message_vision(HIC"\n\n$N��Ȼ���ﲮ��˵�˿쵶�����ľ�Ҫ�����������ʹ�õľ�������һʱ֮��ȴ��������⡣\n"
		+"��ħ��������û�з��ӳ����������㻹���д������¸��ﲮ��ѧϰ�ˡ�\n"NOR,me);
		message_vision(HBWHT HIB"������ħ���쵶����ʧ�ܣ�"NOR,me);
		log_file("quest/tmdkuaidao",sprintf("%8s%-10s�õ��ﲮ�������ָ��쵶����������û�гɹ�������Ŭ������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),k,i,me->query("quest/hmy/tmd/kuaidao/fail"),me->query("combat_exp"),me));
		me->add("quest/hmy/tmd/kuaidao/fail",1);
		me->set("quest/hmy/tmd/kuaidao/time",time());
		me->start_busy(1);
		return 1;
	}     
	return 1;
}
