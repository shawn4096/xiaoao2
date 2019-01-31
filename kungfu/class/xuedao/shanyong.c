// shanyong.c ����
// by iceland

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string ask_hongsha();

void create()
{
        set_name("����", ({ "shan yong", "shanyong" ,"shan","yong"}));
        set("long",@LONG
����Ѫ���������¶����ӣ�����ݸߣ���ɫ�����͵ģ�����һ�������۾�
��������Щ���ˡ�
LONG
        );
        set("title", HIR "Ѫ���������µ���" NOR);
        set("gender", "����");
		set("class", "huanxi");
        set("age", 42);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 28);
        set("int", 15);
        set("con", 28);
        set("dex", 28);
        set("max_qi", 21000);
        set("eff_jing", 6400);
        set("max_jing",6400);
		set("neili", 21300);
        set("max_neili", 21300);
        set("jiali", 180);
        set("combat_exp", 9400000);
        set("score", 40000);
		set("unique", 1);

        set_skill("huanxi-chan", 180);
        set_skill("literate", 180);
        set_skill("force", 450);
        set_skill("xuedao-jing", 450);
        set_skill("dodge", 450);
        set_skill("xueying-dunxing", 100);
      //  set_skill("hand", 450);
       //set_skill("hongsha-shou", 450);
        set_skill("strike", 100);
        set_skill("hongsha-zhang", 450);
        set_skill("parry", 450 );
        set_skill("xuedao-daofa", 450);
        set_skill("blade", 450 );

        map_skill("force", "xuedao-jing");
        map_skill("dodge", "xueying-dunxing");
      //  map_skill("hand", "hongsha-shou");
        map_skill("parry", "xuedao-daofa");
        map_skill("strike", "hongsha-zhang");

       // prepare_skill("hand","hongsha-shou");
        prepare_skill("strike","hongsha-zhang");
		set("inquiry",([
		"��ɰ�ƾ���"	: (: ask_hongsha :),
		//"test"	: (: ask_test :),
	

		]));

        create_family("Ѫ����", 5, "����");
        set("class", "huanxi");

        setup();
        carry_object("/d/xueshan/npc/obj/gongde-jiasha")->wear();
        carry_object(BINGQI_D("miandao"))->wield();      

        add_money("silver",50);
}
string ask_test()
{
	command("say teset");
	//return notify_fail("tete");
	return "111";
}
void attempt_apprentice(object ob)
{
        if ((string)ob->query("family/family_name") != "Ѫ����") {
               command("say"+ RANK_D->query_respect(ob) +
                        "���Ǳ��ŵ��ӣ������ﵷʲô�ң���");
                return;
        }

        if ((int)ob->query_skill("huanxi-chan", 1) < 150) {
                command("say ��ϲ���Ǹ����书֮��������150�������ڼ������ɡ�");
                command("say"+ RANK_D->query_respect(ob) +
                        "�ٰ�����ͨ��������������б��ŵ��ķ��ɡ�");
                return;
        }
        if ((int)ob->query_skill("jingang-liantishu", 1) < 200) {
                command("say ����������Ǹ����书֮��������200�������ڼ������ɡ�");
                command("say"+ RANK_D->query_respect(ob) +
                        "�ٰ�����ͨ���������ϰ�ɡ�");
                return;
        }

        if ((int)ob->query_skill("xuedao-jing", 1) < 200) {
                command("say Ѫ�����Ǹ����书֮��������200�������ڼ������ɡ�");
                command("say"+ RANK_D->query_respect(ob) +
                        "�ٰ�����ͨ���������ϰ�ɡ�");
                return;
        }
        if (!ob->query("quest/xd/dichuan")) {
                command("say ��û�еմ���ݣ��Ҳ������㡣");
                return;
        }

        command("say �ðɣ��Ժ���ͺú��̷��ү�Ұɡ�");
        command("recruit " + ob->query("id"));

       // ob->set("title", HIR "Ѫ���ŵ���������" NOR);
}


string ask_hongsha()
{

	object me;

	int i,j; 
	me = this_player();

	if(!me) return 0;
	
	i=random(me->query("kar"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	j=random(j);
	
	if (me->query("family/family_name")!="Ѫ����")
	{
		return "�㲻��Ѫ���ŵ��ӣ�������ǲ��ô��\n";
	}

	if (me->query("quest/xd/hongsha/pass"))
	{
		
		return "���Ѿ��⿪�˺�ɰѪ����������⣬����Ե�޹���������������\n";
	}


	if (time()-me->query("quest/xd/hongsha/time")<86400)
	{
		return "������̫Ƶ���ˣ��书��ɻ��������ꣿ��\n";
	}
	if (!me->query("quest/xd/dichuan"))
	{
		return "Ѫ����Ҫ����ʼ����һ���ҳϵ��ӣ���ǵմ������ܴ�����߼��书����\n";
	}
	if (me->query_skill("force",1)<200)
	{
		return "��ϰ�����ڹ���Ҫ��200������ϰ��ɰ�ƾ��������Ǻú�����ȥ�ɣ���\n";
	}
	if (me->query_skill("hongsha-zhang",1)<250)
	{
		return "��ϰ��ɰ�Ʒ���Ҫ��250������ϰ��ɰ�ƾ��������Ǻú�����ȥ�ɣ���\n";
	}

	if (i>25
	  && j<6
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 message_vision(HIB"\n$Nĥ�˰��죬������Ѩ��Ȼһʹ�����ɰѪ���������Ȼ��ͨ����\n"NOR,me); 
         message_vision(HIY"\n$N���д�ϲ�����������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N����������ĥ��ϰ����������������ɮ�����ڵĺ�ɰѪ�����İ��أ���\n"NOR,me); 
         log_file("quest/xdhongsha", sprintf("%s(%s) ��ɰѪ�������ܳɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ������ɰѪ�������İ��أ��������ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/hongsha/fail"),
		 i,
		 j,
         me->query("combat_exp"),
		 ));

		 me->set("quest/xd/hongsha/time",time());
		 me->set("quest/xd/hongsha/pass",1);
		 return "��ϲ��ϲ���Ҵ�Ѫ��ǰ;����\n";
     }
	 else {
	     message_vision(HIG"\n$N�����ɥ�����������˵�������������ɰѪ�������ǲ��ýⰡ������Ŭ���ɡ���\n"NOR,me); 
		 message_vision(HIY"\n�����ɰѪ������������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/xdhongsha", sprintf("%s(%s) ʧ�ܣ������ɰѪ������%d��ʧ�ܣ��������ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/hongsha/fail",1),
		 i,
		 j,
         me->query("combat_exp"),));        
		 me->add("quest/xd/hongsha/fail",1);
		 me->set("quest/xd/hongsha/time",time());
		 me->start_busy(2);
		 me->delete_temp("quest/xd/hongsha/modao");
		 me->delete_temp("quest/xd");
		 return "���Ƿ��\n";
   }
	

}