// jiumozhi.c �Ħ��
// by iceland
// Modified by Lklv 2001.10.23
// Modified by tangfeng 2004
// mod by sohu 2014
inherit F_MASTER;
#include <ansi.h>
inherit NPC;
#include "jiumozhi.h"

#define QUESTDIR2 "quest/�����˲�/����Ӫ��ƪ/"

string askduanyu();
string ask_hyd();
string ask_lx();
string ask_jueji();
string hyd_jueji();
string ask_jianpin();
string ask_rmdf();
string ask_jiasha();

//int start_condition(object ob);
int power_condition(object me,object ob,int p);

void create()
{
        set_name("�Ħ��", ({ "jiumo zhi", "jiumozhi","zhi" }));
        set("long",@LONG
������ȳƣ�������ɷ���������б������������������鱦����Ȼ���ԣ�
ֻ���������ü��ۣ����������׽�֮�⡣
LONG
        );
        set("title", HIY "����������" NOR);
        set("gender", "����");
		set("nickname","��������");
        set("class", "mizong");
        set("age", 55);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 45);
        set("int", 40);
        set("con", 30);
        set("dex", 30);
        set("per", 25);
        set("max_qi", 36500);
        set("eff_jingli", 7500);
        set("max_jing", 6000);
        set("neili", 34000);
        set("max_neili", 34000);
        set("jiali", 250);
        set("combat_exp", 15000000);
        set("score", 290000);
        set("unique", 1);
        set("lx/gree",12);
		set("quest/dls/longxiang/pass",13);
		set("quest/dls/hyd/pass",1);
		set("mishikey",1);

        set_skill("mizong-fofa", 200);
        set_skill("literate", 300);
        set_skill("force", 500);
        set_skill("longxiang-boruo", 500);
        set_skill("dodge", 500);
	    set_skill("poison", 100);
        set_skill("yuxue-dunxing", 500);
		set_skill("hand", 500);
		set_skill("dashou-yin", 500);
        set_skill("strike", 550);
        set_skill("huoyan-dao", 550);
        set_skill("parry", 500 );
        set_skill("staff",500);
        set_skill("wushang-dali",500);

        map_skill("force", "longxiang-boruo");
        map_skill("dodge", "yuxue-dunxing");
        map_skill("strike", "huoyan-dao");
        map_skill("staff","wushang-dali");
        map_skill("parry", "huoyan-dao");
        map_skill("hand", "dashou-yin");

        prepare_skill("strike","huoyan-dao");
        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
                (: exert_function, "shield" :),
				(: exert_function, "longxiang" :),
				(: perform_action, "strike.daoqi" :),
				(: perform_action, "strike.fen" :),
				(: perform_action, "strike.ran" :),
				(: perform_action, "strike.biyan" :),
                (: perform_action, "strike.honglian" :), }));

        create_family("������", 10, "����");
        set("class", "huanxi");
        set("chat_chance", 2);
        set("chat_msg", ({
			"�Ħ�ǵ�ͷ��˼��˵������ɽ�����£����������£��ߣ���ѩɽ�������ĵ�Ȳ��ϣ���\n",
			"�Ħ��˵�������浶�����µ�һ�似�����л������ս�ɱ�������£������������������֣�\n",
			"�Ħ�ǽ�˫�ƾٵ���ǰ�����ƣ���Ц��һ�����������м������ҵĵ��֣���\n",
		}) );
		set("inquiry",([
					"����" : (: askduanyu :),
					"�����¾���" : (: ask_jueji :),
					"�����������Ʒ" : (: ask_jianpin :),
					"ȼľ��������" : (: ask_rmdf :),
					"�����ݺ����" : (: hyd_jueji :),
					"ʮ����������" : (: ask_jiasha :),

					"������" : "������Ǵ����¡�",
					"������" : "�������Ǵ���μ���ѧ�����֮�أ���˵�������񽣾������С�",
					"Ӫ�ȶ���" : (: askduanyu :),
					"Ľ�ݸ�" : "�����˳���Ľ�ݡ������壬��˵Ľ�ݹ����꼶���ᣬȴ����������",
					"Ľ�ݲ�" : "���˹���Ľ�ݲ����Ľܲţ���ϧӢ�����š�",
					"������" : "��˵������������߾�ѧ����һ��Ҫ��취�����ü���",
		]));
	    add_temp("apply/armor", 60);
        add_temp("apply/damage", 50);
        add_temp("apply/attack", 160);
        add_temp("apply/dodge", 50);
        setup();
        carry_object("/d/xueshan/npc/obj/longxiang-jiasha")->wear();
        add_money("gold",1);
}
string ask_jianpin()
{

	object me;
	int i;
	me=this_player();
	i = (int)me->query_skill("longxiang-boruo", 1);   
    if (me->query("quest/dls/longxiang/pass")==11)
    {
		 tell_object(me,HIW"���������ʮ������������������"HIR+me->query("lx/gree")+HIW"�㡣\n");
	     me->set("lx/gree",11);
		 return "�ۣ����Ȼ�⿪����������11���ˣ���ϲ���ˣ�\n";
    }
	if (me->query("quest/dls/longxiang/pass")==12)
    {
		 tell_object(me,HIW"���������ʮ������������������"HIR+me->query("lx/gree")+HIW"�㡣\n");
	     me->set("lx/gree",12);
		 return "�ۣ����Ȼ�⿪����������12���ˣ���ϲ���ˣ�\n";
    }
	if (me->query("quest/dls/longxiang/pass")==13)
    {
		 tell_object(me,HIW"���������ʮ������������������"HIR+me->query("lx/gree")+HIW"�㡣\n");
	     me->set("lx/gree",13);
		 return "�ۣ����Ȼ�⿪����������13���ˣ���ϲ���ˣ�\n";
    }
	if (me->query("lx/gree")>10)
	{
		 tell_object(me,HIW"���������ʮ������������������"HIR+me->query("lx/gree")+HIW"�㡣\n");
	     me->set("lx/gree",1);
		 return "��ϲ���ˣ�\n";
	}
	if (i < 100)
	{
		 tell_object(me,HIW"���������ʮ������Ÿո��𲽡�\n");
	     me->set("lx/gree",1);
		 
	}
	else if (i < 150)
	{
		//150
		 tell_object(me,HIW"���������ʮ�������Ѿ��������˵�һ���ˡ�\n");
	     me->set("lx/gree",1);
	}
	else if (i < 200)
	{
		//200
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵ڶ����ˡ�\n");
        me->set("lx/gree",2);
	}
	else if (i < 250) 
	{
		//250
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵������ˡ�\n");
	    me->set("lx/gree",3);
	}
	else if (i < 300)
	{
		//300
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵��Ĳ��ˡ�\n");
	    me->set("lx/gree",4);
	}
	else if (i < 350)
    {
		//350
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵�����ˡ�\n");
	     me->set("lx/gree",5);
	}
	else if (i < 400)
	{
		//400
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵������ˡ�\n");
	    me->set("lx/gree",6);
	}
	else if (i < 450)
	{
		//450
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵��߲��ˡ�\n");
	    me->set("lx/gree",7);
	}
	else if (i < 500)
    {
		//500
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵ڰ˲��ˡ�\n");
	     me->set("lx/gree",8);
	}
	else if (i < 550)
	{
		//550
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵ھŲ��ˡ�\n");
	    me->set("lx/gree",9);
	}
	else if (i >= 550 )
	{
		tell_object(me,HIW"���������ʮ�������Ѿ��������˵�ʮ���ˣ��Ѿ��߱���ʮ��ʮ��Ĵ�����\n"
					+"�Ժ������Ϳ����������������,�Ǵ󳹴����������Դﵽ��Ⱦ���ġ�\n\n");
	    me->set("lx/gree",10);
	}
	return "";

}


