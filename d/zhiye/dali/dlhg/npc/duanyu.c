// duanyu.c ����
// COOL@SJ,990827
// Modified by tangfeng 2004
// ����Ķ����漰������������һ������������һ����ʯ���һ���ڴ����°�����
// By Spiderii@ty ����ʱ������
//inherit F_MASTER;
#include <ansi.h>
inherit NPC;

int ask_liumai();

void create()
{
        set_name("����", ({"duan yu", "duan", "duayu"}));
        set("gender", "����");
        set("age", 20);
		set("title",HIC"���������������"NOR);

        set("long", "����һ���������ӣ���һ����ɫ���ۣ��������񣬳ݰ״��죬���ʸ��š�\n"
                    "����Ϊ�峺��һ�����Ǿþ�Ѭ�ն����ɵ������������ӣ����������ң�ȴ���ɷ�����ˡ�\n");
        set("attitude", "peaceful");
        set("str", 40);
        set("per", 30);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        //set("no_quest", 1);

        

        set("jing", 10000);
        set("max_jing", 10000);
        set("jingli", 10000);
        set("eff_jingli", 10000);
        set("qi", 80000);
        set("max_qi", 80000);
        set("neili", 80000);
        set("max_neili", 80000);
        set("jiali",250);
		//Ҫ�趨��ڤ���貨����
        
        set("combat_exp", 15000000);
        set_skill("buddhism", 250);            
        //set_skill("daode-jing", 250);                   
        set_skill("literate", 400);                
        set_skill("force", 550);                
        set_skill("beiming-shengong", 550);     
        set_skill("dodge", 550);                
        set_skill("lingbo-weibu", 550);         
        set_skill("parry", 500);
        set_skill("finger", 550);
        set_skill("yiyang-zhi", 550);
        set_skill("liumai-shenjian", 180);
        map_skill("parry", "yiyang-zhi");
        map_skill("finger", "yiyang-zhi");
        map_skill("force", "beiming-shengong");
        map_skill("dodge", "lingbo-weibu");
		prepare_skill("finger","yiyang-zhi");
		set("quest/tls/yyz/liumai/pass",1);
		set("quest/tls/yyz/zhijian/pass",1);

		set("env/liumai","shenjian");

		set("inquiry", ([
			"������" : (: ask_liumai :),
	

        ]));
        set("chat_chance_combat", 100);
        set("chat_msg_combat",({ 
                (: exert_function, "beiming" :),
				(: perform_action, "dodge.luoshen" :),

                (: perform_action, "finger.yizhisanmai" :),
                (: perform_action, "finger.ciqu" :),
				//(: perform_action, "finger.liumai" :),
				(: perform_action, "finger.ciqu" :),
        }));

        setup();        
}



