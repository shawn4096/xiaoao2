// yideng.c һ�ƴ�ʦ By River@SJ 2002.6.6

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

int ask_hr();
int ask_qiu();
int ask_xtg();
int ask_ronghe();
int ask_yinggu();
int check_yideng(object me);

void create()
{
	set_name("һ�ƴ�ʦ", ({ "yideng dashi", "yideng", "dashi" }) );
	set("title",HIR"�ϵ�"NOR);
	set("gender", "����" );
	set("class", "bonze");
	set("age", 78);
	set("str", 45);
	set("con", 40);
	set("dex", 35);
	set("int", 35);
	set("per", 28);
	set("unique", 1);
    set("no_get", 1);

	set("max_qi", 45000);
	set("max_jing", 7500);
	set("eff_jingli", 8500);
	set("neili", 32000);
	set("max_neili", 32000);
	set("jiali", 250);
	set("combat_exp", 15500000);
	set("score", 20000);
	//����
    set("yideng/ronghe","pass");
	create_family("������", 12, "�׼ҵ���");

	set("long", "һ�����ֲ�ɮ�ۣ����������İ�ü���۽Ǵ�����������Ŀ���飬\n"+
		"ü����������࣬��һ��Ӻ�ݸ߻�����ɫ��ȴ��һ����֪��\n");

	set_skill("parry", 500);
	set_skill("dodge", 500);
	set_skill("qingyan-zhang", 500);
	set_skill("strike", 500);
	set_skill("buddhism",200);
	set_skill("force", 500);
	set_skill("literate", 350);
	set_skill("sword", 500);
	set_skill("duanjia-jianfa", 500);
	//set_skill("cuff", 500);
	//set_skill("axe",500);
	//set_skill("pangen-fu",500);
	//set_skill("duanjia-quan", 500);
	set_skill("yiyang-zhi", 550);
	set_skill("finger", 550);
	set_skill("qiantian-yiyang", 530);
	set_skill("tianlong-xiang", 500);

	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "yiyang-zhi");
	map_skill("sword", "duanjia-jianfa");
	map_skill("force", "qiantian-yiyang");
	//map_skill("cuff", "duanjia-quan");
	map_skill("strike", "qingyan-zhang");
	map_skill("finger","yiyang-zhi");
	prepare_skill("finger","yiyang-zhi");
	set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
				(: exert_function, "yiyang" :),
                (: perform_action, "finger.yizhisanmai" :),
				(: perform_action, "finger.sandie" :),
				//(: perform_action, "brush.yiyangshu" :),
        	    //(: perform_action, "brush.shiguwen" :),        
	    }));
	
	set("inquiry", ([
		"here": "�������ʯ�ݡ�",
		"����": (: ask_hr :),
        "�ȶ�": (: ask_qiu :),
      	"���칦": (: ask_xtg :),
    	"�������": (: ask_ronghe :),
		"������": (: ask_yinggu :),
	]));

	setup();
	carry_object("/d/tls/obj/jiasha")->wear();
	carry_object("/d/tls/obj/sengxie")->wear();
}

void attempt_apprentice(object ob)
{
/*	if (!ob->query("quest/tls/yideng")) 
	{
		command("buddhi");
		command("say �������ൽ�ˣ����������ڴ�����棬�޷�����Ϊͽ�������½⣡\n");
        return;
	}*/
	if ( ob->query_skill("qiantian-yiyang",1) < 450 ){
		command ("hmm");
		command ("say ��Ǭ��һ�������֮��,����450���ҿɲ����㣡");
		return;
	}
	if( ob->query_int() < 60){
		command("say ��ѧ֮���������Ըߣ����ҿ�" + RANK_D->query_respect(ob) + "�������ƺ�����60��");
		return;
	}
	if(ob->query("shen") < 2000000){
		command("say ���������û��ң�����λ" + RANK_D->query_respect(ob) + "����2m�����ҿ����ʺ����Ҵ������ȥ�ˡ�");
		return;
	}
	if(ob->query_skill("liumai-shenjian", 1)){
		command("say ��λ" + RANK_D->query_respect(ob) +"�Ѿ�ѧ���������񽣣������ʺϰ���Ϊʦ�ˡ�");
		return;
	}

	if (ob->query("tls")) {
		command ("say ���Ѿ��������³��ҵ����ˣ��Ҳ����������ˣ�");
		return;
	}
	command("smile");
	command("say �ܺã�" + RANK_D->query_respect(ob) + "���Ŭ�������ձض��гɡ�");
	command("recruit " + ob->query("id") );
	//ob->delete("tls"); //�ͺ���ĳ�ͻ����ʱ���ε�
    //ob->delete("tls"); 
	//ob->delete("class");
	ob->set("title",HIY"������ϵ����µ���"NOR);
}

