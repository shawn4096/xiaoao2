// NPC: /d/huashan/npc/ai.c
// Date: Look 99/03/25
// Lklv modify 2001.10.18

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

int ask_quest();
int ask_weigong();
int ask_zhangwuji();
int ask_liangyi();

void create()
{
        set_name("������",({"ai laozhe","ai"}));
        set("title","��ɽ�ɵ�ʮ��������");
        set("long", "������ڽ��������ӵĻ�ɽ�ɰ����ߡ�");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 32);
        set("int", 32);
        set("con", 32);
        set("dex", 32);

        set("max_qi",13500);
        set("qi", 13500);
        set("max_jing", 5500);
        set("jing",5500);
        set("eff_jingli", 5000);
        set("max_neili", 24000);
        set("neili", 24000);
        set("jiali", 200);
        set("combat_exp", 12000000);
        set("score", 30000);

        set_skill("blade",  450);
		set_skill("dodge",  450);
        set_skill("force",  450);
        set_skill("parry",  450);
        set_skill("cuff", 450);
	    set_skill("sword", 450);
	    set_skill("literate",100);
        set_skill("poyu-quan", 450);
	    set_skill("huashan-qigong", 450);
		set_skill("fanliangyi-dao", 450);
        set_skill("huashan-jianfa",  450);
        set_skill("huashan-shenfa",  450);
        set_skill("zhengqi-jue", 200);

	    map_skill("dodge", "huashan-shenfa");
	    map_skill("sword", "huashan-jianfa");
		map_skill("blade", "fanliangyi-dao");
        map_skill("force","huashan-qigong");
        map_skill("parry","poyu-quan");
        map_skill("cuff", "poyu-quan");

        prepare_skill("cuff","poyu-quan");
	    set("chat_chance_combat",50);
	    set("chat_msg_combat", ({
		(: perform_action, "blade.sanshenfeng" :),
		//(: perform_action, "sword.feijian" :),
		//(: perform_action, "sword.junzi" :),
		//(: perform_action, "sword.kuaijian" :),
		//(: perform_action, "sword.lianhuan" :),
		//(: perform_action, "sword.sanqing" :),
	}));
        create_family("��ɽ��",12,"����");

        set("inquiry", ([
                "����ͨ": (: ask_quest :),
				"��������Χ������": (: ask_weigong :),
				"���޼�": (: ask_zhangwuji :),
				"�����Ǿ�": (: ask_liangyi :),
        ]));
        setup();
	    carry_object(ARMOR_D("cloth"))->wear();
	    carry_object(BINGQI_D("blade"))->wield();
}
/*
void attempt_apprentice(object ob)
{
       // mapping fam;
        if (ob->query("family/family_name")!= "��ɽ��"
         && ob->query("is/huashan")==1 ||!ob->query("quest/huashan") )
		{
                message_vision(CYN "$N���������ɽ�ɵ���ͽ��������ʲô ������\n"NOR, ob );
                command("slap "+ob->query("id"));
                return;
        }
		if ( ob->query("fengset")) {
			command("say �㲻���Ѿ����˷�����Ϊʦ��ô��");
			return;
		}
        if ((int)ob->query("shen") <= 2000000) {
	        command("say �һ�ɽ�����������������ɣ��Ե���Ҫ���ϡ�");
        	command("say �ڵ��з��治��2M��" + RANK_D->query_respect(ob) + "�Ƿ����ò�����");
			return;
        }
        if ((int)ob->query("max_pot") < 450) {
		command("say " + RANK_D->query_respect(ob)+"���ڲ���Ҫ����ָ������ȥ��������ʦ��ѧ��ȥ�ɡ�");
		return;
        }
        if( (int)ob->query_skill("huashan-qigong", 1) < 350 ) {
		command("say ��Ļ�ɽ������δ�����,�����ҿɲ�������Ϊͽ��\n");
		return;
        }

        if( (int)ob->query_skill("force") < 350 ) {
		command("say ����ڹ���δ�����,�����ҿɲ�������Ϊͽ��\n");
		return;
        }
        command("say �ðɣ��Ҿ���������,���ҪΪ���ǻ�ɽ����������");
        command("recruit " + ob->query("id"));
}
*/
int ask_quest()
{
        object me = this_player();
	    if (!me->query_temp("hu/quest1")) {
		command("say ���ǻ�ɽǰ�ε�����....���������ʲô��");
		command("consider " + me->query("id"));
		return 1;
        }
        else {
		command("say ���ǻ�ɽǰ�ε����ţ��Լ�����ʦ��ȴ�޻����̡�");
		command("say ������һս�����Ѿ������̽������޼�ɱ�ˡ�");
		command("sneer");
		me->set_temp("hu/quest1",2);
		return 1;
        }
}

