// NPC: /d/huashan/npc/mu_renqing.c
// Date: Look 99/03/25
// Modify by Lklv 2001.10.18
#define QUESTDIR "quest/��ɽ��/ӥ��������/"

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_quest1();
string ask_quest2();
string ask_miji();
int do_jiejian();

void create()
{
        set_name("������",({"mu renqing", "mu", "renqing"}));
        set("nickname","����ԯ");
        set("long", "������ڽ���������Զ����������𣬻�ɽ������ԯ�����塣\n");
        set("age", 70);
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("per", 26);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 29000);
        set("max_jing", 7800);
        set("eff_jingli", 7500);
        set("max_neili", 26500);
        set("neili", 26500);
        set("jiali", 200);
        set("combat_exp", 15200000);
        set("score", 29000);
		set("questbusy", 0);

        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
                (: perform_action, "sword.jianzhang" :),
 
			    (: perform_action, "sword.shijiushi" :),
				(: perform_action, "sword.luomu" :), 
				(: perform_action, "sword.fengyi" :),
  
		}));
        set_skill("sword",  500);
        set_skill("dodge",  500);
        set_skill("force",  500);
        set_skill("cuff", 500);
        set_skill("poyu-quan", 500);
        set_skill("huashan-jianfa", 500);
        set_skill("parry",  500);
        set_skill("literate", 230);
        set_skill("huashan-qigong", 500);
		set_skill("strike", 500);

		set_skill("hunyuan-zhang", 500);

		set_skill("huashan-shenfa", 500);
       // set_skill("zhengqi-jue", 200);

        map_skill("dodge", "huashan-shenfa");
        map_skill("force","huashan-qigong");
        map_skill("cuff","poyu-quan");
	    map_skill("strike","hunyuan-zhang");
 
		map_skill("parry","huashan-jianfa");
        map_skill("sword","huashan-jianfa");
        prepare_skill("strike", "hunyuan-zhang");

	    set_temp("apply/damage", 80);
        set_temp("apply/dodge", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/armor", 80);
        create_family("��ɽ��",12,"����");

        set("inquiry", ([
         "ӥ������" : (: ask_quest1 :),
         "ӥ��������" : (: ask_quest2 :),
         "�ؼ�" : (: ask_miji :),
		 "�ؽ�ʽ" : (: do_jiejian() :),
        ]));
        setup();
        carry_object(BINGQI_D("sword"))->wield();
        carry_object(ARMOR_D("cloth"))->wear();
}
void init()
{
     add_action("do_go", "gensui");
     add_action("do_go", "goto");
}


void attempt_apprentice(object ob)
{
        mapping fam;
    if (mapp(fam=ob->query("family")) 
		&& (string)fam["family_name"] != "��ɽ��"  
		&& (int)ob->query("is/huashan")==1
		|| !ob->query("quest/huashan")) {
                message_vision(CYN "$N���������ɽ�ɵ���ͽ��������ʲô ������\n"NOR, ob );
                command("slap "+ob->query("id"));
                return;
        }
	if (ob->query("fengset")) {
		command("say �㲻���Ѿ����˷����������˼�Ϊʦ��ô��");
		return;
	}
	if(ob->query("quest/huashan")=="����"){
                command("heng");
                command("say �ߺߣ����ڵ��������뿪��ɽ�������ǻ�ɽ�ɵ��ӣ�����������ѵ���������������֮λ��");
                return;
        }
	if (ob->query_skill("huashan-qigong",1) < 350 ) {
		command("say ��Ļ�ɽ������Ϊ̫�ץ�������ɡ�");
		return;
	}
    if ((int)ob->query("shen") <= 2000000) {
	        command("say �һ�ɽ�����������������ɣ��Ե���Ҫ����2m��");
	        command("say �ڵ��з��棬" + RANK_D->query_respect(ob)+"�Ƿ����ò�����");
	        return;
        }
    if ((int)ob->query("max_pot") < 450) {
	        command("say " + RANK_D->query_respect(ob)+"���ڲ���Ҫ����ָ������ȥ��������ʦ��ѧ��ȥ�ɡ�");
	        return;
        }
        command("say �ðɣ��Ҿ���������,���ҪΪ���ǻ�ɽ��������������");
        command("recruit " + ob->query("id"));
        ob->set("title","��ɽ�������״�����");
        ob->set("quest/huashan","����");
		return;
}

