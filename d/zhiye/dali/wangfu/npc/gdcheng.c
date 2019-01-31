// gdcheng.c
// Modify By River 98/12 
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_jueji();

void create()
{
        set_name("���Ƴ�", ({ "gu ducheng", "gu", "ducheng" }));
        set("title", "��������������ҽ�");
        set("gender", "����");
        set("age", 33);
        set("str", 37);
        set("dex", 26);
        set("per", 20);
        set("long", "�������������ֳ������師���������ݡ�\n");
        set("combat_exp", 4500000);
        set("shen_type", 1);
        set("attitude", "friendly");
        //create_family("����", 3 , "����");
		create_family("������", 15 , "�׼ҵ���");
        set_skill("cuff", 90);
        set_skill("qiantian-yiyang", 350);
        set_skill("tianlong-xiang", 350);
        set_skill("pangen-fu", 350);
        set_skill("duanjia-quan", 350);
        set_skill("force", 350);
        set_skill("axe", 350);
        set_skill("dodge", 350);
        set_skill("parry", 350);
        set_temp("apply/attack", 70);
        set_temp("apply/defense", 70);
        set_temp("apply/armor", 70);
        set_temp("apply/damage", 20);
        map_skill("force", "qiantian-yiyang");
        map_skill("cuff", "duanjia-quan");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "pangen-fu");
        map_skill("axe", "pangen-fu");
        prepare_skill("cuff","duanjia-quan");
        set("chat_chance_combat", 30);
	    set("chat_msg_combat", ({
				(: exert_function, "yiyang" :),
                (: perform_action, "axe.pangen" :),
				(: perform_action, "axe.cuojie" :),
				(: perform_action, "axe.jingtian" :),
        	       
	    }));
		set("inquiry", ([
				"�̸���ھ���" : (: ask_jueji :),
		]));
        set("max_qi", 15000);
        set("neili", 6000); 
        set("max_neili", 6000);
        set("jing", 6600);
        set("max_jing", 6060);
        set("eff_jingli", 6600);
        set("jiali", 150);

        setup();
        carry_object(__DIR__"obj/banfu")->wield();
        carry_object("/d/dali/npc/obj/zipao")->wear();
}

void attempt_apprentice(object ob)
{
	
	if ((string)ob->query("gender") != "����" ){
		command ("say ����������Ů���ӻ򹫹����������ң�");
		return;
	}
	if ((string)ob->query("class")=="bonze" ){
		command ("say �����ӷ��Ҳ��ճ��ҵ��ӡ�");
		return;
	}
	if ((int)ob->query_skill("qiantian-yiyang", 1) < 200 ){
		command("say ��ĳ���Ҳ�����������֮�ˣ��㻹�Ƕ��������Ǭ��һ����200�ɡ�");
		return;
	}
	if ((int)ob->query_skill("duanjia-quan", 1) < 200 ){
		command("say ��ĳ���Ҳ�����������֮�ˣ��㻹�Ƕ�������Ķμ�ȭ��200�ɡ�");
		return;
	}
	if ((int)ob->query_skill("force", 1) < 200 ){
		command("say ��ĳ�˲�����������֮�ˣ��㻹�Ƕ�������Ļ����ڹ���200�ɡ�");
		return;
	}
	if ((int)ob->query("shen") < 20000){
		command("say ������������������ɣ��㲻��20k����������ҡ�");
		return;
	}
    if( (int)ob->query("family/generation")<15){
		command("sigh ");
		command("say "+RANK_D->query_respect(ob)+"���Ѿ���ǰ����ʦ�̵�������������Ϊͽ��");
		return;
	}
	command("say �治���һ�����ӣ���ʦ��һ���书�㶼�ڰѸ�ͷ�ϣ����Ժ��Ҫ�ú������ˡ�\n");
	command("say ��Ȼ��Ե�Ҿ��������ˣ�\n");
	command("haha ");
	command("recruit " + ob->query("id"));
	//ob->set("title", "�����µ�ʮ�����׼ҵ���");
	return;
}

string ask_jueji()
{
	object me;
	int i,j;

	me=this_player();
	if (me->query_skill("axe",1)<200)
	{
		command("say ��Ļ�����������200��������Ҳѧ���ᣡ\n");
		return "˭�ĸ�ͷ��˭��˵���㣡\n";
	}
	if (me->query("quest/tls/pgf/pangen/pass"))
		return "�㲻���Ѿ����̸���ھ���ѧ����!\n";
	if (me->query_skill("pangen-fu",1)<200)
	{
		command("say ����̸���ڸ�������200��������Ҳѧ���ᣡ\n");
		return "˭�ĸ�ͷ��˭��˵���㣡\n";
	}
	if (time()-me->query("quest/tls/pgf/pangen/time")<86400)
		return "������̫Ƶ���ˣ��������书����������\n";
	if (me->is_busy())
		return "��������æ�����У�\n";
		command("say �̸���ڸ������ҵĿ��ұ��죬ȫƾһ��������ת������ѧ�Ҿ͸����㣿\n");
		command("say ��С�ӣ���Ȼ��������ã��������ˣ�\n");
		  j = 20;
		  if(me->query("m-card-vip")) j =  18;
		  if(me->query("y-card-vip")) j =  15;
		  if(me->query("buyvip"))     j =  10;
		  i=random(j);

		  if (i<5 
			 && me->query("kar")<31
			 && random(me->query("kar"))>24)
		  {       
			  tell_object(me,HIC"\n�㰴�չ��Ƴϵ�ָ�㽫��������ע���ֱ��У����еĸ�ͷ��ʱ������࣡\n"NOR);
			  message_vision(HIR"\n$N�����ʹ�������ͷ�ļ���һ���ӻ�Ȼ��ͨ����\n"NOR,me); 
			  tell_object(me,HIG"��ϲ�������̸���ڸ������ɹ���\n"NOR);
			  me->set("quest/tls/pgf/pangen/pass",1);
			  log_file("quest/tlspangen", sprintf("%s(%s) ʧ��%d�γɹ��⿪�̸�������Դ��%d�����飺%d��\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/tls/pgf/pangen/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			  me->start_busy(1);
			}
			else
			{
			 tell_object(me,HIG"\n���˼��ã�����Ҫ�졣\n"NOR);
			 message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿���,�����Լ���ʵ�����ˡ�\n"NOR,me); 
			 tell_object(me,HBBLU"\n�ܿ�ϧ���㱾�γ����̸���������ʧ�ܣ�\n"NOR);
			 tell_object(me,HBBLU"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
			 tell_object(me,HBBLU"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
			 log_file("quest/tlspangen", sprintf("%s(%s) �����̸�������ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/tls/pgf/pangen/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			 me->add("quest/tls/pgf/pangen/fail",1);
			 me->set("quest/tls/pgf/pangen/exp", me->query("combat_exp") );
			 me->start_busy(1);
			 me->set("quest/tls/pgf/pangen/time",time());
			}
		me->delete_temp("quest/tls");
		return "һ��ͷ�͹��ˣ�\n";
	 
		
}