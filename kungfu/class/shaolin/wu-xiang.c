// Npc: wuming-laoseng
inherit NPC;
inherit F_MASTER;
#include <ansi.h>

string ask_wx();
int ask_wj();
mixed ask_ff();
int ask_wxjj(); 
void create()
{
        set_name("������ʦ", ({"wuxiang chanshi", "wuxiang", "chanshi",
        }));
        set("long",
                "����һλ�����۵Ŀ���ɮ�ˣ���ľ��ݡ�\n"
                "�뷢��Ȼȫ�ף�Ҳ������������͡�\n"
        );


        set("gender", "����");
        set("attitude", "friendly");
        set("class", "bonze");
        set("no_bark",1);

        set("age", 80);
        set("shen", 32000);
        set("str", 40);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 8000);
        set("max_jing", 7000);
        set("eff_jingli", 4000);
        set("neili", 25000);
        set("max_neili", 25000);
        set("jiali", 100);
        set("combat_exp", 6000000);

        set_skill("force", 550);
        set_skill("yijin-jing", 550);
        set_skill("dodge", 550);
        set_skill("shaolin-shenfa", 550);
        set_skill("parry", 550);
        set_skill("finger", 550);
        set_skill("buddhism", 220);
        set_skill("literate", 550);
	    set_skill("wuxiang-zhi",550);
	    set_skill("cuff",550);
	    set_skill("luohan-quan",550);

        map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "wuxiang-zhi");
	    map_skill("cuff","luohan-quan");

        prepare_skill("finger", "wuxiang-zhi");
	    prepare_skill("cuff", "luohan-quan");

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "finger.qiankun" :),
        }));

        create_family("������", 34, "����");
	    set("inquiry", ([
		"�����似": (: ask_wj :),
		"�����ָ": (: ask_wx :),
		"�������": (: ask_wxjj :),
		"��": (: ask_ff :),
	]));

        setup();
        set_temp("apply/damage", 50);
        set_temp("apply/dodge", 100);
        set_temp("apply/attack", 80);
        set_temp("apply/armor", 60);
	UPDATE_D->get_cloth(this_object());
	set("no_quest", 1);
}

void attempt_apprentice(object ob)
{
	command("say �Բ����������ڲ���ͽ��");
	return;
}
/*
string ask_wj()
{
	object me=this_player();
   
	if(me->query("wxz/quest") < 4) return 0;
	
	if( me->query("wxz/quest")== 4 && random(me->query("kar"))>=27)
		me->set("wxz/quest",5);
	return RANK_D->query_respect(me)+"�ο�̰����ѧС������֪�ȱ�Ϊ���������޳�������\n"
		+"������Ȼ�����������Ҳ��������Ե�������������ָ���㴫�˸���ɡ�\n";
}
*/
string ask_wj()
{
	object me=this_player();

	if(me->query("wxz/done"))
		return RANK_D->query_respect(me)+"�����Ѿ�ѧ����ô��\n";

	if(me->query("wxz/quest")<5)
		return "";
	if( me->query("wxz/quest")== 5)
		me->set_temp("wxz/done",1);
        command("say ����Գ�����ָ���ľ����������ϵ�ľм����������ĵá�");

	   // log_file("quest/wuxiang", sprintf("%8s%-10s ��������ʦ��ѧ�������ָ��\n",
	//	me->query("name"), "("+me->query("id")+")" ), me);
	    
	    return "ֻ��ľƬԾ�����������ࡣ����Ҫ������ʵ�������������࣬�������֮����Ҳ�����гɡ�";
}

