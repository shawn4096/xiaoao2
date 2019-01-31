// yingying.c
// Finish by action@SJ 2009.1.6
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_chong();
string ask_ling();
int do_answer(string arg);
string ask_sanshi();
string ask_qingxinzhou();
void create()
{
        
        set_name("��ӯӯ", ({ "ren yingying","ren","yingying" }));
        set("long", "����ò�������ף�����ʮ�߰�����ͣ�����̬֮���������ɷ��\n");
        set("nickname", HIC"С��Ů"NOR);
        set("title", HIY"�������  ʥ��"NOR);
        set("gender", "Ů��");
        set("attitude", "peaceful");
        set("age", 18);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 30);
        set("unique", 1);
        set("location", 1);
        set_temp("no_return", 1);

        set("max_qi", 15000);
        set("qi", 15000);
        set("jing", 6300);
        set("max_jing", 6300);
        set("neili", 19000);
        set("max_neili",19000);
        set("eff_jingli", 5700);
        set("jingli", 5700);
        set("jiali", 200);
        set("combat_exp", 9800000);
        set("shen", -1200);

        set_temp("apply/attack", 40);
        set_temp("apply/defence", 40);

        set_skill("tianmo-zhang",400);
        set_skill("mantian-huayu",400);
        set_skill("qingxin-jian",450);
        set_skill("strike", 400);
		set_skill("hand", 400);
        set_skill("parry", 400);
        set_skill("dodge",400);
        set_skill("huanmo-wubu", 400);
        set_skill("tianmo-shou", 400);
        set_skill("force", 400);
        set_skill("sword",450);
        set_skill("throwing",400);
        set_skill("tianmo-gong", 400);
        set_skill("tianmo-jue", 200);
        set_skill("art", 200);

        map_skill("strike", "tianmo-zhang");
        map_skill("hand", "tianmo-shou");
        map_skill("throwing", "mantian-huayu");
        map_skill("sword", "qingxin-jian");
        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
        map_skill("parry", "qingxin-jian");
        prepare_skill("hand", "tianmo-shou");
        set("inquiry", ([
			 "�����": (: ask_chong :),
		     "��ľ��": (: ask_ling :),
			 "��ʬ����": (: ask_sanshi :),
		     "����������": (: ask_qingxinzhou :),

        ]));

        create_family("�������", 8, "����");
        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chaofeng" :),
				(: perform_action, "sword.qingxin" :),

                (: exert_function, "tianmo" :),
        }));

        setup();

        carry_object("/clone/misc/cloth")->wear();     
        carry_object(("clone/weapon/duanjian"))->wield();    
}

void init()
{
	object ob;
	::init();
	ob = this_player();
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object me)
{
	
	object chong;
	me=this_player();
	if(!me) return;
    if (present("heimu ling",me)) 
    {
		command("angry "+me->query("id"));
        return;
    }

	if (!me->query_temp("hostage/passed_l")) return;

	//hmling->move(this_object());

	if ( file_name(environment(this_object())) != "/d/changan/xiaoshe") return;
    
	
    if(objectp(chong=present("linghu chong",environment(me)))){
		command("chat* blush");
		command("chat ��磬��û�뵽��Ȼ�ּ������ˣ�\n");
		message_vision(HIY"������ӯӯ��һ����˵��Ц�����ǿ��ġ�\n"NOR,me);
        command("thank " + me->query("id"));
		command("say ��Ȼ��λ" + RANK_D->query_respect(me)+"���Ҽ����˳�磬�ҾͰ�����ľ���͸��㵱�������ˡ�\n");
		//command("give "+me->query("id")+" heimu ling");
        new("/d/hmy/npc/obj/heimuling")->move(me);
		me->set_temp("hostage/linggived",1);
		me->delete_temp("hostage/passed_l");
		
		if (me->query_temp("qxj/askren"))
		{
			message_vision(HIC"��ӯӯ��$NЦ��������Ȼ��������ģ��ҾͰ�������������ĵ���˵�����������������ˡ���\n"NOR,me);
			me->set("quest/hmy/qxj/qingxin/pass",1);

		}
		message_vision(CYN"�������Ѿ������굱ǰ���ˣ��ͺ�ӯӯЯ���뿪��ȥ,����һ�����ɾ��¡�\n"NOR,me);
		destruct(chong);
		return ;
	}
	

}


