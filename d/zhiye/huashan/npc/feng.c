// NPC: /d/huashan/npc/feng.c
// Date: Look 99/03/25
// Modify by Lklv 2001.10.18
// By KinGSo ���Ӷ��¾Ž� ������ʽ 2010

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_wuzhao();
string ask_jiushi();
void create()
{
	set_name("������", ( {"feng qingyang","feng","qingyang"} ) );
	set("long", "����������ɫ�����������ֽ��\n" );
	create_family("��ɽ��", 12, "����");

	set("age", 91);
	set("gender", "����");
	set("attitude", "friendly");
	set("shen_type", 1);
	set("shen",150000);
	set("no_quest",1);

        set("con", 45);
        set("dex", 40);
        set("int", 50);
        set("str", 40);
	    set("per", 24);
        set("max_jing", 9000);
        set("max_neili", 45000);
        set("max_qi", 47500);
        set("eff_jingli", 9000);
        set("neili", 45000);
        set("jiali", 250);
        set("combat_exp", 15000000);

        set_skill("sword",550);
        set_skill("force",500);
        set_skill("dodge",500);
	    set_skill("poyu-quan", 500);
	    set_skill("cuff", 500);
        set_skill("parry",500);
        set_skill("dugu-jiujian",550);
        set_skill("huashan-shenfa",500);
        set_skill("huashan-jianfa",550);
        set_skill("huashan-qigong",500);
        set_skill("zhengqi-jue",200);
		set_skill("ziyin-yin",200);


        map_skill("force","huashan-qigong");
        map_skill("sword","dugu-jiujian");
        map_skill("dodge","huashan-shenfa");
	    map_skill("parry","dugu-jiujian");
	    map_skill("cuff", "poyu-quan");
	    prepare_skill("cuff", "poyu-quan");

	    set_temp("apply/damage", 40);
        set_temp("apply/dodge", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/armor", 40);
		set("inquiry", ([
			"������ʽ"	: (: ask_wuzhao :),
			//"���¾�ʽ"	: (: ask_jiushi :),
			]));
		set("chat_chance_combat",160);
        set("chat_msg_combat", ({
		    (: perform_action, "sword.jiushi" :),
			(: perform_action, "sword.wuzhao" :),
			(: perform_action, "sword.zongjue" :),
			(: perform_action, "sword.poqi" :),
			(: perform_action, "sword.pozhao" :),
			(: exert_function, "yujianshi" :),
	    }));
		
		setup();

        carry_object(BINGQI_D("sword"))->wield();
        carry_object(ARMOR_D("cloth"))->wear();
}

void attempt_apprentice(object ob)
{
        if (!ob->query("fengset")) {
		command("say ���ҿ��½�����Ե����λ" + RANK_D->query_respect(ob)+"������ذɡ�");
		command("wave " + ob->query("id"));
		return;
        }
        if (ob->query("shen") < 1000000 ) {
		command("say �һ�ɽ�����������������ɣ��Ե���Ҫ���ϡ�");
		command("say �ڵ��з��棬" + RANK_D->query_respect(ob) + "�Ƿ����ò�����");
		return;
        }
        if ((int)ob->query_skill("huashan-qigong",1) < 350)
			
        if ((int)ob->query_skill("zixia-gong",1) < 350){

			command("say ��λ" + RANK_D->query_respect(ob)+
                        "����������ڹ��ȼ����ͣ��²��������Ҷ��¾Ž����衣");
                return;
        }
        if ((int)ob->query_skill("huashan-shenfa",1) < 350){
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "����Ļ�ɽ���ȼ����ͣ��²��������Ҷ��¾Ž����衣");
                return;
        }
        if ((int)ob->query_skill("huashan-jianfa",1) < 350){
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "����Ļ�ɽ�����ȼ����ͣ��²��������Ҷ��¾Ž����衣");
                return;
        }
        command("say �ðɣ��Ҿ���������,���ҪΪ���ǻ�ɽ����������");
        command("chat* ���ϸ��ֳ�һ˿Ц�ݣ�����"+ob->query("name")+"Ц�����һ�ɽ��������ˡ�");
        command("chat* nomatch feng");
        command("recruit " + ob->query("id"));
        ob->set("title", HIW"���¡��Ž�"NOR);
		ob->set("mytitle/quest/dgjjtitle",HIW"���¡��Ž�"NOR);
        ob->set("quest/huashan","����");
}

