// miaoke.c��� 
// by sohu
// ��ҩid
#include <ansi.h>

inherit NPC;
//inherit F_MASTER;
int ask_jingjie();
int ask_miji();
int ask_lianwan();
int ask_fail();
int ask_fangqi();

void create()
{
        set_name("���", ({ "miao ke", "miaoke" ,"ke"}));
        set("long",@LONG
���Ǳ���ʦ���µĵմ�����֮һ���ڼ��������й������Ϊ����
������Ұ�����Ƹ���ҩ�ģ����Ե���������������ｻ����������Ȼ��
�Ƴ�Ѫ���ž���ҩ�衣������֣�״��������������Ц�ݣ�һ��������
�������ӡ�
LONG
        );
        set("title", "Ѫ���ŵ���������" NOR);
        set("gender", "����");
		set("class", "huanxi");
        set("age", 35);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 13200);
        set("eff_jing", 3500);
		set("max_jing",3500);
		set("eff_jingli", 3500);
        set("neili", 13500);
        set("max_neili", 13500);
        set("jiali", 150);
        set("combat_exp", 4700000);
        set("score", 5000);
		set("unique", 1);

        set_skill("huanxi-chan", 150);
        set_skill("literate", 100);
        set_skill("force", 350);
        set_skill("xuedao-jing", 400);
        set_skill("dodge", 350);
        set_skill("xueying-dunxing", 350);
        set_skill("xuedao-daofa", 400);
        set_skill("parry", 350);
        set_skill("strike", 350);
        set_skill("blade", 400);
       // set_skill("hand", 350 );
        set_skill("jingang-liantishu", 400 );

        map_skill("force", "xuedao-jing");
        map_skill("dodge", "xueying-dunxing");
        map_skill("strike", "hongsha-zhang");
        map_skill("parry", "xuedao-daofa");
        map_skill("blade", "xuedao-daofa");

        prepare_skill("strike","hongsha-zhang");

        create_family("Ѫ����",6, "����");
		set("chat_chance_combat", 65);
		set("chat_msg_combat", ({
			(: perform_action, "blade.chuanxin" :),
			(: perform_action, "blade.liuxing" :),
			(: perform_action, "blade.bafang" :),
			(: perform_action, "blade.chilian" :),
			(: exert_function, "yuxue" :),			
			(: perform_action, "dodge.xueying" :),
		}));
		set("inquiry",([
		"Ѫ������"	: (: ask_jingjie :),
		"����"	: (: ask_lianwan :),
		"�ؼ�"	: (: ask_miji :),
		"��������"	: (: ask_fail :),
		"��������"	: (: ask_fangqi :),

		]));


        setup();
        carry_object("/d/xueshan/npc/obj/gongde-jiasha")->wear();
        carry_object(BINGQI_D("xinyuedao"))->wield();        

        add_money("silver",20+random(10));
}

int ask_jingjie()
{
	object me;
	me=this_player();
	if (me->query("family/family_name")!="Ѫ����")
	{
		return notify_fail("�㲻����Ѫ���ŵ��ӣ�����������\n");
	}
	if (me->query("combat_exp")>2000000)
	{
		return notify_fail("����书�Ѿ��㹻�ݺὭ���ˣ�����Щ�������ᶼ�ø����ʦ��ʦ���ǰɣ�\n");
	}

	command("say ��Ȼ���Ѿ�������Ѫ���ɵ��ӣ���ΪѪ��������������\n");
	command("say ��Ѫ����֮�������ڳɳ��Ͽ죬��Ҫ��ԭ����������һ�Ŷ������ط���\n");
	command("say ����ͨ��Ѫ��������Ѫ���еľ��������ɡ����⡱������Ѫ�����ӣ��ӿ��书������\n");
	command("say ������Щ��Ϊ��������ʿһֱ�����ǵ�������а����ʱ�����˸������е���������\n");

	command("say ���������ɲ���֮�أ����Ȼ�Ѿ���Ϊ���е��ӣ�����Ϊ������Щ���ף�\n");
	command("say �ڴ˴��úþ���������֣����������뿪�����������Ѫ����\n");
	command("say ����ָ��(jingjie ͭ��)���Ϳ��Կ�ʼ�����Ҫ�뿪������(leave)\n");
	me->set_temp("xdjj/askmiaoke",1);
	return 1;
		
}

