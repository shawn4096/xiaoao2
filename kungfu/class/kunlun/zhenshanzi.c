// zhenshanzi.c (Ц��)
// By sohu
inherit NPC;
//inherit F_MASTER;
#include <ansi.h>
string ask_duanyun();
string ask_zhenshen();

void create()
{
	set_name("��ɽ��", ({ "zhen shanzi", "zhen" }));
	set("title", "�����ɳ���");
        set("nickname", HIC"Ǭ��һ��"NOR);
	set("long",
		"�����������ɳ��ϡ����ｭ����Ǭ��һ����ɽ�ӡ�\n"
		"��Ȼ����Ѵ󣬵���Ȼ���ó�������ʱӢ��������\n");
	set("gender", "����");
	set("age", 40);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);

	set("max_qi", 23500);
	set("max_jing", 7000);
	set("neili", 29000);
	set("max_neili", 29000);
	set("eff_jingli", 7000);
	set("jiali", 200);
	set("combat_exp", 12500000);
	set("score", 4000);
	set_skill("art", 200);
    set_skill("literate", 250);
	set_skill("force", 500);
	set_skill("xuantian-wuji", 500);
	set_skill("dodge", 500);
	set_skill("taxue-wuhen", 500);
	set_skill("parry", 500);
	set_skill("sword", 500);
	set_skill("liangyi-jue", 200);
	set_skill("xunlei-jian", 500);
	set_skill("cuff", 500);
	set_skill("zhentian-quan", 500);
	set_skill("leg", 500);
	set_skill("chuanyun-tui", 500);

	map_skill("force", "xuantian-wuji");
	map_skill("leg", "chuanyun-tui");
	map_skill("dodge", "taxue-wuhen");
	map_skill("cuff", "zhentian-quan");
	map_skill("parry", "xunlei-jian");
	map_skill("sword", "xunlei-jian");
	set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
  		(: perform_action, "sword.podi" :),
  		(: perform_action, "sword.benlei" :),
		(: perform_action, "sword.sanqiu" :),
		(: exert_function, "wuji" :),			
  		(: perform_action, "dodge.taxue" :),
	}));
	prepare_skill("cuff", "zhentian-quan");
	prepare_skill("leg", "chuanyun-tui");

    create_family("������", 2, "���г���");
	set("class", "taoist");

	set("inquiry", ([
		"�ͱڶ���" : (: ask_duanyun :),
	//	"��ɽȭ����" : (: ask_zhenshan :),
		
	]));


	setup();
	carry_object(BINGQI_D("changjian"))->wield();
	carry_object("/d/kunlun/obj/pao2.c")->wear();
}