string ask_wuzhao()
{
    object me;
    mapping fam;
    me=this_player();
   if ( mapp(fam=me->query("family"))
    && (string)fam["family_name"] != "��ɽ��"){
    command("? "+me->query("id"));
    return "��λ" + RANK_D->query_respect(me) + "��������˵�Ķ��¾Ž�����\n";
    }
  
   if (me->query("quest/huashan")=="����")
       return "����Ԧ������ֱ���Ǻ�����\n";

   if ((int)me->query("combat_exp") < 12000000)
       return "���ʵս���黹���㣬�޷������¾Ž��ġ�������ʽ����\n";

   if(me->query("quest/hs/dgjj/wuzhao/pass"))
   {

	   return "�㲻���Ѿ�������������ʽ������ǲ��ͷ���ң�\n";
   }
   if(me->query("int") < 40 )
   {
		return"���¾Ž�������Ҫ���ߵ����ԣ����ҿ�" + RANK_D->query_respect(me) + "�������������ʲ���40���ƺ��޷���⣿\n";
   }
   
   if(me->query("dex") < 35)
   {
	   
		return"���¾Ž�������Ҫ���ߵ��鶯�ԣ����ҿ�" + RANK_D->query_respect(me) + "�����������ʲ���35���ƺ��޷�ʩչ��\n";
		
	}

   if ((int)me->query_skill("force",1) < 500){
                return"��λ" + RANK_D->query_respect(me)+"������ڹ��ȼ����ͣ�����500���²��������Ҷ��¾Ž����塣\n";
   }

   if ((int)me->query_skill("dugu-jiujian",1) < 500){
                return"��λ" + RANK_D->query_respect(me)+"����Ķ��¾Ž��ȼ�����(500)���²��������Ҷ��¾Ž����塣\n";
                
   }
   if (me->query("family/master_id")!="feng qingyang"){
                return"��λ" + RANK_D->query_respect(me)+"���Ҳ���ʶ����Ϊ������\n";
                
   }
    if (time()-me->query("quest/hs/dgjj/wuzhao/time")<86400){
                return"��λ" + RANK_D->query_respect(me)+"��������̫�ڿ���Ү��\n";
                
   }
  
	command("say ���¾Ž����н����ˣ����ж��ǽ�����������ʽ֮���ɱ仯����ν�ﵽ�仯֮���¡�\n");
	command("say ����ʽ�����ģ����ǻ�ģ�����һ����һֱ��׷�󽣵�֮����--�����ж�ʤ���С�\n");
	command("say ���¾Ž����б仯�Լ��ܾ�ʽ���Ѿ��������㣬����δ���ܷ�ﵽ������磬�Ϳ�����˻����ˡ�\n");

	command("say ����������¾Ž����Ǵ���һ����ħ�������ǰ����\n");
	command("say ��ʱ����ǰ���ųƶ�����ܣ�����һ�ܶ����á�����������Ⱥ�����֡������Ƕ�ô��į�����ΰ���\n");
	command("say ��Ҳ�����������ԣ�����ǰ��������һ���·أ��ųơ���ڣ����\n");
	command("say �ڽ�ڣ֮�������¾����似��Ҳ����ȥ�Ķ��������ҵ�Щ���Ե��\n");
	command("say ����ʮ��󣬲����������Կ�Ϊ�����Դ˽��ޣ������޽�ʤ�н����硱.....\n");
	me->set_temp("wuzhao/askfeng",1);
	return "����ʤ���У�����һ��������ʦ���ռ����磡\n"; 

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
//��ʽ��ʱ�ر�
/*
string ask_jiushi()
{
    object me;
    mapping fam;
    me=this_player();
   if ( mapp(fam=me->query("family"))
    && (string)fam["family_name"] != "��ɽ��"){
    command("? "+me->query("id"));
    return "��λ" + RANK_D->query_respect(me) + "��������˵�Ķ��¾Ž�����\n";
    }
   
   if (me->query("quest/huashan")=="����")
       return "����Ԧ������ֱ���Ǻ�����\n";

   if ((int)me->query("combat_exp") < 12000000)
       return "���ʵս���黹���㣬�޷������¾Ž��ġ����¾�ʽ����\n";

   if(me->query("quest/hs/dgjj/jiushi/pass"))
   {

	   return "�㲻���Ѿ������ˡ����¾�ʽ��������ǲ��ͷ���ң�\n";
    //        return;
   }

   if(me->query("int") < 40 )
   {
		return"���¾Ž�������Ҫ���ߵ����ԣ����ҿ�" + RANK_D->query_respect(me) + "�������������ʲ���40���ƺ��޷���⣿\n";
   }
   
   if(me->query("dex") < 35)
   {
	   
		return"���¾Ž�������Ҫ���ߵ��鶯�ԣ����ҿ�" + RANK_D->query_respect(me) + "�����������ʲ���35���ƺ��޷�ʩչ��\n";
		
	}

   if ((int)me->query_skill("force",1) < 500){
                return"��λ" + RANK_D->query_respect(me)+"������ڹ��ȼ����ͣ�����500���²��������Ҷ��¾Ž����塣\n";
   }

   if ((int)me->query_skill("dugu-jiujian",1) < 500){
                return"��λ" + RANK_D->query_respect(me)+"����Ķ��¾Ž��ȼ�����(500)���²��������Ҷ��¾Ž����塣\n";
                
   }
   if (me->query("family/master_id")=="feng qingyang"){
                return"��λ" + RANK_D->query_respect(me)+"���Ҳ���ʶ����Ϊ������\n";
                
   }
   if (timer()-me->query("quest/hs/dujj/jiushi/time")<86400){
                return"��λ" + RANK_D->query_respect(me)+"���书̰�಻�ã�������̫�ڿ���Ү��\n";
                
   }
	command("say ���¾Ž����н����ˣ����ж��ǽ�����������ʽ֮���ɱ仯����ν�ﵽ�仯֮���¡�\n");
	command("say ����ʽ�����ģ����ǻ�ģ����Ȱ����ʽ��һ��ȥ׷������ʤ���еľ��硣\n");
	command("say ���¾Ž����б仯�Լ��ܾ�ʽ���Ѿ��������㣬����δ���ܷ�ﵽ������磬�Ϳ�����˻����ˡ�\n");

	command("say ����������¾Ž����Ǵ���һ����ħ�������ǰ����\n");
	command("say ��ʱ����ǰ���ųƶ�����ܣ�����һ�ܶ����á�����������Ⱥ�����֡������Ƕ�ô��į�����ΰ���\n");
	command("say ��Ҳ�����������ԣ�����ǰ��������һ���·أ��ųơ���ڣ����\n");
	command("say �ڽ�ڣ֮�������¾����似��Ҳ����ȥ�Ķ��������ҵ�Щ���Ե��\n");
	command("say ����ʮ��󣬲����������Կ�Ϊ�����Դ˽��ޣ������޽�ʤ�н����硱.....\n");
	me->set_temp("wuzhao/askfeng",1);
	return 1;

}

*/