string askduanyu()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR2+"start" ))
  {
  	  command("?");
  		return "Сɮ�����ö�������֪���ķ����֡�";
  }
	if (me->query(QUESTDIR2+"start") && !me->query_temp(QUESTDIR2+"jiumozhi")&& !me->query(QUESTDIR2+"over"))
	{
  	  command("shrug "+me->query("id"));
  		return "Сɮ�����ö�������֪���ķ����֡�";
  }
	if (me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"jiumozhi")&& !me->query_temp(QUESTDIR2+"kill_dizi")&& !me->query(QUESTDIR2+"over"))
	{
  	  command("flop "+me->query("id"));
  		return "��֪����֪�����飬���Ǻ��񻹲�Ӧ���ٵ��Ұɣ�ȥ��������¿���ȥ��";
  }
	if (me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"kill_dizi")&& !me->query_temp(QUESTDIR2+"caught")&& !me->query(QUESTDIR2+"over"))
	{
  	  command("flop");
  	  command("kick "+me->query("id"));
  		return "��֪����֪�����飬���Ǻ��񻹲�Ӧ���ٵ��Ұɣ���ȥ�������";
  }
	if (me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"caught") && !me->query_temp(QUESTDIR2+"askzhi")&& !me->query(QUESTDIR2+"over"))
	{
  	  command("sneer "+me->query("id"));
  	  kill_ob(me); 
  	  set("quest/try_fight",1);
  	  set("quest/try_fight_id",me->query("id"));
  	  command("haha "+me->query("id"));	  
  	  power_condition(me,this_object(),200+random(100));  	  
		  return "��������ι��������������Ҫ���߻����õ㱾�³����ɡ�\n";
  }
	if (me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"caught") && me->query_temp(QUESTDIR2+"askzhi")&& !me->query(QUESTDIR2+"over"))
	{
  	  command("sneer "+me->query("id"));
  	  kill_ob(me); 
  	  power_condition(me,this_object(),300+random(100));  	  
		  return "��������ι��������������Ҫ���߻����õ㱾�³����ɡ�\n";
  }
	if (me->query(QUESTDIR2+"over"))
	{
  	  command("sneer "+me->query("id"));
		  return "��������ι������������ﶺ�����죬���������粻�������ˡ�\n";
  }
	return "�������Ǵ���������֮�ӡ�";
}
void attempt_apprentice(object ob)
{
        if( (string)ob->query("gender") == "����" ) {
                command("say ʩ�������ȱ����˵�����ն�����������...\n");
                return;
        }
        if ((string)ob->query("family/family_name") != "������") {
                command("say"+ RANK_D->query_respect(ob) +
                        "���Ǳ��µ��ӣ������ﵷʲô�ң���");
                return;
        }
        if ((int)ob->query_skill("longxiang-boruo", 1) < 350) {
                command("say �Ҵ����¸����书������������ڹ��ศ��ɡ���С�ɱ������ҡ�");
                command("say"+ RANK_D->query_respect(ob) +
                        "�ٰ�����ͨ��������������б��ŵ��ڹ��ɡ�");
                return;
        }
        if (((int)ob->query_con() < 50) || ((int)ob->query_str() < 60)){
                command("hmm");
                command("say ��λ" + RANK_D->query_respect(ob) +
                	"��������60�����ǲ���50�������ƺ����ʺ�ѧϰ�һ��浶�񹦣����Ǿ��������ĳ�·�ɡ�");
                return;
        }
	command("say ������Ǿ��棬ȷʵ������ĺò��ϣ��ðɣ����������úõ��̵�����ɡ�");
	command("recruit " + ob->query("id"));
	ob->set("title",  "�������������µ���");
}

