// ����

inherit NPC;
#include <ansi.h>

string ask_fish();
string ask_yideng(string name);
int check_yuren(object me);

string ask_diao();

void create()
{
	set_name("����", ({ "yu ren", "yu", "ren" }) );
	set("long", "����ԼĪ��ʮ������ͣ�һ�ź�����Ĺ��������������������������\n");
	set("gender", "����" );
	set("age", 45);
	set("str", 30);
	set("con", 30);
	set("dex", 25);
	set("int", 25);
	set("per", 20);
	set("unique", 1);
	set("attitude", "friendly");

	set("max_qi", 25000);
	set("max_jing", 12800);
	set("eff_jingli", 13600);
	set("neili", 18000);
	set("qi", 25000);
	set("jingli", 13600);
	set("max_neili", 18000);
	set("jiali", 200);

	set("combat_exp", 12300000);
	set("score", 5000);

	set_skill("parry", 400);
	set_skill("dodge", 400);
	set_skill("force", 400);
	set_skill("literate", 200);
	set_skill("qiantian-yiyang", 400);
	set_skill("tianlong-xiang", 400);
	set_skill("finger", 400);
	set_skill("yiyang-zhi", 400);
	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "yiyang-zhi");
	map_skill("force", "qiantian-yiyang");
	map_skill("finger", "yiyang-zhi");
	prepare_skill("finger","yiyang-zhi");

	set("inquiry", ([
		"������" : "�����޾��ǽ�ɫ�������㡣",
		"һ�ƴ�ʦ" :(: ask_yideng, "һ�ƴ�ʦ" :),
		"�λ�ү" : (: ask_yideng, "�λ�ү" :),
		"���ž���" :(: ask_diao:),

	]));
	setup();

	carry_object(ARMOR_D("b_cloth"))->wear();
	carry_object(ARMOR_D("caoxie"))->wear();
}
string ask_diao()
{
	object me;
	int i,j;

	me=this_player();
	if (!me->query_temp("quest/tls/askzhu"))
	{
		command("say �������ʶô��\n");
		return "�ߣ�\n";
	}
	//���ƴ���
	if (me->query("quest/tls/qxbf/diao/pass"))
		return "�㲻���Ѿ�������޵��־�ѧ����!\n";
	if (time()-me->query("quest/tls/qxbf/diao/time")<86400)
		return "������̫Ƶ����\n";
	if (me->is_busy()) return "������æµ�У�\n";
	if (!me->query_temp("quest/tls/giveyu"))
	{
		command("say ԭ����Ҫ��ѧ�����������\n");
		command("say ��С�ӣ���Ȼ��������ã��������ˣ�\n");
		  j = 20;
		  if(me->query("m-card-vip")) j =  18;
		  if(me->query("y-card-vip")) j =  15;
		  if(me->query("buyvip"))     j =  10;
		  i=random(j);

		  if (i<5 
			 && me->query("kar")<31
			 && random(me->query("kar"))>24)
		  {       
			  tell_object(me,HIM"\n�㰴�����˵�ָ��Ǭ��һ������ע�������У����еĵ��Ͳ���������һ����\n"NOR);
			  message_vision(HIG"\n$N�����ʹ��������͵ļ���һ���ӻ�Ȼ��ͨ����\n"NOR,me); 
			  tell_object(me,HIR"��ϲ�����ܵ��ŵ��־������ɹ���\n"NOR);
			  me->set("quest/tls/qxbf/diao/pass",1);
			  //me->set("title",HIC"ȫ��� ���칦����"NOR);
			  log_file("quest/tlsdiao", sprintf("%s(%s) ʧ��%d�γɹ��⿪���־�����Դ��%d�����飺%d��\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/tls/qxbf/diao/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			  me->start_busy(1);
			}
			else
			{
			 tell_object(me,HIG"\n���˼��ã�����Ҫ�졣\n"NOR);
			 message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿���,�����Լ���ʵ�����ˡ�\n"NOR,me); 
			 tell_object(me,HBBLU"\n�ܿ�ϧ���㱾�γ��Ե��־�����ʧ�ܣ�\n"NOR);
			 tell_object(me,HBBLU"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
			 tell_object(me,HBBLU"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
			 log_file("quest/tlsdiao", sprintf("%s(%s) ���ܵ��־�ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/tls/qxbf/diao/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			 me->add("quest/tls/qxbf/diao/fail",1);
			 me->set("quest/tls/qxbf/diao/exp", me->query("combat_exp") );
			 me->start_busy(1);
			 me->set("quest/tls/qxbf/diao/time",time());
			}
		me->delete_temp("quest/tls");
		return "�ҵĽ����ޣ�\n";
	 }
		
	
	command("say ������ң������ڵ������ޣ�\n");
	command("say �ò����������Һܲ����ģ��������ң�\n");
	return "��Ҫ�����ޣ�\n";
}
string ask_yideng(string name)
{
	object me= this_player();
    


	if ( name == "�λ�ү" )
		return "�λ�ү���Ѳ��ڳ����ˣ�";

	if ( me->query_temp("yideng/boat"))
		return "�Ҳ����Ѿ���������ɽ�ķ�����ô��";

	if ( me->query_temp("yideng/yuren"))
		return "������ȥ�ҵĽ������أ�";

	if ( name == "һ�ƴ�ʦ" ){
		me->set_temp("yideng/yuren", 1);

		return "Ҫ����ʦ����Ҳ���ѣ������Ҹն�ʧ�����������ޣ���֪��λ"+RANK_D->query_respect(me)+"�ܷ����ץ�ء�";
	}
}

int accept_object(object me, object ob)
{
	if ( ob->query("id") != "jin wawa" ){
		command("say ���������Ҹ���");
		return 0;
	}
	if ( ob->query_temp("owner") != me->query("id")){
		command("say �������õ���Խ����ް���");
		return 1;
	}
	message_vision(CYN"$N������β�����������з������������۶��У�������䣬����Ц�������ֲ�\n"+
			"�ý��������㣬��Ȼ��С�����޽�һ�㡣��\n"+
			HIW"\n$N���ֽ���$n����$nϲ��ü�ң��������������ֽ��˹�ȥ��\n\n"NOR, me, this_object());
	me->delete_temp("yideng");
	me->set_temp("yideng/boat", 1);
	if (me->query_temp("quest/tls/askzhu"))
	{
		command("pat "+me->query("id"));
		command("say ��Ȼ�����ﰲ���㵽������������ʲô�¾����Ұɣ�\n");
		me->set_temp("quest/tls/giveyu",1);
	}
	me->add_busy(2);
	if (me->query_temp("nqg/askyingok"))
	{
		command("hehe ");
		command("hehe "+me->query("id"));
		command("say ��С�ӣ����治������Ȼû�б�ˮ��������\n");
		command("say �������ɣ�");
		tell_object(me,HIR"\n\n\n������֪������ʲô�裬�������еĴ���������ȥ��\n"NOR);
		me->add_busy(2+random(2));
		this_object()->kill_ob(me);
		call_out("check_yuren",1,me);
		call_out("dest", 1, ob);
		return 1;

	}else call_out("give_bonus", 1, me, this_object());
	
	call_out("dest", 1, ob);
	return 1;
}

void dest(object ob)
{
	if ( !ob) return;
	destruct(ob);
}

int give_bonus(object me, object ob)
{
	object boat, jiang;

	message_vision("\n", me);
	command("say ����ɽ˵�����ѣ�˵��ȴҲ���׵ý���������ת��ɽ�ǣ��ѷ���\n"+
		"������һ������������������֮�У��⶯�������ڼ������������ϾͿ����ˡ�");
	boat = unew(__DIR__"../obj/boat");
	jiang= unew(__DIR__"../obj/jiang");
	boat->move(me);
	jiang->move(me);
	message_vision("$N����$nһ��"HIB"����"NOR"��\n",this_object(), me);
	message_vision("$N����$nһ��"BLU"����"NOR"��\n",this_object(), me);
	
	return 1;
}

void die()
{
	object ob,me;
	object boat, jiang;
	 me=this_player();
	
	if (!query_temp("living"))
	{

	
		if (!objectp(jiang=present("tie jiang",me))&& me->query_temp("nqg/askyingok"))
		{
			message_vision("���������֮���ѵ�һ��"BLU"����"NOR"��\n", me);
			jiang= unew(__DIR__"../obj/jiang");
			jiang->move(me);
		}
		if (!objectp(boat=present("tie zhou",me))&& me->query_temp("nqg/askyingok"))
		{
			message_vision("���������֮���ѵ�һ��"HIB"����"NOR"��\n", me);
			boat= unew(__DIR__"../obj/boat");
			boat->move(me);

		}
	

	}
	::die();
}


int check_yuren(object me)
{
	object yuren;
	object boat, jiang;
	yuren=present("yu ren",environment(me));
    if (objectp(yuren)&& me->is_fighting(yuren))
    {
		remove_call_out("check_yuren");
		call_out("check_yuren",2,me);
		return 0;
    }
	if (!objectp(me)) return 0;
	
		boat = unew(__DIR__"../obj/boat");
		jiang= unew(__DIR__"../obj/jiang");
		boat->move(me);
		jiang->move(me);
		message_vision("���������֮���ѵ�һ��"HIB"����"NOR"��\n", me);
		message_vision("���������֮���ѵ�һ��"BLU"����"NOR"��\n", me);
		return 1;
	
}