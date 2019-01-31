// due.c
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
#include "bai-du.h"
string ask_me();
string ask_kanshou();
string ask_rybjj();
string ask_rybronghe();

void create()
{
        object ob;
        set_name("�ɶ�", ({ "du e", "du", "e" }) );
        set("title", "���ֳ���");
        set("gender", "����");
        set("class", "bonze");
        set("age", 90);
        set("long", "����һ��������ݣ��ݹ��㶡����ɮ������ɫ�ݻƣ���ͬһ�ο�ľ��\n");
        set("attitude", "peaceful");
        set("combat_exp",16500000);
        set("shen", 50000);
        set("str", 30);
        set("int", 25);
        set("dex", 28);
        set("con", 28);
        set("qi", 36000);
        set("max_qi",36000);
        set("max_jing", 9000);
        set("eff_jingli", 9500);
        set("neili",36000);
        set("max_neili",36000);
        set("jiali", 250);
        set("no_get", 1);
        set("unique", 1);

        create_family("������", 35, "����");
        assign_apprentice("����", 0);
        set_skill("force", 550);
		set_skill("club", 530);
        set_skill("zui-gun",530);
        set_skill("whip", 530);
        set_skill("parry", 530);
        set_skill("dodge", 530);
        set_skill("buddhism", 201);
        set_skill("literate", 250);
        set_skill("yijin-jing", 550);
        set_skill("riyue-bian", 550);
        set_skill("shaolin-shenfa", 530);
        set_skill("hand",530);
        set_skill("fumoquan-zhen",530);
        set_skill("leg",530);
        set_skill("blade", 530);
        set_skill("xiuluo-dao", 530);
        set_skill("qianye-shou",530);
        set_skill("ruying-suixingtui",530);
        map_skill("force", "yijin-jing");
        map_skill("blade", "xiuluo-dao");
        map_skill("whip",  "riyue-bian");
        map_skill("parry", "xiuluo-dao");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("hand","qianye-shou");
		map_skill("club","zui-gun");
        map_skill("leg","ruying-suixingtui");
        prepare_skill("hand","qianye-shou");
        prepare_skill("leg","ruying-suixingtui");
        set("inquiry", ([
                "��ħ����"     : (: ask_me :),
				"����лѷ"     : (: ask_kanshou :),
				"��ħȦ����"     : (: ask_rybjj :),
				"���±��ں�"     : (: ask_rybronghe :),

        ]));
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "whip.chanrao" :),
                (: perform_action, "whip.fumoquan" :),
                (: perform_action, "hand.qianshou" :),
                (: perform_action, "leg.ruying" :),
        })); 
        setup();
        if (clonep()) {
                ob=unew(BINGQI_D("whip/heisuo"));
                if (!ob) ob = unew(BINGQI_D("changbian"));
                ob->move(this_object());
                ob->wield();
                carry_object("/d/shaolin/obj/du-cloth")->wear();
        }       
}

void init()
{
        int i, j;
        object me, ob;
        mapping fam;
        me = this_player();
        ob = this_object();
        ::init();
        if(interactive(me)){
                if (mapp(fam = me->query("family")) && fam["family_name"] == "������" 
                && fam["generation"] <= 36 ) {
                        me->set_temp("fighter", 1);
                        return;
		}
                if (mapp(fam = me->query("family")) && fam["family_name"] == "������" 
                && fam["generation"] > 36               
                && me->query("qi") < 50 ) {
                        me->move("/d/shaolin/qyping");
                        me->unconcious();
                        return;
		}
                if(base_name(environment(ob))!="/d/shaolin/fumoquan") return;
                command("say �����ӷ�");
                i = me->query("combat_exp");
                j = me->query("potential");
                COMBAT_D->do_attack(ob, me, query_temp("weapon"), 2);
                COMBAT_D->do_attack(ob, me, query_temp("weapon"), 2);
                me->set("combat_exp", i);
                me->set("potential", j);
                me->set_temp("fighter", 1);
                remove_call_out("halt");
                call_out("halt", 0, me);
                return;
        }
        return;
}

void halt(object me)
{
	if(me->is_ghost()) return;
	if(!living(me) && environment(me) == environment()){
		message_vision("$N���ɶ��ó���һ���ӳ��˽�շ�ħȦ��\n", me);
		me->move("/d/shaolin/qyping");  
		message_vision("$N���˴Խ�շ�ħȦ�����˳�����\n", me);
	}
	else command("say �ðɣ����ס�֣� ����һ���ʲô��Ҫ˵��");
}