int power_condition(object me,object ob,int p)
{
	int i;
	if(!me || !ob) return 0;
	if(environment(me)!=environment(ob)) return 0;
	//ע�⣬С��15m��Ĭ��ϵͳ���ԣ�����15m����ǿ
 	i=me->query("max_pot");
	/*if(p<150) p=150;
	if(i<p) i=p;
	i=i-100;*/	
	//ob->set_skill("mizong-fofa", i+random(50));
	ob->set_skill("literate", i+random(50));
	ob->set_skill("force", i+random(50));
	ob->set_skill("longxiang-boruo",i+random(50));
	ob->set_skill("dodge", i+random(50));
	ob->set_skill("poison", 200);
	ob->set_skill("yuxue-dunxing", i+random(50));
	ob->set_skill("strike", i+random(50));
	ob->set_skill("huoyan-dao", i+random(50));
	ob->set_skill("parry", i+random(50));
	ob->set_skill("staff",i+random(50));
	ob->set_skill("wushang-dali",i+random(50));
	i=me->query("combat_exp");
	
	ob->set("combat_exp",i+random(1000000));
	i=me->query("neili");	  
	if(i<15000) i=15000;
	ob->set("neili", i);	  
	i=me->query("max_neili");	  
	if(i<8000) i=8000;
	ob->set("max_neili", i);	  
 	i=me->query("max_qi");	  
	ob->set("max_qi", i*2);	  
	ob->set("eff_qi", ob->query("max_qi"));	
	ob->set("qi", ob->query("max_qi"));	
	return 1;
}

