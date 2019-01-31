// qqren.c ��ǧ��

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
#include "tz_job1.c"

int ask_qiubai();
string do_change();
int thinking(object me);
int ask_tiezhang();
int ask_zhangdao();
int ask_aomi();

void create()
{
        set_name("��ǧ��", ({ "qiu qianren", "qiu", "qianren", "ren"}));
        set("nickname", "����ˮ��Ư");
        set("long",
        "����������������ư�İ���-����ˮ��Ư��ǧ��\n"
        "����һ��������ͷ�����Ƹ���������ֻ���һ�Ѵ����ȡ�\n");
        set("gender", "����");
        set("age", 60);
        set("attitude", "peaceful");
        set("unique", 1);
        set("shen_type", -1);

        set("str", 45);
        set("int", 30);
        set("con", 28);
        set("dex", 35);

        set("max_qi", 39500);
        set("max_jing", 9000);
        set("max_neili", 36000);
        set("eff_jingli", 7500);
        set("jiali", 250);
        set("combat_exp", 12350000);
        set("score", 40000);
        set_skill("axe", 500);
		set("tiezhang/pass",1);
		

	
		
set_skill("lietian-fu", 500);

		set_skill("force", 500);
        set_skill("guiyuan-tunafa", 500);
        set_skill("dodge", 500);
        set_skill("shuishangpiao", 500);
        set_skill("strike", 500);
        set_skill("tiezhang-zhangfa", 500);
        set_skill("parry", 500);
        set_skill("literate", 180);
        set_skill("blade", 500);
        set_skill("liuye-daofa", 500);
        set_skill("tiezhang-xinfa", 200);

        map_skill("force", "guiyuan-tunafa");
        map_skill("dodge", "shuishangpiao");
        map_skill("strike", "tiezhang-zhangfa");
        map_skill("parry", "tiezhang-zhangfa");
        map_skill("blade", "liuye-daofa");
		map_skill("axe", "lietian-fu");
		
        prepare_skill("strike", "tiezhang-zhangfa");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "strike.tiezhang" :),
                (: perform_action, "strike.tianlei" :),
                (: perform_action, "strike.lianhuan" :),
				(: perform_action, "strike.qinna" :),
                (: perform_action, "strike.zhangdao" :),
				(: perform_action, "strike.pushan" :),
                (: perform_action, "strike.lianhuan" :),
                (: perform_action, "strike.heyi" :),
				(: exert_function, "guiyuan" :),
                (: perform_action, "strike.duoming" :)
        }));
        set_temp("apply/armor", 80);
        set_temp("apply/damage", 80);
        set_temp("apply/attack", 80);

        create_family("���ư�", 14, "����");

        set("inquiry", ([
                       "name" : "�Ϸ���ǡ�����ˮ��Ư����ǧ�������Ϸ�������ʲô��ô��\n",
                       "here" : "����������ư����̳���ڣ�����û�£���Ҫ�Ĵ����ߣ�����ɱ��֮��������\n",
                       "�Ϲٽ���" : (: ask_qiubai :),
                       "����" : (: ask_job1 :),
			           "���ư���" : (: ask_aomi :),
			           "���ƾ���" : (: ask_tiezhang :),
					    "�����Ƶ�����" : (: ask_zhangdao :),
                       "����" : "��ȥ���߷���Ҫ�ɣ�",
                ]));
        setup();
        carry_object("/d/tiezhang/npc/obj/mayi")->wear();
	    carry_object(ARMOR_D("buxue"))->wear();
}

