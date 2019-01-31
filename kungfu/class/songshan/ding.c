// deng.c ��ɽ�ɵ�������� ���� 2004.12.15 add ask gold
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_jueji();
int ask_gold(object who);

void create()
{
	set_name("����", ({ "ding mian", "ding", "mian" }));
	set("nickname", HIR"������"NOR);
	set("long", "����λ���ֵ����ߣ�����Ŀ�ΰ������ɽ�������˵Ķ�ʦ�������ֶ��㡣\n");
	set("gender", "����");
	set("age", 51);
	set("per", 18);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 33);
	set("int", 23);
	set("con", 25);
	set("dex", 25);
	set("unique", 1);
	set("env/wimpy", 70);

	set("max_qi", 23000);
	set("max_jing", 5000);
	set("eff_jingli", 5000);
	set("max_neili", 23500);
	set("jiali", 200);
	set("combat_exp", 9500000);
	set("shen", -1640000);
	set_skill("songyang-jue", 180);

	set_skill("literate", 200);
	set_skill("force", 450);
	set_skill("parry", 450);
	set_skill("sword", 450);
	set_skill("dodge", 450);
	set_skill("hand", 450);
	set_skill("zhongyuefeng", 450);
	set_skill("songyang-shou", 450);
	set_skill("hanbing-zhenqi", 450);
	set_skill("songshan-jian", 450);

	map_skill("force", "hanbing-zhenqi");
	map_skill("dodge", "zhongyuefeng");
	map_skill("hand", "songyang-shou");
	map_skill("parry", "songyang-shou");
	map_skill("sword", "songshan-jian");

	prepare_skill("hand", "songyang-shou");
	set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
		(: perform_action, "hand.junji" :),
		(: perform_action, "hand.tuota" :),
		(: exert_function, "juhan" :),
		(: exert_function, "hanbing" :),
	}));

	create_family("��ɽ��", 3, "����");

	set("inquiry", ([
		"��������" : (: ask_gold :),
	//	"�����־���" : (: ask_jueji :),
		"����": "������и����ֽУ�����������(junji)����ȡ�Դ˾����塣",
		"��������": "�ٺ٣��뵱�����������˺�ɽ�������ᣬ�õľ��������ַ��ľ�����",
		"��ɽ��" : "������ɽ������������֮�ף�\n",
		"��������" : "������������������֮�������޴󣬿������֡��䵱���⡣\n",
		"������" : "���������ǵ������ˣ�������ɲ⡣\n",
	]) );

	setup();
	carry_object(ARMOR_D("changpao1"))->wear();
	add_money("gold", 1);
}

int ask_gold(object who)
{
	object me = this_player();
	int gold = 0;

	if( me->query("family/family_name") != "��ɽ��" ) {
		command("say ������ɽ�ɵ��£�" + RANK_D->query_respect(me) + "����ǲ�Ҫ���֣�");
		return 1;
	}

        if( (int)me->query_skill("hanbing-zhenqi", 1) < 216 ) {
		command("say " + RANK_D->query_respect(me) + "���ú�ѧϰ����ɽ���书�������ʶ�������������������Σ�");
		return 1;
	}

	if( me->query("songshan_given") >= 300 ) {
		command("say " + RANK_D->query_respect(me) + "�书��ǿ����Ȼ���ĳ������Ǿͷ������ϵЩ������������������ɣ�");
		return 1;
	}

	if( (int)me->query("songshan_given") + 10 < (int)me->query_skill("hanbing-zhenqi", 1) ) {
		if( (int)me->query_skill("hanbing-zhenqi", 1) > 300 ) 
			gold = 300 - (int)me->query("songshan_given");
		else gold = (int)me->query_skill("hanbing-zhenqi", 1) - (int)me->query("songshan_given");
		gold *= 10000;

		if( (int)me->query_skill("literate", 1) < 100 ) gold *= 5; 
		else if( (int)me->query_skill("literate", 1) >= 150 ) gold *= 3; 
		else gold *= 4; 

		command("interest");
		me->add("balance", gold);
		me->set("songshan_given", (int)me->query_skill("hanbing-zhenqi", 1));
		command("say ���ղ�����" + RANK_D->query_respect(me) + "����ѧ�ƺ��������ٰ���");
		command("say ��Ȼ" + RANK_D->query_respect(me) + "���ģ�����ͽ�" + MONEY_D->money_str(gold) + "�������Ǯׯ���㶨Ҫ�ú�����Ⱥ�������ɶ������֮λ����");
	} else command("say " + RANK_D->query_respect(me) + "������ɽ�����书�ư����֣�����ѧ���������ð���");
	return 1;
}

