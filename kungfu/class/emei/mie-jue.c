// /kungfu/class/emei/mie-jue.c
// ��������
// Lklv 2001.10.18 update

#include <ansi.h>
inherit F_MASTER;
inherit NPC;
#include "miejue.h"
int ask_sword();
int ask_zhou();
int ask_guo();
int ask_jiuyin();
int ask_dragon();
int ask_mie();
int ask_jue();
int ask_jiuyang();
void create()
{
	set_name("���ʦ̫", ({"miejue shitai", "miejue", "shitai"}));
	set("long","�����Ƕ����ɵ��������������ʦ̫�ˡ�\n"
"����ò��ü�����������üëбб�´���һ��������ü��ǹ��죬����\n"
"�е��Ϸ̨�ϵĵ�����ζ����\n"
	);
	set("gender", "Ů��");
	set("attitude", "friendly");
	set("unique", 1);
	set("class", "bonze");

	set("age", 50);
	set("shen_type", 1);
	set("str", 42);
        set("int", 42);
        set("con", 42);
        set("dex", 42);
        set("max_qi", 13500);
        set("max_jing", 6500);
        set("neili", 14500);
        set("max_neili", 14500);
        set("jiali", 100);
		set("em/jiuyang/pass", 1);
		set("em/mie/pass", 1);
		set("em/jue/pass", 1);
		set("quest/em/hfj/liaoyuan/pass", 1);
	    set("combat_exp", 10000000);
	    set("chat_chance_combat", 40);
	    set("chat_msg_combat", ({
                (: perform_action, "sword.mie" :),
				(: perform_action, "sword.jue" :),
        	    (: perform_action, "sword.liaoyuan" :), 
					(: exert_function, "fengyun" :),   
					(: exert_function, "riyue" :), 
					(: exert_function, "youming" :),  
					(: exert_function, "tiandi" :),  
	    }));
        set_skill("dacheng-fofa", 200);
        set_skill("linji-jianzhen", 500);
        set_skill("linji-zhuang", 480);
        set_skill("jieshou-jiushi", 500);
        set_skill("huifeng-jian", 500);
        set_skill("sixiang-zhang", 480);
        set_skill("yanxing-daofa", 480);
        set_skill("hand", 500);
        set_skill("literate", 180);
        set_skill("strike", 480);
        set_skill("sword", 500);
        set_skill("blade", 480);
        set_skill("parry", 480);
        set_skill("dodge", 480);
        set_skill("force", 500);
        set_skill("anying-fuxiang",480);
        set("inquiry",([
		"���콣" : (: ask_sword :),
		"�����澭" : (: ask_jiuyin :),
		"������" : (: ask_zhou :),
		"����" : (: ask_guo :),
		"����" : (: ask_guo :),
		"��������" : (: ask_dragon :),
		"��������" : (: ask_dragon :),
		"�𽣾���" : (: ask_mie :),
		"��������" : (: ask_jue :),
		"���Ҿ���" : (: ask_jiuyang :),
        ]) );

        map_skill("force", "linji-zhuang");
        map_skill("sword", "huifeng-jian");
        map_skill("blade", "yanxing-daofa");
        map_skill("parry", "huifeng-jian");
        map_skill("dodge", "anying-fuxiang");
        map_skill("strike", "sixiang-zhang");
        map_skill("hand", "jieshou-jiushi");
        prepare_skill("parry", "huifeng-jian");
        prepare_skill("hand", "jieshou-jiushi");

        create_family("������", 3, "����");

        setup();
        carry_object(BINGQI_D("changjian"))->wield();
        carry_object("/d/emei/obj/shoes")->wear();
        carry_object("/d/emei/obj/cloth")->wear();
}

void init()
{
        object me, ob;
        ::init();
        ob = this_player();
        me = this_object();
        if (interactive(ob = this_player()) && !wizardp(ob) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
        }
}

