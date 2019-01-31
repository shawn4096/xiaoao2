// sun.c �ﲻ��

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_chongyang();
string ask_baojian();

void create()
{
        set_name("�ﲻ��", ({"sun buer", "sun"}));
        set("gender", "Ů��");
        set("age", 33);
        set("class", "taoist");
        set("nickname",CYN"�徻ɢ��"NOR);
        set("long",
                "������ȫ��̶���������Ψһ��Ů�����ﲻ�������ˡ�������\n"
                "�������ǰ�����ӣ�����������һ������ͷ��\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 30);
        set("int", 29);
        set("con", 29);
        set("dex", 29);
		//set("");
        set("title","ȫ������֮ĩ");

        set("qi", 23700);
        set("max_qi", 23700);
        set("jing", 4800);
        set("max_jing", 4800);
        set("neili", 14100);
        set("max_neili", 14100);
        set("jiali", 200);

        set("combat_exp", 9600000);

        set_skill("force", 450);
        set_skill("xiantian-gong", 450);
        set_skill("sword", 450);
        set_skill("quanzhen-jianfa",450);
        set_skill("dodge", 450);
        set_skill("jinyan-gong", 450);
        set_skill("parry", 450);
        set_skill("strike", 450);
        set_skill("haotian-zhang", 450);
        set_skill("literate",200);
        set_skill("taoism",200);
	    set_skill("tiangang-beidouzhen", 450);
		set_skill("whip",450);
		set_skill("qiufeng-chenfa",350);
		set_skill("leg", 200);
        set_skill("yuanyang-lianhuantui", 450);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
		map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("strike","haotian-zhang");
		prepare_skill("leg", "yuanyang-lianhuantui");

        create_family("ȫ���", 2, "����");

        set("book_count",1);
        set("inquiry", ([
                "������" :  (:ask_chongyang():),
				"���Ǳ���" :  (:ask_baojian():),
        ]) );
		set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: perform_action, "sword.sanqing" :),
                (: perform_action, "sword.qixing" :),
                (: perform_action, "sword.ding" :),
				(: perform_action, "sword.jianqi" :),
                (: perform_action, "sword.lian" :),
				(: exert_function, "daojue" :),
				(: exert_function, "wuqi" :),
				(: exert_function, "yusuo" :),
               
        }));
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}


void attempt_apprentice(object ob)
{
       if (ob->query("gender")!="Ů��")
       {
		   command("say ��һ�����˼�������Ϊʦ���ѵ�����ʲô��ͼ���ɣ���\n");
		   command("say ��ȫ��һ��������ȫ���ڵ���Ϊ�ϣ�����Ǭ���������Ҳ��ó���\n");
		   command("say �㻹��ȥѰ��ȫ���������ӣ��������Ƿ����㣿\n");
		   return ;

       }

	   if ((int)ob->query("shen") < 2000000) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����(2m)");
               return;
       }
	   if (ob->query("party/gongji") < 3000) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڽ��ɹ������棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����(��Ҫ3000�����ɹ���ֵ)\n");
               return;
       }
	   if (!ob->query("quest/qz/dichuan"))
	   {
		       command("say ��������еմ����ӣ�����������");
              return;

	   }
	   if (ob->query_skill("xiantian-gong",1) < 350) {
               command("say ��ȫ���һ����ȫ�����칦�������칦����350��������������");
               return;
       }
	 
       command("say �ðɣ�ƶ�����������ˡ�");
       command("recruit " + ob->query("id"));
       ob->set("title", "ȫ�������״�����");
       ob->set("class","taoism");
	   return;
}
string ask_chongyang()
{
	object me;
	me=this_player();
	if (me->query("family/family_name")!="ȫ���")
	{
		command("say ����������Ե�޹ʣ�Ϊ���д�һ�ʣ�\n");
		return "�ߣ�\n";
	}
	if (me->query("family/generation")>3)
	{
		command("say ����������ӣ�����ȥ�����ͱ���ô��\n");
		return "�ߣ�\n";
	}
	if (!me->query("quest/qz/dichuan"))
	{
		command("say ������ɵմ���Ϊ���д�һ�ʣ�\n");
		return "�ߣ�\n";
	}
	if (me->query("party/gongji")<100)
	{
		command("say ������ɹ���ֵ����100���޹�������»��\n");
		return "�ߣ�\n";
	}
	command("say ÿ�ν��ñ��ﶼ���۳����100�����ɹ���ֵ��\n");
	command("say �������������֮�ף����ͳƺ�Ϊ������ͨ��\n");
	command("say �����������ӵ�ʦ����ʦ�������Ƕ�����ɽ\n");
	command("say ������������Ψһ��Ů�ԣ�Ϊ�������Ա������⽫���Ǳ������ҷ���\n");
	me->set_temp("qixing/asksun",1);
	return "���Ǳ�������ȫ����������ϱ��\n";
}

string ask_baojian()
{
	object me,ob;
	object room;
	me=this_player();
	room=load_object("/d/quanzhen/qingjing");

	if (me->query("family/family_name")!="ȫ���")
	{
		command("say ����������Ե�޹ʣ�Ϊ���д�һ�ʣ�\n");
		return "�ߣ�\n";
	}
	if (file_name(environment(this_object()))!="/d/quanzhen/qingjing")
	{
		command("say �˵����������������Ķ�����\n");
		return "�ߣ�\n";
	}
	if (!me->query_temp("qixing/asksun"))
	{
		command("say ����ȫ�浱���øж�����֪��������ʦ��˭ô��\n");
		return "�ߣ�\n";
	}
	if (me->query_temp("qixing/gived"))
	{
		command("say �ҷ��Ų��Ǹ�����ô��\n");
		return "�ߣ�\n";
	}

/*	if ((int)room->query("qixing")<1)
	{
		command("say �Ҹհ���ѱ����͸����е����ˣ������������!\n");
		return "�����ȫ���Խ��Խ������!\n";
	}*/

	ob=unew("/clone/weapon/sword/qixing-jian");
	if (!objectp(ob)) 
	{
		command("say ���Ǳ���������������Ѿ������ˣ�\n");
		return "���Ǳ�����ʦ���͸��ҵı��\n";
	}
	ob->move(me);
//	environment(this_object())->add("qixing",-1);

	command("say �ã���Ȼ������ȫ����ĵ��ӣ����ҾͰ���ѱ����ݽ�����ã�\n");
	message_vision(HIC"$n���һ�Ѻ�������ı����ݸ�$N!\n"NOR,me,this_object());
	me->set_temp("qixing/gived",1);
	me->delete_temp("qixing/asksun");
	return "";
}