void die()
{
	object me,ob=this_object();
	
	if(ob->query("quest/try_fight"))
	  if(ob->query("quest/try_fight_id"))
	  {
	  	me=find_player(ob->query("quest/try_fight_id"));
	  	if(!me) 
		{
			::die();
			return 0;
		}
	    if(environment(me)!=environment(ob))
		{
			::die();
			return 0;
		}
	    if (me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"caught") && !me->query_temp(QUESTDIR2+"askzhi")&& !me->query(QUESTDIR2+"over"))
	        me->set_temp(QUESTDIR2+"askzhi",1);
	    ob->delete("quest/try_fight");
	    ob->delete("quest/try_fight_id");
     }
	::die();
}

string ask_jueji()
{ 
	object me, ob;
	int i,time;

	ob = this_object();
	me = this_player();
    
	if (!me->query("family")
		|| me->query("family/family_name")!="������")
		//|| me->query("family/master_id")!="jiumo zhi"
		return "����ҵ��ӣ����ʴ�����������";
    if ((int)me->query("lx/gree")<10)
    {
		return "����������������ʮ�㶼��δ������������������";
    }
	if( me->query_skill("longxiang-boruo", 1) < 450 )
		return RANK_D->query_respect(me) + "�������������������費��450�����޷��������ɻ��浶��Ҫ���ڣ�";
	

	command("pat "+me->query("id"));
	command("say �Ҵ���������������ǿ������ɣ������ܹ������������");
	command("say ��һ�ž���������������֮�����С��������������");
	command("say �ڶ��ž���������ƽ��������ѧ�����ǡ����浶��������ƾ��������ɨ�ڽ̡�");
	command("say �����ž���������ʦ����ַ����Ļ����񼼣��������־�������");
	command("say ����ѧ�����񹦣�����answer xx �ش�");
	me->set_temp("jueji/askjmz",1);
	add_action("do_answer","answer");
	return "�Ħ������������ǰ��꣬����һ����ɮ��¡�";
}
 
