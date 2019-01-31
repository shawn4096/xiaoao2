// madayuan.c ���Ԫ
// 
// by sohu@xojh
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
#include "begger.h";
string ask_suohou();
int ask_xiaofeng();


void create()
{
        set_name("���Ԫ", ({ "ma dayuan", "ma"}));
        set("title", HIW"������"NOR);
        set("gb/bags",9);
        set("gender", "����");
        set("age", 47);
        set("long", "������ؤ���еĸ���������Ե���á�\n"
        	    "����ʹ�������־���������������\n");
        set("attitude", "peaceful");
        set("unique", 1);
        set("str", 25);
        set("int", 20);
        set("con", 20);
        set("dex", 20);

        set("qi", 12400);
        set("max_qi", 12400);
        set("jing", 6000);
        set("max_jing", 6000);
	set("eff_jingli", 6000);
        set("neili", 25000);
        set("max_neili", 25000);
        set("jiali", 200);
        set("combat_exp", 6500000);

        set_skill("force", 400);
        set_skill("huntian-qigong", 400);
        set_skill("dodge", 400);
        set_skill("xiaoyaoyou", 400);
        set_skill("parry", 400);
        set_skill("hand", 450);
        set_skill("suohou-shou",450);
        set_skill("begging", 90);

        map_skill("force", "huntian-qigong");
        map_skill("parry","suohou-shou");
        map_skill("strike","lianhua-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("hand", "suohou-shou");
        prepare_skill("hand", "suohou-shou");
    	set("chat_chance_combat", 90);
    	set("chat_msg_combat", ({
        	(: perform_action, "hand.suohou" :),
        	(: perform_action, "hand.qinna" :),
        	(: exert_function, "huntian" :),
        }));

        create_family("ؤ��", 18, "�Ŵ�����");

        set("inquiry", ([
                "ؤ��" : "����ؤ�������µ�һ��\n",
                "�Ƿ�" : "�����������壬���ǵ�ǰ�ΰ�����\n",
				"�������þ���" : (: ask_suohou :),
        ]));
        setup();
        carry_object(ARMOR_D("bainayi"))->wear();
        carry_object(ARMOR_D("shoes"))->wear();
        carry_object(__DIR__"obj/gb_budai9")->wear();
}

void attempt_apprentice(object ob)
{
        if (ob->query("family/family_name")
        && ob->query("family/family_name") != "ؤ��") {
                command("say �㻹��ȥ������ɿ����ɡ�");
                return;
        }
        if ((int)ob->query("gb/bags") >= 2
         && ob->query("family/family_name") != "ؤ��" ) {
                command("say ؤ����ݲ��������ֱ��������С�ˣ�");
                command("kill "+ob->query("id"));
                return;
        }
        if ((int)ob->query("gb/bags") < 3 ) {
                command("say ���ڰ��е�������ǳ����Щ������˵�ɣ�");
                return;
        }
        if ( ob->query("shen") <0 || ob->query("shen") < ob->query("combat_exp")/2) {
                command("say �����Ϊʦ���ٶ���������°ɡ�");
                return;
        }
        command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
        "�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");
        command("recruit " + ob->query("id"));
        ob->set("title",sprintf(HIR"ؤ������%s������"NOR,
                chinese_number(ob->query("gb/bags"))) );
        ob->set("gb/fenduo","����");
        ob->set("class","beggar");
}

string ask_suohou()
{
        object me;
		int i,j,k;
        me = this_player();

        if ( me->query("family/family_name") != "ؤ��")
                return RANK_D->query_respect(me) +
                "����ؤ��ú�����֪�˻��Ӻ�̸��";

        //if ( me->query("family/master_name")!="������" && me->query("family/master_name")!="���߹�" )

			//return RANK_D->query_respect(me) +
               // "���������õ��ӣ��γ����ԣ�";
		if (me->query_skill("suohou-shou",1)<200)
		{
			return "��������ֵȼ�̫�ͣ�����200��������Ҳ��ⲻ�ˡ�\n";
		}
        if ( me->query("quest/gb/shs/qinna/pass"))
        	return "���Ѿ�ѧ��������\n��";

        if (time()-me->query("quest/gb/shs/qinna/time")<86400)
                return RANK_D->query_respect(me) +
                "������̫Ƶ���ˣ�\n";

        //list = filter_array(objects(), (: $1->query("id")=="fa dao":));
        
		command("consider ");
		command("say ����ʮ��·�������������ҳ��������ľ���\n");
		command("say һ��ʩչ���������в���Է�Ҫ����\n");
		command("say һ�Ź������ǡ������������һ������Է��ʺ��öԷ�������\n");
		command("say һ�ž�����������\n");
		command("say ���������Ϊ���Ҿʹ������㣬���������ϧ�����񼼣���Ҫ���ҽ�����\n");
	
        j = 15;
        if(me->query("m-card-vip")) j =  13;
        if(me->query("y-card-vip")) j =  10;
        if(me->query("buyvip"))     j =  5;
	    i=random(j);
	

	//Խ����ѧϰԽ�졣����
		k=random(me->query("kar"));
		if (me->query("kar")<31
			&&k>=23
			&&i<3)
		{
			message_vision(HIR"\n\n��ϲ�㣡�������������������þ����ľ����似��ϰ�����������־�����\n"NOR,me);
			command("chat* haha"+me->query("id"));
			command("chat "+me->query("name")+"������ô��ʱ�����������ˡ����������־���������ϲ�ɺء�");
			command("chat "+"��ؤ���ֶ���һ���ú���");
			command("chat* congra"+me->query("id"));
	  
	   log_file("quest/suohoushou",sprintf("%s(%s)�����Ԫ�㲥���������������־�������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),k,j,me->query("quest/gb/shs/qinna/fail"),me->query("combat_exp"),me));
	   
	   me->set("quest/gb/shs/qinna/pass",1);
	   //me->set("title",HIY"NOR);
	   return "���������֣�һ��ϰ�ã�����������\n";
	}
	else
	{
		message_vision(HIC"\n\n$N��Ȼ�����Ԫ˵�������ֵľ�Ҫ�����������ʹ�õľ�������һʱ֮��ȴ��������⡣\n"
		+"������������û�з��ӳ����������㻹���д������¸����Ԫ����ˡ�\n"NOR,me);
		log_file("quest/suohoushou",sprintf("%8s%-10s�õ����Ԫ������ָ�����������֣�����û�гɹ�������Ŭ������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),k,j,me->query("quest/gb/shs/qinna/fail"),me->query("combat_exp"),me));
		me->add("quest/gb/shs/qinna/fail",1);
		me->set("quest/gb/shs/qinna/time",time());
		return "��ԭ��һֱ��Ϊ������ģ�û�뵽����Ҹ�����\n";
	}  
   
}
