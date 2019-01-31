// lu.c ��ɽ�ɵ��������� ½��
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_jueji();

void create()
{
        set_name("½��", ({ "lu bo", "lu", "bo" }));
        set("nickname", HIM"�ɺ���"NOR);
        set("long", "����һ�����������ߣ���ɽ�����������ѽ���,һ��������־��������뻯��\n");
        set("gender", "����");
        set("age", 46);
        set("per", 18);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 24);
        set("int", 23);
        set("con", 26);
        set("dex", 26);
		set("unique", 1);
        set("max_qi", 13000);
        set("max_jing", 5000);
        set("eff_jingli", 5000);
        set("jiali", 200);
        set("combat_exp", 6500000);
        set("shen", -1400000);
		set_skill("songyang-jue", 160);

		set_skill("force", 400);
		set_skill("hanbing-zhenqi", 400);
		set_skill("dodge", 400);
		set_skill("zhongyuefeng", 400);
		set_skill("hand", 450);
		set_skill("songyang-shou", 450);
		set_skill("parry", 400);
		set_skill("sword", 400);
		set_skill("songshan-jian", 400);
		set_skill("literate", 200);
		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("parry", "songshan-jian");
		map_skill("sword", "songshan-jian");
		prepare_skill("hand", "songyang-shou");
		create_family("��ɽ��", 3, "����");
		
		set("chat_chance_combat", 70);
		set("chat_msg_combat", ({
					(: perform_action, "hand.xianhe" :),
					(: exert_function, "hanbing" :),
					(: perform_action, "hand.junji" :),
					(: exert_function, "juhan" :),
			}));
		set("inquiry", ([
			"��ɽ��" : "������ɽ������������֮�ף�\n",
			"��������" : "������������������֮�������޴󣬿������֡��䵱���⡣\n",
			"������" : "���������ǵ������ˣ�������ɲ⡣\n",
			//"�ɺ��־���" :(: ask_jueji :),
		]) );
			setup();
			carry_object(ARMOR_D("changpao1"))->wear();
			//carry_object(BINGQI_D("changjian"))->wield();
			add_money("gold", 1);
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
	
	if (me->query_skill("songyang-shou",1)<200)
	{
		command("say ��Ĵ������ַ�����200��������Ҳѧ���ᣡ\n");
		return "˭��ȭͷ��˭��˵���㣡\n";
	}
	if (time()-me->query("quest/ss/sys/xianhe/time")<86400) 
		return "������̫�ڿ��ˣ�����书�����ǲ����ģ�\n";
	
		command("say �����������ɺ��־��������Ҷ���������ѧ�Ҿ͸����㣿\n");
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
			  tell_object(me,HIC"\n�㰴��½�ص�ָ�㽫��������ע���ֱ��У��ַ���ʱ������࣡\n"NOR);
			  message_vision(HIR"\n$N�����ʹ������ɺ��ֵļ���һ���ӻ�Ȼ��ͨ����\n"NOR,me); 
			  tell_object(me,HIG"��ϲ�������ɺ��־����ɹ���\n"NOR);
			  me->set("quest/tls/sys/xianhe/pass",1);
			  log_file("quest/ssxianhe", sprintf("%s(%s) ʧ��%d�γɹ��⿪�ɺ��֡���Դ��%d�����飺%d��\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/tls/sys/xianhe/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			  me->start_busy(1);
			}
			else
			{
			 tell_object(me,HIG"\n���˼��ã�����Ҫ�졣\n"NOR);
			 message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿���,�����Լ���ʵ�����ˡ�\n"NOR,me); 
			 tell_object(me,HBBLU"\n�ܿ�ϧ���㱾�γ����ɺ��־�������ʧ�ܣ�\n"NOR);
			 tell_object(me,HBBLU"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
			 tell_object(me,HBBLU"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
			 log_file("quest/ssxianhe", sprintf("%s(%s) �����ɺ��־���ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/tls/sys/xianhe/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			 me->add("quest/tls/sys/xianhe/fail",1);
			 me->set("quest/tls/sys/xianhe/exp", me->query("combat_exp") );
			 me->start_busy(1);
			 me->set("quest/tls/sys/xianhe/time",time());
			}
		me->add_busy(2);
		return "�ɺ�չ���Ǵ������־�����\n";
	 
		
}