void attempt_apprentice(object ob)
{
     if(ob->query_skill("force",1) < 200 ||
      ob->query_skill("qingxin-jian",1) < 200 ||
        ob->query_skill("tianmo-shou",1) < 200){
        command("say ����书��������죬�ٻ�ȥ�����ɡ�");
        return;
        }
	 if (ob->query("family/family_name")!="�������")
	    return notify_fail("����˵��������ס��ľ�£���Ҳ�������յ��ӣ�\n");

     command("say �ã��������б�����Ƚ��������������㻹��������������ˡ�");
     command("recruit " + ob->query("id"));
     ob->set("title",HIW"�������ʥ�����µ���"NOR);
}

int ask_chong()
{
     object me=this_player();
  
     command("say ���ϴ�һ����Ҳû�м�����磬��֪��������������ʲô��\n");
	 command("blush "+me->query("id"));
	 command("say ���Ƿ�Ը��������һ�˻�ɽ��������һ���ţ�(answer ��/��)");
	 
	 me->set_temp("askyy/songxin",1);
	 add_action("do_answer","answer");
	 return 1;

}
int do_answer(string arg)
{
	 object me=this_player();
     object ob=this_object();
     if (!me->query_temp("askyy/songxin"))
       return notify_fail("������ʲô��\n");
	 if (!arg||arg!="Ը��")
	   return notify_fail("�������˵�˵�����ʲô��\n");
     if(arg == "��" || arg == "Ը��" ){
        me->delete_temp("askyy/songxin");
		me->set_temp("yy/songxin",1);
		me->set_temp("qxj/askren",1);
		message_vision(HIG"$N���˵�ͷ�������ơ��õģ�ʥ�ã���Ը������ȥ���ţ���\n"NOR,me,ob);
		
		message_vision(HIC"$n��$N���ˬ���Ӧ��������¶����֮ɫ��\n"NOR,me,ob);
		command("say �Ұ�����žͽ������ˣ�\n");
	    new("/d/hmy/npc/obj/letter")->move(me);
       return 1;
    }
    return 0;

}


string ask_ling()
{
     object me=this_player();
     object ling;
	 command("jump");
	 if (me->query("family/family_name")!="�������")
            { command("?");
	    return "�㲻������̵��ӣ���ľ������������ӵ�еģ�\n";
            }
	 if ((int)me->query_skill("tianmo-gong",1)<450)
		return "����ħ����̫ǳ����ľ������������ӵ�еģ�\n";
     command("say ��ľ��������̼�����ʥ֮��˽�������������������\n");
	 //ling=new("/d/hmy/npc/obj/heimuling");
     return "";

}
string ask_sanshi()
{
     object me=this_player();
     object dan;
	 if (me->query("family/family_name")!="�������")
	    return "�㲻������̵��ӣ���ʬ��������������ӵ�еģ�\n";
	 if (me->query_skill("tianmo-gong",1)<450)
		return "����ħ����̫ǳ��������ʬ����Ҳ���˷ѣ�\n";
     if (!me->query_temp("hostage/linggived"))
        return "��ʬ����������̹���֮�ƾʲôҪ���㣿\n";
	
	 command("say ��л�����ҳ�����ţ�����Ϊ������ö��ʬ���񵤾͸���ɡ�\n");
	 command("xixi");
	 message_vision(HIG"$n�ݸ�$N������ʬ����.\n"NOR,me,this_object());
	 me->delete_temp("hostage/linggived");
	 new("/d/hmy/obj/sanshidan")->move(me);
     new("/d/hmy/obj/sanshidan")->move(me);
     new("/d/hmy/obj/sanshidan")->move(me);
     return "";

}

string ask_qingxinzhou()
{
     object me=this_player();
     object dan;
	 if (me->query("family/family_name")!="�������")
	    return "�㲻������̵��ӣ��Ҳ���̸���ģ�\n";
	 if (me->query_skill("force",1)<200)
		return "���������̫ǳ��������Ҳ���˷ѣ�\n";
     if (me->query("quest/hmy/qxj/qingxin/pass"))
        return "�㲻���Ѿ��⿪������������İ�����ô��\n";
	 command("say ����������������һ���������ѧ����������Ȥ�������������ȣ�\n");
	 command("say ��ȥ���Ҹ�������ţ������������Ҿ͸����㡣\n");
	 command("xixi");
     me->set_temp("qxj/askren",1);	 
	 return "";

}