string ask_quest1()
{
        mapping fam;
        object me;
        int exp, exp2, i;
        me = this_player();
        exp = (int)me->query("combat_exp", 1);
        exp2 = (int)me->query(QUESTDIR+"combat_exp", 1);
        i = (int)me->query("job_time/��ɽ",1);
        fam = me->query("family");
        
        if (!fam || fam["family_name"] !="��ɽ��")
                return RANK_D->query_respect(me)+"�뱾��������������֪�˻��Ӻ�̸��\n";

      if (!me->query(QUESTDIR+"������/over"))
        return "�һ�ɽ����λǰ���ۿ�ӥ������������һ��ӥ���������ľ�ѧ��\n";

        if(me->query_temp(QUESTDIR+"start2"))
                return "�Ҳ����Ѿ�����˵������\n";

        if( i < 2000 )
                return "��Ϊ�һ�ɽ�������Ĺ���΢�������ܸ�������Ȼ���Ҫ�£�\n";
         //��ɽ�����������1000�� by daidai

        if(exp2 && exp-exp2 < 200000)
                return "�㵱ǰ�ľ�����»���������������������ץ��ȥ����ȥ�ɡ�\n";
         //������200k by daidai

        if(me->query(QUESTDIR+"time") && time()-me->query(QUESTDIR+"time")<86400)
                return "����͵�����ɣ������������ɡ�\n";
        
        if(me->query(QUESTDIR+"pass"))
                return "�㲻���Ѿ�������\n";

        if(me->query(QUESTDIR+"fail")>=3 && me->query("registered")<3)
                return "���Ѿ����㽲������ˣ�����Ͳ����Ҵ�Ϊ�μ�����˲��\n";
        me->set_temp(QUESTDIR+"start2", 1);
        me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
        me->set(QUESTDIR+"time",time());
         message_vision(CYN"\n�������������һλ���ˣ�\n"NOR, me);
        return "�������ֺ����ɽ���ﳣ��ӥ�߳�û���һ�ɽ����ʮ��·ӥ������������ǰ������������ۿ�ӥ���භ�иж�����
��������Ȥ�������˴���ȥ��(gensui)��˵���������ջ��أ�\n";
}

string ask_quest2()
{
        mapping fam;
        object me;
        me = this_player();
        fam = me->query("family");

        if (!fam || fam["family_name"] !="��ɽ��")
                return RANK_D->query_respect(me)+"�뱾��������������֪�˻��Ӻ�̸��\n";

        if(!me->query(QUESTDIR+"over"))
          return "�����һ�ɽ�ɵľ�ѧ���ԴӵھŴ�����ɥ���ڹ�����֮���ʧ���ˣ�ֻ����һ�������ܲ�͸���ؼ��б���\n";
 
        tell_object(me,HIC"\n�㽫�ղ������Լ��Լ��ĸ���һһ�����������塣\n"NOR);
        me->set(QUESTDIR+"pass",1);
        me->delete(QUESTDIR+"over");
        return "��Ȼ��ˣ��������б�ӥ�����������ؼ��б���Ҳ�����ܴ���ѧ���㶫����\n";
}
string ask_miji()
{
        mapping fam;
        object me,book;
	int exp, exp2;
        me = this_player();
        fam = me->query("family");

        if (!fam || fam["family_name"] !="��ɽ��")
                return RANK_D->query_respect(me)+"�뱾��������������֪�˻��Ӻ�̸��\n";

       if(me->query_temp(QUESTDIR+"������/over"))
                return "���Ѿ��õ��ؼ��ˣ���������ң�\n";

      if(!me->query(QUESTDIR+"������/over")){
                exp = (int)me->query("combat_exp", 1);
                exp2 = (int)me->query(QUESTDIR+"combat_exp", 1);

      if(exp2 && exp-exp2 < 200000)
                return "�㵱ǰ�ľ�����»���������������������ץ��ȥ����ȥ�ɡ�\n";
         //������200k by daidai

        if(me->query(QUESTDIR+"time") && time()-me->query(QUESTDIR+"time")<86400)
                return "����͵�����ɣ������������ɡ�\n";

        if(me->query_temp(QUESTDIR+"start"))
                return "�Ҳ����Ѿ�����˵�������㻹��ȥ��������ͽ����\n";

          me->set_temp(QUESTDIR+"start", 1);
                return "�ؼ��б��ҽ�����ͽ���������ˣ����ں���һ������ȥ����ȡ���ؼ��ɡ�\n";
          
           }
       if(!me->query(QUESTDIR+"pass"))
          return "�ؼ���ʲô�ؼ���������ֻ��һ����ѧ��ƪ����ɿ�����Ŷ��\n";

        book = unew("/d/huashan/npc/obj/yingshe-book.c"); 
        if(!clonep(book)) return "�������ˣ�ӥ�����������ؼ��б��ѱ������������������ˡ�";
         
        if(clonep(book) && book->violate_unique()){
               destruct(book);
               return "�������ˣ�ӥ�����������ؼ��б��ѱ������������������ˡ�";
        }
        book->move(this_player());
        return "�������б���ӥ���������ؼ��б��������û�ȥ�ú����У�������ֱ��ɾ�ѧ��";
}