void init()
{
        object me, ob;
        ::init();
        ob = this_player();
        me = this_object();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_task","task");
}

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping fam = ob->query("family");

        if ((int)ob->query("shen") >= -2000000) {
                command("hehe");
                command("say ����ǧ��ɲ����Ĵ����������ͽ�ܣ�������2m��Ҫ�����ҡ�");
                return;
        }
        if(fam["master_name"] == "�Ϲٽ���"){
                command("ah");
                command("grin" + ob->query("id"));
                command("say �Ϲٰ����������ѹ����������");
                command("say "+RANK_D->query_respect(ob)+"ԭ�����ϰ������ŵ��Ӱ���ʧ����"+RANK_D->query_self(me)+"����������Ϊͽ��");
                return;
        }
        if ((int)ob->query_skill("guiyuan-tunafa", 1) < 350) {
                command("say Ҫѧ��Ϊ������书�������и�����ڹ���Ϊ������350���������ҡ�");
                command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ���ڹ�Ԫ���ɷ��϶��µ㹦��");
                return;
        }
		if ( !ob->query("quest/tz/dichuan")) {
                command("say Ҫѧ��Ϊ������书���������㹻���ҳ϶ȣ��������Ұ����Ƶ������������");
                //command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ���ڹ�Ԫ���ɷ��϶��µ㹦��");
                return;
        }
        if ((int)ob->query_str() < 50) {
                command("say ��ѧ�ҵ������Ʒ�������Ҫ���㹻������,�����������50,�������ҡ�");
                command("say �ڱ������棬"+RANK_D->query_respect(ob)+"�Ƿ��Ӳ��˵㣿");
                return;
        }
        command("say �ðɣ��Ҿ��������ˡ�ϣ������������񹦣���֮������");
        command("recruit " + ob->query("id"));
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                add("apprentice_available", -1);
        ob->set("title", "���ư��ʮ�Ĵ���������");
        ob->set("class","brigand");
}

int ask_qiubai()
{
        say("������ʦ��������ʮ�����������ȹ�����֮�����ж�ͼ����\n"
            "��ȫ���书�������ܡ���ϧʮ��ǰ�����ں�������Χ������������\n");
        return 1;
}

int ask_aomi()
{
	object me=this_player();
	if (me->query("family/family_name")!="���ư�") 
	{
		command("say ���ƾ����������ưﲻ��֮�գ���һ�����ɵ�������������");
		return 1;
	}
	if (me->query("str")<40) 
	{
		command("say ���ƾ���������Ҫ���ߵ�������������ڻ��ͨ���㲻��40������Ŭ��ȥ�����ɣ�");
		return 1;
	}
    if( me->query("tiezhang/pass"))
    {   
	  command("say ������С���Ѿ���ȫ���������ƾ�����Ҫּ�����ˡ�");
	  me->set("quest/tz/tzzf/tiezhang/pass",1);
      command("angry ");
      return 1;
    }

	if( me->query("combat_exp",1)<5000000)
    {   
	  command("say ��ľ���ֵ̫�ͣ�����ϰ�ú��������ƾ�����");
      command("sigh "+me->query("id"));
      return 1;
    }
    if( me->query_skill("tiezhang-zhangfa",1)<450)
    {   
	  command("say ��������Ʒ�û�д�ɣ�����ϰ�ú��������ƾ�����");
      command("sigh "+me->query("id"));
      return 1;
    }
    if( time()-me->query("tiezhang/time")<86400)		
   	{
		command("say С�ѻ���ȥ��Ϣһ�°ɡ�");
		return 1;
	}
	command("say �������ռ�����Ҳ�������������������ģ�����ȥȫ��̺�ɽƽ��һ��ȥ������˵������Щ������\n");
	me->set_temp("tzjj/askqiu",1);
	return 1;

}
int ask_tiezhang()
{
	object me= this_player();
	if (!me->query_temp("tzjj/killover"))
	{
		command("say �������û��ȥ��˵���ǵط�����δ��������Ƶľ��裬������ȥ�������˵�ɡ�\n");
		return 1;
	}
	if (me->query("family/family_name")!="���ư�") 
	{
		command("say ���ƾ����������ưﲻ��֮�գ���һ�����ɵ�������������");
		return 1;
	}
	if (me->query("str")<40) 
	{
		command("say ���ƾ���������Ҫ���ߵ�������������ڻ��ͨ���㲻��40������Ŭ��ȥ�����ɣ�");
		return 1;
	}
    if( me->query("tiezhang/pass"))
    {   
	  command("say ������С���Ѿ���ȫ���������ƾ�����Ҫּ�����ˡ�");
	  me->set("quest/tz/tzzf/tiezhang/pass",1);
      command("angry ");
      return 1;
    }
	if( me->query("combat_exp",1)<5000000)
    {   
	  command("say ��ľ���ֵ̫�ͣ�����ϰ�ú��������ƾ�����");
      command("sigh "+me->query("id"));
      return 1;
    }
    if( me->query_skill("tiezhang-zhangfa",1)<450)
    {   
	  command("say ��������Ʒ�û�д�ɣ�����ϰ�ú��������ƾ�����");
      command("sigh "+me->query("id"));
      return 1;
    }
    if( time()-me->query("tiezhang/time")<86400)		
   	{
		command("say С�ѻ���ȥ��Ϣһ�°ɡ�");
		return 1;
	}

	command("say �����Ʒ������������������Ͻл��ӵĽ���ʮ���Ʋ������ʽ�ϸ��Ǿ�����ס������ƹ�����ͬѰ����");
    command("say ���ư￪ɽ�����������������ԭ�����ľ��������Ʒ��������Ϲٽ�������������໯���˲��پ�΢������");
    command("say ��Ȼ����������ư����Ĺ������ұ㽫�����ƾ������ڸ��㣬�㵱������ϰ����Ҫ��������������˺���������");
	command("say ����ϸ�ˣ�");


    message_vision(HIR"��ǧ����������ǰ���������Ƹ����ĳ��������仺����ȴͬʱϮ��������ǿ����ɽ������ѹ�˹�����\n"
	+"������˺��ӱܣ�ȴ���ﻹ���ü������ϰ��������Ѩȴ��ȫ����������֮�£�\n"NOR+
                        HIG"��ǧ������δ�꣬�������������������ĳ������ȴ������$NС������֫\n"+
                        HIM"$NһƳ֮����ѿ�������ǧ��������һץ��Ȼ���ͣ���Զ����������ôһ��������������,�����������������ɱ�С� \n"NOR, me);
    command("smile ");
    command("say ��ɿ������ˣ�");
    //me->delete_temp("xtg1");
       tell_object(me,HIY"\n�㿪ʼ����Ļ�����ǧ���һ��һʽ����\n"NOR);
       me->start_busy(999);
	   me->set_temp("tzjueji/ask",10);
       remove_call_out("thinking");
	  // me->set("tiezhang/time",time());//��ǵ�ǰʱ��
	   //me->set("tiezhang/exp",me->query("combat_exp"));
       call_out("thinking",5, me );
	return 1;
}