int ask_liumai()
{
	object me=this_player();
    int time;

	if(me->query("family/family_name")!="������") 
	{
		command("say �����µ��������������µ�һ�ȵ��书��\n");
		command("say ����Ҵ��������µ��ӣ����˴�����������ǲ����Ĵ治�죿\n");
		return 1;
	}
	
	if (me->query("yyz/degree")>1)
	{
		command("say һ��ָ��˵������Ʒ����Ϳ���ʩչ�����񽣣����Ͼ�����ǿ������ﵽһƷ�����������ҡ�\n");
		return 1;
	}
	if (!me->query("quest/�����˲�/���ɾ�Ԯƪ/over"))
	{
		command("say �����˲������㻹û��������ɾ�Ԯƪ���Ҹ���˵����Ҳ������\n");
		return 1;
	}
	if (me->query("yideng/ronghe")!="pass")
	{
		command("say ����һ��ָ�ľ������ض���������ף��Ҹ���˵���������ܶ�ô��\n");
		return 1;
	}
	if (me->query("quest/tls/yyz/liumai/pass"))
	{
		command("say ���Ѿ�����������֮ͨ�����������ʲô��\n");
		me->set("title",HIG"�����񽣴���"NOR);
		me->set("mytitle/quest/6mtitle",HIG"�����񽣴���"NOR);
		return 1;
	}
	if (me->query("int")<40)
	{
		command("say ��������Ҫ���ߵ����ԣ����������Բ���40��������������!\n");
		return 1;
	}
	if (me->query("yideng/ronghe")!="pass")
	{
		command("say ����һ��ָ�ľ������ض���������ף��Ҹ���˵���������ܶ�ô��\n");
		return 1;
	}
	if (!me->query("quest/tls/liumai/winzhi"))
	{
		command("say ���Ƽʻ���һ��˵��������飬�������ѣ������Ķ���\n");
		return 1;
	}
	time=time() - me->query("quest/tls/yyz/liumai/time");
	if (me->query("quest/tls/yyz/liumai/time") && time<86400)
	{
		command("say ���������Ƶ����������ô��\n");
		return 1;
	}
	command("sigh ");
	command("say �Ҵ���ԭ��������������,��Ȼ��Ӵ���������λ������δ�������书��ϰ��\n");
	command("say ��ƾ���Ҵ���Ҵ���ѧһ��ָ���������¡�\n");
	command("say ���˽�֪�Ҵ���һ��ָ�����ⲻ֪�Ҵ������������书���ǽ����������񽣡����漼��\n");
	command("say �������񽣲����������ڣ����Ҵ�����������ѧ��\n");
	command("say ����Ϊ������Ʒ�Ժ󷽿�ʩչ������һ��������ѧ��\n");
	command("say ��Ȼ������ѧ����ɿ����ˣ�\n");
	message_vision(HIY"$N��Ȼ�������˲��ʩչ�������񽣵ľ�����$nֻ�����佣���ݺᣬ�����ҡ��\n"NOR,this_object(),me);
	command("say �����ˣ�");

	   message_vision(HIC"\n$N����Сָһ�죬ʹ�������󽣷�����һ�ɾ�����$P����Ѩ�м��������ָ����ǰ$n��\n"+
							"$nֻ����һ�����ν��������$l�����������仯��΢������ޱȣ������Ǻ�����ȥ���仯��΢\n"NOR,this_object(),me);
                   message_vision(MAG"\n$N����ָһ�ӣ�׾�͹��ӵĹس彣��ֱ��������˶������ش���$n��$l,���ǡ��س彣����\n"+
									"$n�о��������ν���׾�͹��ӣ������б�ίʵ���Լܵ�,���ν�����Ȼʹ���޴Ӷ��\n"NOR,this_object(),me);
                   message_vision(HIG"\n$NĴָһ����ʳָ���������ˡ�������������һ�ƽ�����$n$l�̳���������Ѹ�٣������ޱ�\n"+
									"�����εĽ���������������ĥ���û���ֱ��$n������˲���ѱƵ���$��ǰ\n"NOR,this_object(),me);

				   message_vision(HIR"\n$N����һ����˫��ǰ�죬һʽ���г彣����,˫�ֺ�ʹ�����������ޱȵĽ����ƿմ���$n��$l\n"+
										"��Ȼ��$n�е������Ѩ����һ�ɴ󿪴�ϣ�������ΰ�����ν�������Χ\n"NOR,this_object(),me);
                   message_vision(CYN"\n$N��������ǰ�������Сָ��һ�С��ٳ彣����,�����ص���$n�������Ѩ����ָ��������ȴ��������\n"+
										"$n���ǽ������ý�ǰ�����Ǿ����������ƿ�֮������,���ν����ơ�׾������������������������������\n"NOR,this_object(),me);
                   message_vision(HIB"\n$N��Ĵָ��ǰ˫���������̽�����������һ����īɽˮ���ƣ��ݺ���б���������ʣ�ȴ�ǽ�·�۾�\n"+
									 "$n�������ν�������ʯ���쾪���������֮�ƣ��󿪴��أ����ɺ�ΰ�Ƶ�$n�ݸ߷��ͣ��������ܣ�\n"NOR,this_object(),me);
	me->start_busy(99);
	remove_call_out("thinking");
	call_out("thinking",1,me);
	return 1;
}

int thinking(object me)
{
	int i,j,total;
	if(!me) return 0;
	
	if(me->query_temp("liumai_ask")<(13+random(3)))
    { 
	  me->add_temp("liumai_ask",1);
      if(random(2)) tell_object(me,HIG"\n����������ŸղŶ�����һ��һʽ...\n"NOR);
             else tell_object(me,HIY"\nͻȻ�䣬���ƺ��о�ץ����ʲô�����񽣵�һ˿����...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	 // remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
   else
   {  
	  me->delete_temp("liumai_ask");
      total = me->query("int");
      j = 25;
      if(me->query("m-card-vip")) j =  23;
      if(me->query("y-card-vip")) j =  20;
      if(me->query("buyvip"))     j =  17;
	  i= random(j);
 
 
	  if(i<2 
		&& random(total)>40
		&& random(me->query("kar"))>28)
	  {
		tell_object(me,HIG"\n�㰴�ն�����ָ�㣬�������񽣵����������ƺ���Щ�ĵá�\n"NOR);
        tell_object(me, HIY"�㰴�ն������ԣ���Ϣ���ԡ���ǿѨ������������ᡢ���ء����š�����\n+"+
"��Ѩ��һ·���ż�׵�������ߵĶ��Ǳ��϶��θ���ҪѨ��Ȼ���Ǽ��С����ࡢ������������\n"+
"��̨��������������յ�����׵�����š��縮���Ի���ǿ�䡢�󶥡��������ŵġ��ٻ�Ѩ����\n"NOR);
		tell_object(me,BYEL+HIW"\n������ǧ����࣬���ڵó���Ը�����������ڻ��ͨ��\n"NOR);
       	//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/tls/yyz/liumai/pass",1);
		me->set("title",HIG"�����񽣴���"NOR);
		me->set("mytitle/quest/6mtitle",HIG"�����񽣴���"NOR);
		me->start_busy(1);
		log_file("quest/liumaishenjian", sprintf("%8s(%8s) ʧ��%d�κ󣬳������������񽣵ľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/tls/yyz/liumai/fail"),i,me->query("combat_exp")) );
	  }
	  else
	  {
		me->add("quest/tls/yyz/liumai/fail",1);
		me->set("quest/tls/yyz/liumai/time",time());
		command("hehe ");
		tell_object(me,HBGRN+HIW"\n�����˶�����ָ�㣬��Ȼ�����������񽣵İ��أ����Ƕ������񽣹�����������ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		log_file("quest/liumaishenjian", sprintf("%8s(%8s) �����񽣽���ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/tls/yyz/liumai/fail"),i,me->query("combat_exp")) );
	   }
    	return 1;
    }

}
