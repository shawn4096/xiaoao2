// qqren.c ��ǧ��

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
#include "tz_job1.c"

int ask_qiubai();
string do_change();
int thinking(object me);
int ask_tiezhang();
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

        set("str", 35);
        set("int", 30);
        set("con", 28);
        set("dex", 35);

        set("max_qi", 9500);
        set("max_jing", 6000);
        set("max_neili", 16000);
        set("eff_jingli", 7500);
        set("jiali", 100);
        set("combat_exp", 9350000);
        set("score", 40000);
        
set_skill("axe", 450);

		set_skill("brush", 450);
		
set_skill("yingou-bifa", 450);
		
set_skill("lietian-fu", 450);

		set_skill("force", 450);
        set_skill("guiyuan-tunafa", 450);
        set_skill("dodge", 450);
        set_skill("shuishangpiao", 450);
        set_skill("strike", 450);
        set_skill("tiezhang-zhangfa", 450);
        set_skill("parry", 450);
        set_skill("literate", 180);
        set_skill("blade", 450);
        set_skill("liuye-daofa", 450);
        set_skill("tiezhang-xinfa", 200);

        map_skill("force", "guiyuan-tunafa");
        map_skill("dodge", "shuishangpiao");
        map_skill("strike", "tiezhang-zhangfa");
        map_skill("parry", "tiezhang-zhangfa");
        map_skill("blade", "liuye-daofa");
        prepare_skill("strike", "tiezhang-zhangfa");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "strike.tiezhang" :),
                (: perform_action, "strike.tianlei" :),
                (: perform_action, "strike.lianhuan" :),
                (: perform_action, "strike.heyi" :)
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
			           //"ˮ��Ư����" : (: ask_piao :),
			           "���ƾ���" : (: ask_tiezhang :),
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

        if ((int)ob->query("shen") >= -50000) {
                command("hehe");
                command("say ����ǧ��ɲ����Ĵ����������ͽ�ܡ�");
                return;
        }
        if(fam["master_name"] == "�Ϲٽ���"){
                command("ah");
                command("grin" + ob->query("id"));
                command("say �Ϲٰ����������ѹ����������");
                command("say "+RANK_D->query_respect(ob)+"ԭ�����ϰ������ŵ��Ӱ���ʧ����"+RANK_D->query_self(me)+"����������Ϊͽ��");
                return;
        }
        if ((int)ob->query_skill("guiyuan-tunafa", 1) < 120) {
                command("say Ҫѧ��Ϊ������书�������и�����ڹ���Ϊ��");
                command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ���ڹ�Ԫ���ɷ��϶��µ㹦��");
                return;
        }
        if ((int)ob->query_str() < 28) {
                command("say ��ѧ�ҵ������Ʒ�������Ҫ���㹻��������");
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
        ob->set("title", HIY"���ư��ʮ�Ĵ���������"NOR);
        ob->set("class","brigand");
}

int ask_qiubai()
{
        say("������ʦ��������ʮ�����������ȹ�����֮�����ж�ͼ����\n"
            "��ȫ���书�������ܡ���ϧʮ��ǰ�����ں�������Χ������������\n");
        return 1;
}

int ask_tiezhang()
{
	object me= this_player();
	if (me->query("family/family_name")!="���ư�") {
		command("say ���ƾ����������ưﲻ��֮�գ���һ�����ɵ�������������");
		return 1;
	}

   if( me->query("tiezhang/pass"))
   {   
	  command("say ������С���Ѿ���ȫ���������ƾ�����Ҫּ�����ˡ�");
      command("angry ");
      return 1;
   }

	if( me->query("combat_exp",1)<5000000)
   {   
	  command("say ��ľ���ֵ̫�ͣ�����ϰ�ú��������ƾ�����");
      command("sigh "+me->query("id"));
      return 1;
   }
   if( me->query("tiezhang-zhangfa",1)<350)
   {   
	  command("say ��������Ʒ�̫�ͣ�����ϰ�ú��������ƾ�����");
      command("sigh "+me->query("id"));
      return 1;
   }
    if( time()-me->query("tiezhang/time")<86400)		
   		{
				command("say С�ѻ���ȥ��Ϣһ�°ɡ�");
			    return 1;
		}

	command("say �����Ʒ������������������Ͻл��ӵĽ���ʮ���Ʋ������ʽ�ϸ��Ǿ�����ס�");
    command("say �����ƹ�����ͬѰ�������ư￪ɽ�����������������ԭ�����ľ��������Ʒ��������Ϲٽ�������������໯���˲��پ�΢������");
    command("say ��Ȼ����������ư����Ĺ������ұ㽫�����ƾ������ڸ��㣬�㵱������ϰ����Ҫ��������������˺���������");
	command("say ����ϸ�ˣ�");


    message_vision(HIR"��ǧ����������ǰ���������Ƹ����ĳ��������仺����ȴͬʱϮ��������ǿ����ɽ������ѹ�˹�����\n"
	+"������˺��ӱܣ�ȴ���ﻹ���ü���$N�ϰ��������Ѩȴ��ȫ����������֮�£�\n"NOR+
                        HIG"��ǧ������δ�꣬�������������������ĳ������ȴ������$NС������֫\n"+
                        HIM"$NһƳ֮����ѿ�����$n������һץ��Ȼ���ͣ���Զ����������ôһ��������������,�����������������ɱ�С� \n"NOR, me);
    command("smile ");
    command("say ��ɿ������ˣ�");
    //me->delete_temp("xtg1");
       tell_object(me,HIY"\n�㿪ʼ����Ļ�����ǧ���һ��һʽ����\n"NOR);
       me->start_busy(999);
	   me->set_temp("tzjueji/ask",10);
       remove_call_out("thinking");
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
      j = 25;
      if(me->query("m-card-vip")) j =  20;
      if(me->query("y-card-vip")) j =  17;
      if(me->query("buyvip"))     j =  15;
      i=random(j-7);

     if (i == 3 
		// && random(total) >= 80 
		 && random(me->query("kar"))>=27  )
     {
       
          tell_object(me,HIM"\n�����ۻ�������������������һ��һ�����þ�����������ת���ݣ�\n"NOR);
          message_vision(HIC"\n$N�����ʹ�������Ʒ��ƺ���Щ�˽��ˡ���\n"NOR,me); 
		  message_vision(HIC"\n$N�����ʹ��ˮ��Ư�Ṧ�����ƺ���Щ�˽��ˡ���\n"NOR,me); 
          tell_object(me,HIR"������ʹ�����ƾ����ڻ��ͨ��\n"NOR);
		  command("chat* laugh ");
          command("chat ������ˮ��Ư�������������Ĵ����ˣ������޺��� ");
		  message_vision(HIW"\n$nһʱ���ˣ������ȷ�ǿ���֮�ģ����ǽ��Լ����Ṧ������ˮ��Ư���İ���һ���Զ����ڸ�$N����\n"NOR,me); 
          me->set("tiezhang/pass",1);
		  me->set("tz/piao",1);
          me->set("title",HIR"����"+HIW"ˮ��Ư"NOR);
          log_file("quest/tiezhang", sprintf("%s(%s) ʧ��%d�κ󣬳ɹ��⿪���ƾ�������Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query("tiezhang/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->start_busy(1);
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
        }

     }

}