string ask_duanyun()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="������")
	{
		return "��Ĳ��������ɣ��ѵ�������ô����\n";
	}
	if (me->query_skill("liangyi-jian",1)<350)
	{
		return "������ǽ��ȼ�����350��������Ҳû�ã�\n";
	}
	if (me->query("quest/kl/lyj/duanyun/pass"))
	{
		return "������ǽ����ͱڶ����Ѿ��⿪�ˡ���\n";
	}
	if (time()-me->query("quest/kl/lyj/duanyun/time")<86400)
	{
		return "������̫Ƶ���ˣ�����������\n";
	}
	if (!me->query("quest/kl/dichuan"))
	{
		return "�㾹Ȼ�������صմ����ӣ���\n";
	}

	message_vision(HIC"$N����Ŀ���$n������˵���������ɵ����ǽ������Ľ������飬���������ɶ���̫��ͬ��\n"
						"���Ȼ������˳̶ȣ��Ҿʹ����������ͱڶ��Ƶİ��أ��Ҹ�����ʾһ�飬�����Լ��������ˡ�\n"+
				   HIR"\n\n\n$N�������һ������������Ծ�����ͱڶ���к�£�����$n�����ҡ\n"NOR,this_object(),me);
	
 
    i = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
      i=random(i);
	j=random(me->query("kar"));
	command("say �㿴����ô��\n");
	command("pat "+me->query("id"));
	if( i<5
		&& me->query("kar")<31
		&& j >= 26 ) 
	{
		tell_object(me,HIY"\n�����˵���ɽ�ӳ��ϵ�����ָ�㣬�����������Լ��������ǽ��������ĵã�����ӡ�ա�\n"NOR);
		tell_object(me,HIG"\n�㽣�����������糤����ӣ����ϲ�����һ���ֽ��м�Ϊ������ʽ������ʶ�ĳ��С�\n"
			             +"��ʽ���Ʒ��������������ʽ���Ѿ���Ȼ���أ��������������಻����\n"
						 +"�����������������ͱڶ��Ƶ����÷��š����д�ϲ��\n"NOR);
		me->set("quest/kl/lyj/duanyun/pass",1);
		log_file("quest/lyjduanyun", sprintf("%8s(%8s) ʧ��%d�κ�ѧ���ͱڶ���,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/duanyun/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "��ϲ�����ͱڶ��ƾ����ɹ�!\n";
		
	}	
   else
	{
		log_file("quest/lyjduanyun", sprintf("%8s(%8s) �����ͱڶ��ƾ���ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/duanyun/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"��������ɽ�ӳ��ϵ�ָ�㣬���Ƕ����ǽ����ͱڶ��Ƶİ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/lyj/duanyun/fail",1);
		me->set("quest/kl/lyj/duanyun/time",time());
		me->start_busy(1+random(3));
		
		return "�ǳ��ź��������ǽ�֮�ͱڶ���ʧ��"+me->query("quest/kl/lyj/duanyun/fail")+"�Ρ�\n";
	}


}
/*
string ask_zhenshan()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="������")
	{
		return "��Ĳ��������ɣ��ѵ�������ô����\n";
	}
	if (me->query_skill("zhenshan-quan",1)<200)
	{
		return "�����ɽȭ�ȼ�����200��������Ҳû�ã�\n";
	}
	if (me->query("quest/kl/zsq/zhenshan/pass"))
	{
		return "�����ɽȭ�İ����Ѿ��⿪�ˡ���\n";
	}
	if (time()-me->query("quest/kl/zsq/zhenshan/time")<86400)
	{
		return "������̫Ƶ���ˣ�����������\n";
	}

	message_vision(HIC"$N����Ŀ���$n������˵���������ɵ����ǽ������Ľ������飬���������ɶ���̫��ͬ��\n"
						"���Ȼ������˳̶ȣ��Ҿʹ����������ͱڶ��Ƶİ��أ��Ҹ�����ʾһ�飬�����Լ��������ˡ�\n"+
				   HIR"\n\n\n$N�������һ������������Ծ�����ͱڶ���к�£�����$n�����ҡ\n"NOR,this_object(),me);
	
 
    i = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
      i=random(i);
	j=random(me->query("kar"));
	command("say �㿴����ô��\n");
	command("pat "+me->query("id"));
	if( i<5
		&& me->query("kar")<31
		&& j >= 26 ) 
	{
		tell_object(me,HIY"\n�����˵���ɽ�ӳ��ϵ�����ָ�㣬�����������Լ��������ǽ��������ĵã�����ӡ�ա�\n"NOR);
		tell_object(me,HIG"\n�㽣�����������糤����ӣ����ϲ�����һ���ֽ��м�Ϊ������ʽ������ʶ�ĳ��С�\n"
			             +"��ʽ���Ʒ��������������ʽ���Ѿ���Ȼ���أ��������������಻����\n"
						 +"�����������������ͱڶ��Ƶ����÷��š����д�ϲ��\n"NOR);
		me->set("quest/kl/lyj/duanyun/pass",1);
		log_file("quest/lyjduanyun", sprintf("%8s(%8s) ʧ��%d�κ�ѧ���ͱڶ���,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/duanyun/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "��ϲ�����ͱڶ��ƾ����ɹ�!\n";
		
	}	
   else
	{
		log_file("quest/lyjduanyun", sprintf("%8s(%8s) �����ͱڶ��ƾ���ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/duanyun/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"��������ɽ�ӳ��ϵ�ָ�㣬���Ƕ����ǽ����ͱڶ��Ƶİ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/lyj/duanyun/fail",1);
		me->set("quest/kl/lyj/duanyun/time",time());
		me->start_busy(1+random(3));
		
		return "�ǳ��ź��������ǽ�֮�ͱڶ���ʧ��"+me->query("quest/kl/lyj/duanyun/fail")+"�Ρ�\n";
	}


}*/