string ask_me()
{
        object whip;
        object ob,me;
        me = this_player();
        
	if ( !this_player()->query_temp("fighter") 
	 ||  this_player()->query("combat_exp") < 5000 ){
		command("say ���󱲣����δ�ɣ�����͵���շ�ħȦ�������������������㣡");
		this_object()->kill_ob(this_player());
		this_player()->kill_ob(this_object());
		return 0;
        }

        if ( present("huangjin nao", this_player()) || present("fumo nao", this_player()))
                return RANK_D->query_respect(this_player())+ "����ֻ��һ�ԣ����Ҿ��������ϣ�����̰�����У�";

        if ( present("huangjin nao", environment()) || present("fumo nao", environment()))
                return RANK_D->query_respect(this_player()) + 
                "����ֻ��һ�ԣ����Ҿ�����������ȡ�ߣ�����̰�����У�";

        if(present("zhanyao nao", environment()) || present("zhanyao nao",this_player()))
                return RANK_D->query_respect(this_player())+ "������ն�����󣬾Ͳ������÷�ħ����ĪҪ̰�����У�";

        if ( present("jingang zhao", this_player()) || present("jingang zhao", environment()) )
		return RANK_D->query_respect(this_player())+ "ȡ�˽���֣��Ͳ������ûƽ���ĪҪ̰�����У�";

        if(me->query_temp("fmnao")) return "�ղŷ�ħ�����Ǹո�����"; 

	if( clonep()){
		ob= unew(BINGQI_D("blade/jinnao"));
		if(ob){
			destruct(ob);
			ob=unew(BINGQI_D("blade/jinnao1"));
		}
		if(ob) ob->move(this_object());
	}
	if ( present("fumo nao", this_object())){
		message_vision("\n�ɶ�Цһ�������ͷ�������еķ�ħ�����ò����á�\n\n", this_player());
		command("give fumo nao to "+this_player()->query("id")); 
		me->add_busy(2);
		me->set_temp("fmnao",1);
		whip = unew(BINGQI_D("whip/heisuo")); 
		if(clonep(whip)){
			whip->move(this_object());
			command("wield bian"); 
		}    
		else {
			if (!(whip = present("changbian", this_object()))) 
				whip = unew(BINGQI_D("changbian")); 
			whip->move(this_object());
			command("wield bian"); 
		}
		return "���Ȼ�ܴ�����շ�ħȦ������Ȼ�ǵ��������еķǷ������ֻ�����ʷ������ˣ�";
	}
	return "��Ǹ���������ˣ���ħ�����Ѿ�����ȡ���ˡ�";
}

string ask_kanshou()
{
	object me = this_player();

	
	if (time()-me->query("quest/sl/ryb/kanshou/time")<86400)
	{
		command("say ������̫Ƶ���ˣ�������������!\n");
		return "�����ӷ�!\n";
	}
	if ( me->query_skill("yijin-jing",1)<500 )
		return RANK_D->query_respect(me)+"������׽����̫ǳ������500�������ǵ��������������ɣ�";
	
	if ( me->query_skill("riyue-bian",1)<500 )
		return RANK_D->query_respect(me)+"��������±޷�����̫ǳ������500�������ǵ��������������ɣ�";
	if ( me->query("int")<35 )
		return RANK_D->query_respect(me)+"�����±޷���Ҫ�����ԣ�����������Բ���35�����ǵ��������������ɣ�";

	command("say лѷ������������ִ�У���ɱ����ʦֶ�տռ����˳𲻿ɲ�����\n");
	command("say ��Ȼ����������⣬�Ǿ����������������ش˶�����ǧ�򲻿�и����\n");
	command("say ����ħ�̽�ͽ�����������֣��������������ٴ�������Ҫ�ػ����ˣ�\n");
	command("say �ɱ����ҵ�������ɮʧ����\n");
	me->set_temp("ryb/askdue",1);
	
	return "ħ���������˵ö���֮����һ��ɱһ��\n" +
	       "��Ҳ��һ�ִȱ���\n";
}
string ask_rybronghe()
{
	object me = this_player();

	

	if ( me->query_skill("yijin-jing",1)<500 )
		return RANK_D->query_respect(me)+"������׽����̫ǳ������500�������ǵ��������������ɣ�";
	
	if ( me->query_skill("riyue-bian",1)<500 )
		return RANK_D->query_respect(me)+"��������±޷�����̫ǳ������500�������ǵ��������������ɣ�";
//	command("say ���±޷�������������������似֮һ��\n");

	command("say ���±޷�������������������似֮һ��\n");
	command("say �������������̽������޼ɺͶ����������������ֹ��ҷ�ħȦ��\n");
	command("say ��ʱ�Ҽ������ŵı޷������ص㣬���±仯�����߹���Ͳ��ɲ⣡\n");
	command("say �������ģ�������ȥ�ݷ�����Ů����˵���������ҵȱ���֮���ܴ���������ӵİ��أ�\n");
		command("say Ҳ��Ὣ�����±޷�������ߵ�һ�����磬��ȫƾԵ����\n");

	me->set_temp("ryb/jiuyin_askdue",1);
	
	return "�����ŵı����˵���һ�������䲻�����±޵ĸվ�ǿ�ᣬ��ȴ�����仯֮���¡�\n";
}