int thinking(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("tzjueji/ask",1)>0)
    { 
	  me->add_temp("tzjueji/ask",-1);
          if(random(2)) tell_object(me,HIG"\n����������Ÿղ���ǧ���һ��һʽ...\n"NOR);
             else tell_object(me,HIY"\nͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}

   else
   {  
	  me->delete_temp("tzjueji/ask");
      total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
      i=random(j);

     if (i < 3 
		 && random(total) > 80
		 && random(me->query("str"))>=35
		 && random(me->query("kar"))>=25  )
     {
       
          tell_object(me,HIM"\n�����ۻ�������������������һ��һ�����þ�����������ת���ݣ�\n"NOR);
          message_vision(HIC"\n$N�����ʹ�������Ʒ��ƺ���Щ�˽��ˡ���\n"NOR,me); 
		  message_vision(HIC"\n$N�����ʹ��ˮ��Ư�Ṧ�����ƺ���Щ�˽��ˡ���\n"NOR,me); 
          tell_object(me,HIR"������ʹ�����ƾ����ڻ��ͨ��\n"NOR);
		  command("chat* laugh "+me->query("id"));
          command("chat ������ˮ��Ư�������������Ĵ����ˣ������޺��� ");
		  message_vision(HIW"\n��ǧ��һʱ���ˣ������ȷ�ǿ���֮�ģ����ǽ��Լ����Ṧ������ˮ��Ư���İ���һ���Զ����ڸ�$N����\n"NOR,me); 
          me->set("tiezhang/pass",1);
		  me->set("tz/piao",1);
          me->set("title",HIR"����"+HIC"ˮ��Ư"NOR);
		  me->set("mytitle/quest/tiezhangtitle",HIR"����"+HIC"ˮ��Ư"NOR);
          log_file("quest/tiezhang", sprintf("%s(%s) ʧ��%d�κ󣬳ɹ��⿪���ƾ�������Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("tiezhang/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->start_busy(1);
		  me->delete_temp("tzjj/killover");
        }
        else
        {        
		 tell_object(me,HIG"\n���˼��ã�����Ҫ�졣\n"NOR);
         message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿�����\n"NOR,me); 
         tell_object(me,HIW"\n�ܿ�ϧ���㱾�γ������ƾ�������ʧ�ܣ�\n"NOR);
         tell_object(me,HIY"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
         tell_object(me,HIM"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
		 log_file("quest/tiezhang", sprintf("%s(%s) �������ƾ���ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("tiezhang/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
         me->add("tiezhang/fail",1);
         me->set("tiezhang/exp", me->query("combat_exp") );
         me->start_busy(1);
         me->set("tiezhang/time",time());
		 me->delete_temp("tzjj/killover");
        }

     }

}
//ask zhangdao

int ask_zhangdao()
{
	object me=this_player();
	me->start_busy(10);
	if (me->query("family/family_name")!="���ư�") {
		command("say �㲻���Ұ��еĵ��ӣ�����������\n");
		return 1;
	}
	if (me->query("quest/tz/tzzf/zhangdao/pass")) {
		command("say ���Ѿ�ȫ�������������Ƶ��似��\n");
		return 1;
	}
	if (time()-me->query("quest/tz/tzzf/zhangdao/time")<86400) {
		command("say ������̫�ڿ��ˣ�");
		return 1;
	}
	//if (me->query_temp("tzzf/dunwu1")) 
	//{
		   message_vision(HIC"��վ���Ƕ���������Ҿ������ǧ�𲻶�����������Ƶ��İ��ء�\n"NOR,me);
           me->start_busy(999);
		   remove_call_out("thinking1");
		   call_out("thinking1",1,me);
		   //me->delete_temp("tzzf/dunwu1");
	//}
	return 1;
}

int thinking1(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
  j=random(10);

  me->set("quest/tz/tzzf/zhangdao/time",time());

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) ���������Ƶ�����ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_zhangdao")<(10+random(10)))
   {  
	  me->add_temp("canwu_zhangdao",1);

	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n�㽫ʦ�������ڵ��ķ��˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n��Ȼ�����ƺ�ץס��һЩ����\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n���������״̬������һƬ�������ƺ�Ҫץס�Ǹ������ˣ�..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n������Ķ����������ģ������������ƺ���Щ����.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n�������������ƣ��֮�ʣ��ƺ�����ƿ����..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n��˼άƯ���ڿ��У�����Ӥ����ԡ.������ˬ.\n"NOR);
			break;
		default:tell_object(me,YEL"\n��̾��һ�������������ǲ�����Ч����.\n"NOR);
			break;

	  }
      

	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));
	
	  remove_call_out("thinking1");
	  call_out("thinking1",3+random(3), me);
	  return 1;

   } 
   else if (i>=20
			&& j>=8
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N���������������������˰��������ڵ������Ƶ��İ��أ������Ʒ��ָ���һ��¥����\n"NOR,me); 
         log_file("quest/tzzhangdao", sprintf("%s(%s) �ɹ�����%d�β��򣬳ɹ����������Ƶ����أ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/tz/tzzf/zhangdao/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/tz/tzzf/zhangdao/time",time());
		 me->set("quest/tz/tzzf/zhangdao/pass",1);
		 me->delete_temp("canwu_zhangdao");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵��������������һ�����񰡡���\n"NOR,me); 
		 message_vision(HIY"\n$N���������Ƶ���������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/tzzhangdao", sprintf("%s(%s) ʧ�ܣ���%d��,ʧ�ܲ��������Ƶ���������ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/tz/tzzf/zhangdao/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/tz/tzzf/zhangdao/fail",1);
		 me->set("quest/tz/tzzf/zhangdao/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_zhangdao");
		 return 1;
   }

}