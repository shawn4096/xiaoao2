// zhenshanzi.c (Ц��)
// By sohu
inherit NPC;
//inherit F_MASTER;
#include <ansi.h>
string ask_feihua();
string ask_xu();

void create()
{
	set_name("��ص���", ({ "kubai daoren", "kubai", "daoren" }));
	set("title", "�����ɳ���");
        set("nickname", HIC"���س���"NOR);
	set("long",
		"�����������ɳ��ϡ����ｭ�����������޿�ص��ˡ�\n"
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
	set_skill("dodge", 550);
	set_skill("taxue-wuhen", 550);
	set_skill("parry", 500);
	set_skill("sword", 500);
	set_skill("liangyi-jue", 200);
	set_skill("xunlei-jian", 500);
	set_skill("cuff", 500);
	set_skill("zhentian-quan", 500);
	set_skill("kunlun-zhang", 500);
	set_skill("strike", 500);

	map_skill("force", "xuantian-wuji");
	map_skill("strike", "kunlun-zhang");
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
	prepare_skill("strike", "kunlun-zhang");

    create_family("������", 2, "���г���");
	set("class", "taoist");

	set("inquiry", ([
		"���ɻ�����" : (: ask_feihua :),
		"�����������" : (: ask_xu :),
		//"�����Ƶ���" : (: ask_diezhang :),

		//"�ټ����ż���" : (: ask_qinji :),
	//	"��ϰ֮" : (: ask_su :),
		//"׷ɱ" : (: ask_ding :),
	]));


	setup();
	carry_object(BINGQI_D("changjian"))->wield();
	carry_object("/d/kunlun/obj/pao2.c")->wear();
}

string ask_feihua()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="������")
	{
		return "��Ĳ��������ɣ��ѵ�������ô����\n";
	}
	if (me->query_skill("liangyi-jian",1)<450)
	{
		return "������ǽ��ȼ�����450��������Ҳû�ã�\n";
	}
	if (me->query("quest/kl/lyj/feihua/pass"))
	{
		return "������ǽ������ɻ��Ѿ��⿪�ˡ���\n";
	}
	if (time()-me->query("quest/kl/lyj/feihua/time")<86400)
	{
		return "������̫Ƶ���ˣ�����������\n";
	}
	if (!me->query("quest/kl/dichuan"))
	{
		return "�㾹Ȼ�������صմ����ӣ���\n";
	}

	message_vision(HIC"$N����Ŀ���$n������˵���������ɵ����ǽ������Ľ������飬���������ɶ���̫��ͬ��\n"
						"���Ȼ������˳̶ȣ��Ҿʹ������������ɻ��İ��أ��Ҹ�����ʾһ�飬�����Լ��������ˡ�\n"+
				   HIR"\n\n\n$N�������һ������������Ծ�������ɻ�к�£�����$n�����ҡ\n"NOR,this_object(),me);
	
 
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
		tell_object(me,HIY"\n�����˵Ŀ�ص��˳��ϵ�����ָ�㣬�����������Լ��������ǽ��������ĵã�����ӡ�ա�\n"NOR);
		tell_object(me,HIG"\n�㽣�����������糤����ӣ����ϲ�����һ���ֽ��м�Ϊ������ʽ������ʶ�ĳ��С�\n"
			             +"��ʽ���Ʒ��������������ʽ���Ѿ���Ȼ���أ��������������಻����\n"
						 +"�������������������ɻ������÷��š����д�ϲ��\n"NOR);
		me->set("quest/kl/lyj/feihua/pass",1);
		log_file("quest/lyjfeihua", sprintf("%8s(%8s) ʧ��%d�κ�ѧ�����ɻ�,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/feihua/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "��ϲ�������ɻ������ɹ�!\n";
		
	}	
   else
	{
		log_file("quest/lyjfeihua", sprintf("%8s(%8s) �������ɻ�����ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/feihua/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"�����˿�ص��˳��ϵ�ָ�㣬���Ƕ����ǽ������ɻ��İ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/lyj/feihua/fail",1);
		me->set("quest/kl/lyj/feihua/time",time());
		me->start_busy(1+random(3));
		
		return "�ǳ��ź��������ǽ�֮���ɻ�ʧ��"+me->query("quest/kl/lyj/feihua/fail")+"�Ρ�\n";
	}


}

string ask_xu()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="������")
	{
		return "��Ĳ��������ɣ��ѵ�������ô����\n";
	}
	if (me->query_skill("kunlun-zhang",1)<500)
	{
		return "��������Ƶȼ�����500��������Ҳû�ã�\n";
	}
	if (me->query("quest/kl/klz/xu/pass"))
	{
		return "���������Ѿ��⿪�ˡ���\n";
	}
	if (time()-me->query("quest/kl/klz/xu/time")<86400)
	{
		return "������̫Ƶ���ˣ�����������\n";
	}
	if (!me->query("quest/kl/dichuan"))
	{
		return "�㾹Ȼ�������صմ����ӣ���\n";
	}

	message_vision(HIC"$N����Ŀ���$n������˵���������ɵ������ƽ����ı����͹�����񣬺��������ɶ���̫��ͬ��\n"
						"���Ȼ������˳̶ȣ��Ҿʹ�����������İ��أ��Ҹ�����ʾһ�飬�����Լ��������ˡ�\n"+
				   HIR"\n\n\n$N����Ծ��˫���˹�����������$n�����ҡ��\n"NOR,this_object(),me);
	
 
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
		tell_object(me,HIY"\n�����˵Ŀ�ص��˳��ϵ�����ָ�㣬�����������Լ����������Ƶ������ĵã�����ӡ�ա�\n"NOR);
		tell_object(me,HIG"\n�������������������������������÷��š����д�ϲ��\n"NOR);
		me->set("quest/kl/klz/xu/pass",1);
		log_file("quest/klzxu", sprintf("%8s(%8s) ʧ��%d�κ�ѧ������������,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/klz/xu/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "��ϲ�������������������ɹ�!\n";
		
	}	
   else
	{
		log_file("quest/klzxu", sprintf("%8s(%8s) ������������������ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/klz/xu/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"�����˿�ص��˳��ϵ�ָ�㣬���Ƕ������������İ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/klz/xu/fail",1);
		me->set("quest/kl/klz/xu/time",time());
		me->start_busy(1+random(3));
		
		return "�ǳ��ź���������������ʧ��"+me->query("quest/kl/klz/xu/fail")+"�Ρ�\n";
	}


}