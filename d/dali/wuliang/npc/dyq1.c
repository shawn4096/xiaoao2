// cool980310
// ������
// cool980724
// Modify By River 98/12
// Modify by tangfeng@SJ
// ��Ҫ�޸��˱�־�ļ�¼��ʽ���������޸�

inherit NPC;
#include <ansi.h>
string ask_duan1();
string ask_duan2();
#define QUESTDIR1 "quest/�����˲�/�貨΢��ƪ/"
string ask_yiyang();

int do_kill(object me, object ob);

void create()
{
        set_name("������", ({ "duan yanqing", "duan","yanqing"}) );
        set("gender", "����" );
		set("title",HIC"�Ĵ����"NOR);
		set("nickname",HIR"��"HIG"����ӯ"NOR);
        set("age", 52);
        set("str", 30);
        set("con", 30);
        set("dex", 30);
        set("int", 25);
        set("per", 10);
   		set("attitude", "friendly");

		set("max_qi", 30000);
		set("max_jing", 30000);
		set("eff_jingli", 30000);
        set("max_neili", 22000);
        set("neili", 22000);
		set("jiali", 200);
        
        set("long","�����Ǹ����ߣ����봹�أ���Ŀ��ڡ�\n",);
		set("env/һ��ָ","����");
        set("combat_exp", 9400000+random(1000000));
        set("shen", -8000);

        set("chat_chance_combat", 100);
        set("chat_msg_combat",({ 
		(: perform_action, "finger.sandie" :), 
		(: perform_action, "finger.sanmai" :),
		(: perform_action, "finger.yizhisanmai" :),
	    }));

        set_skill("parry", 480);
        set_skill("dodge", 480);
        set_skill("force", 480);
        set_skill("finger", 480);
        set_skill("buddhism", 150);
        set_skill("literate", 300);
        set_skill("staff", 480);
        set_skill("duanjia-jianfa", 480);
        set_skill("qiantian-yiyang", 480);
        set_skill("yiyang-zhi", 480);
        set_skill("tianlong-xiang", 480);

		map_skill("dodge", "tianlong-xiang");
		map_skill("parry", "yiyang-zhi");
		map_skill("finger", "yiyang-zhi");
		map_skill("force", "qiantian-yiyang");
		prepare_skill("finger","yiyang-zhi");

		set("inquiry", ([
		
		"�Խ���ָ����" : (: ask_yiyang :),
	]));

	setup();
	carry_object("/d/dali/npc/obj/pao")->wear();
}

string ask_yiyang()
{
     object me,ob;
	 int i,j;
     me=this_player();
     ob=this_object();
	 
	 if( !me->query_temp("yanqing/killhuang") )
	 {
		return "��ȥ���Ұѻ�üɮ����ɱ�ˣ��Ҿͽ��㣡\n";
	 }
	 
	 if (me->query("family/family_name")!="������") 
	 {
		command("say ����Ȼ���������µ��ӣ��������书Ҳ���������⴫��\n");
		return "�ߣ�";
	 }
	 if (me->query_skill("qiantian-yiyang",1)<200) 
	 {
		command("say ���Ǭ��һ��������200���ò����Խ���ָ��\n");
		return "�ߣ�";
	 }
	 if( !me->query(QUESTDIR1+"over") )
	 {
		return "�Ҳ���ʶ�㣬�����ҵ�������С����˵��";
	 }
	 
	 if (time()-me->query("quest/tls/djjf/yanqing/time")<86400)
	 {
			return "������̫�ڿ��ˣ��������㣡";
	 }
	 if (me->query("quest/tls/djjf/yanqing/pass"))
	 {
			return "���Ѿ��⿪�ˣ��������ң�";
	 }
	 if (me->query("shen")>-200000)
	 {
			return "�㸺�����-200k,һ���Ͳ����ĺ�����֮ͽ��";
	 }
	  j = 18;
      if(me->query("m-card-vip")) j =  16;
      if(me->query("y-card-vip")) j =  13;
      if(me->query("buyvip"))     j =  8;
	  if (me->query("class")=="bonze")
	     i=random(j+5);
	  else i= random(j);
	 
	 if(i<6 && random(me->query("kar"))>=20)
	 {
		tell_object(me,HIG"\n�㰴�ն������ָ�㣬���Խ���ָ��һ��ָ�������������ƺ���Щ�ĵá�\n"NOR);
        tell_object(me, HIW"�㰴�ն��������ԣ���Ϣ���ž��������������Ȼ�䡰������һ�����ڽ��˷���һ�����졣\n"NOR);
		tell_object(me,HIY"\n\n������ǧ����࣬���ڵó���Ը�����μҽ������Խ���ָ�����ڻ��ͨ��\n"NOR);
       	//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/tls/djjf/yanqing/pass",1);
		me->set("title",HIR"��"+RED"����ӯ����"NOR);
		me->start_busy(1);
		me->delete_temp("yanqing");
		//if (objectp(ob))
		//	destruct(ob);
		log_file("quest/djjfyanqing", sprintf("%8s(%8s) ʧ��%d�κ󣬳��������Խ���ָ�ľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/tls/djjf/yanqing/fail"),i,me->query("combat_exp")) );
	    return "��ϲ����ϲ���Ҵ������ֶ��˸��������֣�\n";
	 }
	 else
	 {
		me->add("quest/tls/djjf/yanqing/fail",1);
		me->set("quest/tls/djjf/yanqing/time",time());
		command("buddha ");
		tell_object(me,HIY"\n\n�����˶������ָ�㣬��Ȼ�������Խ���ָ�İ��أ����Ƕ��Խ���ָ����������ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		me->delete_temp("yanqing");
	//	if (objectp(ob))
			//destruct(ob);

		log_file("quest/djjfyanqing", sprintf("%8s(%8s) �Խ���ָ����ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/tls/djjf/yanqing/fail"),i,me->query("combat_exp")) );
		return "����һ��ָ���Ҵ���������Ҵ������ܵ��������°���\n";
	  }
    	
}

int accept_object(object who, object obj)
{
	
	object duan,me;
	duan =present("duan yanqing", who);
	me = this_player();
    

	if (me->query_temp("yanqing/askzhong")
		&& obj->query("name")=="��ü���е��׼�"
		&& obj->query("kill_by")==who
		&& obj->query("id")=="shouji")
	{
		
		write(HIY"��������˵α����������ƺ�����ĺøд�����\n"NOR);
		write(HIC"$N�ѻ�ü���е���ͷ�͸��˶����죡\n"NOR);
		obj->move(this_object());
		destruct(obj);
		command("pat "+who->query("id"));
		me->delete_temp("yanqing/askzhong");
		me->set_temp("yanqing/killhuang",1);
		return 1;
	}

	
}
