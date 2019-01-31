// NPC: /d/huashan/npc/ningzhongze.c
// Date: Look 99/03/25
// Lklv Modify at 2001.10.18
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_jianzong();
string ask_wushuang();
int do_qingjiao();
void create()
{
        set_name("������",({"ning zhongze","ning"}));
        set("title","��ɽ�ɵ�ʮ�������ŷ���");
		set("nickname",HIC"��˫�޶ԣ�����һ��"NOR);
        set("long", "���Ǹ�������ü��Ů�к��ܣ���ɽ�ɾ��ӽ�����Ⱥ�ķ��ˡ�\n");
        set("gender", "Ů��");
        set("age", 40);
        set("attitude", "friendly");
        set("per", 28);
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

        set("max_qi",3000);
        set("max_jing", 2000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("eff_jingli", 2000);
        set("jiali", 50);
        set("combat_exp", 4500000);
        set("score", 9000);
        set("quest/hsjf/wushuang","pass");
       
        set_skill("cuff",   350);

		set_skill("strike",   350);
        set_skill("hunyuan-zhang",   350);

		set_skill("sword",  380);
        set_skill("dodge",  350);
        set_skill("force",  400);
        set_skill("parry",  350);
        set_skill("literate",200);
        set_skill("poyu-quan", 350);
        set_skill("huashan-qigong", 400);
        set_skill("huashan-jianfa", 380);
        set_skill("huashan-shenfa", 350);
        set_skill("zhengqi-jue", 200);
		set_skill("ziyin-yin", 200);
        map_skill("force", "huashan-qigong");
        map_skill("dodge", "huashan-shenfa");
 
	    map_skill("strike", "hunyuan-zhang");

		map_skill("sword","huashan-jianfa");
        map_skill("parry","huashan-jianfa");
	    map_skill("cuff","poyu-quan");

	    prepare_skill("strike", "huanyuan-zhang");

        set("chat_chance_combat",60);
        set("chat_msg_combat", ({
		    (: perform_action, "sword.jianzhang" :),
			(: perform_action, "sword.wushuang" :),
			(: exert_function, "yujianshi" :),
	    }));
		set("inquiry", ([
		
		 "��˫�޶�����һ��"	: (: ask_wushuang :),
         //"����֮��"      : (: ask_qizong :),
         "��ɽ����"      : (: ask_jianzong :),
	    ]));

	    create_family("��ɽ��",13,"����");

        setup();

	carry_object(BINGQI_D("sword"))->wield();
	carry_object(ARMOR_D("cloth"))->wear();
}
void init()
{
   ::init();
   add_action("do_qingjiao", "qingjiao");
}
void attempt_apprentice(object ob)
{
        mapping fam;
        if ( mapp(fam=ob->query("family"))
         && (string)fam["family_name"] != "��ɽ��"
         && (int)ob->query("is/huashan")==1 ) {
		message_vision("$N���������ɽ�ɵ���ͽ��������ʲô ��\n", ob );
		command("slap "+ob->query("id"));
		return;
        }
	if ( ob->query("fengset")) {
		command("say �㲻���Ѿ����˽��ڵ�ǰ��Ϊʦ��ô��");
		return;
	}
		        if(ob->query("quest/huashan")=="����"){
                command("heng");
                command("say �ߺߣ����ڵ��������뿪��ɽ�������ǻ�ɽ�ɵ��ӣ�����������ѵ���������������֮λ��");
                return;
        }
        if( (string)ob->query("gender") != "Ů��" ) {
                command ("say �Բ�����ֻ��Ů���ӡ�");
                return;
        }
		if ( ob->query_skill("huashan-qigong",1) <300 ){
		command("say ��ֻ��Ůͽ��" + RANK_D->query_respect(ob) + "��Ļ�ɽ��������300��������ذɡ�");
		return;
	}
        if ((int)ob->query("shen") < 1000000) {
		command("say �һ�ɽ�����������������ɣ��Ե���Ҫ����,����1m��");
		command("say �ڵ��з��棬" + RANK_D->query_respect(ob) + "�Ƿ����ò�����");
		return;
        }
        command("say �ף������СŮ����Ҿ��������ˡ�");
        command("recruit " + ob->query("id"));
	    ob->set("title","��ɽ�������״�����");
        ob->set("quest/huashan","����");
        return;
}


string ask_jianzong()
{
   object me=this_player();
   if (me->query("family/family_name")!="��ɽ��" )
     return "�㲻�ǻ�ɽ���ӣ�������������⣬��Ҫ��Ϊ��\n";
   if (me->query("quest/huashan")=="����" )
     return "���Ѿ��ǽ��ڵ��ӣ����ѱ���������ɽ�����˺�Ϊ��\n";
   if (me->query_skill("huashan-jianfa",1)<100)
     return "�㻹�Ǻú���ϰ�似�ɣ��������С��֪����ô��Ҳ���á���\n";
   command("sigh "+me->query("id"));
   command("say �������ں����ڱ���һ�ң�������Ϊ�������ͣ����±����ڽ���֮�֣��������黹��ȥ����ʦ��ȥ�ɡ�\n");
   me->set_temp("jianzong/askning",1);
   return "������·�������ʲô���£����ϴ��м��侪�������.\n";

}

string ask_wushuang()
{
   
    object me=this_player();
  
   //if (!arg || arg!="��˫�޶�����һ��")
   //  return notify_fail("�Ҵ�����������Ľ������Ȼ���ǲ�ס���㵽��Ҫ��ʲô��\n");
   if (me->query("family/family_name")!="��ɽ��" )
      return "�㲻�ǻ�ɽ���ӣ�������������⣬��Ҫ��Ϊ��\n";
   if (me->query("quest/huashan")=="����" )
      return "���Ѿ��ǽ��ڵ��ӣ����ѱ���������ɽ�����˺�Ϊ��\n";
   if (me->query_skill("huashan-jianfa",1)<300)
      return "�㻹�Ǻú���ϰ�似�ɣ��������С��֪����ô��Ҳ���á���\n";
   if (me->query("hsjj/wushuang")=="pass")
      return "���Ѿ�ϰ����˫�޶�����һ������������ʲô��\n";
   if (time()-me->query("hs/wushuang/time")<86400)
      return "��Ľ���ʱ�䲻�㣬����̫�ڿ�Щ�ˣ�\n";
   
   if (!present("yue buqun",environment(me)))
   {
	   
       me->delete_temp("wushuang/askning1");
	   me->set_temp("wushuang/askning2",1);
       return "������˵������ ��˫�޶��������Լ����ݻ�ɽ��������һ�Ž�������,��������ѧϰ�������������(qingjiao)����\n";
	  
   }else {
      
	   me->set_temp("wushuang/askning1",1);
	   return "������˵�����������˶����ӣ����м�ϸ����Ȼ����ѧ���͵������䳡���ң���һ��͵�����\n";
   }

}

int do_qingjiao()
{
      int i,j;
      object me, ob, weapon, weapon1;

	  me = this_player();
	  ob = this_object();
      weapon=me->query_temp("weapon");
	  weapon1 = ob->query_temp("weapon");
      if (!me->query_temp("wushuang/askning2"))
        return notify_fail("��Ҫ���ʲô��\n");
      if (!weapon||weapon->query("skill_type")!="sword")
         return notify_fail("���Ǵ��ģ��㲻�ý��������ʦ����У�\n");
	  if (!weapon1)
         return notify_fail("��ʦ�������޽���ʩչ���˻�ɽ������˫�޶ԣ�\n");
	  if (me->query_skill_mapped("sword")!="huashan-jianfa"||me->query_skill_mapped("parry")!="huashan-jianfa")
	     return notify_fail("��û�м�����ɽ��������������������˵ľ�����\n");
     
	  message_vision(HIG"$N����$n˵��������ʦ��ָ�㡾��˫�޶ԣ�����һ������������\n"NOR, me,ob);
	  ob->add_temp("apply/damage",-100);
	  ob->set("jiali",1);
	  COMBAT_D->do_attack(ob, me, weapon, 1);
		
	 
	  message_vision(HIC"\n\n$n�����������һ��Ů��������γ�һ����������$N˵������ʹ�콣����$N�������ǣ����͵�һ��\n"+
	                 "�����ƹ���$n�����ӣ�������$n��������ת����$n�����ݳ����������$N�Ӻ�������һ��������\n"
                     +"������ȡ$N�ؿڣ�Ҳ�ǿ�����ס������Կ��죬���ǽ�������������һ�е��ܷ���˲Ϣ֮�䣬ʦͽ���Ѳ��˶�ʮ���С�\n"NOR,me,ob);
      COMBAT_D->do_attack(ob, me, weapon, 1);
	  COMBAT_D->do_attack(ob, me, weapon, 1);
	  //COMBAT_D->do_attack(ob, me, weapon, 1);
	  COMBAT_D->do_attack(ob, me, weapon, 1);	 
	 message_vision(HIY"\n\nȴ������Խ��Խ�죬$N���ú���������Ͼ��˵�κλ��ÿ���$Nһ����ס��ֻ��ҡͷʾ��\n"
                        +"$n����ʹ���˷���ͻȻ��һ����Х��������˸������Χ��$N��Χ���̣�������裬���˿�����\n"
						+"�����ˡ��͵�����һ��ͦ����ֱ��$N�Ŀڣ������ǽ������磬�������ס�$N���һ�����е�����ʦ�\n"
						+"��ʱ���������Ѵ���$N������$n������ǰ���ͣ���������������$N�����ţ��ۼ���һ������$N����\n"
						+"�Դ�������ֱû������ֻ���ö�������֮��������һƬƬ�������ĶϽ�����$N�Ľűߡ�$n����һЦ��\n"
						+"����������ֻ��$n���еĳ�����ֻʣ��һ��������\n"NOR,me,ob);
   	  COMBAT_D->do_attack(ob, me, weapon, 1);
	  COMBAT_D->do_attack(ob, me, weapon, 1);	 
	i=random(10);
	j=random(me->query("kar"));
	if (me->query("kar")<31
		&&j>=25
		&&i>5	)
	{
       message_vision(HIG"\n\n$N���һ������Ȼ����������˫�޶�����һ���İ��أ�������ϲ����\n"NOR,me);
	   command("smile "+me->query("id"));
	   command("say ���Ĳ���������ô��ʱ����������о���������������ǲ�����\n");
	   command("chat ��ϲ"+me->query("name")+"�⿪��˫�޶�����һ����\n");
	   command("chat* congra "+me->query("id"));	 
	   command("chat* pat "+me->query("id"));
	   log_file("quest/wushuang",sprintf("%s(%s)���ڽ⿪��˫�޶�����һ����������������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),j,i,me->query("hs/wushuang/fail"),me->query("combat_exp"),me));
	   me->set("hsjj/wushuang","pass");	  
	   destruct(ob);
	   me->delete_temp("wushuang/askning2");
	   return 1;
	}
	else
	{
		message_vision(HIY"\n\n$N��Ȼ����һ����˫�޶ԣ�����һ��������δ����������о�����\n"NOR,me);
		log_file("quest/wushaung",sprintf("%8s%-10s������˫�޶�����һ��ʧ�ܣ�����Ŭ������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),j,i,me->query("xlz/slbw/fail"),me->query("combat_exp"),me));
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("hs/wushuang/fail",1);
		me->set("hs/wushuang/time",time());
		me->delete_temp("wushuang/askning2");
	    destruct(ob);
        return 1; 
	}   
   return 1;

}
int prevent_learn(object ob, string skill)
{
	
	if (skill=="ziyin-yin"||skill=="zhengqi-jue")
	{
		write("���ֹ���ֻ�ܿ����˴����в������ã����ʦ�������ѧ��ʲô?\n");
		return 1;
	}
	return 0;
}