int ask_hr()
{
	object me= this_player();
	if (me->query_temp("quest/jindaoheijian/huangrong3")!=1) {
		command("say С���ﻹ�ðɣ�");
		command("haha");
		return 1;
	}

	command("say ��20�����ˣ���ǧ�߻������ء�");
	command("say ��֪�����ܰ�æ��");
	message_vision(WHT"�㽫�ڻ��������ʦ�����������һ�ƴ�ʦ!\n"NOR,me); 
	command("say �ðɣ�����ȥ����ȣ������ʹ��ȶ���ȥ��");
	command("say ����ԩԩ�౨��ʱ���ˣ�");
	me->delete_temp("quest/jindaoheijian/huangrong3");
	me->set_temp("quest/jindaoheijian/yideng",1);
	return 1;
}

int ask_qiu()
{   
    object me= this_player();
    if (me->query("quest/tzauto/pass")|| me->query("family/family_name")!="���ư�")
                 {   
                    command(" say �ȶ���Ը���ˣ���Ը��մȾ����֮�£�ʩ����ذɡ�");
                    return 1;
                  }
    command("say ��������Ƶ����˵���ɹŴ���ù��������£������Ƶ��Ϲ������Ա�ؾ��ػأ�����������\n");
    command("say �ȶ�����������ʹ�����ȥ��̽��Ϣ���Ѿ�������ҹû�����ˡ�\n");
    me->set_temp("quest/tzauto/yideng",1); 
  return 1;

}

int accept_object(object me, object ob) 
{
   if (userp(ob)) return 0;
 
   if( ob->query("id") == "lingwen" 
	  && me->query("quest/qz/xtg/dingyang/start")
	  && ob->query("owner")==me->query("id")
      && me->query("family/family_name")=="ȫ���"
      && me->query_temp("quanzhen/force") 
      && !me->query("quanzhen/force")    )
   	   {
               command("ah ");
               command("say �벻������֮�껹��Ŀ���������˵��ּ��� "); 
               me->delete_temp("quanzhen/force");
               message_vision(HIM"һ�ƴ�ʦ�������еġ���ƪ����������Ĭ�˰��죬���ɵ�����̾��һ����������һ�γ���������������\n"NOR+
                          HIG"ԭ�����껪ɽ�۽�֮���������˶��ϵ۶���ү��һ��ָ��Ϊ������ڶ���ͺ���ʦ�����´������ϵۻ����д蹦��\n"+
                               "�ϵ۽�һ��ָ��Ҫּ���ϣ�����˵������������֪������������ʮ��ϲ���������������������칦���򴫸��˶���ү��\n"+
                               "���������ٱ�֮���Ե����������Ҿɼ��ַ������ǲ����������������칦���д��ˣ��ټ��ϻ�ү��һ��ָ�񹦣�������\n"+
                               "�п��Ƹ�󡹦֮�ˣ��Ͳ��������������ˡ��� \n"NOR, me);
               command("say ��ʱ���ķ������ף���������ǧ����������������ּ��Ҫ�����칦�������ģ�Ҫ��������֮������һ����������ŷ����֮�ˡ� ");         
               command("sigh ");     
           
               me->set_temp("xtg1",1);
               me->set("give_book",1);
			   destruct(ob);
              // call_out("destructing", 1, ob); 
                return 1; 
      }
   else return 0;
             }