int do_go(string arg)
 {
      object me;
      me = this_player();
      if(!living(me) ) return 0;
      if(! me->query_temp(QUESTDIR+"start2")) return 0;        
      if (me->is_busy() || me->is_fighting())
        return notify_fail("����æ���ģ�\n");
      if( !arg || arg != "puren")
        return notify_fail("��Ҫ��˭�߰���\n"); 

         message_vision(CYN"\n����˵�������������ɣ�����Ȼ��������ȥ��$N��æ���ϣ�\n"NOR, me);
          me->move("/d/huashan/ys_houshan");     
        return 1;
}


int accept_object(object who, object ob,object me)
{
        me= this_object();

        if( ob->query("id") != "muxia"){
                command("say ������ⶫ������");
                return 0;
        }
        if( ob->query("owner") != who->query("id")
         || !who->query_temp(QUESTDIR+"������/over")){
                command("haha");
                command("say ��л"+RANK_D->query_respect(who) + "�������ؼ��һأ�̫��л�ˡ�");
                who->delete_temp("limochou");
                call_out("dest", 1, ob);
                return 1;
        }
        command("say ̫���ˣ������ڰ��Ȿ�ؼ��б�ȡ�����ˡ�");

            command("say ����������������ɽ��ӥ��֮������֪��.......");
        who->set(QUESTDIR+"������/over", 1);
        who->delete_temp(QUESTDIR+"������/over");
        call_out("dest", 1 ,ob);
        return 1;
}

void dest(object obj)
{
        if(! obj) return;
        destruct(obj);
}