void attempt_apprentice(object ob)
{
	if (!ob->query("quest/ss/rumen/pass"))
	{
		command("say ����ͨ������ʦ�ܵĿ�����˵��\n");
		command("say ���кεº��ܰ���Ϊʦ��\n");
		command("say ���ֺ�ԭ�ι�����Ϊͽ��\n");
		command("say ����ɽ��Ҫ�ҳϵ���ͽ���㻹���������ҿ��ɣ�\n");
		return;
	}
	if (ob->query("family/family_name")!="��ɽ��")
	{
		command("say һ�����ǹ������֮ͽ��Ϊ�ε��ˣ�\n");
		return;
	}
	if(ob->query("party/gongji") < 5000 ){
		command("say ������ɹ�������5000���������ң�");
		return;
	}
	if(ob->query_skill("hanbing-zhenqi",1) < 300 ){
		command("say ��ĺ�������̫���ˣ�����300�������ң�");
		return;
	}
	if(ob->query_skill("songyang-shou",1) < 300 ){
		command("say ���������̫���ˣ�����300�������ң�");
		return;
	}
	if(ob->query("family/generation") <4){
		command("say ���Ѿ�����ʦ��Ϊʦ�ˣ��ҿɲ������㣡");
		return;
	}
	if(ob->query("shen") > -1000000 ){
		command("say ��ɽ�����Ժ������ƣ�<-1m������������ǻһ���Ͳ����ĺ������������");
		return;
	}
	command("say �ðɣ�ʦ����Ҫ�Ҷ�����һЩ������������ɽ���ء�");
	command("recruit " + ob->query("id"));
}

string ask_jueji()
{
	object me;
	int i,j;

	me=this_player();
	if (me->query_skill("hand",1)<200)
	{
		command("say ��Ļ����ַ�����200��������Ҳѧ���ᣡ\n");
		return "˭��ȭͷ��˭��˵���㣡\n";
	}
	if (me->is_busy()) return "���æ����\n";
	
	if (me->query_skill("songyang-shou",1)<220)
	{
		command("say ��Ĵ������ַ�����220��������Ҳѧ���ᣡ\n");
		return "˭��ȭͷ��˭��˵���㣡\n";
	}
	if (time()-me->query("quest/ss/sys/tuota/time")<86400) 
		return "������̫�ڿ��ˣ�����书�����ǲ����ģ�\n";
	
		command("say ���������������־��������Ҷ���������ѧ�Ҿ͸����㣿\n");
		command("say ��С�ӣ���Ȼ����ѧ���������ˣ�\n");
		  j = 20;
		  if(me->query("m-card-vip")) j =  18;
		  if(me->query("y-card-vip")) j =  15;
		  if(me->query("buyvip"))     j =  10;
		  i=random(j);

		  if (i<4 
			 && me->query("kar")<31
			 && random(me->query("kar"))>25)
		  {       
			  tell_object(me,HIC"\n�㰴�ն����ָ�㽫��������ע���ֱ��У��ַ���ʱ������࣡\n"NOR);
			  message_vision(HIR"\n$N�����ʹ����������ֵļ���һ���ӻ�Ȼ��ͨ����\n"NOR,me); 
			  tell_object(me,HIG"��ϲ�����������־����ɹ���\n"NOR);
			  me->set("quest/tls/sys/tuota/pass",1);
			  log_file("quest/sstuota", sprintf("%s(%s) ʧ��%d�γɹ��⿪�����֡���Դ��%d�����飺%d��\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/tls/sys/tuota/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			  me->start_busy(1);
			}
			else
			{
			 tell_object(me,HIG"\n���˼��ã�����Ҫ�졣\n"NOR);
			 message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿���,�����Լ���ʵ�����ˡ�\n"NOR,me); 
			 tell_object(me,HBBLU"\n�ܿ�ϧ���㱾�γ��������־�������ʧ�ܣ�\n"NOR);
			 tell_object(me,HBBLU"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
			 tell_object(me,HBBLU"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
			 log_file("quest/sstuota", sprintf("%s(%s) ���������־���ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/tls/sys/tuota/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			 me->add("quest/tls/sys/tuota/fail",1);
			 me->set("quest/tls/sys/tuota/exp", me->query("combat_exp") );
			 me->start_busy(1);
			 me->set("quest/tls/sys/tuota/time",time());
			}
		me->add_busy(2);
		return "�������Ǵ������־�����\n";
	 
		
}

