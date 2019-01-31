// zhong.c ��ɽ�ɵ��������� ����
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
string ask_jueji();

void create()
{
        set_name("����", ({ "zhong zhen", "zhong", "zhen" }));
        set("nickname", HIC"������"NOR);
        set("long", "����һ�����������ߣ�һ����ɽ�����ڽ����Ϻպ�������\n");
        set("gender", "����");
        set("age", 45);
        set("per", 20);
        set("attitude", "heroism");
	set("class", "songshan");
        set("shen_type", -1);
        set("str", 26);
        set("int", 26);
        set("con", 26);
        set("dex", 27);
        set("unique", 1);

        set("max_qi", 23000);
        set("max_jing", 6000);
        set("eff_jingli", 6000);
        set("jiali", 200);
        set("combat_exp", 6500000);
        set("eff_neili", 5000);
        set("shen", -1500000);
		set_skill("songyang-jue", 150);

		set_skill("literate", 200);
		set_skill("force", 400);
		set_skill("parry", 450);
		set_skill("sword", 450);
		set_skill("dodge", 400);
		set_skill("hand", 400);
		set_skill("zhongyuefeng", 400);
		set_skill("songyang-shou", 400);
		set_skill("hanbing-zhenqi", 400);
		set_skill("songshan-jian", 450);

		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("parry", "songshan-jian");
		map_skill("sword", "songshan-jian");
		prepare_skill("hand", "songyang-shou");

		create_family("��ɽ��", 3, "����");
		
		set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: perform_action, "sword.feiwu" :),
			(: perform_action, "sword.jiuqu" :),
			(: perform_action, "sword.leiting" :),
			//(: perform_action, "sword.longfeng" :),
			(: perform_action, "hand.junji" :),
			(: exert_function, "hanbing" :),
		}));
			setup();
		set("inquiry", ([
			//"��ɽ��" : "������ɽ������������֮�ף�\n",
			//"��������" : "������������������֮�������޴󣬿������֡��䵱���⡣\n",
			//"������" : "���������ǵ������ˣ�������ɲ⡣\n",
		//	"����������": (: ask_jueji() :),
		]) );
			carry_object(ARMOR_D("changpao1"))->wear();
			carry_object(BINGQI_D("changjian"))->wield();
}

#include "app3.h";



string ask_jueji()
{
	object me;
	int i,j;

	me=this_player();
	if (me->query_skill("sword",1)<300)
	{
		command("say ��Ļ�����������200��������Ҳѧ���ᣡ\n");
		return "�����仯���м��£�\n";
	}
	if (me->is_busy()) return "���æ����\n";
	
	if (me->query_skill("songshan-jian",1)<300)
	{
		command("say �����ɽ��������300��������Ҳѧ���ᣡ\n");
		return "�����仯���м��£�\n";
	}
	if (time()-me->query("quest/ss/ssj/jiuqu/time")<86400) 
		return "������̫�ڿ��ˣ�����书�����ǲ����ģ�\n";
	
		command("say ��ɽ�������������������Ҷ���������ѧ�Ҿ͸����㣿\n");
		command("say ��С�ӣ���Ȼ����ѧ���������ˣ�\n");
		  j = 20;
		  if(me->query("m-card-vip")) j =  18;
		  if(me->query("y-card-vip")) j =  15;
		  if(me->query("buyvip"))     j =  10;
		  i=random(j);

		  if (i<4 
			 && me->query("kar")<31
			 && random(me->query("kar"))>26)
		  {       
			  tell_object(me,HIC"\n�㰴�������ָ�㽫��������ע���ֱ��У��ֶ�ʱ������࣡\n"NOR);
			  message_vision(HIR"\n$N�����ʹ������������ļ���һ���ӻ�Ȼ��ͨ����\n"NOR,me); 
			  tell_object(me,HIG"��ϲ�����ܾ����������ɹ���\n"NOR);
			  me->set("quest/ss/ssj/jiuqu/pass",1);
			  log_file("quest/ssjiuqu", sprintf("%s(%s) ʧ��%d�γɹ��⿪����������Դ��%d�����飺%d��\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/ss/ssj/jiuqu/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			  me->start_busy(1);
			}
			else
			{
			 tell_object(me,HIG"\n���˼��ã�����Ҫ�졣\n"NOR);
			 message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿���,�����Լ���ʵ�����ˡ�\n"NOR,me); 
			 tell_object(me,HBBLU"\n�ܿ�ϧ���㱾�γ��Ծ�������������ʧ�ܣ�\n"NOR);
			 tell_object(me,HBBLU"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
			 tell_object(me,HBBLU"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
			 log_file("quest/ssjiuqu", sprintf("%s(%s) ���ܾ���������ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
			 me->name(1),
			 me->query("id"), 
			 me->query("quest/ss/ssj/jiuqu/fail"),
			 me->query("kar"),
			 me->query("combat_exp")) );
			 me->add("quest/ss/ssj/jiuqu/fail",1);
			 me->set("quest/ss/ssj/jiuqu/exp", me->query("combat_exp") );
			 me->start_busy(1);
			 me->set("quest/ss/ssj/jiuqu/time",time());
			}
		me->add_busy(2);
		return "��������������ɽ��������\n";
	 
		
}