int ask_xtg()
{
	object me= this_player();
	if (!me->query_temp("xtg1")&& !me->query("give_book")) {
		command("say ���칦�������������ҵ��ڹ�������");
		return 1;
	}
	if (me->query("int")<42) {
		command("say ����������Բ���42��");
		return 1;
	}
  if( me->query("quanzhen/force")== "pass")
  {   command("say ������С���Ѿ���ȫ���������칦��Ҫּ�����ˡ�");
      command("haha ");
      return 1;
  }

	if(me->query("quanzhen/force")== "try"   )
	{
				command("say ������С�ѻ��ö����ϰ���С�");
						return 1;
		}

    if( time()-me->query("xtg/dyz/time")<86400)		
   		{
				command("say С�ѻ���ȥ��Ϣһ�°ɡ�");
			    return 1;
		}
	if( me->is_busy())		
   		{
				command("say С��̫æµ�ˣ�����ȥ��Ϣһ�°ɡ�");
			    return 1;
		}
	command("say ��������ѧ��һ��ָ���������ã���δ��ϰ����˵Ҳû����ͽ�ܡ�");
    command("say ���������Ѹߣ�����Ҳ��˶���ˡ���˵����ŷ�������д��ˣ�����֮�ϣ�Ψ���칦��һ��ָ�����񼼲��ܿ��Ƹ�󡹦��");
    command("say ��Ȼ��õ����������˵����칦��Ҫ�����ı㽫��һ��ָ���ڸ��㣬�㵱������ϰ����Ҫ���������˺���������");


     message_vision(HIY"һ�ƴ�ʦ���Ƹ��أ�����ʳָ����������仺��$N�ϰ��������Ѩȴ��ȫ��һָ����֮�£�����֪Ҫ�������һ��Ѩ�����Ŵ���Ѩ�Դ�ָ֮�ݣ�\n"NOR+
                        HIG"һ�ƴ�ʦ����δ�꣬��������������һָ��������ȴ��ָ��$NС������һָ�����ֵ�ҪѨ���㣬�Ǹ������ʮ����Ѩ��������\n"+
                               "ͨ�ȣ�������ע��������ֱ�ֺ�ǡ���������������һָ����֮�¡�\n"+
                        HIM"����һ�ƴ�ʦ����ָ�ֳ�����һָѸ�����磬ֱָ$Nü�ģ�ָ���������ƺ�ͷ��̫�������У��ٻᣮ���ȸ���ҪѨ������һָ���֡� \n"NOR, me);
    command("smile ");
    command("say ��ɿ������ˣ�");
    me->delete_temp("xtg1");
    tell_object(me,HIY"\n�㿪ʼ����Ļ���һ�ƴ�ʦ��һ��һʽ����\n"NOR);
       me->start_busy(999);              
       remove_call_out("thinking");
       call_out("thinking",5, me );
	return 1;
}


