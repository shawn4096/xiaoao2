// zhou-zhiruo.c
// Lklv 2001.10.18 update hehe С�

inherit F_MASTER;
inherit NPC;
#include <ansi.h>

int ask_zhang();
int ask_dragon();
int do_jiuyin();
void create()
{
	set_name("������", ({ "zhou zhiruo", "zhou", "zhiruo"}));
	set("long", "�������ʦ̫�İ˴��׼ҵ���֮һ��һ����ɫ�������Եĳ������ˡ�\n");
	set("gender", "Ů��");
	set("attitude", "friendly");
	set("age", 25);
	set("shen_type", -1);
	set("str", 42);
	set("int", 42);
	set("con", 42);
	set("dex", 42);
	set("per", 40);

        set("max_qi", 15000);
        set("max_jing", 5000);
        set("neili", 15000);
        set("max_neili", 15000);
        set("jiali", 250);
        set("combat_exp", 9500000);
        set("score", 100);

        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
                (: perform_action, "claw.jiuyin" :),
					(: perform_action, "whip.chanrao" :),
					(: perform_action, "whip.feilong" :),
		}));

        set_skill("literate", 350);
	    set_skill("sword", 350);
        set_skill("parry", 450);
        set_skill("dodge", 450);
        set_skill("force", 480);
        set_skill("strike", 350);
		set_skill("sixiang-zhang", 350);
		set_skill("hand", 350);
		set_skill("jieshou-jiushi", 350);
        set_skill("claw", 480);
        set_skill("anying-fuxiang", 450);
        set_skill("jiuyin-baiguzhua", 480);
	    set_skill("huifeng-jian", 350);
        set_skill("dacheng-fofa", 150);
        set_skill("linji-zhuang", 480);
		set_skill("yinlong-bian", 480);
		set_skill("whip", 450);
        set("apply/attack", 50);
        set("apply/dexerity", 50);
        create_family("������", 3, "�׼�������");

        map_skill("force", "linji-zhuang");
        map_skill("parry", "yinlong-bian");
        map_skill("claw", "jiuyin-baiguzhua");
        map_skill("sword", "huifeng-jian");
        map_skill("dodge", "anying-fuxiang");
		map_skill("whip", "yinlong-bian");
		map_skill("strike", "sixiang-zhang");
		map_skill("hand", "jiehshou-jiushi");
		  
        prepare_skill("claw", "jiuyin-baiguzhua");

        set("inquiry",([
		"���޼�" : (: ask_zhang :),
		"���������޼���" : (: do_jiuyin() :),
		"������" : (: ask_dragon :),
		"�������" : (: ask_dragon :),
        ]) );
        //create_family("������", 4, "����");

        setup();
		carry_object("clone/weapon/whip/whip")->wield();
        carry_object("/d/emei/obj/shoes")->wear();
        carry_object("/d/emei/obj/cloth")->wear();
}
int prevent_learn(object ob, string skill)
{
	if (skill == "jiuyin-baiguzhua"||skill == "yinlong-bian")
		return 1;
	return 0;
}

void attempt_apprentice(object ob)
{
        if (! ob->query("family")) {
		command("say ����Ҷ����ɵ��ӣ��Ҳ������㡣\n");
		return;
        }
        if ((int)ob->query_skill("claw", 1) < 100 ) {
		command("say �����צ�����δ��100���Ҳ������㡣\n");
		return;
        }
        if ((int)ob->query_skill("strike", 1) < 100 ) {
		command("say ������Ʒ����δ��100���Ҳ������㡣\n");
		return;
        }
	if (ob->query("class") == "bonze"){
		command ("blush");
		command ("say ��ֻ���׼ҵ��ӡ�");
		return;
	}
        if ((int)ob->query_skill("jiuyin-baiguzhua", 1) < 100 ) {
		command("say ���צ��̫���ˣ�����100�������ڲ�����ͽ��\n");
		return;
        }
        command("recruit " + ob->query("id"));
        command("chat* grin");
		command("chat "+ob->query("name")+"�Ժ�����ҵ����ˣ���������ͬ����СŮ�Ӹ�����,���߽���֮�ʣ�������չ�!\n");
		command("chat* heng");
		command("chat �����˵����۸��ҵ��ˣ��Ҵ��ü�ɲ��Ǻ��ǵģ�!\n");
        command("chat* grin");
}