int ask_weigong()
{
        object me = this_player();
	    if (!me->query_temp("liangyi/askhe")) {
		command("say ....���������ʲô��");
		command("consider " + me->query("id"));
		return 1;
        }
        else {
		command("say ���֡��䵱����ɽ����ἡ����ҡ���������������ԼΧ����������");
		command("say ��Ȼ����������ʥ�����ˣ��Ҿ͸���˵���⵱��Ե�ɡ�");
		command("whisper "+me->query("id"));
		command("say ������������һս�����̽������޼���Ǭ����Ų�ƺ;����񹦴���������ɡ�");
		command("say �����������޼��˵�������Ҳ�����Ϊ�Һ���ʦ����ɱ���ߣ�");
		command("sneer");
		me->set_temp("liangyi/askweigong",1);
		return 1;
        }
}
int ask_zhangwuji()
{
        object me = this_player();
	    if (!me->query_temp("liangyi/askweigong")) {
		command("say ....���������ʲô��");
		command("consider " + me->query("id"));
		return 1;
        }
        else {
		command("say ���޼��ڹ�������ս�������ɣ��˵�����һ���֡�");
		command("say ��ʱ�Һ�ʦ���û�ɽ�����ǵ���������ס�����ͽ���ɱ�ˡ�");
		command("haha "+me->query("id"));
		command("say �һ�ɽ�����ǵ����ǻ�ɽ�������⣬��ϧ�����ǰ�ǰɽ�ĳ�С�Ӷ�ȥѧ�������ⲻ֪���ŵĵ���Ҳ��һ����");
		command("say ��Ȼ��������ص������Ǿ��Ǹ��������ˮ��");
		command("hero ");
		me->set_temp("liangyi/askzwj",1);
		return 1;
        }
}
int ask_liangyi()
{
        object me = this_player();
	 
		if( time()-me->query("quest/kl/lyj/liangyi/time")<86400 ){
			command("������̫�ڿ��ˣ�Ҫ��ƽ���ͣ�������Ϣ���ɡ�\n");
			return 1;
		}
		if (me->query_skill("fanliangyi-jue",1)<200 && me->query("quest/kl/lyj/liangyi/jue"))
		{
			message_vision(CYN"$n����������$NС�ĵ���̹��ڷ����Ǿ���ԭ��\n"NOR,this_object(),me);
			me->improve_skill("fanliangyi-jue", 10+random(me->query_int(1)));
			me->receive_damage("jing",random(10),"����͸֧��");
			return 1;
		}
		if( me->query("quest/kl/lyj/liangyi/jue") ) {
			command("say ���Ѿ�������������ǽ������ֺιʿ�����Ц�أ�\n");
			return 1;
		}
		if (!me->query_temp("liangyi/askzwj")) {
			command("say ....���������ʲô��");
			command("consider " + me->query("id"));
			return 1;
        }
        else {
		command("say �����Ǿ����Ǻ����������Ǿ��෴�Ĺ������ء�");
		command("say ��ʱʦ�ܺ����Լ������ɵ�����������һͬ����������Լ�Ǭ����Ų�ơ�");
		command("say �������Ǿ������һ��Ȼ��˿�Ϸ죬�������");
		command("say ��Ȼ����������ʥ�ĵ��ӣ���ô�ҾͰ����׹����������㣬�ܷ����׾Ϳ�����ˡ�");
		command("say ..........��");
		command("whisper "+me->query("id"));
		
			me->set_temp("liangyi/askfly",1);
			me->start_busy(999);
			call_out("thinking",1,me);
			return 1;
        }
}

int thinking(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("liangyi/askfly")<(10+random(3)))
    { 
	  me->add_temp("liangyi/askfly",1);
      if(random(2)) tell_object(me,HIG"\n����������ŸղŰ����ϸ��㽲�ķ����ǰ���...\n"NOR);
             else tell_object(me,HIY"\nͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
   else
   {  
	  me->delete_temp("liangyi/askfly");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
	  i= random(j);
 
 
    if(i<3 && random(me->query("kar"))>=26)
	 {
		tell_object(me,HIG"\n�㰴�հ����ϵ�ָ�㣬�Է����Ǿ������������ƺ���Щ�ĵá�\n"NOR);
        tell_object(me, HIW"�㰴�հ��������ԣ����յ��������Ľ�ӡ��ʼ��ϰ��һȦһȦ�Ĳ�������\n+"+
							"��ʱ��Ϊ��ɬ���ⷴ���Ǿ�����ǰ�������Ǿ���Ȼ��ͬ��������ȫ�෴��\n"+
							"�������ţ���Ȼ�������������ײ�����ԭ�����в��ɵش󳩣���Хһ����\n"NOR);
		
		tell_object(me,HIY"\n������ǧ���ڿ࣬���ڵó���Ը���������Ǿ��ڻ��ͨ��\n"NOR);
       	me->improve_skill("fanliangyi-jue", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/kl/lyj/liangyi/jue",1);
		me->start_busy(1);
		log_file("quest/klfliangyi", sprintf("%8s(%8s) ʧ��%d�κ󣬳����������Ǿ��ľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/kl/lyj/liangyi/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/kl/lyj/liangyi/fail",1);
		me->set("quest/kl/lyj/liangyi/time",time());
		command("poor ");
		tell_object(me,HIY"�����˰����ϵ�ָ�㣬��Ȼ�����˷����Ǿ��İ��أ����ǶԷ����Ǿ�����������ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		me->delete_temp("liangyi");
		log_file("quest/klfliangyi", sprintf("%8s(%8s) �����Ǿ�����ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/kl/lyj/liangyi/fail"),i,me->query("combat_exp")) );
	  }
    	return 1;
  }

}