void greeting(object me)
{
        int shen;
        if(!me) return;
        shen = me->query("shen");

        if ( file_name(environment(this_object())) != this_object()->query("startroom")) return;

        if(shen <= -200000 && me->query("family/family_name") == "������"){
        	command("chat* kick2 "+me->query("id"));
        	command("say ���������������а�����ٺ�аħ��������ҿ�����������ɣ�");
	}
	if(shen <0 && shen > -200000 && me->query("family/family_name") == "������"){
		command("look "+me->query("id"));
		command("say �ҿ����������������а��������ǲ�������������ʲô���£�");
	}
	else command("buddhi miejue shitai");
}

int ask_mie() 
{
	object me = this_player();
	int i;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N��$n����й��𽣾������������\n"NOR, me, this_object());
	
	command("look "+me->query("id"));	
	//��ͨ�������
	if(me->query("family/family_name")!="������")
	{
		command("heng "+me->query_id());
		command("say �����������ʲô��ϵ���Ͻ����ҹ���");
		return 1;
	}
	if(me->query("em/mie/pass"))
	{
		command("heng "+me->query_id());
		command("say ���Ѿ��⿪�����⣬����ǲ������ô��");
		return 1;
	}
	if(me->query("em/mie/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say �Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		command("puke "+me->query("id"));
		return 1;
	}
	//�书ѧϰ֮����Ҫ���һ�죬������Ҫ���50K
	if( time()-me->query("em/mie/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say �����Ƚ̵�����ɣ�����ɡ�");
		return 1;
	}
	if(me->query("combat_exp")<4500000)
	{
		command("look "+me->query("id"));
		command("say ���㵱ǰ�ľ�����»����������򣬻���ץ��ȥ����ȥ�ɡ�");
		return 1;
	}
    
	me->set("em/mie/time",time());
	me->set("em/mie/combat_exp",me->query("combat_exp")); 
	
	if (me->query("class")=="bonze")
	   i=random(14);
	else i= random(7);
	command("sigh "+me->query("id"));
	command("say �������Ҷ��һط�������ľ�������Ȼ����������Ҿ�˵����������������û����������ˡ�");
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));
    command("say ͽ���������о�������Ϊʦ������Ѫ���ã���ѧϰ��һ��Ҫ�ô˾��������̽�ͽ����ȫɱ�ˡ�");
	command("say ���㷽�ŵ�ͷ��̬�Ⱥ��棬����������������ԣ�����������Ҳ�Ĳ����㡣");
	if(i>5 && random(me->query("kar"))>=20)
	{
		tell_object(me,HIG"\n�㰴�����ʦ̫��ָ�㣬���𽣵����������ƺ���Щ�ĵá�\n"NOR);
		tell_object(me,HIC"\n������ʦ̫����ʽ�ӿ�ʼ������һ·�����������������硣\n"NOR);
       
		
		//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("buddha "+me->query("id"));
		command("haha "+me->query("id"));
		//me->set(QUESTDIR4+"sword",1);
		me->set("em/mie/pass",1);
		log_file("quest/miejian", sprintf("%8s(%8s) ʧ��%d�κ󣬳�������ط�������𽣵ľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("em/mie/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("em/mie/fail",1);
		me->set("em/mie/time",time());
		command("buddha");
		tell_object(me,HIY"�������𽣾�����ָ�㣬��Ȼ�������𽣵���ʽ�����Ƕ��𽣾�������������ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/miejian", sprintf("%8s(%8s) �𽣾�������ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("em/mie/fail"),i,me->query("combat_exp")) );
	}
	return 1;
}
int ask_jue() 
{
	object me = this_player();
	int i;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N��$n����йؾ����������������\n"NOR, me, this_object());
	
	command("look "+me->query("id"));	
	//��ͨ�������
	if(me->query("family/family_name")!="������")
	{
		command("heng "+me->query_id());
		command("say �����������ʲô��ϵ���Ͻ����ҹ���");
		return 1;
	}
	if(me->query("em/jue/pass"))
	{
		command("heng "+me->query_id());
		command("say ���Ѿ��⿪�����⣬����ǲ������ô��");
		return 1;
	}
	if(me->query("em/jue/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say �Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		command("puke "+me->query("id"));
		return 1;
	}
	//�书ѧϰ֮����Ҫ���һ�죬������Ҫ���50K
	if( time()-me->query("em/jue/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say �����Ƚ̵�����ɣ�����ɡ�");
		return 1;
	}

	me->set("em/jue/time",time());
	me->set("em/jue/combat_exp",me->query("combat_exp")); 
	if (me->query("class")=="bonze")
	   i=random(14);
	else i= random(7);
	command("sigh "+me->query("id"));
	command("say ���������Ҷ��һط�������ľ�������Ȼ����������Ҿ�˵����������������û����������ˡ�");
    command("say ͽ���������о�������Ϊʦ������Ѫ���ã���ѧϰ��һ��Ҫ�ô˾��������̽�ͽ����ȫɱ�ˡ�");
	command("say ���㷽�ŵ�ͷ��̬�Ⱥ��棬����������������ԣ�����������Ҳ�Ĳ����㡣");
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));
	if(i>5 && random(me->query("kar"))>=20)
	{
		tell_object(me,HIG"\n�㰴�����ʦ̫��ָ�㣬�Ծ��������������ƺ���Щ�ĵá�\n"NOR);
		tell_object(me,HIC"\n������ʦ̫����ʽ�ӿ�ʼ������һ·�����������������硣\n"NOR);
       
		
		//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("buddha "+me->query("id"));
		command("haha "+me->query("id"));
		//me->set(QUESTDIR4+"sword",1);
		me->set("em/jue/pass",1);
		log_file("quest/juejian", sprintf("%8s(%8s) ʧ��%d�κ󣬳�������ط�����������ľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("em/jue/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("em/jue/fail",1);
		me->set("em/jue/time",time());
		command("buddha");
		tell_object(me,HIY"�������𽣾�����ָ�㣬��Ȼ�����˾�������ʽ�����ǶԾ�����������������ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/juejian", sprintf("%8s(%8s) ������������ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("em/jue/fail"),i,me->query("combat_exp")) );
	}
	return 1;
}
int ask_jiuyang() 
{
	object me = this_player();
	int i;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N��$n����йض�ü�������������\n"NOR, me, this_object());
	
	command("look "+me->query("id"));	
	//��ͨ�������
	if(me->query("family/family_name")!="������")
	{
		command("heng "+me->query_id());
		command("say �����������ʲô��ϵ���Ͻ����ҹ���");
		return 1;
	}
	if(me->query("emjy/pass"))
	{
		command("heng "+me->query_id());
		me->set("title",HIC"����"+HIR"������"+HIG"����"NOR);
		me->set("mytitle/quest/emjiuyangtitle",HIC"����"+HIR"������"+HIG"����"NOR);

		command("say ���Ѿ��⿪�����⣬����ǲ������ô��");
		return 1;
	}
	
	if (me->is_busy())
	{
		command("say ����æµ�У�\n");
		return 1;
	}
	if(me->query("em/jiuyang/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say �Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		command("puke "+me->query("id"));
		return 1;
	}
	//�书ѧϰ֮����Ҫ���һ�죬������Ҫ���50K
	if( time()-me->query("em/jiuyang/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say �����Ƚ̵�����ɣ�����ɡ�");
		return 1;
	}
	if(me->query_skill("linji-zhuang",1)<500)
	{
		command("pat "+me->query("id"));
		command("say ����ټ�ׯ����500������δ�ڻ��ͨ��˵����Ҳ����������ץ��ȥ����ȥ�ɡ�");
		return 1;
	}
	if(me->query("con")<40)
	{
		command("pat "+me->query("id"));
		command("say ��ü������ȫƾ���ǣ����������ǲ���40��������ץ��ȥ����ȥ�ɡ�");
		return 1;
	}
    
	me->set("em/jiuyang/time",time());
	me->set("em/jiuyang/combat_exp",me->query("combat_exp")); 
	
	command("sigh "+me->query("id"));
	command("say ���Ҿ��������Ҷ�������ķ�����Ȼ����������Ҿ�˵����������������û����������ˡ�");
	command("say ͽ���������о�������Ϊʦ������Ѫ���ã���ѧϰ��һ��Ҫ�ô˾��������̽�ͽ����ȫɱ�ˡ�");
	command("say ���㷽�ŵ�ͷ��̬�Ⱥ��棬����������������ԣ�����������Ҳ�Ĳ����㡣");
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));
	
	message_vision(HIC"���ʦ̫��̾һ���󣬻���˵���������Ҿ����������Ƕ����ɶ����ڹ��ķ���\n"+
		"�����ɹ����ھ�ԶԲ��ǰ���̡������澭��ʱ��Ĭ���µĲ��־�������������\n"+
		HIY+"�����ɿ������ɵ��书����Ҫ��Դ��������һ���ֵġ������澭���������־�����\n"+
		"�䵱���������������޼����ɵľ����񹦱���ͬԴ����Զ���С������澭��ʱ������\n"+
		"����ɫ��ʦ���ž�����������Ĭ����һ���֡������澭���ľ��ģ������������Լ���ѧ\n"+
		"���ײ�ͬ����ѧ������ƫ�ģ���������������ѧһ����ѧ��������������Դ��Ķ��Ҿ�����\n"+
		"���ǵ��䡰����֮�棬��ƾ�˴��������ɡ�����������\n\n\n\n"+
		HIW"���ʦ̫����������������渵������㲻������������գ���Ȼ������ʱ�������.\m"NOR,me);
	
	tell_object(me,HIG"\n�㰴�����ʦ̫��ָ�㣬���ڶԶ��Ҿ�����������������˼����\n"NOR);
	me->set_temp("em/jiuyang/ask",1);
	me->start_busy(999);  
	remove_call_out("thinking");
	call_out("thinking",2,me);	
	return 1;
}

int thinking(object me)
{
  int i,j,total;
  if(!me) return 0;
	
 if(me->query_temp("em/jiuyang/ask")<(3+random(3)))
    { 
	  me->add_temp("em/jiuyang/ask",1);
      if(random(2)) tell_object(me,HIG"\n����������Ÿղ����ʦ̫��һ��һʽ...\n"NOR);
             else tell_object(me,HIY"\nͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
   else
   {  
	  me->delete_temp("em/jiuyang/ask");
      total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 25;
      if(me->query("m-card-vip")) j =  20;
      if(me->query("y-card-vip")) j =  17;
      if(me->query("buyvip"))     j =  15;
	  if (me->query("class")=="bonze")
	     i=random(j-2);
	  else i= random(j);
		
 
    if(i<3
		&& random(me->query("con"))>40
		&& random(me->query("kar"))>26)
	 {
		tell_object(me,HIG"\n�㰴�����ʦ̫��ָ�㣬�Զ��Ҿ��������������ƺ���Щ�ĵá�\n"NOR);
        tell_object(me, HIW"�㰴�����ʦ̫���ԣ���Ϣ���ԡ���ǿѨ������������ᡢ���ء����š�����\n+"+
"��Ѩ��һ·���ż�׵�������ߵĶ��Ǳ��϶��θ���ҪѨ��Ȼ���Ǽ��С����ࡢ������������\n"+
"��̨��������������յ�����׵�����š��縮���Ի���ǿ�䡢�󶥡��������ŵġ��ٻ�Ѩ����\n"NOR);
		tell_object(me,HIY"\n������ǧ����࣬���ڵó���Ը�������Ҿ����ڻ��ͨ��\n"NOR);
       	//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("emjy/pass",1);
		me->set("title",HIC"����"+HIR"������"+HIG"����"NOR);
		me->set("mytitle/quest/emjiuyangtitle",HIC"����"+HIR"������"+HIG"����"NOR);
		me->start_busy(1);
		log_file("quest/emjiuyang", sprintf("%8s(%8s) ʧ��%d�κ󣬳��������ü�����ľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("em/jiuyang/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("em/jiuyang/fail",1);
		me->set("em/jiuyang/time",time());
		command("buddha ");
		tell_object(me,HIY"���������ʦ̫��ָ�㣬��Ȼ�����˶�ü�����İ��أ����ǶԶ�ü����������������ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		log_file("quest/emjiuyang", sprintf("%8s(%8s) ��ü��������ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("em/jiuyang/fail"),i,me->query("combat_exp")) );
	  }
    	return 1;
  }

}