mixed ask_ff()
{
	object me=this_player();

	if (!me->query("potential")) return "���Ǳ�ܲ����ˡ�";
	if (!me->query("wxz/poison")) return RANK_D->query_respect(me)+"�𷨾���Ļ��ȱ�����Ŀǰʵ��û��ʲô���Խ���ġ�";

	do if (me->add("wxz/poison",-2-random(2)) < 0) {
		me->set("wxz/poison",0);
		break;
	}
	while (me->add("potential",-4-random(2)) > 0);
	if (me->query("potential") < 0) me->set("potential",0);
	command("say ���ļ��𣬼����ģ�����ʶ��ʶ�����ģ����ķǷ������ġ���");
	command("buddhi wuxiang chanshi");
	tell_object(me,"��������ã���������\n");
	return 1;
}
int ask_wxjj() 
{
	object me = this_player();
	int i;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N��$n����й������ָ�������������\n"NOR, me, this_object());
	
	if(!me->query("wxz/done")||!me->query("wxjz/pass"))
	{
		command("?");
		command("say ���������ָ��ʲô��������֪����������̸������"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	command("look "+me->query("id"));	
	//��ͨ�������
   if(me->query("wxjz/jueji"))
	{
	
		command("say "+me->query("id"));
		command("say ���Ѿ��⿪��������ˣ�����������ɮ���ǲ��ǳԱ��ˣ�\n");
		me->set("title",HIR"����"HIW"��ɫ"HIY"��ʦ"NOR);
		me->set("mytitle/quest/wusewuxiangtitle",HIR"����"HIW"��ɫ"HIY"��ʦ"NOR);
		return 1;
	}
	if(me->query("wxzjj/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say �Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		command("puke "+me->query("id"));
		return 1;
	}
	//�书ѧϰ֮����Ҫ���һ�죬������Ҫ���50K
	if( time()-me->query("wxzjj/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say �����Ƚ̵�������ɣ�����ɡ�");
		return 1;
	}
	if(me->query("combat_exp")<5000000)
	{
		command("look "+me->query("id"));
		command("say ���㵱ǰ�ľ�����»����������򣬻���ץ��ȥ����ȥ�ɡ�");
		return 1;
	}
    
	me->set("wxzjj/time",time());
	me->set("wxzjj/combat_exp",me->query("combat_exp")); 
	i= random(20);
	command("sigh "+me->query("id"));
	command("say �������Ρ���Ȼ����������Ҿ�˵����������������û����������ˡ�");
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));
	if(i==3 
	  && random(me->query("kar"))>27
	  && random(me->query("int"))>35
	  && me->query("kar")<31)
	{
		tell_object(me,HIY"\n�㰴��������ʦ��ָ�㣬�������ָ�����������ƺ���Щ�ĵá�\n"NOR);
		tell_object(me,HIW"\n���ȴӡ�����ʽ����ʼ������һ·�����������������硣\n"NOR);
       
		
		//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("buddha "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("title",HIR"����"HIW"��ɫ"HIY"��ʦ"NOR);
		me->set("mytitle/quest/wusewuxiangtitle",HIR"����"HIW"��ɫ"HIY"��ʦ"NOR);
		me->set("wxjz/jueji",1);
		log_file("quest/wxjueji", sprintf("%8s(%8s) ʧ��%d�γ������������ָ�ľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("wxzjj/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("wxzjj/fail",1);
		command("buddha");
		tell_object(me,HIY"������������ʦ��ָ�㣬��Ȼ�����������ָ����ʽ�����Ƕ������ָ����������ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/wxjueji", sprintf("%8s(%8s) �����ָ��������ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("wxzjj/fail"),i,me->query("combat_exp")) );
	}
	return 1;
}


int ask_wx() 
{
	object me = this_player();
	int i;
	if(this_object()->is_fighting()) return 0;

	message_vision(HIG"$N��$n����й������ָ�İ��ء�\n"NOR, me, this_object());
	
	if(me->query("wxz/done"))
	{
		command("smile "+me->query("id"));
		me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		
		return 1;
	}
	if (!me->query_temp("wxz/done"))
	{
		command("say ������ô��������ģ�����ԭ�������ߣ�������ʦ�����似������ѯ�������ָ��\n");
	    return 1;
	}
	command("look "+me->query("id"));	
	//��ͨ�������
	if(me->query("wxjz/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say �Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		command("puke "+me->query("id"));
		return 1;
	}
	//�书ѧϰ֮����Ҫ���һ�죬������Ҫ���50K
	if( time()-me->query("wxjz/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say �����Ƚ̵�������ɣ�����ɡ�");
		return 1;
	}
	if(me->query("combat_exp")<5000000)
	{
		command("look "+me->query("id"));
		command("say ���㵱ǰ�ľ�����»����������򣬻���ץ��ȥ����ȥ�ɡ�");
		return 1;
	}
    
	me->set("wxjz/time",time());
	me->set("wxjz/combat_exp",me->query("combat_exp")); 
	i= random(15);
	command("sigh "+me->query("id"));
	command("say �������Ρ���Ȼ����������Ҿ�˵����������������û����������ˡ�");
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));
	if(me->query("kar")<31 
		&& random(me->query("kar"))>=27
		&&i==2)
	{
		tell_object(me,HIY"\n�㰴��������ʦ��ָ�㣬�������ָ�ƺ���Щ�ĵá�\n"NOR);
		tell_object(me,HIW"\n���ȴӡ�����ʽ����ʼ������һ·�����������������硣\n"NOR);
		tell_object(me,HIR"\n��Ȼ�䣬��ʳָһ�ɾ�����ӿ��������������ǿ���仯Ī�⣬���˷���ʤ����\n"NOR);
		tell_object(me,HIC"\n��ϲ�㣡����ǧ����࣬��������Ը�Գ���ϰ�����־��������ָ��\n"NOR);
		//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("buddha "+me->query("id"));
		command("haha "+me->query("id"));
		//me->set(QUESTDIR4+"sword",1);
		me->set("wxjz/pass",1);
		me->set("wxz/done",1); 
		me->set("title",HIR"�����ָ����"NOR);
		me->set("mytitle/quest/wxjztitle",HIR"�����ָ����"NOR);
		log_file("quest/wxjz", sprintf("%8s(%8s) ʧ��%d�γ������������ָ��iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("wxjz/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("wxjz/fail",1);
		//me->set("wxjz/");
		command("buddha");
		tell_object(me,HIY"������������ʦ��ָ�㣬��Ȼ�����������ָ����ʽ�����Ƕ������ָ����������ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/wxjz", sprintf("%8s(%8s) �����ָ��������ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("wxjz/fail"),i,me->query("combat_exp")) );
	}
	return 1;
} 