int do_jiejian() 
{
	object me = this_player();
	
	
	if (this_object()->query("questbusy")) 
	{
		command("say ��æ���أ�\n");
		return 0;
	}
	if(this_object()->is_fighting()) return 0;
	if(me->query("family/family_name")!="��ɽ��")
	{
		command("heng "+me->query_id());
		command("say �����������ʲô��ϵ���Ͻ����ҹ���");
		return 1;
	}
	if(me->query("shen")<0)
	{
		command("heng "+me->query_id());
		command("say ��ɽ���������ɣ��Ͻ����ҹ���");
		return 1;
	}
	if(me->query("quest/hs/hsjf/jiejian/pass"))
	{
		command("heng "+me->query_id());
		command("say ���Ѿ�����ɽ�����ؽ�ʽ�ڻ��ͨ������ǲ��ô��");
		return 1;
	}
	if(me->query("quest/hs/hsjf/jiejian/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say �Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		command("puke "+me->query("id"));
		return 1;
	}
	
	if (me->query_skill("huashan-jianfa",1)<300)
	{
	   command("say ��ɽ������������300��˵������Ҳ�ǰ״\n");
	   return 1;
	}
	message_vision(HIC"$N��$n����йػ�ɽ�����ؽ�ʽ�������ռ����\n"NOR, me, this_object());
	
	command("look "+me->query("id"));	
	
	if( time()-me->query("quest/hs/hsjf/jiejian/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say �����Ƚ̵�����ɣ�����ɡ�");
		return 1;
	}
	
    
	me->set("quest/hs/hsjf/jiejian/time",time());
	me->set("quest/hs/hsjf/jiejian/combat_exp",me->query("combat_exp")); 
	
	command("sigh "+me->query("id"));
	command("think ");
	command("consider ");
	
	command("say ��ɽ�������ϴ�����ʧ̫�࣬����������ڷܵķ��Ͼͽ���������Ļ�ɽ��������˵����������������û����������ˡ�");
    command("say ͽ���������о�������Ϊʦ������Ѫ���ã���Ҫ�ú������ˡ�\n");
	command("whisper "+me->query("id"));
	
	command("smile "+me->query("id"));
	this_object()->set("questbusy",1);
	me->start_busy(999);
	remove_call_out("think_hsjf");
	call_out("think_hsjf",1,me);
	return 1;
}

int think_hsjf(object me)
{
	//object me=this_player();
    int i;
	i=random(10);
	if(me->query_temp("canwu_hsjf")<(10+random(5)))
    {  
	  me->add_temp("canwu_hsjf",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n����ϸ����ʦ���Ľ�������ʦ�������ڵ���ʽ�˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
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

	  //remove_call_out("think_ssjf");
	  call_out("think_hsjf",3+random(3), me);
	  return 1;

   } 
	else if( i>=8 && random(me->query("kar"))>=28)
	{
		tell_object(me,HIC"\n�㰴�������峤�ϵ�ָ�㣬����Լ���ϰ���ã��Ի�ɽ�����ؽ�ʽ�İ����ƺ���Щ�ĵá�\n"NOR);
		tell_object(me,HIC"\n��������������ڵ���ʽ��ͷ��ʼ������һ·�����������������硣Խ��Խ�Ǵ��졣\n"NOR);
        tell_object(me,HIC"\n��Ȼ�䣬�����һ������ǰ�������Ҳ�벻���׵������Ȼ���Ȼ��ͨ���̲�ס������Ц.\n"NOR);		
		
		command("look "+me->query("id"));
		command("chat*haha "+me->query("id"));
        command("chat*pat "+me->query("id"));
		command("chat "+"��������������Ȼ����Ԥ��Ľ�����˵㣬�����������߽ؽ�ʽ�����ƽʱ�������Ƚ����࣡");

		
		me->set("quest/hs/hsjf/jiejian/pass",1);
		//me->set("title",HIC"��ɽ��"+HIY"��ɽ��������"NOR);
		me->set("quest/hs/hsjf/jiejian/time",time());
		log_file("quest/hsjfjiejian", sprintf("�ɹ���%8s(%8s) ʧ��%d�κ󣬳�������ɽ�����ؽ�ʽ�ľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/hs/hsjf/jiejian/fail"),i,me->query("combat_exp")) );
		me->delete_temp("canwu_hsjf");
		this_object()->set("questbusy",0);
		//me->delete_temp("hssb");

	}
	else
	{
		command("heng "+me->query("id"));
		command("say �ҿ��������ģ��Ҿ�û��������ŵġ�");
		command("say �������ǵ���Ԭ��־���̶̼���ʱ���ھ���������У����Ȼ��ûѧ�ᣬ��������!\n");
		command("angry "+me->query("id"));
		tell_object(me,HIY"�������������ָ�㣬��Ȼ�����˻�ɽ�����ؽ�ʽ��������ʽ�����ǶԻ�ɽ�����ؽ�ʽ����������ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/hsjfjiejian", sprintf("ʧ�ܣ�%8s(%8s) ��ɽ�����ؽ�ʽ����ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/hs/hsjf/jiejian/fail"),i,me->query("combat_exp")) );
		me->set("quest/hs/hsjf/jiejian/time",time());
		me->add("quest/hs/hsjf/jiejian/fail",1);
		me->delete_temp("canwu_hsjf");
		this_object()->set("questbusy",0);
		//me->delete_temp("hssb");
	}
	me->start_busy(1);
	return 1;

}