int do_say()
{
  object me=this_player();
  command("congra "+me->query("id"));
  command("chat ħ�̽�ͽ�ݺ������ҿ�Ҳûʲô�˲���\n");
  command("chat ���ο��ų����µ�һ���ֵ����޼�Ҳ��ɥ"+me->query("name")+"֮�֣�\n");
  command("chat ��ϲ"+me->query("name")+"���������̽�ͽ���Ҵ�����������һ�������֣�\n");
  return 1;
}


string ask_rybjj()
{
	int i,j;
	object me = this_player();
	
	if (me->query("quest/sl/ryb/fumoquan/pass"))
	{
		command("say ���Ѿ��⿪�ˣ��α������ɧ����ɮ!\n");
		me->set("title",HIY"������"+HIR"��"HIB"��"HIY"�޷�����"NOR);
		me->set("mytitle/quest/riyuebiantitle",HIY"������"+HIR"��"HIB"��"HIY"�޷�����"NOR);
		return "�����ӷ�!\n";
	}
	if (me->query("family/family_name")!="������")
	{
		command("say ��������ֵ��ӣ���������!\n");
		return "�����ӷ�!\n";
	}
	if (me->query("int")<35)
	{
		command("say ���±޷������鶯������������Բ���35,����Ҳ�״�!\n");
		return "�����ӷ�!\n";
	}


	if (time()-me->query("quest/sl/ryb/fumoquan/time")<86400)
	{
		command("say ������̫Ƶ���ˣ�������������!\n");
		return "�����ӷ�!\n";
	}
	if ( me->query_skill("yijin-jing",1)<500 )
		return RANK_D->query_respect(me)+"������׽����̫ǳ������500�������ǵ��������������ɣ�";
	
	if ( me->query_skill("riyue-bian",1)<500 )
		return RANK_D->query_respect(me)+"��������±޷�����̫ǳ������500�������ǵ��������������ɣ�";
	
	command("say ��Ȼ���ػ��й���Ϊ�Ҵ����ֳɹ�������ʦ��ᡱ��ϼ�����ͣ��Ҿͽ��˱޷�Ҫ�崫�ڸ��㣡\n");
	command("say �ܷ�����Ϳ����Լ��������ˣ�\n");
	command("whisper "+me->query("id"));
	
	j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;
	if (me->query("class")=="bonze")
	     j=random(j-2);
	else j= random(j);
	
	i=random(me->query("kar"));
 
    if(j<3
		&& i>26
		&& random(me->query("int"))>35)
	 {
		tell_object(me,HIG"\n�㰴�նɶ��ָ�㣬�����±޷������������ƺ���Щ�ĵá�\n"NOR);
        tell_object(me, HIW"�㰴�նɶ����ԣ���Ϣ���ԡ���ǿѨ������������ᡢ���ء����š�����\n+"+
"��Ѩ��һ·���ż�׵�������ߵĶ��Ǳ��϶��θ���ҪѨ��Ȼ���Ǽ��С����ࡢ������������\n"+
"��̨��������������յ�����׵�����š��縮���Ի���ǿ�䡢�󶥡��������ŵġ��ٻ�Ѩ����\n"NOR);
		tell_object(me,HIY"\n\n\n��ϲ�㣡������ǧ���ڿ࣬���ڵó���Ը�������±޷���ħȦ�����ڻ��ͨ��\n"NOR);
       	//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/sl/ryb/fumoquan/pass",1);
		me->set("title",HIY"������"+HIR"��"HIB"��"HIY"�޷�����"NOR);
		me->set("mytitle/quest/riyuebiantitle",HIY"������"+HIR"��"HIB"��"HIY"�޷�����"NOR);
		me->start_busy(1);
		log_file("quest/fumoquan", sprintf("%8s(%8s) ʧ��%d�κ󣬳��������ħȦ�ľ�����iȡֵ��%d|jȡֵ��%d|intȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/sl/ryb/fumoquan/fail"),i,j,me->query("int"),me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/sl/ryb/fumoquan/fail",1);
		me->set("quest/sl/ryb/fumoquan/time",time());
		command("buddha ");
		tell_object(me,HIY"�����˶ɶ��ָ�㣬��Ȼ�����˷�ħȦ�İ��أ����ǶԷ�ħȦ������������ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		log_file("quest/fumoquan", sprintf("%8s(%8s) ��ħȦ����ʧ��%d�Ρ�iȡֵ��%d|jȡֵ��%d|intȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/sl/ryb/fumoquan/fail"),i,j,me->query("int"),me->query("combat_exp")) );
	  }
    		
		return "ħ���������˵ö���֮����һ��ɱһ��\n" +
	       "��Ҳ��һ�ִȱ���\n";
}