int ask_miji()
{
	object me,ob;
	me=this_player();
	if (me->query("family/family_name")!="Ѫ����")
	{
		return notify_fail("�㲻����Ѫ���ŵ��ӣ�����������\n");
	}
	if (!me->query("quest/xd/dichuan"))
	{
		return notify_fail("�㲻����Ѫ���ŵմ����ӣ�����������\n");
	}
	command("say ��Ȼ���Ѿ�������Ѫ���ŵմ����ӣ��Ҿ͸����Ȿ��ʱ�־�����\n");
	command("say �Ȿ����Ҫ�ú��ж������ɹ������ҵ�һ��������\n");
	ob=new("d/xuedao/obj/huanxi_book2");
	ob->move(me);
	command("pat "+me->query("id"));
	command("say Ѫ���ŵ����ˣ�\n");
	return 1;
		
}

int ask_lianwan()
{
	object me;
	me=this_player();
	
	if (me->query("family/family_name")!="Ѫ����")
	{
		command("say �㲻����Ѫ���ŵ��ӣ�����������\n");
		return 1;
	}
	if (me->query("job_time/Ѫ������")<200)
	{
		command("say ����Դ�������200�Σ������͸㲻�����裿\n");
		return 1;
	}
	if (me->query_skill("medicine",1)<100)
	{
		command("say ���ҽѧ���ܲ���100�Σ���Ϲ�����ˣ�\n\n");
		return 1;
	}


	if (me->query_temp("xd/lianwan/askke"))
	{
		command("say ���Ѿ�����˵�˰���\n");
		return 1;
	}
	if (me->query_temp("lianwan_tick"))
	{
		command("say �������������У�\n");
		return 1;
	}
	command("say �ã���������������ǰ�ڻ��۵�һЩѪ�⣬��Ϳ�ʼ�����Ӱɣ�\n");
	command("say ǧ��Ҫע����ͼ��ɣ�\n");

	command("say ������Խ�࣬Խ���׳ɹ���\n");
	message_vision(HIY"$N��һ�Ե�ľ����ȡ��¹�⡢���⡢�����⡢ӥ�⡢�������һЩ����ѪҺ���ݸ���$n��\n"NOR,this_object(),me);
	command("say ������������������Լ����ã����������д��棡\n");
	command("say "+me->query("name")+"��Ҳ�����͸���������Ƚϴ�ĳ��ϣ����ǱϾ���Ѫ���㣬������Ҫ��\n");
	command("say "+me->query("name")+"��ǧ��Ҫע����\n");
	me->set_temp("xd/lianwan/askke",1);
	return 1;
		
}
//����ʧ��job

int ask_fail()
{
	object me,ob;
	me=this_player();
	if (me->query_temp("xdjj/askmiaoke"))
	{
		command("say ��Ȼ���겻��Ѫ�������������ʱ��ȥЪϢȥ��,�ߣ�\n");
		me->delete_temp("xdjj/askmiaoke");

	} else command("say ��ʲô��û����Ϲ����ʲô��\n");

	me->delete_temp("xdjj");
	me->apply_condtion("job_busy",35);
	command("say "+me->query("name")+"�����˴��������ӵ���Ѫ����������\n");
	return 1;
}

int ask_fangqi()
{
	object me,ob;
	me=this_player();
	if (me->query_temp("xd/lianwan/askke"))
	{
		command("say ��Ȼ���겻�������������ʱ��ȥЪϢȥ��,�ߣ�\n");
		me->delete_temp("xdjj/askmiaoke");
		

	} else command("say ��ʲô��û����Ϲ����ʲô��\n");


	me->delete_temp("xd");
	me->apply_condtion("job_busy",35);
	environment(this_object())->delete("lianwan");
	command("say "+me->query("name")+"�����˴�������ӵ�����������\n");
	return 1;
}