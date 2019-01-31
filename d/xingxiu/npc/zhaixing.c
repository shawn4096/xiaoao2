// zhaixing.c ժ����
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_job();
string ask_laoyue();
void create()
{
	set_name("ժ����", ({ "zhaixing zi", "zhaixing", "zi" }));
	set("nickname", "�����ɴ�ʦ��");
	set("long", "һ����ʮ�߰���İ��������ˡ�����ĸ��ݣ���ɫ���з��ƣ���Ŀȴ��Ӣ����\n");
	set("gender", "����");
	set("age", 27);
        set("attitude", "peaceful");
        set("str", 30);
        set("int", 24);
        set("con", 23);
        set("dex", 30);
        set("per", 24);

        set("max_qi", 15500);
        set("max_jing", 6000);
        set("eff_jingli", 5500);
        set("combat_exp", 6800000);
        set("shen", -18000);

    	set_skill("force", 400);
    	set_skill("huagong-dafa", 400);
    	set_skill("dodge", 400);
    	set_skill("zhaixingshu", 400);
    	set_skill("strike", 400);
    	set_skill("chousui-zhang", 400);
    	set_skill("poison", 190);
    	set_skill("parry", 400);
    	set_skill("staff", 400);
    	set_skill("tianshan-zhang", 400);
    	set_skill("literate", 120);
    	set_skill("claw", 400);
    	set_skill("sanyin-zhua", 400);

    	map_skill("force", "huagong-dafa");
    	map_skill("dodge", "zhaixingshu");
    	map_skill("strike", "chousui-zhang");
    	map_skill("parry", "chousui-zhang");
    	map_skill("staff", "tianshan-zhang");
    	map_skill("claw", "sanyin-zhua");
    	prepare_skill("claw", "sanyin-zhua");
    	prepare_skill("strike", "chousui-zhang");

    	set("chat_chance_combat", 15);
    	set("chat_msg_combat", ({
                (: exert_function, "huagong" :),
                (: perform_action, "strike.huoqiu" :),
                (: perform_action, "strike.yinhuo" :),
                (: perform_action, "strike.biyan" :),
    	}));

    	create_family("������", 2, "����");
    	set("inquiry", ([
		"������" : "������룬�Ͱ���Ϊʦ��",
                "���޺�" : "ȥ���޺���ʲô������Ϊʦ�͹���ѧ���ˡ�",
                "������" : "����������е���û��ûС�ġ��Ժ�����ɣ�",
				"��������" : (: ask_laoyue :),
                "����" : (: ask_job :),
	]));
    	setup();
    	UPDATE_D->get_cloth(this_object());
    	carry_object("/d/xingxiu/obj/yao");
    	carry_object("/d/xingxiu/obj/yao1");
    	carry_object("/d/xingxiu/obj/yao3");
    	add_money("silver", 60);
}
void attempt_apprentice(object ob)
{
	if(ob->query("family/family_name") != "������"){
        	say("ժ���Ӷ�"+ob->name()+"������\n");
        	return;
        }
     	if(ob->query_skill("huagong-dafa",1) < 250 || ob->query("shen") > -50000){
        	command("say ����������������ҲŲ��������ء�");
        	return;
        }
		if(ob->query_skill("poison",1) < 120 ){
			command("say ��Ķ��ƻ�����120���ҲŲ��������ء�");
			return;
		}
     	command("say �ðɣ�������Ļ������е�����ˣ��Ҿ�������ɡ�");
     	command("recruit " + ob->query("id"));
}
string ask_job()
{
  	object me, ob;
  	mapping fam;
  	int shen, exp;
  	me = this_player();
  	fam = (mapping)me->query("family");
  	shen = me->query("shen");
  	exp=me->query("combat_exp",1);
    
	if (!me->query_temp("ding_flatter"))
	{
		command("say �㲻ȥ�ֺ����ɣ�������ʲô��");
		return "ժ���������ƺ���Ϊ���䣬��֪����˵ʲô��\n";
	}
    	if(!fam) return "���ó��������̬�ȹ������β��������������أ�";
    	if(fam["family_name"] != "������" && !me->query_temp("ding_flatter"))
       		return "������ɵ�̬�ȿ���ȥ��̫��������";
    	if(exp < 1000000)
    		return "������������㹦���ȥ���������˵ģ��ټӰ��������ɡ�";
        //if(exp >= 1000000 )
    		//return "�������������Ҳ�̫��������Լ�ȥ���������˼Ұɡ�";
		if( me->query("job_name") == "���ɷ���")
			return "�����������黹�ã���������Ϊ���ɷ��ǡ�";
    	if(me->query_condition("wait_xx_task"))
    		return "�ϴθ����ˣ������͵ȵȰɡ�";
    	if( me->query_temp("xx_job"))
    		return "����ô�������﷢����";
    	if( me->query_condition("wait_xx_task"))
    		return "�����������黹�ã���������Ϊ�����ǡ�";
    	ob = new("/d/xingxiu/obj/di");
    	ob->move(me);
    	ob->set("name", MAG "����̵�" NOR);
    	ob->set("long", MAG"����Ѷ̵ó��棬ֻ�����ߴ�������ͨ���Ϻ죬��Ө�ɰ���\n" NOR);
    	ob->set("xx_user", getuid(me));
    	if(fam["family_name"] != "������")
      		me->set_temp("title", MAG"�������ſ�"NOR);
    	me->set_temp("xx_job", 1);
    	message_vision("\n$N�ó�һֻ���ƶ̵ѣ�����$n��\n", this_object(), me);
    	return "����������鲻�ѣ����Ҫ���Ϊ�����˼ҷ��ǲ��ǣ�\n";
}
string ask_laoyue()
{
  	object me, ob;
  	mapping fam;
  	int shen, exp;
  	me = this_player();
  	fam = (mapping)me->query("family");
  	shen = me->query("shen");
  	exp=me->query("combat_exp",1);

    	if(!fam) return "���ó��������̬�ȹ������β��������������أ�";
    	if(fam["family_name"] != "������" && !me->query_temp("ding_flatter"))
       		return "������ɵ�̬�ȿ���ȥ��̫��������";
    	if(exp < 150000)
    		return "����������150k�����������ټӰ��������ɡ�";
        if(me->query_skill("huagong-dafa",1)<100 
			||me->query_skill("zhaixingshu",1)<100)
    		return "��������ȫƾǿ���ڹ����Ṧ֧�֣���������100���������Ͻ�����ȥ��";
		
    	if (me->query("quest/xx/tsz/laoyue/pass"))
			return "��λ"+RANK_D->query_respect(me)+"���Ѿ��⿪����ɽ�Ⱥ������¾�������û����ɧ����!";
        if (time()-me->query("quest/xx/tsz/laoyue/time")<86400)
			return "��λ"+RANK_D->query_respect(me)+"��Ҳ̫�ڿ���ˣ�������Ҫ����Ŭ���ź�!";
        //���״̬
		me->set("quest/xx/tsz/laoyue/time",time());
		me->set("quest/xx/tsz/laoyue/exp",me->query("combat_exp"));
		command("say �⺣��������������ժ��������������ץס�ɳ�ȥ�ȷ���һ�ż��ɡ�\n");
		command("say ������ѧ���͸�������������ϸ������\n");
        if(random(me->query("kar"))> 15) 
	    {
			command("heng "+me->query("id"));
	   	    command("pat "+me->query("id"));
		    message_vision(HIC"\n������������ժ����˵�ĺ������¾�����\n",me);
		    me->set("quest/xx/tsz/laoyue/pass",1);
			log_file("quest/xxlaoyue", sprintf("%s(%s) ʧ��%d�γɹ��⿪�������¾�������Դ��%d�����飺%d��\n",   
             me->name(1),
             me->query("id"), 
             me->query("quest/xx/tsz/laoyue/fail"),
             me->query("kar"),
             me->query("combat_exp")) );
			command("grin ");
            return "ժ����˵�����ðɣ��Ժ����������һ�������ˡ������Ҷ���׷ɱ���ף�"; 
			
		  }
		  else {
	   	    command("say �ܱ�Ǹ���Ұﲻ���㡣�´������ɡ�");
			me->set("quest/xx/tsz/laoyue/time",time());
			me->set("quest/xx/tsz/laoyue/exp",exp);	
			log_file("quest/xxlaoyue", sprintf("%s(%s) �⺣������ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
             me->name(1),
             me->query("id"), 
             me->query("quest/xx/tsz/laoyue/fail"),
             me->query("kar"),
             me->query("combat_exp")) );
			me->add("quest/xx/tsz/laoyue/fail",1);
			return "ժ����ɨ���㼸�ۣ������ֹ������������Ȼ��ô���������ҵĲ˰�����\n";
		  }
}