int thinking(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("try_yyz")<(3+random(3)))
    { me->add_temp("try_yyz",1);
          if(random(2)) tell_object(me,HIG"\n����������Ÿղ�һ�ƴ�ʦ��һ��һʽ...\n"NOR);
             else tell_object(me,HIY"\nͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
   else
   {  
	  me->delete_temp("try_yyz");
      total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 25;
      if(me->query("m-card-vip")) j =  23;
      if(me->query("y-card-vip")) j =  20;
      if(me->query("buyvip"))     j =  17;
      i=random(j);

      if (i<2 
		 && random(me->query("int")) >= 40 
	     && me->query("kar")<31
		 && random(me->query("kar"))>28)
	  {       
          tell_object(me,HIM"\n�����칦���������У���ȱ�裬��������أ���������������֮����һ��һ����������������������ת���ݣ�\n"NOR);
          message_vision(HIC"\n$N�����ʹ��һ��ָָ���������칦�����ƺ���Щ�˽��ˡ���\n"NOR,me); 
          tell_object(me,HIR"������ʹ��һ��ָָ���������칦�����ƺ���Щ�˽��ˣ�ʣ�µľ����ڼ���ϰ�ˣ�\n"NOR);
          me->set("quanzhen/force", "try" );
          me->set("title",HIC"ȫ��� ���칦����"NOR);
          log_file("quest/dingyang", sprintf("%s(%s) ʧ��%d�γɹ��⿪�����롣��Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("xtg/dyz/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->start_busy(1);
        }
        else
        {
         tell_object(me,HIG"\n���˼��ã�����Ҫ�졣\n"NOR);
         message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿�����\n"NOR,me); 
         tell_object(me,HBBLU"\n�ܿ�ϧ���㱾�γ������칦����������ʧ�ܣ�\n"NOR);
         tell_object(me,HBBLU"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
         tell_object(me,HBBLU"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
		 log_file("quest/dingyang", sprintf("%s(%s) ���ܶ�����ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("xtg/dyz/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
         me->add("xtg/dyz/fail",1);
         me->set("xtg/dyz/exp", me->query("combat_exp") );
         me->start_busy(1);
         me->set("xtg/dyz/time",time());
        }

     }

}

//һ��ָ�����칦�ں�

int ask_ronghe()
{
	object me= this_player();
	int total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
	if (!me->query_temp("yyzjx")) {
		command("say һ��ָ�����칦���ں����Ҵ���μҵļҴ�������\n");
		return 1;
	}
    if (me->query_skill("yiyang-zhi",1)<450) {
		command("say �㹦��̫���ˣ����ǰ����һ��ָ����������˵�ɡ�\n");
		return 1;
	}
	if (me->query("int")<40) 
	{
		command("say �����������̫���ˣ����ǰѰ���������������˵�ɡ�\n");
		return 1;
	}

    if( me->query("yideng/ronghe")== "pass")
    {   
		command("say ������С���Ѿ���ȫ������һ��ָ��Ҫּ�����ˡ�");
        command("haha ");
		me->set("title",HIR"�ϵ�"+HIY"һ��ָ����"NOR);
        return 1;
    }
    if( me->is_busy())		
   		{
				command("say С��̫æµ�ˣ�����ȥ��Ϣһ�°ɡ�");
			    return 1;
		}
    if( time()-me->query("ydrh/time")<86400)		
   	{
		command("say ������Ҳ̫�ڿ���Ү��С�ѻ���ȥ��Ϣһ�°ɡ�");
		return 1;
	}
	command("say ��һ��ָ�����Ǵ����ѧ����ʱ����ڻ�ɽ�����۽������������κ��ˣ�");
    command("say �����������˺�����ʦ���ܲ�ͨһ�����������Ҵ������Ķ�ѧ�����칦�����������������̡�");
    command("say ��Ȼ���������Ѹߣ���Ȼ��Ե���Ҿͽ��Ҷ�����ĵô�������,�㵱������ϰ����Ҫ��һ��ָ��ѧ������");
    me->delete_temp("yyzjx");
	me->set_temp("juexue");

     message_vision(HIY"һ�ƴ�ʦ���Ƹ��أ�����ʳָ����������仺��$N�ϰ��������Ѩȴ��ȫ��һָ����֮�£�����֪Ҫ�������һ��Ѩ�����Ŵ���Ѩ�Դ�ָ֮�ݣ�\n"NOR+
                        HIG"һ�ƴ�ʦ����δ�꣬��������������һָ��������ȴ��ָ��$NС������һָ�����ֵ�ҪѨ���㣬�Ǹ������ʮ����Ѩ��������\n"+
                               "ͨ�ȣ�������ע��������ֱ�ֺ�ǡ���������������һָ����֮�¡�\n"+
                        HIM"����һ�ƴ�ʦ����ָ�ֳ�����һָѸ�����磬ֱָ$Nü�ģ�ָ���������ƺ�ͷ��̫�������У��ٻᣮ���ȸ���ҪѨ������һָ���֡� \n"NOR, me);
    command("smile ");
    command("say ��ɿ������ˣ�");
    
    tell_object(me,HIY"\n�㿪ʼ����Ļ���һ�ƴ�ʦ��һ��һʽ����\n"NOR);
    me->start_busy(999);              
    remove_call_out("tkjx");
    call_out("tkjx",2, me );

	return 1;
}

int tkjx(object me)
{
  
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("try_juexue")<(5+random(3)))
    { 
	  me->add_temp("try_juexue",1);
      if(random(2)) tell_object(me,HIG"\n����������Ÿղ�һ�ƴ�ʦ��һ��һʽ...\n"NOR);
      else tell_object(me,HIY"\nͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("tkjx");
	  call_out("tkjx",2+random(3), me);
	}

   else
   {  
	  me->delete_temp("try_juexue");
    //  total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 25;
      if(me->query("m-card-vip")) j =  23;
      if(me->query("y-card-vip")) j =  20;
      if(me->query("buyvip"))     j =  15;
      i=random(j);
//�����⿪��
     if (random(me->query("kar"))>27
		 &&random(me->query("int"))>40
		 &&i<3 )
       {
       tell_object(me,HIM"\n����һ��ָ�����������������Ǭ��һ�������ں���һ�������У���ȱ�裬��������أ���������������\n֮����һ��һ����������������������ת���ݣ�\n"NOR);
       message_vision(HIC"$n��$NЦ�����뵱���������˴����������칦�ı��������һ��ָ�������칦�ںϣ���Ȼ������Ե���Ҿʹ�������!\n"NOR,me,this_object());
	   message_vision(HIC"Ҳ���������������˵�һƬ���ģ���Ȼ���Ǵ����и����ͷ����ŷ�����,��������Ĵ���һ��������������\n"NOR,me,this_object());
	   message_vision(HIR"$n�������������ڸ��Լ������칦����һ���Դ��ڸ�$N��\n"NOR,me,this_object());

	   message_vision(HIC"\n\n$N�����ʹ��һ��ָָ���������칦�����ƺ���Щ�˽��ˡ���\n"NOR,me); 
       tell_object(me,HIR"������ʹ��һ��ָ�����������գ�\n"NOR);
       me->set("yideng/ronghe","pass");
	   //me->set_skill("xiantian-gong",200);
	   //tell_object(me,HIC"��������һ�ƵĽ̻壬������칦�����ˣ�\n"NOR);

       me->set("title",HIR"�ϵ�"+HIY"һ��ָ����"NOR);
	   
       log_file("quest/yyzronghe", sprintf("%s(%s) ʧ��%d�κ�ɹ��⿪һ��ָ�ںϡ���Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("ydrh/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->start_busy(1);
       }
     else
       {
       tell_object(me,HIG"\n���˼��ã�����Ҫ�졣\n"NOR);
       message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿�����\n"NOR,me); 
       tell_object(me,HBBLU"\n�ܿ�ϧ���㱾�γ���һ��ָ��ѧ����ʧ�ܣ�\n"NOR);
       tell_object(me,HBBLU"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
       tell_object(me,HBBLU"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
       me->add("ydrh/fail",1);
       me->set("ydrh/exp", me->query("combat_exp") );
       me->start_busy(1);
       me->set("ydrh/time",time());
	   log_file("quest/yyzronghe", sprintf("%s(%s) ����һ��ָ�ں�ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("ydrh/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
       } 
     }
}

int ask_yinggu()
{
	object me= this_player();
	if (!me->query_temp("nqg/askyingok")) {
		command("say ԩԩ�౨��ʱ�ˣ�");
		command("sigh ");
		return 1;
	}

	command("say ��20�����ˣ��������ء�");
	command("say �λ�ү�Ѿ����������ˣ������е���һ�ƴ�ʦ�������ҡ�");
	message_vision(WHT"�㽫�����ô������ļ��ź����������һ�ƴ�ʦ!\n"NOR,me); 
	
	command("say ����ԩԩ�౨��ʱ���ˣ�");
	command("say �ðɣ����������е����ԩ���ɡ�");
	command("say �ðɣ����ְɡ�");
	write(HIG"���Ƿ���ɱ��һ�ƴ�ʦ����(yes)���ǲ���(no)��\n");
	write(HIR"�����ػش���ɱ��һ�ƴ�ʦ���⵽����������ʿ��������\n");
	add_action("do_huida","answer");
	return 1; 

}

int do_huida(string arg)
{
	object yideng;
	object me=this_player();
	
	if (!objectp(yideng=present("yideng dashi",environment(me))))
	{
		yideng=new("d/dali/yideng/npc/yideng");
		yideng->move(environment(me));
	}
	if (!arg) return notify_fail("��ش�ʲô��");
	if (arg=="yes")
	{
		command("say ��ͺ¿���ϻ���˵��ɱ�˳�����Ƿծ��Ǯ�����������ɣ�\n");
		command("say ��ɱ��,�ҶԲ�ס���õĳ�ŵ���ҵ�������������\n");
		me->set_temp("nqg/killyideng",1);

		me->kill_ob(yideng);
		yideng->kill_ob(me);
    
		me->delete_temp("nqg/askyingok");
		//call_out("check_yideng",1,me);
		return 1;
	}else if(arg=="no")
	{
		command("say �ðɣ���Ȼ�㲻Ը�����֣��Ǿ��Ȼ�ȥ�ɣ�\n");
		me->delete_temp("nqg/askyingok");
		return 1;
	}	
}
/*
int check_yideng(object me)
{

	object yideng;
	yideng=present("yideng dashi",environment(me));
    if (objectp(yideng)&& me->is_fighting(yideng))
    {
		remove_call_out("check_yideng");
		call_out("check_yideng",2,me);
		return 0;
    }
	if (!objectp(me)) return 0;
	
	me->set_temp("yideng/kill_yideng", 1);
	me->add("shen",-random(2000000));
	me->set("tls/killyideng",1);

	message_vision("\n\n�����һ��������������ͺ¿�������������°ܽ���\n", me);

	message_vision("\n\n�����Ǹõ��˻�ȥ�����ý����ʱ���ˡ�\n", me);

	return 1;

}*/