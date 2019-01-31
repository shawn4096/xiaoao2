// lan.c

#include <ansi.h>
inherit F_MASTER;
inherit NPC;
string ask_book();
string ask_dan();
string ask_xiezifen();
void create()
{
        set_name(HIB"�����"NOR, ({ "lan fenghuang", "lan", "fenghuang"}));
        set("long", "��Ů�Ӽ���΢�ƣ�˫�ۼ��󣬺�����ᡣ\n"+
        	    "���ƹ����½����置���������嶾�̡���ʹ���ַ��������أ����˷���ʤ����\n");
        set("title",HIY"�������  "HIB"�嶾�̽���"NOR);
        set("gender", "Ů��");
        set("age", 23);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("per", 25);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);

        set("max_qi", 9800);
        set("max_jing", 5600);
        set("eff_jingli", 5600);
        set("jiali", 150);
        set("combat_exp", 5500000);
		set("book_count",1);
		set("dan_count",3);

        set_skill("parry", 380);
        set_skill("poison", 200);
        set_skill("dodge", 380);
        set_skill("force", 380);
        set_skill("hand", 380);
		set_skill("whip", 380);
        set_skill("literate", 100);
        set_skill("huanmo-wubu", 380);        
        set_skill("tianmo-shou", 380);
		set_skill("tianmo-gong", 380);
        set_skill("wudu-bian", 380);
		set_skill("poison", 180);

        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
        map_skill("parry", "wudu-bian");
        map_skill("hand", "tianmo-shou");
		map_skill("whip", "wudu-bian");
        prepare_skill("hand", "tianmo-shou");
        
		set("chat_chance_combat", 40);
		set("chat_msg_combat", ({
  		(: perform_action, "whip.shuaichou" :),
  		(: perform_action, "whip.wudu" :),
		
		}));
		set("inquiry", ([
			"�嶾��" : "�嶾�������置��Ҫ�����ɣ����嶾��Ϊ����֮������",
			"�嶾�̶������"  : (: ask_book :),
			"�嶾�ⶾ��"  : (: ask_dan :),
			"������"  : (: ask_xiezifen :),

	]));
	    create_family("�������",9,"����");
       	setup();
		carry_object(MISC_D("cloth"))->wear();
		carry_object("clone/weapon/whip")->wield(); 
}
void attempt_apprentice(object ob)
{
     if(ob->query("str") < 25 ){
        command("say ��ϰ��ħ����Ҫ�ߵı��������������25���Ҳ����㣡");
        return;
        }
	 if(!ob->query("family") || ob->query("family/family_name")!="�������" ){
        command("say ��������ʦ�����˺θɣ�");
        return;
        }
	 if(ob->query("gender") =="����" ){
        command("say Ů���Ӻ����鷳���ҿ��㻹��ȥѰ��������˿�������˵����������Ů���ӣ���");
        return;
        }
	 if(ob->query("gender") =="����" ){
        command("say �����ֲ��в�Ů�Ļ�ɫ������Ϊʦ����");
        return;
        }
     command("haha");
	 command("say �ðɣ�Ϊ�˹��������̣��Ҿ��������ˡ�");
     command("recruit " + ob->query("id"));
}

string ask_book()
{
	object me=this_player();
	object book;
	book=new("d/hmy/obj/poison-book.c");
	if (me->query("family/family_name") !="�������")
	{
		command("say �㲻���Ҵ�������̵��ӣ�������϶��ô��\n");
		return "���Ĳ��Ű���";
	}
	if (me->query("generation")>10)
	{
		command("say ��ı���̫���ˣ��ӽ�Ŭ����\n");
		return "��������ӣ�\n";
	}
	if (query("book_count")<0)
	{
		command("say �ؼ��Ѿ�Ϊ���е��������ˣ����������!\n");
		return "�Ҵ����µĶ���ؽ��������֣�\n";
	}
	book->move(me);
	add("book_count",-1);
	message_vision(HIY"$N�ݸ�$nһ���ؼ���\n"NOR,this_object(),me);
	return "��������̵��嶾��Ϊ��������ѧ�����ݺ�����δ�����ɣ�\n";
}
string ask_dan()
{
	object me=this_player();
	object dan;
	dan=new("d/hmy/obj/wududan.c");
	if (me->query("family/family_name") !="�������")
	{
		command("say �㲻���Ҵ�������̵��ӣ�������϶��ô��\n");
		command("smile "+me->query("id"));
		return "С����һ�Ŷ�ҩ�����㣡";
	}

	if (query("dan_count")<0)
	{
		command("say �����ϵĶ����պ÷����ˣ����������!\n");
		return "";
	}
	dan->set("owner",me->query("id"));
	dan->move(me);
	add("dan_count",-1);
	message_vision(HIY"$N�ݸ�$nһ���嶾����\n"NOR,this_object(),me);
	return "��������̵��嶾��������Ч�ķ�ֹ�嶾���ӣ�\n";
}

                                                                                 
string ask_xiezifen()
{
	object me,ob;
	me=this_player();
	
	if (!me->query_temp("quest/kl/klz/hongsha/asklan"))
	{
		command("say ������Ե�޹ʣ������Һ��£���\n");
		return "";
	}
	command("say �ðɣ�ԭ����������ɰ��֮�á�\n");
	command("say ��Ȼ��ˣ��Ҿ͸���һ�ݣ�������綾����Ҫ����ͿĨ(tumo)��\n");
	me->delete_temp("quest/kl/klz/hongsha/asklan");

 //   me->set_temp("quest/kl/klz/hongsha/kegive",1);
	ob=new("d/miaojiang/obj/xiezifen");
	ob->move(me);
	return "��Щ���ᣡ\n";
}