int do_answer(string arg)
{
   object key;
	object me=this_player();
	 if (!me->query_temp("jueji/askjmz"))
		return notify_fail("�����ʲô��");
	if (!arg) return notify_fail("�Ħ����Ц��������Ĭ���");
  //���������
   
	
	if (arg=="���������")
	{
      command("say �ðɣ���Ȼ�����������񹦣������ȥ�ɡ�");
	  command("say �����񹦲��������������ԣ�����������־���͡�");
	  command("say �ã���������һ��Կ�ף���ȥ�����Ƿ��������Ե��");
	  if( me->query("quest/dls/longxiang/pass")>12 )
		return notify_fail( RANK_D->query_respect(me) + "���㲻���Ѿ��⿪��ô��");
	  if (time()-me->query("quest/dls/longxiang/time")<86400)
		return notify_fail( RANK_D->query_respect(me) + "��������̫�ڿ��ˣ�");
	  if (me->query_skill("longxiang-boruo",1)<500)
		return notify_fail( RANK_D->query_respect(me) + "������������������500����������\n");
	  if (me->query_skill("longxiang-boruo",1)<500)
		return notify_fail( RANK_D->query_respect(me) + "������������������500����������\n");
	  if (me->query("int")<40)
	  {
		return notify_fail("�Ħ����Ц�������������������Ҫ�������ԣ��������Բ���40�������ң���");
	  }
	  if (this_object()->query("mishikey")>0)
	  {
		  key=new("d/xueshan/npc/obj/goldkey");
		  key->move(me);
		  command("say ��ú���أ���ҪŪ���ˡ�");
		  
		  me->set_temp("lxbr/start",1);

		  this_object()->add("mishikey",-1);
		  me->move("d/xueshan/mishi");
		  command("rumor ��˵"+me->query("name")+"�õ�һöѩɽ�����ҵĽ�Կ�ף�\n");
	  }
	  else {
       command("say �������е����ˣ�������������");
	  }
	  
	   me->delte_temp("jueji/askjmz");
	  return 1;
	 }
	 //���浶
	 if (arg=="���浶����")
	 {
       if( me->query("quest/dls/hyd/pass")){
		   me->set("title",HIY"�Ħ�������״�����"+HIR"���浶����"NOR);
		   me->set("mytitle/quest/dlshydtitle",HIY"�Ħ�������״�����"+HIR"���浶����"NOR);
		   return notify_fail( RANK_D->query_respect(me) + "���㲻���Ѿ��⿪��ô��\n");

	  }
	  if (me->query("family/master_id")!="jiumo zhi")
		 return notify_fail("�Ħ����Ц�������ȵ������ҵĵ��Ӷ����㣬����ȥ�����¸��Ҷ�������ô��");
	  
	  command("laugh "+me->query("id"));
	  command("say ���浶���������µ�һ�似��");
	  command("say ���ž��������ҳ����似����Ȼ����ѧ���Ǻ��Ҿͽ�����һ������ȥ��ɡ�");
	  command("say ������ӦĽ�ݲ�����Ū�����������µ�����֮�������񽣽��ס�");
	  command("say ��Ľ�ݲ��������������񽣶˵��ǰ��������Ҳ���Ǻ��档");
	  command("say ���������һ�ˣ�ȥ���Ǳ��ؼ����������������������Ҿʹ��������Ż��浶������");
	  command("say ������������Ҳ���������ң�");
	  if( me->query("quest/dls/hyd/pass") )
		return notify_fail( RANK_D->query_respect(me) + "���㲻���Ѿ��⿪��ô��");
	  if (time()-me->query("quest/dls/hyd/time")<86400)
		return notify_fail( RANK_D->query_respect(me) + "��������̫�ڿ��ˣ�\n");
	  if (me->query_skill("longxiang-boruo",1)<500)
		return notify_fail( RANK_D->query_respect(me) + "������������������500����������\n");
	  if (me->query_skill("huoyan-dao",1)<500)
		return notify_fail( RANK_D->query_respect(me) + "����Ļ��浶����500����������\n");
	  if (me->query("con")<40)
		return notify_fail( RANK_D->query_respect(me) + "������浶�ܿ����ǣ�����ǲ���40���������ң�\n");
	  me->set_temp("jueji/askhyd",1);
	  me->delete_temp("jueji/askjmz");
	  new("d/xueshan/npc/obj/goldletter")->move(me);
	  command("say ������д�����������¿��ٴ�ʦ�İ��������ô˰���ȥ�ɣ�");
	  command("say �ɲ�Ҫ��ʦ����ʧ������");
	  command("chat �������ɳ��ҵ��״�����"+me->query("name")+"Ϊ�ҳ�ʹ�����£�������λ���ž�ˣ��Ħ�ǲ�ʤ�м���");

	  return 1;
	 }
//������
	 if (arg=="�����־���")
	 {
		command("say ������������ʦ����ַ����Ķ��ž�������ȥ�������԰ɡ�");
		if( me->query("quest/wulun/pass") )
			command( "say ��λ�㲻���Ѿ��⿪��ô��");
		if (me->query("str")<32)
			return notify_fail( RANK_D->query_respect(me) + "���⽵������������������������32���ҿ�ȥҲ�ǰ״\n");
		return 1;
	 }

}
string hyd_jueji()
{ 
	

	object me, ob;
	int i,j,x;
	
	ob = this_object();
	me = this_player();       
	if (!me->query("quest/dls/hyd/biyan/givebook"))
	{
		me->add_temp("hydjj/askjueji",1);
		command("say ����ô�����������¶�ûȥ���������ң�С����ɱ���㣡");
		if ((int)me->query("hyd/askjueji")>3)
		{
			command("say ����");
			command("kick "+me->query("id"));
			me->move("d/xiangyang/damen");
		}
		return "";
	}
	if (!me->query("family")
		|| me->query("family/family_name")!="������"
		|| me->query("family/master_id")!="jiumo zhi")
		return "����ҵ��ӣ����ʴ�����������";

	
    if( me->query_skill("longxiang-boruo", 1) < 500 )
		return "�������������費�������޷��������ɻ��浶��Ҫ���ڣ�";
	if( me->query("quest/dls/hyd/pass")>12 )
		return "���Ѿ��������������quest���ֺιʿ�����Ц�أ�";

    if( me->query_skill("huoyan-dao", 1) < 500 )
		return "��Ļ��浶���費��450�����޷������������ִ�ת�ľ�Ҫ���ڣ�";
	if ((int)me->query("con")<40)
		return "����浶�ܿ����ǣ�����ǲ���40���������ң�\n";
	
	
	if( time()- me->query("quest/dls/hyd/time")<86400)
		return "�ţ��㲻�Ǹ�����̹��������ؼ��İ����𣿻�����Ŭ����ʱ��ɣ�";

   
	message_vision(HIY"$N����Ŀ���$n������˵���������ɵĻ��浶���������������飬ǧ���򻯣���һ��֮�棬����ѭ��������\n"
						"�㿴���ˣ��Ҹ�����ʾһ�飬�����Լ��������ˡ�\n"+
	  HIR"\n\n\n$N������ѣ����Ʒ��ɣ�������ӿ������������������磬Ѹ���ޱȡ�����$n�ۻ�����\n"NOR+
	  HBBLU"\n\n$N�����浶������������⾳ʩչ���������ɾ������ű��̶�ȥ�����ƻ�������ȴѸ���ޱ�\n\n"NOR+
	  HBBLU+HIG"\n\n$N��������������������鰴������бб���������������������ʹ�������ǡ����浶���е�һ���ֵ�����\n"NOR+
	  HBBLU+HIG"\n\n$N�˿�˫�����𣬺ݿ�����ȫ���������书��·�ӡ�$Nһ�����䣬�����浶��������ӿ������һ����\n"NOR+
	  HBBLU+HIG"\n\n$N��ʹ�����浶�������������޷����������������ӿ���������̺�Ȼ����$n���ұ�\n"NOR+
	  HBBLU+HIG"\n\n$N˫���籧Բ�������˳����������������������Ѷ�ȥ��ңңָ�Ż���$n�������Ѩ\n"NOR+
	  HBBLU+HIG"\n\n$N�����ڹ�����ǿ���������浶������������������ȻĪ�ܵ����������������죬��$n���ҳ����ȥ\n"NOR+
	  HBBLU+HIG"\n\n$N��ʹ���浶��һ�С��׺���ա�������ʽ�о���֮����һ����Ҫ����$n�����ȿ�������\n"NOR, ob, me);
 
    i = 20;
	if(me->query("m-card-vip")) i =  18;
	if(me->query("y-card-vip")) i =  15;
	if(me->query("buyvip"))     i =  10;
	i=random(i);

	j=random(me->query("kar"));
	x=random(me->query("con"));

	command("say �������ִ�Ψ�к������������֮������Ϸ��ܷ��������������һ����ǧ��Ҫ��ס��\n");
	command("pat "+me->query("id"));
	if( i<4 
		&& me->query("kar")<31
		&& x >= 35
		&& j >= 25 ) 
	{
		tell_object(me,HIY"\n�������Ħ�ǵ�ָ�㣬�Ա����ݺ�İ��������ĵá�\n"NOR);
		tell_object(me,HIG"\n����ͼ����Ϣ�嵽�͹�Ѩ�У�ͻȻֻ������������һ������ֱͨ˫�֣����Ͼ���������Ȼһ�ᡣ\n"
			             +"������ʶ��˳��һ�ӣ�һ���ƿ�������������һ��������ǿ���ĺܡ�\n"
						 +"���������������ű����ݺ���������÷��š����д�ϲ֮�£�������ʽ���಻��������\n"
						 +"����ʽ������ʹ���ŵ�һ��ͨ��ʱ���Ǽ��ѣ��ζ�������ͨ��������Ϥ����������\n"
						 +"���֮�䣬�����Ͼ�����ͨ�������˻��浶�����ݺ������\n"NOR);
		me->set("quest/dls/hyd/pass",1);
		log_file("quest/hydjueji", sprintf("%8s(%8s) ʧ��%d�κ�ѧ�����浶�����ݺ����,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/dls/hyd/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));
		me->set("title",HIY"�Ħ�������״�����"+HIR"���浶����"NOR);
		 me->set("mytitle/quest/dlshydtitle",HIY"�Ħ�������״�����"+HIR"���浶����"NOR);
		me->delete_temp("hydjj/givejianpu");
		return "��ϲ���ܻ��浶�����ݺ�ɹ�!\n";
		
	}	
   else
	{
		log_file("quest/hydjueji", sprintf("%8s(%8s) ���ܱ����ݺ����ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/dls/hyd/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"�������Ħ�ǵ�ָ�㣬���ǶԱ����ݺ�İ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/dls/hyd/fail",1);
		me->set("quest/dls/hyd/time",time());
		me->start_busy(1+random(3));
		me->delete_temp("hydjj/givejianpu");
		return "�ǳ��ź����ܻ��浶�����ݺ�ʧ��"+me->query("quest/dls/hyd/fail")+"�Ρ�\n";
	}
}

int accept_object(object who, object obj)
{
	int i,j;
	i=2+random(10);
	j=1000+random(5000);
	if (obj->query("id")!="liumai jianpu")
	{
		command("kick "+who->query("id"));
		return notify_fail("���������ҵ��������ҵĶ����ҵ���ô��");
	}
	if (who->query_temp("hydjj/tlsover")
		&& obj->query("id")=="liumai jianpu"
		&& obj->query("owner")==who->query("id")
		)
	{
		//who->set_temp("hydjj/givejianpu",1);
		write(HIY"�㽫"HIC"��������"HIY"���������ݸ��Ħ�ǣ�˵������ʦ�����Ҳ���ʹ������\n"NOR);
		command("say ��ͽ������ͽ���������ڿ�ʼ���Ҵ����µĹ�������");
		command("chat �����ºô����������ҿ���������˶��ѣ��ҵĵ��Ӵ������������������");
		command("chat �����������˵�������");
		command("chat "+who->query("name")+"�������״����ӣ���λ���Ż����չ�һ����");
		write(HIG"�Ħ�������������ף�һ�߷��뻳��һ��˵������ͽ��������ȥ��Ϣȥ�ɣ�ΪʦҪ�úò�����꣡����\n"NOR);
		obj->move(this_object());
		destruct(obj);
		who->delete_temp("hydjj/tlsover");
		who->add("SJ_Credit",i);
		who->add("combat_exp",j);
		who->set("quest/dls/hyd/biyan/givebook",1);
		message_vision(HIC"���յ����Ħ�Ǵ�ʦ����Ľ������ܹ�"HIR+chinese_number(i)+HIC"��ͨ�����Լ�"HIR+chinese_number(j)+HIC"��ս�����顣\n"NOR,who);
		return 1;
	}
}