int ask_zhang()
{
	object me=this_player();
	if( me->query_temp("jiuyin140") == 2 ) {
		command("blush");
		command("say ��Ȼ���Ѿ����Ĳ���ϲ������������Ӱ����ʱ�޿̲��������ҵ��Ժ��\n");
		command("say ���վ�������ƭ�Լ�����������ƭʦ����ʦ���̸��ҵ��������������ܺ͹�����ɵ��뷨�վ��ǲ���ʵ���ˡ�\n");
		command("sigh");
		me->set_temp("jiuyin140", 3 );
		return 1;
	}
	message_vision("����������$Nһ�ۡ�\n", me);
	return 1;
}

int ask_dragon()
{
	object me=this_player();
	if( me->query_temp("jiuyin140") >= 3 ) {
		if( me->query("family/master_name") != "������"
	 	 && !me->query_skill("jiuyin-baiguzhua",1) ) {
			command("say �����ڲ����ҵ�ͽ�ܣ�Ҳû�д�������ѧ��ʲô��������ƾ�����ڵ��书����������������ģ�Ҳ�͸�̸���Ϲ������ˡ�\n");
			return 1;
		}
		command("say ��Ȼ��ˣ��㵽��ʦ������ѯ���������������ܰɡ�\n");
		command("say �����ҵ�ϣ��ֻ�ܼ��������ˡ�\n");
		command("sigh");
		me->set_temp("jiuyin140", 4 );
		return 1;
	}
	message_vision("�����������ؿ���$Nһ�ۣ�ҡ��ҡͷ��\n", me);
	return 1;
}

//˵��Ե�ɣ�Ȼ��ȥ��һ���ط���������ȥ

int do_jiuyin() 
{
	object me = this_player();
	
	if(this_object()->is_fighting()) return 0;
	
	if(me->query("family/family_name")!="������")
		if (!me->query_temp("ryb/jiuyin_askdue")) //�����ɶɶ��Ƽ�������һ��
		{
			command("heng "+me->query_id());
			command("say �����������ʲô��ϵ���Ͻ����ҹ���");
			return 1;
		}
	if(me->query("shen")<0)
	{
		command("heng "+me->query_id());
		command("say �������������ɣ��Ͻ����ҹ���");
		return 1;
	}
	if(me->query("quest/em/zzr/pass"))
	{
		command("heng "+me->query_id());
		command("say ���Ѿ������������޵������ڻ��ͨ������ǲ��ô��");
		return 1;
	}
	
	 message_vision(HIC"$N��$n����й������޷���ʹ�ü��ɡ�\n"NOR, me, this_object());
	
	 command("look "+me->query("id"));	
	

	
    
	me->set("quest/em/zzr/ylb/time",time());
	me->set("quest/em/zzr/ylb/combat_exp",me->query("combat_exp")); 
	
	command("sigh "+me->query("id"));
	command("think ");
	command("consider ");
	if (me->query_temp("ryb/jiuyin_askdue"))
	{
		command("mei ");
		command("say ��Ȼ�����ֶɶ��ʦ���������Ҿ͸��㽲��һ�¡�\n\n\n");
	}
	command("say ���Ǿ����澭�����ص��书����Ȼ���Ѿ�ϰ���������书�����ҾͰ��⵱�еľ���˵����������");
    command("say ͽ���������������޵�ʹ�ü�������Ϊʦ������Ѫ���ã���Ҫ�ú������ˡ�\n");
	command("say �����ұ���ʦ����־���İѱ�������������书��Ѱ�һ�����������һ�죬��Ե�ɺϡ�\n");
	command("say ���ҵõ����������������콣������֪�������е����ܡ��������Ű�ʧ����ؼ�Ѱ�һ���\n");
	command("say �����ҶԵ���ʦ��������֮���ˡ�\n");
	command("say �������ģ��Ұ������ķ������ڲؾ�¥������ȥ����,�ܷ�õ��Ϳ���Ļ�Ե�ˡ�\n");
	command("whisper "+me->query("id"));
	
	command("smile "+me->query("id"));
	me->set_temp("quest/em/zzr/askzhou",1);
	return 1;
}